#include <iostream>
#include <cstdlib>

#include "ovpCVncBox.h"

using namespace OpenViBEPlugins::VNC;

CVncBox::CVncBox() : m_pSocket(0), m_oBufferIn(2048), m_oBufferOut(2048), m_oActionsMapping(), m_oRfbActor()
{
}

void	CVncBox::release(void)
{
  this->m_pSocket->release();
  delete this;
}

OpenViBE::boolean CVncBox::initialize(void)
{
  OpenViBE::Kernel::IBox const * l_pStaticBoxContext = this->getBoxAlgorithmContext()->getStaticBoxContext();

  this->m_oRfbActor.initialize(FSettingValueAutoCast(*this->getBoxAlgorithmContext(), 2), &(this->getLogManager()));

  for (unsigned int l_uint32ActionId = ACTION_MOUSEL,
	 l_uint32SettingIndex = 3; // Le premier setting qui nous interesse est "Move left mouse" son index est 3
       l_uint32SettingIndex < l_pStaticBoxContext->getSettingCount(); ++l_uint32ActionId, ++l_uint32SettingIndex)
    {
      this->m_oActionsMapping.insert(std::pair<OpenViBE::uint64, EAction>(FSettingValueAutoCast(*this->getBoxAlgorithmContext(), l_uint32SettingIndex), static_cast<EAction>(l_uint32ActionId)));
    }

  // Boucle de debug a supprimer
  for (std::map<OpenViBE::uint64, EAction>::const_iterator it = this->m_oActionsMapping.begin(), itEnd = this->m_oActionsMapping.end(); it != itEnd; ++it)
    {
      std::cerr << this->getTypeManager().getEnumerationEntryNameFromValue(OV_TypeId_Stimulation, it->first) << " --> " << it->second << std::endl;
    }

  this->m_pSocket = Socket::createConnectionClient();
  OpenViBE::CString l_sHostname, l_sPort;
  l_pStaticBoxContext->getSettingValue(0, l_sHostname);
  l_pStaticBoxContext->getSettingValue(1, l_sPort);
  this->m_pSocket->connect(l_sHostname, atoi(l_sPort));

  this->m_pStimulationDecoder= &this->getAlgorithmManager().getAlgorithm(this->getAlgorithmManager().createAlgorithm(OVP_GD_ClassId_Algorithm_StimulationStreamDecoder));
  this->m_pStimulationDecoder->initialize();

  this->ip_pMemoryBuffer.initialize(m_pStimulationDecoder->getInputParameter(OVP_GD_Algorithm_StimulationStreamDecoder_InputParameterId_MemoryBufferToDecode));
  this->op_pStimulationSet.initialize(m_pStimulationDecoder->getOutputParameter(OVP_GD_Algorithm_StimulationStreamDecoder_OutputParameterId_StimulationSet));
  return (this->m_pSocket->isConnected());
}

OpenViBE::boolean CVncBox::uninitialize(void)
{
  this->op_pStimulationSet.uninitialize();
  this->ip_pMemoryBuffer.uninitialize();
  this->m_pStimulationDecoder->uninitialize();
  this->getAlgorithmManager().releaseAlgorithm(*(this->m_pStimulationDecoder));
  return (true);
}

OpenViBE::boolean CVncBox::processInput(OpenViBE::uint32 ui32InputIndex)
{
  std::cerr << "~~~~~~~~~~~~~~~~~~~~~~~~~~CVncBox::processInput~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;

  if (!this->m_oRfbActor.isInitProcessFinish())
    {
      this->receiveBuffer();
      boost::circular_buffer<char> const & l_rParseResult = this->m_oRfbActor.parse(this->m_oBufferIn);
      this->sendBuffer(l_rParseResult);
    }
  if (this->m_oRfbActor.isInitProcessFinish())
    {
      this->getBoxAlgorithmContext()->markAlgorithmAsReadyToProcess();
    }
  return (true);
}

OpenViBE::boolean CVncBox::process(void)
{
  std::cerr << "~~~~~~~~~~~~~~~~~~~~~~~~~~ [CVncBox::process] ~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;

  OpenViBE::Kernel::IBoxIO & l_rDynamicBoxContext = this->getDynamicBoxContext();

  for(OpenViBE::uint32 l_uint32I = 0; l_uint32I < l_rDynamicBoxContext.getInputChunkCount(0) && this->m_pSocket->isReadyToSend(); ++l_uint32I)
    {
      this->ip_pMemoryBuffer = l_rDynamicBoxContext.getInputChunk(0, l_uint32I);
      this->m_pStimulationDecoder->process();
      if(this->m_pStimulationDecoder->isOutputTriggerActive(OVP_GD_Algorithm_StimulationStreamDecoder_OutputTriggerId_ReceivedBuffer))
	{
	  for(OpenViBE::uint64 l_uint64K = 0; l_uint64K < this->op_pStimulationSet->getStimulationCount(); l_uint64K++)
	    {
	      std::cerr << "Stimulation["<< l_uint64K<< "] - Id = " << op_pStimulationSet->getStimulationIdentifier(l_uint64K) << " = " << this->getTypeManager().getEnumerationEntryNameFromValue(OV_TypeId_Stimulation, op_pStimulationSet->getStimulationIdentifier(l_uint64K)) << std::endl;
	      std::map<OpenViBE::uint64, EAction>::const_iterator l_oItSearch = this->m_oActionsMapping.find(op_pStimulationSet->getStimulationIdentifier(l_uint64K));
	      if (l_oItSearch != this->m_oActionsMapping.end())
		{
		  boost::circular_buffer<char> const & l_rExecResult = this->m_oRfbActor.execute(l_oItSearch->second);
		  this->sendBuffer(l_rExecResult);
		}
	    }
	  l_rDynamicBoxContext.markInputAsDeprecated(0, l_uint32I);
	}
    }
  return (true);
}

void CVncBox::receiveBuffer()
{
  std::cerr << "~~~~~~~~~~~~~~~~~~~~~~~~~~ [CVncBox::receiveBuffer] ~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;

  if (this->m_pSocket->isReadyToReceive())
    {
      char l_pBuffer[1024];
      Socket::uint32 l_uint32BytesReceived = this->m_pSocket->receiveBuffer(l_pBuffer, 1024);
      std::cerr << "Lecture de " << l_uint32BytesReceived << " octets sur la socket."<< std::endl;
      if (l_uint32BytesReceived != 0)
	{
	  this->getLogManager() << OpenViBE::Kernel::LogLevel_Info << l_uint32BytesReceived << "bytes received\n";
	  std::cerr << "Taille du buffer d'entre avant remplissage : " << this->m_oBufferIn.size() << " octets." << std::endl;
	  this->m_oBufferIn.insert(this->m_oBufferIn.end(), l_pBuffer, l_pBuffer + l_uint32BytesReceived);
	  std::cerr << "Taille du buffer d'entre apres remplissage : "<< this->m_oBufferIn.size() << " octets." << std::endl;
	}
    }
}

void CVncBox::sendBuffer(boost::circular_buffer<char> const & rInputBuffer)
{
  std::cerr << "~~~~~~~~~~~~~~~~~~~~~~~~~~ [CVncBox::sendBuffer] ~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;

  if (!rInputBuffer.empty())
    {
      std::cerr << "Ajout au buffer de sortie de "<< rInputBuffer.size() << " octets."<< std::endl;
      this->m_oBufferOut.insert(this->m_oBufferIn.end(), rInputBuffer.begin(), rInputBuffer.end());
      if (!this->m_oBufferOut.empty() && this->m_pSocket->isReadyToSend())
	{
	  std::cerr << "Tentative d'envoie de " << this->m_oBufferOut.size()<< " octets."<< std::endl;
	  Socket::uint32 l_uint32BytesSend = this->m_pSocket->sendBuffer(this->m_oBufferOut.linearize(), this->m_oBufferOut.size());
	  this->getLogManager() << OpenViBE::Kernel::LogLevel_Info << l_uint32BytesSend << "bytes send of" << static_cast<Socket::uint32>(this->m_oBufferOut.size()) << "expected\n";
	  std::cerr << "Nombre d'octets envoyes : " << l_uint32BytesSend << std::endl;
	  this->m_oBufferOut.erase_begin(l_uint32BytesSend);
	  std::cerr << "Taille du buffer de sortie apres nettoyage :"<< this->m_oBufferOut.size() << " octets." << std::endl;
	}
    }
}

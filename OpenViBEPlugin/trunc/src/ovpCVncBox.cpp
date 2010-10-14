#include <iostream>
#include <cstdlib>

#include "ovpCVncBox.h"

using namespace OpenViBE;
using namespace OpenViBE::Plugins;
using namespace OpenViBE::Kernel;
using namespace OpenViBEPlugins;
using namespace OpenViBEPlugins::VNC;
using namespace OpenViBEToolkit;

CVncBox::CVncBox() : _socket(0), _bufferIn(2048), _bufferOut(2048), _actionsMapping(), _protocolClientRFB()
{
}

void	CVncBox::release(void)
{
  this->_socket->release(); // effectue le close de la socket
  delete this;
}

OpenViBE::boolean CVncBox::initialize(void)
{
  const IBox* l_pStaticBoxContext = this->getBoxAlgorithmContext()->getStaticBoxContext();

  this->_protocolClientRFB.initialize(FSettingValueAutoCast(*this->getBoxAlgorithmContext(), 2));

  for (unsigned int actionId = ACTION_MOUSEL,
	 settingIndex = 3; // Le premier setting qui nous interesse est "Move left mouse" son index est 3
       settingIndex < l_pStaticBoxContext->getSettingCount(); ++actionId, ++settingIndex)
    {
      this->_actionsMapping.insert(std::pair<OpenViBE::uint64, Action>(FSettingValueAutoCast(*this->getBoxAlgorithmContext(), settingIndex), static_cast<Action>(actionId)));
    }
  
  // debug, faire une boucle pour la partie du dessus pour eviter la repetition de code
  for (std::map<OpenViBE::uint64, Action>::const_iterator it = this->_actionsMapping.begin(), itEnd = this->_actionsMapping.end(); it != itEnd; ++it)
    {
      std::cerr << it->first << " --> " << it->second << std::endl;
    }

  this->_socket = Socket::createConnectionClient();
  CString l_sHostname, l_sPort;
  l_pStaticBoxContext->getSettingValue(0, l_sHostname);
  l_pStaticBoxContext->getSettingValue(1, l_sPort);
  this->_socket->connect(l_sHostname, atoi(l_sPort));

  this->m_pStimulationDecoder= &this->getAlgorithmManager().getAlgorithm(this->getAlgorithmManager().createAlgorithm(OVP_GD_ClassId_Algorithm_StimulationStreamDecoder)); // On recupere une instance de l'algorithme
  this->m_pStimulationDecoder->initialize();

  this->ip_pMemoryBuffer.initialize(m_pStimulationDecoder->getInputParameter(OVP_GD_Algorithm_StimulationStreamDecoder_InputParameterId_MemoryBufferToDecode)); // On map l'input de la box sur l'input de l'algorithme
  this->op_pStimulationSet.initialize(m_pStimulationDecoder->getOutputParameter(OVP_GD_Algorithm_StimulationStreamDecoder_OutputParameterId_StimulationSet)); // On map l'ouput de l'algorithme sur un attribut de la box
  return (this->_socket->isConnected());
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
  if (!this->_protocolClientRFB.isInitProcessFinish())
    {
      this->receiveBuffer();
      VncResult result = this->_protocolClientRFB.parse(this->_bufferIn);
      this->sendBuffer(result);
    }
  if (this->_protocolClientRFB.isInitProcessFinish())
    {
      this->getBoxAlgorithmContext()->markAlgorithmAsReadyToProcess();
    }
  return (true);
}

OpenViBE::boolean CVncBox::process(void)
{
  std::cerr << "~~~~~~~~~~~~~~~~~~~~~~~~~~ [CVncBox::process] ~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
  IBoxIO& l_rDynamicBoxContext = this->getDynamicBoxContext();
  // On parcours les chunks tant que l'on peut ecrire sur le reseau
  for(uint32 i = 0; i < l_rDynamicBoxContext.getInputChunkCount(0) && this->_socket->isReadyToSend(); ++i)
    {
      this->ip_pMemoryBuffer = l_rDynamicBoxContext.getInputChunk(0, i);
      this->m_pStimulationDecoder->process();
      std::cerr << "Buffer en cours decodage" << std::endl;
      if(this->m_pStimulationDecoder->isOutputTriggerActive(OVP_GD_Algorithm_StimulationStreamDecoder_OutputTriggerId_ReceivedBuffer))
	{
	  // Un buffer peut contenir plusieurs Stimulation
	  std::cerr << "Buffer decode" << std::endl << "getStimulationCount = " << op_pStimulationSet->getStimulationCount() << std::endl;
	  for(uint64 s = 0; s < this->op_pStimulationSet->getStimulationCount(); s++)
	    {
	      std::cerr << "Stimulation["<< s<< "] - Id = " << op_pStimulationSet->getStimulationIdentifier(s) << std::endl;
	      std::map<OpenViBE::uint64, Action>::const_iterator itSearch = this->_actionsMapping.find(op_pStimulationSet->getStimulationIdentifier(s));
	      if (itSearch != this->_actionsMapping.end())
		{
		  VncResult result = this->_protocolClientRFB.execute(itSearch->second);
		  this->sendBuffer(result);
		}
	    }
	  l_rDynamicBoxContext.markInputAsDeprecated(0, i);
	}
    }
  return (true);
}

void CVncBox::receiveBuffer()
{
  std::cerr << "~~~~~~~~~~~~~~~~~~~~~~~~~~ [CVncBox::receiveBuffer] ~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
  std::cerr << "Socket ready to read ?" << std::boolalpha << this->_socket->isReadyToReceive() << std::endl;
  if (this->_socket->isReadyToReceive())
    {
      char networkBuffer[1024];
      Socket::uint32 bytesReceived = this->_socket->receiveBuffer(networkBuffer, 1024);
      std::cerr << "Lecture de " << bytesReceived << " octets sur la socket."<< std::endl;
      if (bytesReceived != 0)
	{
	  std::cerr << "Taille du buffer d'entre avant remplissage : " << this->_bufferIn.size() << " octets." << std::endl;
	  this->_bufferIn.insert(this->_bufferIn.end(), networkBuffer, networkBuffer + bytesReceived);
	  std::cerr << "Taille du buffer d'entre apres remplissage : "<< this->_bufferIn.size() << " octets." << std::endl;
	}
    }
}

void CVncBox::sendBuffer(VncResult const & bufferToSend)
{
  std::cerr << "~~~~~~~~~~~~~~~~~~~~~~~~~~ [CVncBox::VncResult] ~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
  if (bufferToSend.second != 0)
    {
      std::cerr << "sendBuffer\tAjout au buffer de sortie de "<< bufferToSend.second << " octets."<< std::endl;
      this->_bufferOut.insert(this->_bufferIn.end(), bufferToSend.first, bufferToSend.first + bufferToSend.second);
      if (!this->_bufferOut.empty() && this->_socket->isReadyToSend())
	{
	  std::cerr << "Tentative d'envoie de " << this->_bufferOut.size()<< " octets."<< std::endl;
	  Socket::uint32 bytesSend = this->_socket->sendBuffer(this->_bufferOut.linearize(), this->_bufferOut.size());
	  std::cerr << "Nombre d'octets envoyes : " << bytesSend << std::endl;
	  this->_bufferOut.erase_begin(bytesSend);
	  std::cerr << "Taille du buffer de sortie apres nettoyage :"<< this->_bufferOut.size() << " octets." << std::endl;
	}
    }
}

#include <iostream>
#include <cstdlib>

#include "ovpCVncBox.h"

using namespace OpenViBE;
using namespace OpenViBE::Plugins;
using namespace OpenViBE::Kernel;
using namespace OpenViBEPlugins;
using namespace OpenViBEPlugins::VNC;
using namespace OpenViBEToolkit;

CVncBox::CVncBox() : _socket(0), _actionsMapping(), _mouveMoveDistance(0)
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

  this->_mouveMoveDistance = FSettingValueAutoCast(*this->getBoxAlgorithmContext(), 2);

  for (unsigned int actionId = ACTION_MOUSEL,
	 settingIndex = 3; // Le premier setting qui nous interesse est "Move left mouse" son index est 3
       settingIndex < l_pStaticBoxContext->getSettingCount(); ++actionId, ++settingIndex)
    {
      this->_actionsMapping.insert(std::pair<Action, OpenViBE::uint64>(static_cast<Action>(actionId), FSettingValueAutoCast(*this->getBoxAlgorithmContext(), settingIndex)));
    }
  
  // debug, faire une boucle pour la partie du dessus pour eviter la repetition de code
  for (std::map<Action, OpenViBE::uint64>::const_iterator it = this->_actionsMapping.begin(), itEnd = this->_actionsMapping.end(); it != itEnd; ++it)
    {
      std::cerr << it->first << " --> " << it->second << std::endl;
    }

  this->_socket = Socket::createConnectionClient();
  CString l_sHostname, l_sPort;
  l_pStaticBoxContext->getSettingValue(0, l_sHostname);
  l_pStaticBoxContext->getSettingValue(1, l_sPort);
  this->_socket->connect(l_sHostname, atoi(l_sPort));

  m_pStimulationDecoder= &this->getAlgorithmManager().getAlgorithm(this->getAlgorithmManager().createAlgorithm(OVP_GD_ClassId_Algorithm_StimulationStreamDecoder)); // On recupere une instance de l'algorithme
  m_pStimulationDecoder->initialize();

  ip_pMemoryBuffer.initialize(m_pStimulationDecoder->getInputParameter(OVP_GD_Algorithm_StimulationStreamDecoder_InputParameterId_MemoryBufferToDecode)); // On map l'input de la box sur l'input de l'algorithme
  op_pStimulationSet.initialize(m_pStimulationDecoder->getOutputParameter(OVP_GD_Algorithm_StimulationStreamDecoder_OutputParameterId_StimulationSet)); // On map l'ouput de l'algorithme sur un attribut de la box

  return (this->_socket->isConnected());
}

OpenViBE::boolean CVncBox::uninitialize(void)
{
  op_pStimulationSet.uninitialize();
  ip_pMemoryBuffer.uninitialize();
  m_pStimulationDecoder->uninitialize();
  this->getAlgorithmManager().releaseAlgorithm(*m_pStimulationDecoder);
  return (true);
}

OpenViBE::boolean CVncBox::processInput(OpenViBE::uint32 ui32InputIndex)
{
  std::cerr << "~~~~~~~~~~~~~~~~~~~~~~~~~~CVncBox::processInput~~~~~~~~~~~~~~~~~~~~~~~~~~ = " << std::endl;
  if (this->_socket->isConnected() == false)
    return (false);
  // En fait tant que la phase initiale de connexion/securite n'est pas finie tu ne rentres pas dans le if
  if (true)
    {
      // seulement une fois que tu apelles la methode de la ligne du dessous que la methode CVncBox::process sera apelle
      this->getBoxAlgorithmContext()->markAlgorithmAsReadyToProcess();
    }
  return (true);
}

OpenViBE::boolean CVncBox::process(void)
{
  std::cerr << "~~~~~~~~~~~~~~~~~~~~~~~~~~CVncBox::process~~~~~~~~~~~~~~~~~~~~~~~~~~ = " << std::endl;
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
	      std::cerr << "Stimulation["<< s<< "] - Id = " << op_pStimulationSet->getStimulationIdentifier(s) << std::endl
			<< "Date = "<< op_pStimulationSet->getStimulationDate(s) << std::endl
			<< "Duration = " << op_pStimulationSet->getStimulationDuration(s) << std::endl << std::endl;
	      /*
		Faire des locate pour trouver les fichiers !
		Exemple pour le reseau dans ovpCGenericNetworkAcquisition.h
		Pour connaitre les methodes disponibles a _socket voir le fichier IConnection.h
	      */
	      // La valeur a utilisee est donc op_pStimulationSet->getStimulationIdentifier(s) <-------------------------------------------
	      /* 
		 La ligne suivante sera apelle uniquement lorsqu'on aura reussi a envoyer le packet en entier - packet relatif au chunk en cours :)
		 Donc il faudra faire un check si le sendBuffer retourne bien la meme valeur que la taille du packet qu'on a voulu envoyer
	      */

	    }
	  l_rDynamicBoxContext.markInputAsDeprecated(0, i);
	}
    }
  return (true);
}

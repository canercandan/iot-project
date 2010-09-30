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

  CString l_sDistance, l_sMouseL, l_sMouseR, l_sMouseU, l_sMouseD, l_sKey1, l_sKey2;
  l_pStaticBoxContext->getSettingValue(2, l_sDistance);
  l_pStaticBoxContext->getSettingValue(3, l_sMouseL);
  l_pStaticBoxContext->getSettingValue(4, l_sMouseR);
  l_pStaticBoxContext->getSettingValue(5, l_sMouseU);
  l_pStaticBoxContext->getSettingValue(6, l_sMouseD);
  l_pStaticBoxContext->getSettingValue(7, l_sKey1);
  l_pStaticBoxContext->getSettingValue(8, l_sKey2);
  this->_mouveMoveDistance = atoi(l_sDistance);
  this->_actionsMapping.insert(std::pair<Action, int>(ACTION_MOUSEL, atoi(l_sMouseL)));
  this->_actionsMapping.insert(std::pair<Action, int>(ACTION_MOUSER, atoi(l_sMouseR)));
  this->_actionsMapping.insert(std::pair<Action, int>(ACTION_MOUSEU, atoi(l_sMouseU)));
  this->_actionsMapping.insert(std::pair<Action, int>(ACTION_MOUSED, atoi(l_sMouseD)));
  this->_actionsMapping.insert(std::pair<Action, int>(ACTION_KEY1, atoi(l_sKey1)));
  this->_actionsMapping.insert(std::pair<Action, int>(ACTION_KEY2, atoi(l_sKey2)));
  // debug, faire une boucle pour la partie du dessus pour eviter la repetition de code
  for (std::map<Action, int>::const_iterator it = this->_actionsMapping.begin(), itEnd = this->_actionsMapping.end(); it != itEnd; ++it)
    {
      std::cerr << it->first << " --> " << it->second << std::endl;
    }

  CString l_sServerHostPort, l_sServerHostName;
  l_pStaticBoxContext->getSettingValue(0, l_sServerHostName);
  l_pStaticBoxContext->getSettingValue(1, l_sServerHostPort);
  this->_socket = Socket::createConnectionClient();
  std::cerr << "Trying to connect at : " << l_sServerHostName << "(" << l_sServerHostPort << ")" << std::endl;
  this->_socket->connect(l_sServerHostName, atoi(l_sServerHostPort));
  std::cerr << "Connected ? " << std::boolalpha << this->_socket->isConnected() << std::endl;
  return (this->_socket->isConnected());
}

OpenViBE::boolean CVncBox::uninitialize(void)
{
  return (true);
}

OpenViBE::boolean CVncBox::processInput(OpenViBE::uint32 ui32InputIndex)
{
  std::cerr << "~~~~~~~~~~~~~~~~~~~~~~~~~~CVncBox::processInput~~~~~~~~~~~~~~~~~~~~~~~~~~ = " << ui32InputIndex << std::endl;
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
      std::cerr << "Item[" << i << "] = " << l_rDynamicBoxContext.getInputChunk(0, i) << " - Size du chunk = " << l_rDynamicBoxContext.getInputChunk(0, i)->getSize() << std::endl;
      /*
	Faire des locate pour trouver les fichiers !
	Exemple pour le reseau dans ovpCGenericNetworkAcquisition.h
	Pour connaitre les methodes disponibles a _socket voir le fichier IConnection.h
      */
      /* Pour le moment pour faire tes test utilise en int en dure ! */
      /* 
	 La ligne suivante sera apelle uniquement lorsqu'on aura reussi a envoyer le packet en entier - packet relatif au chunk en cours :)
	 Donc il faudra faire un check si le sendBuffer retourne bien la meme valeur que la taille du packet qu'on a voulu envoyer
      */
      l_rDynamicBoxContext.markInputAsDeprecated(0, i);
    }
  return (true);
}

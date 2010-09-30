#include "ovpCVncBox.h"

using namespace OpenViBE;
using namespace OpenViBE::Plugins;
using namespace OpenViBE::Kernel;
using namespace OpenViBEPlugins;
using namespace OpenViBEPlugins::VNC;
using namespace OpenViBEToolkit;


/*
  Exemple pour le reseau ovpCGenericNetworkAcquisition.h
  Exemple pour l output regarde le clavier virtuel
*/
void	CVncBox::release(void)
{
  this->_socket->release(); // effectue le close
  delete this;
}

OpenViBE::boolean CVncBox::initialize(void)
{
  const IBox* l_pStaticBoxContext = this->getBoxAlgorithmContext()->getStaticBoxContext();

  CString l_sServerHostPort, l_sServerHostName;
  this->l_pStaticBoxContext->getSettingValue(0, l_sServerHostName);
  this->l_pStaticBoxContext->getSettingValue(1, l_sServerHostPort);
  this->_socket = Socket::createConnectionClient();
  this->_socket->connect(l_sServerHostName, atoi(l_sServerHostPort));
  return (this->_socket->isConnected());
}

OpenViBE::boolean CVncBox::uninitialize(void)
{
  return (true);
}

OpenViBE::boolean CVncBox::processInput(OpenViBE::uint32 ui32InputIndex)
{
  std::cerr << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
  return (true);
}

OpenViBE::boolean CVncBox::process(void)
{
  if (this->_socket->isConnected() == false)
    return (false);
  return (true);
}

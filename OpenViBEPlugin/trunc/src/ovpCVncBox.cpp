#include "ovpCVncBox.h"

using namespace OpenViBE;
using namespace OpenViBE::Plugins;
using namespace OpenViBE::Kernel;
using namespace OpenViBEPlugins;
using namespace OpenViBEPlugins::VNC;
using namespace OpenViBEToolkit;

void	CVncBox::release(void)
{
  this->_socket->release();
  delete this;
}

OpenViBE::boolean CVncBox::initialize(void)
{
  IBox& l_rStaticBoxContext=this->getStaticBoxContext();



  this->_socket = Socket::createConnectionClient();
  this->_socket->connect(this->_hostName, this->_port);
  return (true);
}

OpenViBE::boolean CVncBox::uninitialize(void)
{
  this->_socket->close();
  return (true);
}

OpenViBE::boolean CVncBox::processInput(OpenViBE::uint32 ui32InputIndex)
{
  return (true);
}

OpenViBE::boolean CVncBox::process(void)
{
  return (true);
}

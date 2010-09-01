#include "ovpCVncBox.h"

using namespace OpenViBE;
using namespace OpenViBE::Plugins;
using namespace OpenViBE::Kernel;
using namespace OpenViBEPlugins;
using namespace OpenViBEPlugins::VNC;
using namespace OpenViBEToolkit;

void	CVncBox::release(void)
{
  delete this;
}

OpenViBE::boolean CVncBox::initialize(void)
{
  return (true);
}

OpenViBE::boolean CVncBox::uninitialize(void)
{
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

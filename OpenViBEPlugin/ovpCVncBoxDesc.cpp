#include "ovpCVncBoxDesc.h"

using namespace OpenViBE;
using namespace OpenViBE::Plugins;
using namespace OpenViBE::Kernel;
using namespace OpenViBEPlugins;
using namespace OpenViBEPlugins::VNC;
using namespace OpenViBEToolkit;

void				CVncBoxDesc::release(void)
{
}

OpenViBE::CString			CVncBoxDesc::getName(void) const
{
  return ("VNC");
}

OpenViBE::CString			CVncBoxDesc::getAuthorName(void) const
{
  return ("IOT Consortium");
}

OpenViBE::CString			CVncBoxDesc::getAuthorCompanyName(void) const
{
  return ("La Chamelle Club");
}

OpenViBE::CString			CVncBoxDesc::getShortDescription(void) const
{
  return ("Boite permettant d'interargir avec un serveur VNC (distant ou local) et donc de controller l'ordinateur par la pensee.");
}

OpenViBE::CString			CVncBoxDesc::getDetailedDescription(void) const
{
  return ("Il est possible d'envoyer des evenements souris mais aussi clavier. Le protocole VNC : RFB (Remote Frame Buffer) est utilisee.");
}

OpenViBE::CString			CVncBoxDesc::getCategory(void) const
{
  return ("vnc");
}

OpenViBE::CString			CVncBoxDesc::getVersion(void) const
{
  return ("1.0");
}

OpenViBE::CString			CVncBoxDesc::getStockItemName(void) const
{
  return ("");
}

OpenViBE::CIdentifier		CVncBoxDesc::getCreatedClass(void) const
{
  return (0);
}

OpenViBE::Plugins::IPluginObject* CVncBoxDesc::create(void)
{
  return (new OpenViBE::Plugins::VNC::CVncBox);
}

OpenViBE::boolean			CVncBoxDesc::getBoxPrototype(OpenViBE::Kernel::IBoxProto& rBoxAlgorithmPrototype) const
{
  return (true);
}

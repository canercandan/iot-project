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
  return ("vnc"); // Cree ton une nouvelle categorie ?
}

OpenViBE::CString			CVncBoxDesc::getVersion(void) const
{
  return ("1.0");
}

OpenViBE::CString			CVncBoxDesc::getStockItemName(void) const
{
  return (""); // Ca correspond  a quoi ca?
}

OpenViBE::CIdentifier		CVncBoxDesc::getCreatedClass(void) const
{
  return (0); // Qui choisis cet identifier
}

OpenViBE::Plugins::IPluginObject* CVncBoxDesc::create(void)
{
  return (new OpenViBE::Plugins::VNC::CVncBox);
}

OpenViBE::boolean			CVncBoxDesc::getBoxPrototype(OpenViBE::Kernel::IBoxProto& rBoxAlgorithmPrototype) const
{
  rBoxAlgorithmPrototype.addInput("Labels",  OV_TypeId_Stimulations); // C'est l'output provenant du Classifier processor

  rBoxAlgorithmPrototype.addSetting("Host", OV_TypeId_String, "localhost");
  rBoxAlgorithmPrototype.addSetting("Port", OV_TypeId_Integer, 5900); // Mettre un define pour ca
  rBoxAlgorithmPrototype.addSetting("Active Secure Connection", OV_TypeId_Boolean,    false);
  rBoxAlgorithmPrototype.addSetting("Username", OV_TypeId_String, "");
  rBoxAlgorithmPrototype.addSetting("Password", OV_TypeId_String, "");
  rBoxAlgorithmPrototype.addSetting("Mouse move distance", OV_TypeId_Integer, 1); // La distance pour faire bouger la souris
  // Voir avec Yann renard si on fait le mouvement ds un fichier ou ds les settings direct
  rBoxAlgorithmPrototype.addFlag(OpenViBE::Kernel::BoxFlag_IsUnstable);
  return (true);
}

#include "ovpCVncBoxDesc.h"
#include "ovpCVncBox.h"

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
  return ("gtk-network"); // http://library.gnome.org/devel/gtk/2.13/gtk-Stock-Items.html
}

OpenViBE::CIdentifier		CVncBoxDesc::getCreatedClass(void) const
{
  return (OVP_ClassId_VncBox);
}

OpenViBE::Plugins::IPluginObject* CVncBoxDesc::create(void)
{
  return (new VNC::CVncBox);
}

OpenViBE::boolean			CVncBoxDesc::getBoxPrototype(OpenViBE::Kernel::IBoxProto& rBoxAlgorithmPrototype) const
{
  rBoxAlgorithmPrototype.addInput("Labels",  OV_TypeId_Stimulations); // C'est l'output provenant du Classifier processor


  rBoxAlgorithmPrototype.addSetting("Host", OV_TypeId_String, "localhost");
  rBoxAlgorithmPrototype.addSetting("Port", OV_TypeId_Integer, "5900"); // Mettre un define pour ca

  // rBoxAlgorithmPrototype.addSetting("Active Secure Connection", OV_TypeId_Boolean, false);
  // rBoxAlgorithmPrototype.addSetting("Username", OV_TypeId_String, "");
  // rBoxAlgorithmPrototype.addSetting("Password", OV_TypeId_String, "");
  rBoxAlgorithmPrototype.addSetting("Mouse move distance", OV_TypeId_Integer, "1"); // La distance pour faire bouger la souris

  rBoxAlgorithmPrototype.addSetting("Move left mouse", OV_TypeId_Stimulation, "OVTK_GDF_Left");
  rBoxAlgorithmPrototype.addSetting("Move right mouse", OV_TypeId_Stimulation, "OVTK_GDF_Right");
  rBoxAlgorithmPrototype.addSetting("Move up mouse", OV_TypeId_Stimulation, "OVTK_GDF_Up");
  rBoxAlgorithmPrototype.addSetting("Move down mouse", OV_TypeId_Stimulation, "OVTK_GDF_Down");
  rBoxAlgorithmPrototype.addSetting("Left Button Mouse", OV_TypeId_Stimulation, "OVTK_GDF_Foot");
  rBoxAlgorithmPrototype.addSetting("Middle Button Mouse", OV_TypeId_Stimulation, "OVTK_GDF_Tongue");
  rBoxAlgorithmPrototype.addSetting("Right Button Mouse", OV_TypeId_Stimulation, "OVTK_GDF_Flashing_Light");
  rBoxAlgorithmPrototype.addSetting("Key 1", OV_TypeId_Stimulation, "OVTK_GDF_Eyes_Left");
  rBoxAlgorithmPrototype.addSetting("Key 2", OV_TypeId_Stimulation, "OVTK_GDF_Eyes_Right");
  rBoxAlgorithmPrototype.addFlag(OpenViBE::Kernel::BoxFlag_IsUnstable);
  return (true);
}

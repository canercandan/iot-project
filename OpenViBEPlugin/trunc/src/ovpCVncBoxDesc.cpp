#include "ovpCVncBoxDesc.h"
#include "ovpCVncBox.h"

using namespace OpenViBEPlugins::VNC;

void				CVncBoxDesc::release(void)
{
}

OpenViBE::CString			CVncBoxDesc::getName(void) const
{
  return ("VNC");
}

OpenViBE::CString			CVncBoxDesc::getAuthorName(void) const
{
  return ("Jaguar & La Ch@melle");
}

OpenViBE::CString			CVncBoxDesc::getAuthorCompanyName(void) const
{
  return ("IOT Consortium");
}

OpenViBE::CString			CVncBoxDesc::getShortDescription(void) const
{
  return ("Boite permettant d'interagir avec un serveur VNC (distant ou local) et donc de controller l'ordinateur par la pensee.");
}

OpenViBE::CString			CVncBoxDesc::getDetailedDescription(void) const
{
  return ("Le protocole VNC : RFB (Remote Frame Buffer) est utilisee. Il est possible d'envoyer des evenements souris mais aussi clavier. Il n'est pas possible d'utiliser le mode securise de RFB.");
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
  return ("gtk-network");
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
  rBoxAlgorithmPrototype.addInput("Labels",  OV_TypeId_Stimulations);

  rBoxAlgorithmPrototype.addSetting("Host", OV_TypeId_String, "localhost");
  rBoxAlgorithmPrototype.addSetting("Port", OV_TypeId_Integer, "5900");

  rBoxAlgorithmPrototype.addSetting("Mouse move distance", OV_TypeId_Integer, "1");

  rBoxAlgorithmPrototype.addSetting("Move left mouse", OV_TypeId_Stimulation, "OVTK_GDF_Left");
  rBoxAlgorithmPrototype.addSetting("Move right mouse", OV_TypeId_Stimulation, "OVTK_GDF_Right");
  rBoxAlgorithmPrototype.addSetting("Move up mouse", OV_TypeId_Stimulation, "OVTK_GDF_Up");
  rBoxAlgorithmPrototype.addSetting("Move down mouse", OV_TypeId_Stimulation, "OVTK_GDF_Down");
  rBoxAlgorithmPrototype.addSetting("Left Button Mouse", OV_TypeId_Stimulation, "OVTK_GDF_Foot");
  rBoxAlgorithmPrototype.addSetting("Middle Button Mouse", OV_TypeId_Stimulation, "OVTK_GDF_Tongue");
  rBoxAlgorithmPrototype.addSetting("Right Button Mouse", OV_TypeId_Stimulation, "OVTK_GDF_Flashing_Light");
  rBoxAlgorithmPrototype.addSetting("Key 1", OV_TypeId_Stimulation, "OVTK_GDF_Eyes_Left");
  rBoxAlgorithmPrototype.addSetting("Key 2", OV_TypeId_Stimulation, "OVTK_GDF_Eyes_Right");

  return (true);
}

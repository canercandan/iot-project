#ifndef OVPCVNCBOXDESC_H_
# define OVPCVNCBOXDESC_H_

#include "../../ovp_defines.h"
#include <openvibe/ov_all.h>
#include <openvibe-toolkit/ovtk_all.h>

namespace OpenViBEPlugins
{
  namespace VNC
  {
    class CVncBoxDesc : public OpenViBE::Plugins::IBoxAlgorithmDesc
    {
    public:
      virtual void				release(void);
      virtual OpenViBE::CString			getName(void) const;
      virtual OpenViBE::CString			getAuthorName(void) const;
      virtual OpenViBE::CString			getAuthorCompanyName(void) const;
      virtual OpenViBE::CString			getShortDescription(void) const;
      virtual OpenViBE::CString			getDetailedDescription(void) const;
      virtual OpenViBE::CString			getCategory(void) const;
      virtual OpenViBE::CString			getVersion(void) const;
      virtual OpenViBE::CString			getStockItemName(void) const;
      virtual OpenViBE::CIdentifier		getCreatedClass(void) const;
      virtual OpenViBE::Plugins::IPluginObject* create(void);
      virtual OpenViBE::boolean			getBoxPrototype(OpenViBE::Kernel::IBoxProto& rBoxAlgorithmPrototype) const;

      _IsDerivedFromClass_Final_(OpenViBE::Plugins::IBoxAlgorithmDesc, OVP_ClassId_VncBoxDesc);
    };
  }
}

#endif

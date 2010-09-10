#ifndef OVPCVNCBOX_H_
# define OVPCVNCBOX_H_

#include "../../ovp_defines.h"
#include <openvibe/ov_all.h>
#include <openvibe-toolkit/ovtk_all.h>

namespace OpenViBEPlugins
{
  namespace VNC
  {
    class CVncBox : public OpenViBEToolkit::TBoxAlgorithm < OpenViBE::Plugins::IBoxAlgorithm >
    {
    public:
      virtual void		release(void);
      virtual OpenViBE::boolean initialize(void);
      virtual OpenViBE::boolean uninitialize(void);
      virtual OpenViBE::boolean processInput(OpenViBE::uint32 ui32InputIndex);
      virtual OpenViBE::boolean process(void);

      _IsDerivedFromClass_Final_(OpenViBEToolkit::TBoxAlgorithm < OpenViBE::Plugins::IBoxAlgorithm >, OVP_ClassId_VncBox);
    };
  }
}

#endif // OVPCVNCBOX_H_

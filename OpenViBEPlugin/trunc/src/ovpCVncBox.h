#ifndef OVPCVNCBOX_H_
# define OVPCVNCBOX_H_

#include "../../ovp_defines.h"
#include <openvibe/ov_all.h>
#include <openvibe-toolkit/ovtk_all.h>

namespace OpenViBEPlugins
{
  namespace VNC
  {
    enum Action
    {
      ACTION_MOUSEL,
      ACTION_MOUSER,
      ACTION_MOUSEU,
      ACTION_MOUSED,
      ACTION_MOUSE1,
      ACTION_MOUSE2,
      ACTION_MOUSE3
    };

    class CVncBox : public OpenViBEToolkit::TBoxAlgorithm < OpenViBE::Plugins::IBoxAlgorithm >
      {
      public:
	virtual void		release(void);
	virtual OpenViBE::boolean initialize(void);
	virtual OpenViBE::boolean uninitialize(void);
	virtual OpenViBE::boolean processInput(OpenViBE::uint32 ui32InputIndex);
	virtual OpenViBE::boolean process(void);

	_IsDerivedFromClass_Final_(OpenViBEToolkit::TBoxAlgorithm < OpenViBE::Plugins::IBoxAlgorithm >, OVP_ClassId_VncBox);

      private:
	// Pour la box
	OpenViBE::Kernel::TParameterHandler<OpenViBE::IMemoryBuffer*> ip_pMemoryBufferToDecode;

	// Pour VNC
	// Reseau
	Socket::IConnectionClient * _socket;
	CString _hostName;
	Socket::uint32 _port;

	std::map<Action, OpenViBE::uint64> _actions;
      };
  }
}

#endif // OVPCVNCBOX_H_

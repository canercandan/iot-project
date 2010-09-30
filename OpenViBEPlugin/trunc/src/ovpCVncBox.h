#ifndef OVPCVNCBOX_H_
# define OVPCVNCBOX_H_

#include <map>

#include <openvibe/ov_all.h>
#include <openvibe-toolkit/ovtk_all.h>
#include <socket/IConnectionClient.h>

#include "ovp_defines.h"

namespace OpenViBEPlugins
{
  namespace VNC
  {
    enum Action
    {
      ACTION_MOUSEL, // Mouse Move Left
      ACTION_MOUSER, // Mouse Move Right
      ACTION_MOUSEU, // Mouse Move Up
      ACTION_MOUSED, // Mouse Move Down
      ACTION_MOUSE1, // Mouse Button 1
      ACTION_MOUSE2, // Mouse Button 2
      ACTION_MOUSE3, // Mouse Button 3
      ACTION_KEY1,  // First key
      ACTION_KEY2  // Second key
    };

    class CVncBox : public OpenViBEToolkit::TBoxAlgorithm<OpenViBE::Plugins::IBoxAlgorithm>
      {
      public:
	CVncBox();

	// Methodes heritees
	virtual void			release(void);
	virtual OpenViBE::boolean	initialize(void);
	virtual OpenViBE::boolean	uninitialize(void);
	virtual OpenViBE::boolean	processInput(OpenViBE::uint32 ui32InputIndex);
	virtual OpenViBE::boolean	process(void);

	_IsDerivedFromClass_Final_(OpenViBEToolkit::TBoxAlgorithm<OpenViBE::Plugins::IBoxAlgorithm>, OVP_ClassId_VncBox);

      private:
	Socket::IConnectionClient *	_socket;
	std::map<Action, int>		_actionsMapping; // Mapping entre les labels recus et les actions a effectue
	int				_mouveMoveDistance;
      };
  }
}

#endif // OVPCVNCBOX_H_

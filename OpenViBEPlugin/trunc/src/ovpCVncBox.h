#ifndef OVPCVNCBOX_H_
# define OVPCVNCBOX_H_

#include <map>

#include <openvibe/ov_all.h>
#include <openvibe-toolkit/ovtk_all.h>
#include <socket/IConnectionClient.h>

#include <boost/circular_buffer.hpp>

#include "ovp_defines.h"
#include "ProtocolClientRFB.h"

namespace OpenViBEPlugins
{
  namespace VNC
  {
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
	void				receiveBuffer(); // Essaye de lire sur la socket
	void				sendBuffer(boost::circular_buffer<char> & bufferToSend); // Remplis le buffer de sortie et essaye d'ecrire sur la socket
      private:
	OpenViBE::Kernel::IAlgorithmProxy*					m_pStimulationDecoder; // Algorithme permettant de decoder le buffer input de la box
	OpenViBE::Kernel::TParameterHandler<const OpenViBE::IMemoryBuffer*>	ip_pMemoryBuffer; // 1st Input of the box
	OpenViBE::Kernel::TParameterHandler<OpenViBE::IStimulationSet*>		op_pStimulationSet; // Output --> Buffer decoder par l'algorithme

	Socket::IConnectionClient *			_socket;
	boost::circular_buffer<char>			_bufferIn;

	std::map<OpenViBE::uint64, Action>		_actionsMapping; // Mapping entre les labels recus et les actions a effectue
	ProtocolClientRFB				_protocolClientRFB;
	// Doc pour les circular_buffer : http://www.boost.org/doc/libs/1_44_0/libs/circular_buffer/doc/circular_buffer.html

      };
  }
}

#endif // OVPCVNCBOX_H_

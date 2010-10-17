#ifndef OVPCVNCBOX_H_
# define OVPCVNCBOX_H_

#include <map>

#include <boost/circular_buffer.hpp>

#include <socket/IConnectionClient.h>

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

	virtual void			release(void);
	virtual OpenViBE::boolean	initialize(void);
	virtual OpenViBE::boolean	uninitialize(void);
	virtual OpenViBE::boolean	processInput(OpenViBE::uint32 ui32InputIndex);
	virtual OpenViBE::boolean	process(void);

	_IsDerivedFromClass_Final_(OpenViBEToolkit::TBoxAlgorithm<OpenViBE::Plugins::IBoxAlgorithm>, OVP_ClassId_VncBox);

      private:
	/**
	 * \brief Read the socket and save the buffer
	 */
	void				receiveBuffer();

	/**
	 * \brief Add the param buffer in the output buffer and try to write on the socket the output buffer
	 * \param rInputBuffer [in] : A buffer to add in the output buffer
	 */
	void				sendBuffer(boost::circular_buffer<char> const & rInputBuffer);

      private:
	OpenViBE::Kernel::IAlgorithmProxy*					m_pStimulationDecoder; /** Algorithm who decode the box's input */
	OpenViBE::Kernel::TParameterHandler<const OpenViBE::IMemoryBuffer*>	ip_pMemoryBuffer; /** The box's input encoded */
	OpenViBE::Kernel::TParameterHandler<OpenViBE::IStimulationSet*>		op_pStimulationSet; /** The Algorihtm's Output decoded */

	Socket::IConnectionClient *			m_pSocket; /** A socket connected to a VNC Server */
	boost::circular_buffer<char>			m_oBufferIn; /** The received packet are save in , it's consume by the RFB Parser */
	boost::circular_buffer<char>			m_oBufferOut; /** The packet to send, content is remove when it sent */

	std::map<OpenViBE::uint64, EAction>		m_oActionsMapping; /** Mapping between label and the VNC Action */
	CProtocolClientRFB				m_oRfbActor; /** RFB Parser */
      };
  }
}

#endif // OVPCVNCBOX_H_

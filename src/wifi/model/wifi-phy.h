/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2005,2006 INRIA
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * Authors: Mathieu Lacage <mathieu.lacage@sophia.inria.fr>
 *          Sébastien Deronne <sebastien.deronne@gmail.com>
 */

#ifndef WIFI_PHY_H
#define WIFI_PHY_H

<<<<<<< HEAD
#include <stdint.h>
#include <map>
#include "ns3/callback.h"
#include "ns3/event-id.h"
#include "ns3/packet.h"
#include "ns3/object.h"
#include "ns3/nstime.h"
#include "ns3/ptr.h"
#include "ns3/mobility-model.h"
#include "ns3/random-variable-stream.h"
#include "wifi-mode.h"
#include "wifi-preamble.h"
#include "wifi-phy-standard.h"
#include "ns3/traced-callback.h"
#include "wifi-tx-vector.h"
#include "wifi-phy-standard.h"
#include "interference-helper.h"
#include "ns3/net-device.h"
#include "ns3/node.h"
#include "wifi-channel.h"

namespace ns3 {

#define VHT_PHY 126
#define HT_PHY 127

class WifiPhyStateHelper;

/**
 * This enumeration defines the type of an MPDU.
 */
enum mpduType
{
  /** The MPDU is not part of an A-MPDU */
  NORMAL_MPDU = 0,
  /** The MPDU is part of an A-MPDU, but is not the last aggregate */
  MPDU_IN_AGGREGATE,
  /** The MPDU is the last aggregate in an A-MPDU */
  LAST_MPDU_IN_AGGREGATE
};

struct signalNoiseDbm
{
  double signal; //in dBm
  double noise; //in dBm
};

struct mpduInfo
{
  enum mpduType type;
  uint32_t mpduRefNumber;
};

/**
 * \brief receive notifications about phy events.
 */
class WifiPhyListener
{
public:
  virtual ~WifiPhyListener ();

  /**
   * \param duration the expected duration of the packet reception.
   *
   * We have received the first bit of a packet. We decided
   * that we could synchronize on this packet. It does not mean
   * we will be able to successfully receive completely the
   * whole packet. It means that we will report a BUSY status until
   * one of the following happens:
   *   - NotifyRxEndOk
   *   - NotifyRxEndError
   *   - NotifyTxStart
   */
  virtual void NotifyRxStart (Time duration) = 0;
  /**
   * We have received the last bit of a packet for which
   * NotifyRxStart was invoked first and, the packet has
   * been successfully received.
   */
  virtual void NotifyRxEndOk (void) = 0;
  /**
   * We have received the last bit of a packet for which
   * NotifyRxStart was invoked first and, the packet has
   * _not_ been successfully received.
   */
  virtual void NotifyRxEndError (void) = 0;
  /**
   * \param duration the expected transmission duration.
   * \param txPowerDbm the nominal tx power in dBm
   *
   * We are about to send the first bit of the packet.
   * We do not send any event to notify the end of
   * transmission. Listeners should assume that the
   * channel implicitely reverts to the idle state
   * unless they have received a cca busy report.
   */
  virtual void NotifyTxStart (Time duration, double txPowerDbm) = 0;
  /**
   * \param duration the expected busy duration.
   *
   * This method does not really report a real state
   * change as opposed to the other methods in this class.
   * It merely reports that, unless the medium is reported
   * busy through NotifyTxStart or NotifyRxStart/End,
   * it will be busy as defined by the currently selected
   * CCA mode.
   *
   * Typical client code which wants to have a clear picture
   * of the CCA state will need to keep track of the time at
   * which the last NotifyCcaBusyStart method is called and
   * what duration it reported.
   */
  virtual void NotifyMaybeCcaBusyStart (Time duration) = 0;
  /**
   * \param duration the expected channel switching duration.
   *
   * We do not send any event to notify the end of
   * channel switching. Listeners should assume that the
   * channel implicitely reverts to the idle or busy states.
   */
  virtual void NotifySwitchingStart (Time duration) = 0;
  /**
   * Notify listeners that we went to sleep
   */
  virtual void NotifySleep (void) = 0;
  /**
   * Notify listeners that we woke up
   */
  virtual void NotifyWakeup (void) = 0;
};

=======
#include "ns3/error-model.h"
#include "wifi-standards.h"
#include "interference-helper.h"
#include "wifi-phy-state-helper.h"
#include "phy-entity.h"
#include "wifi-phy-operating-channel.h"

namespace ns3 {

class Channel;
class NetDevice;
class MobilityModel;
class WifiPhyStateHelper;
class FrameCaptureModel;
class PreambleDetectionModel;
class WifiRadioEnergyModel;
class UniformRandomVariable;
>>>>>>> origin

/**
 * \brief 802.11 PHY layer model
 * \ingroup wifi
 *
 */
class WifiPhy : public Object
{
public:
  friend class PhyEntity;
  /**
   * \brief Get the type ID.
   * \return the object TypeId
   */
<<<<<<< HEAD
  enum State
  {
    /**
     * The PHY layer is IDLE.
     */
    IDLE,
    /**
     * The PHY layer has sense the medium busy through the CCA mechanism
     */
    CCA_BUSY,
    /**
     * The PHY layer is sending a packet.
     */
    TX,
    /**
     * The PHY layer is receiving a packet.
     */
    RX,
    /**
     * The PHY layer is switching to other channel.
     */
    SWITCHING,
    /**
     * The PHY layer is sleeping.
     */
    SLEEP
  };

  /**
   * arg1: packet received successfully
   * arg2: snr of packet
   * arg3: TXVECTOR of packet
   * arg4: type of preamble used for packet.
   */
  typedef Callback<void, Ptr<Packet>, double, WifiTxVector, enum WifiPreamble> RxOkCallback;
  /**
   * arg1: packet received unsuccessfully
   * arg2: snr of packet
   */
  typedef Callback<void, Ptr<Packet>, double> RxErrorCallback;

=======
>>>>>>> origin
  static TypeId GetTypeId (void);

  WifiPhy ();
  virtual ~WifiPhy ();

  static const std::set<FrequencyChannelInfo> m_frequencyChannels;  //!< Available frequency channels

  /**
<<<<<<< HEAD
=======
   * Return the WifiPhyStateHelper of this PHY
   *
   * \return the WifiPhyStateHelper of this PHY
   */
  Ptr<WifiPhyStateHelper> GetState (void) const;

  /**
>>>>>>> origin
   * \param callback the callback to invoke
   *        upon successful packet reception.
   */
  void SetReceiveOkCallback (RxOkCallback callback);
  /**
   * \param callback the callback to invoke
   *        upon erroneous packet reception.
   */
<<<<<<< HEAD
  virtual void SetReceiveErrorCallback (RxErrorCallback callback) = 0;

  /**
   * \param packet the packet to send
   * \param txVector the TXVECTOR that has tx parameters such as mode, the transmission mode to use to send
   *        this packet, and txPowerLevel, a power level to use to send this packet. The real transmission
   *        power is calculated as txPowerMin + txPowerLevel * (txPowerMax - txPowerMin) / nTxLevels
   * \param preamble the type of preamble to use to send this packet.
   */
  virtual void SendPacket (Ptr<const Packet> packet, WifiTxVector txVector, enum WifiPreamble preamble) = 0;
  /**
   * \param packet the packet to send
   * \param txVector the TXVECTOR that has tx parameters such as mode, the transmission mode to use to send
   *        this packet, and txPowerLevel, a power level to use to send this packet. The real transmission
   *        power is calculated as txPowerMin + txPowerLevel * (txPowerMax - txPowerMin) / nTxLevels
   * \param preamble the type of preamble to use to send this packet.
   * \param mpdutype the type of the MPDU as defined in WifiPhy::mpduType.
   */
  virtual void SendPacket (Ptr<const Packet> packet, WifiTxVector txVector, enum WifiPreamble preamble, enum mpduType mpdutype) = 0;
=======
  void SetReceiveErrorCallback (RxErrorCallback callback);
>>>>>>> origin

  /**
   * \param listener the new listener
   *
   * Add the input listener to the list of objects to be notified of
   * PHY-level events.
   */
  void RegisterListener (WifiPhyListener *listener);
  /**
   * \param listener the listener to be unregistered
   *
   * Remove the input listener from the list of objects to be notified of
   * PHY-level events.
   */
  void UnregisterListener (WifiPhyListener *listener);

  /**
   * \param callback the callback to invoke when PHY capabilities have changed.
   */
  void SetCapabilitiesChangedCallback (Callback<void> callback);

  /**
   * Start receiving the PHY preamble of a PPDU (i.e. the first bit of the preamble has arrived).
   *
   * \param ppdu the arriving PPDU
   * \param rxPowersW the receive power in W per band
   * \param rxDuration the duration of the PPDU
   */
  void StartReceivePreamble (Ptr<WifiPpdu> ppdu, RxPowerWattPerChannelBand& rxPowersW, Time rxDuration);

  /**
   * Reset PHY at the end of the packet under reception after it has failed the PHY header.
   *
   * \param event the corresponding event of the first time the packet arrives (also storing packet and TxVector information)
   */
  void ResetReceive (Ptr<Event> event);

  /**
   * For HE receptions only, check and possibly modify the transmit power restriction state at
   * the end of PPDU reception.
   */
  void EndReceiveInterBss (void);

  /**
   * Get a WifiConstPsduMap from a PSDU and the TXVECTOR to use to send the PSDU.
   * The STA-ID value is properly determined based on whether the given PSDU has
   * to be transmitted as a DL or UL frame.
   *
   * \param psdu the given PSDU
   * \param txVector the TXVECTOR to use to send the PSDU
   * \return a WifiConstPsduMap built from the given PSDU and the given TXVECTOR
   */
  static WifiConstPsduMap GetWifiConstPsduMap (Ptr<const WifiPsdu> psdu, const WifiTxVector& txVector);

  /**
   * This function is a wrapper for the Send variant that accepts a WifiConstPsduMap
   * as first argument. This function inserts the given PSDU in a WifiConstPsduMap
   * along with a STA-ID value that is determined based on whether the given PSDU has
   * to be transmitted as a DL or UL frame.
   *
   * \param psdu the PSDU to send (in a SU PPDU)
   * \param txVector the TXVECTOR that has TX parameters such as mode, the transmission mode to use to send
   *        this PSDU, and txPowerLevel, a power level to use to send the whole PPDU. The real transmission
   *        power is calculated as txPowerMin + txPowerLevel * (txPowerMax - txPowerMin) / nTxLevels
   */
  void Send (Ptr<const WifiPsdu> psdu, const WifiTxVector& txVector);
  /**
   * \param psdus the PSDUs to send
   * \param txVector the TXVECTOR that has tx parameters such as mode, the transmission mode to use to send
   *        this PSDU, and txPowerLevel, a power level to use to send the whole PPDU. The real transmission
   *        power is calculated as txPowerMin + txPowerLevel * (txPowerMax - txPowerMin) / nTxLevels
   */
  void Send (WifiConstPsduMap psdus, WifiTxVector txVector);

  /**
   * \param ppdu the PPDU to send
   */
  virtual void StartTx (Ptr<WifiPpdu> ppdu) = 0;

  /**
   * Put in sleep mode.
   */
  void SetSleepMode (void);
  /**
   * Resume from sleep mode.
   */
  void ResumeFromSleep (void);
  /**
   * Put in off mode.
   */
  void SetOffMode (void);
  /**
   * Resume from off mode.
   */
  void ResumeFromOff (void);

  /**
   * \return true of the current state of the PHY layer is WifiPhy::IDLE, false otherwise.
   */
<<<<<<< HEAD
  virtual bool IsStateIdle (void);
  /**
   * \return true of the current state of the PHY layer is WifiPhy::CCA_BUSY, false otherwise.
   */
  virtual bool IsStateCcaBusy (void);
  /**
   * \return true of the current state of the PHY layer is not WifiPhy::IDLE, false otherwise.
   */
  virtual bool IsStateBusy (void);
  /**
   * \return true of the current state of the PHY layer is WifiPhy::RX, false otherwise.
   */
  virtual bool IsStateRx (void);
  /**
   * \return true of the current state of the PHY layer is WifiPhy::TX, false otherwise.
   */
  virtual bool IsStateTx (void);
  /**
   * \return true of the current state of the PHY layer is WifiPhy::SWITCHING, false otherwise.
   */
  virtual bool IsStateSwitching (void);
  /**
   * \return true if the current state of the PHY layer is WifiPhy::SLEEP, false otherwise.
   */
  virtual bool IsStateSleep (void);
=======
  bool IsStateIdle (void) const;
  /**
   * \return true of the current state of the PHY layer is WifiPhy::CCA_BUSY, false otherwise.
   */
  bool IsStateCcaBusy (void) const;
  /**
   * \return true of the current state of the PHY layer is WifiPhy::RX, false otherwise.
   */
  bool IsStateRx (void) const;
  /**
   * \return true of the current state of the PHY layer is WifiPhy::TX, false otherwise.
   */
  bool IsStateTx (void) const;
  /**
   * \return true of the current state of the PHY layer is WifiPhy::SWITCHING, false otherwise.
   */
  bool IsStateSwitching (void) const;
  /**
   * \return true if the current state of the PHY layer is WifiPhy::SLEEP, false otherwise.
   */
  bool IsStateSleep (void) const;
>>>>>>> origin
  /**
   * \return true if the current state of the PHY layer is WifiPhy::OFF, false otherwise.
   */
<<<<<<< HEAD
  virtual Time GetStateDuration (void);
=======
  bool IsStateOff (void) const;

>>>>>>> origin
  /**
   * \return the predicted delay until this PHY can become WifiPhy::IDLE.
   *
   * The PHY will never become WifiPhy::IDLE _before_ the delay returned by
   * this method but it could become really idle later.
   */
<<<<<<< HEAD
  virtual Time GetDelayUntilIdle (void);
=======
  Time GetDelayUntilIdle (void);
>>>>>>> origin

  /**
   * Return the start time of the last received packet.
   *
   * \return the start time of the last received packet
   */
<<<<<<< HEAD
  virtual Time GetLastRxStartTime (void) const;
=======
  Time GetLastRxStartTime (void) const;
  /**
   * Return the end time of the last received packet.
   *
   * \return the end time of the last received packet
   */
  Time GetLastRxEndTime (void) const;
>>>>>>> origin

  /**
   * \param size the number of bytes in the packet to send
   * \param txVector the TXVECTOR used for the transmission of this packet
<<<<<<< HEAD
   * \param preamble the type of preamble to use for this packet.
   * \param frequency the channel center frequency (MHz)
   *
   * \return the total amount of time this PHY will stay busy for the transmission of these bytes.
   */
  Time CalculateTxDuration (uint32_t size, WifiTxVector txVector, enum WifiPreamble preamble, double frequency);
  /**
   * \param size the number of bytes in the packet to send
   * \param txVector the TXVECTOR used for the transmission of this packet
   * \param preamble the type of preamble to use for this packet.
   * \param frequency the channel center frequency (MHz)
   * \param mpdutype the type of the MPDU as defined in WifiPhy::mpduType.
   * \param incFlag this flag is used to indicate that the static variables need to be update or not. This function is called a couple of times for the same packet so static variables should not be increased each time.
   *
   * \return the total amount of time this PHY will stay busy for the transmission of these bytes.
   */
  Time CalculateTxDuration (uint32_t size, WifiTxVector txVector, enum WifiPreamble preamble, double frequency, enum mpduType mpdutype, uint8_t incFlag);
=======
   * \param band the frequency band being used
   * \param staId the STA-ID of the recipient (only used for MU)
   *
   * \return the total amount of time this PHY will stay busy for the transmission of these bytes.
   */
  static Time CalculateTxDuration (uint32_t size, const WifiTxVector& txVector, WifiPhyBand band,
                                   uint16_t staId = SU_STA_ID);
  /**
   * This function is a wrapper for the CalculateTxDuration variant that accepts a
   * WifiConstPsduMap as first argument. This function inserts the given PSDU in a
   * WifiConstPsduMap along with a STA-ID value that is determined based on whether
   * the given PSDU has to be transmitted as a DL or UL frame, thus allowing to
   * properly calculate the TX duration in case the PSDU has to be transmitted as
   * an UL frame.
   *
   * \param psdu the PSDU to transmit
   * \param txVector the TXVECTOR used for the transmission of the PSDU
   * \param band the frequency band
   *
   * \return the total amount of time this PHY will stay busy for the transmission of the PPDU
   */
  static Time CalculateTxDuration (Ptr<const WifiPsdu> psdu, const WifiTxVector& txVector, WifiPhyBand band);
  /**
   * \param psduMap the PSDU(s) to transmit indexed by STA-ID
   * \param txVector the TXVECTOR used for the transmission of the PPDU
   * \param band the frequency band being used
   *
   * \return the total amount of time this PHY will stay busy for the transmission of the PPDU
   */
  static Time CalculateTxDuration (WifiConstPsduMap psduMap, const WifiTxVector& txVector, WifiPhyBand band);
>>>>>>> origin

  /**
   * \param txVector the transmission parameters used for this packet
   *
   * \return the total amount of time this PHY will stay busy for the transmission of the PHY preamble and PHY header.
   */
  static Time CalculatePhyPreambleAndHeaderDuration (const WifiTxVector& txVector);
  /**
   * \return the preamble detection duration, which is the time correlation needs to detect the start of an incoming frame.
   */
  static Time GetPreambleDetectionDuration (void);
  /**
   * \param size the number of bytes in the packet to send
   * \param txVector the TXVECTOR used for the transmission of this packet
<<<<<<< HEAD
   * \param preamble the type of preamble to use for this packet
   * \param frequency the channel center frequency (MHz)
   *
   * \return the duration of the payload
   */
  Time GetPayloadDuration (uint32_t size, WifiTxVector txVector, WifiPreamble preamble, double frequency);
  /**
   * \param size the number of bytes in the packet to send
   * \param txVector the TXVECTOR used for the transmission of this packet
   * \param preamble the type of preamble to use for this packet
   * \param frequency the channel center frequency (MHz)
   * \param mpdutype the type of the MPDU as defined in WifiPhy::mpduType.
   * \param incFlag this flag is used to indicate that the static variables need to be update or not. This function is called a couple of times for the same packet so static variables should not be increased each time
=======
   * \param band the frequency band
   * \param mpdutype the type of the MPDU as defined in WifiPhy::MpduType.
   * \param staId the STA-ID of the PSDU (only used for MU PPDUs)
>>>>>>> origin
   *
   * \return the duration of the PSDU
   */
<<<<<<< HEAD
  Time GetPayloadDuration (uint32_t size, WifiTxVector txVector, WifiPreamble preamble, double frequency, enum mpduType mpdutype, uint8_t incFlag);
=======
  static Time GetPayloadDuration (uint32_t size, const WifiTxVector& txVector, WifiPhyBand band, MpduType mpdutype = NORMAL_MPDU,
                                  uint16_t staId = SU_STA_ID);
  /**
   * \param size the number of bytes in the packet to send
   * \param txVector the TXVECTOR used for the transmission of this packet
   * \param band the frequency band
   * \param mpdutype the type of the MPDU as defined in WifiPhy::MpduType.
   * \param incFlag this flag is used to indicate that the variables need to be update or not
   * This function is called a couple of times for the same packet so variables should not be increased each time.
   * \param totalAmpduSize the total size of the previously transmitted MPDUs for the concerned A-MPDU.
   * If incFlag is set, this parameter will be updated.
   * \param totalAmpduNumSymbols the number of symbols previously transmitted for the MPDUs in the concerned A-MPDU,
   * used for the computation of the number of symbols needed for the last MPDU.
   * If incFlag is set, this parameter will be updated.
   * \param staId the STA-ID of the PSDU (only used for MU PPDUs)
   *
   * \return the duration of the PSDU
   */
  static Time GetPayloadDuration (uint32_t size, const WifiTxVector& txVector, WifiPhyBand band, MpduType mpdutype,
                                  bool incFlag, uint32_t &totalAmpduSize, double &totalAmpduNumSymbols,
                                  uint16_t staId);
  /**
   * \param txVector the transmission parameters used for this packet
   *
   * \return the duration until the start of the packet
   */
  static Time GetStartOfPacketDuration (const WifiTxVector& txVector);
>>>>>>> origin

  /**
   * The WifiPhy::GetModeList() method is used
   * (e.g., by a WifiRemoteStationManager) to determine the set of
   * transmission/reception (non-MCS) modes that this WifiPhy(-derived class)
   * can support - a set of modes which is stored by each non-HT PHY.
   *
   * It is important to note that this list is a superset (not
   * necessarily proper) of the OperationalRateSet (which is
   * logically, if not actually, a property of the associated
   * WifiRemoteStationManager), which itself is a superset (again, not
   * necessarily proper) of the BSSBasicRateSet.
   *
   * \return the list of supported (non-MCS) modes.
   */
<<<<<<< HEAD
  virtual uint32_t GetNModes (void) const;
=======
  std::list<WifiMode> GetModeList (void) const;
>>>>>>> origin
  /**
   * Get the list of supported (non-MCS) modes for the given modulation class (i.e.
   * corresponding to a given PHY entity).
   *
   * \param modulation the modulation class
   * \return the list of supported (non-MCS) modes for the given modulation class.
   *
   * \see GetModeList (void)
   */
<<<<<<< HEAD
  virtual WifiMode GetMode (uint32_t mode) const;
=======
  std::list<WifiMode> GetModeList (WifiModulationClass modulation) const;
>>>>>>> origin
  /**
   * Check if the given WifiMode is supported by the PHY.
   *
   * \param mode the wifi mode to check
   *
   * \return true if the given mode is supported,
   *         false otherwise
   */
<<<<<<< HEAD
  virtual bool IsModeSupported (WifiMode mode) const;
  /**
   * Check if the given WifiMode is supported by the PHY.
   *
   * \param mode the wifi mode to check
=======
  bool IsModeSupported (WifiMode mode) const;
  /**
   * Get the default WifiMode supported by the PHY.
   * This is the first mode to be added (i.e. the lowest one
   * over all supported PHY entities).
   *
   * \return the default WifiMode
   */
  WifiMode GetDefaultMode (void) const;
  /**
   * Check if the given MCS of the given modulation class is supported by the PHY.
   *
   * \param modulation the modulation class
   * \param mcs the MCS value
>>>>>>> origin
   *
   * \return true if the given mode is supported,
   *         false otherwise
   */
<<<<<<< HEAD
  virtual bool IsMcsSupported (WifiMode mcs) const;
=======
  bool IsMcsSupported (WifiModulationClass modulation, uint8_t mcs) const;
>>>>>>> origin

  /**
   * \param txVector the transmission vector
   * \param ber the probability of bit error rate
   *
<<<<<<< HEAD
   * \return the minimum snr which is required to achieve
   *          the requested ber for the specified transmission vector. (W/W)
   */
  virtual double CalculateSnr (WifiTxVector txVector, double ber) const;

  /**
  * The WifiPhy::NBssMembershipSelectors() method is used
  * (e.g., by a WifiRemoteStationManager) to determine the set of
  * transmission/reception modes that this WifiPhy(-derived class)
  * can support - a set of WifiMode objects which we call the
  * BssMembershipSelectorSet, and which is stored as WifiPhy::m_bssMembershipSelectorSet.
  *
  * \return the memebership selector whose index is specified.
  */
  virtual uint32_t GetNBssMembershipSelectors (void) const;
=======
   * \return the minimum SNR which is required to achieve
   *          the requested BER for the specified transmission vector. (W/W)
   */
  double CalculateSnr (const WifiTxVector& txVector, double ber) const;

  /**
   * Set the Short Interframe Space (SIFS) for this PHY.
   *
   * \param sifs the SIFS duration
   */
  void SetSifs (Time sifs);
  /**
   * Return the Short Interframe Space (SIFS) for this PHY.
   *
   * \return the SIFS duration
   */
  Time GetSifs (void) const;
  /**
   * Set the slot duration for this PHY.
   *
   * \param slot the slot duration
   */
  void SetSlot (Time slot);
  /**
   * Return the slot duration for this PHY.
   *
   * \return the slot duration
   */
  Time GetSlot (void) const;
  /**
   * Set the PCF Interframe Space (PIFS) for this PHY.
   *
   * \param pifs the PIFS duration
   */
  void SetPifs (Time pifs);
  /**
   * Return the PCF Interframe Space (PIFS) for this PHY.
   *
   * \return the PIFS duration
   */
  Time GetPifs (void) const;
  /**
   * Return the estimated Ack TX time for this PHY.
   *
   * \return the estimated Ack TX time
   */
  Time GetAckTxTime (void) const;
  /**
   * Return the estimated BlockAck TX time for this PHY.
   *
   * \return the estimated BlockAck TX time
   */
  Time GetBlockAckTxTime (void) const;

  /**
   * Get the maximum PSDU size in bytes for the given modulation class.
   *
   * \param modulation the modulation class
   * \return the maximum PSDU size in bytes for the given modulation class
   */
  static uint32_t GetMaxPsduSize (WifiModulationClass modulation);

>>>>>>> origin
  /**
  * The WifiPhy::BssMembershipSelector() method is used
  * (e.g., by a WifiRemoteStationManager) to determine the set of
  * transmission/reception modes that this WifiPhy(-derived class)
  * can support - a set of WifiMode objects which we call the
  * BssMembershipSelectorSet, and which is stored inside HT PHY (and above)
  * instances.
  *
  * \return the list of BSS membership selectors.
  */
<<<<<<< HEAD
  virtual uint32_t GetBssMembershipSelector (uint32_t selector) const;
=======
  std::list<uint8_t> GetBssMembershipSelectorList (void) const;
>>>>>>> origin
  /**
   * \return the number of supported MCSs.
   *
   * \see GetMcsList (void)
   */
<<<<<<< HEAD
  virtual WifiModeList GetMembershipSelectorModes (uint32_t selector);
=======
  uint16_t GetNMcs (void) const;
>>>>>>> origin
  /**
   * The WifiPhy::GetMcsList() method is used
   * (e.g., by a WifiRemoteStationManager) to determine the set of
   * transmission/reception MCS indices that this WifiPhy(-derived class)
   * can support - a set of MCS indices which is stored by each HT PHY (and above).
   *
   * \return the list of supported MCSs.
   */
<<<<<<< HEAD
  virtual uint8_t GetNMcs (void) const;
=======
  std::list<WifiMode> GetMcsList (void) const;
>>>>>>> origin
  /**
   * Get the list of supported MCSs for the given modulation class (i.e.
   * corresponding to a given PHY entity).
   *
   * \param modulation the modulation class
   * \return the list of supported MCSs for the given modulation class.
   *
   * \see GetMcsList (void)
   */
<<<<<<< HEAD
  virtual WifiMode GetMcs (uint8_t mcs) const;
=======
  std::list<WifiMode> GetMcsList (WifiModulationClass modulation) const;
  /**
   * Get the WifiMode object corresponding to the given MCS of the given
   * modulation class.
   *
   * \param modulation the modulation class
   * \param mcs the MCS value
   *
   * \return the WifiMode object corresponding to the given MCS of the given
   *         modulation class
   */
  WifiMode GetMcs (WifiModulationClass modulation, uint8_t mcs) const;
>>>>>>> origin

  /**
   * \brief Set channel number.
   *
   * Channel center frequency = Channel starting frequency + 5 MHz * (nch - 1)
   *
   * where Starting channel frequency is standard-dependent,
   * as defined in (Section 18.3.8.4.2 "Channel numbering"; IEEE Std 802.11-2012).
   * This method may fail to take action if the Phy model determines that
   * the channel number cannot be switched for some reason (e.g. sleep state)
   *
   * If the operating channel for this object has not been set yet, the given
   * channel number is saved and will be used, along with the center frequency and
   * width that have been saved similarly, to set the operating channel when the
   * standard and band are configured. Note that if center frequency and channel
   * number are both 0 when the standard and band are configured, a default channel
   * (of the configured width, if any, or the default width for the current standard
   * and band, otherwise) is set.
   * If the operating channel for this object has been already set, the specified
   * channel number must uniquely identify a channel in the band being used. If so,
   * this method may still fail to take action if the PHY model determines that
   * the channel number cannot be switched for some reason (e.g. sleep state)
   *
   * \param id the channel number
   */
<<<<<<< HEAD
  virtual void SetChannelNumber (uint16_t id);
=======
  virtual void SetChannelNumber (uint8_t id);
>>>>>>> origin
  /**
   * Return current channel number.
   *
   * \return the current channel number
   */
<<<<<<< HEAD
  virtual uint16_t GetChannelNumber (void) const;
  /**
   * \return the required time for channel switch operation of this WifiPhy
   */
  virtual Time GetChannelSwitchDelay (void) const;
=======
  uint8_t GetChannelNumber (void) const;
  /**
   * \return the required time for channel switch operation of this WifiPhy
   */
  Time GetChannelSwitchDelay (void) const;
>>>>>>> origin

  /**
   * Configure the PHY-level parameters for different Wi-Fi standard.
   *
   * \param standard the Wi-Fi standard
   * \param band the Wi-Fi band
   */
<<<<<<< HEAD
  virtual void ConfigureStandard (enum WifiPhyStandard standard);

  /**
   * Get the configured Wi-Fi standard
   *
   * \return the Wi-Fi standard that has been configured
   */
  virtual enum WifiPhyStandard GetStandard (void) const;

  /**
   * Add a channel definition to the WifiPhy.  The pair (channelNumber,
   * WifiPhyStandard) may then be used to lookup a pair (frequency, 
   * channelWidth).
   *
   * If the channel is not already defined for the standard, the method
   * should return true; otherwise false.
   *
   * \param channelNumber the channel number to define
   * \param standard the applicable WifiPhyStandard
   * \param frequency the frequency (MHz)
   * \param channelWidth the channel width (MHz)
   *
   * \return true if the channel definition succeeded
   */
  bool DefineChannelNumber (uint16_t channelNumber, enum WifiPhyStandard standard, uint32_t frequency, uint32_t channelWidth);

  /**
   * A pair of a ChannelNumber and WifiPhyStandard
   */
  typedef std::pair<uint16_t, enum WifiPhyStandard> ChannelNumberStandardPair;
  /**
   * A pair of a center Frequency and a ChannelWidth
   */
  typedef std::pair<uint32_t, uint32_t> FrequencyWidthPair;
=======
  virtual void ConfigureStandardAndBand (WifiPhyStandard standard, WifiPhyBand band);
>>>>>>> origin

  /**
   * Get the configured Wi-Fi standard
   *
   * \return the Wi-Fi standard that has been configured
   */
  WifiPhyStandard GetPhyStandard (void) const;

  /**
   * Get the configured Wi-Fi band
   *
   * \return the Wi-Fi band that has been configured
   */
  WifiPhyBand GetPhyBand (void) const;

  /**
   * Get a const reference to the operating channel
   *
   * \return a const reference to the operating channel
   */
  const WifiPhyOperatingChannel& GetOperatingChannel (void) const;

  /**
   * Return the Channel this WifiPhy is connected to.
   *
   * \return the Channel this WifiPhy is connected to
   */
<<<<<<< HEAD
  static WifiMode GetVhtMcs0 ();
  /**
   * Return MCS 1 from VHT MCS values.
   *
   * \return MCS 1 from VHT MCS values
   */
  static WifiMode GetVhtMcs1 ();
  /**
   * Return MCS 2 from VHT MCS values.
   *
   * \return MCS 2 from VHT MCS values
   */
  static WifiMode GetVhtMcs2 ();
  /**
   * Return MCS 3 from VHT MCS values.
   *
   * \return MCS 3 from VHT MCS values
   */
  static WifiMode GetVhtMcs3 ();
  /**
   * Return MCS 4 from VHT MCS values.
   *
   * \return MCS 4 from VHT MCS values
   */
  static WifiMode GetVhtMcs4 ();
  /**
   * Return MCS 5 from VHT MCS values.
   *
   * \return MCS 5 from VHT MCS values
   */
  static WifiMode GetVhtMcs5 ();
  /**
   * Return MCS 6 from VHT MCS values.
   *
   * \return MCS 6 from VHT MCS values
   */
  static WifiMode GetVhtMcs6 ();
  /**
   * Return MCS 7 from VHT MCS values.
   *
   * \return MCS 7 from VHT MCS values
   */
  static WifiMode GetVhtMcs7 ();
  /**
   * Return MCS 8 from VHT MCS values.
   *
   * \return MCS 8 from VHT MCS values
   */
  static WifiMode GetVhtMcs8 ();
  /**
   * Return MCS 9 from VHT MCS values.
   *
   * \return MCS 9 from VHT MCS values
   */
  static WifiMode GetVhtMcs9 ();
  /**
   * The standard disallows certain combinations of WifiMode, number of
   * spatial streams, and channel widths.  This method can be used to
   * check whether this WifiTxVector contains an invalid combination.
   *
   * \param txVector the WifiTxVector to inspect
   * \return true if the WifiTxVector parameters are allowed by the standard
   */
  static bool IsValidTxVector (WifiTxVector txVector);
=======
  virtual Ptr<Channel> GetChannel (void) const = 0;
>>>>>>> origin

  /**
   * Public method used to fire a PhyTxBegin trace.
   * Implemented for encapsulation purposes.
   *
   * \param psdus the PSDUs being transmitted (only one unless DL MU transmission)
   * \param txPowerW the transmit power in Watts
   */
  void NotifyTxBegin (WifiConstPsduMap psdus, double txPowerW);
  /**
   * Public method used to fire a PhyTxEnd trace.
   * Implemented for encapsulation purposes.
   *
   * \param psdus the PSDUs being transmitted (only one unless DL MU transmission)
   */
  void NotifyTxEnd (WifiConstPsduMap psdus);
  /**
   * Public method used to fire a PhyTxDrop trace.
   * Implemented for encapsulation purposes.
   *
   * \param psdu the PSDU being transmitted
   */
  void NotifyTxDrop (Ptr<const WifiPsdu> psdu);
  /**
   * Public method used to fire a PhyRxBegin trace.
   * Implemented for encapsulation purposes.
   *
   * \param psdu the PSDU being transmitted
   * \param rxPowersW the receive power per channel band in Watts
   */
  void NotifyRxBegin (Ptr<const WifiPsdu> psdu, const RxPowerWattPerChannelBand& rxPowersW);
  /**
   * Public method used to fire a PhyRxEnd trace.
   * Implemented for encapsulation purposes.
   *
   * \param psdu the PSDU being transmitted
   */
  void NotifyRxEnd (Ptr<const WifiPsdu> psdu);
  /**
   * Public method used to fire a PhyRxDrop trace.
   * Implemented for encapsulation purposes.
   *
   * \param psdu the PSDU being transmitted
   * \param reason the reason the packet was dropped
   */
  void NotifyRxDrop (Ptr<const WifiPsdu> psdu, WifiPhyRxfailureReason reason);

  /**
   * Public method used to fire a MonitorSniffer trace for a wifi PSDU being received.
   * Implemented for encapsulation purposes.
   * This method will extract all MPDUs if packet is an A-MPDU and will fire tracedCallback.
   * The A-MPDU reference number (RX side) is set within the method. It must be a different value
   * for each A-MPDU but the same for each subframe within one A-MPDU.
   *
   * \param psdu the PSDU being received
   * \param channelFreqMhz the frequency in MHz at which the packet is
   *        received. Note that in real devices this is normally the
   *        frequency to which  the receiver is tuned, and this can be
   *        different than the frequency at which the packet was originally
   *        transmitted. This is because it is possible to have the receiver
   *        tuned on a given channel and still to be able to receive packets
   *        on a nearby channel.
   * \param txVector the TXVECTOR that holds RX parameters
   * \param signalNoise signal power and noise power in dBm (noise power includes the noise figure)
   * \param statusPerMpdu reception status per MPDU
   * \param staId the STA-ID
   */
  void NotifyMonitorSniffRx (Ptr<const WifiPsdu> psdu,
                             uint16_t channelFreqMhz,
                             WifiTxVector txVector,
                             SignalNoiseDbm signalNoise,
                             std::vector<bool> statusPerMpdu,
                             uint16_t staId = SU_STA_ID);

  /**
   * TracedCallback signature for monitor mode receive events.
   *
   *
   * \param packet the packet being received
   * \param channelFreqMhz the frequency in MHz at which the packet is
   *        received. Note that in real devices this is normally the
   *        frequency to which  the receiver is tuned, and this can be
   *        different than the frequency at which the packet was originally
   *        transmitted. This is because it is possible to have the receiver
   *        tuned on a given channel and still to be able to receive packets
   *        on a nearby channel.
   * \param txVector the TXVECTOR that holds RX parameters
   * \param aMpdu the type of the packet (0 is not A-MPDU, 1 is a MPDU that is part of an A-MPDU and 2 is the last MPDU in an A-MPDU)
   *        and the A-MPDU reference number (must be a different value for each A-MPDU but the same for each subframe within one A-MPDU)
   * \param signalNoise signal power and noise power in dBm
   * \param staId the STA-ID
   * \todo WifiTxVector should be passed by const reference because
   * of its size.
   */
<<<<<<< HEAD
  typedef void (* MonitorSnifferRxCallback)(Ptr<const Packet> packet, uint16_t channelFreqMhz,
                                            uint16_t channelNumber, uint32_t rate, WifiPreamble preamble,
                                            WifiTxVector txVector, struct mpduInfo aMpdu, struct signalNoiseDbm signalNoise);
=======
  typedef void (* MonitorSnifferRxCallback)(Ptr<const Packet> packet,
                                            uint16_t channelFreqMhz,
                                            WifiTxVector txVector,
                                            MpduInfo aMpdu,
                                            SignalNoiseDbm signalNoise,
                                            uint16_t staId);
>>>>>>> origin

  /**
   * Public method used to fire a MonitorSniffer trace for a wifi PSDU being transmitted.
   * Implemented for encapsulation purposes.
   * This method will extract all MPDUs if packet is an A-MPDU and will fire tracedCallback.
   * The A-MPDU reference number (RX side) is set within the method. It must be a different value
   * for each A-MPDU but the same for each subframe within one A-MPDU.
   *
   * \param psdu the PSDU being received
   * \param channelFreqMhz the frequency in MHz at which the packet is
   *        transmitted.
   * \param txVector the TXVECTOR that holds TX parameters
   * \param staId the STA-ID
   */
  void NotifyMonitorSniffTx (Ptr<const WifiPsdu> psdu,
                             uint16_t channelFreqMhz,
                             WifiTxVector txVector,
                             uint16_t staId = SU_STA_ID);

  /**
   * TracedCallback signature for monitor mode transmit events.
   *
   * \param packet the packet being transmitted
   * \param channelFreqMhz the frequency in MHz at which the packet is
   *        transmitted.
   * \param txVector the TXVECTOR that holds TX parameters
   * \param aMpdu the type of the packet (0 is not A-MPDU, 1 is a MPDU that is part of an A-MPDU and 2 is the last MPDU in an A-MPDU)
   *        and the A-MPDU reference number (must be a different value for each A-MPDU but the same for each subframe within one A-MPDU)
   * \param staId the STA-ID
   * \todo WifiTxVector should be passed by const reference because
   * of its size.
   */
  typedef void (* MonitorSnifferTxCallback)(const Ptr<const Packet> packet,
                                            uint16_t channelFreqMhz,
                                            WifiTxVector txVector,
                                            MpduInfo aMpdu,
                                            uint16_t staId);

  /**
   * TracedCallback signature for Phy transmit events.
   *
   * \param packet the packet being transmitted
   * \param txPowerW the transmit power in Watts
   */
  typedef void (* PhyTxBeginTracedCallback)(Ptr<const Packet> packet, double txPowerW);

  /**
   * TracedCallback signature for PSDU transmit events.
   *
   * \param psduMap the PSDU map being transmitted
   * \param txVector the TXVECTOR holding the TX parameters
   * \param txPowerW the transmit power in Watts
   */
  typedef void (* PsduTxBeginCallback)(WifiConstPsduMap psduMap, WifiTxVector txVector, double txPowerW);

  /**
   * TracedCallback signature for PhyRxBegin trace source.
   *
   * \param packet the packet being received
   * \param rxPowersW the receive power per channel band in Watts
   */
  typedef void (* PhyRxBeginTracedCallback) (Ptr<const Packet> packet, RxPowerWattPerChannelBand rxPowersW);

  /**
   * TracedCallback signature for start of PSDU reception events.
   *
   * \param txVector the TXVECTOR decoded from the PHY header
   * \param psduDuration the duration of the PSDU
   */
  typedef void (* PhyRxPayloadBeginTracedCallback)(WifiTxVector txVector, Time psduDuration);

  /**
   * Assign a fixed random variable stream number to the random variables
   * used by this model. Return the number of streams (possibly zero) that
   * have been assigned.
   *
   * \param stream first stream index to use
   * \return the number of stream indices assigned by this model
   */
  virtual int64_t AssignStreams (int64_t stream);

  /**
<<<<<<< HEAD
   * Sets the energy detection threshold (dBm).
   * The energy of a received signal should be higher than
   * this threshold (dbm) to allow the PHY layer to detect the signal.
   *
   * \param threshold the energy detction threshold in dBm
   */
  void SetEdThreshold (double threshold);
  /**
   * Return the energy detection threshold (dBm).
   *
   * \return the energy detection threshold in dBm
   */
  double GetEdThreshold (void) const;
  /**
   * Return the energy detection threshold.
   *
   * \return the energy detection threshold.
   */
  double GetEdThresholdW (void) const;
  /**
   * Sets the CCA threshold (dBm). The energy of a received signal
   * should be higher than this threshold to allow the PHY
   * layer to declare CCA BUSY state.
   *
   * \param threshold the CCA threshold in dBm
   */
  void SetCcaMode1Threshold (double threshold);
  /**
   * Return the CCA threshold (dBm).
   *
   * \return the CCA threshold in dBm
   */
  double GetCcaMode1Threshold (void) const;
  /**
   * Sets the RX loss (dB) in the Signal-to-Noise-Ratio due to non-idealities in the receiver.
   *
   * \param noiseFigureDb noise figure in dB
   */
  void SetRxNoiseFigure (double noiseFigureDb);
  /**
   * Return the RX noise figure (dBm).
   *
   * \return the RX noise figure in dBm
   */
  double GetRxNoiseFigure (void) const;
  /**
   * Sets the minimum available transmission power level (dBm).
   *
   * \param start the minimum transmission power level (dBm)
   */
  void SetTxPowerStart (double start);
  /**
   * Return the minimum available transmission power level (dBm).
   *
   * \return the minimum available transmission power level (dBm)
   */
  virtual double GetTxPowerStart (void) const;
  /**
   * Sets the maximum available transmission power level (dBm).
   *
   * \param end the maximum transmission power level (dBm)
   */
  void SetTxPowerEnd (double end);
  /**
   * Return the maximum available transmission power level (dBm).
   *
   * \return the maximum available transmission power level (dBm)
   */
  virtual double GetTxPowerEnd (void) const;
  /**
   * Sets the number of transmission power levels available between the
   * minimum level and the maximum level. Transmission power levels are
   * equally separated (in dBm) with the minimum and the maximum included.
   *
   * \param n the number of available levels
   */
  void SetNTxPower (uint32_t n);
  /**
   * Return the number of available transmission power levels.
   *
   * \return the number of available transmission power levels
   */
  virtual uint32_t GetNTxPower (void) const;
  /**
   * Sets the transmission gain (dB).
   *
   * \param gain the transmission gain in dB
   */
  void SetTxGain (double gain);
  /**
   * Return the transmission gain (dB).
   *
   * \return the transmission gain in dB
   */
  double GetTxGain (void) const;
  /**
   * Sets the reception gain (dB).
   *
   * \param gain the reception gain in dB
   */
  void SetRxGain (double gain);
  /**
   * Return the reception gain (dB).
   *
   * \return the reception gain in dB
   */
  double GetRxGain (void) const;
  /**
   * Sets the device this PHY is associated with.
   *
   * \param device the device this PHY is associated with
   */
  void SetDevice (Ptr<NetDevice> device);
  /**
   * Return the device this PHY is associated with
   *
   * \return the device this PHY is associated with
   */
  Ptr<NetDevice> GetDevice (void) const;
  /**
   * \brief assign a mobility model to this device
   *
   * This method allows a user to specify a mobility model that should be
   * associated with this physical layer.  Calling this method is optional
   * and only necessary if the user wants to override the mobility model
   * that is aggregated to the node.
   *
   * \param mobility the mobility model this PHY is associated with
   */
  void SetMobility (Ptr<MobilityModel> mobility);
  /**
   * Return the mobility model this PHY is associated with.
   * This method will return either the mobility model that has been
   * explicitly set by a call to YansWifiPhy::SetMobility(), or else
   * will return the mobility model (if any) that has been aggregated
   * to the node.
   *
   * \return the mobility model this PHY is associated with
   */
  Ptr<MobilityModel> GetMobility (void);

  /**
   * \param freq the operating center frequency (MHz) on this node.
   */
  virtual void SetFrequency (uint32_t freq);
  /**
   * \return the operating center frequency (MHz) 
   */
  virtual uint32_t GetFrequency (void) const;
=======
   * Sets the receive sensitivity threshold (dBm).
   * The energy of a received signal should be higher than
   * this threshold to allow the PHY layer to detect the signal.
   *
   * \param threshold the receive sensitivity threshold in dBm
   */
  void SetRxSensitivity (double threshold);
  /**
   * Return the receive sensitivity threshold (dBm).
   *
   * \return the receive sensitivity threshold in dBm
   */
  double GetRxSensitivity (void) const;
>>>>>>> origin
  /**
   * Sets the CCA threshold (dBm). The energy of a received signal
   * should be higher than this threshold to allow the PHY
   * layer to declare CCA BUSY state.
   *
   * \param threshold the CCA threshold in dBm
   */
<<<<<<< HEAD
  virtual void SetNumberOfTransmitAntennas (uint32_t tx);
=======
  void SetCcaEdThreshold (double threshold);
>>>>>>> origin
  /**
   * Return the CCA threshold (dBm).
   *
   * \return the CCA threshold in dBm
   */
<<<<<<< HEAD
  virtual uint32_t GetNumberOfTransmitAntennas (void) const;
  /**
  * \param rx the number of receivers on this node.
  */
  virtual void SetNumberOfReceiveAntennas (uint32_t rx);
  /**
   * \return the number of receivers on this node.
   */
  virtual uint32_t GetNumberOfReceiveAntennas (void) const;

  /**
   * Enable or disable short/long guard interval.
   *
   * \param guardInterval Enable or disable guard interval
   */
  virtual void SetGuardInterval (bool guardInterval);
  /**
   * Return whether guard interval is being used.
   *
   * \return true if guard interval is being used, false otherwise
   */
  virtual bool GetGuardInterval (void) const;
  /**
   * Enable or disable LDPC.
   * \param ldpc Enable or disable LDPC
   */
  virtual void SetLdpc (bool ldpc);
  /**
   * Return if LDPC is supported.
   *
   * \return true if LDPC is supported, false otherwise
   */
  virtual bool GetLdpc (void) const;
  /**
   * Enable or disable STBC.
   *
   * \param stbc Enable or disable STBC
   */
  virtual void SetStbc (bool stbc);
  /**
   * Return whether STBC is supported.
   *
   * \return true if STBC is supported, false otherwise
   */
  virtual bool GetStbc (void) const;
  /**
   * Enable or disable Greenfield support.
   *
   * \param greenfield Enable or disable Greenfield
   */
  virtual void SetGreenfield (bool greenfield);
  /**
   * Return whether Greenfield is supported.
   *
   * \return true if Greenfield is supported, false otherwise
   */
  virtual bool GetGreenfield (void) const;
  /**
   * Enable or disable short PLCP preamble.
   *
   * \param preamble sets whether short PLCP preamble is supported or not
   */
  virtual void SetShortPlcpPreambleSupported (bool preamble);
  /**
   * Return whether short PLCP preamble is supported.
   *
   * \returns if short PLCP preamble is supported or not
   */
  virtual bool GetShortPlcpPreambleSupported (void) const;

  /**
   * Sets the error rate model.
   *
   * \param rate the error rate model
   */
  void SetErrorRateModel (Ptr<ErrorRateModel> rate);
  /**
   * Return the error rate model this PHY is using.
   *
   * \return the error rate model this PHY is using
   */
  Ptr<ErrorRateModel> GetErrorRateModel (void) const;

=======
  double GetCcaEdThreshold (void) const;
  /**
   * Sets the RX loss (dB) in the Signal-to-Noise-Ratio due to non-idealities in the receiver.
   *
   * \param noiseFigureDb noise figure in dB
   */
  void SetRxNoiseFigure (double noiseFigureDb);
  /**
   * Sets the minimum available transmission power level (dBm).
   *
   * \param start the minimum transmission power level (dBm)
   */
  void SetTxPowerStart (double start);
  /**
   * Return the minimum available transmission power level (dBm).
   *
   * \return the minimum available transmission power level (dBm)
   */
  double GetTxPowerStart (void) const;
  /**
   * Sets the maximum available transmission power level (dBm).
   *
   * \param end the maximum transmission power level (dBm)
   */
  void SetTxPowerEnd (double end);
  /**
   * Return the maximum available transmission power level (dBm).
   *
   * \return the maximum available transmission power level (dBm)
   */
  double GetTxPowerEnd (void) const;
  /**
   * Sets the number of transmission power levels available between the
   * minimum level and the maximum level. Transmission power levels are
   * equally separated (in dBm) with the minimum and the maximum included.
   *
   * \param n the number of available levels
   */
  void SetNTxPower (uint8_t n);
  /**
   * Return the number of available transmission power levels.
   *
   * \return the number of available transmission power levels
   */
  uint8_t GetNTxPower (void) const;
  /**
   * Sets the transmission gain (dB).
   *
   * \param gain the transmission gain in dB
   */
  void SetTxGain (double gain);
  /**
   * Return the transmission gain (dB).
   *
   * \return the transmission gain in dB
   */
  double GetTxGain (void) const;
>>>>>>> origin
  /**
   * Sets the reception gain (dB).
   *
   * \param gain the reception gain in dB
   */
<<<<<<< HEAD
  virtual uint32_t GetChannelWidth (void) const;
=======
  void SetRxGain (double gain);
>>>>>>> origin
  /**
   * Return the reception gain (dB).
   *
   * \return the reception gain in dB
   */
<<<<<<< HEAD
  virtual void SetChannelWidth (uint32_t channelwidth);
  /**
   * \param channelwidth channel width (in MHz) to support
   */
  virtual void AddSupportedChannelWidth (uint32_t channelwidth);
  /**
   * \return a vector containing the supported channel widths, values in MHz
   */
  virtual std::vector<uint32_t> GetSupportedChannelWidthSet (void) const;
  /**
   * \return the maximum number of supported Rx spatial streams
   */
  virtual uint8_t GetSupportedRxSpatialStreams (void) const;
  /**
   * \return the maximum number of supported Tx spatial streams
   */
  virtual uint8_t GetSupportedTxSpatialStreams (void) const;
  /**
   * Convert from dBm to Watts.
   *
   * \param dbm the power in dBm
   *
   * \return the equivalent Watts for the given dBm
   */
  double DbmToW (double dbm) const;
  /**
   * Convert from dB to ratio.
   *
   * \param db
   *
   * \return ratio
   */
  double DbToRatio (double db) const;
  /**
   * Convert from Watts to dBm.
   *
   * \param w the power in Watts
   *
   * \return the equivalent dBm for the given Watts
   */
  double WToDbm (double w) const;
  /**
   * Convert from ratio to dB.
   *
   * \param ratio
   *
   * \return dB
   */
  double RatioToDb (double ratio) const;
=======
  double GetRxGain (void) const;

  /**
   * Sets the device this PHY is associated with.
   *
   * \param device the device this PHY is associated with
   */
  void SetDevice (const Ptr<NetDevice> device);
  /**
   * Return the device this PHY is associated with
   *
   * \return the device this PHY is associated with
   */
  Ptr<NetDevice> GetDevice (void) const;
  /**
   * \brief assign a mobility model to this device
   *
   * This method allows a user to specify a mobility model that should be
   * associated with this physical layer.  Calling this method is optional
   * and only necessary if the user wants to override the mobility model
   * that is aggregated to the node.
   *
   * \param mobility the mobility model this PHY is associated with
   */
  void SetMobility (const Ptr<MobilityModel> mobility);
  /**
   * Return the mobility model this PHY is associated with.
   * This method will return either the mobility model that has been
   * explicitly set by a call to YansWifiPhy::SetMobility(), or else
   * will return the mobility model (if any) that has been aggregated
   * to the node.
   *
   * \return the mobility model this PHY is associated with
   */
  Ptr<MobilityModel> GetMobility (void) const;

  /**
   * Set the operating channel according to the specified parameters. If this object
   * has been already initialized, setting the operating channel involves a channel
   * switch, which might be suppressed (e.g., if this object is in sleep mode) or
   * delayed (e.g., if this object is transmitting a frame).
   *
   * \param number the channel number (use 0 to leave it unspecified)
   * \param frequency the channel center frequency in MHz (use 0 to leave it unspecified)
   * \param width the channel width in MHz (use 0 to leave it unspecified)
   */
  void SetOperatingChannel (uint8_t number, uint16_t frequency, uint16_t width);
  /**
   * If the operating channel for this object has not been set yet, the given
   * center frequency is saved and will be used, along with the channel number and
   * width that have been saved similarly, to set the operating channel when the
   * standard and band are configured. Note that if center frequency and
   * channel number are both 0 when the standard and band are configured, a default
   * channel (of the configured width, if any, or the default width for the current
   * standard and band, otherwise) is set.
   * If the operating channel for this object has been already set, the specified
   * center frequency must uniquely identify a channel in the band being used. If so,
   * this method may still fail to take action if the PHY model determines that
   * the operating channel cannot be switched for some reason (e.g. sleep state)
   *
   * \param freq the operating center frequency (MHz) on this node.
   */
  virtual void SetFrequency (uint16_t freq);
  /**
   * \return the operating center frequency (MHz)
   */
  uint16_t GetFrequency (void) const;
  /**
   * Set the index of the primary 20 MHz channel (0 indicates the 20 MHz subchannel
   * with the lowest center frequency).
   *
   * \param index the index of the primary 20 MHz channel
   */
  void SetPrimary20Index (uint8_t index);
  /**
   * \param antennas the number of antennas on this node.
   */
  void SetNumberOfAntennas (uint8_t antennas);
  /**
   * \return the number of antennas on this device
   */
  uint8_t GetNumberOfAntennas (void) const;
  /**
   * \param streams the maximum number of supported TX spatial streams.
   */
  void SetMaxSupportedTxSpatialStreams (uint8_t streams);
  /**
   * \return the maximum number of supported TX spatial streams
   */
  uint8_t GetMaxSupportedTxSpatialStreams (void) const;
  /**
   * \param streams the maximum number of supported RX spatial streams.
   */
  void SetMaxSupportedRxSpatialStreams (uint8_t streams);
  /**
   * \return the maximum number of supported RX spatial streams
   */
  uint8_t GetMaxSupportedRxSpatialStreams (void) const;
  /**
   * Enable or disable short PHY preamble.
   *
   * \param preamble sets whether short PHY preamble is supported or not
   */
  void SetShortPhyPreambleSupported (bool preamble);
  /**
   * Return whether short PHY preamble is supported.
   *
   * \returns if short PHY preamble is supported or not
   */
  bool GetShortPhyPreambleSupported (void) const;

  /**
   * Sets the error rate model.
   *
   * \param rate the error rate model
   */
  void SetErrorRateModel (const Ptr<ErrorRateModel> rate);
  /**
   * Attach a receive ErrorModel to the WifiPhy.
   *
   * The WifiPhy may optionally include an ErrorModel in
   * the packet receive chain. The error model is additive
   * to any modulation-based error model based on SNR, and
   * is typically used to force specific packet losses or
   * for testing purposes.
   *
   * \param em Pointer to the ErrorModel.
   */
  void SetPostReceptionErrorModel (const Ptr<ErrorModel> em);
  /**
   * Sets the frame capture model.
   *
   * \param frameCaptureModel the frame capture model
   */
  void SetFrameCaptureModel (const Ptr<FrameCaptureModel> frameCaptureModel);
  /**
   * Sets the preamble detection model.
   *
   * \param preambleDetectionModel the preamble detection model
   */
  void SetPreambleDetectionModel (const Ptr<PreambleDetectionModel> preambleDetectionModel);
  /**
   * Sets the wifi radio energy model.
   *
   * \param wifiRadioEnergyModel the wifi radio energy model
   */
  void SetWifiRadioEnergyModel (const Ptr<WifiRadioEnergyModel> wifiRadioEnergyModel);

  /**
   * \return the channel width in MHz
   */
  uint16_t GetChannelWidth (void) const;
  /**
   * If the operating channel for this object has not been set yet, the given
   * channel width is saved and will be used, along with the center frequency and
   * channel number that have been saved similarly, to set the operating channel
   * when the standard and band are configured. Note that if center frequency and
   * channel number are both 0 when the standard and band are configured, a default
   * channel (of the configured width, if any, or the default width for the current
   * standard and band, otherwise) is set.
   * Do not call this method when the standard and band of this object have been
   * already configured, because it cannot uniquely identify a channel in the band
   * being used.
   *
   * \param channelWidth the channel width (in MHz)
   */
  virtual void SetChannelWidth (uint16_t channelWidth);
  /**
   * \param width the channel width (in MHz) to support
   */
  void AddSupportedChannelWidth (uint16_t width);
  /**
   * \return a vector containing the supported channel widths, values in MHz
   */
  std::vector<uint16_t> GetSupportedChannelWidthSet (void) const;

  /**
   * Get the power of the given power level in dBm.
   * In SpectrumWifiPhy implementation, the power levels are equally spaced (in dBm).
   *
   * \param power the power level
   *
   * \return the transmission power in dBm at the given power level
   */
  double GetPowerDbm (uint8_t power) const;

  /**
   * Reset PHY to IDLE, with some potential TX power restrictions for the next transmission.
   *
   * \param powerRestricted flag whether the transmit power is restricted for the next transmission
   * \param txPowerMaxSiso the SISO transmit power restriction for the next transmission in dBm
   * \param txPowerMaxMimo the MIMO transmit power restriction for the next transmission in dBm
   */
  void ResetCca (bool powerRestricted, double txPowerMaxSiso = 0, double txPowerMaxMimo = 0);
  /**
   * Compute the transmit power for the next transmission.
   * The returned power will satisfy the power density constraints
   * after addition of antenna gain.
   *
   * \param ppdu the PPDU to transmit
   * \return the transmit power in dBm for the next transmission
   */
  double GetTxPowerForTransmission (Ptr<const WifiPpdu> ppdu) const;
  /**
   * Notify the PHY that an access to the channel was requested.
   * This is typically called by the channel access manager to
   * to notify the PHY about an ongoing transmission.
   * The PHY will use this information to determine whether
   * it should use power restriction as imposed by OBSS_PD SR.
   */
  void NotifyChannelAccessRequested (void);


  /**
   * \param bandWidth the width (MHz) of the band used for the OFDMA transmission. Must be
   *                  a multiple of 20 MHz
   * \param guardBandwidth width of the guard band (MHz)
   * \param range the subcarrier range of the HE RU
   * \param bandIndex the index (starting at 0) of the band within the operating channel
   * \return the converted subcarriers
   *
   * This is a helper function to convert HE RU subcarriers, which are relative to the center frequency subcarrier, to the indexes used by the Spectrum model.
   */
  virtual WifiSpectrumBand ConvertHeRuSubcarriers (uint16_t bandWidth, uint16_t guardBandwidth,
                                                   HeRu::SubcarrierRange range, uint8_t bandIndex = 0) const;

  /**
   * Add the PHY entity to the map of __implemented__ PHY entities for the
   * given modulation class.
   * Through this method, child classes can add their own PHY entities in
   * a static manner.
   *
   * \param modulation the modulation class
   * \param phyEntity the PHY entity
   */
  static void AddStaticPhyEntity (WifiModulationClass modulation, Ptr<PhyEntity> phyEntity);

  /**
   * Get the __implemented__ PHY entity corresponding to the modulation class.
   * This is used to compute the different amendment-specific parameters within
   * calling static methods.
   *
   * \param modulation the modulation class
   * \return the pointer to the static implemented PHY entity
   */
  static const Ptr<const PhyEntity> GetStaticPhyEntity (WifiModulationClass modulation);

  /**
   * Get the supported PHY entity corresponding to the modulation class, for
   * the WifiPhy instance.
   *
   * \param modulation the modulation class
   * \return the pointer to the supported PHY entity
   */
  Ptr<PhyEntity> GetPhyEntity (WifiModulationClass modulation) const;

  /**
   * \return the UID of the previously received PPDU (reset to UINT64_MAX upon transmission)
   */
  uint64_t GetPreviouslyRxPpduUid (void) const;

  /**
   * \param currentChannelWidth channel width of the current transmission (MHz)
   * \return the width of the guard band (MHz)
   *
   * Note: in order to properly model out of band transmissions for OFDM, the guard
   * band has been configured so as to expand the modeled spectrum up to the
   * outermost referenced point in "Transmit spectrum mask" sections' PSDs of
   * each PHY specification of 802.11-2016 standard. It thus ultimately corresponds
   * to the current channel bandwidth (which can be different from devices max
   * channel width).
   *
   * This method is only relevant for SpectrumWifiPhy.
   */
  virtual uint16_t GetGuardBandwidth (uint16_t currentChannelWidth) const = 0;
  /**
   * \return a tuple containing the minimum rejection (in dBr) for the inner band,
   *                            the minimum rejection (in dBr) for the outer band, and
   *                            the maximum rejection (in dBr) for the outer band
   *                            for the transmit spectrum mask.
   *
   * This method is only relevant for SpectrumWifiPhy.
   */
  virtual std::tuple<double, double, double> GetTxMaskRejectionParams (void) const = 0;

protected:
  virtual void DoDispose (void);

  /**
   * Reset data upon end of TX or RX
   */
  void Reset (void);

  /**
   * Perform any actions necessary when user changes operating channel after
   * initialization.
   *
   * \return zero if the PHY can immediately switch channel, a positive value
   *         indicating the amount of time to wait until the channel switch can
   *         be performed or a negative value indicating that channel switch is
   *         currently not possible (i.e., the radio is in sleep mode)
   */
  Time DoChannelSwitch (void);

  /**
   * Check if PHY state should move to CCA busy state based on current
   * state of interference tracker.  In this model, CCA becomes busy when
   * the aggregation of all signals as tracked by the InterferenceHelper
   * class is higher than the CcaEdThreshold
   *
   * \param channelWidth the channel width in MHz used for RSSI measurement
   */
  void SwitchMaybeToCcaBusy (uint16_t channelWidth);

  /**
   * Return the channel width used to measure the RSSI.
   * This corresponds to the primary channel unless it corresponds to the
   * HE TB PPDU solicited by the AP.
   *
   * \param ppdu the PPDU that is being received
   * \return the channel width (in MHz) used for RSSI measurement
   */
  uint16_t GetMeasurementChannelWidth (const Ptr<const WifiPpdu> ppdu) const;

  /**
   * Get the start band index and the stop band index for a given band
   *
   * \param bandWidth the width of the band to be returned (MHz)
   * \param bandIndex the index of the band to be returned
   *
   * \return a pair of start and stop indexes that defines the band
   */
  virtual WifiSpectrumBand GetBand (uint16_t bandWidth, uint8_t bandIndex = 0);

  /**
   * If the operating channel width is a multiple of 20 MHz, return the start
   * band index and the stop band index for the primary channel of the given
   * bandwidth (which must be a multiple of 20 MHz and not exceed the operating
   * channel width). Otherwise, this call is equivalent to GetBand with
   * <i>bandIndex</i> equal to zero.
   *
   * \param bandWidth the width of the band to be returned (MHz)
   *
   * \return a pair of start and stop indexes that defines the band
   */
  WifiSpectrumBand GetPrimaryBand (uint16_t bandWidth);

  /**
   * Add the PHY entity to the map of supported PHY entities for the
   * given modulation class for the WifiPhy instance.
   * This is a wrapper method used to check that the PHY entity is
   * in the static map of implemented PHY entities (\see m_staticPhyEntities).
   * In addition, child classes can add their own PHY entities.
   *
   * \param modulation the modulation class
   * \param phyEntity the PHY entity
   */
  void AddPhyEntity (WifiModulationClass modulation, Ptr<PhyEntity> phyEntity);

  InterferenceHelper m_interference;   //!< the class handling interference computations
  Ptr<UniformRandomVariable> m_random; //!< Provides uniform random variables.
  Ptr<WifiPhyStateHelper> m_state;     //!< Pointer to WifiPhyStateHelper

  uint32_t m_txMpduReferenceNumber;    //!< A-MPDU reference number to identify all transmitted subframes belonging to the same received A-MPDU
  uint32_t m_rxMpduReferenceNumber;    //!< A-MPDU reference number to identify all received subframes belonging to the same received A-MPDU

  EventId m_endPhyRxEvent;             //!< the end of PHY receive event
  EventId m_endTxEvent;                //!< the end of transmit event

  Ptr<Event> m_currentEvent; //!< Hold the current event
  std::map <std::pair<uint64_t /* UID*/, WifiPreamble>, Ptr<Event> > m_currentPreambleEvents; //!< store event associated to a PPDU (that has a unique ID and preamble combination) whose preamble is being received

  uint64_t m_previouslyRxPpduUid;  //!< UID of the previously received PPDU, reset to UINT64_MAX upon transmission

  /**
   * This map holds the supported PHY entities.
   *
   * The set of parameters (e.g. mode) that this WifiPhy(-derived class) can
   * support can be obtained through it.
   *
   * When it comes to modes, in conversation we call this set
   * the DeviceRateSet (not a term you'll find in the standard), and
   * it is a superset of standard-defined parameters such as the
   * OperationalRateSet, and the BSSBasicRateSet (which, themselves,
   * have a superset/subset relationship).
   *
   * Mandatory rates relevant to this WifiPhy can be found by
   * iterating over the elements of this map, for each modulation class,
   * looking for WifiMode objects for which
   * WifiMode::IsMandatory() is true.
   */
  std::map<WifiModulationClass, Ptr<PhyEntity> > m_phyEntities;
>>>>>>> origin

protected:
  // Inherited
  virtual void DoInitialize (void);
  virtual void DoDispose (void);

  /**
   * The default implementation does nothing and returns true.  This method 
   * is typically called internally by SetChannelNumber ().
   *
   * \brief Perform any actions necessary when user changes channel number
   * \param id channel number to try to switch to
   * \return true if WifiPhy can actually change the number; false if not
   * \see SetChannelNumber
   */
  virtual bool DoChannelSwitch (uint16_t id);
  /**
   * The default implementation does nothing and returns true.  This method
   * is typically called internally by SetFrequency ().
   *
   * \brief Perform any actions necessary when user changes frequency
   * \param frequency frequency to try to switch to
   * \return true if WifiPhy can actually change the frequency; false if not
   * \see SetFrequency
   */
  virtual bool DoFrequencySwitch (uint32_t frequency);

  /**
   * Get the power of the given power level in dBm.
   * In SpectrumWifiPhy implementation, the power levels are equally spaced (in dBm).
   *
   * \param power the power level
   *
   * \return the transmission power in dBm at the given power level
   */
  double GetPowerDbm (uint8_t power) const;
  
  InterferenceHelper m_interference;   //!< Pointer to InterferenceHelper
  Ptr<UniformRandomVariable> m_random; //!< Provides uniform random variables.
  Ptr<WifiPhyStateHelper> m_state;     //!< Pointer to WifiPhyStateHelper

  uint16_t m_mpdusNum;                 //!< carries the number of expected mpdus that are part of an A-MPDU
  bool m_plcpSuccess;                  //!< Flag if the PLCP of the packet or the first MPDU in an A-MPDU has been received
  uint32_t m_txMpduReferenceNumber;    //!< A-MPDU reference number to identify all transmitted subframes belonging to the same received A-MPDU
  uint32_t m_rxMpduReferenceNumber;    //!< A-MPDU reference number to identify all received subframes belonging to the same received A-MPDU
  
  EventId m_endRxEvent;
  EventId m_endPlcpRxEvent;

private:
  /**
<<<<<<< HEAD
   * \brief post-construction setting of frequency and/or channel number
   *
   * This method exists to handle the fact that two attribute values,
   * Frequency and ChannelNumber, are coupled.  The initialization of
   * these values needs to be deferred until after attribute construction 
   * time, to avoid static initialization order issues.  This method is
   * typically called either when ConfigureStandard () is called or when
   * DoInitialize () is called.  
   */
  void InitializeFrequencyChannelNumber (void);
  /**
=======
>>>>>>> origin
   * Configure WifiPhy with appropriate channel frequency and
   * supported rates for 802.11a standard.
   */
  void Configure80211a (void);
  /**
   * Configure WifiPhy with appropriate channel frequency and
   * supported rates for 802.11b standard.
   */
  void Configure80211b (void);
  /**
   * Configure WifiPhy with appropriate channel frequency and
   * supported rates for 802.11g standard.
   */
  void Configure80211g (void);
  /**
   * Configure WifiPhy with appropriate channel frequency and
<<<<<<< HEAD
   * supported rates for 802.11a standard with 10MHz channel spacing.
   */
  void Configure80211_10Mhz (void);
  /**
   * Configure WifiPhy with appropriate channel frequency and
   * supported rates for 802.11a standard with 5MHz channel spacing.
   */
  void Configure80211_5Mhz ();
  void ConfigureHolland (void);
=======
   * supported rates for 802.11p standard.
   */
  void Configure80211p (void);
>>>>>>> origin
  /**
   * Configure WifiPhy with appropriate channel frequency and
   * supported rates for 802.11n standard.
   */
  void Configure80211n (void);
  /**
   * Configure WifiPhy with appropriate channel frequency and
   * supported rates for 802.11ac standard.
   */
  void Configure80211ac (void);
  /**
<<<<<<< HEAD
   * Configure the device Mcs set with the appropriate HtMcs modes for
=======
   * Configure WifiPhy with appropriate channel frequency and
   * supported rates for 802.11ax standard.
   */
  void Configure80211ax (void);
  /**
   * Configure the device MCS set with the appropriate HtMcs modes for
>>>>>>> origin
   * the number of available transmit spatial streams
   */
  void ConfigureHtDeviceMcsSet (void);
  /**
<<<<<<< HEAD
   * Configure the PHY-level parameters for different Wi-Fi standard.
   * This method is called when defaults for each standard must be 
   * selected.
   *
   * \param standard the Wi-Fi standard
   */
  virtual void ConfigureDefaultsForStandard (enum WifiPhyStandard standard);
  /**
   * Configure the PHY-level parameters for different Wi-Fi standard.
   * This method is called when the Frequency or ChannelNumber attributes
   * are set by the user.  If the Frequency or ChannelNumber are valid for
   * the standard, they are used instead.
   *
   * \param standard the Wi-Fi standard
   */
  virtual void ConfigureChannelForStandard (enum WifiPhyStandard standard);

  /**
   * Look for channel number matching the frequency and width
   * \param frequency The center frequency to use
   * \param width The channel width to use
   * \return the channel number if found, zero if not
   */
  uint16_t FindChannelNumberForFrequencyWidth (uint32_t frequency, uint32_t width) const;
  /**
   * Lookup frequency/width pair for channelNumber/standard pair
   * \param channelNumber The channel number to check
   * \param standard The WifiPhyStandard to check
   * \return the FrequencyWidthPair found
   */
  FrequencyWidthPair GetFrequencyWidthForChannelNumberStandard (uint16_t channelNumber, enum WifiPhyStandard standard) const;
=======
   * Add the given MCS to the device MCS set.
   *
   * \param mode the MCS to add to the device MCS set
   */
  void PushMcs (WifiMode mode);
  /**
   * Rebuild the mapping of MCS values to indices in the device MCS set.
   */
  void RebuildMcsMap (void);

  /**
   * Due to newly arrived signal, the current reception cannot be continued and has to be aborted
   * \param reason the reason the reception is aborted
   *
   */
  void AbortCurrentReception (WifiPhyRxfailureReason reason);

  /**
   * Get the PSDU addressed to that PHY in a PPDU (useful for MU PPDU).
   *
   * \param ppdu the PPDU to extract the PSDU from
   * \return the PSDU addressed to that PHY
   */
  Ptr<const WifiPsdu> GetAddressedPsduInPpdu (Ptr<const WifiPpdu> ppdu) const;
>>>>>>> origin

  /**
   * The trace source fired when a packet begins the transmission process on
   * the medium.
   *
   * \see class CallBackTraceSource
   */
  TracedCallback<Ptr<const Packet>, double > m_phyTxBeginTrace;
  /**
   * The trace source fired when a PSDU map begins the transmission process on
   * the medium.
   *
   * \see class CallBackTraceSource
   */
  TracedCallback<WifiConstPsduMap, WifiTxVector, double /* TX power (W) */> m_phyTxPsduBeginTrace;

  /**
   * The trace source fired when a packet ends the transmission process on
   * the medium.
   *
   * \see class CallBackTraceSource
   */
  TracedCallback<Ptr<const Packet> > m_phyTxEndTrace;

  /**
   * The trace source fired when the PHY layer drops a packet as it tries
   * to transmit it.
   *
   * \see class CallBackTraceSource
   */
  TracedCallback<Ptr<const Packet> > m_phyTxDropTrace;

  /**
   * The trace source fired when a packet begins the reception process from
   * the medium.
   *
   * \see class CallBackTraceSource
   */
  TracedCallback<Ptr<const Packet>, RxPowerWattPerChannelBand > m_phyRxBeginTrace;

  /**
   * The trace source fired when the reception of the PHY payload (PSDU) begins.
   *
   * This traced callback models the behavior of the PHY-RXSTART
   * primitive which is launched upon correct decoding of
   * the PHY header and support of modes within.
   * We thus assume that it is sent just before starting
   * the decoding of the payload, since it's there that
   * support of the header's content is checked. In addition,
   * it's also at that point that the correct decoding of
   * HT-SIG, VHT-SIGs, and HE-SIGs are checked.
   *
   * \see class CallBackTraceSource
   */
  TracedCallback<WifiTxVector, Time> m_phyRxPayloadBeginTrace;

  /**
   * The trace source fired when a packet ends the reception process from
   * the medium.
   *
   * \see class CallBackTraceSource
   */
  TracedCallback<Ptr<const Packet> > m_phyRxEndTrace;

  /**
   * The trace source fired when the PHY layer drops a packet it has received.
   *
   * \see class CallBackTraceSource
   */
  TracedCallback<Ptr<const Packet>, WifiPhyRxfailureReason > m_phyRxDropTrace;

  /**
   * A trace source that emulates a Wi-Fi device in monitor mode
   * sniffing a packet being received.
   *
   * As a reference with the real world, firing this trace
   * corresponds in the madwifi driver to calling the function
   * ieee80211_input_monitor()
   *
   * \see class CallBackTraceSource
   * \todo WifiTxVector and signalNoiseDbm should be passed as
   *       const references because of their sizes.
   */
<<<<<<< HEAD
  TracedCallback<Ptr<const Packet>, uint16_t, uint16_t, uint32_t,
                 WifiPreamble, WifiTxVector, struct mpduInfo, struct signalNoiseDbm> m_phyMonitorSniffRxTrace;
=======
  TracedCallback<Ptr<const Packet>, uint16_t /* frequency (MHz) */, WifiTxVector, MpduInfo, SignalNoiseDbm, uint16_t /* STA-ID*/> m_phyMonitorSniffRxTrace;
>>>>>>> origin

  /**
   * A trace source that emulates a Wi-Fi device in monitor mode
   * sniffing a packet being transmitted.
   *
   * As a reference with the real world, firing this trace
   * corresponds in the madwifi driver to calling the function
   * ieee80211_input_monitor()
   *
   * \see class CallBackTraceSource
   * \todo WifiTxVector should be passed by const reference because
   * of its size.
   */
<<<<<<< HEAD
  TracedCallback<Ptr<const Packet>, uint16_t, uint16_t, uint32_t,
                 WifiPreamble, WifiTxVector, struct mpduInfo> m_phyMonitorSniffTxTrace;
    
  /**
   * This vector holds the set of transmission modes that this
   * WifiPhy(-derived class) can support. In conversation we call this
   * the DeviceRateSet (not a term you'll find in the standard), and
   * it is a superset of standard-defined parameters such as the
   * OperationalRateSet, and the BSSBasicRateSet (which, themselves,
   * have a superset/subset relationship).
   *
   * Mandatory rates relevant to this WifiPhy can be found by
   * iterating over this vector looking for WifiMode objects for which
   * WifiMode::IsMandatory() is true.
   *
   * A quick note is appropriate here (well, here is as good a place
   * as any I can find)...
   *
   * In the standard there is no text that explicitly precludes
   * production of a device that does not support some rates that are
   * mandatory (according to the standard) for PHYs that the device
   * happens to fully or partially support.
   *
   * This approach is taken by some devices which choose to only support,
   * for example, 6 and 9 Mbps ERP-OFDM rates for cost and power
   * consumption reasons (i.e., these devices don't need to be designed
   * for and waste current on the increased linearity requirement of
   * higher-order constellations when 6 and 9 Mbps more than meet their
   * data requirements). The wording of the standard allows such devices
   * to have an OperationalRateSet which includes 6 and 9 Mbps ERP-OFDM
   * rates, despite 12 and 24 Mbps being "mandatory" rates for the
   * ERP-OFDM PHY.
   *
   * Now this doesn't actually have any impact on code, yet. It is,
   * however, something that we need to keep in mind for the
   * future. Basically, the key point is that we can't be making
   * assumptions like "the Operational Rate Set will contain all the
   * mandatory rates".
   */
  WifiModeList m_deviceRateSet;
  WifiModeList m_deviceMcsSet;

  std::vector<uint32_t> m_bssMembershipSelectorSet;

  enum WifiPhyStandard m_standard;     //!< WifiPhyStandard
  bool m_isConstructed;                //!< true when ready to set frequency
  uint32_t m_channelCenterFrequency;   //!< Center frequency in MHz
  uint32_t m_initialFrequency;         //!< Store frequency until initialization
  bool m_frequencyChannelNumberInitialized; //!< Store initialization state
  uint32_t m_channelWidth;             //!< Channel width

  double m_edThresholdW;          //!< Energy detection threshold in watts
  double   m_ccaMode1ThresholdW;  //!< Clear channel assessment (CCA) threshold in watts
=======
  TracedCallback<Ptr<const Packet>, uint16_t /* frequency (MHz) */, WifiTxVector, MpduInfo, uint16_t /* STA-ID*/> m_phyMonitorSniffTxTrace;

  /**
   * Map of __implemented__ PHY entities. This is used to compute the different
   * amendment-specific parameters in a static manner.
   * For PHY entities supported by a given WifiPhy instance,
   * \see m_phyEntities.
   */
  static std::map<WifiModulationClass, Ptr<PhyEntity> > m_staticPhyEntities;

  WifiPhyStandard m_standard;               //!< WifiPhyStandard
  WifiPhyBand m_band;                       //!< WifiPhyBand
  uint16_t m_initialFrequency;              //!< Store frequency until initialization (MHz)
  uint8_t m_initialChannelNumber;           //!< Store channel number until initialization
  uint16_t m_initialChannelWidth;           //!< Store channel width (MHz) until initialization
  uint8_t m_initialPrimary20Index;          //!< Store the index of primary20 until initialization

  WifiPhyOperatingChannel m_operatingChannel;       //!< Operating channel
  std::vector<uint16_t> m_supportedChannelWidthSet; //!< Supported channel width set (MHz)

  Time m_sifs;                              //!< Short Interframe Space (SIFS) duration
  Time m_slot;                              //!< Slot duration
  Time m_pifs;                              //!< PCF Interframe Space (PIFS) duration
  Time m_ackTxTime;                         //!< estimated Ack TX time
  Time m_blockAckTxTime;                    //!< estimated BlockAck TX time

  double   m_rxSensitivityW;      //!< Receive sensitivity threshold in watts
  double   m_ccaEdThresholdW;     //!< Clear channel assessment (CCA) threshold in watts
>>>>>>> origin
  double   m_txGainDb;            //!< Transmission gain (dB)
  double   m_rxGainDb;            //!< Reception gain (dB)
  double   m_txPowerBaseDbm;      //!< Minimum transmission power (dBm)
  double   m_txPowerEndDbm;       //!< Maximum transmission power (dBm)
<<<<<<< HEAD
  uint32_t m_nTxPower;            //!< Number of available transmission power levels
  
  bool     m_ldpc;                  //!< Flag if LDPC is used
  bool     m_stbc;                  //!< Flag if STBC is used
  bool     m_greenfield;            //!< Flag if GreenField format is supported
  bool     m_guardInterval;         //!< Flag if short guard interval is used
  bool     m_shortPreamble;         //!< Flag if short PLCP preamble is supported

  uint32_t m_numberOfTransmitters;     //!< Number of transmitters
  uint32_t m_numberOfReceivers;        //!< Number of receivers

  typedef std::map<ChannelNumberStandardPair,FrequencyWidthPair> ChannelToFrequencyWidthMap;
  static ChannelToFrequencyWidthMap m_channelToFrequencyWidth;

  std::vector<uint32_t> m_supportedChannelWidthSet; //!< Supported channel width
  uint16_t             m_channelNumber;  //!< Operating channel number
  uint16_t             m_initialChannelNumber;  //!< Initial channel number

  Time m_channelSwitchDelay;     //!< Time required to switch between channel
  uint32_t m_totalAmpduSize;     //!< Total size of the previously transmitted MPDUs in an A-MPDU, used for the computation of the number of symbols needed for the last MPDU in the A-MPDU
  double m_totalAmpduNumSymbols; //!< Number of symbols previously transmitted for the MPDUs in an A-MPDU, used for the computation of the number of symbols needed for the last MPDU in the A-MPDU
  
  Ptr<NetDevice>     m_device;   //!< Pointer to the device
  Ptr<MobilityModel> m_mobility; //!< Pointer to the mobility model
=======
  uint8_t  m_nTxPower;            //!< Number of available transmission power levels
  double m_powerDensityLimit;     //!< the power density limit (dBm/MHz)

  bool m_powerRestricted;        //!< Flag whether transmit power is restricted by OBSS PD SR
  double m_txPowerMaxSiso;       //!< SISO maximum transmit power due to OBSS PD SR power restriction (dBm)
  double m_txPowerMaxMimo;       //!< MIMO maximum transmit power due to OBSS PD SR power restriction (dBm)
  bool m_channelAccessRequested; //!< Flag if channels access has been requested (used for OBSS_PD SR)

  bool m_shortPreamble;        //!< Flag if short PHY preamble is supported
  uint8_t m_numberOfAntennas;  //!< Number of transmitters
  uint8_t m_txSpatialStreams;  //!< Number of supported TX spatial streams
  uint8_t m_rxSpatialStreams;  //!< Number of supported RX spatial streams

  Time m_channelSwitchDelay;     //!< Time required to switch between channel

  Ptr<NetDevice>     m_device;   //!< Pointer to the device
  Ptr<MobilityModel> m_mobility; //!< Pointer to the mobility model

  Ptr<FrameCaptureModel> m_frameCaptureModel;           //!< Frame capture model
  Ptr<PreambleDetectionModel> m_preambleDetectionModel; //!< Preamble detection model
  Ptr<WifiRadioEnergyModel> m_wifiRadioEnergyModel;     //!< Wifi radio energy model
  Ptr<ErrorModel> m_postReceptionErrorModel;            //!< Error model for receive packet events
  Time m_timeLastPreambleDetected;                      //!< Record the time the last preamble was detected

  Callback<void> m_capabilitiesChangedCallback; //!< Callback when PHY capabilities changed
>>>>>>> origin
};

/**
 * \param os           output stream
 * \param rxSignalInfo received signal info to stringify
 * \return output stream
 */
std::ostream& operator<< (std::ostream& os, RxSignalInfo rxSignalInfo);

} //namespace ns3

#endif /* WIFI_PHY_H */

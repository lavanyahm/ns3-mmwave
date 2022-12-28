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
 *          Ghada Badawy <gbadawy@gmail.com>
 *          Sébastien Deronne <sebastien.deronne@gmail.com>
 *
 * Ported from yans-wifi-phy.h by several contributors starting
 * with Nicola Baldo and Dean Armstrong
 */

#ifndef SPECTRUM_WIFI_PHY_H
#define SPECTRUM_WIFI_PHY_H

#include "ns3/antenna-model.h"
<<<<<<< HEAD
#include "wifi-phy.h"
#include "wifi-spectrum-phy-interface.h"
#include "ns3/spectrum-channel.h"
#include "ns3/spectrum-interference.h"

namespace ns3 {

=======
#include "ns3/spectrum-channel.h"
#include "ns3/spectrum-model.h"
#include "wifi-phy.h"
#include <map>

class SpectrumWifiPhyFilterTest;

namespace ns3 {

class WifiSpectrumPhyInterface;
struct WifiSpectrumSignalParameters;

>>>>>>> origin
/**
 * \brief 802.11 PHY layer model
 * \ingroup wifi
 *
 * This PHY implements a spectrum-aware enhancement of the 802.11 SpectrumWifiPhy
 * model.
 *
 * This PHY model depends on a channel loss and delay
 * model as provided by the ns3::SpectrumPropagationLossModel
 * and ns3::PropagationDelayModel classes.
 *
 */
class SpectrumWifiPhy : public WifiPhy
{
public:
<<<<<<< HEAD
=======
  /// allow SpectrumWifiPhyFilterTest class access
  friend class ::SpectrumWifiPhyFilterTest;

  /**
   * \brief Get the type ID.
   * \return the object TypeId
   */
>>>>>>> origin
  static TypeId GetTypeId (void);

  SpectrumWifiPhy ();
  virtual ~SpectrumWifiPhy ();

<<<<<<< HEAD
=======
  // Implementation of pure virtual method.
  void StartTx (Ptr<WifiPpdu> ppdu) override;
  Ptr<Channel> GetChannel (void) const override;
  uint16_t GetGuardBandwidth (uint16_t currentChannelWidth) const override;
  std::tuple<double, double, double> GetTxMaskRejectionParams (void) const override;

>>>>>>> origin
  /**
   * Set the SpectrumChannel this SpectrumWifiPhy is to be connected to.
   *
   * \param channel the SpectrumChannel this SpectrumWifiPhy is to be connected to
   */
<<<<<<< HEAD
  void SetChannel (Ptr<SpectrumChannel> channel);
  /**
   * Add a channel number to the list of operational channels.  This method
   * is used to support scanning for strongest base station.
   *
   * \param channelNumber the channel number to add
   */
  void AddOperationalChannel (uint16_t channelNumber);
  /**
   * Return a list of channels to which it may be possible to roam
   * By default, this method will return the current channel number followed
   * by any other channel numbers that have been added.
   *
   * \return vector of channel numbers to which it may be possible to roam
   */
  std::vector<uint16_t> GetOperationalChannelList (void) const;
  /**
   * Clear the list of operational channels.
   */
  void ClearOperationalChannelList (void);

  /**
   * Starting receiving the payload of a packet (i.e. the first bit of the packet has arrived).
   *
   * \param packet the arriving packet
   * \param txVector the TXVECTOR of the arriving packet
   * \param preamble the preamble of the arriving packet
   * \param mpdutype the type of the MPDU as defined in WifiPhy::mpduType.
   * \param event the corresponding event of the first time the packet arrives
   */
  void StartReceivePacket (Ptr<Packet> packet,
                           WifiTxVector txVector,
                           WifiPreamble preamble,
                           enum mpduType mpdutype,
                           Ptr<InterferenceHelper::Event> event);

  /**
   * Input method for delivering a signal from the spectrum channel
   * and low-level Phy interface to this SpectrumWifiPhy instance.
=======
  void SetChannel (const Ptr<SpectrumChannel> channel);

  /**
   * Input method for delivering a signal from the spectrum channel
   * and low-level PHY interface to this SpectrumWifiPhy instance.
>>>>>>> origin
   *
   * \param rxParams Input signal parameters
   */
  void StartRx (Ptr<SpectrumSignalParameters> rxParams);
<<<<<<< HEAD
=======

>>>>>>> origin
  /**
   * Method to encapsulate the creation of the WifiSpectrumPhyInterface
   * object (used to bind the WifiSpectrumPhy to a SpectrumChannel) and
   * to link it to this SpectrumWifiPhy instance
   *
   * \param device pointer to the NetDevice object including this new object
   */
  void CreateWifiSpectrumPhyInterface (Ptr<NetDevice> device);
  /**
<<<<<<< HEAD
   * \return pointer to WifiSpectrumPhyInterface associated with this Phy
   */
  Ptr<WifiSpectrumPhyInterface> GetSpectrumPhy (void) const;
  /**
   * \param antenna an AntennaModel to include in the transmitted
   * SpectrumSignalParameters (in case any objects downstream of the
   * SpectrumWifiPhy wish to adjust signal properties based on the
   * transmitted antenna model.  This antenna is also used when
   * the underlying WifiSpectrumPhyInterface::GetRxAntenna() method
   * is called.
   *
   * Note:  this method may be split into separate SetTx and SetRx
   * methods in the future if the modelling need for this arises
   */
  void SetAntenna (Ptr<AntennaModel> antenna);
=======
   * \param antenna an AntennaModel to include in the transmitted
   *                SpectrumSignalParameters (in case any objects downstream of the
   *                SpectrumWifiPhy wish to adjust signal properties based on the
   *                transmitted antenna model.  This antenna is also used when
   *                the underlying WifiSpectrumPhyInterface::GetRxAntenna() method
   *                is called.
   *
   * Note:  this method may be split into separate SetTx and SetRx
   * methods in the future if the modeling need for this arises
   */
  void SetAntenna (const Ptr<AntennaModel> antenna);
>>>>>>> origin
  /**
   * Get the antenna model used for reception
   *
   * \return the AntennaModel used for reception
   */
  Ptr<AntennaModel> GetRxAntenna (void) const;
  /**
<<<<<<< HEAD
   * \return returns the SpectrumModel that this SpectrumPhy expects to be used
   * for all SpectrumValues that are passed to StartRx. If 0 is
   * returned, it means that any model will be accepted.
   */
  Ptr<const SpectrumModel> GetRxSpectrumModel () const;
  /**
   * Callback invoked at the end of a frame reception, to notify whether
   * the frame was received successfully (true) or not (false)
   */
  typedef Callback<void,bool> RxCallback;
  /**
   * Set the packet received callback (invoked at the end of a frame
   * reception), to notify whether the frame was received successfully
   * or not.
   *
   * \param callback the function to hook to the callback
   */
  void SetPacketReceivedCallback (RxCallback callback);

  /**
   * Callback invoked when the Phy model starts to process a signal
=======
   * \return the SpectrumModel that this SpectrumPhy expects to be used
   *         for all SpectrumValues that are passed to StartRx. If 0 is
   *         returned, it means that any model will be accepted.
   */
  Ptr<const SpectrumModel> GetRxSpectrumModel ();

  /**
   * \return the width of each band (Hz)
   */
  uint32_t GetBandBandwidth (void) const;

  /**
   * Callback invoked when the PHY model starts to process a signal
>>>>>>> origin
   *
   * \param signalType Whether signal is WiFi (true) or foreign (false)
   * \param senderNodeId Node Id of the sender of the signal
   * \param rxPower received signal power (dBm)
   * \param duration Signal duration
   */
  typedef void (* SignalArrivalCallback) (bool signalType, uint32_t senderNodeId, double rxPower, Time duration);

<<<<<<< HEAD
  virtual void SetReceiveOkCallback (WifiPhy::RxOkCallback callback);
  virtual void SetReceiveErrorCallback (WifiPhy::RxErrorCallback callback);
  virtual void SendPacket (Ptr<const Packet> packet, WifiTxVector txVector, enum WifiPreamble preamble);
  virtual void SendPacket (Ptr<const Packet> packet, WifiTxVector txVector, enum WifiPreamble preamble, enum mpduType mpdutype);
  virtual void RegisterListener (WifiPhyListener *listener);
  virtual void UnregisterListener (WifiPhyListener *listener);
  virtual void SetSleepMode (void);
  virtual void ResumeFromSleep (void);
  virtual Ptr<WifiChannel> GetChannel (void) const;

protected:
  // Inherited
  virtual void DoDispose (void);
  virtual void DoInitialize (void);
  virtual bool DoChannelSwitch (uint16_t id);
  virtual bool DoFrequencySwitch (uint32_t frequency);

private:
  /**
   * The last bit of the packet has arrived.
   *
   * \param packet the packet that the last bit has arrived
   * \param preamble the preamble of the arriving packet
   * \param mpdutype the type of the MPDU as defined in WifiPhy::mpduType.
   * \param event the corresponding event of the first time the packet arrives
   */
  void EndReceive (Ptr<Packet> packet, enum WifiPreamble preamble, enum mpduType mpdutype, Ptr<InterferenceHelper::Event> event);

  /**
   * Check if Phy state should move to CCA busy state based on current
   * state of interference tracker.  In this model, CCA becomes busy when
   * the aggregation of all signals as tracked by the InterferenceHelper
   * class is higher than the CcaMode1Threshold
   */
  void SwitchMaybeToCcaBusy (void);

  /**
   * \param centerFrequency center frequency (MHz)
   * \param channelWidth channel width (MHz) of the channel
   * \param txPowerW power in W to spread across the bands
   * \return Ptr to SpectrumValue
   *
   * This is a helper function to create the right Tx PSD corresponding
   * to the standard in use.
   */
  Ptr<SpectrumValue> GetTxPowerSpectralDensity (uint32_t centerFrequency, uint32_t channelWidth, double txPowerW) const;

  Ptr<SpectrumChannel> m_channel;        //!< SpectrumChannel that this SpectrumWifiPhy is connected to
  std::vector<uint16_t> m_operationalChannelList; //!< List of possible channels

  Ptr<WifiSpectrumPhyInterface> m_wifiSpectrumPhyInterface;
  Ptr<AntennaModel> m_antenna;
  mutable Ptr<const SpectrumModel> m_rxSpectrumModel;
  RxCallback m_rxCallback;
  bool m_disableWifiReception;          //!< forces this Phy to fail to sync on any signal
  TracedCallback<bool, uint32_t, double, Time> m_signalCb;

=======
  // The following four methods call to the base WifiPhy class method
  // but also generate a new SpectrumModel if called during runtime
  void SetChannelNumber (uint8_t id) override;
  void SetFrequency (uint16_t freq) override;
  void SetChannelWidth (uint16_t channelwidth) override;
  void ConfigureStandardAndBand (WifiPhyStandard standard, WifiPhyBand band) override;

  /**
   * This function is sending the signal to the Spectrum channel
   * after finishing the configuration of the transmit parameters.
   *
   * \param txParams the parameters to be provided to the Spectrum channel
   */
  void Transmit (Ptr<WifiSpectrumSignalParameters> txParams);

protected:
  void DoDispose (void) override;
  void DoInitialize (void) override;

  /**
   * Get the start band index and the stop band index for a given band
   *
   * \param bandWidth the width of the band to be returned (MHz)
   * \param bandIndex the index of the band to be returned
   *
   * \return a pair of start and stop indexes that defines the band
   */
  WifiSpectrumBand GetBand (uint16_t bandWidth, uint8_t bandIndex = 0) override;

private:
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
  WifiSpectrumBand ConvertHeRuSubcarriers (uint16_t bandWidth, uint16_t guardBandwidth,
                                           HeRu::SubcarrierRange range, uint8_t bandIndex = 0) const override;

  /**
   * Perform run-time spectrum model change
   */
  void ResetSpectrumModel (void);
  /**
   * This function is called to update the bands handled by the InterferenceHelper.
   */
  void UpdateInterferenceHelperBands (void);

  Ptr<SpectrumChannel> m_channel; //!< SpectrumChannel that this SpectrumWifiPhy is connected to

  Ptr<WifiSpectrumPhyInterface> m_wifiSpectrumPhyInterface; //!< Spectrum PHY interface
  Ptr<AntennaModel> m_antenna;                              //!< antenna model
  mutable Ptr<const SpectrumModel> m_rxSpectrumModel;       //!< receive spectrum model

  /// Map a spectrum band associated with an RU to the RU specification
  typedef std::map<WifiSpectrumBand, HeRu::RuSpec> RuBand;

  std::map<uint16_t, RuBand> m_ruBands;  /**< For each channel width, store all the distinct spectrum
                                              bands associated with every RU in a channel of that width */
  bool m_disableWifiReception;                              //!< forces this PHY to fail to sync on any signal
  TracedCallback<bool, uint32_t, double, Time> m_signalCb;  //!< Signal callback

  double m_txMaskInnerBandMinimumRejection; //!< The minimum rejection (in dBr) for the inner band of the transmit spectrum mask
  double m_txMaskOuterBandMinimumRejection; //!< The minimum rejection (in dBr) for the outer band of the transmit spectrum mask
  double m_txMaskOuterBandMaximumRejection; //!< The maximum rejection (in dBr) for the outer band of the transmit spectrum mask
>>>>>>> origin
};

} //namespace ns3

#endif /* SPECTRUM_WIFI_PHY_H */

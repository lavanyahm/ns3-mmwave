/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2005,2006 INRIA
 * Copyright (c) 2009 MIRKO BANCHI
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
 *          Mirko Banchi <mk.banchi@gmail.com>
 *          Stefano Avallone <stavallo@unina.it>
 */

#include "ns3/simulator.h"
#include "ns3/log.h"
<<<<<<< HEAD
#include "ns3/node.h"
#include "ns3/socket.h"
#include "ns3/double.h"
=======
>>>>>>> origin
#include "mac-low.h"
#include "qos-txop.h"
#include "snr-tag.h"
#include "ampdu-tag.h"
#include "wifi-mac-queue.h"
<<<<<<< HEAD
=======
#include "wifi-psdu.h"
#include "wifi-utils.h"
#include "ctrl-headers.h"
#include "mgt-headers.h"
#include "wifi-remote-station-manager.h"
#include "mpdu-aggregator.h"
#include "msdu-aggregator.h"
#include "ampdu-subframe-header.h"
#include "wifi-phy-listener.h"
#include "wifi-mac-trailer.h"
#include "wifi-phy.h"
#include "wifi-net-device.h"
#include "wifi-mac.h"
#include <algorithm>
#include "wifi-ack-policy-selector.h"
>>>>>>> origin

#undef NS_LOG_APPEND_CONTEXT
#define NS_LOG_APPEND_CONTEXT std::clog << "[mac=" << m_self << "] "

// Time (in nanoseconds) to be added to the PSDU duration to yield the duration
// of the timer that is started when the PHY indicates the start of the reception
// of a frame and we are waiting for a response.
#define PSDU_DURATION_SAFEGUARD 400

namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("MacLow");

<<<<<<< HEAD
MacLowTransmissionListener::MacLowTransmissionListener ()
{
}
MacLowTransmissionListener::~MacLowTransmissionListener ()
{
}
void
MacLowTransmissionListener::GotBlockAck (const CtrlBAckResponseHeader *blockAck, Mac48Address source, double rxSnr, WifiMode mode, double dataSnr)
{
}
void
MacLowTransmissionListener::MissedBlockAck (uint32_t nMpdus)
{
}

MacLowDcfListener::MacLowDcfListener ()
{
}
MacLowDcfListener::~MacLowDcfListener ()
{
}

MacLowAggregationCapableTransmissionListener::MacLowAggregationCapableTransmissionListener ()
{
}
MacLowAggregationCapableTransmissionListener::~MacLowAggregationCapableTransmissionListener ()
{
}
void MacLowAggregationCapableTransmissionListener::SetAmpdu (Mac48Address dest, bool enableAmpdu)
{
}
void MacLowAggregationCapableTransmissionListener::CompleteTransfer (Mac48Address address, uint8_t tid)
{
}
void
MacLowAggregationCapableTransmissionListener::CompleteMpduTx (Ptr<const Packet> packet, WifiMacHeader hdr, Time tstamp)
{
}
uint16_t
MacLowAggregationCapableTransmissionListener::GetNextSequenceNumberfor (WifiMacHeader *hdr)
{
  return 0;
}
uint16_t
MacLowAggregationCapableTransmissionListener::PeekNextSequenceNumberfor (WifiMacHeader *hdr)
{
  return 0;
}
Ptr<const Packet>
MacLowAggregationCapableTransmissionListener::PeekNextPacketInBaQueue (WifiMacHeader &header, Mac48Address recipient, uint8_t tid, Time *timestamp)
{
  return 0;
}
void
MacLowAggregationCapableTransmissionListener::RemoveFromBaQueue (uint8_t tid, Mac48Address recipient, uint16_t seqnumber)
{
}
uint32_t
MacLowAggregationCapableTransmissionListener::GetNOutstandingPackets (Mac48Address recipient, uint8_t tid)
{
  return 0;
}
uint32_t
MacLowAggregationCapableTransmissionListener::GetNRetryNeededPackets (Mac48Address recipient, uint8_t tid) const
{
  return 0;
}
Ptr<MsduAggregator>
MacLowAggregationCapableTransmissionListener::GetMsduAggregator (void) const
{
  return 0;
}
Ptr<MpduAggregator>
MacLowAggregationCapableTransmissionListener::GetMpduAggregator (void) const
{
  return 0;
}
Mac48Address
MacLowAggregationCapableTransmissionListener::GetSrcAddressForAggregation (const WifiMacHeader &hdr)
{
  return 0;
}
Mac48Address
MacLowAggregationCapableTransmissionListener::GetDestAddressForAggregation (const WifiMacHeader &hdr)
{
  return 0;
}

MacLowTransmissionParameters::MacLowTransmissionParameters ()
  : m_nextSize (0),
    m_waitAck (ACK_NONE),
    m_sendRts (false),
    m_overrideDurationId (Seconds (0))
{
}
void
MacLowTransmissionParameters::EnableNextData (uint32_t size)
{
  m_nextSize = size;
}
void
MacLowTransmissionParameters::DisableNextData (void)
{
  m_nextSize = 0;
}
void
MacLowTransmissionParameters::EnableOverrideDurationId (Time durationId)
{
  m_overrideDurationId = durationId;
}
void
MacLowTransmissionParameters::DisableOverrideDurationId (void)
{
  m_overrideDurationId = Seconds (0);
}
void
MacLowTransmissionParameters::EnableSuperFastAck (void)
{
  m_waitAck = ACK_SUPER_FAST;
}
void
MacLowTransmissionParameters::EnableBasicBlockAck (void)
{
  m_waitAck = BLOCK_ACK_BASIC;
}
void
MacLowTransmissionParameters::EnableCompressedBlockAck (void)
{
  m_waitAck = BLOCK_ACK_COMPRESSED;
}
void
MacLowTransmissionParameters::EnableMultiTidBlockAck (void)
{
  m_waitAck = BLOCK_ACK_MULTI_TID;
}
void
MacLowTransmissionParameters::EnableFastAck (void)
{
  m_waitAck = ACK_FAST;
}
void
MacLowTransmissionParameters::EnableAck (void)
{
  m_waitAck = ACK_NORMAL;
}
void
MacLowTransmissionParameters::DisableAck (void)
{
  m_waitAck = ACK_NONE;
}
void
MacLowTransmissionParameters::EnableRts (void)
{
  m_sendRts = true;
}
void
MacLowTransmissionParameters::DisableRts (void)
{
  m_sendRts = false;
}
bool
MacLowTransmissionParameters::MustWaitAck (void) const
{
  return (m_waitAck != ACK_NONE);
}
bool
MacLowTransmissionParameters::MustWaitNormalAck (void) const
{
  return (m_waitAck == ACK_NORMAL);
}
bool
MacLowTransmissionParameters::MustWaitFastAck (void) const
{
  return (m_waitAck == ACK_FAST);
}
bool
MacLowTransmissionParameters::MustWaitSuperFastAck (void) const
{
  return (m_waitAck == ACK_SUPER_FAST);
}
bool
MacLowTransmissionParameters::MustWaitBasicBlockAck (void) const
{
  return (m_waitAck == BLOCK_ACK_BASIC) ? true : false;
}
bool
MacLowTransmissionParameters::MustWaitCompressedBlockAck (void) const
{
  return (m_waitAck == BLOCK_ACK_COMPRESSED) ? true : false;
}
bool
MacLowTransmissionParameters::MustWaitMultiTidBlockAck (void) const
{
  return (m_waitAck == BLOCK_ACK_MULTI_TID) ? true : false;
}
bool
MacLowTransmissionParameters::MustSendRts (void) const
{
  return m_sendRts;
}
bool
MacLowTransmissionParameters::HasDurationId (void) const
{
  return (m_overrideDurationId != Seconds (0));
}
Time
MacLowTransmissionParameters::GetDurationId (void) const
{
  NS_ASSERT (m_overrideDurationId != Seconds (0));
  return m_overrideDurationId;
}
bool
MacLowTransmissionParameters::HasNextPacket (void) const
{
  return (m_nextSize != 0);
}
uint32_t
MacLowTransmissionParameters::GetNextPacketSize (void) const
{
  NS_ASSERT (HasNextPacket ());
  return m_nextSize;
}

std::ostream &operator << (std::ostream &os, const MacLowTransmissionParameters &params)
{
  os << "["
     << "send rts=" << params.m_sendRts << ", "
     << "next size=" << params.m_nextSize << ", "
     << "dur=" << params.m_overrideDurationId << ", "
     << "ack=";
  switch (params.m_waitAck)
    {
    case MacLowTransmissionParameters::ACK_NONE:
      os << "none";
      break;
    case MacLowTransmissionParameters::ACK_NORMAL:
      os << "normal";
      break;
    case MacLowTransmissionParameters::ACK_FAST:
      os << "fast";
      break;
    case MacLowTransmissionParameters::ACK_SUPER_FAST:
      os << "super-fast";
      break;
    case MacLowTransmissionParameters::BLOCK_ACK_BASIC:
      os << "basic-block-ack";
      break;
    case MacLowTransmissionParameters::BLOCK_ACK_COMPRESSED:
      os << "compressed-block-ack";
      break;
    case MacLowTransmissionParameters::BLOCK_ACK_MULTI_TID:
      os << "multi-tid-block-ack";
      break;
    }
  os << "]";
  return os;
}


=======
>>>>>>> origin
/**
 * Listener for PHY events. Forwards to MacLow
 */
class PhyMacLowListener : public ns3::WifiPhyListener
{
public:
  /**
   * Create a PhyMacLowListener for the given MacLow.
   *
   * \param macLow
   */
  PhyMacLowListener (ns3::MacLow *macLow)
    : m_macLow (macLow)
  {
  }
  virtual ~PhyMacLowListener ()
  {
  }
  void NotifyRxStart (Time duration)
  {
  }
  void NotifyRxEndOk (void)
  {
  }
  void NotifyRxEndError (void)
  {
  }
  void NotifyTxStart (Time duration, double txPowerDbm)
  {
  }
  void NotifyMaybeCcaBusyStart (Time duration)
  {
  }
  void NotifySwitchingStart (Time duration)
  {
    m_macLow->NotifySwitchingStartNow (duration);
  }
  void NotifySleep (void)
  {
    m_macLow->NotifySleepNow ();
  }
  void NotifyOff (void)
  {
    m_macLow->NotifyOffNow ();
  }
  void NotifyWakeup (void)
  {
  }
  void NotifyOn (void)
  {
  }

private:
  ns3::MacLow *m_macLow; ///< the MAC
};


MacLow::MacLow ()
  : m_msduAggregator (0),
    m_mpduAggregator (0),
    m_normalAckTimeoutEvent (),
    m_blockAckTimeoutEvent (),
    m_ctsTimeoutEvent (),
    m_sendCtsEvent (),
    m_sendAckEvent (),
    m_sendDataEvent (),
    m_waitIfsEvent (),
    m_endTxNoAckEvent (),
    m_currentPacket (0),
    m_currentTxop (0),
    m_lastNavStart (Seconds (0)),
    m_lastNavDuration (Seconds (0)),
    m_cfpStart (Seconds (0)),
    m_lastBeacon (Seconds (0)),
    m_cfpForeshortening (Seconds (0)),
    m_promisc (false),
    m_phyMacLowListener (0),
    m_ctsToSelfSupported (false),
<<<<<<< HEAD
    m_nTxMpdus (0)
=======
    m_cfAckInfo ()
>>>>>>> origin
{
  NS_LOG_FUNCTION (this);
}

MacLow::~MacLow ()
{
  NS_LOG_FUNCTION (this);
}

/* static */
TypeId
MacLow::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::MacLow")
    .SetParent<Object> ()
    .SetGroupName ("Wifi")
    .AddConstructor<MacLow> ()
  ;
  return tid;
}

void
MacLow::SetupPhyMacLowListener (const Ptr<WifiPhy> phy)
{
  m_phyMacLowListener = new PhyMacLowListener (this);
  phy->RegisterListener (m_phyMacLowListener);
}

void
MacLow::RemovePhyMacLowListener (Ptr<WifiPhy> phy)
{
  if (m_phyMacLowListener != 0 )
    {
      phy->UnregisterListener (m_phyMacLowListener);
      delete m_phyMacLowListener;
      m_phyMacLowListener = 0;
    }
}

void
MacLow::DoDispose (void)
{
  NS_LOG_FUNCTION (this);
  m_normalAckTimeoutEvent.Cancel ();
  m_blockAckTimeoutEvent.Cancel ();
  m_ctsTimeoutEvent.Cancel ();
  m_sendCtsEvent.Cancel ();
  m_sendAckEvent.Cancel ();
  m_sendDataEvent.Cancel ();
  m_waitIfsEvent.Cancel ();
  m_endTxNoAckEvent.Cancel ();
  m_msduAggregator = 0;
  m_mpduAggregator = 0;
  m_phy = 0;
  m_stationManager = 0;
  if (m_phyMacLowListener != 0)
    {
      delete m_phyMacLowListener;
      m_phyMacLowListener = 0;
    }
<<<<<<< HEAD
  m_sentMpdus = 0;
  m_aggregateQueue = 0;
  m_ampdu = false;
=======
>>>>>>> origin
}

void
MacLow::CancelAllEvents (void)
{
  NS_LOG_FUNCTION (this);
  bool oneRunning = false;
  if (m_normalAckTimeoutEvent.IsRunning ())
    {
      m_normalAckTimeoutEvent.Cancel ();
      oneRunning = true;
    }
  if (m_blockAckTimeoutEvent.IsRunning ())
    {
      m_blockAckTimeoutEvent.Cancel ();
      oneRunning = true;
    }
  if (m_ctsTimeoutEvent.IsRunning ())
    {
      m_ctsTimeoutEvent.Cancel ();
      oneRunning = true;
    }
  if (m_sendCtsEvent.IsRunning ())
    {
      m_sendCtsEvent.Cancel ();
      oneRunning = true;
    }
  if (m_sendAckEvent.IsRunning ())
    {
      m_sendAckEvent.Cancel ();
      oneRunning = true;
    }
  if (m_sendDataEvent.IsRunning ())
    {
      m_sendDataEvent.Cancel ();
      oneRunning = true;
    }
  if (m_waitIfsEvent.IsRunning ())
    {
      m_waitIfsEvent.Cancel ();
      oneRunning = true;
    }
  if (m_endTxNoAckEvent.IsRunning ())
    {
      m_endTxNoAckEvent.Cancel ();
      oneRunning = true;
    }
  if (oneRunning && m_currentTxop != 0)
    {
      m_currentTxop->Cancel ();
      m_currentTxop = 0;
    }
}

void
MacLow::SetPhy (const Ptr<WifiPhy> phy)
{
  m_phy = phy;
  m_phy->TraceConnectWithoutContext ("PhyRxPayloadBegin", MakeCallback (&MacLow::RxStartIndication, this));
  m_phy->SetReceiveOkCallback (MakeCallback (&MacLow::DeaggregateAmpduAndReceive, this));
  m_phy->SetReceiveErrorCallback (MakeCallback (&MacLow::ReceiveError, this));
  SetupPhyMacLowListener (phy);
}

Ptr<WifiPhy>
MacLow::GetPhy (void) const
{
  return m_phy;
}

void
MacLow::ResetPhy (void)
{
<<<<<<< HEAD
  m_phy->SetReceiveOkCallback (MakeNullCallback<void, Ptr<Packet>, double, WifiTxVector, enum WifiPreamble> ());
  m_phy->SetReceiveErrorCallback (MakeNullCallback<void, Ptr<Packet>, double> ());
=======
  m_phy->TraceDisconnectWithoutContext ("PhyRxPayloadBegin", MakeCallback (&MacLow::RxStartIndication, this));
  m_phy->SetReceiveOkCallback (MakeNullCallback<void, Ptr<WifiPsdu>, double, WifiTxVector, std::vector<bool>> ());
  m_phy->SetReceiveErrorCallback (MakeNullCallback<void, Ptr<WifiPsdu>> ());
>>>>>>> origin
  RemovePhyMacLowListener (m_phy);
  m_phy = 0;
}

Ptr<QosTxop>
MacLow::GetEdca (uint8_t tid) const
{
  auto it = m_edca.find (QosUtilsMapTidToAc (tid));
  NS_ASSERT (it != m_edca.end ());
  return it->second;
}

void
MacLow::SetMac (const Ptr<WifiMac> mac)
{
  m_mac = mac;
}

void
MacLow::SetWifiRemoteStationManager (const Ptr<WifiRemoteStationManager> manager)
{
  m_stationManager = manager;
}

Ptr<MsduAggregator>
MacLow::GetMsduAggregator (void) const
{
  return m_msduAggregator;
}

Ptr<MpduAggregator>
MacLow::GetMpduAggregator (void) const
{
  return m_mpduAggregator;
}

void
MacLow::SetMsduAggregator (const Ptr<MsduAggregator> aggr)
{
  NS_LOG_FUNCTION (this << aggr);
  m_msduAggregator = aggr;
}

void
MacLow::SetMpduAggregator (const Ptr<MpduAggregator> aggr)
{
  NS_LOG_FUNCTION (this << aggr);
  m_mpduAggregator = aggr;
}

void
MacLow::SetAddress (Mac48Address ad)
{
  m_self = ad;
}

void
MacLow::SetCtsToSelfSupported (bool enable)
{
  m_ctsToSelfSupported = enable;
}

bool
MacLow::GetCtsToSelfSupported (void) const
{
  return m_ctsToSelfSupported;
}

void
MacLow::SetBeaconInterval (Time interval)
{
  m_beaconInterval = interval;
}

void
MacLow::SetCfpMaxDuration (Time cfpMaxDuration)
{
  m_cfpMaxDuration = cfpMaxDuration;
}

void
MacLow::SetBssid (Mac48Address bssid)
{
  m_bssid = bssid;
}

void
MacLow::SetPromisc (void)
{
  m_promisc = true;
}

Mac48Address
MacLow::GetAddress (void) const
{
  return m_self;
}

Time
MacLow::GetSifs (void) const
{
  return m_phy->GetSifs ();
}

Time
MacLow::GetSlotTime (void) const
{
  return m_phy->GetSlot ();
}

Time
MacLow::GetPifs (void) const
{
  return m_phy->GetPifs ();
}

Mac48Address
MacLow::GetBssid (void) const
{
  return m_bssid;
}

Time
MacLow::GetBeaconInterval (void) const
{
  return m_beaconInterval;
}

Time
MacLow::GetCfpMaxDuration (void) const
{
  return m_cfpMaxDuration;
}

bool
MacLow::IsPromisc (void) const
{
  return m_promisc;
}

void
MacLow::SetRxCallback (Callback<void, Ptr<WifiMacQueueItem>> callback)
{
  m_rxCallback = callback;
}

void
MacLow::RegisterChannelAccessManager (Ptr<ChannelAccessManager> channelAccessManager)
{
  m_channelAccessManagers.push_back (channelAccessManager);
}

void
MacLow::StartTransmission (Ptr<WifiMacQueueItem> mpdu,
                           MacLowTransmissionParameters params,
                           Ptr<Txop> txop)
{
  NS_LOG_FUNCTION (this << *mpdu << params << txop);
  NS_ASSERT (!m_cfAckInfo.expectCfAck);
  if (m_phy->IsStateOff ())
    {
      NS_LOG_DEBUG ("Cannot start TX because device is OFF");
      return;
    }
  /* m_currentPacket is not NULL because someone started
   * a transmission and was interrupted before one of:
   *   - ctsTimeout
   *   - sendDataAfterCTS
   * expired. This means that one of these timers is still
   * running. They are all cancelled below anyway by the
   * call to CancelAllEvents (because of at least one
   * of these two timers) which will trigger a call to the
   * previous listener's cancel method.
   *
   * This typically happens because the high-priority
   * QapScheduler has taken access to the channel from
   * one of the EDCA of the QAP.
   */
<<<<<<< HEAD
  m_currentPacket = packet->Copy ();
  // remove the priority tag attached, if any
  SocketPriorityTag priorityTag;
  m_currentPacket->RemovePacketTag (priorityTag);
  m_currentHdr = *hdr;
=======
  m_currentPacket = Create<WifiPsdu> (mpdu, false);
  const WifiMacHeader& hdr = mpdu->GetHeader ();
>>>>>>> origin
  CancelAllEvents ();
  m_currentTxop = txop;
  m_txParams = params;
<<<<<<< HEAD
  m_currentTxVector = GetDataTxVector (m_currentPacket, &m_currentHdr);

  if (!m_currentHdr.IsQosData () && !m_currentHdr.IsBlockAck () && !m_currentHdr.IsBlockAckReq ())
    {
      //This is mainly encountered when a higher priority control frame (such as beacons)
      //is sent between A-MPDU transmissions. It avoids to unexpectedly flush the aggregate
      //queue when previous RTS request has failed.
      m_ampdu = false;
    }
  else if (m_aggregateQueue->GetSize () > 0)
    {
      //m_aggregateQueue > 0 occurs when a RTS/CTS exchange failed before an A-MPDU transmission.
      //In that case, we transmit the same A-MPDU as previously.
      m_sentMpdus = m_aggregateQueue->GetSize ();
      m_ampdu = true;
      if (m_sentMpdus > 1)
        {
          m_txParams.EnableCompressedBlockAck ();
        }
      else if (m_currentHdr.IsQosData ())
        {
          //VHT single MPDUs are followed by normal ACKs
          m_txParams.EnableAck ();
        }
    }
  else
    {
      //Perform MPDU aggregation if possible
      m_ampdu = IsAmpdu (m_currentPacket, m_currentHdr);
      if (m_ampdu)
        {
          AmpduTag ampdu;
          m_currentPacket->PeekPacketTag (ampdu);
          if (ampdu.GetRemainingNbOfMpdus () > 0)
            {
              m_txParams.EnableCompressedBlockAck ();
            }
          else if (m_currentHdr.IsQosData ())
            {
              //VHT single MPDUs are followed by normal ACKs
              m_txParams.EnableAck ();
            }
        }
=======
  if (hdr.IsCtl ())
    {
      m_currentTxVector = GetRtsTxVector (mpdu);
    }
  else
    {
      m_currentTxVector = GetDataTxVector (mpdu);
>>>>>>> origin
    }
    
  if (NeedRts ())
    {
      m_txParams.EnableRts ();
    }
  else
    {
      m_txParams.DisableRts ();
    }

  /* The packet received by this function can be any of the following:
   * (a) a management frame dequeued from the Txop
   * (b) a non-QoS data frame dequeued from the Txop
   * (c) a non-group addressed QoS Data frame peeked or dequeued from a QosTxop
   * (d) a group addressed QoS data or DELBA Request frame dequeued from a QosTxop
   * (e) a BlockAckReq or ADDBA Request frame
   * (f) a fragment of non-QoS/QoS Data frame dequeued from the Txop/QosTxop
   */
  if (hdr.IsQosData () && !hdr.GetAddr1 ().IsGroup ()
      && !hdr.IsMoreFragments () && hdr.GetFragmentNumber () == 0)
    {
      // We get here if the received packet is a non-broadcast QoS data frame
      uint8_t tid = hdr.GetQosTid ();
      Ptr<QosTxop> qosTxop = m_edca.find (QosUtilsMapTidToAc (tid))->second;

      // if a TXOP limit exists, compute the remaining TXOP duration
      Time txopLimit = Time::Min ();
      if (m_currentTxop->GetTxopLimit ().IsStrictlyPositive ())
        {
          txopLimit = m_currentTxop->GetTxopRemaining () - CalculateOverheadTxTime (mpdu, m_txParams);
          NS_ASSERT (txopLimit.IsPositive ());
        }

      // QosTxop may send us a peeked frame
      Ptr<const WifiMacQueueItem> tmp = qosTxop->PeekNextFrame ();
      bool isPeeked = (tmp != 0 && tmp->GetPacket () == mpdu->GetPacket ());

      Ptr<WifiMacQueueItem> newMpdu;
      // If the frame has been peeked, dequeue it if it meets the size and duration constraints
      if (isPeeked)
        {
          newMpdu = qosTxop->DequeuePeekedFrame (mpdu, m_currentTxVector, true, 0, txopLimit);
        }
      else if (IsWithinSizeAndTimeLimits (mpdu, m_currentTxVector, 0, txopLimit))
        {
          newMpdu = mpdu;
        }

      if (newMpdu == 0)
        {
          // if the frame has been dequeued, then there is no BA agreement with the
          // receiver (otherwise the frame would have been peeked). Hence, the frame
          // has been sent under Normal Ack policy, not acknowledged and now retransmitted.
          // If we cannot send it now, let the QosTxop retransmit it again.
          // If the frame has been just peeked, reset the current packet at QosTxop.
          if (isPeeked)
            {
              qosTxop->UpdateCurrentPacket (Create<WifiMacQueueItem> (nullptr, WifiMacHeader ()));
            }
          return;
        }
      // Update the current packet at QosTxop, given that A-MSDU aggregation may have
      // been performed on the peeked frame
      qosTxop->UpdateCurrentPacket (newMpdu);

      //Perform MPDU aggregation if possible
      std::vector<Ptr<WifiMacQueueItem>> mpduList;
      if (m_mpduAggregator != 0)
        {
          mpduList = m_mpduAggregator->GetNextAmpdu (newMpdu, m_currentTxVector, txopLimit);
        }

      if (mpduList.size () > 1)
        {
          m_currentPacket = Create<WifiPsdu> (mpduList);

          NS_LOG_DEBUG ("tx unicast A-MPDU containing " << mpduList.size () << " MPDUs");
          qosTxop->SetAmpduExist (hdr.GetAddr1 (), true);
        }
      else if (m_currentTxVector.GetMode ().GetModulationClass () == WIFI_MOD_CLASS_VHT
               || m_currentTxVector.GetMode ().GetModulationClass () == WIFI_MOD_CLASS_HE)
        {
          // VHT/HE single MPDU
          m_currentPacket = Create<WifiPsdu> (newMpdu, true);

          NS_LOG_DEBUG ("tx unicast S-MPDU with sequence number " << hdr.GetSequenceNumber ());
          qosTxop->SetAmpduExist (hdr.GetAddr1 (), true);
        }
      else  // HT
        {
          m_currentPacket = Create<WifiPsdu> (newMpdu, false);
        }

      // A QoS Txop must have an installed ack policy selector
      NS_ASSERT (qosTxop->GetAckPolicySelector () != 0);
      qosTxop->GetAckPolicySelector ()->UpdateTxParams (m_currentPacket, m_txParams);
      qosTxop->GetAckPolicySelector ()->SetAckPolicy (m_currentPacket, m_txParams);
    }

  NS_LOG_DEBUG ("startTx size=" << m_currentPacket->GetSize () <<
                ", to=" << m_currentPacket->GetAddr1 () << ", txop=" << m_currentTxop);

  if (m_txParams.MustSendRts ())
    {
      SendRtsForPacket ();
    }
  else
    {
      if ((m_ctsToSelfSupported || m_stationManager->GetUseNonErpProtection ()) && NeedCtsToSelf ())
        {
          SendCtsToSelf ();
        }
      else
        {
          SendDataPacket ();
        }
    }

  /* When this method completes, either we have taken ownership of the medium or the device switched off in the meantime. */
  NS_ASSERT (m_phy->IsStateTx () || m_phy->IsStateOff ());
}

bool
<<<<<<< HEAD
MacLow::NeedRts (void)
{
  WifiTxVector dataTxVector = GetDataTxVector (m_currentPacket, &m_currentHdr);
  return m_stationManager->NeedRts (m_currentHdr.GetAddr1 (), &m_currentHdr,
                                    m_currentPacket, dataTxVector);
}

bool
MacLow::NeedCtsToSelf (void)
=======
MacLow::NeedCtsToSelf (void) const
>>>>>>> origin
{
  WifiTxVector dataTxVector = GetDataTxVector (*m_currentPacket->begin ());
  return m_stationManager->NeedCtsToSelf (dataTxVector);
}

<<<<<<< HEAD
void
MacLow::ReceiveError (Ptr<Packet> packet, double rxSnr)
{
  NS_LOG_FUNCTION (this << packet << rxSnr);
  NS_LOG_DEBUG ("rx failed ");
  if (m_txParams.MustWaitFastAck ())
=======
bool
MacLow::IsWithinSizeAndTimeLimits (Ptr<const WifiMacQueueItem> mpdu, WifiTxVector txVector,
                                    uint32_t ampduSize, Time ppduDurationLimit)
{
  NS_ASSERT (mpdu != 0 && mpdu->GetHeader ().IsQosData ());

  return IsWithinSizeAndTimeLimits (mpdu->GetSize (), mpdu->GetHeader ().GetAddr1 (),
                                    mpdu->GetHeader ().GetQosTid (), txVector,
                                    ampduSize, ppduDurationLimit);
}

bool
MacLow::IsWithinSizeAndTimeLimits (uint32_t mpduSize, Mac48Address receiver, uint8_t tid,
                                    WifiTxVector txVector, uint32_t ampduSize, Time ppduDurationLimit)
{
  NS_LOG_FUNCTION (this << mpduSize << receiver << +tid << txVector << ampduSize << ppduDurationLimit);

  if (ppduDurationLimit != Time::Min () && ppduDurationLimit.IsNegative ())
    {
      return false;
    }

  WifiModulationClass modulation = txVector.GetMode ().GetModulationClass ();

  uint32_t maxAmpduSize = 0;
  if (GetMpduAggregator ())
>>>>>>> origin
    {
      maxAmpduSize = GetMpduAggregator ()->GetMaxAmpduSize (receiver, tid, modulation);
    }

  // If maxAmpduSize is null, then ampduSize must be null as well
  NS_ASSERT (maxAmpduSize || ampduSize == 0);

  uint32_t ppduPayloadSize = mpduSize;

  // compute the correct size for A-MPDUs and S-MPDUs
  if (ampduSize > 0 || modulation >= WIFI_MOD_CLASS_VHT)
    {
      ppduPayloadSize = GetMpduAggregator ()->GetSizeIfAggregated (mpduSize, ampduSize);
    }

  if (maxAmpduSize > 0 && ppduPayloadSize > maxAmpduSize)
    {
      NS_LOG_DEBUG ("the frame does not meet the constraint on max A-MPDU size");
      return false;
    }

  // Get the maximum PPDU Duration based on the preamble type
  Time maxPpduDuration = GetPpduMaxTime (txVector.GetPreambleType ());

  Time txTime = m_phy->CalculateTxDuration (ppduPayloadSize, txVector, m_phy->GetPhyBand ());

  if ((ppduDurationLimit.IsStrictlyPositive () && txTime > ppduDurationLimit)
      || (maxPpduDuration.IsStrictlyPositive () && txTime > maxPpduDuration))
    {
      NS_LOG_DEBUG ("the frame does not meet the constraint on max PPDU duration");
      return false;
    }

  return true;
}

void
MacLow::RxStartIndication (WifiTxVector txVector, Time psduDuration)
{
  NS_LOG_FUNCTION (this);
  NS_LOG_DEBUG ("PSDU reception started for " << psduDuration.ToDouble (Time::US)
                << " us (txVector: " << txVector << ")");
  if (psduDuration.IsZero ())
    {
      //PHY-RXEND immediately follows PHY-RXSTART (e.g. when PPDU has been filtered), no need to reschedule timeouts (CCA will take over)
      return;
    }
  NS_ASSERT (psduDuration.IsStrictlyPositive ());

  if (m_normalAckTimeoutEvent.IsRunning ())
    {
      // we are waiting for a Normal Ack and something arrived
      NS_LOG_DEBUG ("Rescheduling Normal Ack timeout");
      m_normalAckTimeoutEvent.Cancel ();
      NotifyAckTimeoutResetNow ();
      m_normalAckTimeoutEvent = Simulator::Schedule (psduDuration + NanoSeconds (PSDU_DURATION_SAFEGUARD),
                                                     &MacLow::NormalAckTimeout, this);
    }
  else if (m_blockAckTimeoutEvent.IsRunning ())
    {
      // we are waiting for a BlockAck and something arrived
      NS_LOG_DEBUG ("Rescheduling Block Ack timeout");
      m_blockAckTimeoutEvent.Cancel ();
      NotifyAckTimeoutResetNow ();
      m_blockAckTimeoutEvent = Simulator::Schedule (psduDuration + NanoSeconds (PSDU_DURATION_SAFEGUARD),
                                                    &MacLow::BlockAckTimeout, this);
    }
  else if (m_ctsTimeoutEvent.IsRunning ())
    {
      // we are waiting for a CTS and something arrived
      NS_LOG_DEBUG ("Rescheduling CTS timeout");
      m_ctsTimeoutEvent.Cancel ();
      NotifyCtsTimeoutResetNow ();
      m_ctsTimeoutEvent = Simulator::Schedule (psduDuration + NanoSeconds (PSDU_DURATION_SAFEGUARD),
                                               &MacLow::CtsTimeout, this);
    }
  else if (m_navCounterResetCtsMissed.IsRunning ())
    {
      NS_LOG_DEBUG ("Cannot reset NAV");
      m_navCounterResetCtsMissed.Cancel ();
    }
}

void
MacLow::ReceiveError (Ptr<WifiPsdu> psdu)
{
  NS_LOG_FUNCTION (this << *psdu);
  NS_LOG_DEBUG ("rx failed");
  if (IsCfPeriod () && m_currentPacket->GetHeader (0).IsCfPoll ())
    {
      NS_ASSERT (m_currentTxop != 0);
      m_currentTxop->MissedCfPollResponse (m_cfAckInfo.expectCfAck);
    }
  else if (m_cfAckInfo.expectCfAck)
    {
      NS_ASSERT (m_currentTxop != 0);
      Ptr<Txop> txop = m_currentTxop;
      m_currentTxop = 0;
      txop->MissedAck ();
    }
  m_cfAckInfo.expectCfAck = false;
  return;
}

void
MacLow::NotifySwitchingStartNow (Time duration)
{
  NS_LOG_DEBUG ("switching channel. Cancelling MAC pending events");
  m_stationManager->Reset ();
  CancelAllEvents ();
  if (m_navCounterResetCtsMissed.IsRunning ())
    {
      m_navCounterResetCtsMissed.Cancel ();
    }
  m_lastNavStart = Simulator::Now ();
  m_lastNavDuration = Seconds (0);
  m_currentPacket = 0;
  m_currentTxop = 0;
}

void
MacLow::NotifySleepNow (void)
{
  NS_LOG_DEBUG ("Device in sleep mode. Cancelling MAC pending events");
  CancelAllEvents ();
  if (m_navCounterResetCtsMissed.IsRunning ())
    {
      m_navCounterResetCtsMissed.Cancel ();
    }
  m_lastNavStart = Simulator::Now ();
  m_lastNavDuration = Seconds (0);
  m_currentPacket = 0;
  m_currentTxop = 0;
}

void
MacLow::NotifyOffNow (void)
{
  NS_LOG_DEBUG ("Device is switched off. Cancelling MAC pending events");
  CancelAllEvents ();
  if (m_navCounterResetCtsMissed.IsRunning ())
    {
      m_navCounterResetCtsMissed.Cancel ();
    }
  m_lastNavStart = Simulator::Now ();
  m_lastNavDuration = Seconds (0);
  m_currentPacket = 0;
  m_currentTxop = 0;
}

void
MacLow::ReceiveOk (Ptr<WifiMacQueueItem> mpdu, double rxSnr, WifiTxVector txVector, bool ampduSubframe)
{
  NS_LOG_FUNCTION (this << *mpdu << rxSnr << txVector);
  /* An MPDU is received from the PHY.
   * When we have handled this MPDU,
   * we handle any packet present in the
   * packet queue.
   */
<<<<<<< HEAD
  WifiMacHeader hdr;
  packet->RemoveHeader (hdr);
  m_lastReceivedHdr = hdr;
=======
  const WifiMacHeader& hdr = mpdu->GetHeader ();
  Ptr<Packet> packet = mpdu->GetPacket ()->Copy ();
>>>>>>> origin

  bool isPrevNavZero = IsNavZero ();
  NS_LOG_DEBUG ("duration/id=" << hdr.GetDuration ());
  NotifyNav (packet, hdr);
  if (hdr.IsRts ())
    {
      /* see section 9.2.5.7 802.11-1999
       * A STA that is addressed by an RTS frame shall transmit a CTS frame after a SIFS
       * period if the NAV at the STA receiving the RTS frame indicates that the medium is
       * idle. If the NAV at the STA receiving the RTS indicates the medium is not idle,
       * that STA shall not respond to the RTS frame.
       */
      if (ampduSubframe)
        {
          NS_FATAL_ERROR ("Received RTS as part of an A-MPDU");
        }
      else
        {
          if (isPrevNavZero
              && hdr.GetAddr1 () == m_self)
            {
              NS_LOG_DEBUG ("rx RTS from=" << hdr.GetAddr2 () << ", schedule CTS");
              NS_ASSERT (m_sendCtsEvent.IsExpired ());
              m_stationManager->ReportRxOk (hdr.GetAddr2 (),
                                            rxSnr, txVector.GetMode ());
              m_sendCtsEvent = Simulator::Schedule (GetSifs (),
                                                    &MacLow::SendCtsAfterRts, this,
                                                    hdr.GetAddr2 (),
                                                    hdr.GetDuration (),
                                                    txVector,
                                                    rxSnr);
            }
          else
            {
              NS_LOG_DEBUG ("rx RTS from=" << hdr.GetAddr2 () << ", cannot schedule CTS");
            }
        }
    }
  else if (hdr.IsCts ()
           && hdr.GetAddr1 () == m_self
           && m_ctsTimeoutEvent.IsRunning ()
           && m_currentPacket != 0)
    {
      if (ampduSubframe)
        {
          NS_FATAL_ERROR ("Received CTS as part of an A-MPDU");
        }

      NS_LOG_DEBUG ("received cts from=" << m_currentPacket->GetAddr1 ());

      SnrTag tag;
      packet->RemovePacketTag (tag);
      m_stationManager->ReportRxOk (m_currentPacket->GetAddr1 (),
                                    rxSnr, txVector.GetMode ());
      m_stationManager->ReportRtsOk (m_currentPacket->GetAddr1 (), &m_currentPacket->GetHeader (0),
                                     rxSnr, txVector.GetMode (), tag.Get ());

      m_ctsTimeoutEvent.Cancel ();
      NotifyCtsTimeoutResetNow ();
      NS_ASSERT (m_sendDataEvent.IsExpired ());
      m_sendDataEvent = Simulator::Schedule (GetSifs (),
                                             &MacLow::SendDataAfterCts, this,
                                             hdr.GetDuration ());
    }
  else if (hdr.IsAck ()
           && hdr.GetAddr1 () == m_self
           && m_normalAckTimeoutEvent.IsRunning ()
           && m_txParams.MustWaitNormalAck ())
    {
      NS_LOG_DEBUG ("receive ack from=" << m_currentPacket->GetAddr1 ());
      SnrTag tag;
      packet->RemovePacketTag (tag);
      //When fragmentation is used, only update manager when the last fragment is acknowledged
      if (!m_txParams.HasNextPacket ())
        {
          m_stationManager->ReportRxOk (m_currentPacket->GetAddr1 (),
                                        rxSnr, txVector.GetMode ());
          m_stationManager->ReportDataOk (m_currentPacket->GetAddr1 (), &m_currentPacket->GetHeader (0),
                                          rxSnr, txVector.GetMode (), tag.Get (),
                                          m_currentTxVector, m_currentPacket->GetSize ());
        }
      // cancel the Normal Ack timer
      m_normalAckTimeoutEvent.Cancel ();
      NotifyAckTimeoutResetNow ();
      m_currentTxop->GotAck ();

<<<<<<< HEAD
      bool gotAck = false;
      if (m_txParams.MustWaitNormalAck ()
          && m_normalAckTimeoutEvent.IsRunning ())
        {
          m_normalAckTimeoutEvent.Cancel ();
          NotifyAckTimeoutResetNow ();
          gotAck = true;
        }
      if (m_txParams.MustWaitFastAck ()
          && m_fastAckTimeoutEvent.IsRunning ())
        {
          m_fastAckTimeoutEvent.Cancel ();
          NotifyAckTimeoutResetNow ();
          gotAck = true;
        }
      if (gotAck)
        {
          m_listener->GotAck (rxSnr, txVector.GetMode ());
        }
      if (m_txParams.HasNextPacket ())
        {
          m_waitSifsEvent = Simulator::Schedule (GetSifs (),
                                                 &MacLow::WaitSifsAfterEndTxFragment, this);
        }
      else if (m_currentHdr.IsQosData () && !m_ampdu)
        {
          m_waitSifsEvent = Simulator::Schedule (GetSifs (),
                                                 &MacLow::WaitSifsAfterEndTx, this);
=======
      if (m_txParams.HasNextPacket ())
        {
          m_waitIfsEvent = Simulator::Schedule (GetSifs (), &MacLow::WaitIfsAfterEndTxFragment, this);
        }
      else if (m_currentPacket->GetHeader (0).IsQosData () && m_currentTxop->IsQosTxop () &&
               m_currentTxop->GetTxopLimit ().IsStrictlyPositive () && m_currentTxop->GetTxopRemaining () > GetSifs ())
        {
          m_waitIfsEvent = Simulator::Schedule (GetSifs (), &MacLow::WaitIfsAfterEndTxPacket, this);
        }
      else if (m_currentTxop->IsQosTxop ())
        {
          m_currentTxop->TerminateTxop ();
>>>>>>> origin
        }

      FlushAggregateQueue ();
      m_ampdu = false;
    }
  else if (hdr.IsBlockAck () && hdr.GetAddr1 () == m_self
           && m_txParams.MustWaitBlockAck ()
           && m_blockAckTimeoutEvent.IsRunning ())
    {
      NS_LOG_DEBUG ("got block ack from " << hdr.GetAddr2 ());
      SnrTag tag;
      packet->RemovePacketTag (tag);
      CtrlBAckResponseHeader blockAck;
      packet->RemoveHeader (blockAck);
      m_blockAckTimeoutEvent.Cancel ();
      NotifyAckTimeoutResetNow ();
<<<<<<< HEAD
      m_listener->GotBlockAck (&blockAck, hdr.GetAddr2 (), rxSnr, txVector.GetMode (), tag.Get ());
      m_sentMpdus = 0;
      m_ampdu = false;
      FlushAggregateQueue ();
=======
      m_currentTxop->GotBlockAck (&blockAck, hdr.GetAddr2 (), rxSnr, tag.Get (), m_currentTxVector);
      // start next packet if TXOP remains, otherwise contend for accessing the channel again
      if (m_currentTxop->IsQosTxop () && m_currentTxop->GetTxopLimit ().IsStrictlyPositive ()
          && m_currentTxop->GetTxopRemaining () > GetSifs ())
        {
          m_waitIfsEvent = Simulator::Schedule (GetSifs (), &MacLow::WaitIfsAfterEndTxPacket, this);
        }
      else if (m_currentTxop->IsQosTxop ())
        {
          m_currentTxop->TerminateTxop ();
        }
>>>>>>> origin
    }
  else if (hdr.IsBlockAckReq () && hdr.GetAddr1 () == m_self)
    {
      m_stationManager->ReportRxOk (hdr.GetAddr2 (), rxSnr, txVector.GetMode ());

      CtrlBAckRequestHeader blockAckReq;
      packet->RemoveHeader (blockAckReq);
      if (!blockAckReq.IsMultiTid ())
        {
          uint8_t tid = blockAckReq.GetTidInfo ();
          AgreementsI it = m_bAckAgreements.find (std::make_pair (hdr.GetAddr2 (), tid));
          if (it != m_bAckAgreements.end ())
            {
              //Update block ack cache
              BlockAckCachesI i = m_bAckCaches.find (std::make_pair (hdr.GetAddr2 (), tid));
              NS_ASSERT (i != m_bAckCaches.end ());
              (*i).second.UpdateWithBlockAckReq (blockAckReq.GetStartingSequence ());

              //NS_ASSERT (m_sendAckEvent.IsExpired ());
              m_sendAckEvent.Cancel ();
              /* See section 11.5.3 in IEEE 802.11 for mean of this timer */
              ResetBlockAckInactivityTimerIfNeeded (it->second.first);
              if ((*it).second.first.IsImmediateBlockAck ())
                {
                  NS_LOG_DEBUG ("rx blockAckRequest/sendImmediateBlockAck from=" << hdr.GetAddr2 ());
                  m_sendAckEvent = Simulator::Schedule (GetSifs (),
                                                        &MacLow::SendBlockAckAfterBlockAckRequest, this,
                                                        blockAckReq,
                                                        hdr.GetAddr2 (),
                                                        hdr.GetDuration (),
                                                        txVector.GetMode (),
                                                        rxSnr);
                }
              else
                {
                  NS_FATAL_ERROR ("Delayed block ack not supported.");
                }
            }
          else
            {
              NS_LOG_DEBUG ("There's not a valid agreement for this block ack request.");
            }
        }
      else
        {
          NS_FATAL_ERROR ("Multi-tid block ack is not supported.");
        }
    }
  else if (hdr.IsCtl ())
    {
<<<<<<< HEAD
      NS_LOG_DEBUG ("rx drop " << hdr.GetTypeString ());
=======
      if (hdr.IsCfEnd ())
        {
          NS_LOG_DEBUG ("rx CF-END ");
          m_cfpStart = NanoSeconds (0);
          if (m_cfAckInfo.expectCfAck)
            {
              NS_ASSERT (m_currentTxop != 0);
              if (hdr.IsCfAck ())
                {
                  m_currentTxop->GotAck ();
                }
              else
                {
                  m_currentTxop->MissedAck ();
                }
            }
          if (m_currentTxop != 0)
            {
              m_currentTxop->GotCfEnd ();
            }
          m_cfAckInfo.expectCfAck = false;
        }
      else
        {
          NS_LOG_DEBUG ("rx drop " << hdr.GetTypeString ());
        }
>>>>>>> origin
    }
  else if (hdr.GetAddr1 () == m_self)
    {
      if (hdr.IsCfPoll ())
        {
          m_cfpStart = Simulator::Now ();
          if (m_cfAckInfo.expectCfAck && !hdr.IsCfAck ())
            {
              NS_ASSERT (m_currentTxop != 0);
              Ptr<Txop> txop = m_currentTxop;
              m_currentTxop = 0;
              txop->MissedAck ();
              m_cfAckInfo.expectCfAck = false;
            }
        }
      m_stationManager->ReportRxOk (hdr.GetAddr2 (),
                                    rxSnr, txVector.GetMode ());
      if (hdr.IsQosData () && ReceiveMpdu (mpdu))
        {
          /* From section 9.10.4 in IEEE 802.11:
             Upon the receipt of a QoS data frame from the originator for which
             the block ack agreement exists, the recipient shall buffer the MSDU
             regardless of the value of the Ack Policy subfield within the
             QoS Control field of the QoS data frame. */
          if (hdr.IsQosAck () && !ampduSubframe)
            {
              NS_LOG_DEBUG ("rx QoS unicast/sendAck from=" << hdr.GetAddr2 ());
              AgreementsI it = m_bAckAgreements.find (std::make_pair (hdr.GetAddr2 (), hdr.GetQosTid ()));

              RxCompleteBufferedPacketsWithSmallerSequence (it->second.first.GetStartingSequenceControl (),
                                                            hdr.GetAddr2 (), hdr.GetQosTid ());
              RxCompleteBufferedPacketsUntilFirstLost (hdr.GetAddr2 (), hdr.GetQosTid ());
              NS_ASSERT (m_sendAckEvent.IsExpired ());
              m_sendAckEvent = Simulator::Schedule (GetSifs (),
                                                    &MacLow::SendAckAfterData, this,
                                                    hdr.GetAddr2 (),
                                                    hdr.GetDuration (),
                                                    txVector.GetMode (),
                                                    rxSnr);
            }
          else if (hdr.IsQosBlockAck ())
            {
              AgreementsI it = m_bAckAgreements.find (std::make_pair (hdr.GetAddr2 (), hdr.GetQosTid ()));
              /* See section 11.5.3 in IEEE 802.11 for mean of this timer */
              ResetBlockAckInactivityTimerIfNeeded (it->second.first);
            }
          return;
        }
      else if (hdr.IsQosData () && hdr.IsQosBlockAck ())
        {
          /* This happens if a packet with ack policy Block Ack is received and a block ack
             agreement for that packet doesn't exist.

             From section 11.5.3 in IEEE 802.11e:
             When a recipient does not have an active block ack for a TID, but receives
             data MPDUs with the Ack Policy subfield set to Block Ack, it shall discard
             them and shall send a DELBA frame using the normal access
             mechanisms. */
          AcIndex ac = QosUtilsMapTidToAc (hdr.GetQosTid ());
          m_edca[ac]->SendDelbaFrame (hdr.GetAddr2 (), hdr.GetQosTid (), false);
          return;
        }
      else if (hdr.IsQosData () && hdr.IsQosNoAck ())
        {
          if (ampduSubframe)
            {
              NS_LOG_DEBUG ("rx Ampdu with No Ack Policy from=" << hdr.GetAddr2 ());
            }
          else
            {
              NS_LOG_DEBUG ("rx unicast/noAck from=" << hdr.GetAddr2 ());
            }
        }
      else if (hdr.IsData () || hdr.IsMgt ())
        {
          if (hdr.IsProbeResp ())
            {
              // Apply SNR tag for probe response quality measurements
              SnrTag tag;
              tag.Set (rxSnr);
              packet->AddPacketTag (tag);
<<<<<<< HEAD
=======
              mpdu = Create<WifiMacQueueItem> (packet, hdr);
>>>>>>> origin
            }
          if (hdr.IsMgt () && ampduSubframe)
            {
              NS_FATAL_ERROR ("Received management packet as part of an A-MPDU");
            }
          else
            {
<<<<<<< HEAD
              NS_LOG_DEBUG ("rx unicast/sendAck from=" << hdr.GetAddr2 ());
              NS_ASSERT (m_sendAckEvent.IsExpired ());
              m_sendAckEvent = Simulator::Schedule (GetSifs (),
                                                    &MacLow::SendAckAfterData, this,
                                                    hdr.GetAddr2 (),
                                                    hdr.GetDuration (),
                                                    txVector.GetMode (),
                                                    rxSnr);
=======
              if (IsCfPeriod ())
                {
                  if (hdr.HasData ())
                    {
                      m_cfAckInfo.appendCfAck = true;
                      m_cfAckInfo.address = hdr.GetAddr2 ();
                    }
                }
              else
                {
                  NS_LOG_DEBUG ("rx unicast/sendAck from=" << hdr.GetAddr2 ());
                  NS_ASSERT (m_sendAckEvent.IsExpired ());
                  m_sendAckEvent = Simulator::Schedule (GetSifs (),
                                                        &MacLow::SendAckAfterData, this,
                                                        hdr.GetAddr2 (),
                                                        hdr.GetDuration (),
                                                        txVector.GetMode (),
                                                        rxSnr);
                }
>>>>>>> origin
            }
        }
      goto rxPacket;
    }
  else if (hdr.GetAddr1 ().IsGroup ())
    {
      if (ampduSubframe)
        {
          NS_FATAL_ERROR ("Received group addressed packet as part of an A-MPDU");
        }
      else
        {
          if (hdr.IsData () || hdr.IsMgt ())
            {
              NS_LOG_DEBUG ("rx group from=" << hdr.GetAddr2 ());
              if (hdr.IsBeacon ())
                {
                  // Apply SNR tag for beacon quality measurements
                  SnrTag tag;
                  tag.Set (rxSnr);
                  packet->AddPacketTag (tag);
<<<<<<< HEAD
=======
                  mpdu = Create<WifiMacQueueItem> (packet, hdr);
>>>>>>> origin
                }
              goto rxPacket;
            }
        }
    }
  else if (m_promisc)
    {
      NS_ASSERT (hdr.GetAddr1 () != m_self);
      if (hdr.IsData ())
        {
          goto rxPacket;
        }
    }
  else
    {
      if (m_cfAckInfo.expectCfAck && hdr.IsCfAck ())
        {
          m_cfAckInfo.expectCfAck = false;
          NS_ASSERT (m_currentTxop != 0);
          m_currentTxop->GotAck ();
        }
      NS_LOG_DEBUG ("rx not for me from=" << hdr.GetAddr2 ());
    }
  return;
rxPacket:
  if (m_cfAckInfo.expectCfAck && hdr.IsCfAck ())
    {
      m_cfAckInfo.expectCfAck = false;
      NS_ASSERT (m_currentTxop != 0);
      m_currentTxop->GotAck ();
    }
  m_rxCallback (mpdu);
  return;
}

uint32_t
MacLow::GetCfEndSize (void) const
{
  WifiMacHeader cfEnd;
  if (m_cfAckInfo.expectCfAck || m_cfAckInfo.appendCfAck)
    {
      cfEnd.SetType (WIFI_MAC_CTL_END_ACK);
    }
  else
    {
      cfEnd.SetType (WIFI_MAC_CTL_END);
    }
  return cfEnd.GetSize () + 4;
}

Time
MacLow::GetAckDuration (Mac48Address to, WifiTxVector dataTxVector) const
{
  WifiTxVector ackTxVector = GetAckTxVectorForData (to, dataTxVector.GetMode ());
  return GetAckDuration (ackTxVector);
}

Time
MacLow::GetAckDuration (WifiTxVector ackTxVector) const
{
<<<<<<< HEAD
  NS_ASSERT (ackTxVector.GetMode ().GetModulationClass () != WIFI_MOD_CLASS_HT); //ACK should always use non-HT PPDU (HT PPDU cases not supported yet)
  WifiPreamble preamble;
  if (m_stationManager->GetShortPreambleEnabled ())
    {
      preamble = WIFI_PREAMBLE_SHORT;
    }
  else
    {
      preamble = WIFI_PREAMBLE_LONG;
    }
  return m_phy->CalculateTxDuration (GetAckSize (), ackTxVector, preamble, m_phy->GetFrequency ());
=======
  NS_ASSERT (ackTxVector.GetMode ().GetModulationClass () != WIFI_MOD_CLASS_HT); //Ack should always use non-HT PPDU (HT PPDU cases not supported yet)
  return m_phy->CalculateTxDuration (GetAckSize (), ackTxVector, m_phy->GetPhyBand ());
>>>>>>> origin
}

Time
MacLow::GetBlockAckDuration (WifiTxVector blockAckReqTxVector, BlockAckType type) const
{
  /*
   * For immediate Basic BlockAck we should transmit the frame with the same WifiMode
   * as the BlockAckReq.
   */
<<<<<<< HEAD
  WifiPreamble preamble;
  if (blockAckReqTxVector.GetMode ().GetModulationClass () == WIFI_MOD_CLASS_HT && type == BASIC_BLOCK_ACK)
    {
      preamble = WIFI_PREAMBLE_HT_MF;
    }
  else if (m_stationManager->GetShortPreambleEnabled ())
    {
      preamble = WIFI_PREAMBLE_SHORT;
    }
  else
    {
      preamble = WIFI_PREAMBLE_LONG;
    }
  return m_phy->CalculateTxDuration (GetBlockAckSize (type), blockAckReqTxVector, preamble, m_phy->GetFrequency ());
=======
  return m_phy->CalculateTxDuration (GetBlockAckSize (type), blockAckReqTxVector, m_phy->GetPhyBand ());
}

Time
MacLow::GetBlockAckRequestDuration (WifiTxVector blockAckReqTxVector, BlockAckType type) const
{
  return m_phy->CalculateTxDuration (GetBlockAckRequestSize (type), blockAckReqTxVector, m_phy->GetPhyBand ());
>>>>>>> origin
}

Time
MacLow::GetCtsDuration (Mac48Address to, WifiTxVector rtsTxVector) const
{
  WifiTxVector ctsTxVector = GetCtsTxVectorForRts (to, rtsTxVector.GetMode ());
  return GetCtsDuration (ctsTxVector);
}

Time
MacLow::GetCtsDuration (WifiTxVector ctsTxVector) const
{
  NS_ASSERT (ctsTxVector.GetMode ().GetModulationClass () != WIFI_MOD_CLASS_HT); //CTS should always use non-HT PPDU (HT PPDU cases not supported yet)
<<<<<<< HEAD
  WifiPreamble preamble;
  if (m_stationManager->GetShortPreambleEnabled ())
    {
      preamble = WIFI_PREAMBLE_SHORT;
    }
  else
    {
      preamble = WIFI_PREAMBLE_LONG;
    }
  return m_phy->CalculateTxDuration (GetCtsSize (), ctsTxVector, preamble, m_phy->GetFrequency ());
=======
  return m_phy->CalculateTxDuration (GetCtsSize (), ctsTxVector, m_phy->GetPhyBand ());
>>>>>>> origin
}

WifiTxVector
MacLow::GetRtsTxVector (Ptr<const WifiMacQueueItem> item) const
{
  return m_stationManager->GetRtsTxVector (item->GetHeader ().GetAddr1 ());
}

WifiTxVector
MacLow::GetDataTxVector (Ptr<const WifiMacQueueItem> item) const
{
  return m_stationManager->GetDataTxVector (item->GetHeader ());
}

Time
MacLow::GetResponseDuration (const MacLowTransmissionParameters& params, WifiTxVector dataTxVector,
                             Mac48Address receiver) const
{
  NS_LOG_FUNCTION (this << receiver << dataTxVector << params);

  Time duration = Seconds (0);
  if (params.MustWaitNormalAck ())
    {
      duration += GetSifs ();
      duration += GetAckDuration (receiver, dataTxVector);
    }
  else if (params.MustWaitBlockAck ())
    {
      duration += GetSifs ();
      WifiTxVector blockAckReqTxVector = GetBlockAckTxVector (m_self, dataTxVector.GetMode ());
      duration += GetBlockAckDuration (blockAckReqTxVector, params.GetBlockAckType ());
    }
  else if (params.MustSendBlockAckRequest ())
    {
      duration += 2 * GetSifs ();
      WifiTxVector blockAckReqTxVector = GetBlockAckTxVector (m_self, dataTxVector.GetMode ());
      duration += GetBlockAckRequestDuration (blockAckReqTxVector, params.GetBlockAckRequestType ());
      duration += GetBlockAckDuration (blockAckReqTxVector, params.GetBlockAckRequestType ());
    }
  return duration;
}

WifiMode
MacLow::GetControlAnswerMode (WifiMode reqMode) const
{
  /**
   * The standard has relatively unambiguous rules for selecting a
   * control response rate (the below is quoted from IEEE 802.11-2012,
   * Section 9.7):
   *
   * To allow the transmitting STA to calculate the contents of the
   * Duration/ID field, a STA responding to a received frame shall
   * transmit its Control Response frame (either CTS or Ack), other
   * than the BlockAck control frame, at the highest rate in the
   * BSSBasicRateSet parameter that is less than or equal to the
   * rate of the immediately previous frame in the frame exchange
   * sequence (as defined in Annex G) and that is of the same
   * modulation class (see Section 9.7.8) as the received frame...
   */
  NS_LOG_FUNCTION (this << reqMode);
  WifiMode mode = m_stationManager->GetDefaultMode ();
  bool found = false;
  //First, search the BSS Basic Rate set
  for (uint8_t i = 0; i < m_stationManager->GetNBasicModes (); i++)
    {
      WifiMode testMode = m_stationManager->GetBasicMode (i);
      if ((!found || testMode.IsHigherDataRate (mode))
          && (!testMode.IsHigherDataRate (reqMode))
          && (IsAllowedControlAnswerModulationClass (reqMode.GetModulationClass (), testMode.GetModulationClass ())))
        {
          mode = testMode;
          //We've found a potentially-suitable transmit rate, but we
          //need to continue and consider all the basic rates before
          //we can be sure we've got the right one.
          found = true;
        }
    }
  if (m_stationManager->GetHtSupported ())
    {
      if (!found)
        {
          mode = m_stationManager->GetDefaultMcs ();
          for (uint8_t i = 0; i != m_stationManager->GetNBasicMcs (); i++)
            {
              WifiMode testMode = m_stationManager->GetBasicMcs (i);
              if ((!found || testMode.IsHigherDataRate (mode))
                  && (!testMode.IsHigherDataRate (reqMode))
                  && (testMode.GetModulationClass () == reqMode.GetModulationClass ()))
                {
                  mode = testMode;
                  //We've found a potentially-suitable transmit rate, but we
                  //need to continue and consider all the basic rates before
                  //we can be sure we've got the right one.
                  found = true;
                }
            }
        }
    }
  //If we found a suitable rate in the BSSBasicRateSet, then we are
  //done and can return that mode.
  if (found)
    {
      NS_LOG_DEBUG ("MacLow::GetControlAnswerMode returning " << mode);
      return mode;
    }

  /**
   * If no suitable basic rate was found, we search the mandatory
   * rates. The standard (IEEE 802.11-2007, Section 9.6) says:
   *
   *   ...If no rate contained in the BSSBasicRateSet parameter meets
   *   these conditions, then the control frame sent in response to a
   *   received frame shall be transmitted at the highest mandatory
   *   rate of the PHY that is less than or equal to the rate of the
   *   received frame, and that is of the same modulation class as the
   *   received frame. In addition, the Control Response frame shall
   *   be sent using the same PHY options as the received frame,
   *   unless they conflict with the requirement to use the
   *   BSSBasicRateSet parameter.
   *
   * \todo Note that we're ignoring the last sentence for now, because
   * there is not yet any manipulation here of PHY options.
   */
  for (uint8_t idx = 0; idx < m_phy->GetNModes (); idx++)
    {
      WifiMode thismode = m_phy->GetMode (idx);
      /* If the rate:
       *
       *  - is a mandatory rate for the PHY, and
       *  - is equal to or faster than our current best choice, and
       *  - is less than or equal to the rate of the received frame, and
       *  - is of the same modulation class as the received frame
       *
       * ...then it's our best choice so far.
       */
      if (thismode.IsMandatory ()
          && (!found || thismode.IsHigherDataRate (mode))
          && (!thismode.IsHigherDataRate (reqMode))
          && (IsAllowedControlAnswerModulationClass (reqMode.GetModulationClass (), thismode.GetModulationClass ())))
        {
          mode = thismode;
          //As above; we've found a potentially-suitable transmit
          //rate, but we need to continue and consider all the
          //mandatory rates before we can be sure we've got the right one.
          found = true;
        }
    }
  if (m_stationManager->GetHtSupported () )
    {
      for (uint8_t idx = 0; idx < m_phy->GetNMcs (); idx++)
        {
          WifiMode thismode = m_phy->GetMcs (idx);
          if (thismode.IsMandatory ()
              && (!found || thismode.IsHigherDataRate (mode))
              && (!thismode.IsHigherCodeRate (reqMode))
              && (thismode.GetModulationClass () == reqMode.GetModulationClass ()))
            {
              mode = thismode;
              //As above; we've found a potentially-suitable transmit
              //rate, but we need to continue and consider all the
              //mandatory rates before we can be sure we've got the right one.
              found = true;
            }
        }
    }

<<<<<<< HEAD
WifiTxVector
MacLow::GetDataTxVector (Ptr<const Packet> packet, const WifiMacHeader *hdr) const
{
  Mac48Address to = hdr->GetAddr1 ();
  return m_stationManager->GetDataTxVector (to, hdr, packet);
=======
  /**
   * If we still haven't found a suitable rate for the response then
   * someone has messed up the simulation configuration. This probably means
   * that the WifiPhyStandard is not set correctly, or that a rate that
   * is not supported by the PHY has been explicitly requested.
   *
   * Either way, it is serious - we can either disobey the standard or
   * fail, and I have chosen to do the latter...
   */
  if (!found)
    {
      NS_FATAL_ERROR ("Can't find response rate for " << reqMode);
    }

  NS_LOG_DEBUG ("MacLow::GetControlAnswerMode returning " << mode);
  return mode;
>>>>>>> origin
}

WifiTxVector
MacLow::GetCtsTxVector (Mac48Address to, WifiMode rtsTxMode) const
{
  NS_ASSERT (!to.IsGroup ());
  WifiMode ctsMode = GetControlAnswerMode (rtsTxMode);
  WifiTxVector v;
  v.SetMode (ctsMode);
  v.SetPreambleType (GetPreambleForTransmission (ctsMode.GetModulationClass (), m_stationManager->GetShortPreambleEnabled (), m_stationManager->UseGreenfieldForDestination (to)));
  v.SetTxPowerLevel (m_stationManager->GetDefaultTxPowerLevel ());
  v.SetChannelWidth (GetChannelWidthForTransmission (ctsMode, m_phy->GetChannelWidth ()));
   uint16_t ctsTxGuardInterval = ConvertGuardIntervalToNanoSeconds (ctsMode, DynamicCast<WifiNetDevice> (m_phy->GetDevice ()));
  v.SetGuardInterval (ctsTxGuardInterval);
  v.SetNss (1);
  return v;
}

WifiTxVector
MacLow::GetAckTxVector (Mac48Address to, WifiMode dataTxMode) const
{
  NS_ASSERT (!to.IsGroup ());
  WifiMode ackMode = GetControlAnswerMode (dataTxMode);
  WifiTxVector v;
  v.SetMode (ackMode);
  v.SetPreambleType (GetPreambleForTransmission (ackMode.GetModulationClass (), m_stationManager->GetShortPreambleEnabled (), m_stationManager->UseGreenfieldForDestination (to)));
  v.SetTxPowerLevel (m_stationManager->GetDefaultTxPowerLevel ());
  v.SetChannelWidth (GetChannelWidthForTransmission (ackMode, m_phy->GetChannelWidth ()));
   uint16_t ackTxGuardInterval = ConvertGuardIntervalToNanoSeconds (ackMode, DynamicCast<WifiNetDevice> (m_phy->GetDevice ()));
  v.SetGuardInterval (ackTxGuardInterval);
  v.SetNss (1);
  return v;
}

WifiTxVector
MacLow::GetBlockAckTxVector (Mac48Address to, WifiMode dataTxMode) const
{
  NS_ASSERT (!to.IsGroup ());
  WifiMode blockAckMode = GetControlAnswerMode (dataTxMode);
  WifiTxVector v;
  v.SetMode (blockAckMode);
  v.SetPreambleType (GetPreambleForTransmission (blockAckMode.GetModulationClass (), m_stationManager->GetShortPreambleEnabled (), m_stationManager->UseGreenfieldForDestination (to)));
  v.SetTxPowerLevel (m_stationManager->GetDefaultTxPowerLevel ());
  v.SetChannelWidth (GetChannelWidthForTransmission (blockAckMode, m_phy->GetChannelWidth ()));
uint16_t blockAckTxGuardInterval = ConvertGuardIntervalToNanoSeconds (blockAckMode, DynamicCast<WifiNetDevice> (m_phy->GetDevice ()));
  v.SetGuardInterval (blockAckTxGuardInterval);
  v.SetNss (1);
  return v;
}

WifiTxVector
MacLow::GetCtsTxVectorForRts (Mac48Address to, WifiMode rtsTxMode) const
{
  return GetCtsTxVector (to, rtsTxMode);
}

WifiTxVector
MacLow::GetAckTxVectorForData (Mac48Address to, WifiMode dataTxMode) const
{
  return GetAckTxVector (to, dataTxMode);
}

Time
MacLow::CalculateOverallTxTime (Ptr<const Packet> packet,
                                const WifiMacHeader* hdr,
                                const MacLowTransmissionParameters& params,
                                uint32_t fragmentSize) const
{
  Ptr<const WifiMacQueueItem> item = Create<const WifiMacQueueItem> (packet, *hdr);
  Time txTime = CalculateOverheadTxTime (item, params);
  uint32_t dataSize;
  if (fragmentSize > 0)
    {
<<<<<<< HEAD
      WifiTxVector rtsTxVector = GetRtsTxVector (packet, hdr);
      //standard says RTS packets can have GF format sec 9.6.0e.1 page 110 bullet b 2
      if (m_phy->GetGreenfield () && m_stationManager->GetGreenfieldSupported (m_currentHdr.GetAddr1 ()))
        {
          preamble = WIFI_PREAMBLE_HT_GF;
        }
      //Otherwise, RTS should always use non-HT PPDU (HT PPDU cases not supported yet)
      else if (m_stationManager->GetShortPreambleEnabled ())
        {
          preamble = WIFI_PREAMBLE_SHORT;
        }
      else
        {
          preamble = WIFI_PREAMBLE_LONG;
        }
      txTime += m_phy->CalculateTxDuration (GetRtsSize (), rtsTxVector, preamble, m_phy->GetFrequency ());
      txTime += GetCtsDuration (hdr->GetAddr1 (), rtsTxVector);
      txTime += Time (GetSifs () * 2);
    }
  WifiTxVector dataTxVector = GetDataTxVector (packet, hdr);
  if (dataTxVector.GetMode ().GetModulationClass () == WIFI_MOD_CLASS_VHT)
    {
      preamble = WIFI_PREAMBLE_VHT;
    }
  else if (m_phy->GetGreenfield () && m_stationManager->GetGreenfieldSupported (m_currentHdr.GetAddr1 ()))
    {
      preamble = WIFI_PREAMBLE_HT_GF;
    }
  else if (dataTxVector.GetMode ().GetModulationClass () == WIFI_MOD_CLASS_HT)
    {
      preamble = WIFI_PREAMBLE_HT_MF;
=======
      Ptr<const Packet> fragment = Create<Packet> (fragmentSize);
      dataSize = GetSize (fragment, hdr, m_currentPacket && m_currentPacket->IsAggregate ());
>>>>>>> origin
    }
  else if (m_stationManager->GetShortPreambleEnabled ())
    {
      preamble = WIFI_PREAMBLE_SHORT;
    }
  else
    {
      dataSize = GetSize (packet, hdr, m_currentPacket && m_currentPacket->IsAggregate ());
    }
<<<<<<< HEAD
  uint32_t dataSize = GetSize (packet, hdr);
  txTime += m_phy->CalculateTxDuration (dataSize, dataTxVector, preamble, m_phy->GetFrequency ());
  if (params.MustWaitAck ())
=======
  txTime += m_phy->CalculateTxDuration (dataSize, GetDataTxVector (item), m_phy->GetPhyBand ());
  return txTime;
}

Time
MacLow::CalculateOverheadTxTime (Ptr<const WifiMacQueueItem> item,
                                 const MacLowTransmissionParameters& params) const
{
  Time txTime = Seconds (0);
  if (params.MustSendRts ())
>>>>>>> origin
    {
      WifiTxVector rtsTxVector = GetRtsTxVector (item);
      txTime += m_phy->CalculateTxDuration (GetRtsSize (), rtsTxVector, m_phy->GetPhyBand ());
      txTime += GetCtsDuration (item->GetHeader ().GetAddr1 (), rtsTxVector);
      txTime += Time (GetSifs () * 2);
    }
  txTime += GetResponseDuration (params, GetDataTxVector (item), item->GetHeader ().GetAddr1 ());

  return txTime;
}

Time
MacLow::CalculateTransmissionTime (Ptr<const Packet> packet,
                                   const WifiMacHeader* hdr,
                                   const MacLowTransmissionParameters& params) const
{
  Time txTime = CalculateOverallTxTime (packet, hdr, params);
  if (params.HasNextPacket ())
    {
<<<<<<< HEAD
      WifiTxVector dataTxVector = GetDataTxVector (packet, hdr);
      WifiPreamble preamble;
      if (dataTxVector.GetMode ().GetModulationClass () == WIFI_MOD_CLASS_HT)
        {
          preamble = WIFI_PREAMBLE_VHT;
        }
      if (m_phy->GetGreenfield () && m_stationManager->GetGreenfieldSupported (m_currentHdr.GetAddr1 ()))
        {
          preamble = WIFI_PREAMBLE_HT_GF;
        }
      else if (dataTxVector.GetMode ().GetModulationClass () == WIFI_MOD_CLASS_HT)
        {
          preamble = WIFI_PREAMBLE_HT_MF;
        }
      else if (m_stationManager->GetShortPreambleEnabled ())
        {
          preamble = WIFI_PREAMBLE_SHORT;
        }
      else
        {
          preamble = WIFI_PREAMBLE_LONG;
        }
      txTime += GetSifs ();
      txTime += m_phy->CalculateTxDuration (params.GetNextPacketSize (), dataTxVector, preamble, m_phy->GetFrequency ());
=======
      WifiTxVector dataTxVector = GetDataTxVector (Create<const WifiMacQueueItem> (packet, *hdr));
      txTime += GetSifs ();
      txTime += m_phy->CalculateTxDuration (params.GetNextPacketSize (), dataTxVector, m_phy->GetPhyBand ());
>>>>>>> origin
    }
  return txTime;
}

void
MacLow::NotifyNav (Ptr<const Packet> packet, const WifiMacHeader &hdr)
{
  NS_ASSERT (m_lastNavStart <= Simulator::Now ());
  if (hdr.GetRawDuration () > 32767)
    {
      //All stations process Duration field values less than or equal to 32 767 from valid data frames
      //to update their NAV settings as appropriate under the coordination function rules.
      return;
    }
  if (hdr.IsCfEnd () && hdr.GetAddr2 () == m_bssid)
    {
      //see section 9.3.2.2 802.11-1999
      DoNavResetNow (Seconds (0));
      return;
    }
  else if (hdr.GetAddr1 () != m_self)
    {
      // see section 9.2.5.4 802.11-1999
      Time duration = hdr.GetDuration ();
      bool navUpdated = DoNavStartNow (duration);
      if (hdr.IsRts () && navUpdated)
        {
          /**
           * A STA that used information from an RTS frame as the most recent basis to update its NAV setting
           * is permitted to reset its NAV if no PHY-RXSTART.indication is detected from the PHY during a
           * period with a duration of (2 * aSIFSTime) + (CTS_Time) + aRxPHYStartDelay + (2 * aSlotTime)
           * starting at the PHY-RXEND.indication corresponding to the detection of the RTS frame. The
           * “CTS_Time” shall be calculated using the length of the CTS frame and the data rate at which
           * the RTS frame used for the most recent NAV update was received.
           */
          WifiMacHeader cts;
          cts.SetType (WIFI_MAC_CTL_CTS);
          WifiTxVector txVector = GetRtsTxVector (Create<const WifiMacQueueItem> (packet, hdr));
          Time navCounterResetCtsMissedDelay =
<<<<<<< HEAD
            m_phy->CalculateTxDuration (cts.GetSerializedSize (), txVector, preamble, m_phy->GetFrequency ()) +
            Time (2 * GetSifs ()) + Time (2 * GetSlotTime ());
=======
            m_phy->CalculateTxDuration (cts.GetSerializedSize (), txVector, m_phy->GetPhyBand ()) +
            Time (2 * GetSifs ()) + Time (2 * GetSlotTime ()) +
            m_phy->CalculatePhyPreambleAndHeaderDuration (txVector);
>>>>>>> origin
          m_navCounterResetCtsMissed = Simulator::Schedule (navCounterResetCtsMissedDelay,
                                                            &MacLow::DoNavResetNow, this,
                                                            Seconds (0));
        }
    }
}

void
MacLow::DoNavResetNow (Time duration)
{
  NS_LOG_FUNCTION (this << duration);
  for (ChannelAccessManagersCI i = m_channelAccessManagers.begin (); i != m_channelAccessManagers.end (); i++)
    {
      (*i)->NotifyNavResetNow (duration);
    }
  m_lastNavStart = Simulator::Now ();
  m_lastNavDuration = duration;
}

bool
MacLow::DoNavStartNow (Time duration)
{
  for (ChannelAccessManagersCI i = m_channelAccessManagers.begin (); i != m_channelAccessManagers.end (); i++)
    {
      (*i)->NotifyNavStartNow (duration);
    }
  Time newNavEnd = Simulator::Now () + duration;
  Time oldNavEnd = m_lastNavStart + m_lastNavDuration;
  if (newNavEnd > oldNavEnd)
    {
      m_lastNavStart = Simulator::Now ();
      m_lastNavDuration = duration;
      return true;
    }
  return false;
}

void
MacLow::NotifyAckTimeoutStartNow (Time duration)
{
  for (ChannelAccessManagersCI i = m_channelAccessManagers.begin (); i != m_channelAccessManagers.end (); i++)
    {
      (*i)->NotifyAckTimeoutStartNow (duration);
    }
}

void
MacLow::NotifyAckTimeoutResetNow (void)
{
  for (ChannelAccessManagersCI i = m_channelAccessManagers.begin (); i != m_channelAccessManagers.end (); i++)
    {
      (*i)->NotifyAckTimeoutResetNow ();
    }
}

void
MacLow::NotifyCtsTimeoutStartNow (Time duration)
{
  for (ChannelAccessManagersCI i = m_channelAccessManagers.begin (); i != m_channelAccessManagers.end (); i++)
    {
      (*i)->NotifyCtsTimeoutStartNow (duration);
    }
}

void
MacLow::NotifyCtsTimeoutResetNow (void)
{
  for (ChannelAccessManagersCI i = m_channelAccessManagers.begin (); i != m_channelAccessManagers.end (); i++)
    {
      (*i)->NotifyCtsTimeoutResetNow ();
    }
}

void
MacLow::ForwardDown (Ptr<const WifiPsdu> psdu, WifiTxVector txVector)
{
  NS_LOG_FUNCTION (this << psdu << txVector);

  NS_ASSERT (psdu->GetNMpdus ());
  const WifiMacHeader& hdr = (*psdu->begin ())->GetHeader ();

  NS_LOG_DEBUG ("send " << hdr.GetTypeString () <<
                ", to=" << hdr.GetAddr1 () <<
                ", size=" << psdu->GetSize () <<
                ", mode=" << txVector.GetMode  () <<
<<<<<<< HEAD
                ", duration=" << hdr->GetDuration () <<
                ", seq=0x" << std::hex << m_currentHdr.GetSequenceControl () << std::dec);
  if (!m_ampdu || hdr->IsRts () || hdr->IsBlockAck ())
    {
      m_phy->SendPacket (packet, txVector, preamble);
    }
  else
    {
      Ptr<Packet> newPacket;
      Ptr <const Packet> dequeuedPacket;
      WifiMacHeader newHdr;
      WifiMacTrailer fcs;
      m_nTxMpdus = m_aggregateQueue->GetSize ();
      uint32_t queueSize = m_aggregateQueue->GetSize ();
      bool vhtSingleMpdu = false;
      bool last = false;
      enum mpduType mpdutype = NORMAL_MPDU;
      
      uint8_t tid = GetTid (packet, *hdr);
      AcIndex ac = QosUtilsMapTidToAc (tid);
      std::map<AcIndex, MacLowAggregationCapableTransmissionListener*>::const_iterator listenerIt = m_edcaListeners.find (ac);

      if (queueSize == 1)
        {
          vhtSingleMpdu = true;
        }

      //Add packet tag
      AmpduTag ampdutag;
      ampdutag.SetAmpdu (true);
      Time delay = Seconds (0);
      Time remainingAmpduDuration = m_phy->CalculateTxDuration (packet->GetSize (), txVector, preamble, m_phy->GetFrequency ());
      if (queueSize > 1 || vhtSingleMpdu)
        {
          txVector.SetAggregation (true);
        }
      for (; queueSize > 0; queueSize--)
        {
          dequeuedPacket = m_aggregateQueue->Dequeue (&newHdr);
          newPacket = dequeuedPacket->Copy ();
          newHdr.SetDuration (hdr->GetDuration ());
          newPacket->AddHeader (newHdr);
          newPacket->AddTrailer (fcs);
          if (queueSize == 1)
            {
              last = true;
              mpdutype = LAST_MPDU_IN_AGGREGATE;
            }

          listenerIt->second->GetMpduAggregator ()->AddHeaderAndPad (newPacket, last, vhtSingleMpdu);
          
          if (delay == Seconds (0))
            {
              if (!vhtSingleMpdu)
                {
                  NS_LOG_DEBUG ("Sending MPDU as part of A-MPDU");
                  mpdutype = MPDU_IN_AGGREGATE;
                }
              else
                {
                  mpdutype = NORMAL_MPDU;
                }
            }
          
          Time mpduDuration = m_phy->CalculateTxDuration (newPacket->GetSize (), txVector, preamble, m_phy->GetFrequency (), mpdutype, 0);
          remainingAmpduDuration -= mpduDuration;

          ampdutag.SetRemainingNbOfMpdus (queueSize - 1);
          if (queueSize > 1)
            {
              ampdutag.SetRemainingAmpduDuration (remainingAmpduDuration);
            }
          else
            {
              ampdutag.SetRemainingAmpduDuration (NanoSeconds (0));
            }
          newPacket->AddPacketTag (ampdutag);

          if (delay == Seconds (0))
            {
              m_phy->SendPacket (newPacket, txVector, preamble, mpdutype);
            }
          else
            {
              Simulator::Schedule (delay, &MacLow::SendMpdu, this, newPacket, txVector, preamble, mpdutype);
            }
          if (queueSize > 1)
            {
              NS_ASSERT (remainingAmpduDuration > 0);
              delay = delay + mpduDuration;
            }

          preamble = WIFI_PREAMBLE_NONE;
        }
=======
                ", preamble=" << txVector.GetPreambleType () <<
                ", duration=" << hdr.GetDuration () <<
                ", seq=0x" << std::hex << hdr.GetSequenceControl () << std::dec);

  if (hdr.IsCfPoll () && m_stationManager->GetPcfSupported ())
    {
      Simulator::Schedule (GetPifs () + m_phy->CalculateTxDuration (psdu->GetSize (), txVector, m_phy->GetPhyBand ()), &MacLow::CfPollTimeout, this);
    }
  if (hdr.IsBeacon () && m_stationManager->GetPcfSupported ())
    {
      if (Simulator::Now () > m_lastBeacon + m_beaconInterval)
        {
          m_cfpForeshortening = (Simulator::Now () - m_lastBeacon - m_beaconInterval);
        }
      m_lastBeacon = Simulator::Now ();
    }
  else if (hdr.IsCfEnd () && m_stationManager->GetPcfSupported ())
    {
      m_cfpStart = NanoSeconds (0);
      m_cfpForeshortening = NanoSeconds (0);
      m_cfAckInfo.appendCfAck = false;
      m_cfAckInfo.expectCfAck = false;
    }
  else if (IsCfPeriod () && hdr.HasData ())
    {
      m_cfAckInfo.expectCfAck = true;
    }

  if (psdu->IsSingle ())
    {
      txVector.SetAggregation (true);
      NS_LOG_DEBUG ("Sending S-MPDU");
    }
  else if (psdu->IsAggregate ())
    {
      txVector.SetAggregation (true);
      NS_LOG_DEBUG ("Sending A-MPDU");
    }
  else
    {
      NS_LOG_DEBUG ("Sending non aggregate MPDU");
>>>>>>> origin
    }

  for (auto& mpdu : *PeekPointer (psdu))
    {
      if (mpdu->GetHeader ().IsQosData ())
        {
          auto edcaIt = m_edca.find (QosUtilsMapTidToAc (mpdu->GetHeader ().GetQosTid ()));
          edcaIt->second->CompleteMpduTx (mpdu);
        }
    }
  m_phy->Send (psdu, txVector);
}

void
<<<<<<< HEAD
MacLow::SendMpdu (Ptr<const Packet> packet, WifiTxVector txVector, WifiPreamble preamble, enum mpduType mpdutype)
{
  NS_LOG_DEBUG ("Sending MPDU as part of A-MPDU");
  m_phy->SendPacket (packet, txVector, preamble, mpdutype);
=======
MacLow::CfPollTimeout (void)
{
  NS_LOG_FUNCTION (this);
  //to be reworked
  bool busy = false;
  for (ChannelAccessManagersCI i = m_channelAccessManagers.begin (); i != m_channelAccessManagers.end (); i++)
    {
      busy = (*i)->IsBusy ();
    }
  if (!busy)
    {
      NS_ASSERT (m_currentTxop != 0);
      m_currentTxop->MissedCfPollResponse (m_cfAckInfo.expectCfAck);
      m_cfAckInfo.expectCfAck = false;
    }
>>>>>>> origin
}

void
MacLow::CtsTimeout (void)
{
  NS_LOG_FUNCTION (this);
  NS_LOG_DEBUG ("cts timeout");
  /// \todo should check that there was no RX start before now.
  /// we should restart a new CTS timeout now until the expected
  /// end of RX if there was a RX start before now.
  m_stationManager->ReportRtsFailed (m_currentPacket->GetAddr1 (), &m_currentPacket->GetHeader (0));

  Ptr<QosTxop> qosTxop = DynamicCast<QosTxop> (m_currentTxop);
  if (qosTxop != 0)
    {
      qosTxop->NotifyMissedCts (std::list<Ptr<WifiMacQueueItem>> (m_currentPacket->begin (), m_currentPacket->end ()));
    }
  else
    {
      m_currentTxop->MissedCts ();
    }
  m_currentTxop = 0;
}

void
MacLow::NormalAckTimeout (void)
{
  NS_LOG_FUNCTION (this);
  NS_LOG_DEBUG ("normal ack timeout");
  /// \todo should check that there was no RX start before now.
  /// we should restart a new ack timeout now until the expected
  /// end of RX if there was a RX start before now.
  Ptr<Txop> txop = m_currentTxop;
  m_currentTxop = 0;
  txop->MissedAck ();
}

void
MacLow::BlockAckTimeout (void)
{
  NS_LOG_FUNCTION (this);
  NS_LOG_DEBUG ("block ack timeout");
<<<<<<< HEAD
  MacLowTransmissionListener *listener = m_listener;
  m_listener = 0;
  m_sentMpdus = 0;
  m_ampdu = false;
  FlushAggregateQueue ();
  listener->MissedBlockAck (m_nTxMpdus);
}

void
MacLow::SuperFastAckTimeout ()
{
  NS_LOG_FUNCTION (this);
  m_stationManager->ReportDataFailed (m_currentHdr.GetAddr1 (), &m_currentHdr);
  MacLowTransmissionListener *listener = m_listener;
  m_listener = 0;
  if (m_phy->IsStateIdle ())
    {
      NS_LOG_DEBUG ("super fast Ack failed");
      listener->MissedAck ();
    }
  else
    {
      NS_LOG_DEBUG ("super fast Ack ok");
      listener->GotAck (0.0, WifiMode ());
    }
=======
  Ptr<Txop> txop = m_currentTxop;
  m_currentTxop = 0;
  txop->MissedBlockAck (m_currentPacket->GetNMpdus ());
>>>>>>> origin
}

void
MacLow::SendRtsForPacket (void)
{
  NS_LOG_FUNCTION (this);
  /* send an RTS for this packet. */
  WifiMacHeader rts;
  rts.SetType (WIFI_MAC_CTL_RTS);
  rts.SetDsNotFrom ();
  rts.SetDsNotTo ();
  rts.SetNoRetry ();
  rts.SetNoMoreFragments ();
  rts.SetAddr1 (m_currentPacket->GetAddr1 ());
  rts.SetAddr2 (m_self);
  WifiTxVector rtsTxVector = GetRtsTxVector (*m_currentPacket->begin ());
  Time duration = Seconds (0);

  duration += GetSifs ();
  duration += GetCtsDuration (m_currentPacket->GetAddr1 (), rtsTxVector);
  duration += GetSifs ();
  duration += m_phy->CalculateTxDuration (m_currentPacket->GetSize (),
                                          m_currentTxVector, m_phy->GetPhyBand ());
  duration += GetResponseDuration (m_txParams, m_currentTxVector, m_currentPacket->GetAddr1 ());
  if (m_txParams.HasNextPacket ())
    {
<<<<<<< HEAD
      preamble = WIFI_PREAMBLE_HT_GF;
    }
  //Otherwise, RTS should always use non-HT PPDU (HT PPDU cases not supported yet)
  else if (m_stationManager->GetShortPreambleEnabled ())
    {
      preamble = WIFI_PREAMBLE_SHORT;
    }
  else
    {
      preamble = WIFI_PREAMBLE_LONG;
    }

  if (m_txParams.HasDurationId ())
    {
      duration += m_txParams.GetDurationId ();
    }
  else
    {
      duration += GetSifs ();
      duration += GetCtsDuration (m_currentHdr.GetAddr1 (), rtsTxVector);
      duration += GetSifs ();
      duration += m_phy->CalculateTxDuration (GetSize (m_currentPacket, &m_currentHdr),
                                              m_currentTxVector, preamble, m_phy->GetFrequency ());
      duration += GetSifs ();
      if (m_txParams.MustWaitBasicBlockAck ())
        {
          WifiTxVector blockAckReqTxVector = GetBlockAckTxVector (m_currentHdr.GetAddr2 (), m_currentTxVector.GetMode ());
          duration += GetBlockAckDuration (m_currentHdr.GetAddr1 (), blockAckReqTxVector, BASIC_BLOCK_ACK);
        }
      else if (m_txParams.MustWaitCompressedBlockAck ())
        {
          WifiTxVector blockAckReqTxVector = GetBlockAckTxVector (m_currentHdr.GetAddr2 (), m_currentTxVector.GetMode ());
          duration += GetBlockAckDuration (m_currentHdr.GetAddr1 (), blockAckReqTxVector, COMPRESSED_BLOCK_ACK);
        }
      else if (m_txParams.MustWaitAck ())
        {
          duration += GetAckDuration (m_currentHdr.GetAddr1 (), m_currentTxVector);
        }
      if (m_txParams.HasNextPacket ())
        {
          duration += m_phy->CalculateTxDuration (m_txParams.GetNextPacketSize (),
                                                  m_currentTxVector, preamble, m_phy->GetFrequency ());
          if (m_txParams.MustWaitAck ())
            {
              duration += GetSifs ();
              duration += GetAckDuration (m_currentHdr.GetAddr1 (), m_currentTxVector);
            }
        }
    }
  rts.SetDuration (duration);

  Time txDuration = m_phy->CalculateTxDuration (GetRtsSize (), rtsTxVector, preamble, m_phy->GetFrequency ());
  Time timerDelay = txDuration + GetCtsTimeout ();

=======
      duration += m_phy->CalculateTxDuration (m_txParams.GetNextPacketSize (),
                                              m_currentTxVector, m_phy->GetPhyBand ());
      duration += GetResponseDuration (m_txParams, m_currentTxVector, m_currentPacket->GetAddr1 ());
    }
  rts.SetDuration (duration);

  Time txDuration = m_phy->CalculateTxDuration (GetRtsSize (), rtsTxVector, m_phy->GetPhyBand ());
  // After transmitting an RTS frame, the STA shall wait for a CTSTimeout interval with
  // a value of aSIFSTime + aSlotTime + aRxPHYStartDelay (IEEE 802.11-2016 sec. 10.3.2.7).
  // aRxPHYStartDelay equals the time to transmit the PHY header.
  Time timerDelay = txDuration + GetSifs () + GetSlotTime ()
                    + m_phy->CalculatePhyPreambleAndHeaderDuration (rtsTxVector);
>>>>>>> origin
  NS_ASSERT (m_ctsTimeoutEvent.IsExpired ());
  NotifyCtsTimeoutStartNow (timerDelay);
  m_ctsTimeoutEvent = Simulator::Schedule (timerDelay, &MacLow::CtsTimeout, this);

<<<<<<< HEAD
  Ptr<Packet> packet = Create<Packet> ();
  packet->AddHeader (rts);
  WifiMacTrailer fcs;
  packet->AddTrailer (fcs);

  ForwardDown (packet, &rts, rtsTxVector, preamble);
=======
  ForwardDown (Create<const WifiPsdu> (Create<Packet> (), rts), rtsTxVector);
>>>>>>> origin
}

void
MacLow::StartDataTxTimers (WifiTxVector dataTxVector)
{
  Time txDuration = m_phy->CalculateTxDuration (m_currentPacket->GetSize (), dataTxVector, m_phy->GetPhyBand ());
  if (m_txParams.MustWaitNormalAck () && !IsCfPeriod ())
    {
<<<<<<< HEAD
      preamble = WIFI_PREAMBLE_VHT;
    }
  //Since it is data then it can have format = GF
  else if (m_phy->GetGreenfield () && m_stationManager->GetGreenfieldSupported (m_currentHdr.GetAddr1 ()))
    {
      preamble = WIFI_PREAMBLE_HT_GF;
    }
  else if (dataTxVector.GetMode ().GetModulationClass () == WIFI_MOD_CLASS_HT)
    {
      preamble = WIFI_PREAMBLE_HT_MF;
    }
  else if (m_stationManager->GetShortPreambleEnabled ())
    {
      preamble = WIFI_PREAMBLE_SHORT;
    }
  else
    {
      preamble = WIFI_PREAMBLE_LONG;
    }

  Time txDuration = m_phy->CalculateTxDuration (GetSize (m_currentPacket, &m_currentHdr), dataTxVector, preamble, m_phy->GetFrequency ());
  if (m_txParams.MustWaitNormalAck ())
    {
      Time timerDelay = txDuration + GetAckTimeout ();
=======
      // the timeout duration is "aSIFSTime + aSlotTime + aRxPHYStartDelay, starting
      // at the PHY-TXEND.confirm primitive" (section 10.3.2.9 or 10.22.2.2 of 802.11-2016).
      // aRxPHYStartDelay equals the time to transmit the PHY header.
      WifiTxVector ackTxVector = GetAckTxVector (m_currentPacket->GetAddr1 (),
                                                 dataTxVector.GetMode ());
      Time timerDelay = txDuration + GetSifs () + GetSlotTime ()
                        + m_phy->CalculatePhyPreambleAndHeaderDuration (ackTxVector);
>>>>>>> origin
      NS_ASSERT (m_normalAckTimeoutEvent.IsExpired ());
      NotifyAckTimeoutStartNow (timerDelay);
      m_normalAckTimeoutEvent = Simulator::Schedule (timerDelay, &MacLow::NormalAckTimeout, this);
    }
  else if (m_txParams.MustWaitBlockAck ())
    {
      // the timeout duration is "aSIFSTime + aSlotTime + aRxPHYStartDelay, starting
      // at the PHY-TXEND.confirm primitive" (section 10.3.2.9 or 10.22.2.2 of 802.11-2016).
      // aRxPHYStartDelay equals the time to transmit the PHY header.
      WifiTxVector blockAckTxVector = GetBlockAckTxVector (m_currentPacket->GetAddr1 (),
                                                           dataTxVector.GetMode ());
      Time timerDelay = txDuration + GetSifs () + GetSlotTime ()
                        + m_phy->CalculatePhyPreambleAndHeaderDuration (blockAckTxVector);
      NS_ASSERT (m_blockAckTimeoutEvent.IsExpired ());
      NotifyAckTimeoutStartNow (timerDelay);
      m_blockAckTimeoutEvent = Simulator::Schedule (timerDelay, &MacLow::BlockAckTimeout, this);
    }
  else if (m_txParams.HasNextPacket ())
    {
<<<<<<< HEAD
      if (m_stationManager->HasHtSupported ())
        {
          Time delay = txDuration + GetRifs ();
          NS_ASSERT (m_waitRifsEvent.IsExpired ());
          m_waitRifsEvent = Simulator::Schedule (delay, &MacLow::WaitSifsAfterEndTxFragment, this);
        }
      else
        {
          Time delay = txDuration + GetSifs ();
          NS_ASSERT (m_waitSifsEvent.IsExpired ());
          m_waitSifsEvent = Simulator::Schedule (delay, &MacLow::WaitSifsAfterEndTxFragment, this);
        }
=======
      NS_ASSERT (m_waitIfsEvent.IsExpired ());
      Time delay = txDuration + GetSifs ();
      m_waitIfsEvent = Simulator::Schedule (delay, &MacLow::WaitIfsAfterEndTxFragment, this);
    }
  else if (m_currentPacket->GetHeader (0).IsQosData () && m_currentTxop->IsQosTxop () &&
           m_currentTxop->GetTxopLimit ().IsStrictlyPositive () && m_currentTxop->GetTxopRemaining () > GetSifs ())
   {
      Time delay = txDuration + GetSifs ();
      m_waitIfsEvent = Simulator::Schedule (delay, &MacLow::WaitIfsAfterEndTxPacket, this);
>>>>>>> origin
    }
  else
    {
      // since we do not expect any timer to be triggered.
      m_endTxNoAckEvent = Simulator::Schedule (txDuration, &MacLow::EndTxNoAck, this);
    }
}

void
MacLow::SendDataPacket (void)
{
  NS_LOG_FUNCTION (this);
  /* send this packet directly. No RTS is needed. */
<<<<<<< HEAD
  WifiPreamble preamble;
  if (m_currentTxVector.GetMode ().GetModulationClass () == WIFI_MOD_CLASS_VHT)
    {
      preamble = WIFI_PREAMBLE_VHT;
    }
  else if (m_phy->GetGreenfield () && m_stationManager->GetGreenfieldSupported (m_currentHdr.GetAddr1 ()))
    {
      //In the future has to make sure that receiver has greenfield enabled
      preamble = WIFI_PREAMBLE_HT_GF;
    }
  else if (m_currentTxVector.GetMode ().GetModulationClass () == WIFI_MOD_CLASS_HT)
    {
      preamble = WIFI_PREAMBLE_HT_MF;
    }
  else if (m_stationManager->GetShortPreambleEnabled ())
    {
      preamble = WIFI_PREAMBLE_SHORT;
    }
  else
    {
      preamble = WIFI_PREAMBLE_LONG;
    }

  StartDataTxTimers (m_currentTxVector);

  Time duration = Seconds (0.0);
  if (m_txParams.HasDurationId ())
    {
      duration += m_txParams.GetDurationId ();
    }
  else
    {
      if (m_txParams.MustWaitBasicBlockAck ())
        {
          duration += GetSifs ();
          WifiTxVector blockAckReqTxVector = GetBlockAckTxVector (m_currentHdr.GetAddr2 (), m_currentTxVector.GetMode ());
          duration += GetBlockAckDuration (m_currentHdr.GetAddr1 (), blockAckReqTxVector, BASIC_BLOCK_ACK);
        }
      else if (m_txParams.MustWaitCompressedBlockAck ())
        {
          duration += GetSifs ();
          WifiTxVector blockAckReqTxVector = GetBlockAckTxVector (m_currentHdr.GetAddr2 (), m_currentTxVector.GetMode ());
          duration += GetBlockAckDuration (m_currentHdr.GetAddr1 (), blockAckReqTxVector, COMPRESSED_BLOCK_ACK);
        }
      else if (m_txParams.MustWaitAck ())
        {
          duration += GetSifs ();
          duration += GetAckDuration (m_currentHdr.GetAddr1 (), m_currentTxVector);
        }
=======
  StartDataTxTimers (m_currentTxVector);

  if (!IsCfPeriod ())
    {
      Time duration = GetResponseDuration (m_txParams, m_currentTxVector, m_currentPacket->GetAddr1 ());
>>>>>>> origin
      if (m_txParams.HasNextPacket ())
        {
          duration += GetSifs ();
          duration += m_phy->CalculateTxDuration (m_txParams.GetNextPacketSize (),
<<<<<<< HEAD
                                                  m_currentTxVector, preamble, m_phy->GetFrequency ());
          if (m_txParams.MustWaitAck ())
            {
              duration += GetSifs ();
              duration += GetAckDuration (m_currentHdr.GetAddr1 (), m_currentTxVector);
            }
=======
                                                  m_currentTxVector, m_phy->GetPhyBand ());
          duration += GetResponseDuration (m_txParams, m_currentTxVector, m_currentPacket->GetAddr1 ());
        }
      m_currentPacket->SetDuration (duration);
    }
  else
    {
      if (m_currentPacket->GetHeader (0).IsCfEnd ())
        {
          m_currentPacket->GetHeader (0).SetRawDuration (0);
        }
      else
        {
          m_currentPacket->GetHeader (0).SetRawDuration (32768);
>>>>>>> origin
        }
    }

  if (!m_currentPacket->IsAggregate ())
    {
      if (m_cfAckInfo.appendCfAck)
        {
          switch (m_currentPacket->GetHeader (0).GetType ())
            {
            case WIFI_MAC_DATA:
              m_currentPacket->GetHeader (0).SetType (WIFI_MAC_DATA_CFACK, false);
              break;
            case WIFI_MAC_DATA_CFPOLL:
              m_currentPacket->GetHeader (0).SetType (WIFI_MAC_DATA_CFACK_CFPOLL, false);
              break;
            case WIFI_MAC_DATA_NULL:
              m_currentPacket->GetHeader (0).SetType (WIFI_MAC_DATA_NULL_CFACK, false);
              break;
            case WIFI_MAC_DATA_NULL_CFPOLL:
              m_currentPacket->GetHeader (0).SetType (WIFI_MAC_DATA_NULL_CFACK_CFPOLL, false);
              break;
            case WIFI_MAC_CTL_END:
              m_currentPacket->GetHeader (0).SetType (WIFI_MAC_CTL_END_ACK, false);
              break;
            default:
              NS_ASSERT (false);
              break;
            }
          NS_ASSERT (m_cfAckInfo.address != Mac48Address ());
          //Standard says that, for frames of type Data+CF-Ack, Data+CF-Poll+CF-Ack, and CF-Poll+CF-Ack,
          //the rate chosen to transmit the frame must be supported by both the addressed recipient STA and the STA to which the Ack is intended.
          //This ideally requires the rate manager to handle this case, but this requires to update all rate manager classes.
          //Instead, we simply fetch two TxVector and we select the one with the lowest data rate.
          //This should be later changed, at the latest once HCCA is implemented for HT/VHT/HE stations.
          WifiMacHeader tmpHdr = m_currentPacket->GetHeader (0);
          tmpHdr.SetAddr1 (m_cfAckInfo.address);
          WifiTxVector tmpTxVector = GetDataTxVector (Create<const WifiMacQueueItem> (m_currentPacket->GetPayload (0), tmpHdr));
          if (tmpTxVector.GetMode ().GetDataRate (tmpTxVector) < m_currentTxVector.GetMode ().GetDataRate (m_currentTxVector))
            {
              m_currentTxVector = tmpTxVector;
            }
          m_cfAckInfo.appendCfAck = false;
          m_cfAckInfo.address = Mac48Address ();
        }
    }
<<<<<<< HEAD

  ForwardDown (m_currentPacket, &m_currentHdr, m_currentTxVector, preamble);
  m_currentPacket = 0;
=======
  if (m_txParams.MustSendBlockAckRequest ())
    {
      Ptr<QosTxop> qosTxop = DynamicCast<QosTxop> (m_currentTxop);
      NS_ASSERT (qosTxop != 0);
      auto bar = qosTxop->PrepareBlockAckRequest (m_currentPacket->GetAddr1 (), *m_currentPacket->GetTids ().begin ());
      qosTxop->ScheduleBar (bar);
    }
  ForwardDown (m_currentPacket, m_currentTxVector);
>>>>>>> origin
}

bool
MacLow::IsNavZero (void) const
{
  return (m_lastNavStart + m_lastNavDuration < Simulator::Now ());
}

void
MacLow::SendCtsToSelf (void)
{
  WifiMacHeader cts;
  cts.SetType (WIFI_MAC_CTL_CTS);
  cts.SetDsNotFrom ();
  cts.SetDsNotTo ();
  cts.SetNoMoreFragments ();
  cts.SetNoRetry ();
  cts.SetAddr1 (m_self);

<<<<<<< HEAD
  WifiTxVector ctsTxVector = GetRtsTxVector (m_currentPacket, &m_currentHdr);

  WifiPreamble preamble;
  if (ctsTxVector.GetMode ().GetModulationClass () == WIFI_MOD_CLASS_HT)
    {
      preamble = WIFI_PREAMBLE_HT_MF;
    }
  else if (m_stationManager->GetShortPreambleEnabled ())
    {
      preamble = WIFI_PREAMBLE_SHORT;
    }
  else
    {
      preamble = WIFI_PREAMBLE_LONG;
    }

=======
  WifiTxVector ctsTxVector = GetRtsTxVector (*m_currentPacket->begin ());
>>>>>>> origin
  Time duration = Seconds (0);

  duration += GetSifs ();
  duration += m_phy->CalculateTxDuration (m_currentPacket->GetSize (),
                                          m_currentTxVector, m_phy->GetPhyBand ());
  duration += GetResponseDuration (m_txParams, m_currentTxVector, m_currentPacket->GetAddr1 ());
  if (m_txParams.HasNextPacket ())
    {
<<<<<<< HEAD
      duration += m_txParams.GetDurationId ();
    }
  else
    {
      duration += GetSifs ();
      duration += m_phy->CalculateTxDuration (GetSize (m_currentPacket,&m_currentHdr),
                                              m_currentTxVector, preamble, m_phy->GetFrequency ());
      if (m_txParams.MustWaitBasicBlockAck ())
        {

          duration += GetSifs ();
          WifiTxVector blockAckReqTxVector = GetBlockAckTxVector (m_currentHdr.GetAddr2 (), m_currentTxVector.GetMode ());
          duration += GetBlockAckDuration (m_currentHdr.GetAddr1 (), blockAckReqTxVector, BASIC_BLOCK_ACK);
        }
      else if (m_txParams.MustWaitCompressedBlockAck ())
        {
          duration += GetSifs ();
          WifiTxVector blockAckReqTxVector = GetBlockAckTxVector (m_currentHdr.GetAddr2 (), m_currentTxVector.GetMode ());
          duration += GetBlockAckDuration (m_currentHdr.GetAddr1 (), blockAckReqTxVector, COMPRESSED_BLOCK_ACK);
        }
      else if (m_txParams.MustWaitAck ())
        {
          duration += GetSifs ();
          duration += GetAckDuration (m_currentHdr.GetAddr1 (), m_currentTxVector);
        }
      if (m_txParams.HasNextPacket ())
        {
          duration += GetSifs ();
          duration += m_phy->CalculateTxDuration (m_txParams.GetNextPacketSize (),
                                                  m_currentTxVector, preamble, m_phy->GetFrequency ());
          if (m_txParams.MustWaitCompressedBlockAck ())
            {
              duration += GetSifs ();
              WifiTxVector blockAckReqTxVector = GetBlockAckTxVector (m_currentHdr.GetAddr2 (), m_currentTxVector.GetMode ());
              duration += GetBlockAckDuration (m_currentHdr.GetAddr1 (), blockAckReqTxVector, COMPRESSED_BLOCK_ACK);
            }
          else if (m_txParams.MustWaitAck ())
            {
              duration += GetSifs ();
              duration += GetAckDuration (m_currentHdr.GetAddr1 (), m_currentTxVector);
            }
        }
=======
      duration += GetSifs ();
      duration += m_phy->CalculateTxDuration (m_txParams.GetNextPacketSize (),
                                              m_currentTxVector, m_phy->GetPhyBand ());
      duration += GetResponseDuration (m_txParams, m_currentTxVector, m_currentPacket->GetAddr1 ());
>>>>>>> origin
    }

  cts.SetDuration (duration);

  ForwardDown (Create<const WifiPsdu> (Create<Packet> (), cts), ctsTxVector);

<<<<<<< HEAD
  ForwardDown (packet, &cts, ctsTxVector,preamble);

  Time txDuration = m_phy->CalculateTxDuration (GetCtsSize (), ctsTxVector, preamble, m_phy->GetFrequency ());
=======
  Time txDuration = m_phy->CalculateTxDuration (GetCtsSize (), ctsTxVector, m_phy->GetPhyBand ());
>>>>>>> origin
  txDuration += GetSifs ();
  NS_ASSERT (m_sendDataEvent.IsExpired ());

  m_sendDataEvent = Simulator::Schedule (txDuration,
                                         &MacLow::SendDataAfterCts, this,
                                         duration);
}

void
MacLow::SendCtsAfterRts (Mac48Address source, Time duration, WifiTxVector rtsTxVector, double rtsSnr)
{
  NS_LOG_FUNCTION (this << source << duration << rtsTxVector.GetMode () << rtsSnr);
  /* send a CTS when you receive a RTS
   * right after SIFS.
   */
  WifiTxVector ctsTxVector = GetCtsTxVector (source, rtsTxVector.GetMode ());
  WifiMacHeader cts;
  cts.SetType (WIFI_MAC_CTL_CTS);
  cts.SetDsNotFrom ();
  cts.SetDsNotTo ();
  cts.SetNoMoreFragments ();
  cts.SetNoRetry ();
  cts.SetAddr1 (source);
  duration -= GetCtsDuration (source, rtsTxVector);
  duration -= GetSifs ();
  NS_ASSERT (duration.IsPositive ());
  cts.SetDuration (duration);

  Ptr<Packet> packet = Create<Packet> ();

  SnrTag tag;
  tag.Set (rtsSnr);
  packet->AddPacketTag (tag);
  
  WifiPreamble preamble;
  if (m_stationManager->GetShortPreambleEnabled ())
    {
      preamble = WIFI_PREAMBLE_SHORT;
    }
  else
    {
      preamble = WIFI_PREAMBLE_LONG;
    }

  //CTS should always use non-HT PPDU (HT PPDU cases not supported yet)
<<<<<<< HEAD
  ForwardDown (packet, &cts, ctsTxVector, preamble);
=======
  ForwardDown (Create<const WifiPsdu> (packet, cts), ctsTxVector);
>>>>>>> origin
}

void
MacLow::SendDataAfterCts (Time duration)
{
  NS_LOG_FUNCTION (this);
  /* send the third step in a
   * RTS/CTS/Data/Ack handshake
   */
  NS_ASSERT (m_currentPacket != 0);

<<<<<<< HEAD
  if (m_aggregateQueue->GetSize () != 0)
    {
      for (std::vector<Item>::size_type i = 0; i != m_txPackets.size (); i++)
        {
          uint8_t tid = GetTid (m_txPackets.at (i).packet, m_txPackets.at (i).hdr);
          AcIndex ac = QosUtilsMapTidToAc (tid);
          std::map<AcIndex, MacLowAggregationCapableTransmissionListener*>::const_iterator listenerIt = m_edcaListeners.find (ac);

          listenerIt->second->CompleteMpduTx (m_txPackets.at (i).packet, m_txPackets.at (i).hdr, m_txPackets.at (i).timestamp);
        }
      m_txPackets.clear ();
    }

  WifiPreamble preamble;
  if (m_currentTxVector.GetMode ().GetModulationClass () == WIFI_MOD_CLASS_VHT)
    {
      preamble = WIFI_PREAMBLE_VHT;
    }
  else if (m_phy->GetGreenfield () && m_stationManager->GetGreenfieldSupported (m_currentHdr.GetAddr1 ()))
    {
      //In the future has to make sure that receiver has greenfield enabled
      preamble = WIFI_PREAMBLE_HT_GF;
    }
  else if (m_currentTxVector.GetMode ().GetModulationClass () == WIFI_MOD_CLASS_HT)
    {
      preamble = WIFI_PREAMBLE_HT_MF;
    }
  else if (m_stationManager->GetShortPreambleEnabled ())
    {
      preamble = WIFI_PREAMBLE_SHORT;
    }
  else
    {
      preamble = WIFI_PREAMBLE_LONG;
    }

  StartDataTxTimers (m_currentTxVector);
  Time newDuration = Seconds (0);
  if (m_txParams.MustWaitBasicBlockAck ())
    {
      newDuration += GetSifs ();
      WifiTxVector blockAckReqTxVector = GetBlockAckTxVector (m_currentHdr.GetAddr2 (), m_currentTxVector.GetMode ());
      newDuration += GetBlockAckDuration (m_currentHdr.GetAddr1 (), blockAckReqTxVector, BASIC_BLOCK_ACK);
    }
  else if (m_txParams.MustWaitCompressedBlockAck ())
    {
      newDuration += GetSifs ();
      WifiTxVector blockAckReqTxVector = GetBlockAckTxVector (m_currentHdr.GetAddr2 (), m_currentTxVector.GetMode ());
      newDuration += GetBlockAckDuration (m_currentHdr.GetAddr1 (), blockAckReqTxVector, COMPRESSED_BLOCK_ACK);
    }
  else if (m_txParams.MustWaitAck ())
    {
      newDuration += GetSifs ();
      newDuration += GetAckDuration (m_currentHdr.GetAddr1 (), m_currentTxVector);
    }
  if (m_txParams.HasNextPacket ())
    {
      newDuration += GetSifs ();
      newDuration += m_phy->CalculateTxDuration (m_txParams.GetNextPacketSize (), m_currentTxVector, preamble, m_phy->GetFrequency ());
      if (m_txParams.MustWaitCompressedBlockAck ())
        {
          newDuration += GetSifs ();
          WifiTxVector blockAckReqTxVector = GetBlockAckTxVector (m_currentHdr.GetAddr2 (), m_currentTxVector.GetMode ());
          newDuration += GetBlockAckDuration (m_currentHdr.GetAddr1 (), blockAckReqTxVector, COMPRESSED_BLOCK_ACK);
        }
      else if (m_txParams.MustWaitAck ())
        {
          newDuration += GetSifs ();
          newDuration += GetAckDuration (m_currentHdr.GetAddr1 (), m_currentTxVector);
        }
    }

  Time txDuration = m_phy->CalculateTxDuration (GetSize (m_currentPacket, &m_currentHdr), m_currentTxVector, preamble, m_phy->GetFrequency ());
=======
  StartDataTxTimers (m_currentTxVector);
  Time newDuration = GetResponseDuration (m_txParams, m_currentTxVector, m_currentPacket->GetAddr1 ());
  if (m_txParams.HasNextPacket ())
    {
      newDuration += GetSifs ();
      newDuration += m_phy->CalculateTxDuration (m_txParams.GetNextPacketSize (), m_currentTxVector, m_phy->GetPhyBand ());
      newDuration += GetResponseDuration (m_txParams, m_currentTxVector, m_currentPacket->GetAddr1 ());
    }

  Time txDuration = m_phy->CalculateTxDuration (m_currentPacket->GetSize (), m_currentTxVector, m_phy->GetPhyBand ());
>>>>>>> origin
  duration -= txDuration;
  duration -= GetSifs ();

  duration = std::max (duration, newDuration);
  NS_ASSERT (duration.IsPositive ());
  m_currentPacket->SetDuration (duration);
  if (m_txParams.MustSendBlockAckRequest ())
    {
      Ptr<QosTxop> qosTxop = DynamicCast<QosTxop> (m_currentTxop);
      NS_ASSERT (qosTxop != 0);
      auto bar = qosTxop->PrepareBlockAckRequest (m_currentPacket->GetAddr1 (), *m_currentPacket->GetTids ().begin ());
      qosTxop->ScheduleBar (bar);
    }
<<<<<<< HEAD

  ForwardDown (m_currentPacket, &m_currentHdr, m_currentTxVector, preamble);
  m_currentPacket = 0;
}

void
MacLow::WaitSifsAfterEndTxFragment (void)
{
  m_listener->StartNextFragment ();
}

void
MacLow::WaitSifsAfterEndTx (void)
=======
  ForwardDown (m_currentPacket, m_currentTxVector);
}

void
MacLow::WaitIfsAfterEndTxFragment (void)
>>>>>>> origin
{
  NS_LOG_FUNCTION (this);
  m_currentTxop->StartNextFragment ();
}

void
MacLow::WaitIfsAfterEndTxPacket (void)
{
  NS_LOG_FUNCTION (this);
  m_currentTxop->StartNextPacket ();
}

void
MacLow::EndTxNoAck (void)
{
  NS_LOG_FUNCTION (this);
  if (m_currentPacket->GetHeader (0).IsBeacon () && m_stationManager->GetPcfSupported ())
    {
      m_cfpStart = Simulator::Now ();
    }
  if (!m_cfAckInfo.expectCfAck)
    {
      Ptr<Txop> txop = m_currentTxop;
      txop->EndTxNoAck ();
    }
  if (!IsCfPeriod ())
    {
      m_currentTxop = 0;
    }
}

void
MacLow::SendAckAfterData (Mac48Address source, Time duration, WifiMode dataTxMode, double dataSnr)
{
  NS_LOG_FUNCTION (this);
<<<<<<< HEAD
  // send an ACK, after SIFS, when you receive a packet 
=======
  // send an Ack, after SIFS, when you receive a packet
>>>>>>> origin
  WifiTxVector ackTxVector = GetAckTxVector (source, dataTxMode);
  WifiMacHeader ack;
  ack.SetType (WIFI_MAC_CTL_ACK);
  ack.SetDsNotFrom ();
  ack.SetDsNotTo ();
  ack.SetNoRetry ();
  ack.SetNoMoreFragments ();
  ack.SetAddr1 (source);
  // 802.11-2012, Section 8.3.1.4:  Duration/ID is received duration value
<<<<<<< HEAD
  // minus the time to transmit the ACK frame and its SIFS interval
  duration -= GetAckDuration (ackTxVector);
  duration -= GetSifs ();
  NS_ASSERT_MSG (duration >= MicroSeconds (0), "Please provide test case to maintainers if this assert is hit.");
=======
  // minus the time to transmit the Ack frame and its SIFS interval
  duration -= GetAckDuration (ackTxVector);
  duration -= GetSifs ();
  NS_ASSERT_MSG (duration.IsPositive (), "Please provide test case to maintainers if this assert is hit.");
>>>>>>> origin
  ack.SetDuration (duration);

  Ptr<Packet> packet = Create<Packet> ();

  SnrTag tag;
  tag.Set (dataSnr);
  packet->AddPacketTag (tag);
  
  WifiPreamble preamble;
  if (m_stationManager->GetShortPreambleEnabled ())
    {
      preamble = WIFI_PREAMBLE_SHORT;
    }
  else
    {
      preamble = WIFI_PREAMBLE_LONG;
    }

<<<<<<< HEAD
  //ACK should always use non-HT PPDU (HT PPDU cases not supported yet)
  ForwardDown (packet, &ack, ackTxVector, preamble);
=======
  //Ack should always use non-HT PPDU (HT PPDU cases not supported yet)
  ForwardDown (Create<const WifiPsdu> (packet, ack), ackTxVector);
>>>>>>> origin
}

bool
MacLow::ReceiveMpdu (Ptr<WifiMacQueueItem> mpdu)
{
  const WifiMacHeader& hdr = mpdu->GetHeader ();

  if (m_stationManager->GetHtSupported ()
      || m_stationManager->GetVhtSupported ()
      || m_stationManager->GetHeSupported ())
    {
      Mac48Address originator = hdr.GetAddr2 ();
      uint8_t tid = 0;
      if (hdr.IsQosData ())
        {
          tid = hdr.GetQosTid ();
        }
      uint16_t seqNumber = hdr.GetSequenceNumber ();
      AgreementsI it = m_bAckAgreements.find (std::make_pair (originator, tid));
      if (it != m_bAckAgreements.end ())
        {
          //Implement HT immediate BlockAck support for HT Delayed BlockAck is not added yet
          if (!QosUtilsIsOldPacket ((*it).second.first.GetStartingSequence (), seqNumber))
            {
              StoreMpduIfNeeded (mpdu);
              if (!IsInWindow (hdr.GetSequenceNumber (), (*it).second.first.GetStartingSequence (), (*it).second.first.GetBufferSize ()))
                {
                  uint16_t delta = (seqNumber - (*it).second.first.GetWinEnd () + 4096) % 4096;
                  NS_ASSERT (delta > 0);
                  uint16_t bufferSize = (*it).second.first.GetBufferSize ();
                  uint16_t startingSeq = (seqNumber - bufferSize + 1 + 4096) % 4096;
                  (*it).second.first.SetStartingSequence (startingSeq);
                  RxCompleteBufferedPacketsWithSmallerSequence ((*it).second.first.GetStartingSequenceControl (), originator, tid);
                }
              RxCompleteBufferedPacketsUntilFirstLost (originator, tid); //forwards up packets starting from winstart and set winstart to last +1
            }
          return true;
        }
      return false;
    }
  return StoreMpduIfNeeded (mpdu);
}

bool
MacLow::StoreMpduIfNeeded (Ptr<WifiMacQueueItem> mpdu)
{
  const WifiMacHeader& hdr = mpdu->GetHeader ();

  AgreementsI it = m_bAckAgreements.find (std::make_pair (hdr.GetAddr2 (), hdr.GetQosTid ()));
  if (it != m_bAckAgreements.end ())
    {
      uint16_t endSequence = ((*it).second.first.GetStartingSequence () + 2047) % 4096;
      uint32_t mappedSeqControl = QosUtilsMapSeqControlToUniqueInteger (hdr.GetSequenceControl (), endSequence);

      BufferedPacketI i = (*it).second.second.begin ();
      for (; i != (*it).second.second.end ()
           && QosUtilsMapSeqControlToUniqueInteger ((*i)->GetHeader ().GetSequenceControl (), endSequence) < mappedSeqControl; i++)
        {
        }
      (*it).second.second.insert (i, mpdu);

      //Update block ack cache
      BlockAckCachesI j = m_bAckCaches.find (std::make_pair (hdr.GetAddr2 (), hdr.GetQosTid ()));
      NS_ASSERT (j != m_bAckCaches.end ());
      (*j).second.UpdateWithMpdu (&hdr);
      return true;
    }
  return false;
}

void
MacLow::CreateBlockAckAgreement (const MgtAddBaResponseHeader *respHdr, Mac48Address originator,
                                 uint16_t startingSeq)
{
  NS_LOG_FUNCTION (this);
  uint8_t tid = respHdr->GetTid ();
  BlockAckAgreement agreement (originator, tid);
  if (respHdr->IsImmediateBlockAck ())
    {
      agreement.SetImmediateBlockAck ();
    }
  else
    {
      agreement.SetDelayedBlockAck ();
    }
  agreement.SetAmsduSupport (respHdr->IsAmsduSupported ());
  agreement.SetBufferSize (respHdr->GetBufferSize () + 1);
  agreement.SetTimeout (respHdr->GetTimeout ());
  agreement.SetStartingSequence (startingSeq);

  std::list<Ptr<WifiMacQueueItem>> buffer (0);
  AgreementKey key (originator, respHdr->GetTid ());
  AgreementValue value (agreement, buffer);
  m_bAckAgreements.insert (std::make_pair (key, value));

  BlockAckCache cache;
  cache.Init (startingSeq, respHdr->GetBufferSize () + 1);
  m_bAckCaches.insert (std::make_pair (key, cache));

  if (respHdr->GetTimeout () != 0)
    {
      AgreementsI it = m_bAckAgreements.find (std::make_pair (originator, respHdr->GetTid ()));
      Time timeout = MicroSeconds (1024 * agreement.GetTimeout ());

      AcIndex ac = QosUtilsMapTidToAc (agreement.GetTid ());

      it->second.first.m_inactivityEvent = Simulator::Schedule (timeout,
                                                                &QosTxop::SendDelbaFrame,
                                                                m_edca[ac], originator, tid, false);
    }
}

void
MacLow::DestroyBlockAckAgreement (Mac48Address originator, uint8_t tid)
{
  NS_LOG_FUNCTION (this);
  AgreementsI it = m_bAckAgreements.find (std::make_pair (originator, tid));
  if (it != m_bAckAgreements.end ())
    {
      RxCompleteBufferedPacketsWithSmallerSequence (it->second.first.GetStartingSequenceControl (), originator, tid);
      RxCompleteBufferedPacketsUntilFirstLost (originator, tid);
      m_bAckAgreements.erase (it);
      BlockAckCachesI i = m_bAckCaches.find (std::make_pair (originator, tid));
      NS_ASSERT (i != m_bAckCaches.end ());
      m_bAckCaches.erase (i);
    }
}

void
MacLow::RxCompleteBufferedPacketsWithSmallerSequence (uint16_t seq, Mac48Address originator, uint8_t tid)
{
  AgreementsI it = m_bAckAgreements.find (std::make_pair (originator, tid));
  if (it != m_bAckAgreements.end ())
    {
      uint16_t endSequence = ((*it).second.first.GetStartingSequence () + 2047) % 4096;
      uint32_t mappedStart = QosUtilsMapSeqControlToUniqueInteger (seq, endSequence);
      BufferedPacketI last = (*it).second.second.begin ();
      uint16_t guard = 0;
      if (last != (*it).second.second.end ())
        {
          guard = (*(*it).second.second.begin ())->GetHeader ().GetSequenceControl ();
        }
      BufferedPacketI i = (*it).second.second.begin ();
      for (; i != (*it).second.second.end ()
           && QosUtilsMapSeqControlToUniqueInteger ((*i)->GetHeader ().GetSequenceControl (), endSequence) < mappedStart; )
        {
          if (guard == (*i)->GetHeader ().GetSequenceControl ())
            {
              if (!(*i)->GetHeader ().IsMoreFragments ())
                {
                  while (last != i)
                    {
                      m_rxCallback (*last);
                      last++;
                    }
                  m_rxCallback (*last);
                  last++;
                  /* go to next packet */
                  while (i != (*it).second.second.end () && guard == (*i)->GetHeader ().GetSequenceControl ())
                    {
                      i++;
                    }
                  if (i != (*it).second.second.end ())
                    {
                      guard = (*i)->GetHeader ().GetSequenceControl ();
                      last = i;
                    }
                }
              else
                {
                  guard++;
                }
            }
          else
            {
              /* go to next packet */
              while (i != (*it).second.second.end () && guard == (*i)->GetHeader ().GetSequenceControl ())
                {
                  i++;
                }
              if (i != (*it).second.second.end ())
                {
                  guard = (*i)->GetHeader ().GetSequenceControl ();
                  last = i;
                }
            }
        }
      (*it).second.second.erase ((*it).second.second.begin (), i);
    }
}

void
MacLow::RxCompleteBufferedPacketsUntilFirstLost (Mac48Address originator, uint8_t tid)
{
  AgreementsI it = m_bAckAgreements.find (std::make_pair (originator, tid));
  if (it != m_bAckAgreements.end ())
    {
      uint16_t guard = (*it).second.first.GetStartingSequenceControl ();
      BufferedPacketI lastComplete = (*it).second.second.begin ();
      BufferedPacketI i = (*it).second.second.begin ();
      for (; i != (*it).second.second.end () && guard == (*i)->GetHeader ().GetSequenceControl (); i++)
        {
          if (!(*i)->GetHeader ().IsMoreFragments ())
            {
              while (lastComplete != i)
                {
                  m_rxCallback (*lastComplete);
                  lastComplete++;
                }
              m_rxCallback (*lastComplete);
              lastComplete++;
            }
          guard = (*i)->GetHeader ().IsMoreFragments () ? (guard + 1) : ((guard + 16) & 0xfff0);
        }
      (*it).second.first.SetStartingSequenceControl (guard);
      /* All packets already forwarded to WifiMac must be removed from buffer:
      [begin (), lastComplete) */
      (*it).second.second.erase ((*it).second.second.begin (), lastComplete);
    }
}

void
MacLow::SendBlockAckResponse (const CtrlBAckResponseHeader* blockAck, Mac48Address originator, bool immediate,
                              Time duration, WifiMode blockAckReqTxMode, double rxSnr)
{
  NS_LOG_FUNCTION (this);
  Ptr<Packet> packet = Create<Packet> ();
  packet->AddHeader (*blockAck);

  WifiMacHeader hdr;
  hdr.SetType (WIFI_MAC_CTL_BACKRESP);
  hdr.SetAddr1 (originator);
  hdr.SetAddr2 (GetAddress ());
  hdr.SetDsNotFrom ();
  hdr.SetDsNotTo ();
  hdr.SetNoRetry ();
  hdr.SetNoMoreFragments ();

  WifiTxVector blockAckReqTxVector = GetBlockAckTxVector (originator, blockAckReqTxMode);

  if (immediate)
    {
      m_txParams.DisableAck ();
      duration -= GetSifs ();
      duration -= GetBlockAckDuration (blockAckReqTxVector, blockAck->GetType ());
    }
  else
    {
      m_txParams.EnableAck ();
      duration += GetSifs ();
      duration += GetAckDuration (originator, blockAckReqTxVector);
    }
  m_txParams.DisableNextData ();

  if (!immediate)
    {
      StartDataTxTimers (blockAckReqTxVector);
    }

<<<<<<< HEAD
  NS_ASSERT (duration >= NanoSeconds (0));
=======
  NS_ASSERT (duration.IsPositive ());
>>>>>>> origin
  hdr.SetDuration (duration);
  //here should be present a control about immediate or delayed BlockAck
  //for now we assume immediate
<<<<<<< HEAD
  packet->AddHeader (hdr);
  WifiMacTrailer fcs;
  packet->AddTrailer (fcs);
  WifiPreamble preamble;
  if (blockAckReqTxVector.GetMode ().GetModulationClass () == WIFI_MOD_CLASS_HT)
    {
      preamble = WIFI_PREAMBLE_HT_MF;
    }
  else if (m_stationManager->GetShortPreambleEnabled ())
    {
      preamble = WIFI_PREAMBLE_SHORT;
    }
  else
    {
      preamble = WIFI_PREAMBLE_LONG;
    }
  SnrTag tag;
  tag.Set (rxSnr);
  packet->AddPacketTag (tag);
  ForwardDown (packet, &hdr, blockAckReqTxVector, preamble);
  m_currentPacket = 0;
=======
  SnrTag tag;
  tag.Set (rxSnr);
  packet->AddPacketTag (tag);
  ForwardDown (Create<const WifiPsdu> (packet, hdr), blockAckReqTxVector);
>>>>>>> origin
}

void
MacLow::SendBlockAckAfterAmpdu (uint8_t tid, Mac48Address originator, Time duration, WifiTxVector blockAckReqTxVector, double rxSnr)
{
<<<<<<< HEAD
  NS_LOG_FUNCTION (this << (uint16_t) tid << originator << duration.As (Time::S) << blockAckReqTxVector << rxSnr);
  CtrlBAckResponseHeader blockAck;
  uint16_t seqNumber = 0;
  BlockAckCachesI i = m_bAckCaches.find (std::make_pair (originator, tid));
  NS_ASSERT (i != m_bAckCaches.end ());
  seqNumber = (*i).second.GetWinStart ();
=======
  NS_LOG_FUNCTION (this);
  if (!m_phy->IsStateTx () && !m_phy->IsStateRx ())
    {
      NS_LOG_FUNCTION (this << +tid << originator << duration.As (Time::S) << blockAckReqTxVector << rxSnr);
      CtrlBAckResponseHeader blockAck;
      uint16_t seqNumber = 0;
      BlockAckCachesI i = m_bAckCaches.find (std::make_pair (originator, tid));
      NS_ASSERT (i != m_bAckCaches.end ());
      seqNumber = (*i).second.GetWinStart ();
>>>>>>> origin

      bool immediate = true;
      AgreementsI it = m_bAckAgreements.find (std::make_pair (originator, tid));
      blockAck.SetStartingSequence (seqNumber);
      blockAck.SetTidInfo (tid);
      immediate = (*it).second.first.IsImmediateBlockAck ();
      if ((*it).second.first.GetBufferSize () > 64)
        {
          blockAck.SetType (EXTENDED_COMPRESSED_BLOCK_ACK);
        }
      else
        {
          blockAck.SetType (COMPRESSED_BLOCK_ACK);
        }
      NS_LOG_DEBUG ("Got Implicit block Ack Req with seq " << seqNumber);
      (*i).second.FillBlockAckBitmap (&blockAck);

<<<<<<< HEAD
  SendBlockAckResponse (&blockAck, originator, immediate, duration, blockAckReqTxVector.GetMode (), rxSnr);
=======
      WifiTxVector blockAckTxVector = GetBlockAckTxVector (originator, blockAckReqTxVector.GetMode ());

      SendBlockAckResponse (&blockAck, originator, immediate, duration, blockAckTxVector.GetMode (), rxSnr);
    }
  else
    {
      NS_LOG_DEBUG ("Skip block ack response!");
    }
>>>>>>> origin
}

void
MacLow::SendBlockAckAfterBlockAckRequest (const CtrlBAckRequestHeader reqHdr, Mac48Address originator,
                                          Time duration, WifiMode blockAckReqTxMode, double rxSnr)
{
  NS_LOG_FUNCTION (this);
  CtrlBAckResponseHeader blockAck;
  uint8_t tid = 0;
  bool immediate = false;
  if (!reqHdr.IsMultiTid ())
    {
      tid = reqHdr.GetTidInfo ();
      AgreementsI it = m_bAckAgreements.find (std::make_pair (originator, tid));
      if (it != m_bAckAgreements.end ())
        {
          blockAck.SetStartingSequence (reqHdr.GetStartingSequence ());
          blockAck.SetTidInfo (tid);
          immediate = (*it).second.first.IsImmediateBlockAck ();
          if (reqHdr.IsBasic ())
            {
              blockAck.SetType (BASIC_BLOCK_ACK);
            }
          else if (reqHdr.IsCompressed ())
            {
              blockAck.SetType (COMPRESSED_BLOCK_ACK);
            }
          else if (reqHdr.IsExtendedCompressed ())
            {
              blockAck.SetType (EXTENDED_COMPRESSED_BLOCK_ACK);
            }
          BlockAckCachesI i = m_bAckCaches.find (std::make_pair (originator, tid));
          NS_ASSERT (i != m_bAckCaches.end ());
          (*i).second.FillBlockAckBitmap (&blockAck);
          NS_LOG_DEBUG ("Got block Ack Req with seq " << reqHdr.GetStartingSequence ());

          if (!m_stationManager->GetHtSupported ()
              && !m_stationManager->GetVhtSupported ()
              && !m_stationManager->GetHeSupported ())
            {
              /* All packets with smaller sequence than starting sequence control must be passed up to WifiMac
               * See 9.10.3 in IEEE 802.11e standard.
               */
              RxCompleteBufferedPacketsWithSmallerSequence (reqHdr.GetStartingSequenceControl (), originator, tid);
              RxCompleteBufferedPacketsUntilFirstLost (originator, tid);
            }
          else
            {
              if (!QosUtilsIsOldPacket ((*it).second.first.GetStartingSequence (), reqHdr.GetStartingSequence ()))
                {
                  (*it).second.first.SetStartingSequence (reqHdr.GetStartingSequence ());
                  RxCompleteBufferedPacketsWithSmallerSequence (reqHdr.GetStartingSequenceControl (), originator, tid);
                  RxCompleteBufferedPacketsUntilFirstLost (originator, tid);
                }
            }
        }
      else
        {
          NS_LOG_DEBUG ("there's not a valid block ack agreement with " << originator);
        }
    }
  else
    {
      NS_FATAL_ERROR ("Multi-tid block ack is not supported.");
    }
<<<<<<< HEAD

=======
>>>>>>> origin
  SendBlockAckResponse (&blockAck, originator, immediate, duration, blockAckReqTxMode, rxSnr);
}

void
MacLow::ResetBlockAckInactivityTimerIfNeeded (BlockAckAgreement &agreement)
{
  if (agreement.GetTimeout () != 0)
    {
      NS_ASSERT (agreement.m_inactivityEvent.IsRunning ());
      agreement.m_inactivityEvent.Cancel ();
      Time timeout = MicroSeconds (1024 * agreement.GetTimeout ());
      AcIndex ac = QosUtilsMapTidToAc (agreement.GetTid ());
      agreement.m_inactivityEvent = Simulator::Schedule (timeout,
                                                         &QosTxop::SendDelbaFrame,
                                                         m_edca[ac], agreement.GetPeer (),
                                                         agreement.GetTid (), false);
    }
}

void
MacLow::RegisterEdcaForAc (AcIndex ac, Ptr<QosTxop> edca)
{
  m_edca.insert (std::make_pair (ac, edca));
}

void
<<<<<<< HEAD
MacLow::DeaggregateAmpduAndReceive (Ptr<Packet> aggregatedPacket, double rxSnr, WifiTxVector txVector, WifiPreamble preamble)
{
  NS_LOG_FUNCTION (this);
  AmpduTag ampdu;
=======
MacLow::DeaggregateAmpduAndReceive (Ptr<WifiPsdu> psdu, double rxSnr, WifiTxVector txVector, std::vector<bool> statusPerMpdu)
{
  NS_LOG_FUNCTION (this);
>>>>>>> origin
  bool normalAck = false;
  bool ampduSubframe = txVector.IsAggregation (); //flag indicating the packet belongs to an A-MPDU and is not a VHT/HE single MPDU
  //statusPerMpdu is empty for intermediate MPDU forwarding.
  //This function is called also once the PPDU has been fully received by the PHY,
  //in that case statusPerMpdu carries the information about the received MPDUs.
  if (ampduSubframe && !statusPerMpdu.empty ())
    {
      //We are here if a S-MPDU is received or if all MPDUs of an A-MPDU have been
      //received (but have been already forwarded up, so ReceiveOk won't be called)
      NS_ASSERT (psdu->IsAggregate ());
      ampduSubframe = true;
<<<<<<< HEAD
      MpduAggregator::DeaggregatedMpdus packets = MpduAggregator::Deaggregate (aggregatedPacket);
      MpduAggregator::DeaggregatedMpdusCI n = packets.begin ();

      WifiMacHeader firsthdr;
      (*n).first->PeekHeader (firsthdr);
      NS_LOG_DEBUG ("duration/id=" << firsthdr.GetDuration ());
      NotifyNav ((*n).first, firsthdr, preamble);

      if (firsthdr.GetAddr1 () == m_self)
        {
          bool vhtSingleMpdu = (*n).second.GetEof ();
          if (vhtSingleMpdu)
            {
              //If the MPDU is sent as a VHT single MPDU (EOF=1 in A-MPDU subframe header), then the responder sends an ACK.
              NS_LOG_DEBUG ("Receive VHT single MPDU");
              ampduSubframe = false;
            }
          else if (preamble != WIFI_PREAMBLE_NONE || !m_sendAckEvent.IsRunning ())
            {
              m_sendAckEvent = Simulator::Schedule (ampdu.GetRemainingAmpduDuration () + GetSifs (),
                                                    &MacLow::SendBlockAckAfterAmpdu, this,
                                                    firsthdr.GetQosTid (),
                                                    firsthdr.GetAddr2 (),
                                                    firsthdr.GetDuration (),
                                                    txVector,
                                                    rxSnr);
            }

          if (firsthdr.IsAck () || firsthdr.IsBlockAck () || firsthdr.IsBlockAckReq ())
=======
      auto n = psdu->begin ();
      auto status = statusPerMpdu.begin ();
      NS_ABORT_MSG_IF (psdu->GetNMpdus () != statusPerMpdu.size (), "Should have one receive status per MPDU");

      WifiMacHeader firsthdr = (*n)->GetHeader ();
      if (firsthdr.GetAddr1 () == m_self)
        {
          //Iterate over all MPDUs and notify reception only if status OK
          for (; n != psdu->end (); ++n, ++status)
>>>>>>> origin
            {
              firsthdr = (*n)->GetHeader ();
              NS_ABORT_MSG_IF (firsthdr.GetAddr1 () != m_self, "All MPDUs of A-MPDU should have the same destination address");
              if (*status) //PER and thus CRC check succeeded
                {
<<<<<<< HEAD
                  NS_LOG_DEBUG ("Normal Ack");
                  normalAck = true;
                }
            }
          else
            {
              NS_FATAL_ERROR ("Received A-MPDU with invalid first MPDU type");
            }

          if (ampdu.GetRemainingNbOfMpdus () == 0 && !vhtSingleMpdu)
            {
              if (normalAck)
                {
                  //send block Ack
                  if (firsthdr.IsBlockAckReq ())
                    {
                      NS_FATAL_ERROR ("Sending a BlockAckReq with QosPolicy equal to Normal Ack");
                    }
                  uint8_t tid = firsthdr.GetQosTid ();
                  AgreementsI it = m_bAckAgreements.find (std::make_pair (firsthdr.GetAddr2 (), tid));
                  if (it != m_bAckAgreements.end ())
                    {
                      /* See section 11.5.3 in IEEE 802.11 for mean of this timer */
                      ResetBlockAckInactivityTimerIfNeeded (it->second.first);
                      NS_LOG_DEBUG ("rx A-MPDU/sendImmediateBlockAck from=" << firsthdr.GetAddr2 ());
                      NS_ASSERT (m_sendAckEvent.IsRunning ());
                    }
                  else
                    {
                      NS_LOG_DEBUG ("There's not a valid agreement for this block ack request.");
                    }
                }
            }
        }
    }
  else
    {
      ReceiveOk (aggregatedPacket, rxSnr, txVector, preamble, ampduSubframe);
    }
}

bool
MacLow::StopMpduAggregation (Ptr<const Packet> peekedPacket, WifiMacHeader peekedHdr, Ptr<Packet> aggregatedPacket, uint16_t size) const
{
  if (peekedPacket == 0)
    {
      NS_LOG_DEBUG ("no more packets in queue");
      return true;
    }

  WifiPreamble preamble;
  Time aPPDUMaxTime = MilliSeconds (10);

  uint8_t tid = GetTid (peekedPacket, peekedHdr);
  AcIndex ac = QosUtilsMapTidToAc (tid);
  std::map<AcIndex, MacLowAggregationCapableTransmissionListener*>::const_iterator listenerIt = m_edcaListeners.find (ac);

  if (m_currentTxVector.GetMode ().GetModulationClass () == WIFI_MOD_CLASS_VHT)
    {
      preamble = WIFI_PREAMBLE_VHT;
      aPPDUMaxTime = MicroSeconds (5484);
    }
  else if (m_phy->GetGreenfield () && m_stationManager->GetGreenfieldSupported (m_currentHdr.GetAddr1 ()))
    {
      preamble = WIFI_PREAMBLE_HT_GF;
    }
  else if (m_currentTxVector.GetMode ().GetModulationClass () == WIFI_MOD_CLASS_HT)
    {
      preamble = WIFI_PREAMBLE_HT_MF;
    }
  else if (m_stationManager->GetShortPreambleEnabled ())
    {
      preamble = WIFI_PREAMBLE_SHORT;
    }
  else
    {
      preamble = WIFI_PREAMBLE_LONG;
    }

  //A STA shall not transmit a PPDU that has a duration that is greater than aPPDUMaxTime
  if (m_phy->CalculateTxDuration (aggregatedPacket->GetSize () + peekedPacket->GetSize () + peekedHdr.GetSize () + WIFI_MAC_FCS_LENGTH, m_currentTxVector, preamble, m_phy->GetFrequency ()) > aPPDUMaxTime)
    {
      NS_LOG_DEBUG ("no more packets can be aggregated to satisfy PPDU <= aPPDUMaxTime");
      return true;
    }

  if (!listenerIt->second->GetMpduAggregator ()->CanBeAggregated (peekedPacket->GetSize () + peekedHdr.GetSize () + WIFI_MAC_FCS_LENGTH, aggregatedPacket, size))
    {
      NS_LOG_DEBUG ("no more packets can be aggregated because the maximum A-MPDU size has been reached");
      return true;
    }

  return false;
}

Ptr<Packet>
MacLow::AggregateToAmpdu (Ptr<const Packet> packet, const WifiMacHeader hdr)
{
  NS_ASSERT (m_aggregateQueue->GetSize () == 0);
  bool isAmpdu = false;
  Ptr<Packet> newPacket, tempPacket;
  WifiMacHeader peekedHdr;
  newPacket = packet->Copy ();
  Ptr<Packet> currentAggregatedPacket;
  CtrlBAckRequestHeader blockAckReq;
  
  if (hdr.IsBlockAckReq ())
    {
      //Workaround to avoid BlockAckReq to be part of an A-MPDU. The standard says that
      //BlockAckReq is not present in A-MPDU if any QoS data frames for that TID are present.
      //Since an A-MPDU in non-PSMP frame exchanges aggregates MPDUs from one TID, this means
      //we should stop aggregation here for single-TID A-MPDUs. Once PSMP and multi-TID A-MPDUs
      //are supported, the condition of entering here should be changed.
      return newPacket;
    }
  
  //missing hdr.IsAck() since we have no means of knowing the Tid of the Ack yet
  if (hdr.IsQosData () || hdr.IsBlockAck ()|| hdr.IsBlockAckReq ())
    {
      Time tstamp;
      uint8_t tid = GetTid (packet, hdr);
      Ptr<WifiMacQueue> queue;
      AcIndex ac = QosUtilsMapTidToAc (tid);
      //since a blockack agreement always preceeds mpdu aggregation there should always exist blockAck listener
      std::map<AcIndex, MacLowAggregationCapableTransmissionListener*>::const_iterator listenerIt = m_edcaListeners.find (ac);
      NS_ASSERT (listenerIt != m_edcaListeners.end ());
      queue = listenerIt->second->GetQueue ();

      if (!hdr.GetAddr1 ().IsBroadcast () && listenerIt->second->GetMpduAggregator () != 0)
        {
          //Have to make sure that their exist a block Ack agreement before sending an AMPDU (BlockAck Manager)
          if (listenerIt->second->GetBlockAckAgreementExists (hdr.GetAddr1 (), tid))
            {
              /* here is performed mpdu aggregation */
              /* MSDU aggregation happened in edca if the user asked for it so m_currentPacket may contains a normal packet or a A-MSDU*/
              currentAggregatedPacket = Create<Packet> ();
              peekedHdr = hdr;
              uint16_t startingSequenceNumber = 0;
              uint16_t currentSequenceNumber = 0;
              uint8_t qosPolicy = 0;
              uint16_t blockAckSize = 0;
              bool aggregated = false;
              int i = 0;
              Ptr<Packet> aggPacket = newPacket->Copy ();

              if (!hdr.IsBlockAckReq ())
                {
                  if (!hdr.IsBlockAck ())
=======
                  if (psdu->IsSingle ())
>>>>>>> origin
                    {
                      //If the MPDU is sent as a VHT/HE single MPDU (EOF=1 in A-MPDU subframe header), then the responder sends an Ack.
                      NS_LOG_DEBUG ("Receive S-MPDU");
                      ampduSubframe = false;
                    }
<<<<<<< HEAD
                  currentSequenceNumber = peekedHdr.GetSequenceNumber ();
                  newPacket->AddHeader (peekedHdr);
                  WifiMacTrailer fcs;
                  newPacket->AddTrailer (fcs);

                  aggregated = listenerIt->second->GetMpduAggregator ()->Aggregate (newPacket, currentAggregatedPacket);

                  if (aggregated)
=======
                  else if (!m_sendAckEvent.IsRunning () && firsthdr.IsQosAck ()) // Implicit BAR Ack Policy
>>>>>>> origin
                    {
                      m_sendAckEvent = Simulator::Schedule (GetSifs (),
                                                            &MacLow::SendBlockAckAfterAmpdu, this,
                                                            firsthdr.GetQosTid (),
                                                            firsthdr.GetAddr2 (),
                                                            firsthdr.GetDuration (),
                                                            txVector, rxSnr);
                    }
<<<<<<< HEAD
                }
              else if (hdr.IsBlockAckReq ())
                {
                  blockAckSize = packet->GetSize () + hdr.GetSize () + WIFI_MAC_FCS_LENGTH;
                  qosPolicy = 3; //if the last subrame is block ack req then set ack policy of all frames to blockack
                  packet->PeekHeader (blockAckReq);
                  startingSequenceNumber = blockAckReq.GetStartingSequence ();
                }
              /// \todo We should also handle Ack and BlockAck
              aggregated = false;
              bool retry = false;
              //looks for other packets to the same destination with the same Tid need to extend that to include MSDUs
              Ptr<const Packet> peekedPacket = listenerIt->second->PeekNextPacketInBaQueue (peekedHdr, peekedHdr.GetAddr1 (), tid, &tstamp);
              if (peekedPacket == 0)
                {
                  peekedPacket = queue->PeekByTidAndAddress (&peekedHdr, tid,
                                                             WifiMacHeader::ADDR1,
                                                             hdr.GetAddr1 (), &tstamp);
                  currentSequenceNumber = listenerIt->second->PeekNextSequenceNumberfor (&peekedHdr);
=======
>>>>>>> origin

                  if (firsthdr.IsAck () || firsthdr.IsBlockAck () || firsthdr.IsBlockAckReq ())
                    {
                      ReceiveOk ((*n), rxSnr, txVector, ampduSubframe);
                    }
                  else if (firsthdr.IsData () || firsthdr.IsQosData ())
                    {
                      NS_LOG_DEBUG ("Deaggregate packet from " << firsthdr.GetAddr2 () << " with sequence=" << firsthdr.GetSequenceNumber ());
                      if (psdu->IsSingle ())
                        {
                          ReceiveOk ((*n), rxSnr, txVector, ampduSubframe);
                        }
                      if (firsthdr.IsQosAck ())
                        {
                          NS_LOG_DEBUG ("Normal Ack");
                          normalAck = true;
                        }
                    }
                  else
                    {
                      NS_FATAL_ERROR ("Received A-MPDU with invalid first MPDU type");
                    }

<<<<<<< HEAD
                  newPacket = peekedPacket->Copy ();
                  Ptr<Packet> aggPacket = newPacket->Copy ();

                  newPacket->AddHeader (peekedHdr);
                  WifiMacTrailer fcs;
                  newPacket->AddTrailer (fcs);
                  aggregated = listenerIt->second->GetMpduAggregator ()->Aggregate (newPacket, currentAggregatedPacket);
                  if (aggregated)
=======
                  if (!psdu->IsSingle ())
>>>>>>> origin
                    {
                      if (normalAck)
                        {
                          //send BlockAck
                          if (firsthdr.IsBlockAckReq ())
                            {
                              NS_FATAL_ERROR ("Sending a BlockAckReq with QosPolicy equal to Normal Ack");
                            }
                          uint8_t tid = firsthdr.GetQosTid ();
                          AgreementsI it = m_bAckAgreements.find (std::make_pair (firsthdr.GetAddr2 (), tid));
                          if (it != m_bAckAgreements.end ())
                            {
                              /* See section 11.5.3 in IEEE 802.11 for the definition of this timer */
                              ResetBlockAckInactivityTimerIfNeeded (it->second.first);
                              NS_LOG_DEBUG ("rx A-MPDU/sendImmediateBlockAck from=" << firsthdr.GetAddr2 ());
                              NS_ASSERT (m_sendAckEvent.IsRunning ());
                            }
                          else
                            {
                              NS_LOG_DEBUG ("There's not a valid agreement for this block ack request.");
                            }
                        }
<<<<<<< HEAD
                      NS_LOG_DEBUG ("Adding packet with Sequence number " << peekedHdr.GetSequenceNumber () << " to A-MPDU, packet size = " << newPacket->GetSize () << ", A-MPDU size = " << currentAggregatedPacket->GetSize ());
                      i++;
                      isAmpdu = true;
                      m_sentMpdus++;
                      if (!m_txParams.MustSendRts ())
                        {
                          listenerIt->second->CompleteMpduTx (peekedPacket, peekedHdr, tstamp);
                        }
                      else
                        {
                          InsertInTxQueue (peekedPacket, peekedHdr, tstamp);
                        }
                      if (retry)
                        {
                          listenerIt->second->RemoveFromBaQueue (tid, hdr.GetAddr1 (), peekedHdr.GetSequenceNumber ());
                        }
                      else
                        {
                          queue->Remove (peekedPacket);
                        }
                      newPacket = 0;
                    }
                  else
                    {
                      break;
                    }
                  if (retry == true)
                    {
                      peekedPacket = listenerIt->second->PeekNextPacketInBaQueue (peekedHdr, hdr.GetAddr1 (), tid, &tstamp);
                      if (peekedPacket == 0)
                        {
                          //I reached the first packet that I added to this A-MPDU
                          retry = false;
                          peekedPacket = queue->PeekByTidAndAddress (&peekedHdr, tid,
                                                                     WifiMacHeader::ADDR1, hdr.GetAddr1 (), &tstamp);
                          if (peekedPacket != 0)
                            {
                              //find what will the sequence number be so that we don't send more than 64 packets apart
                              currentSequenceNumber = listenerIt->second->PeekNextSequenceNumberfor (&peekedHdr);

                              if (listenerIt->second->GetMsduAggregator () != 0)
                                {
                                  tempPacket = PerformMsduAggregation (peekedPacket, &peekedHdr, &tstamp, currentAggregatedPacket, blockAckSize);
                                  if (tempPacket != 0) //MSDU aggregation
                                    {
                                      peekedPacket = tempPacket->Copy ();
                                    }
                                }
                            }
                        }
                      else
                        {
                          currentSequenceNumber = peekedHdr.GetSequenceNumber ();
                        }
                    }
                  else
                    {
                      peekedPacket = queue->PeekByTidAndAddress (&peekedHdr, tid,
                                                                 WifiMacHeader::ADDR1, hdr.GetAddr1 (), &tstamp);
                      if (peekedPacket != 0)
                        {
                          //find what will the sequence number be so that we don't send more than 64 packets apart
                          currentSequenceNumber = listenerIt->second->PeekNextSequenceNumberfor (&peekedHdr);

                          if (listenerIt->second->GetMsduAggregator () != 0 && IsInWindow (currentSequenceNumber, startingSequenceNumber, 64))
                            {
                              tempPacket = PerformMsduAggregation (peekedPacket, &peekedHdr, &tstamp, currentAggregatedPacket, blockAckSize);
                              if (tempPacket != 0) //MSDU aggregation
                                {
                                  peekedPacket = tempPacket->Copy ();
                                }
                            }
                        }
                    }
                }

              if (isAmpdu)
                {
                  if (hdr.IsBlockAckReq ())
                    {
                      newPacket = packet->Copy ();
                      peekedHdr = hdr;
                      Ptr<Packet> aggPacket = newPacket->Copy ();
                      m_aggregateQueue->Enqueue (aggPacket, peekedHdr);
                      newPacket->AddHeader (peekedHdr);
                      WifiMacTrailer fcs;
                      newPacket->AddTrailer (fcs);
                      listenerIt->second->GetMpduAggregator ()->Aggregate (newPacket, currentAggregatedPacket);
                      currentAggregatedPacket->AddHeader (blockAckReq);
                    }

                  if (qosPolicy == 0)
                    {
                      listenerIt->second->CompleteTransfer (hdr.GetAddr1 (), tid);
                    }

                  //Add packet tag
                  AmpduTag ampdutag;
                  ampdutag.SetAmpdu (true);
                  ampdutag.SetRemainingNbOfMpdus (i - 1);
                  newPacket = currentAggregatedPacket;
                  newPacket->AddPacketTag (ampdutag);

                  NS_LOG_DEBUG ("tx unicast A-MPDU");
                  listenerIt->second->SetAmpdu (hdr.GetAddr1 (), true);
                }
              else
                {
                  uint32_t queueSize = m_aggregateQueue->GetSize ();
                  NS_ASSERT (queueSize <= 2); //since it is not an A-MPDU then only 2 packets should have been added to the queue no more
                  if (queueSize >= 1)
                    {
                      //remove any packets that we added to the aggregate queue
                      FlushAggregateQueue ();
                    }
                }
            }
          //VHT single MPDU operation
          WifiTxVector dataTxVector = GetDataTxVector (m_currentPacket, &m_currentHdr);
          if (!isAmpdu && dataTxVector.GetMode ().GetModulationClass () == WIFI_MOD_CLASS_VHT && hdr.IsQosData ())
            {
              peekedHdr = hdr;
              peekedHdr.SetQosAckPolicy (WifiMacHeader::NORMAL_ACK);

              currentAggregatedPacket = Create<Packet> ();
              listenerIt->second->GetMpduAggregator ()->AggregateVhtSingleMpdu (packet, currentAggregatedPacket);
              m_aggregateQueue->Enqueue (packet, peekedHdr);
              m_sentMpdus = 1;

              if (listenerIt->second->GetBlockAckAgreementExists (hdr.GetAddr1 (), tid))
                {
                  listenerIt->second->CompleteTransfer (peekedHdr.GetAddr1 (), tid);
                }

              //Add packet tag
              AmpduTag ampdutag;
              ampdutag.SetAmpdu (true);
              newPacket = currentAggregatedPacket;
              newPacket->AddHeader (peekedHdr);
              WifiMacTrailer fcs;
              newPacket->AddTrailer (fcs);
              newPacket->AddPacketTag (ampdutag);

              NS_LOG_DEBUG ("tx unicast VHT single MPDU with sequence number " << hdr.GetSequenceNumber ());
              listenerIt->second->SetAmpdu (hdr.GetAddr1 (), true);
            }
=======
                    }
                }
            }
>>>>>>> origin
        }
    }
  else
    {
      /* An MPDU has been received */
      NS_ASSERT (!psdu->IsAggregate ());
      ReceiveOk ((*psdu->begin ()), rxSnr, txVector, ampduSubframe);
    }
}

Time
MacLow::GetRemainingCfpDuration (void) const
{
  NS_LOG_FUNCTION (this);
  Time remainingCfpDuration = std::min (m_cfpStart, m_cfpStart + m_cfpMaxDuration - Simulator::Now () - m_cfpForeshortening);
  NS_ASSERT (remainingCfpDuration.IsPositive ());
  return remainingCfpDuration;
}

bool
MacLow::IsCfPeriod (void) const
{
  return (m_stationManager->GetPcfSupported () && m_cfpStart.IsStrictlyPositive ());
}

bool
MacLow::CanTransmitNextCfFrame (void) const
{
  NS_LOG_FUNCTION (this);
  if (!IsCfPeriod ())
    {
      return false;
    }
  NS_ASSERT (GetRemainingCfpDuration ().IsPositive ());
  WifiMacHeader hdr;
  hdr.SetType (WIFI_MAC_DATA);
  WifiMacTrailer fcs;
  uint32_t maxMacFrameSize = MAX_MSDU_SIZE + hdr.GetSerializedSize () + fcs.GetSerializedSize ();
  Time nextTransmission = 2 * m_phy->CalculateTxDuration (maxMacFrameSize, m_currentTxVector, m_phy->GetPhyBand ()) + 3 * GetSifs () + m_phy->CalculateTxDuration (GetCfEndSize (), m_currentTxVector, m_phy->GetPhyBand ());
  return ((GetRemainingCfpDuration () - nextTransmission).IsPositive ());
}

} //namespace ns3

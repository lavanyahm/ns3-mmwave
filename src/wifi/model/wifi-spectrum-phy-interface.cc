/* -*-  Mode: C++; c-file-style: "gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2009 CTTC
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
 * Author: Nicola Baldo <nbaldo@cttc.es>
 */

<<<<<<< HEAD
#include <ns3/ptr.h>
#include <ns3/object.h>
#include <ns3/net-device.h>
#include <ns3/mobility-model.h>
#include <ns3/wifi-phy.h>
#include <ns3/spectrum-phy.h>
#include <ns3/spectrum-signal-parameters.h>
#include <ns3/log.h>
#include <ns3/spectrum-value.h>
#include <ns3/antenna-model.h>

=======
#include "ns3/log.h"
#include "ns3/spectrum-value.h"
#include "ns3/mobility-model.h"
#include "ns3/net-device.h"
>>>>>>> origin
#include "wifi-spectrum-phy-interface.h"
#include "spectrum-wifi-phy.h"

NS_LOG_COMPONENT_DEFINE ("WifiSpectrumPhyInterface");

namespace ns3 {

NS_OBJECT_ENSURE_REGISTERED (WifiSpectrumPhyInterface);

TypeId
WifiSpectrumPhyInterface::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::WifiSpectrumPhyInterface")
    .SetParent<SpectrumPhy> ()
    .SetGroupName ("Wifi");
  return tid;
}

WifiSpectrumPhyInterface::WifiSpectrumPhyInterface ()
{
  NS_LOG_FUNCTION (this);
}

void
WifiSpectrumPhyInterface::DoDispose (void)
{
  NS_LOG_FUNCTION (this);
  m_spectrumWifiPhy = 0;
  m_netDevice = 0;
  m_channel = 0;
}

<<<<<<< HEAD
void WifiSpectrumPhyInterface::SetSpectrumWifiPhy (Ptr<SpectrumWifiPhy> spectrumWifiPhy)
=======
void WifiSpectrumPhyInterface::SetSpectrumWifiPhy (const Ptr<SpectrumWifiPhy> spectrumWifiPhy)
>>>>>>> origin
{
  m_spectrumWifiPhy = spectrumWifiPhy;
}

Ptr<NetDevice>
WifiSpectrumPhyInterface::GetDevice () const
{
  return m_netDevice;
}

Ptr<MobilityModel>
<<<<<<< HEAD
WifiSpectrumPhyInterface::GetMobility ()
=======
WifiSpectrumPhyInterface::GetMobility () const
>>>>>>> origin
{
  return m_spectrumWifiPhy->GetMobility ();
}

void
<<<<<<< HEAD
WifiSpectrumPhyInterface::SetDevice (Ptr<NetDevice> d)
=======
WifiSpectrumPhyInterface::SetDevice (const Ptr<NetDevice> d)
>>>>>>> origin
{
  m_netDevice = d;
}

void
<<<<<<< HEAD
WifiSpectrumPhyInterface::SetMobility (Ptr<MobilityModel> m)
=======
WifiSpectrumPhyInterface::SetMobility (const Ptr<MobilityModel> m)
>>>>>>> origin
{
  m_spectrumWifiPhy->SetMobility (m);
}

void
<<<<<<< HEAD
WifiSpectrumPhyInterface::SetChannel (Ptr<SpectrumChannel> c)
=======
WifiSpectrumPhyInterface::SetChannel (const Ptr<SpectrumChannel> c)
>>>>>>> origin
{
  NS_LOG_FUNCTION (this << c);
  m_channel = c;
}

Ptr<const SpectrumModel>
WifiSpectrumPhyInterface::GetRxSpectrumModel () const
{
  return m_spectrumWifiPhy->GetRxSpectrumModel ();
}

Ptr<AntennaModel>
<<<<<<< HEAD
WifiSpectrumPhyInterface::GetRxAntenna (void)
=======
WifiSpectrumPhyInterface::GetRxAntenna (void) const
>>>>>>> origin
{
  NS_LOG_FUNCTION (this);
  return m_spectrumWifiPhy->GetRxAntenna ();
}

void
WifiSpectrumPhyInterface::StartRx (Ptr<SpectrumSignalParameters> params)
{
  m_spectrumWifiPhy->StartRx (params);
}

<<<<<<< HEAD

=======
>>>>>>> origin
} //namespace ns3

/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2016
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
 * Author: Sébastien Deronne <sebastien.deronne@gmail.com>
 */

<<<<<<< HEAD
#include "wifi-mac-helper.h"
#include "ns3/wifi-mac.h"
#include "ns3/pointer.h"
#include "ns3/boolean.h"
#include "ns3/dca-txop.h"
=======
#include "ns3/net-device.h"
#include "wifi-mac-helper.h"
#include "ns3/frame-exchange-manager.h"
#include "ns3/wifi-protection-manager.h"
#include "ns3/wifi-ack-manager.h"
#include "ns3/multi-user-scheduler.h"
#include "ns3/boolean.h"
>>>>>>> origin

namespace ns3 {

WifiMacHelper::WifiMacHelper ()
{
  //By default, we create an AdHoc MAC layer without QoS.
  SetType ("ns3::AdhocWifiMac",
           "QosSupported", BooleanValue (false));
<<<<<<< HEAD
=======

  m_protectionManager.SetTypeId ("ns3::WifiDefaultProtectionManager");
  m_ackManager.SetTypeId ("ns3::WifiDefaultAckManager");
>>>>>>> origin
}

WifiMacHelper::~WifiMacHelper ()
{
}

<<<<<<< HEAD
void
WifiMacHelper::SetType (std::string type,
                        std::string n0, const AttributeValue &v0,
                        std::string n1, const AttributeValue &v1,
                        std::string n2, const AttributeValue &v2,
                        std::string n3, const AttributeValue &v3,
                        std::string n4, const AttributeValue &v4,
                        std::string n5, const AttributeValue &v5,
                        std::string n6, const AttributeValue &v6,
                        std::string n7, const AttributeValue &v7,
                        std::string n8, const AttributeValue &v8,
                        std::string n9, const AttributeValue &v9,
                        std::string n10, const AttributeValue &v10)
{
  m_mac.SetTypeId (type);
  m_mac.Set (n0, v0);
  m_mac.Set (n1, v1);
  m_mac.Set (n2, v2);
  m_mac.Set (n3, v3);
  m_mac.Set (n4, v4);
  m_mac.Set (n5, v5);
  m_mac.Set (n6, v6);
  m_mac.Set (n7, v7);
  m_mac.Set (n8, v8);
  m_mac.Set (n9, v9);
  m_mac.Set (n10, v10);
}

Ptr<WifiMac>
WifiMacHelper::Create (void) const
{
  Ptr<WifiMac> mac = m_mac.Create<WifiMac> ();
=======
Ptr<WifiMac>
WifiMacHelper::Create (Ptr<NetDevice> device, WifiStandard standard) const
{
  auto standardIt = wifiStandards.find (standard);
  NS_ABORT_MSG_IF (standardIt == wifiStandards.end (), "Selected standard is not defined!");

  Ptr<WifiMac> mac = m_mac.Create<WifiMac> ();
  mac->SetDevice (device);
  mac->SetAddress (Mac48Address::Allocate ());
  mac->ConfigureStandard (standard);

  Ptr<RegularWifiMac> wifiMac = DynamicCast<RegularWifiMac> (mac);
  Ptr<FrameExchangeManager> fem;

  if (wifiMac != 0 && (fem = wifiMac->GetFrameExchangeManager ()) != 0)
    {
      Ptr<WifiProtectionManager> protectionManager = m_protectionManager.Create<WifiProtectionManager> ();
      protectionManager->SetWifiMac (wifiMac);
      fem->SetProtectionManager (protectionManager);

      Ptr<WifiAckManager> ackManager = m_ackManager.Create<WifiAckManager> ();
      ackManager->SetWifiMac (wifiMac);
      fem->SetAckManager (ackManager);

      // create and install the Multi User Scheduler if this is an HE AP
      Ptr<ApWifiMac> apMac = DynamicCast<ApWifiMac> (mac);
      if (apMac != nullptr && standardIt->second.macStandard >= WIFI_MAC_STANDARD_80211ax
          && m_muScheduler.IsTypeIdSet ())
        {
          Ptr<MultiUserScheduler> muScheduler = m_muScheduler.Create<MultiUserScheduler> ();
          apMac->AggregateObject (muScheduler);
        }
    }
>>>>>>> origin
  return mac;
}

} //namespace ns3

/* -*-  Mode: C++; c-file-style: "gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2015, IMDEA Networks Institute
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
 * Author: Hany Assasa <hany.assasa@gmail.com>
.*
 * This is a simple example to test TCP over 802.11n (with MPDU aggregation enabled).
 *
 * Network topology:
 *
 *   Ap    STA
 *   *      *
 *   |      |
 *   n1     n2
 *
<<<<<<< HEAD
 * In this example, an HT station sends TCP packets to the access point. 
 * We report the total throughput received during a window of 100ms. 
=======
 * In this example, an HT station sends TCP packets to the access point.
 * We report the total throughput received during a window of 100ms.
>>>>>>> origin
 * The user can specify the application data rate and choose the variant
 * of TCP i.e. congestion control algorithm to use.
 */

<<<<<<< HEAD
#include "ns3/applications-module.h"
#include "ns3/core-module.h"
#include "ns3/internet-module.h"
#include "ns3/mobility-module.h"
#include "ns3/network-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/wifi-module.h"
=======
#include "ns3/command-line.h"
#include "ns3/config.h"
#include "ns3/string.h"
#include "ns3/log.h"
#include "ns3/yans-wifi-helper.h"
#include "ns3/ssid.h"
#include "ns3/mobility-helper.h"
#include "ns3/on-off-helper.h"
#include "ns3/yans-wifi-channel.h"
#include "ns3/mobility-model.h"
#include "ns3/packet-sink.h"
#include "ns3/packet-sink-helper.h"
#include "ns3/tcp-westwood.h"
#include "ns3/internet-stack-helper.h"
#include "ns3/ipv4-address-helper.h"
#include "ns3/ipv4-global-routing-helper.h"
>>>>>>> origin

NS_LOG_COMPONENT_DEFINE ("wifi-tcp");

using namespace ns3;

Ptr<PacketSink> sink;                         /* Pointer to the packet sink application */
uint64_t lastTotalRx = 0;                     /* The value of the last total received bytes */

void
CalculateThroughput ()
{
  Time now = Simulator::Now ();                                         /* Return the simulator's virtual time. */
<<<<<<< HEAD
  double cur = (sink->GetTotalRx() - lastTotalRx) * (double) 8/1e5;     /* Convert Application RX Packets to MBits. */
=======
  double cur = (sink->GetTotalRx () - lastTotalRx) * (double) 8 / 1e5;     /* Convert Application RX Packets to MBits. */
>>>>>>> origin
  std::cout << now.GetSeconds () << "s: \t" << cur << " Mbit/s" << std::endl;
  lastTotalRx = sink->GetTotalRx ();
  Simulator::Schedule (MilliSeconds (100), &CalculateThroughput);
}

int
<<<<<<< HEAD
main(int argc, char *argv[])
{
  uint32_t payloadSize = 1472;                       /* Transport layer payload size in bytes. */
  std::string dataRate = "100Mbps";                  /* Application layer datarate. */
  std::string tcpVariant = "ns3::TcpNewReno";        /* TCP variant type. */
=======
main (int argc, char *argv[])
{
  uint32_t payloadSize = 1472;                       /* Transport layer payload size in bytes. */
  std::string dataRate = "100Mbps";                  /* Application layer datarate. */
  std::string tcpVariant = "TcpNewReno";             /* TCP variant type. */
>>>>>>> origin
  std::string phyRate = "HtMcs7";                    /* Physical layer bitrate. */
  double simulationTime = 10;                        /* Simulation time in seconds. */
  bool pcapTracing = false;                          /* PCAP Tracing is enabled or not. */

  /* Command line argument parser setup. */
<<<<<<< HEAD
  CommandLine cmd;
  cmd.AddValue ("payloadSize", "Payload size in bytes", payloadSize);
  cmd.AddValue ("dataRate", "Application data ate", dataRate);
  cmd.AddValue ("tcpVariant", "Transport protocol to use: TcpTahoe, TcpReno, TcpNewReno, TcpWestwood, TcpWestwoodPlus ", tcpVariant);
=======
  CommandLine cmd (__FILE__);
  cmd.AddValue ("payloadSize", "Payload size in bytes", payloadSize);
  cmd.AddValue ("dataRate", "Application data ate", dataRate);
  cmd.AddValue ("tcpVariant", "Transport protocol to use: TcpNewReno, "
                "TcpHybla, TcpHighSpeed, TcpHtcp, TcpVegas, TcpScalable, TcpVeno, "
                "TcpBic, TcpYeah, TcpIllinois, TcpWestwood, TcpWestwoodPlus, TcpLedbat ", tcpVariant);
>>>>>>> origin
  cmd.AddValue ("phyRate", "Physical layer bitrate", phyRate);
  cmd.AddValue ("simulationTime", "Simulation time in seconds", simulationTime);
  cmd.AddValue ("pcap", "Enable/disable PCAP Tracing", pcapTracing);
  cmd.Parse (argc, argv);

<<<<<<< HEAD
  /* No fragmentation and no RTS/CTS */
  Config::SetDefault ("ns3::WifiRemoteStationManager::FragmentationThreshold", StringValue ("999999"));
  Config::SetDefault ("ns3::WifiRemoteStationManager::RtsCtsThreshold", StringValue ("999999"));
=======
  tcpVariant = std::string ("ns3::") + tcpVariant;
  // Select TCP variant
  if (tcpVariant.compare ("ns3::TcpWestwoodPlus") == 0)
    {
      // TcpWestwoodPlus is not an actual TypeId name; we need TcpWestwood here
      Config::SetDefault ("ns3::TcpL4Protocol::SocketType", TypeIdValue (TcpWestwood::GetTypeId ()));
      // the default protocol type in ns3::TcpWestwood is WESTWOOD
      Config::SetDefault ("ns3::TcpWestwood::ProtocolType", EnumValue (TcpWestwood::WESTWOODPLUS));
    }
  else
    {
      TypeId tcpTid;
      NS_ABORT_MSG_UNLESS (TypeId::LookupByNameFailSafe (tcpVariant, &tcpTid), "TypeId " << tcpVariant << " not found");
      Config::SetDefault ("ns3::TcpL4Protocol::SocketType", TypeIdValue (TypeId::LookupByName (tcpVariant)));
    }
>>>>>>> origin

  /* Configure TCP Options */
  Config::SetDefault ("ns3::TcpSocket::SegmentSize", UintegerValue (payloadSize));

  WifiMacHelper wifiMac;
  WifiHelper wifiHelper;
<<<<<<< HEAD
  wifiHelper.SetStandard (WIFI_PHY_STANDARD_80211n_5GHZ);

  /* Set up Legacy Channel */
  YansWifiChannelHelper wifiChannel ;
=======
  wifiHelper.SetStandard (WIFI_STANDARD_80211n_5GHZ);

  /* Set up Legacy Channel */
  YansWifiChannelHelper wifiChannel;
>>>>>>> origin
  wifiChannel.SetPropagationDelay ("ns3::ConstantSpeedPropagationDelayModel");
  wifiChannel.AddPropagationLoss ("ns3::FriisPropagationLossModel", "Frequency", DoubleValue (5e9));

  /* Setup Physical Layer */
<<<<<<< HEAD
  YansWifiPhyHelper wifiPhy = YansWifiPhyHelper::Default ();
  wifiPhy.SetChannel (wifiChannel.Create ());
  wifiPhy.Set ("TxPowerStart", DoubleValue (10.0));
  wifiPhy.Set ("TxPowerEnd", DoubleValue (10.0));
  wifiPhy.Set ("TxPowerLevels", UintegerValue (1));
  wifiPhy.Set ("TxGain", DoubleValue (0));
  wifiPhy.Set ("RxGain", DoubleValue (0));
  wifiPhy.Set ("RxNoiseFigure", DoubleValue (10));
  wifiPhy.Set ("CcaMode1Threshold", DoubleValue (-79));
  wifiPhy.Set ("EnergyDetectionThreshold", DoubleValue (-79 + 3));
=======
  YansWifiPhyHelper wifiPhy;
  wifiPhy.SetChannel (wifiChannel.Create ());
>>>>>>> origin
  wifiPhy.SetErrorRateModel ("ns3::YansErrorRateModel");
  wifiHelper.SetRemoteStationManager ("ns3::ConstantRateWifiManager",
                                      "DataMode", StringValue (phyRate),
                                      "ControlMode", StringValue ("HtMcs0"));

  NodeContainer networkNodes;
  networkNodes.Create (2);
  Ptr<Node> apWifiNode = networkNodes.Get (0);
  Ptr<Node> staWifiNode = networkNodes.Get (1);

  /* Configure AP */
  Ssid ssid = Ssid ("network");
  wifiMac.SetType ("ns3::ApWifiMac",
<<<<<<< HEAD
                    "Ssid", SsidValue (ssid));
=======
                   "Ssid", SsidValue (ssid));
>>>>>>> origin

  NetDeviceContainer apDevice;
  apDevice = wifiHelper.Install (wifiPhy, wifiMac, apWifiNode);

  /* Configure STA */
  wifiMac.SetType ("ns3::StaWifiMac",
<<<<<<< HEAD
                    "Ssid", SsidValue (ssid));
=======
                   "Ssid", SsidValue (ssid));
>>>>>>> origin

  NetDeviceContainer staDevices;
  staDevices = wifiHelper.Install (wifiPhy, wifiMac, staWifiNode);

  /* Mobility model */
  MobilityHelper mobility;
  Ptr<ListPositionAllocator> positionAlloc = CreateObject<ListPositionAllocator> ();
  positionAlloc->Add (Vector (0.0, 0.0, 0.0));
  positionAlloc->Add (Vector (1.0, 1.0, 0.0));

  mobility.SetPositionAllocator (positionAlloc);
  mobility.SetMobilityModel ("ns3::ConstantPositionMobilityModel");
  mobility.Install (apWifiNode);
  mobility.Install (staWifiNode);

  /* Internet stack */
  InternetStackHelper stack;
  stack.Install (networkNodes);

  Ipv4AddressHelper address;
  address.SetBase ("10.0.0.0", "255.255.255.0");
  Ipv4InterfaceContainer apInterface;
  apInterface = address.Assign (apDevice);
  Ipv4InterfaceContainer staInterface;
  staInterface = address.Assign (staDevices);

  /* Populate routing table */
  Ipv4GlobalRoutingHelper::PopulateRoutingTables ();

  /* Install TCP Receiver on the access point */
  PacketSinkHelper sinkHelper ("ns3::TcpSocketFactory", InetSocketAddress (Ipv4Address::GetAny (), 9));
  ApplicationContainer sinkApp = sinkHelper.Install (apWifiNode);
  sink = StaticCast<PacketSink> (sinkApp.Get (0));

  /* Install TCP/UDP Transmitter on the station */
  OnOffHelper server ("ns3::TcpSocketFactory", (InetSocketAddress (apInterface.GetAddress (0), 9)));
  server.SetAttribute ("PacketSize", UintegerValue (payloadSize));
  server.SetAttribute ("OnTime", StringValue ("ns3::ConstantRandomVariable[Constant=1]"));
  server.SetAttribute ("OffTime", StringValue ("ns3::ConstantRandomVariable[Constant=0]"));
  server.SetAttribute ("DataRate", DataRateValue (DataRate (dataRate)));
  ApplicationContainer serverApp = server.Install (staWifiNode);

  /* Start Applications */
  sinkApp.Start (Seconds (0.0));
  serverApp.Start (Seconds (1.0));
  Simulator::Schedule (Seconds (1.1), &CalculateThroughput);

  /* Enable Traces */
  if (pcapTracing)
    {
<<<<<<< HEAD
      wifiPhy.SetPcapDataLinkType (YansWifiPhyHelper::DLT_IEEE802_11_RADIO);
=======
      wifiPhy.SetPcapDataLinkType (WifiPhyHelper::DLT_IEEE802_11_RADIO);
>>>>>>> origin
      wifiPhy.EnablePcap ("AccessPoint", apDevice);
      wifiPhy.EnablePcap ("Station", staDevices);
    }

  /* Start Simulation */
  Simulator::Stop (Seconds (simulationTime + 1));
  Simulator::Run ();
<<<<<<< HEAD
  Simulator::Destroy ();

  double averageThroughput = ((sink->GetTotalRx() * 8) / (1e6  * simulationTime));
=======

  double averageThroughput = ((sink->GetTotalRx () * 8) / (1e6 * simulationTime));

  Simulator::Destroy ();

>>>>>>> origin
  if (averageThroughput < 50)
    {
      NS_LOG_ERROR ("Obtained throughput is not in the expected boundaries!");
      exit (1);
    }
<<<<<<< HEAD
  std::cout << "\nAverage throughtput: " << averageThroughput << " Mbit/s" << std::endl;
=======
  std::cout << "\nAverage throughput: " << averageThroughput << " Mbit/s" << std::endl;
>>>>>>> origin
  return 0;
}

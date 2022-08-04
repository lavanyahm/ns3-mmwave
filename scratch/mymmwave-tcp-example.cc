/* -*-  Mode: C++; c-file-style: "gnu"; indent-tabs-mode:nil; -*- */
/*
*   Copyright (c) 2011 Centre Tecnologic de Telecomunicacions de Catalunya (CTTC)
*   Copyright (c) 2015, NYU WIRELESS, Tandon School of Engineering, New York University
*
*   This program is free software; you can redistribute it and/or modify
*   it under the terms of the GNU General Public License version 2 as
*   published by the Free Software Foundation;
*
*   This program is distributed in the hope that it will be useful,
*   but WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*   GNU General Public License for more details.
*
*   You should have received a copy of the GNU General Public License
*   along with this program; if not, write to the Free Software
*   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*
*   Author: Marco Miozzo <marco.miozzo@cttc.es>
*           Nicola Baldo  <nbaldo@cttc.es>
*
*   Modified by: Marco Mezzavilla < mezzavilla@nyu.edu>
*                         Sourjya Dutta <sdutta@nyu.edu>
*                         Russell Ford <russell.ford@nyu.edu>
*                         Menglei Zhang <menglei@nyu.edu>
*/
#include "ns3/log.h"
#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/mobility-module.h"
#include "ns3/config-store.h"
#include "ns3/mmwave-helper.h"
#include "ns3/mmwave-point-to-point-epc-helper.h"
#include <ns3/buildings-helper.h>
#include "ns3/global-route-manager.h"
#include "ns3/ipv4-global-routing-helper.h"
#include "ns3/internet-module.h"
#include "ns3/applications-module.h"
#include <ns3/buildings-module.h>
#include "ns3/internet-module.h"
#include "ns3/point-to-point-helper.h"
#include "ns3/applications-module.h"


using namespace ns3;
using namespace mmwave;

/**
 * A script to simulate the DOWNLINK TCP data over mmWave links
 * with the mmWave devices and the LTE EPC.
 */
NS_LOG_COMPONENT_DEFINE ("mmWaveTCPExample");


class MyApp : public Application
{
public:
  MyApp ();
  virtual ~MyApp ();

  void Setup (Ptr<Socket> socket, Address address, uint32_t packetSize, uint32_t nPackets, DataRate dataRate);

private:
  virtual void StartApplication (void);
  virtual void StopApplication (void);

  void ScheduleTx (void);
  void SendPacket (void);

  Ptr<Socket>     m_socket;
  Address         m_peer;
  uint32_t        m_packetSize;
  uint32_t        m_nPackets;
  DataRate        m_dataRate;
  EventId         m_sendEvent;
  bool            m_running;
  uint32_t        m_packetsSent;
};

MyApp::MyApp ()
  : m_socket (0),
    m_peer (),
    m_packetSize (0),
    m_nPackets (0),
    m_dataRate (0),
    m_sendEvent (),
    m_running (false),
    m_packetsSent (0)
{
}

MyApp::~MyApp ()
{
  m_socket = 0;
}

void
MyApp::Setup (Ptr<Socket> socket, Address address, uint32_t packetSize, uint32_t nPackets, DataRate dataRate)
{
  m_socket = socket;
  m_peer = address;
  m_packetSize = packetSize;
  m_nPackets = nPackets;
  m_dataRate = dataRate;
}

void
MyApp::StartApplication (void)
{
  m_running = true;
  m_packetsSent = 0;
  m_socket->Bind ();
  m_socket->Connect (m_peer);
  SendPacket ();
}

void
MyApp::StopApplication (void)
{
  m_running = false;

  if (m_sendEvent.IsRunning ())
    {
      Simulator::Cancel (m_sendEvent);
    }

  if (m_socket)
    {
      m_socket->Close ();
    }
}

void
MyApp::SendPacket (void)
{
  static int send_num = 1;
  Ptr<Packet> packet = Create<Packet> (m_packetSize);
  m_socket->Send (packet);
  NS_LOG_DEBUG ("Sending:    " << send_num++ << "\t" << Simulator::Now ().GetSeconds ());

  if (++m_packetsSent < m_nPackets)
    {
      ScheduleTx ();
    }
}


void
MyApp::ScheduleTx (void)
{
  if (m_running)
    {
      Time tNext (Seconds (m_packetSize * 8 / static_cast<double> (m_dataRate.GetBitRate ())));
      m_sendEvent = Simulator::Schedule (tNext, &MyApp::SendPacket, this);
    }
}

static void Rx (Ptr<OutputStreamWrapper> stream, Ptr<const Packet> packet, const Address &from)
{
  *stream->GetStream () << Simulator::Now ().GetSeconds () << "\t" << packet->GetSize () << std::endl;
}
static void
CwndChange (Ptr<OutputStreamWrapper> stream, uint32_t oldCwnd, uint32_t newCwnd)
{
  *stream->GetStream () << Simulator::Now ().GetSeconds () << "\t" << oldCwnd << "\t" << newCwnd << std::endl;
}

static void
estimatedRTT (Ptr<OutputStreamWrapper> stream, Time oldRTT, Time newRTT)
{
 // *stream->GetStream () << Simulator::Now ().GetSeconds () << "\t" << oldRTT << "\t" << Seconds(newRTT) << std::endl;
   *stream->GetStream () << Simulator::Now ().GetSeconds () << "\t" << newRTT.GetSeconds ()<< std::endl;
}

static void
EstimatedBytesInFlight (Ptr<OutputStreamWrapper> stream, uint32_t  oldEst, uint32_t  newEst)
{
  *stream->GetStream () << Simulator::Now ().GetSeconds () << "\t" <<newEst << std::endl;
}

/*Ue moving */
void
ChangeSpeed (Ptr<Node> n, Vector speed)
{
  n->GetObject<ConstantVelocityMobilityModel> ()->SetVelocity (speed);
  NS_LOG_UNCOND ("************************--------------------Change Speed-------------------------------*****************");
}


int
main (int argc, char *argv[])
{

  /*Config::SetDefault ("ns3::LteRlcUm::MaxTxBufferSize", UintegerValue (10 * 1024 * 1024));
  Config::SetDefault ("ns3::LteRlcAm::MaxTxBufferSize", UintegerValue (10 * 1024 * 1024));
  Config::SetDefault ("ns3::LteRlcUmLowLat::MaxTxBufferSize", UintegerValue (10 * 1024 * 1024));*/
  Config::SetDefault ("ns3::DropTailQueue<Packet>::MaxSize", QueueSizeValue (QueueSize (QueueSize ("50000p"))));

  Config::SetDefault ("ns3::LteRlcUm::MaxTxBufferSize", UintegerValue (50 * 1024 *1024));//RLC queue length 50 packets
  Config::SetDefault ("ns3::LteRlcAm::MaxTxBufferSize", UintegerValue (50 * 1024 *1024) );
  Config::SetDefault ("ns3::LteRlcUmLowLat::MaxTxBufferSize", UintegerValue (50 * 1024*1024));
  // TCP settings
  Config::SetDefault ("ns3::TcpL4Protocol::SocketType", TypeIdValue (TcpCubic::GetTypeId ()));
  Config::SetDefault ("ns3::TcpSocketBase::MinRto", TimeValue (MilliSeconds (200)));
  Config::SetDefault ("ns3::Ipv4L3Protocol::FragmentExpirationTimeout", TimeValue (Seconds (0.2)));
  Config::SetDefault ("ns3::TcpSocket::SegmentSize", UintegerValue (2500));
  Config::SetDefault ("ns3::TcpSocket::DelAckCount", UintegerValue (0));//Setting the DelAckCount attribute to 0 disables delayed ACKs
  Config::SetDefault ("ns3::TcpSocket::SndBufSize", UintegerValue (131072*100));
  Config::SetDefault ("ns3::TcpSocket::RcvBufSize", UintegerValue (131072*100));

  CommandLine cmd;
  cmd.Parse (argc, argv);

  double totalBandwidth = 13.88e6;//SubbandWidth
  double frequency0 = 28e9;//value from Paper//CenterFreq
  double frequency1 = 73e9;
  double stopTime = 8;
  double simStopTime = 10;
  bool useCa = false;
  std::string condition = "l"; // channel condition, l = LOS, n = NLOS, otherwise the condition is randomly determined

  Ptr<MmWaveHelper> ptr_mmWave = CreateObject<MmWaveHelper> ();
  ptr_mmWave->SetSchedulerType ("ns3::MmWaveFlexTtiMacScheduler");
  Ptr<MmWavePointToPointEpcHelper>  ptr_epcHelper =  CreateObject<MmWavePointToPointEpcHelper>();
  ptr_mmWave->SetEpcHelper (ptr_epcHelper);
  ConfigStore inputConfig;
  inputConfig.ConfigureDefaults ();
  cmd.Parse (argc, argv);

  //Create Pgw
  Ptr<Node> pgw = ptr_epcHelper->GetPgwNode ();

  // Create a single RemoteHost
  NodeContainer remoteHostContainer;
  remoteHostContainer.Create (1);
  Ptr<Node> remoteHost = remoteHostContainer.Get (0);
  InternetStackHelper internet;
  internet.Install (remoteHostContainer);

  // Create the Internet
  PointToPointHelper p2ph;
  p2ph.SetDeviceAttribute ("DataRate", DataRateValue (DataRate ("100Gb/s")));
  p2ph.SetDeviceAttribute ("Mtu", UintegerValue (1500));
  p2ph.SetChannelAttribute ("Delay", TimeValue (MilliSeconds (40)));
  NetDeviceContainer internetDevices = p2ph.Install (pgw, remoteHost);
  Ipv4AddressHelper ipv4h;
  ipv4h.SetBase ("1.0.0.0", "255.0.0.0");
  Ipv4InterfaceContainer internetIpIfaces = ipv4h.Assign (internetDevices);
  // interface 0 is localhost, 1 is the p2p device
  Ipv4Address remoteHostAddr;
  remoteHostAddr = internetIpIfaces.GetAddress (1);
  Ipv4StaticRoutingHelper ipv4RoutingHelper;
  Ptr<Ipv4StaticRouting> remoteHostStaticRouting = ipv4RoutingHelper.GetStaticRouting (remoteHost->GetObject<Ipv4> ());
  remoteHostStaticRouting->AddNetworkRouteTo (Ipv4Address ("7.0.0.0"), Ipv4Mask ("255.0.0.0"), 1);
  //Create Ue and eNB
  NodeContainer enbNodes;
  NodeContainer ueNodes;
  enbNodes.Create (1);
  ueNodes.Create (1);

  MobilityHelper enbmobility;
  Ptr<ListPositionAllocator> enbPositionAlloc = CreateObject<ListPositionAllocator> ();
  enbPositionAlloc->Add (Vector (0.0, 0.0, 25.0));
  enbmobility.SetMobilityModel ("ns3::ConstantPositionMobilityModel");
  enbmobility.SetPositionAllocator (enbPositionAlloc);
  enbmobility.Install (enbNodes);
  BuildingsHelper::Install (enbNodes);


  Ptr<ListPositionAllocator> uePositionAlloc = CreateObject<ListPositionAllocator> ();
  uePositionAlloc->Add (Vector (10.0, 20.0, 0.0));


  if (condition == "l")
    {
      ptr_mmWave->SetChannelConditionModelType ("ns3::AlwaysLosChannelConditionModel");
      ptr_mmWave->SetPathlossModelType ("ns3::ThreeGppUmiStreetCanyonPropagationLossModel");
    }
  else if (condition == "n")
    {
      ptr_mmWave->SetPathlossModelType ("ns3::ThreeGppBuildingPropagationLossModel");
      ptr_mmWave->SetChannelConditionModelType ("ns3::NeverLosChannelConditionModel");
    }
  /*Creating Obstracile*/
  double x_min_1 = 40.0,    x_min_2 = 50.0,     x_min_3 = 60.0;
  double x_max_1 = 40.3048, x_max_2 = 50.3048,  x_max_3 = 60.30;//1 feet =.3048m
  double y_min_1 = 0.0,     y_min_2 = 0.0,      y_min_3 = 0.0;
  double y_max_1 = 0.0,     y_max_2 = 0.0,      y_max_3 = 0.0;
  double z_min_1 = 0.0,     z_min_2 = 0.0,      z_min_3 = 0.0;
  double z_max_1 = 1.0668/*3.5 feet*/, z_max_2 = 1.2192 /*4 feet*/,  z_max_3 = 1.524/*5 feet*/;


  Ptr < Building > building1;
  building1 = Create<Building> ();
  building1->SetBoundaries (Box (x_min_1, x_max_1, y_min_1, y_max_1, z_min_1, z_max_1));
  building1->SetBuildingType (Building::Residential);


  Ptr < Building > building2;
  building2 = Create<Building> ();
  building2->SetBoundaries (Box (x_min_2, x_max_2, y_min_2, y_max_2, z_min_2, z_max_2));
  building2->SetBuildingType (Building::Residential);

  Ptr < Building > building3;
  building3 = Create<Building> ();
  building3->SetBoundaries (Box (x_min_3, x_max_3, y_min_3, y_max_3, z_min_3, z_max_3));
  building3->SetBuildingType (Building::Residential);

  MobilityHelper uemobility;
  uemobility.SetMobilityModel ("ns3::ConstantVelocityMobilityModel");
  uemobility.SetPositionAllocator (uePositionAlloc);
  uemobility.Install (ueNodes);
  Simulator::Schedule (Seconds (2), &ChangeSpeed, ueNodes.Get (0), Vector (1, 0.0, 0)); // start UE movement
  BuildingsHelper::Install (ueNodes);
  NetDeviceContainer enbNetDev = ptr_mmWave->InstallEnbDevice (enbNodes);
  NetDeviceContainer ueNetDev = ptr_mmWave->InstallUeDevice (ueNodes);

  // Install the IP stack on the UEs
  // Assign IP address to UEs, and install applications
  internet.Install (ueNodes);
  Ipv4InterfaceContainer ueIpIface;
  ueIpIface = ptr_epcHelper->AssignUeIpv4Address (NetDeviceContainer (ueNetDev));
  ptr_mmWave->AttachToClosestEnb (ueNetDev, enbNetDev);
  ptr_mmWave->EnableTraces ();
  // CC 0
  // 1. create MmWavePhyMacCommon object
  Ptr<MmWavePhyMacCommon> phyMacConfig0 = CreateObject<MmWavePhyMacCommon> ();
  phyMacConfig0->SetBandwidth (totalBandwidth );
  phyMacConfig0->SetCentreFrequency (frequency0);
  phyMacConfig0->SetNumReferenceSymbols (6);
  phyMacConfig0->SetSlotPerSubframe (8);
  phyMacConfig0->SetSubframePerFrame (10);
  phyMacConfig0->SetSymbolPeriod (MicroSeconds (4.16));
  phyMacConfig0->SetSymbPerSlot (30);
  // 2. create the MmWaveComponentCarrier object
  Ptr<MmWaveComponentCarrier> cc0 = CreateObject<MmWaveComponentCarrier> ();
  cc0->SetConfigurationParameters (phyMacConfig0);
  cc0->SetAsPrimary (true);

  // CC 1
  Ptr<MmWaveComponentCarrier> cc1;
  if (useCa)
    {
      // 1. create MmWavePhyMacCommon object
      Ptr<MmWavePhyMacCommon> phyMacConfig1 = CreateObject<MmWavePhyMacCommon> ();
      phyMacConfig1->SetBandwidth (totalBandwidth / 2);
      phyMacConfig1->SetCentreFrequency (frequency1);
      phyMacConfig1->SetCcId (1);

      // 2. create the MmWaveComponentCarrier object
      cc1 = CreateObject<MmWaveComponentCarrier> ();
      cc1->SetConfigurationParameters (phyMacConfig1);
      cc1->SetAsPrimary (false);
    }
  // create the CC map
  std::map<uint8_t, MmWaveComponentCarrier> ccMap;
  ccMap [0] = *cc0;
  if (useCa)
    {
      ccMap [1] = *cc1;
    }

  ptr_mmWave->SetCcPhyParams (ccMap);
  ptr_mmWave->Initialize ();
#if 0
  to checkassert failed. cond="bearerId == 0 || bid == bearerId", msg="bearer ID mismatch (2 != 1, the assumption that ID are allocated in the same way by MME and RRC is not valid any more", +0.033267999s 3 file=../src/lte/model/lte-enb-rrc.cc, line=439

      // Activate a data radio bearer
      enum EpsBearer::Qci q = EpsBearer::GBR_CONV_VOICE;
  EpsBearer bearer (q);
  ptr_mmWave->ActivateDataRadioBearer (ueNetDev, bearer);
#endif
  // Set the default gateway for the UE
  Ptr<Node> ueNode = ueNodes.Get (0);
  Ptr<Ipv4StaticRouting> ueStaticRouting = ipv4RoutingHelper.GetStaticRouting (ueNode->GetObject<Ipv4> ());
  ueStaticRouting->SetDefaultRoute (ptr_epcHelper->GetUeDefaultGatewayAddress (), 1);


  // Install and start applications on UEs and remote host
  uint16_t sinkPort = 20000;

  Address sinkAddress (InetSocketAddress (ueIpIface.GetAddress (0), sinkPort));
  PacketSinkHelper packetSinkHelper ("ns3::TcpSocketFactory", InetSocketAddress (Ipv4Address::GetAny (), sinkPort));
  ApplicationContainer sinkApps = packetSinkHelper.Install (ueNodes.Get (0));
  sinkApps.Start (Seconds (0.));
  sinkApps.Stop (Seconds (simStopTime));

  Ptr<Socket> ns3TcpSocket = Socket::CreateSocket (remoteHostContainer.Get (0), TcpSocketFactory::GetTypeId ());

  Ptr<MyApp> app = CreateObject<MyApp> ();
  app->Setup (ns3TcpSocket, sinkAddress, 1400, 50000000, DataRate ("500Mb/s"));
  remoteHostContainer.Get (0)->AddApplication (app);

  AsciiTraceHelper asciiTraceHelper;
  Ptr<OutputStreamWrapper> stream1 = asciiTraceHelper.CreateFileStream ("mmWave-tcp-window.txt");
  ns3TcpSocket->TraceConnectWithoutContext ("CongestionWindow", MakeBoundCallback (&CwndChange, stream1));

  Ptr<OutputStreamWrapper> stream2 = asciiTraceHelper.CreateFileStream ("mmWave-tcp-data.txt");
  sinkApps.Get (0)->TraceConnectWithoutContext ("Rx",MakeBoundCallback (&Rx, stream2));
  app->SetStartTime (Seconds (0.1));
  app->SetStopTime (Seconds (stopTime));


  Ptr<OutputStreamWrapper> streamRTT = asciiTraceHelper.CreateFileStream ("Estimated_RTT.dat");
  ns3TcpSocket->TraceConnectWithoutContext ("RTT", MakeBoundCallback (&estimatedRTT, streamRTT));

  Ptr<OutputStreamWrapper> streamBytesInFlight = asciiTraceHelper.CreateFileStream ("Estimated_BytesInFlight.dat");
  ns3TcpSocket->TraceConnectWithoutContext ("BytesInFlight", MakeBoundCallback (&EstimatedBytesInFlight, streamBytesInFlight));

  Simulator::Stop (Seconds (simStopTime));// 20m/s need to reach 100m
  Simulator::Run ();
  Simulator::Destroy ();
  return 0;
}


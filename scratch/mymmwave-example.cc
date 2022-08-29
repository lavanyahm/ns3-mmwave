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
/*This is to simulate the experiment conducted in
 * "5G mmWave Module for ns-3 Network Simulator"
 * Article · June 2015 DOI: 10.1145/2811587.2811619 ·
 * Source: arXiv CITATIONS.
*/

#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/mobility-module.h"
#include "ns3/config-store.h"
#include "ns3/mmwave-helper.h"
#include <ns3/buildings-helper.h>
#include "ns3/global-route-manager.h"
#include "ns3/ipv4-global-routing-helper.h"
#include "ns3/internet-module.h"
#include "ns3/applications-module.h"
#include "ns3/log.h"
#include <ns3/buildings-module.h>
#include "ns3/config-store-module.h"

using namespace ns3;
using namespace mmwave;


NS_LOG_COMPONENT_DEFINE ("mymmWave-example");

#define PrintPositions false
Ptr<PacketSink> sink;                         /* Pointer to the packet sink application */
uint64_t lastTotalRx = 0;
/*Ue moving */
void
ChangeSpeed (Ptr<Node> n, Vector speed)
{
  n->GetObject<ConstantVelocityMobilityModel> ()->SetVelocity (speed);
  // NS_LOG_UNCOND (n->GetObject<ConstantVelocityMobilityModel> ()->GetDistanceFrom());
  //  NS_LOG_UNCOND ("************************--------------------Change Speed-------------------------------*****************");
}
#if 1
void
PrintPosition (Ptr<Node> Uenode,Ptr<Node>enB, Ptr<OutputStreamWrapper> stream)
{

  Ptr<MobilityModel> Ue_model = Uenode->GetObject<MobilityModel> ();
  Ptr<MobilityModel> eNB_model = enB->GetObject<MobilityModel> ();
  *stream->GetStream () << Simulator::Now ().GetSeconds () << "\t" << Ue_model->GetDistanceFrom (eNB_model)<< std::endl;
}

#endif


#if 0
void
CalculateThroughput ()
{
  Time now = Simulator::Now ();                                         /* Return the simulator's virtual time. */
  double cur = (sink->GetTotalRx () - lastTotalRx) * (double) 8 / 1e5;     /* Convert Application RX Packets to MBits. */
  std::cout << now.GetSeconds () << "s: \t" << cur << " Mbit/s" << std::endl;
  lastTotalRx = sink->GetTotalRx ();
  Simulator::Schedule (MilliSeconds (100), &CalculateThroughput);
}
#endif
int
main (int argc, char *argv[])
{
  CommandLine cmd;
  cmd.Parse (argc, argv);

  Config::SetDefault ("ns3::MmWaveEnbPhy::TxPower", DoubleValue (double(30)));
  Config::SetDefault ("ns3::MmWaveEnbPhy::NoiseFigure", DoubleValue (5));

  Ptr<MmWaveHelper> ptr_mmWave = CreateObject<MmWaveHelper> ();
  /* A configuration example.
    * ptr_mmWave->GetCcPhyParams ().at (0).GetConfigurationParameters ()->SetAttribute("SymbolPerSlot", UintegerValue(30));*/
#if PrintPositions
  UintegerValue uintegerValue;
  double ueInitialPosition = 40;
  double ueFinalPosition = 140;

  int windowForTransient = 150; // number of samples for the vector to use in the filter
  //GlobalValue::GetValueByName ("reportTablePeriodicity", uintegerValue);
  int ReportTablePeriodicity = 1600;//(int)uintegerValue.Get (); // in microseconds

  if (ReportTablePeriodicity == 1600)
    {
      windowForTransient = 150;
    }
  else if (ReportTablePeriodicity == 25600)
    {
      windowForTransient = 50;
    }
  else if (ReportTablePeriodicity == 12800)
    {
      windowForTransient = 100;
    }
  else
    {
      // NS_ASSERT_MSG (false, "Unrecognized");
      windowForTransient = 100;
    }


  int vectorTransient = windowForTransient * ReportTablePeriodicity;
  double ueSpeed = 20.0;
  double transientDuration = double(vectorTransient) / 1000000;
  double simTime = transientDuration + ((double)ueFinalPosition - (double)ueInitialPosition) / ueSpeed + 1;
#endif

  /* Configuration setting in the paper 5G mmWave Module for the ns-3 Network Simulator*/

  double totalBandwidth = 13.88e6;//SubbandWidth
  double frequency0 = 28e9;//value from Paper//CenterFreq
  double frequency1 = 73e9;
  bool useCa = false;
  std::string condition = "n"; // channel condition, l = LOS, n = NLOS, otherwise the condition is randomly determined


#if 0
  ptr_mmWave->GetCcPhyParams ().at (0).GetConfigurationParameters ()->SetAttribute ("SlotPerSubFrame",UintegerValue(8));
  ptr_mmWave->GetCcPhyParams ().at (0).GetConfigurationParameters ()->SetAttribute ("SymbolLeghth",TimeValue (MicroSeconds (4.16))  );
  ptr_mmWave->GetCcPhyParams ().at (0).GetConfigurationParameters ()->SetAttribute ("SubframePerFrame",UintegerValue(10));
  ptr_mmWave->GetCcPhyParams ().at (0).GetConfigurationParameters ()->SetAttribute("NumReferenceSymbols", UintegerValue(6));
  ptr_mmWave->GetCcPhyParams ().at (0).GetConfigurationParameters ()->SetAttribute("TDDControlDataPattren", StringValue("ccdddddd"));
  ptr_mmWave->GetCcPhyParams ().at (0).GetConfigurationParameters ()->SetAttribute("SubcarriersPerSubband", UintegerValue(48));
  ptr_mmWave->GetCcPhyParams ().at (0).GetConfigurationParameters ()->SetAttribute("SubbandsPerRB", UintegerValue(18));
  ptr_mmWave->GetCcPhyParams ().at (0).GetConfigurationParameters ()->SetAttribute ("SubbandWidth", DoubleValue(13.89e6));
  ptr_mmWave->GetCcPhyParams ().at (0).GetConfigurationParameters ()->SetAttribute ("NumResourceBlock",UintegerValue(4));
  ptr_mmWave->GetCcPhyParams ().at (0).GetConfigurationParameters ()->SetAttribute ("CenterFreq",DoubleValue(28e9));
  ptr_mmWave->GetCcPhyParams ().at (0).GetConfigurationParameters ()->SetCentreFrequency (28e9);
  ptr_mmWave->GetCcPhyParams ().at (0).GetConfigurationParameters ()->SetNumReferenceSymbols (6);
  ptr_mmWave->GetCcPhyParams ().at (0).GetConfigurationParameters ()->SetSlotPerSubframe (8);
  ptr_mmWave->GetCcPhyParams ().at (0).GetConfigurationParameters ()->SetSubframePerFrame (10);
  ptr_mmWave->GetCcPhyParams ().at (0).GetConfigurationParameters ()->SetSymbolPeriod ((MicroSeconds (4.16)));
# endif

  NodeContainer enbNodes;
  NodeContainer ueNodes;
  enbNodes.Create (1);
  ueNodes.Create (1);

  Ptr<ListPositionAllocator> enbPositionAlloc = CreateObject<ListPositionAllocator> ();
  enbPositionAlloc->Add (Vector (0.0, 0.0, 0.0));

  MobilityHelper enbmobility;
  enbmobility.SetMobilityModel ("ns3::ConstantPositionMobilityModel");
  enbmobility.SetPositionAllocator (enbPositionAlloc);
  enbmobility.Install (enbNodes);
  BuildingsHelper::Install (enbNodes);


  Ptr<ListPositionAllocator> uePositionAlloc = CreateObject<ListPositionAllocator> ();
  uePositionAlloc->Add (Vector (40.0, 20.0, 0.0));


  if (condition == "l")
    {
      ptr_mmWave->SetChannelConditionModelType ("ns3::AlwaysLosChannelConditionModel");
      ptr_mmWave->SetPathlossModelType ("ns3::ThreeGppUmiStreetCanyonPropagationLossModel");
    }
  else if (condition == "l")
    {
      //ptr_mmWave->SetPathlossModelType (" ns3::ThreeGppBuildingPropagationLossModel");
      ptr_mmWave->SetPathlossModelType ("ns3::ThreeGppUmiStreetCanyonPropagationLossModel");
      ptr_mmWave->SetChannelConditionModelType ("ns3::NeverLosChannelConditionModel");
    }
  double x_min = 0.0;
  double x_max = 40.0;
  double y_min = 20.0;
  double y_max = 50.0;
  double z_min = 0.0;
  double z_max =  1.5;

  Ptr < Building > building1;
  building1 = Create<Building> ();
  building1->SetBoundaries (Box (x_min, x_max, y_min, y_max, z_min, z_max));
  building1->SetBuildingType (Building::Residential);
  building1->SetExtWallsType (Building::ConcreteWithWindows);

  Ptr < Building > building2;
  building2 = Create<Building> ();
  building2->SetBoundaries (Box (0.0,60.5,
                                 9.5, 10.0,
                                 0.0, 1.5));

  Ptr < Building > building3;
  building3 = Create<Building> ();
  building3->SetBoundaries (Box (4.0,60.5,
                                 50.5, 60.0,
                                 0.0, 1.5));
  Ptr < Building > building4;
  building1 = Create<Building> ();
  building1->SetBoundaries (Box (60.0,60.5,
                                 6.0, 6.5,
                                 0.0, 1.5));

  MobilityHelper uemobility;
  uemobility.SetMobilityModel ("ns3::ConstantVelocityMobilityModel");
  uemobility.SetPositionAllocator (uePositionAlloc);
  uemobility.Install (ueNodes);
  Simulator::Schedule (Seconds (0), &ChangeSpeed, ueNodes.Get (0), Vector (20, 0.0, 0)); // start UE movement

  BuildingsHelper::Install (ueNodes);
  NetDeviceContainer enbNetDev = ptr_mmWave->InstallEnbDevice (enbNodes);
  NetDeviceContainer ueNetDev = ptr_mmWave->InstallUeDevice (ueNodes);
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


  AsciiTraceHelper asciiTraceHelper;
  Ptr<OutputStreamWrapper> streamUePosition = asciiTraceHelper.CreateFileStream ("UePosition.dat");


  //   streamUePosition->GetStream () << "Time" << "\t" << "Ue DistanceFrom eNB_model" << std::endl;
#if 0
  double numPrints = 0;
  for (int i = 0; i < numPrints; i++)
    {
        //Simulator::Schedule (Seconds(i * simTime / numPrints), &PrintPosition, ueNodes.Get (0),enbNodes.Get (0),streamUePosition);
        Simulator::Schedule (Seconds((10.0 / numPrints) * i), &PrintPosition, ueNodes.Get (0),enbNodes.Get (0),streamUePosition);
      //   Simulator::Schedule (Seconds (1.1), &CalculateThroughput);
    }

#endif
Simulator::Schedule (Seconds(4), &PrintPosition, ueNodes.Get (0),enbNodes.Get (0),streamUePosition);


  // Activate a data radio bearer
  enum EpsBearer::Qci q = EpsBearer::GBR_CONV_VOICE;
  EpsBearer bearer (q);
  //ptr_mmWave->EnableDlPhyTrace ();

  ptr_mmWave->ActivateDataRadioBearer (ueNetDev, bearer);
  Simulator::Stop (Seconds (10));// 20m/s need to reach 100m
  Simulator::Run ();
  Simulator::Destroy ();
  return 0;
}


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

using namespace ns3;
using namespace mmwave;



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
 CommandLine cmd;
 cmd.Parse (argc, argv);

 /* Information regarding the traces generated:
  *
  * 1. UE_1_SINR.txt : Gives the SINR for each sub-band
  *    Subframe no.  | Slot No. | Sub-band  | SINR (db)
  *
  * 2. UE_1_Tb_size.txt : Allocated transport block size
  *    Time (micro-sec)  |  Tb-size in bytes
  * */


 Config::SetDefault ("ns3::MmWaveEnbPhy::TxPower", DoubleValue (double(30)));
 Config::SetDefault ("ns3::MmWaveEnbPhy::NoiseFigure", DoubleValue (5));

 Ptr<MmWaveHelper> ptr_mmWave = CreateObject<MmWaveHelper> ();
 /* A configuration example.
    * ptr_mmWave->GetCcPhyParams ().at (0).GetConfigurationParameters ()->SetAttribute("SymbolPerSlot", UintegerValue(30));*/

/* Configuration setting in the paper 5G mmWave Module for the ns-3 Network Simulator*/

 double totalBandwidth = 13.88e6;//SubbandWidth
 double frequency0 = 28e9;//value from Paper//CenterFreq
 double frequency1 = 73e9;
 bool useCa = false;
 std::string condition = "l"; // channel condition, l = LOS, n = NLOS, otherwise the condition is randomly determined


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
 else if (condition == "n")
 {
   ptr_mmWave->SetPathlossModelType ("ns3::ThreeGppBuildingPropagationLossModel");
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
 Simulator::Schedule (Seconds (2), &ChangeSpeed, ueNodes.Get (0), Vector (20, 0.0, 0)); // start UE movement

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


 // Activate a data radio bearer
 enum EpsBearer::Qci q = EpsBearer::GBR_CONV_VOICE;
 EpsBearer bearer (q);
 ptr_mmWave->ActivateDataRadioBearer (ueNetDev, bearer);

 Simulator::Stop (Seconds (5));// 20m/s need to reach 100m
 Simulator::Run ();
 Simulator::Destroy ();
 return 0;
}


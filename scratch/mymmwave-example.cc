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

#define PrintUePosition false
/*Ue moving */
void
ChangeSpeed (Ptr<Node> n, Vector speed)
{
    n->GetObject<ConstantVelocityMobilityModel> ()->SetVelocity (speed);
    // NS_LOG_UNCOND (n->GetObject<ConstantVelocityMobilityModel> ()->GetDistanceFrom());
    //  NS_LOG_UNCOND ("************************--------------------Change Speed-------------------------------*****************");
}
#if PrintUePosition
void
PrintPosition (Ptr<Node> Uenode,Ptr<Node>enB, Ptr<OutputStreamWrapper> stream)
{
    Ptr<MobilityModel> Ue_model = Uenode->GetObject<MobilityModel> ();
    Ptr<MobilityModel> eNB_model = enB->GetObject<MobilityModel> ();
    *stream->GetStream () << Simulator::Now ().GetSeconds () << "\t" << Ue_model->GetDistanceFrom (eNB_model)<< std::endl;
}
#endif

int
main (int argc, char *argv[])
{


    std::string channel_condition = "l"; // channel condition, l = LOS, n = NLOS, otherwise the condition is randomly determined

    CommandLine cmd;
    cmd.AddValue("channel_condition","Channel Condition (LOS =l : NLOS=n",channel_condition);
    cmd.Parse(argc,argv);
    Config::SetDefault ("ns3::MmWaveEnbPhy::TxPower", DoubleValue (double(30)));
    Config::SetDefault ("ns3::MmWaveEnbPhy::NoiseFigure", DoubleValue (5));

    Ptr<MmWaveHelper> ptr_mmWave = CreateObject<MmWaveHelper> ();
    /* A configuration example.
    * ptr_mmWave->GetCcPhyParams ().at (0).GetConfigurationParameters ()->SetAttribute("SymbolPerSlot", UintegerValue(30));*/
    /* Configuration setting in the paper 5G mmWave Module for the ns-3 Network Simulator*/

    double simTime=5;//Seconds
    double totalBandwidth = 13.88e6;//SubbandWidth
    double frequency0 = 28e9;//value from Paper//CenterFreq
    double frequency1 = 73e9;
    bool useCa = false;

    uint16_t numberOfeNBNodes = 1;
    uint16_t numberOfUeNodes = 1;
    //Position and Speed of Ues
    double Ue_x= 40.0;
    double Ue_y= 20.0;
    double Ue_z= 00.0;
    double Ue_Speed[2]= {20.0,0.0};

#if 0
    double SetSlotPerSubframe [5]= {4,8,16,32,64};//Numeriology from 3
    double SetBandwidthh[5]= {13.88e6,13.88e6,13.88e6,13.88e6,13.88e6};
    double SetCentreFrequency[5]={28e9,28e9,28e9,28e9,28e9};
    double SetNumReferenceSymbols[5]={6,6,6,6,6};
    double SetSubframePerFrame [5]={10,10,10,10,10};
    double SetSymbolPeriod [5]={4.16,4.16,4.16,4.16,4.16,};//MicroSeconds (4.16)
    double SetSymbPerSlot [5]= {30,30,30,30,30};
#endif



    NodeContainer enbNodes;
    NodeContainer ueNodes;
    enbNodes.Create (numberOfeNBNodes);
    ueNodes.Create (numberOfUeNodes);

    /*Create Building obstracles*/
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

    /*Set Channel and Path Loss Conditions*/
     ptr_mmWave->SetPathlossModelType ("ns3::ThreeGppUmiStreetCanyonPropagationLossModel");
   //Dont Conside ptr_mmWave->SetPathlossModelType ("ns3::ThreeGppRmaPropagationLossModel");
    // ptr_mmWave->SetPathlossModelType ("ns3::ThreeGppUmaPropagationLossModel");
    //   ptr_mmWave->SetPathlossModelType ("ns3::ThreeGppIndoorOfficePropagationLossModel");

    if (channel_condition == "l")
    {
        std::cout<<"Channel Codition is LOS";
        ptr_mmWave->SetChannelConditionModelType ("ns3::AlwaysLosChannelConditionModel");

    }
    else if (channel_condition == "n")
    {
         std::cout<<"Channel Codition is NLOS";       
        ptr_mmWave->SetChannelConditionModelType ("ns3::NeverLosChannelConditionModel");
    }
    /*install  Mobility Model*/
    Ptr<ListPositionAllocator> uePositionAlloc = CreateObject<ListPositionAllocator> ();
    for (uint16_t i = 0; i < numberOfUeNodes; i++)
    {
        uePositionAlloc->Add (Vector (Ue_x+(20*i), Ue_y, Ue_z));
    }

    MobilityHelper uemobility;
    uemobility.SetMobilityModel ("ns3::ConstantVelocityMobilityModel");
    uemobility.SetPositionAllocator (uePositionAlloc);
    uemobility.Install (ueNodes);



    Ptr<ListPositionAllocator> enbPositionAlloc = CreateObject<ListPositionAllocator> ();
    enbPositionAlloc->Add (Vector (0.0, 0.0, 0.0));
    MobilityHelper enbmobility;
    enbmobility.SetMobilityModel ("ns3::ConstantPositionMobilityModel");
    enbmobility.SetPositionAllocator (enbPositionAlloc);
    enbmobility.Install (enbNodes);
    BuildingsHelper::Install (enbNodes);
    BuildingsHelper::Install (ueNodes);

    /// CC 0
    // 1. create MmWavePhyMacCommon object
    Ptr<MmWavePhyMacCommon> phyMacConfig0 = CreateObject<MmWavePhyMacCommon> ();
    phyMacConfig0->SetBandwidth (totalBandwidth );
    phyMacConfig0->SetCentreFrequency (frequency0);
    phyMacConfig0->SetNumReferenceSymbols (6);
    phyMacConfig0->SetSlotPerSubframe (32);
    phyMacConfig0->SetSubframePerFrame (10);
    phyMacConfig0->SetSymbolPeriod (MicroSeconds (4.16));
    phyMacConfig0->SetSymbPerSlot (30);

    std::cout<< " System Bandwith "<<phyMacConfig0->GetRbWidth()* phyMacConfig0->GetNumRb()<<"\n";
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
    /* Add mmWave stack to Ue and enbs*/
    NetDeviceContainer enbNetDev = ptr_mmWave->InstallEnbDevice (enbNodes);
    NetDeviceContainer ueNetDev = ptr_mmWave->InstallUeDevice (ueNodes);

    /*Attach Ues to Enb */
    ptr_mmWave->SetCcPhyParams (ccMap);
    ptr_mmWave->Initialize ();
    ptr_mmWave->AttachToClosestEnb (ueNetDev, enbNetDev);
    // Activate a data radio bearer
    enum EpsBearer::Qci q = EpsBearer::GBR_CONV_VOICE;
    EpsBearer bearer (q);
    ptr_mmWave->ActivateDataRadioBearer (ueNetDev, bearer);
    ptr_mmWave->EnableTraces ();
    /*start Ue Moblity*/
    for (uint16_t i = 0; i < numberOfUeNodes; i++)
    {
        Simulator::Schedule (Seconds (0.0), &ChangeSpeed, ueNodes.Get (i), Vector (Ue_Speed[i], 0.0, 0)); // start UE movement
    }
#if PrintUePosition
    AsciiTraceHelper asciiTraceHelper;
    Ptr<OutputStreamWrapper> Ue_1Positionstream = asciiTraceHelper.CreateFileStream ("Ue_1Positionstream.dat");
    Ptr<OutputStreamWrapper> Ue_2Positionstream = asciiTraceHelper.CreateFileStream ("Ue_2Positionstream.dat");
    double numPrints = 5;
    for (int i = 0; i <= numPrints; i++)
    {
        Simulator::Schedule (Seconds((simTime / numPrints) * i), &PrintPosition, ueNodes.Get (0),enbNodes.Get (0),Ue_1Positionstream);
    }

    /*
    for (int i = 0; i <= numPrints; i++)
    {
        Simulator::Schedule (Seconds((simTime / numPrints) * i), &PrintPosition, ueNodes.Get (1),enbNodes.Get (0),Ue_2Positionstream);
    }*/
#endif
    Simulator::Stop (Seconds (simTime));// 20m/s need to reach 100m
    Simulator::Run ();
    Simulator::Destroy ();
    return 0;
}


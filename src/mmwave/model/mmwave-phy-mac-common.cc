<<<<<<< HEAD
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
 *        	 	  Sourjya Dutta <sdutta@nyu.edu>
 *        	 	  Russell Ford <russell.ford@nyu.edu>
 *        		  Menglei Zhang <menglei@nyu.edu>
 */
=======
/* -*-  Mode: C++; c-file-style: "gnu"; indent-tabs-mode:nil; -*- */
/*
*   Copyright (c) 2011 Centre Tecnologic de Telecomunicacions de Catalunya (CTTC)
*   Copyright (c) 2015, NYU WIRELESS, Tandon School of Engineering, New York University
*   Copyright (c) 2016, 2018, University of Padova, Dep. of Information Engineering, SIGNET lab.
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
*/
>>>>>>> origin


#include <ns3/mmwave-phy-mac-common.h>
#include <ns3/log.h>
#include <ns3/uinteger.h>
#include <ns3/double.h>
#include <ns3/string.h>
#include <ns3/attribute-accessor-helper.h>
#include <ns3/simulator.h>
#include "ns3/enum.h"

namespace ns3 {

namespace mmwave {

NS_LOG_COMPONENT_DEFINE ("MmWavePhyMacCommon");

NS_OBJECT_ENSURE_REGISTERED (MmWavePhyMacCommon);

TypeId
MmWavePhyMacCommon::GetTypeId (void)
{
<<<<<<< HEAD
	static TypeId tid = TypeId("ns3::MmWavePhyMacCommon")
			.SetParent<Object> ()
			.AddConstructor<MmWavePhyMacCommon> ()
			.AddAttribute ("SymbolPerSlot",
						   "Number of symbols per slot",
						   UintegerValue (30),
						   MakeUintegerAccessor (&MmWavePhyMacCommon::m_symbolsPerSlot),
						   MakeUintegerChecker<uint32_t> ())
			.AddAttribute ("SymbolsPerSubframe",
							 "OFDM symbols per subframe",
							 UintegerValue (24),
							 MakeUintegerAccessor (&MmWavePhyMacCommon::m_symbolsPerSubframe),
							 MakeUintegerChecker<uint32_t> ())
			 .AddAttribute ("SubframePeriod",
										 "Symbol period in microseconds",
										 DoubleValue (100.0),
										 MakeDoubleAccessor (&MmWavePhyMacCommon::m_subframePeriod),
										 MakeDoubleChecker<double> ())
		   .AddAttribute ("CtrlSymbols",
							 "Number of OFDM symbols for DL control per subframe",
							 UintegerValue (1),
							 MakeUintegerAccessor (&MmWavePhyMacCommon::m_ctrlSymbols),
							 MakeUintegerChecker<uint32_t> ())
			.AddAttribute ("SymbolPeriod",
						   "Symbol period in microseconds",
						   DoubleValue (4.16),
						   MakeDoubleAccessor (&MmWavePhyMacCommon::m_symbolPeriod),
						   MakeDoubleChecker<double> ())
			.AddAttribute ("SlotsPerSubframe",
						   "Number of slots in one subframe",
						   UintegerValue (8),
						   MakeUintegerAccessor (&MmWavePhyMacCommon::m_slotsPerSubframe),
						   MakeUintegerChecker<uint32_t> ())
			.AddAttribute ("SubframePerFrame",
						   "Number of subframe per frame",
						   UintegerValue (10),
						   MakeUintegerAccessor (&MmWavePhyMacCommon::m_subframesPerFrame),
						   MakeUintegerChecker<uint32_t> ())
			.AddAttribute ("SubcarriersPerChunk",
						   "Number of sub-carriers per chunk",
						   UintegerValue (48),
						   MakeUintegerAccessor (&MmWavePhyMacCommon::m_numSubCarriersPerChunk),
						   MakeUintegerChecker<uint32_t> ())
			.AddAttribute ("ChunkPerRB",
						   "Number of chunks comprising a resource block",
						   UintegerValue (72),
						   MakeUintegerAccessor (&MmWavePhyMacCommon::m_chunksPerRb),
						   MakeUintegerChecker<uint32_t> ())
			.AddAttribute ("ChunkWidth",
						   "Width of each chunk in Hz",
						   DoubleValue (13.889e6),
						   MakeDoubleAccessor (&MmWavePhyMacCommon::m_chunkWidth),
						   MakeDoubleChecker<double> ())
			.AddAttribute ("ResourceBlockNum",
						   "Number of resource blocks the entire bandwidth is split into",
						   UintegerValue (1),
						   MakeUintegerAccessor (&MmWavePhyMacCommon::m_numRb),
						   MakeUintegerChecker<uint32_t> ())
			.AddAttribute ("NumReferenceSymbols",
						   "Number of reference symbols per slot",
						   UintegerValue (6),
						   MakeUintegerAccessor (&MmWavePhyMacCommon::m_numRefSymbols),
						   MakeUintegerChecker<uint32_t> ())
			.AddAttribute ("CenterFreq",
						   "The center frequency in Hz",
						   DoubleValue (28e9),
						   MakeDoubleAccessor (&MmWavePhyMacCommon::m_centerFrequency),
						   MakeDoubleChecker<double> ())
			.AddAttribute ("TDDPattern",
						   "The control-data pattern for TDD transmission",
						   StringValue ("ccdddddd"),
						   MakeStringAccessor (&MmWavePhyMacCommon::m_staticTddPattern),
						   MakeStringChecker ())
		  .AddAttribute ("UlSchedDelay",
							 "Number of TTIs between UL scheduling decision and subframe to which it applies",
							 UintegerValue (1),
							 MakeUintegerAccessor (&MmWavePhyMacCommon::m_ulSchedDelay),
							 MakeUintegerChecker<uint32_t> ())
		  .AddAttribute ("NumRbPerRbg",
							 "Number of resource blocks per resource block group",
							 UintegerValue (1),
							 MakeUintegerAccessor (&MmWavePhyMacCommon::m_numRbPerRbg),
							 MakeUintegerChecker<uint32_t> ())
			.AddAttribute ("WbCqiPeriod",
							 "Microseconds between wideband DL-CQI reports",
							 UintegerValue (500),
							 MakeUintegerAccessor (&MmWavePhyMacCommon::m_wbCqiPeriodUs),
							 MakeUintegerChecker<uint32_t> ())
		 .AddAttribute ("GuardPeriod",
							 "Guard period for UL to DL slot transition in microseconds",
							 DoubleValue (4.16),
							 MakeDoubleAccessor (&MmWavePhyMacCommon::m_guardPeriod),
							 MakeDoubleChecker<double> ())
		 .AddAttribute ("NumHarqProcess",
							 "Number of concurrent stop-and-wait Hybrid ARQ processes per user",
							 UintegerValue (20),
							 MakeUintegerAccessor (&MmWavePhyMacCommon::m_numHarqProcess),
							 MakeUintegerChecker<uint8_t> ())
		 .AddAttribute ("HarqDlTimeout",
							 "Number of concurrent stop-and-wait Hybrid ARQ processes per user",
							 UintegerValue (20),
							 MakeUintegerAccessor (&MmWavePhyMacCommon::m_harqTimeout),
							 MakeUintegerChecker<uint8_t> ())
		 .AddAttribute ("TbDecodeLatency",
									 "Number of concurrent stop-and-wait Hybrid ARQ processes per user",
									 UintegerValue (100.0),
									 MakeUintegerAccessor (&MmWavePhyMacCommon::m_tbDecodeLatencyUs),
									 MakeUintegerChecker<uint32_t> ())
	;
=======
  static TypeId tid =
    TypeId ("ns3::MmWavePhyMacCommon")
    .SetParent<Object> ()
    .AddConstructor<MmWavePhyMacCommon> ()
    .AddAttribute ("Numerology",
                   "The PHY layer numerology",
                   EnumValue (2),
                   MakeEnumAccessor (&MmWavePhyMacCommon::SetNumerology),
                   MakeEnumChecker (NrNumerology2, "NrNumerology2",
                                    NrNumerology3, "NrNumerology3"))
    .AddAttribute ("Bandwidth",
                   "The carrier bandwidth in Hz",
                   DoubleValue (200e6),
                   MakeDoubleAccessor (&MmWavePhyMacCommon::SetBandwidth),
                   MakeDoubleChecker<double> ())
    .AddAttribute ("CenterFreq",
                   "The center frequency in Hz", 
                   DoubleValue (28e9),
                   MakeDoubleAccessor (&MmWavePhyMacCommon::m_centerFrequency),
                   MakeDoubleChecker<double> ())
    .AddAttribute ("UlSchedDelay",
                   "Delay between the UL-DCI transmission and when such scheduled UL will take place, defined as # of NR slots.",
                   UintegerValue (1),
                   MakeUintegerAccessor (&MmWavePhyMacCommon::m_ulSchedDelay),
                   MakeUintegerChecker<uint32_t> ())
    .AddAttribute ("NumHarqProcess",
                   "Number of concurrent stop-and-wait Hybrid ARQ processes per user",
                   UintegerValue (20),
                   MakeUintegerAccessor (&MmWavePhyMacCommon::m_numHarqProcess),
                   MakeUintegerChecker<uint8_t> ())
    .AddAttribute ("HarqDlTimeout",
                   "Hybrid ARQ timeout period",
                   UintegerValue (20),
                   MakeUintegerAccessor (&MmWavePhyMacCommon::m_harqTimeout),
                   MakeUintegerChecker<uint8_t> ())
    .AddAttribute ("TbDecodeLatency",
                   "Time required by the PHY layer to decode a transport block in us.",
                   UintegerValue (100.0),
                   MakeUintegerAccessor (&MmWavePhyMacCommon::m_tbDecodeLatencyUs),
                   MakeUintegerChecker<uint32_t> ())
    .AddAttribute ("ComponentCarrierId",
                   "Component carrier ID",
                   UintegerValue (0),
                   MakeUintegerAccessor (&MmWavePhyMacCommon::m_componentCarrierId),
                   MakeUintegerChecker<uint8_t> ());
>>>>>>> origin

  return tid;
}

MmWavePhyMacCommon::MmWavePhyMacCommon ()
  : m_dlCtrlSymbols (1),
  m_ulCtrlSymbols (1),
  m_numRefSc (864),
  m_L1L2Latency (2)
{
  NS_LOG_INFO ("Initialized MmWavePhyMacCommon");
}

void
MmWavePhyMacCommon::SetNumerology (Numerology num)
{
  NS_LOG_FUNCTION (this << num);
  
  if (num == Numerology::NrNumerology2)
    SetNrNumerology (2);
  else if (num == Numerology::NrNumerology3)
    SetNrNumerology (3);
  else 
    NS_FATAL_ERROR ("Currently, only numerologies 2 and 3 are supported!");
}

void
MmWavePhyMacCommon::SetNrNumerology (uint8_t index)
{
  NS_LOG_FUNCTION (this << index); 
  NS_ASSERT_MSG ( (index == 2) || (index == 3), "Numerology index is not valid."); // Only 2 and 3 are supported in NR for FR2.

  double subcarrierSpacing = 15 * std::pow (2, index) * 1000; // Subcarrier spacing, only 60KHz and 120KHz are supported in NR for FR2.

  m_symbolsPerSlot = 14; // TS 38.211 Sec 4.3.2: each slot must have 14 symbols
  m_slotsPerSubframe = std::pow (2, index);// Number of slots per subframe, see TS 38.211 Sec 4.3.2
  m_symbolsPerSubframe = m_symbolsPerSlot * m_slotsPerSubframe;
  m_subframesPerFrame = 10;
  m_subframePeriod = Time (MilliSeconds (1)); // TS 38.211 Section 4.3.1: the subframe duration is 1ms
  m_symbolPeriod = Time (m_subframePeriod / m_symbolsPerSlot / m_slotsPerSubframe); // Duration of an OFDM symbol
  m_rbWidth = SUBCARRIERS_PER_RB * subcarrierSpacing;
}

void
MmWavePhyMacCommon::SetBandwidth (double bw)
{
  NS_LOG_FUNCTION (this << bw); 
  
  m_numRbs = std::ceil(bw/m_rbWidth);  // The amount of RBs is fixed to 1 as only TDMA is supported
  m_numRefSc = REF_SUBCARRIERS_PER_RB*m_numRbs; 
}

} // namespace mmwave

} // namespace ns3

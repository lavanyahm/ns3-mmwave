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
 *          Sébastien Deronne <sebastien.deronne@gmail.com>
 */

<<<<<<< HEAD
#include "wifi-phy.h"
#include "wifi-mode.h"
#include "wifi-channel.h"
#include "wifi-preamble.h"
#include "wifi-phy-state-helper.h"
#include "ns3/simulator.h"
#include "ns3/assert.h"
#include "ns3/log.h"
#include "ns3/boolean.h"
#include "ns3/double.h"
#include "ns3/uinteger.h"
#include "ns3/enum.h"
#include "ns3/pointer.h"
#include "ns3/trace-source-accessor.h"
#include "ns3/fatal-error.h"
#include <cmath>
=======
#include <algorithm>
#include "ns3/simulator.h"
#include "ns3/log.h"
#include "ns3/pointer.h"
#include "ns3/mobility-model.h"
#include "ns3/random-variable-stream.h"
#include "ns3/error-model.h"
#include "wifi-phy.h"
#include "ampdu-tag.h"
#include "wifi-utils.h"
#include "sta-wifi-mac.h"
#include "frame-capture-model.h"
#include "preamble-detection-model.h"
#include "wifi-radio-energy-model.h"
#include "error-rate-model.h"
#include "wifi-net-device.h"
#include "ns3/ht-configuration.h"
#include "ns3/he-configuration.h"
#include "mpdu-aggregator.h"
#include "wifi-psdu.h"
#include "wifi-ppdu.h"
#include "ap-wifi-mac.h"
#include "ns3/dsss-phy.h"
#include "ns3/erp-ofdm-phy.h"
#include "ns3/he-phy.h" //includes OFDM, HT, and VHT
>>>>>>> origin

namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("WifiPhy");

/****************************************************************
 *       The actual WifiPhy class
 ****************************************************************/

NS_OBJECT_ENSURE_REGISTERED (WifiPhy);

<<<<<<< HEAD
/**
 * This table maintains the mapping of valid ChannelNumber to
 * Frequency/ChannelWidth pairs.  If you want to make a channel applicable
 * to all standards, then you may use the WIFI_PHY_STANDARD_UNSPECIFIED
 * standard to represent this, as a wildcard.  If you want to limit the 
 * configuration of a particular channel/frequency/width to a particular 
 * standard(s), then you can specify one or more such bindings. 
 */
WifiPhy::ChannelToFrequencyWidthMap WifiPhy::m_channelToFrequencyWidth =
{
  // 802.11b uses width of 22, while OFDM modes use width of 20
  { std::make_pair (1, WIFI_PHY_STANDARD_80211b), std::make_pair (2412, 22) },
  { std::make_pair (1, WIFI_PHY_STANDARD_UNSPECIFIED), std::make_pair (2412, 20) },
  { std::make_pair (2, WIFI_PHY_STANDARD_80211b), std::make_pair (2417, 22) },
  { std::make_pair (2, WIFI_PHY_STANDARD_UNSPECIFIED), std::make_pair (2417, 20) },
  { std::make_pair (3, WIFI_PHY_STANDARD_80211b), std::make_pair (2422, 22) },
  { std::make_pair (3, WIFI_PHY_STANDARD_UNSPECIFIED), std::make_pair (2422, 20) },
  { std::make_pair (4, WIFI_PHY_STANDARD_80211b), std::make_pair (2427, 22) },
  { std::make_pair (4, WIFI_PHY_STANDARD_UNSPECIFIED), std::make_pair (2427, 20) },
  { std::make_pair (5, WIFI_PHY_STANDARD_80211b), std::make_pair (2432, 22) },
  { std::make_pair (5, WIFI_PHY_STANDARD_UNSPECIFIED), std::make_pair (2432, 20) },
  { std::make_pair (6, WIFI_PHY_STANDARD_80211b), std::make_pair (2437, 22) },
  { std::make_pair (6, WIFI_PHY_STANDARD_UNSPECIFIED), std::make_pair (2437, 20) },
  { std::make_pair (7, WIFI_PHY_STANDARD_80211b), std::make_pair (2442, 22) },
  { std::make_pair (7, WIFI_PHY_STANDARD_UNSPECIFIED), std::make_pair (2442, 20) },
  { std::make_pair (8, WIFI_PHY_STANDARD_80211b), std::make_pair (2447, 22) },
  { std::make_pair (8, WIFI_PHY_STANDARD_UNSPECIFIED), std::make_pair (2447, 20) },
  { std::make_pair (9, WIFI_PHY_STANDARD_80211b), std::make_pair (2452, 22) },
  { std::make_pair (9, WIFI_PHY_STANDARD_UNSPECIFIED), std::make_pair (2452, 20) },
  { std::make_pair (10, WIFI_PHY_STANDARD_80211b), std::make_pair (2457, 22) },
  { std::make_pair (10, WIFI_PHY_STANDARD_UNSPECIFIED), std::make_pair (2457, 20) },
  { std::make_pair (11, WIFI_PHY_STANDARD_80211b), std::make_pair (2462, 22) },
  { std::make_pair (11, WIFI_PHY_STANDARD_UNSPECIFIED), std::make_pair (2462, 20) },
  { std::make_pair (12, WIFI_PHY_STANDARD_80211b), std::make_pair (2467, 22) },
  { std::make_pair (12, WIFI_PHY_STANDARD_UNSPECIFIED), std::make_pair (2467, 20) },
  { std::make_pair (13, WIFI_PHY_STANDARD_80211b), std::make_pair (2472, 22) },
  { std::make_pair (13, WIFI_PHY_STANDARD_UNSPECIFIED), std::make_pair (2472, 20) },
  // Only defined for 802.11b
  { std::make_pair (14, WIFI_PHY_STANDARD_80211b), std::make_pair (2484, 22) },

  // Now the 5GHz channels; UNSPECIFIED for 802.11a/n channels, but limited
  // to 802.11ac for the 80/160 MHz channels
  // 20 MHz channels
  { std::make_pair (36, WIFI_PHY_STANDARD_UNSPECIFIED), std::make_pair (5180, 20) },
  { std::make_pair (40, WIFI_PHY_STANDARD_UNSPECIFIED), std::make_pair (5200, 20) },
  { std::make_pair (44, WIFI_PHY_STANDARD_UNSPECIFIED), std::make_pair (5220, 20) },
  { std::make_pair (48, WIFI_PHY_STANDARD_UNSPECIFIED), std::make_pair (5240, 20) },
  { std::make_pair (52, WIFI_PHY_STANDARD_UNSPECIFIED), std::make_pair (5260, 20) },
  { std::make_pair (56, WIFI_PHY_STANDARD_UNSPECIFIED), std::make_pair (5280, 20) },
  { std::make_pair (60, WIFI_PHY_STANDARD_UNSPECIFIED), std::make_pair (5300, 20) },
  { std::make_pair (64, WIFI_PHY_STANDARD_UNSPECIFIED), std::make_pair (5320, 20) },
  { std::make_pair (100, WIFI_PHY_STANDARD_UNSPECIFIED), std::make_pair (5500, 20) },
  { std::make_pair (104, WIFI_PHY_STANDARD_UNSPECIFIED), std::make_pair (5520, 20) },
  { std::make_pair (108, WIFI_PHY_STANDARD_UNSPECIFIED), std::make_pair (5540, 20) },
  { std::make_pair (112, WIFI_PHY_STANDARD_UNSPECIFIED), std::make_pair (5560, 20) },
  { std::make_pair (116, WIFI_PHY_STANDARD_UNSPECIFIED), std::make_pair (5580, 20) },
  { std::make_pair (120, WIFI_PHY_STANDARD_UNSPECIFIED), std::make_pair (5600, 20) },
  { std::make_pair (124, WIFI_PHY_STANDARD_UNSPECIFIED), std::make_pair (5620, 20) },
  { std::make_pair (128, WIFI_PHY_STANDARD_UNSPECIFIED), std::make_pair (5640, 20) },
  { std::make_pair (132, WIFI_PHY_STANDARD_UNSPECIFIED), std::make_pair (5660, 20) },
  { std::make_pair (136, WIFI_PHY_STANDARD_UNSPECIFIED), std::make_pair (5680, 20) },
  { std::make_pair (140, WIFI_PHY_STANDARD_UNSPECIFIED), std::make_pair (5700, 20) },
  { std::make_pair (144, WIFI_PHY_STANDARD_UNSPECIFIED), std::make_pair (5720, 20) },
  { std::make_pair (149, WIFI_PHY_STANDARD_UNSPECIFIED), std::make_pair (5745, 20) },
  { std::make_pair (153, WIFI_PHY_STANDARD_UNSPECIFIED), std::make_pair (5765, 20) },
  { std::make_pair (157, WIFI_PHY_STANDARD_UNSPECIFIED), std::make_pair (5785, 20) },
  { std::make_pair (161, WIFI_PHY_STANDARD_UNSPECIFIED), std::make_pair (5805, 20) },
  { std::make_pair (165, WIFI_PHY_STANDARD_UNSPECIFIED), std::make_pair (5825, 20) },
  // 40 MHz channels
  { std::make_pair (38, WIFI_PHY_STANDARD_UNSPECIFIED), std::make_pair (5190, 40) },
  { std::make_pair (46, WIFI_PHY_STANDARD_UNSPECIFIED), std::make_pair (5230, 40) },
  { std::make_pair (54, WIFI_PHY_STANDARD_UNSPECIFIED), std::make_pair (5230, 40) },
  { std::make_pair (62, WIFI_PHY_STANDARD_UNSPECIFIED), std::make_pair (5310, 40) },
  { std::make_pair (102, WIFI_PHY_STANDARD_UNSPECIFIED), std::make_pair (5510, 40) },
  { std::make_pair (110, WIFI_PHY_STANDARD_UNSPECIFIED), std::make_pair (5550, 40) },
  { std::make_pair (118, WIFI_PHY_STANDARD_UNSPECIFIED), std::make_pair (5590, 40) },
  { std::make_pair (126, WIFI_PHY_STANDARD_UNSPECIFIED), std::make_pair (5590, 40) },
  { std::make_pair (134, WIFI_PHY_STANDARD_UNSPECIFIED), std::make_pair (5670, 40) },
  { std::make_pair (142, WIFI_PHY_STANDARD_UNSPECIFIED), std::make_pair (5710, 40) },
  { std::make_pair (151, WIFI_PHY_STANDARD_UNSPECIFIED), std::make_pair (5755, 40) },
  { std::make_pair (159, WIFI_PHY_STANDARD_UNSPECIFIED), std::make_pair (5795, 40) },
  // 80 MHz channels
  { std::make_pair (42, WIFI_PHY_STANDARD_80211ac), std::make_pair (5210, 80) },
  { std::make_pair (58, WIFI_PHY_STANDARD_80211ac), std::make_pair (5290, 80) },
  { std::make_pair (106, WIFI_PHY_STANDARD_80211ac), std::make_pair (5530, 80) },
  { std::make_pair (122, WIFI_PHY_STANDARD_80211ac), std::make_pair (5610, 80) },
  { std::make_pair (138, WIFI_PHY_STANDARD_80211ac), std::make_pair (5690, 80) },
  { std::make_pair (155, WIFI_PHY_STANDARD_80211ac), std::make_pair (5775, 80) },
  // 160 MHz channels
  { std::make_pair (50, WIFI_PHY_STANDARD_80211ac), std::make_pair (5250, 160) },
  { std::make_pair (114, WIFI_PHY_STANDARD_80211ac), std::make_pair (5570, 160) },

  // 802.11p (10 MHz channels at the 5.855-5.925 band 
  { std::make_pair (172, WIFI_PHY_STANDARD_80211_10MHZ), std::make_pair (5860, 10) },
  { std::make_pair (174, WIFI_PHY_STANDARD_80211_10MHZ), std::make_pair (5870, 10) },
  { std::make_pair (176, WIFI_PHY_STANDARD_80211_10MHZ), std::make_pair (5880, 10) },
  { std::make_pair (178, WIFI_PHY_STANDARD_80211_10MHZ), std::make_pair (5890, 10) },
  { std::make_pair (180, WIFI_PHY_STANDARD_80211_10MHZ), std::make_pair (5900, 10) },
  { std::make_pair (182, WIFI_PHY_STANDARD_80211_10MHZ), std::make_pair (5910, 10) },
  { std::make_pair (184, WIFI_PHY_STANDARD_80211_10MHZ), std::make_pair (5920, 10) }
};

=======
const std::set<FrequencyChannelInfo> WifiPhy::m_frequencyChannels =
{
  //2.4 GHz channels
  // 802.11b uses width of 22, while OFDM modes use width of 20
  { std::make_tuple (1, 2412, 22, WIFI_PHY_DSSS_CHANNEL, WIFI_PHY_BAND_2_4GHZ) },
  { std::make_tuple (1, 2412, 20, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_2_4GHZ) },
  { std::make_tuple (2, 2417, 22, WIFI_PHY_DSSS_CHANNEL, WIFI_PHY_BAND_2_4GHZ) },
  { std::make_tuple (2, 2417, 20, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_2_4GHZ) },
  { std::make_tuple (3, 2422, 22, WIFI_PHY_DSSS_CHANNEL, WIFI_PHY_BAND_2_4GHZ) },
  { std::make_tuple (3, 2422, 20, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_2_4GHZ) },
  { std::make_tuple (4, 2427, 22, WIFI_PHY_DSSS_CHANNEL, WIFI_PHY_BAND_2_4GHZ) },
  { std::make_tuple (4, 2427, 20, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_2_4GHZ) },
  { std::make_tuple (5, 2432, 22, WIFI_PHY_DSSS_CHANNEL, WIFI_PHY_BAND_2_4GHZ) },
  { std::make_tuple (5, 2432, 20, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_2_4GHZ) },
  { std::make_tuple (6, 2437, 22, WIFI_PHY_DSSS_CHANNEL, WIFI_PHY_BAND_2_4GHZ) },
  { std::make_tuple (6, 2437, 20, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_2_4GHZ) },
  { std::make_tuple (7, 2442, 22, WIFI_PHY_DSSS_CHANNEL, WIFI_PHY_BAND_2_4GHZ) },
  { std::make_tuple (7, 2442, 20, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_2_4GHZ) },
  { std::make_tuple (8, 2447, 22, WIFI_PHY_DSSS_CHANNEL, WIFI_PHY_BAND_2_4GHZ) },
  { std::make_tuple (8, 2447, 20, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_2_4GHZ) },
  { std::make_tuple (9, 2452, 22, WIFI_PHY_DSSS_CHANNEL, WIFI_PHY_BAND_2_4GHZ) },
  { std::make_tuple (9, 2452, 20, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_2_4GHZ) },
  { std::make_tuple (10, 2457, 22, WIFI_PHY_DSSS_CHANNEL, WIFI_PHY_BAND_2_4GHZ) },
  { std::make_tuple (10, 2457, 20, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_2_4GHZ) },
  { std::make_tuple (11, 2462, 22, WIFI_PHY_DSSS_CHANNEL, WIFI_PHY_BAND_2_4GHZ) },
  { std::make_tuple (11, 2462, 20, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_2_4GHZ) },
  { std::make_tuple (12, 2467, 22, WIFI_PHY_DSSS_CHANNEL, WIFI_PHY_BAND_2_4GHZ) },
  { std::make_tuple (12, 2467, 20, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_2_4GHZ) },
  { std::make_tuple (13, 2472, 22, WIFI_PHY_DSSS_CHANNEL, WIFI_PHY_BAND_2_4GHZ) },
  { std::make_tuple (13, 2472, 20, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_2_4GHZ) },
  // Only defined for 802.11b
  { std::make_tuple (14, 2484, 22, WIFI_PHY_DSSS_CHANNEL, WIFI_PHY_BAND_2_4GHZ) },
  // 40 MHz channels
  { std::make_tuple (3, 2422, 40, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_2_4GHZ) },
  { std::make_tuple (4, 2427, 40, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_2_4GHZ) },
  { std::make_tuple (5, 2432, 40, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_2_4GHZ) },
  { std::make_tuple (6, 2437, 40, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_2_4GHZ) },
  { std::make_tuple (7, 2442, 40, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_2_4GHZ) },
  { std::make_tuple (8, 2447, 40, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_2_4GHZ) },
  { std::make_tuple (9, 2452, 40, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_2_4GHZ) },
  { std::make_tuple (10, 2457, 40, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_2_4GHZ) },
  { std::make_tuple (11, 2462, 40, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_2_4GHZ) },

  // Now the 5 GHz channels used for 802.11a/n/ac/ax
  // 20 MHz channels
  { std::make_tuple (36, 5180, 20, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_5GHZ) },
  { std::make_tuple (40, 5200, 20, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_5GHZ) },
  { std::make_tuple (44, 5220, 20, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_5GHZ) },
  { std::make_tuple (48, 5240, 20, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_5GHZ) },
  { std::make_tuple (52, 5260, 20, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_5GHZ) },
  { std::make_tuple (56, 5280, 20, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_5GHZ) },
  { std::make_tuple (60, 5300, 20, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_5GHZ) },
  { std::make_tuple (64, 5320, 20, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_5GHZ) },
  { std::make_tuple (100, 5500, 20, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_5GHZ) },
  { std::make_tuple (104, 5520, 20, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_5GHZ) },
  { std::make_tuple (108, 5540, 20, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_5GHZ) },
  { std::make_tuple (112, 5560, 20, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_5GHZ) },
  { std::make_tuple (116, 5580, 20, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_5GHZ) },
  { std::make_tuple (120, 5600, 20, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_5GHZ) },
  { std::make_tuple (124, 5620, 20, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_5GHZ) },
  { std::make_tuple (128, 5640, 20, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_5GHZ) },
  { std::make_tuple (132, 5660, 20, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_5GHZ) },
  { std::make_tuple (136, 5680, 20, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_5GHZ) },
  { std::make_tuple (140, 5700, 20, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_5GHZ) },
  { std::make_tuple (144, 5720, 20, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_5GHZ) },
  { std::make_tuple (149, 5745, 20, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_5GHZ) },
  { std::make_tuple (153, 5765, 20, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_5GHZ) },
  { std::make_tuple (157, 5785, 20, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_5GHZ) },
  { std::make_tuple (161, 5805, 20, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_5GHZ) },
  { std::make_tuple (165, 5825, 20, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_5GHZ) },
  { std::make_tuple (169, 5845, 20, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_5GHZ) },
  { std::make_tuple (173, 5865, 20, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_5GHZ) },
  { std::make_tuple (177, 5885, 20, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_5GHZ) },
  { std::make_tuple (181, 5905, 20, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_5GHZ) },
  // 40 MHz channels
  { std::make_tuple (38, 5190, 40, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_5GHZ) },
  { std::make_tuple (46, 5230, 40, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_5GHZ) },
  { std::make_tuple (54, 5270, 40, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_5GHZ) },
  { std::make_tuple (62, 5310, 40, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_5GHZ) },
  { std::make_tuple (102, 5510, 40, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_5GHZ) },
  { std::make_tuple (110, 5550, 40, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_5GHZ) },
  { std::make_tuple (118, 5590, 40, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_5GHZ) },
  { std::make_tuple (126, 5630, 40, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_5GHZ) },
  { std::make_tuple (134, 5670, 40, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_5GHZ) },
  { std::make_tuple (142, 5710, 40, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_5GHZ) },
  { std::make_tuple (151, 5755, 40, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_5GHZ) },
  { std::make_tuple (159, 5795, 40, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_5GHZ) },
  { std::make_tuple (167, 5835, 40, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_5GHZ) },
  { std::make_tuple (175, 5875, 40, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_5GHZ) },
  // 80 MHz channels
  { std::make_tuple (42, 5210, 80, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_5GHZ) },
  { std::make_tuple (58, 5290, 80, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_5GHZ) },
  { std::make_tuple (106, 5530, 80, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_5GHZ) },
  { std::make_tuple (122, 5610, 80, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_5GHZ) },
  { std::make_tuple (138, 5690, 80, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_5GHZ) },
  { std::make_tuple (155, 5775, 80, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_5GHZ) },
  { std::make_tuple (171, 5855, 80, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_5GHZ) },
  // 160 MHz channels
  { std::make_tuple (50, 5250, 160, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_5GHZ) },
  { std::make_tuple (114, 5570, 160, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_5GHZ) },
  { std::make_tuple (163, 5815, 160, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_5GHZ) },

  // 802.11p 10 MHz channels at the 5.855-5.925 band
  { std::make_tuple (172, 5860, 10, WIFI_PHY_80211p_CHANNEL, WIFI_PHY_BAND_5GHZ) },
  { std::make_tuple (174, 5870, 10, WIFI_PHY_80211p_CHANNEL, WIFI_PHY_BAND_5GHZ) },
  { std::make_tuple (176, 5880, 10, WIFI_PHY_80211p_CHANNEL, WIFI_PHY_BAND_5GHZ) },
  { std::make_tuple (178, 5890, 10, WIFI_PHY_80211p_CHANNEL, WIFI_PHY_BAND_5GHZ) },
  { std::make_tuple (180, 5900, 10, WIFI_PHY_80211p_CHANNEL, WIFI_PHY_BAND_5GHZ) },
  { std::make_tuple (182, 5910, 10, WIFI_PHY_80211p_CHANNEL, WIFI_PHY_BAND_5GHZ) },
  { std::make_tuple (184, 5920, 10, WIFI_PHY_80211p_CHANNEL, WIFI_PHY_BAND_5GHZ) },

  // 802.11p 5 MHz channels at the 5.855-5.925 band (for simplification, we consider the same center frequencies as the 10 MHz channels)
  { std::make_tuple (171, 5860, 5, WIFI_PHY_80211p_CHANNEL, WIFI_PHY_BAND_5GHZ) },
  { std::make_tuple (173, 5870, 5, WIFI_PHY_80211p_CHANNEL, WIFI_PHY_BAND_5GHZ) },
  { std::make_tuple (175, 5880, 5, WIFI_PHY_80211p_CHANNEL, WIFI_PHY_BAND_5GHZ) },
  { std::make_tuple (177, 5890, 5, WIFI_PHY_80211p_CHANNEL, WIFI_PHY_BAND_5GHZ) },
  { std::make_tuple (179, 5900, 5, WIFI_PHY_80211p_CHANNEL, WIFI_PHY_BAND_5GHZ) },
  { std::make_tuple (181, 5910, 5, WIFI_PHY_80211p_CHANNEL, WIFI_PHY_BAND_5GHZ) },
  { std::make_tuple (183, 5920, 5, WIFI_PHY_80211p_CHANNEL, WIFI_PHY_BAND_5GHZ) },

  // Now the 6 GHz channels (802.11ax only)
  // 20 MHz channels
  { std::make_tuple (1, 5945, 20, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_6GHZ) },
  { std::make_tuple (5, 5965, 20, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_6GHZ) },
  { std::make_tuple (9, 5985, 20, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_6GHZ) },
  { std::make_tuple (13, 6005, 20, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_6GHZ) },
  { std::make_tuple (17, 6025, 20, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_6GHZ) },
  { std::make_tuple (21, 6045, 20, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_6GHZ) },
  { std::make_tuple (25, 6065, 20, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_6GHZ) },
  { std::make_tuple (29, 6085, 20, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_6GHZ) },
  { std::make_tuple (33, 6105, 20, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_6GHZ) },
  { std::make_tuple (37, 6125, 20, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_6GHZ) },
  { std::make_tuple (41, 6145, 20, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_6GHZ) },
  { std::make_tuple (45, 6165, 20, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_6GHZ) },
  { std::make_tuple (49, 6185, 20, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_6GHZ) },
  { std::make_tuple (53, 6205, 20, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_6GHZ) },
  { std::make_tuple (57, 6225, 20, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_6GHZ) },
  { std::make_tuple (61, 6245, 20, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_6GHZ) },
  { std::make_tuple (65, 6265, 20, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_6GHZ) },
  { std::make_tuple (69, 6285, 20, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_6GHZ) },
  { std::make_tuple (73, 6305, 20, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_6GHZ) },
  { std::make_tuple (77, 6325, 20, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_6GHZ) },
  { std::make_tuple (81, 6345, 20, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_6GHZ) },
  { std::make_tuple (85, 6365, 20, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_6GHZ) },
  { std::make_tuple (89, 6385, 20, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_6GHZ) },
  { std::make_tuple (93, 6405, 20, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_6GHZ) },
  { std::make_tuple (97, 6425, 20, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_6GHZ) },
  { std::make_tuple (101, 6445, 20, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_6GHZ) },
  { std::make_tuple (105, 6465, 20, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_6GHZ) },
  { std::make_tuple (109, 6485, 20, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_6GHZ) },
  { std::make_tuple (113, 6505, 20, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_6GHZ) },
  { std::make_tuple (117, 6525, 20, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_6GHZ) },
  { std::make_tuple (121, 6545, 20, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_6GHZ) },
  { std::make_tuple (125, 6565, 20, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_6GHZ) },
  { std::make_tuple (129, 6585, 20, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_6GHZ) },
  { std::make_tuple (133, 6605, 20, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_6GHZ) },
  { std::make_tuple (137, 6625, 20, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_6GHZ) },
  { std::make_tuple (141, 6645, 20, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_6GHZ) },
  { std::make_tuple (145, 6665, 20, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_6GHZ) },
  { std::make_tuple (149, 6685, 20, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_6GHZ) },
  { std::make_tuple (153, 6705, 20, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_6GHZ) },
  { std::make_tuple (157, 6725, 20, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_6GHZ) },
  { std::make_tuple (161, 6745, 20, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_6GHZ) },
  { std::make_tuple (165, 6765, 20, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_6GHZ) },
  { std::make_tuple (169, 6785, 20, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_6GHZ) },
  { std::make_tuple (173, 6805, 20, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_6GHZ) },
  { std::make_tuple (177, 6825, 20, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_6GHZ) },
  { std::make_tuple (181, 6845, 20, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_6GHZ) },
  { std::make_tuple (185, 6865, 20, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_6GHZ) },
  { std::make_tuple (189, 6885, 20, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_6GHZ) },
  { std::make_tuple (193, 6905, 20, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_6GHZ) },
  { std::make_tuple (197, 6925, 20, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_6GHZ) },
  { std::make_tuple (201, 6945, 20, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_6GHZ) },
  { std::make_tuple (205, 6965, 20, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_6GHZ) },
  { std::make_tuple (209, 6985, 20, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_6GHZ) },
  { std::make_tuple (213, 7005, 20, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_6GHZ) },
  { std::make_tuple (217, 7025, 20, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_6GHZ) },
  { std::make_tuple (221, 7045, 20, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_6GHZ) },
  { std::make_tuple (225, 7065, 20, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_6GHZ) },
  { std::make_tuple (229, 7085, 20, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_6GHZ) },
  { std::make_tuple (233, 7105, 20, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_6GHZ) },
  // 40 MHz channels
  { std::make_tuple (3, 5955, 40, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_6GHZ) },
  { std::make_tuple (11, 5995, 40, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_6GHZ) },
  { std::make_tuple (19, 6035, 40, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_6GHZ) },
  { std::make_tuple (27, 6075, 40, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_6GHZ) },
  { std::make_tuple (35, 6115, 40, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_6GHZ) },
  { std::make_tuple (43, 6155, 40, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_6GHZ) },
  { std::make_tuple (51, 6195, 40, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_6GHZ) },
  { std::make_tuple (59, 6235, 40, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_6GHZ) },
  { std::make_tuple (67, 6275, 40, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_6GHZ) },
  { std::make_tuple (75, 6315, 40, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_6GHZ) },
  { std::make_tuple (83, 6355, 40, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_6GHZ) },
  { std::make_tuple (91, 6395, 40, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_6GHZ) },
  { std::make_tuple (99, 6435, 40, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_6GHZ) },
  { std::make_tuple (107, 6475, 40, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_6GHZ) },
  { std::make_tuple (115, 6515, 40, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_6GHZ) },
  { std::make_tuple (123, 6555, 40, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_6GHZ) },
  { std::make_tuple (131, 6595, 40, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_6GHZ) },
  { std::make_tuple (139, 6635, 40, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_6GHZ) },
  { std::make_tuple (147, 6675, 40, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_6GHZ) },
  { std::make_tuple (155, 6715, 40, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_6GHZ) },
  { std::make_tuple (163, 6755, 40, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_6GHZ) },
  { std::make_tuple (171, 6795, 40, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_6GHZ) },
  { std::make_tuple (179, 6835, 40, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_6GHZ) },
  { std::make_tuple (187, 6875, 40, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_6GHZ) },
  { std::make_tuple (195, 6915, 40, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_6GHZ) },
  { std::make_tuple (203, 6955, 40, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_6GHZ) },
  { std::make_tuple (211, 6995, 40, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_6GHZ) },
  { std::make_tuple (219, 7035, 40, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_6GHZ) },
  { std::make_tuple (227, 7075, 40, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_6GHZ) },
  // 80 MHz channels
  { std::make_tuple (7, 5975, 80, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_6GHZ) },
  { std::make_tuple (23, 6055, 80, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_6GHZ) },
  { std::make_tuple (39, 6135, 80, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_6GHZ) },
  { std::make_tuple (55, 6215, 80, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_6GHZ) },
  { std::make_tuple (71, 6295, 80, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_6GHZ) },
  { std::make_tuple (87, 6375, 80, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_6GHZ) },
  { std::make_tuple (103, 6455, 80, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_6GHZ) },
  { std::make_tuple (119, 6535, 80, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_6GHZ) },
  { std::make_tuple (135, 6615, 80, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_6GHZ) },
  { std::make_tuple (151, 6695, 80, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_6GHZ) },
  { std::make_tuple (167, 6775, 80, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_6GHZ) },
  { std::make_tuple (183, 6855, 80, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_6GHZ) },
  { std::make_tuple (199, 6935, 80, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_6GHZ) },
  { std::make_tuple (215, 7015, 80, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_6GHZ) },
  // 160 MHz channels
  { std::make_tuple (15, 6015, 160, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_6GHZ) },
  { std::make_tuple (47, 6175, 160, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_6GHZ) },
  { std::make_tuple (79, 6335, 160, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_6GHZ) },
  { std::make_tuple (111, 6495, 160, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_6GHZ) },
  { std::make_tuple (143, 6655, 160, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_6GHZ) },
  { std::make_tuple (175, 6815, 160, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_6GHZ) },
  { std::make_tuple (207, 6975, 160, WIFI_PHY_OFDM_CHANNEL, WIFI_PHY_BAND_6GHZ) }
};

std::map<WifiModulationClass, Ptr<PhyEntity> > WifiPhy::m_staticPhyEntities; //will be filled by g_constructor_XXX

>>>>>>> origin
TypeId
WifiPhy::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::WifiPhy")
    .SetParent<Object> ()
    .SetGroupName ("Wifi")
    .AddAttribute ("Frequency",
<<<<<<< HEAD
                   "The operating center frequency (MHz)",
                   UintegerValue (0),
                   MakeUintegerAccessor (&WifiPhy::GetFrequency,
                                         &WifiPhy::SetFrequency),
                   MakeUintegerChecker<uint32_t> ())
    .AddAttribute ("ChannelWidth",
                   "Whether 5MHz, 10MHz, 20MHz, 22MHz, 40MHz, 80 MHz or 160 MHz.",
                   UintegerValue (20),
                   MakeUintegerAccessor (&WifiPhy::GetChannelWidth,
                                         &WifiPhy::SetChannelWidth),
                   MakeUintegerChecker<uint32_t> ())
    .AddAttribute ("ChannelNumber",
                   "If set to non-zero defined value, will control Frequency and ChannelWidth assignment",
                   UintegerValue (0),
                   MakeUintegerAccessor (&WifiPhy::SetChannelNumber,
                                         &WifiPhy::GetChannelNumber),
                   MakeUintegerChecker<uint16_t> ())
    .AddAttribute ("EnergyDetectionThreshold",
                   "The energy of a received signal should be higher than "
                   "this threshold (dbm) to allow the PHY layer to detect the signal.",
                   DoubleValue (-96.0),
                   MakeDoubleAccessor (&WifiPhy::SetEdThreshold,
                                       &WifiPhy::GetEdThreshold),
                   MakeDoubleChecker<double> ())
    .AddAttribute ("CcaMode1Threshold",
                   "The energy of a received signal should be higher than "
                   "this threshold (dbm) to allow the PHY layer to declare CCA BUSY state.",
                   DoubleValue (-99.0),
                   MakeDoubleAccessor (&WifiPhy::SetCcaMode1Threshold,
                                       &WifiPhy::GetCcaMode1Threshold),
                   MakeDoubleChecker<double> ())
    .AddAttribute ("TxGain",
                   "Transmission gain (dB).",
                   DoubleValue (1.0),
=======
                   "The center frequency (MHz) of the operating channel. "
                   "If the operating channel for this object has not been set yet, the "
                   "value of this attribute is saved and will be used, along with the channel "
                   "number and width configured via other attributes, to set the operating "
                   "channel when the standard and band are configured. The default value of "
                   "this attribute is 0, which means unspecified center frequency. Note that "
                   "if center frequency and channel number are both 0 when the standard and "
                   "band are configured, a default channel (of the configured width, if any, "
                   "or the default width for the current standard and band, otherwise) is set. "
                   "If the operating channel for this object has been already set, the "
                   "specified center frequency must uniquely identify a channel in the "
                   "band being used.",
                   UintegerValue (0),
                   MakeUintegerAccessor (&WifiPhy::GetFrequency,
                                         &WifiPhy::SetFrequency),
                   MakeUintegerChecker<uint16_t> ())
    .AddAttribute ("ChannelNumber",
                   "The channel number of the operating channel. "
                   "If the operating channel for this object has not been set yet, the "
                   "value of this attribute is saved and will be used, along with the center "
                   "frequency and width configured via other attributes, to set the operating "
                   "channel when the standard and band are configured. The default value of "
                   "this attribute is 0, which means unspecified channel number. Note that "
                   "if center frequency and channel number are both 0 when the standard and "
                   "band are configured, a default channel (of the configured width, if any, "
                   "or the default width for the current standard and band, otherwise) is set. "
                   "If the operating channel for this object has been already set, the "
                   "specified channel number must uniquely identify a channel in the "
                   "band being used.",
                   UintegerValue (0),
                   MakeUintegerAccessor (&WifiPhy::SetChannelNumber,
                                         &WifiPhy::GetChannelNumber),
                   MakeUintegerChecker<uint8_t> (0, 233))
    .AddAttribute ("ChannelWidth",
                   "The width in MHz of the operating channel (5, 10, 20, 22, 40, 80 or 160). "
                   "If the operating channel for this object has not been set yet, the "
                   "value of this attribute is saved and will be used, along with the center "
                   "frequency and channel number configured via other attributes, to set the "
                   "operating channel when the standard and band are configured. The default value "
                   "of this attribute is 0, which means unspecified channel width. Note that "
                   "if center frequency and channel number are both 0 when the standard and "
                   "band are configured, a default channel (of the configured width, if any, "
                   "or the default width for the current standard and band, otherwise) is set. "
                   "Do not set this attribute when the standard and band of this object have "
                   "been already configured, because it cannot uniquely identify a channel in "
                   "the band being used.",
                   UintegerValue (0),
                   MakeUintegerAccessor (&WifiPhy::GetChannelWidth,
                                         &WifiPhy::SetChannelWidth),
                   MakeUintegerChecker<uint16_t> (5, 160))
    .AddAttribute ("Primary20MHzIndex",
                   "The index of the primary 20 MHz channel within the operating channel "
                   "(0 indicates the 20 MHz subchannel with the lowest center frequency). "
                   "This attribute is only valid if the width of the operating channel is "
                   "a multiple of 20 MHz.",
                   UintegerValue (0),
                   MakeUintegerAccessor (&WifiPhy::SetPrimary20Index),
                   MakeUintegerChecker<uint8_t> (0, 7))
    .AddAttribute ("RxSensitivity",
                   "The energy of a received signal should be higher than "
                   "this threshold (dBm) for the PHY to detect the signal. "
                   "This threshold refers to a width of 20 MHz and will be "
                   "scaled to match the width of the received signal.",
                   DoubleValue (-101.0),
                   MakeDoubleAccessor (&WifiPhy::SetRxSensitivity,
                                       &WifiPhy::GetRxSensitivity),
                   MakeDoubleChecker<double> ())
    .AddAttribute ("CcaEdThreshold",
                   "The energy of a non Wi-Fi received signal should be higher than "
                   "this threshold (dBm) to allow the PHY layer to declare CCA BUSY state. "
                   "This check is performed on the 20 MHz primary channel only.",
                   DoubleValue (-62.0),
                   MakeDoubleAccessor (&WifiPhy::SetCcaEdThreshold,
                                       &WifiPhy::GetCcaEdThreshold),
                   MakeDoubleChecker<double> ())
    .AddAttribute ("TxGain",
                   "Transmission gain (dB).",
                   DoubleValue (0.0),
>>>>>>> origin
                   MakeDoubleAccessor (&WifiPhy::SetTxGain,
                                       &WifiPhy::GetTxGain),
                   MakeDoubleChecker<double> ())
    .AddAttribute ("RxGain",
                   "Reception gain (dB).",
<<<<<<< HEAD
                   DoubleValue (1.0),
=======
                   DoubleValue (0.0),
>>>>>>> origin
                   MakeDoubleAccessor (&WifiPhy::SetRxGain,
                                       &WifiPhy::GetRxGain),
                   MakeDoubleChecker<double> ())
    .AddAttribute ("TxPowerLevels",
                   "Number of transmission power levels available between "
                   "TxPowerStart and TxPowerEnd included.",
                   UintegerValue (1),
                   MakeUintegerAccessor (&WifiPhy::m_nTxPower),
<<<<<<< HEAD
                   MakeUintegerChecker<uint32_t> ())
    .AddAttribute ("TxPowerEnd",
                   "Maximum available transmission level (dbm).",
=======
                   MakeUintegerChecker<uint8_t> ())
    .AddAttribute ("TxPowerEnd",
                   "Maximum available transmission level (dBm).",
>>>>>>> origin
                   DoubleValue (16.0206),
                   MakeDoubleAccessor (&WifiPhy::SetTxPowerEnd,
                                       &WifiPhy::GetTxPowerEnd),
                   MakeDoubleChecker<double> ())
    .AddAttribute ("TxPowerStart",
<<<<<<< HEAD
                   "Minimum available transmission level (dbm).",
=======
                   "Minimum available transmission level (dBm).",
>>>>>>> origin
                   DoubleValue (16.0206),
                   MakeDoubleAccessor (&WifiPhy::SetTxPowerStart,
                                       &WifiPhy::GetTxPowerStart),
                   MakeDoubleChecker<double> ())
    .AddAttribute ("RxNoiseFigure",
                   "Loss (dB) in the Signal-to-Noise-Ratio due to non-idealities in the receiver."
                   " According to Wikipedia (http://en.wikipedia.org/wiki/Noise_figure), this is "
                   "\"the difference in decibels (dB) between"
                   " the noise output of the actual receiver to the noise output of an "
                   " ideal receiver with the same overall gain and bandwidth when the receivers "
                   " are connected to sources at the standard noise temperature T0 (usually 290 K)\".",
                   DoubleValue (7),
<<<<<<< HEAD
                   MakeDoubleAccessor (&WifiPhy::SetRxNoiseFigure,
                                       &WifiPhy::GetRxNoiseFigure),
=======
                   MakeDoubleAccessor (&WifiPhy::SetRxNoiseFigure),
>>>>>>> origin
                   MakeDoubleChecker<double> ())
    .AddAttribute ("State",
                   "The state of the PHY layer.",
                   PointerValue (),
                   MakePointerAccessor (&WifiPhy::m_state),
                   MakePointerChecker<WifiPhyStateHelper> ())
    .AddAttribute ("ChannelSwitchDelay",
                   "Delay between two short frames transmitted on different frequencies.",
                   TimeValue (MicroSeconds (250)),
                   MakeTimeAccessor (&WifiPhy::m_channelSwitchDelay),
                   MakeTimeChecker ())
<<<<<<< HEAD
    .AddAttribute ("TxAntennas",
                   "The number of supported Tx antennas.",
                   UintegerValue (1),
                   MakeUintegerAccessor (&WifiPhy::GetNumberOfTransmitAntennas,
                                         &WifiPhy::SetNumberOfTransmitAntennas),
                   MakeUintegerChecker<uint32_t> ())
    .AddAttribute ("RxAntennas",
                   "The number of supported Rx antennas.",
                   UintegerValue (1),
                   MakeUintegerAccessor (&WifiPhy::GetNumberOfReceiveAntennas,
                                         &WifiPhy::SetNumberOfReceiveAntennas),
                   MakeUintegerChecker<uint32_t> ())
    .AddAttribute ("ShortGuardEnabled",
                   "Whether or not short guard interval is enabled."
                   "This parameter is only valuable for 802.11n/ac STAs and APs.",
                   BooleanValue (false),
                   MakeBooleanAccessor (&WifiPhy::GetGuardInterval,
                                        &WifiPhy::SetGuardInterval),
                   MakeBooleanChecker ())
    .AddAttribute ("LdpcEnabled",
                   "Whether or not LDPC is enabled.",
                   BooleanValue (false),
                   MakeBooleanAccessor (&WifiPhy::GetLdpc,
                                        &WifiPhy::SetLdpc),
                   MakeBooleanChecker ())
    .AddAttribute ("STBCEnabled",
                   "Whether or not STBC is enabled.",
                   BooleanValue (false),
                   MakeBooleanAccessor (&WifiPhy::GetStbc,
                                        &WifiPhy::SetStbc),
                   MakeBooleanChecker ())
    .AddAttribute ("GreenfieldEnabled",
                   "Whether or not Greenfield is enabled."
                   "This parameter is only valuable for 802.11n STAs and APs.",
                   BooleanValue (false),
                   MakeBooleanAccessor (&WifiPhy::GetGreenfield,
                                        &WifiPhy::SetGreenfield),
                   MakeBooleanChecker ())
    .AddAttribute ("ShortPlcpPreambleSupported",
                   "Whether or not short PLCP preamble is supported."
                   "This parameter is only valuable for 802.11b STAs and APs."
                   "Note: 802.11g APs and STAs always support short PLCP preamble.",
                   BooleanValue (false),
                   MakeBooleanAccessor (&WifiPhy::GetShortPlcpPreambleSupported,
                                        &WifiPhy::SetShortPlcpPreambleSupported),
                   MakeBooleanChecker ())
=======
    .AddAttribute ("Antennas",
                   "The number of antennas on the device.",
                   UintegerValue (1),
                   MakeUintegerAccessor (&WifiPhy::GetNumberOfAntennas,
                                         &WifiPhy::SetNumberOfAntennas),
                   MakeUintegerChecker<uint8_t> (1, 8))
    .AddAttribute ("MaxSupportedTxSpatialStreams",
                   "The maximum number of supported TX spatial streams."
                   "This parameter is only valuable for 802.11n/ac/ax STAs and APs.",
                   UintegerValue (1),
                   MakeUintegerAccessor (&WifiPhy::GetMaxSupportedTxSpatialStreams,
                                         &WifiPhy::SetMaxSupportedTxSpatialStreams),
                   MakeUintegerChecker<uint8_t> (1, 8))
    .AddAttribute ("MaxSupportedRxSpatialStreams",
                   "The maximum number of supported RX spatial streams."
                   "This parameter is only valuable for 802.11n/ac/ax STAs and APs.",
                   UintegerValue (1),
                   MakeUintegerAccessor (&WifiPhy::GetMaxSupportedRxSpatialStreams,
                                         &WifiPhy::SetMaxSupportedRxSpatialStreams),
                   MakeUintegerChecker<uint8_t> (1, 8))
    .AddAttribute ("ShortPlcpPreambleSupported",
                   "Whether or not short PHY preamble is supported."
                   "This parameter is only valuable for 802.11b STAs and APs."
                   "Note: 802.11g APs and STAs always support short PHY preamble.",
                   BooleanValue (false),
                   MakeBooleanAccessor (&WifiPhy::GetShortPhyPreambleSupported,
                                        &WifiPhy::SetShortPhyPreambleSupported),
                   MakeBooleanChecker ())
    .AddAttribute ("FrameCaptureModel",
                   "Ptr to an object that implements the frame capture model",
                   PointerValue (),
                   MakePointerAccessor (&WifiPhy::m_frameCaptureModel),
                   MakePointerChecker <FrameCaptureModel> ())
    .AddAttribute ("PreambleDetectionModel",
                   "Ptr to an object that implements the preamble detection model",
                   PointerValue (),
                   MakePointerAccessor (&WifiPhy::m_preambleDetectionModel),
                   MakePointerChecker <PreambleDetectionModel> ())
    .AddAttribute ("PostReceptionErrorModel",
                   "An optional packet error model can be added to the receive "
                   "packet process after any propagation-based (SNR-based) error "
                   "models have been applied. Typically this is used to force "
                   "specific packet drops, for testing purposes.",
                   PointerValue (),
                   MakePointerAccessor (&WifiPhy::m_postReceptionErrorModel),
                   MakePointerChecker<ErrorModel> ())
    .AddAttribute ("Sifs",
                   "The duration of the Short Interframe Space. "
                   "NOTE that the default value is overwritten by the value defined "
                   "by the standard; if you want to set this attribute, you have to "
                   "do it after that the PHY object is initialized.",
                   TimeValue (MicroSeconds (0)),
                   MakeTimeAccessor (&WifiPhy::m_sifs),
                   MakeTimeChecker ())
    .AddAttribute ("Slot",
                   "The duration of a slot. "
                   "NOTE that the default value is overwritten by the value defined "
                   "by the standard; if you want to set this attribute, you have to "
                   "do it after that the PHY object is initialized.",
                   TimeValue (MicroSeconds (0)),
                   MakeTimeAccessor (&WifiPhy::m_slot),
                   MakeTimeChecker ())
    .AddAttribute ("Pifs",
                   "The duration of the PCF Interframe Space. "
                   "NOTE that the default value is overwritten by the value defined "
                   "by the standard; if you want to set this attribute, you have to "
                   "do it after that the PHY object is initialized.",
                   TimeValue (MicroSeconds (0)),
                   MakeTimeAccessor (&WifiPhy::m_pifs),
                   MakeTimeChecker ())
    .AddAttribute ("PowerDensityLimit",
                   "The mean equivalent isotropically radiated power density"
                   "limit (in dBm/MHz) set by regulators.",
                   DoubleValue (100.0), //set to a high value so as to have no effect
                   MakeDoubleAccessor (&WifiPhy::m_powerDensityLimit),
                   MakeDoubleChecker<double> ())
>>>>>>> origin
    .AddTraceSource ("PhyTxBegin",
                     "Trace source indicating a packet "
                     "has begun transmitting over the channel medium",
                     MakeTraceSourceAccessor (&WifiPhy::m_phyTxBeginTrace),
                     "ns3::WifiPhy::PhyTxBeginTracedCallback")
    .AddTraceSource ("PhyTxPsduBegin",
                     "Trace source indicating a PSDU "
                     "has begun transmitting over the channel medium",
                     MakeTraceSourceAccessor (&WifiPhy::m_phyTxPsduBeginTrace),
                     "ns3::WifiPhy::PsduTxBeginCallback")
    .AddTraceSource ("PhyTxEnd",
                     "Trace source indicating a packet "
<<<<<<< HEAD
                     "has been completely transmitted over the channel. "
                     "NOTE: the only official WifiPhy implementation "
                     "available to this date never fires "
                     "this trace source.",
=======
                     "has been completely transmitted over the channel.",
>>>>>>> origin
                     MakeTraceSourceAccessor (&WifiPhy::m_phyTxEndTrace),
                     "ns3::Packet::TracedCallback")
    .AddTraceSource ("PhyTxDrop",
                     "Trace source indicating a packet "
                     "has been dropped by the device during transmission",
                     MakeTraceSourceAccessor (&WifiPhy::m_phyTxDropTrace),
                     "ns3::Packet::TracedCallback")
    .AddTraceSource ("PhyRxBegin",
                     "Trace source indicating a packet "
                     "has begun being received from the channel medium "
                     "by the device",
                     MakeTraceSourceAccessor (&WifiPhy::m_phyRxBeginTrace),
                     "ns3::WifiPhy::PhyRxBeginTracedCallback")
    .AddTraceSource ("PhyRxPayloadBegin",
                     "Trace source indicating the reception of the "
                     "payload of a PPDU has begun",
                     MakeTraceSourceAccessor (&WifiPhy::m_phyRxPayloadBeginTrace),
                     "ns3::WifiPhy::PhyRxPayloadBeginTracedCallback")
    .AddTraceSource ("PhyRxEnd",
                     "Trace source indicating a packet "
                     "has been completely received from the channel medium "
                     "by the device",
                     MakeTraceSourceAccessor (&WifiPhy::m_phyRxEndTrace),
                     "ns3::Packet::TracedCallback")
    .AddTraceSource ("PhyRxDrop",
                     "Trace source indicating a packet "
                     "has been dropped by the device during reception",
                     MakeTraceSourceAccessor (&WifiPhy::m_phyRxDropTrace),
                     "ns3::Packet::TracedCallback")
    .AddTraceSource ("MonitorSnifferRx",
                     "Trace source simulating a wifi device in monitor mode "
                     "sniffing all received frames",
                     MakeTraceSourceAccessor (&WifiPhy::m_phyMonitorSniffRxTrace),
                     "ns3::WifiPhy::MonitorSnifferRxTracedCallback")
    .AddTraceSource ("MonitorSnifferTx",
                     "Trace source simulating the capability of a wifi device "
                     "in monitor mode to sniff all frames being transmitted",
                     MakeTraceSourceAccessor (&WifiPhy::m_phyMonitorSniffTxTrace),
                     "ns3::WifiPhy::MonitorSnifferTxTracedCallback")
  ;
  return tid;
}

WifiPhy::WifiPhy ()
<<<<<<< HEAD
  : m_mpdusNum (0),
    m_plcpSuccess (false),
    m_txMpduReferenceNumber (0xffffffff),
    m_rxMpduReferenceNumber (0xffffffff),
    m_endRxEvent (),
    m_endPlcpRxEvent (),
    m_standard (WIFI_PHY_STANDARD_UNSPECIFIED),
    m_isConstructed (false),
    m_channelCenterFrequency (0),
    m_initialFrequency (0),
    m_frequencyChannelNumberInitialized (false),
    m_channelNumber (0),
    m_initialChannelNumber (0),
    m_totalAmpduSize (0),
    m_totalAmpduNumSymbols (0)
=======
  : m_txMpduReferenceNumber (0xffffffff),
    m_rxMpduReferenceNumber (0xffffffff),
    m_endPhyRxEvent (),
    m_endTxEvent (),
    m_currentEvent (0),
    m_previouslyRxPpduUid (UINT64_MAX),
    m_standard (WIFI_PHY_STANDARD_UNSPECIFIED),
    m_band (WIFI_PHY_BAND_UNSPECIFIED),
    m_initialFrequency (0),
    m_initialChannelNumber (0),
    m_initialChannelWidth (0),
    m_initialPrimary20Index (0),
    m_sifs (Seconds (0)),
    m_slot (Seconds (0)),
    m_pifs (Seconds (0)),
    m_ackTxTime (Seconds (0)),
    m_blockAckTxTime (Seconds (0)),
    m_powerRestricted (false),
    m_channelAccessRequested (false),
    m_txSpatialStreams (0),
    m_rxSpatialStreams (0),
    m_wifiRadioEnergyModel (0),
    m_timeLastPreambleDetected (Seconds (0))
>>>>>>> origin
{
  NS_LOG_FUNCTION (this);
  m_random = CreateObject<UniformRandomVariable> ();
  m_state = CreateObject<WifiPhyStateHelper> ();
}

WifiPhy::~WifiPhy ()
{
  NS_LOG_FUNCTION (this);
}

void
WifiPhy::DoDispose (void)
<<<<<<< HEAD
{
  NS_LOG_FUNCTION (this);
  m_device = 0;
  m_mobility = 0;
  m_state = 0;
  m_deviceRateSet.clear ();
  m_deviceMcsSet.clear ();
}

void 
WifiPhy::DoInitialize (void)
{
  NS_LOG_FUNCTION (this); 
  m_isConstructed = true;
  if (m_frequencyChannelNumberInitialized == true)
    {
      NS_LOG_DEBUG ("Frequency already initialized");
      return;
    }
  InitializeFrequencyChannelNumber ();
}

void
WifiPhy::InitializeFrequencyChannelNumber (void)
{
  NS_LOG_FUNCTION (this);

  NS_ASSERT_MSG (m_frequencyChannelNumberInitialized == false, "Initialization called twice");

  // If frequency has been set to a non-zero value during attribute
  // construction phase, the frequency and channel width will drive the
  // initial configuration.  If frequency has not been set, but both
  // standard and channel number have been set, that pair will instead
  // drive the configuration, and frequency and channel number will be 
  // aligned
  if (m_initialFrequency != 0)
    {
      SetFrequency (m_initialFrequency);
    }
  else if (m_initialChannelNumber != 0 && GetStandard () != WIFI_PHY_STANDARD_UNSPECIFIED)
    {
      SetChannelNumber (m_initialChannelNumber);
    }
  else if (m_initialChannelNumber != 0 && GetStandard () == WIFI_PHY_STANDARD_UNSPECIFIED)
    {
      NS_FATAL_ERROR ("Error, ChannelNumber " << GetChannelNumber () << " was set by user, but neither a standard nor a frequency");
    }
  m_frequencyChannelNumberInitialized = true;
}

void
WifiPhy::SetEdThreshold (double threshold)
{
  NS_LOG_FUNCTION (this << threshold);
  m_edThresholdW = DbmToW (threshold);
}

double
WifiPhy::GetEdThresholdW (void) const
{
  return m_edThresholdW;
}

double
WifiPhy::GetEdThreshold (void) const
{
  return WToDbm (m_edThresholdW);
}

void
WifiPhy::SetCcaMode1Threshold (double threshold)
{
  NS_LOG_FUNCTION (this << threshold);
  m_ccaMode1ThresholdW = DbmToW (threshold);
}

double
WifiPhy::GetCcaMode1Threshold (void) const
{
  return WToDbm (m_ccaMode1ThresholdW);
}

void
WifiPhy::SetRxNoiseFigure (double noiseFigureDb)
{
  NS_LOG_FUNCTION (this << noiseFigureDb);
  m_interference.SetNoiseFigure (DbToRatio (noiseFigureDb));
}

double
WifiPhy::GetRxNoiseFigure (void) const
{
  return RatioToDb (m_interference.GetNoiseFigure ());
}

void
WifiPhy::SetTxPowerStart (double start)
{
  NS_LOG_FUNCTION (this << start);
  m_txPowerBaseDbm = start;
}

double
WifiPhy::GetTxPowerStart (void) const
{
  return m_txPowerBaseDbm;
}

void
WifiPhy::SetTxPowerEnd (double end)
{
  NS_LOG_FUNCTION (this << end);
  m_txPowerEndDbm = end;
}

double
WifiPhy::GetTxPowerEnd (void) const
{
  return m_txPowerEndDbm;
}

void
WifiPhy::SetNTxPower (uint32_t n)
{
  NS_LOG_FUNCTION (this << n);
  m_nTxPower = n;
}

uint32_t
WifiPhy::GetNTxPower (void) const
{
  return m_nTxPower;
}

void
WifiPhy::SetTxGain (double gain)
{
  NS_LOG_FUNCTION (this << gain);
  m_txGainDb = gain;
}

double
WifiPhy::GetTxGain (void) const
{
  return m_txGainDb;
}

void
WifiPhy::SetRxGain (double gain)
{
  NS_LOG_FUNCTION (this << gain);
  m_rxGainDb = gain;
}

double
WifiPhy::GetRxGain (void) const
{
  return m_rxGainDb;
}

void
WifiPhy::SetLdpc (bool ldpc)
{
  NS_LOG_FUNCTION (this << ldpc);
  m_ldpc = ldpc;
}

bool
WifiPhy::GetLdpc (void) const
{
  return m_ldpc;
}

void
WifiPhy::SetStbc (bool stbc)
{
  NS_LOG_FUNCTION (this << stbc);
  m_stbc = stbc;
}

bool
WifiPhy::GetStbc (void) const
{
  return m_stbc;
}

void
WifiPhy::SetGreenfield (bool greenfield)
{
  NS_LOG_FUNCTION (this << greenfield);
  m_greenfield = greenfield;
}

bool
WifiPhy::GetGreenfield (void) const
{
  return m_greenfield;
}

void
WifiPhy::SetGuardInterval (bool guardInterval)
{
  NS_LOG_FUNCTION (this << guardInterval);
  m_guardInterval = guardInterval;
}

bool
WifiPhy::GetGuardInterval (void) const
{
  return m_guardInterval;
}

void
WifiPhy::SetShortPlcpPreambleSupported (bool enable)
{
  NS_LOG_FUNCTION (this << enable);
  m_shortPreamble = enable;
}

bool
WifiPhy::GetShortPlcpPreambleSupported (void) const
{
  return m_shortPreamble;
}

void
WifiPhy::SetDevice (Ptr<NetDevice> device)
{
  m_device = device;
}

Ptr<NetDevice>
WifiPhy::GetDevice (void) const
{
  return m_device;
}

void
WifiPhy::SetMobility (Ptr<MobilityModel> mobility)
{
  m_mobility = mobility;
}

Ptr<MobilityModel>
WifiPhy::GetMobility (void)
{
  if (m_mobility != 0)
    {
      return m_mobility;
    }
  else
    {
      return m_device->GetNode ()->GetObject<MobilityModel> ();
    }
}

void
WifiPhy::SetErrorRateModel (Ptr<ErrorRateModel> rate)
{
  m_interference.SetErrorRateModel (rate);
}

Ptr<ErrorRateModel>
WifiPhy::GetErrorRateModel (void) const
{
  return m_interference.GetErrorRateModel ();
}

double
WifiPhy::GetPowerDbm (uint8_t power) const
{
  NS_ASSERT (m_txPowerBaseDbm <= m_txPowerEndDbm);
  NS_ASSERT (m_nTxPower > 0);
  double dbm;
  if (m_nTxPower > 1)
    {
      dbm = m_txPowerBaseDbm + power * (m_txPowerEndDbm - m_txPowerBaseDbm) / (m_nTxPower - 1);
    }
  else
    {
      NS_ASSERT_MSG (m_txPowerBaseDbm == m_txPowerEndDbm, "cannot have TxPowerEnd != TxPowerStart with TxPowerLevels == 1");
      dbm = m_txPowerBaseDbm;
    }
  return dbm;
}

Time
WifiPhy::GetChannelSwitchDelay (void) const
{
  return m_channelSwitchDelay;
}

double
WifiPhy::CalculateSnr (WifiTxVector txVector, double ber) const
{
  return m_interference.GetErrorRateModel ()->CalculateSnr (txVector, ber);
}

void
WifiPhy::ConfigureDefaultsForStandard (enum WifiPhyStandard standard)
{
  NS_LOG_FUNCTION (this << standard);
  switch (standard)
    {
    case WIFI_PHY_STANDARD_80211a:
      SetChannelWidth (20);
      SetFrequency (5180);
      // Channel number should be aligned by SetFrequency () to 36
      NS_ASSERT (GetChannelNumber () == 36);
      break;
    case WIFI_PHY_STANDARD_80211b:
      SetChannelWidth (22);
      SetFrequency (2412);
      // Channel number should be aligned by SetFrequency () to 1
      NS_ASSERT (GetChannelNumber () == 1);
      break;
    case WIFI_PHY_STANDARD_80211g:
      SetChannelWidth (20);
      SetFrequency (2412);
      // Channel number should be aligned by SetFrequency () to 1
      NS_ASSERT (GetChannelNumber () == 1);
      break;
    case WIFI_PHY_STANDARD_80211_10MHZ:
      SetChannelWidth (10);
      SetFrequency (5860);
      // Channel number should be aligned by SetFrequency () to 172
      NS_ASSERT (GetChannelNumber () == 172);
      break;
    case WIFI_PHY_STANDARD_80211_5MHZ:
      SetChannelWidth (5);
      SetFrequency (5860);
      // Channel number should be aligned by SetFrequency () to 0 
      NS_ASSERT (GetChannelNumber () == 0);
      break;
    case WIFI_PHY_STANDARD_holland:
      SetChannelWidth (20);
      SetFrequency (5180);
      // Channel number should be aligned by SetFrequency () to 36
      NS_ASSERT (GetChannelNumber () == 36);
      break;
    case WIFI_PHY_STANDARD_80211n_2_4GHZ:
      SetChannelWidth (20);
      SetFrequency (2412);
      // Channel number should be aligned by SetFrequency () to 1
      NS_ASSERT (GetChannelNumber () == 1);
      break;
    case WIFI_PHY_STANDARD_80211n_5GHZ:
      SetChannelWidth (20);
      SetFrequency (5180);
      // Channel number should be aligned by SetFrequency () to 36
      NS_ASSERT (GetChannelNumber () == 36);
      break;
    case WIFI_PHY_STANDARD_80211ac:
      SetChannelWidth (80);
      SetFrequency (5210);
      // Channel number should be aligned by SetFrequency () to 42
      NS_ASSERT (GetChannelNumber () == 42);
      break;
    case WIFI_PHY_STANDARD_UNSPECIFIED:
      NS_LOG_WARN ("Configuring unspecified standard; performing no action");
      break;
    default:
      NS_ASSERT (false);
      break;
    }
}

void
WifiPhy::Configure80211a (void)
{
  NS_LOG_FUNCTION (this);

  m_deviceRateSet.push_back (WifiPhy::GetOfdmRate6Mbps ());
  m_deviceRateSet.push_back (WifiPhy::GetOfdmRate9Mbps ());
  m_deviceRateSet.push_back (WifiPhy::GetOfdmRate12Mbps ());
  m_deviceRateSet.push_back (WifiPhy::GetOfdmRate18Mbps ());
  m_deviceRateSet.push_back (WifiPhy::GetOfdmRate24Mbps ());
  m_deviceRateSet.push_back (WifiPhy::GetOfdmRate36Mbps ());
  m_deviceRateSet.push_back (WifiPhy::GetOfdmRate48Mbps ());
  m_deviceRateSet.push_back (WifiPhy::GetOfdmRate54Mbps ());
}

void
WifiPhy::Configure80211b (void)
{
  NS_LOG_FUNCTION (this);

  m_deviceRateSet.push_back (WifiPhy::GetDsssRate1Mbps ());
  m_deviceRateSet.push_back (WifiPhy::GetDsssRate2Mbps ());
  m_deviceRateSet.push_back (WifiPhy::GetDsssRate5_5Mbps ());
  m_deviceRateSet.push_back (WifiPhy::GetDsssRate11Mbps ());
}

void
WifiPhy::Configure80211g (void)
{
  NS_LOG_FUNCTION (this);
  Configure80211b ();

  m_deviceRateSet.push_back (WifiPhy::GetErpOfdmRate6Mbps ());
  m_deviceRateSet.push_back (WifiPhy::GetErpOfdmRate9Mbps ());
  m_deviceRateSet.push_back (WifiPhy::GetErpOfdmRate12Mbps ());
  m_deviceRateSet.push_back (WifiPhy::GetErpOfdmRate18Mbps ());
  m_deviceRateSet.push_back (WifiPhy::GetErpOfdmRate24Mbps ());
  m_deviceRateSet.push_back (WifiPhy::GetErpOfdmRate36Mbps ());
  m_deviceRateSet.push_back (WifiPhy::GetErpOfdmRate48Mbps ());
  m_deviceRateSet.push_back (WifiPhy::GetErpOfdmRate54Mbps ());
}

void
WifiPhy::Configure80211_10Mhz (void)
{
  NS_LOG_FUNCTION (this);

  m_deviceRateSet.push_back (WifiPhy::GetOfdmRate3MbpsBW10MHz ());
  m_deviceRateSet.push_back (WifiPhy::GetOfdmRate4_5MbpsBW10MHz ());
  m_deviceRateSet.push_back (WifiPhy::GetOfdmRate6MbpsBW10MHz ());
  m_deviceRateSet.push_back (WifiPhy::GetOfdmRate9MbpsBW10MHz ());
  m_deviceRateSet.push_back (WifiPhy::GetOfdmRate12MbpsBW10MHz ());
  m_deviceRateSet.push_back (WifiPhy::GetOfdmRate18MbpsBW10MHz ());
  m_deviceRateSet.push_back (WifiPhy::GetOfdmRate24MbpsBW10MHz ());
  m_deviceRateSet.push_back (WifiPhy::GetOfdmRate27MbpsBW10MHz ());
}

void
WifiPhy::Configure80211_5Mhz (void)
{
  NS_LOG_FUNCTION (this);

  m_deviceRateSet.push_back (WifiPhy::GetOfdmRate1_5MbpsBW5MHz ());
  m_deviceRateSet.push_back (WifiPhy::GetOfdmRate2_25MbpsBW5MHz ());
  m_deviceRateSet.push_back (WifiPhy::GetOfdmRate3MbpsBW5MHz ());
  m_deviceRateSet.push_back (WifiPhy::GetOfdmRate4_5MbpsBW5MHz ());
  m_deviceRateSet.push_back (WifiPhy::GetOfdmRate6MbpsBW5MHz ());
  m_deviceRateSet.push_back (WifiPhy::GetOfdmRate9MbpsBW5MHz ());
  m_deviceRateSet.push_back (WifiPhy::GetOfdmRate12MbpsBW5MHz ());
  m_deviceRateSet.push_back (WifiPhy::GetOfdmRate13_5MbpsBW5MHz ());
}

void
WifiPhy::ConfigureHolland (void)
{
  NS_LOG_FUNCTION (this);

  m_deviceRateSet.push_back (WifiPhy::GetOfdmRate6Mbps ());
  m_deviceRateSet.push_back (WifiPhy::GetOfdmRate12Mbps ());
  m_deviceRateSet.push_back (WifiPhy::GetOfdmRate18Mbps ());
  m_deviceRateSet.push_back (WifiPhy::GetOfdmRate36Mbps ());
  m_deviceRateSet.push_back (WifiPhy::GetOfdmRate54Mbps ());
}

void
WifiPhy::ConfigureHtDeviceMcsSet (void)
{
  NS_LOG_FUNCTION (this);

  bool htFound = false;
  for (std::vector<uint32_t>::size_type i = 0; i < m_bssMembershipSelectorSet.size (); i++)
    {
      if (m_bssMembershipSelectorSet[i] == HT_PHY)
        {
          htFound = true;
          break;
        }
    }
  if (htFound)
    {
      // erase all HtMcs modes from deviceMcsSet
      size_t index = m_deviceMcsSet.size () - 1;
      for (std::vector<WifiMode>::reverse_iterator rit = m_deviceMcsSet.rbegin (); rit != m_deviceMcsSet.rend(); ++rit, --index)
        {
          if (m_deviceMcsSet[index].GetModulationClass ()== WIFI_MOD_CLASS_HT)
            {
              m_deviceMcsSet.erase (m_deviceMcsSet.begin () + index);
            }
        }
      m_deviceMcsSet.push_back (WifiPhy::GetHtMcs0 ());
      m_deviceMcsSet.push_back (WifiPhy::GetHtMcs1 ());
      m_deviceMcsSet.push_back (WifiPhy::GetHtMcs2 ());
      m_deviceMcsSet.push_back (WifiPhy::GetHtMcs3 ());
      m_deviceMcsSet.push_back (WifiPhy::GetHtMcs4 ());
      m_deviceMcsSet.push_back (WifiPhy::GetHtMcs5 ());
      m_deviceMcsSet.push_back (WifiPhy::GetHtMcs6 ());
      m_deviceMcsSet.push_back (WifiPhy::GetHtMcs7 ());
      if (GetSupportedTxSpatialStreams () > 1)
        {
          m_deviceMcsSet.push_back (WifiPhy::GetHtMcs8 ());
          m_deviceMcsSet.push_back (WifiPhy::GetHtMcs9 ());
          m_deviceMcsSet.push_back (WifiPhy::GetHtMcs10 ());
          m_deviceMcsSet.push_back (WifiPhy::GetHtMcs11 ());
          m_deviceMcsSet.push_back (WifiPhy::GetHtMcs12 ());
          m_deviceMcsSet.push_back (WifiPhy::GetHtMcs13 ());
          m_deviceMcsSet.push_back (WifiPhy::GetHtMcs14 ());
          m_deviceMcsSet.push_back (WifiPhy::GetHtMcs15 ());
        }
      if (GetSupportedTxSpatialStreams () > 2)
        {
          m_deviceMcsSet.push_back (WifiPhy::GetHtMcs16 ());
          m_deviceMcsSet.push_back (WifiPhy::GetHtMcs17 ());
          m_deviceMcsSet.push_back (WifiPhy::GetHtMcs18 ());
          m_deviceMcsSet.push_back (WifiPhy::GetHtMcs19 ());
          m_deviceMcsSet.push_back (WifiPhy::GetHtMcs20 ());
          m_deviceMcsSet.push_back (WifiPhy::GetHtMcs21 ());
          m_deviceMcsSet.push_back (WifiPhy::GetHtMcs22 ());
          m_deviceMcsSet.push_back (WifiPhy::GetHtMcs23 ());
        }
      if (GetSupportedTxSpatialStreams () > 3)
        {
          m_deviceMcsSet.push_back (WifiPhy::GetHtMcs24 ());
          m_deviceMcsSet.push_back (WifiPhy::GetHtMcs25 ());
          m_deviceMcsSet.push_back (WifiPhy::GetHtMcs26 ());
          m_deviceMcsSet.push_back (WifiPhy::GetHtMcs27 ());
          m_deviceMcsSet.push_back (WifiPhy::GetHtMcs28 ());
          m_deviceMcsSet.push_back (WifiPhy::GetHtMcs29 ());
          m_deviceMcsSet.push_back (WifiPhy::GetHtMcs30 ());
          m_deviceMcsSet.push_back (WifiPhy::GetHtMcs31 ());
        }
    }
}

void
WifiPhy::Configure80211n (void)
{
  NS_LOG_FUNCTION (this);
  if (GetFrequency () >= 2400 && GetFrequency () <= 2500) //at 2.4 GHz
    {
      Configure80211b ();
      Configure80211g ();
    }
  if (GetFrequency () >= 5000 && GetFrequency () <= 6000) //at 5 GHz
    {
      Configure80211a ();
    }
  m_bssMembershipSelectorSet.push_back (HT_PHY);
  ConfigureHtDeviceMcsSet ();
}

void
WifiPhy::Configure80211ac (void)
{
  NS_LOG_FUNCTION (this);
  Configure80211n ();

  m_deviceMcsSet.push_back (WifiPhy::GetVhtMcs0 ());
  m_deviceMcsSet.push_back (WifiPhy::GetVhtMcs1 ());
  m_deviceMcsSet.push_back (WifiPhy::GetVhtMcs2 ());
  m_deviceMcsSet.push_back (WifiPhy::GetVhtMcs3 ());
  m_deviceMcsSet.push_back (WifiPhy::GetVhtMcs4 ());
  m_deviceMcsSet.push_back (WifiPhy::GetVhtMcs5 ());
  m_deviceMcsSet.push_back (WifiPhy::GetVhtMcs6 ());
  m_deviceMcsSet.push_back (WifiPhy::GetVhtMcs7 ());
  m_deviceMcsSet.push_back (WifiPhy::GetVhtMcs8 ());
  m_deviceMcsSet.push_back (WifiPhy::GetVhtMcs9 ());

  m_bssMembershipSelectorSet.push_back (VHT_PHY);
}

bool 
WifiPhy::DefineChannelNumber (uint16_t channelNumber, enum WifiPhyStandard standard, uint32_t frequency, uint32_t channelWidth)
{
  NS_LOG_FUNCTION (this << channelNumber << standard << frequency << channelWidth);
  ChannelNumberStandardPair p = std::make_pair (channelNumber, standard);
  ChannelToFrequencyWidthMap::const_iterator it;
  it = m_channelToFrequencyWidth.find (p);
  if (it != m_channelToFrequencyWidth.end ())
    {
      NS_LOG_DEBUG ("channel number/standard already defined; returning false");
      return false;
    }
  FrequencyWidthPair f = std::make_pair (frequency, channelWidth);
  m_channelToFrequencyWidth[p] = f;
  return true;
}

uint16_t 
WifiPhy::FindChannelNumberForFrequencyWidth (uint32_t frequency, uint32_t width) const
{
  NS_LOG_FUNCTION (this << frequency << width);
  bool found = false;
  FrequencyWidthPair f = std::make_pair (frequency, width);
  ChannelToFrequencyWidthMap::const_iterator it = m_channelToFrequencyWidth.begin ();
  while (it != m_channelToFrequencyWidth.end ())
    {
      if (it->second == f)
        {
           found = true;
           break;
        }
      ++it;
    }
  if (found)
    {
      NS_LOG_DEBUG ("Found, returning " << it->first.first);
      return (it->first.first);
    }
  else
    {
      NS_LOG_DEBUG ("Not found, returning 0");
      return 0;
    }
}

void
WifiPhy::ConfigureChannelForStandard (enum WifiPhyStandard standard)
{
  NS_LOG_FUNCTION (this << standard);
  // If the user has configured both Frequency and ChannelNumber, Frequency
  // takes precedence 
  if (GetFrequency () != 0)
    {
      // If Frequency is already set, then see whether a ChannelNumber can
      // be found that matches Frequency and ChannelWidth.  If so, configure 
      // the ChannelNumber to that channel number.  If not, set 
      // ChannelNumber to zero.
      NS_LOG_DEBUG ("Frequency set; checking whether a channel number corresponds");
      uint32_t channelNumberSearched = FindChannelNumberForFrequencyWidth (GetFrequency (), GetChannelWidth ());
      if (channelNumberSearched)
        {
          NS_LOG_DEBUG ("Channel number found; setting to " << channelNumberSearched);
          SetChannelNumber (channelNumberSearched);
        }
      else
        {
          NS_LOG_DEBUG ("Channel number not found; setting to zero");
          SetChannelNumber (0);
        }
    }
  else if (GetChannelNumber () != 0)
    {
      // If the channel number is known for this particular standard or for 
      // the unspecified standard, configure using the known values;
      // otherwise, this is a configuration error
      NS_LOG_DEBUG ("Configuring for channel number " << GetChannelNumber ());
      FrequencyWidthPair f = GetFrequencyWidthForChannelNumberStandard (GetChannelNumber (), standard);
      if (f.first == 0)
        {
          // the specific pair of number/standard is not known
          NS_LOG_DEBUG ("Falling back to check WIFI_PHY_STANDARD_UNSPECIFIED");
          f = GetFrequencyWidthForChannelNumberStandard (GetChannelNumber (), WIFI_PHY_STANDARD_UNSPECIFIED);
        }
      if (f.first == 0)
        {
          NS_FATAL_ERROR ("Error, ChannelNumber " << GetChannelNumber () << " is unknown for this standard");
        }
      else
        {
          NS_LOG_DEBUG ("Setting frequency to " << f.first << "; width to " << f.second);
          SetFrequency (f.first);
          SetChannelWidth (f.second);
        }
    }
}

void
WifiPhy::ConfigureStandard (enum WifiPhyStandard standard)
{
  NS_LOG_FUNCTION (this << standard);
  m_standard = standard;
  m_isConstructed = true;
  if (m_frequencyChannelNumberInitialized == false)
    {
      InitializeFrequencyChannelNumber ();
    }
  if (GetFrequency () == 0 && GetChannelNumber () == 0)
    {
      ConfigureDefaultsForStandard (standard);
    }
  else
    {
      // The user has configured either (or both) Frequency or ChannelNumber
      ConfigureChannelForStandard (standard);
    }
  switch (standard)
    {
    case WIFI_PHY_STANDARD_80211a:
      Configure80211a ();
      break;
    case WIFI_PHY_STANDARD_80211b:
      Configure80211b ();
      break;
    case WIFI_PHY_STANDARD_80211g:
      Configure80211g ();
      break;
    case WIFI_PHY_STANDARD_80211_10MHZ:
      Configure80211_10Mhz ();
      break;
    case WIFI_PHY_STANDARD_80211_5MHZ:
      Configure80211_5Mhz ();
      break;
    case WIFI_PHY_STANDARD_holland:
      ConfigureHolland ();
      break;
    case WIFI_PHY_STANDARD_80211n_2_4GHZ:
      Configure80211n ();
      break;
    case WIFI_PHY_STANDARD_80211n_5GHZ:
      Configure80211n ();
      break;
    case WIFI_PHY_STANDARD_80211ac:
      Configure80211ac ();
      break;
    default:
      NS_ASSERT (false);
      break;
    }
}

enum WifiPhyStandard
WifiPhy::GetStandard (void) const
{
  return m_standard;
}

void
WifiPhy::SetFrequency (uint32_t frequency)
{
  NS_LOG_FUNCTION (this << frequency);
  if (m_isConstructed == false)
    {
      NS_LOG_DEBUG ("Saving frequency configuration for initialization");
      m_initialFrequency = frequency;
      return;
    }
  if (GetFrequency () == frequency)
    {
      NS_LOG_DEBUG ("No frequency change requested");
      return;
    }
  if (frequency == 0)
    {
      DoFrequencySwitch (0);
      NS_LOG_DEBUG ("Setting frequency and channel number to zero");
      m_channelCenterFrequency = 0;
      m_channelNumber = 0;
      return;
    }
  // If the user has configured both Frequency and ChannelNumber, Frequency
  // takes precedence.  Lookup the channel number corresponding to the
  // requested frequency.
  uint16_t nch = FindChannelNumberForFrequencyWidth (frequency, GetChannelWidth ());
  if (nch != 0)
    {
      NS_LOG_DEBUG ("Setting frequency " << frequency << " corresponds to channel " << nch);
      if (DoFrequencySwitch (frequency))
        {
          NS_LOG_DEBUG ("Channel frequency switched to " << frequency << "; channel number to " << nch);
          m_channelCenterFrequency = frequency;
          m_channelNumber = nch;
        }
      else
        {
          NS_LOG_DEBUG ("Suppressing reassignment of frequency");
        }
    }
  else
    {
      NS_LOG_DEBUG ("Channel number is unknown for frequency " << frequency);
      if (DoFrequencySwitch (frequency))
        {
          NS_LOG_DEBUG ("Channel frequency switched to " << frequency << "; channel number to " << 0);
          m_channelCenterFrequency = frequency;
          m_channelNumber = 0;
        }
      else
        {
          NS_LOG_DEBUG ("Suppressing reassignment of frequency");
        }
    }
}

uint32_t
WifiPhy::GetFrequency (void) const
{
  return m_channelCenterFrequency;
}

void
WifiPhy::SetChannelWidth (uint32_t channelwidth)
{
  NS_ASSERT_MSG (channelwidth == 5 || channelwidth == 10 || channelwidth == 20 || channelwidth == 22 || channelwidth == 40 || channelwidth == 80 || channelwidth == 160, "wrong channel width value");
  m_channelWidth = channelwidth;
  AddSupportedChannelWidth (channelwidth);
}

uint32_t
WifiPhy::GetChannelWidth (void) const
{
  return m_channelWidth;
}

void
WifiPhy::SetNumberOfTransmitAntennas (uint32_t tx)
{
  m_numberOfTransmitters = tx;
  ConfigureHtDeviceMcsSet ();
}

void
WifiPhy::SetNumberOfReceiveAntennas (uint32_t rx)
{
  m_numberOfReceivers = rx;
}

uint32_t
WifiPhy::GetNumberOfTransmitAntennas (void) const
{
  return m_numberOfTransmitters;
}

uint32_t
WifiPhy::GetNumberOfReceiveAntennas (void) const
{
  return m_numberOfReceivers;
}

uint8_t 
WifiPhy::GetSupportedRxSpatialStreams (void) const
{
  return (static_cast<uint8_t> (GetNumberOfReceiveAntennas ()));
}

uint8_t 
WifiPhy::GetSupportedTxSpatialStreams (void) const
{
  return (static_cast<uint8_t> (GetNumberOfTransmitAntennas ()));
}

uint32_t
WifiPhy::GetNBssMembershipSelectors (void) const
{
  return m_bssMembershipSelectorSet.size ();
}

uint32_t
WifiPhy::GetBssMembershipSelector (uint32_t selector) const
{
  return m_bssMembershipSelectorSet[selector];
}

WifiModeList
WifiPhy::GetMembershipSelectorModes (uint32_t selector)
{
  uint32_t id = GetBssMembershipSelector (selector);
  WifiModeList supportedmodes;
  if (id == HT_PHY || id == VHT_PHY)
    {
      //mandatory MCS 0 to 7
      supportedmodes.push_back (WifiPhy::GetHtMcs0 ());
      supportedmodes.push_back (WifiPhy::GetHtMcs1 ());
      supportedmodes.push_back (WifiPhy::GetHtMcs2 ());
      supportedmodes.push_back (WifiPhy::GetHtMcs3 ());
      supportedmodes.push_back (WifiPhy::GetHtMcs4 ());
      supportedmodes.push_back (WifiPhy::GetHtMcs5 ());
      supportedmodes.push_back (WifiPhy::GetHtMcs6 ());
      supportedmodes.push_back (WifiPhy::GetHtMcs7 ());
    }
  if (id == VHT_PHY)
    {
      //mandatory MCS 0 to 9
      supportedmodes.push_back (WifiPhy::GetVhtMcs0 ());
      supportedmodes.push_back (WifiPhy::GetVhtMcs1 ());
      supportedmodes.push_back (WifiPhy::GetVhtMcs2 ());
      supportedmodes.push_back (WifiPhy::GetVhtMcs3 ());
      supportedmodes.push_back (WifiPhy::GetVhtMcs4 ());
      supportedmodes.push_back (WifiPhy::GetVhtMcs5 ());
      supportedmodes.push_back (WifiPhy::GetVhtMcs6 ());
      supportedmodes.push_back (WifiPhy::GetVhtMcs7 ());
      supportedmodes.push_back (WifiPhy::GetVhtMcs8 ());
      supportedmodes.push_back (WifiPhy::GetVhtMcs9 ());
    }
  return supportedmodes;
}

void
WifiPhy::AddSupportedChannelWidth (uint32_t width)
{
  NS_LOG_FUNCTION (this << width);
  for (std::vector<uint32_t>::size_type i = 0; i != m_supportedChannelWidthSet.size (); i++)
    {
      if (m_supportedChannelWidthSet[i] == width)
        {
          return;
        }
    }
  NS_LOG_FUNCTION ("Adding " << width << " to supported channel width set");
  m_supportedChannelWidthSet.push_back (width);
}

std::vector<uint32_t> 
WifiPhy::GetSupportedChannelWidthSet (void) const
{
  return m_supportedChannelWidthSet;
}

WifiPhy::FrequencyWidthPair
WifiPhy::GetFrequencyWidthForChannelNumberStandard (uint16_t channelNumber, enum WifiPhyStandard standard) const
{
  ChannelNumberStandardPair p = std::make_pair (channelNumber, standard);
  FrequencyWidthPair f = m_channelToFrequencyWidth[p];
  return f;
}

void
WifiPhy::SetChannelNumber (uint16_t nch)
{
  NS_LOG_FUNCTION (this << nch);
  if (m_isConstructed == false)
    {
      NS_LOG_DEBUG ("Saving channel number configuration for initialization");
      m_initialChannelNumber = nch;
      return;
    }
  if (GetChannelNumber () == nch)
    {
      NS_LOG_DEBUG ("No channel change requested");
      return;
    }
  if (nch == 0)
    {
      // This case corresponds to when there is not a known channel
      // number for the requested frequency.  There is no need to call
      // DoChannelSwitch () because DoFrequencySwitch () should have been
      // called by the client
      NS_LOG_DEBUG ("Setting channel number to zero");
      m_channelNumber = 0;
      return;
    }

  // First make sure that the channel number is defined for the standard
  // in use
  FrequencyWidthPair f = GetFrequencyWidthForChannelNumberStandard (nch, GetStandard ());
  if (f.first == 0)
    {
      f = GetFrequencyWidthForChannelNumberStandard (nch, WIFI_PHY_STANDARD_UNSPECIFIED);
    }
  if (f.first != 0)
    {
      if (DoChannelSwitch (nch))
        {
          NS_LOG_DEBUG ("Setting frequency to " << f.first << "; width to " << f.second);
          m_channelCenterFrequency = f.first;
          SetChannelWidth (f.second);
          m_channelNumber = nch;
        }
      else
        {
          // Subclass may have suppressed (e.g. waiting for state change)
          NS_LOG_DEBUG ("Channel switch suppressed");
        }
    }
  else
    {
      NS_FATAL_ERROR ("Frequency not found for channel number " << nch);
    }
}

uint16_t
WifiPhy::GetChannelNumber (void) const
{
  return m_channelNumber;
}

bool
WifiPhy::DoChannelSwitch (uint16_t nch)
{
  return true;
}

bool
WifiPhy::DoFrequencySwitch (uint32_t frequency)
{
  return true;
}

WifiMode
WifiPhy::GetHtPlcpHeaderMode (WifiMode payloadMode)
=======
>>>>>>> origin
{
  NS_LOG_FUNCTION (this);
  m_endTxEvent.Cancel ();
  m_endPhyRxEvent.Cancel ();
  for (auto & phyEntity : m_phyEntities)
    {
      phyEntity.second->CancelAllEvents ();
    }
  m_device = 0;
  m_mobility = 0;
  m_frameCaptureModel = 0;
  m_preambleDetectionModel = 0;
  m_wifiRadioEnergyModel = 0;
  m_postReceptionErrorModel = 0;
  m_supportedChannelWidthSet.clear ();
  m_random = 0;
  m_state = 0;
  m_currentEvent = 0;
  for (auto & preambleEvent : m_currentPreambleEvents)
    {
      preambleEvent.second = 0;
    }
  m_currentPreambleEvents.clear ();

  for (auto & phyEntity : m_phyEntities)
    {
      phyEntity.second = 0;
    }
  m_phyEntities.clear ();
}

Ptr<WifiPhyStateHelper>
WifiPhy::GetState (void) const
{
  return m_state;
}

void
WifiPhy::SetReceiveOkCallback (RxOkCallback callback)
{
  m_state->SetReceiveOkCallback (callback);
}

void
WifiPhy::SetReceiveErrorCallback (RxErrorCallback callback)
{
  m_state->SetReceiveErrorCallback (callback);
}

void
WifiPhy::RegisterListener (WifiPhyListener *listener)
{
  m_state->RegisterListener (listener);
}

void
WifiPhy::UnregisterListener (WifiPhyListener *listener)
{
  m_state->UnregisterListener (listener);
}

void
WifiPhy::SetCapabilitiesChangedCallback (Callback<void> callback)
{
  m_capabilitiesChangedCallback = callback;
}

void
WifiPhy::SetRxSensitivity (double threshold)
{
  NS_LOG_FUNCTION (this << threshold);
  m_rxSensitivityW = DbmToW (threshold);
}

double
WifiPhy::GetRxSensitivity (void) const
{
  return WToDbm (m_rxSensitivityW);
}

void
WifiPhy::SetCcaEdThreshold (double threshold)
{
  NS_LOG_FUNCTION (this << threshold);
  m_ccaEdThresholdW = DbmToW (threshold);
}

double
WifiPhy::GetCcaEdThreshold (void) const
{
  return WToDbm (m_ccaEdThresholdW);
}

void
WifiPhy::SetRxNoiseFigure (double noiseFigureDb)
{
  NS_LOG_FUNCTION (this << noiseFigureDb);
  m_interference.SetNoiseFigure (DbToRatio (noiseFigureDb));
  m_interference.SetNumberOfReceiveAntennas (GetNumberOfAntennas ());
}

void
WifiPhy::SetTxPowerStart (double start)
{
  NS_LOG_FUNCTION (this << start);
  m_txPowerBaseDbm = start;
}

double
WifiPhy::GetTxPowerStart (void) const
{
  return m_txPowerBaseDbm;
}

void
WifiPhy::SetTxPowerEnd (double end)
{
  NS_LOG_FUNCTION (this << end);
  m_txPowerEndDbm = end;
}

double
WifiPhy::GetTxPowerEnd (void) const
{
  return m_txPowerEndDbm;
}

void
WifiPhy::SetNTxPower (uint8_t n)
{
  NS_LOG_FUNCTION (this << +n);
  m_nTxPower = n;
}

uint8_t
WifiPhy::GetNTxPower (void) const
{
  return m_nTxPower;
}

void
WifiPhy::SetTxGain (double gain)
{
  NS_LOG_FUNCTION (this << gain);
  m_txGainDb = gain;
}

double
WifiPhy::GetTxGain (void) const
{
  return m_txGainDb;
}

void
WifiPhy::SetRxGain (double gain)
{
  NS_LOG_FUNCTION (this << gain);
  m_rxGainDb = gain;
}

double
WifiPhy::GetRxGain (void) const
{
  return m_rxGainDb;
}

void
WifiPhy::SetShortPhyPreambleSupported (bool enable)
{
  NS_LOG_FUNCTION (this << enable);
  m_shortPreamble = enable;
}

bool
WifiPhy::GetShortPhyPreambleSupported (void) const
{
  return m_shortPreamble;
}

void
WifiPhy::SetDevice (const Ptr<NetDevice> device)
{
  m_device = device;
}

Ptr<NetDevice>
WifiPhy::GetDevice (void) const
{
  return m_device;
}

void
WifiPhy::SetMobility (const Ptr<MobilityModel> mobility)
{
  m_mobility = mobility;
}

Ptr<MobilityModel>
WifiPhy::GetMobility (void) const
{
  if (m_mobility != 0)
    {
      return m_mobility;
    }
  else
    {
      return m_device->GetNode ()->GetObject<MobilityModel> ();
    }
}

void
WifiPhy::SetErrorRateModel (const Ptr<ErrorRateModel> rate)
{
  m_interference.SetErrorRateModel (rate);
  m_interference.SetNumberOfReceiveAntennas (GetNumberOfAntennas ());
}

void
WifiPhy::SetPostReceptionErrorModel (const Ptr<ErrorModel> em)
{
  NS_LOG_FUNCTION (this << em);
  m_postReceptionErrorModel = em;
}

void
WifiPhy::SetFrameCaptureModel (const Ptr<FrameCaptureModel> model)
{
  m_frameCaptureModel = model;
}

void
WifiPhy::SetPreambleDetectionModel (const Ptr<PreambleDetectionModel> model)
{
  m_preambleDetectionModel = model;
}

void
WifiPhy::SetWifiRadioEnergyModel (const Ptr<WifiRadioEnergyModel> wifiRadioEnergyModel)
{
  m_wifiRadioEnergyModel = wifiRadioEnergyModel;
}

double
WifiPhy::GetPowerDbm (uint8_t power) const
{
  NS_ASSERT (m_txPowerBaseDbm <= m_txPowerEndDbm);
  NS_ASSERT (m_nTxPower > 0);
  double dbm;
  if (m_nTxPower > 1)
    {
      dbm = m_txPowerBaseDbm + power * (m_txPowerEndDbm - m_txPowerBaseDbm) / (m_nTxPower - 1);
    }
  else
    {
      NS_ASSERT_MSG (m_txPowerBaseDbm == m_txPowerEndDbm, "cannot have TxPowerEnd != TxPowerStart with TxPowerLevels == 1");
      dbm = m_txPowerBaseDbm;
    }
  return dbm;
}

Time
WifiPhy::GetChannelSwitchDelay (void) const
{
  return m_channelSwitchDelay;
}

double
WifiPhy::CalculateSnr (const WifiTxVector& txVector, double ber) const
{
  return m_interference.GetErrorRateModel ()->CalculateSnr (txVector, ber);
}

const Ptr<const PhyEntity>
WifiPhy::GetStaticPhyEntity (WifiModulationClass modulation)
{
  const auto it = m_staticPhyEntities.find (modulation);
  NS_ABORT_MSG_IF (it == m_staticPhyEntities.end (), "Unimplemented Wi-Fi modulation class");
  return it->second;
}

Ptr<PhyEntity>
WifiPhy::GetPhyEntity (WifiModulationClass modulation) const
{
  const auto it = m_phyEntities.find (modulation);
  NS_ABORT_MSG_IF (it == m_phyEntities.end (), "Unsupported Wi-Fi modulation class");
  return it->second;
}

void
WifiPhy::AddStaticPhyEntity (WifiModulationClass modulation, Ptr<PhyEntity> phyEntity)
{
  NS_LOG_FUNCTION (modulation);
  NS_ASSERT_MSG (m_staticPhyEntities.find (modulation) == m_staticPhyEntities.end (), "The PHY entity has already been added. The setting should only be done once per modulation class");
  m_staticPhyEntities[modulation] = phyEntity;
}

void
WifiPhy::AddPhyEntity (WifiModulationClass modulation, Ptr<PhyEntity> phyEntity)
{
  NS_LOG_FUNCTION (this << modulation);
  NS_ABORT_MSG_IF (m_staticPhyEntities.find (modulation) == m_staticPhyEntities.end (), "Cannot add an unimplemented PHY to supported list. Update the former first.");
  NS_ASSERT_MSG (m_phyEntities.find (modulation) == m_phyEntities.end (), "The PHY entity has already been added. The setting should only be done once per modulation class");
  phyEntity->SetOwner (this);
  m_phyEntities[modulation] = phyEntity;
}

void
WifiPhy::SetSifs (Time sifs)
{
  m_sifs = sifs;
}

Time
WifiPhy::GetSifs (void) const
{
  return m_sifs;
}

void
WifiPhy::SetSlot (Time slot)
{
  m_slot = slot;
}

Time
WifiPhy::GetSlot (void) const
{
  return m_slot;
}

void
WifiPhy::SetPifs (Time pifs)
{
  m_pifs = pifs;
}

Time
WifiPhy::GetPifs (void) const
{
  return m_pifs;
}

Time
WifiPhy::GetAckTxTime (void) const
{
  return m_ackTxTime;
}

Time
WifiPhy::GetBlockAckTxTime (void) const
{
  return m_blockAckTxTime;
}

void
WifiPhy::Configure80211a (void)
{
  NS_LOG_FUNCTION (this);
  AddPhyEntity (WIFI_MOD_CLASS_OFDM, Create<OfdmPhy> ());

  // See Table 17-21 "OFDM PHY characteristics" of 802.11-2016
  SetSifs (MicroSeconds (16));
  SetSlot (MicroSeconds (9));
  SetPifs (GetSifs () + GetSlot ());
  // See Table 10-5 "Determination of the EstimatedAckTxTime based on properties
  // of the PPDU causing the EIFS" of 802.11-2016
  m_ackTxTime = MicroSeconds (44);
}

void
WifiPhy::Configure80211b (void)
{
  NS_LOG_FUNCTION (this);
  Ptr<DsssPhy> phyEntity = Create<DsssPhy> ();
  AddPhyEntity (WIFI_MOD_CLASS_HR_DSSS, phyEntity);
  AddPhyEntity (WIFI_MOD_CLASS_DSSS, phyEntity); //when plain DSSS modes are used

  // See Table 16-4 "HR/DSSS PHY characteristics" of 802.11-2016
  SetSifs (MicroSeconds (10));
  SetSlot (MicroSeconds (20));
  SetPifs (GetSifs () + GetSlot ());
  // See Table 10-5 "Determination of the EstimatedAckTxTime based on properties
  // of the PPDU causing the EIFS" of 802.11-2016
  m_ackTxTime = MicroSeconds (304);
}

void
WifiPhy::Configure80211g (void)
{
  NS_LOG_FUNCTION (this);
  // See Table 18-5 "ERP characteristics" of 802.11-2016
  // Slot time defaults to the "long slot time" of 20 us in the standard
  // according to mixed 802.11b/g deployments.  Short slot time is enabled
  // if the user sets the ShortSlotTimeSupported flag to true and when the BSS
  // consists of only ERP STAs capable of supporting this option.
  Configure80211b ();
  AddPhyEntity (WIFI_MOD_CLASS_ERP_OFDM, Create<ErpOfdmPhy> ());
}

void
WifiPhy::Configure80211p (void)
{
  NS_LOG_FUNCTION (this);
  if (GetChannelWidth () == 10)
    {
      AddPhyEntity (WIFI_MOD_CLASS_OFDM, Create<OfdmPhy> (OFDM_PHY_10_MHZ));

      // See Table 17-21 "OFDM PHY characteristics" of 802.11-2016
      SetSifs (MicroSeconds (32));
      SetSlot (MicroSeconds (13));
      SetPifs (GetSifs () + GetSlot ());
      m_ackTxTime = MicroSeconds (88);
    }
  else if (GetChannelWidth () == 5)
    {
      AddPhyEntity (WIFI_MOD_CLASS_OFDM, Create<OfdmPhy> (OFDM_PHY_5_MHZ));

      // See Table 17-21 "OFDM PHY characteristics" of 802.11-2016
      SetSifs (MicroSeconds (64));
      SetSlot (MicroSeconds (21));
      SetPifs (GetSifs () + GetSlot ());
      m_ackTxTime = MicroSeconds (176);
    }
  else
    {
      NS_FATAL_ERROR ("802.11p configured with a wrong channel width!");
    }
}

void
WifiPhy::Configure80211n (void)
{
  NS_LOG_FUNCTION (this);
  if (m_band == WIFI_PHY_BAND_2_4GHZ)
    {
      Configure80211g ();
    }
  else
    {
      Configure80211a ();
    }
  AddPhyEntity (WIFI_MOD_CLASS_HT, Create<HtPhy> (m_txSpatialStreams));

  // See Table 10-5 "Determination of the EstimatedAckTxTime based on properties
  // of the PPDU causing the EIFS" of 802.11-2016
  m_blockAckTxTime = MicroSeconds (68);
}

void
WifiPhy::Configure80211ac (void)
{
  NS_LOG_FUNCTION (this);
  Configure80211n ();
  AddPhyEntity (WIFI_MOD_CLASS_VHT, Create<VhtPhy> ());
}

void
WifiPhy::Configure80211ax (void)
{
  NS_LOG_FUNCTION (this);
  if (m_band == WIFI_PHY_BAND_2_4GHZ)
    {
      Configure80211n ();
    }
  else
    {
      Configure80211ac ();
    }
  AddPhyEntity (WIFI_MOD_CLASS_HE, Create<HePhy> ());
}

void
WifiPhy::ConfigureStandardAndBand (WifiPhyStandard standard, WifiPhyBand band)
{
  NS_LOG_FUNCTION (this << standard << band);
  m_standard = standard;
  m_band = band;

  if (m_initialFrequency == 0 && m_initialChannelNumber == 0)
    {
      // set a default channel if the user did not specify anything
      if (m_initialChannelWidth == 0)
        {
<<<<<<< HEAD
        case 5:
          return WifiPhy::GetOfdmRate1_5MbpsBW5MHz ();
        case 10:
          return WifiPhy::GetOfdmRate3MbpsBW10MHz ();
        case 20:
        case 40:
        case 80:
        case 160:
        default:
          //(Section 18.3.2 "PLCP frame format"; IEEE Std 802.11-2012)
          //actually this is only the first part of the PlcpHeader,
          //because the last 16 bits of the PlcpHeader are using the
          //same mode of the payload
          return WifiPhy::GetOfdmRate6Mbps ();
        }
    case WIFI_MOD_CLASS_ERP_OFDM:
      return WifiPhy::GetErpOfdmRate6Mbps ();
    case WIFI_MOD_CLASS_DSSS:
    case WIFI_MOD_CLASS_HR_DSSS:
      if (preamble == WIFI_PREAMBLE_LONG || payloadMode == WifiPhy::GetDsssRate1Mbps ())
        {
          //(Section 16.2.3 "PLCP field definitions" and Section 17.2.2.2 "Long PPDU format"; IEEE Std 802.11-2012)
          return WifiPhy::GetDsssRate1Mbps ();
        }
      else //WIFI_PREAMBLE_SHORT
        {
          //(Section 17.2.2.3 "Short PPDU format"; IEEE Std 802.11-2012)
          return WifiPhy::GetDsssRate2Mbps ();
=======
          // set a default channel width
          m_initialChannelWidth = GetDefaultChannelWidth (m_standard, m_band);
>>>>>>> origin
        }

      m_operatingChannel.SetDefault (m_initialChannelWidth, m_standard, m_band);
    }
  else
    {
      m_operatingChannel.Set (m_initialChannelNumber, m_initialFrequency, m_initialChannelWidth,
                              m_standard, m_band);
    }
  m_operatingChannel.SetPrimary20Index (m_initialPrimary20Index);

  switch (standard)
    {
    case WIFI_PHY_STANDARD_80211a:
      Configure80211a ();
      break;
    case WIFI_PHY_STANDARD_80211b:
      Configure80211b ();
      break;
    case WIFI_PHY_STANDARD_80211g:
      Configure80211g ();
      break;
    case WIFI_PHY_STANDARD_80211p:
      Configure80211p ();
      break;
    case WIFI_PHY_STANDARD_80211n:
      Configure80211n ();
      break;
    case WIFI_PHY_STANDARD_80211ac:
      Configure80211ac ();
      break;
    case WIFI_PHY_STANDARD_80211ax:
      Configure80211ax ();
      break;
    case WIFI_PHY_STANDARD_UNSPECIFIED:
    default:
      NS_ASSERT_MSG (false, "Unsupported standard");
      break;
    }
}

WifiPhyBand
WifiPhy::GetPhyBand (void) const
{
  return m_band;
}


WifiPhyStandard
WifiPhy::GetPhyStandard (void) const
{
  return m_standard;
}

const WifiPhyOperatingChannel&
WifiPhy::GetOperatingChannel (void) const
{
  return m_operatingChannel;
}

void
WifiPhy::SetFrequency (uint16_t frequency)
{
  NS_LOG_FUNCTION (this << frequency);

  if (!m_operatingChannel.IsSet ())
    {
      // ConfigureStandardAndBand has not been called yet, so store the frequency
      // into m_initialFrequency
      NS_LOG_DEBUG ("Saving frequency configuration for initialization");
      m_initialFrequency = frequency;
      return;
    }

  if (GetFrequency () == frequency)
    {
      NS_LOG_DEBUG ("No frequency change requested");
      return;
    }

  // if the frequency does not uniquely identify an operating channel,
  // the simulation aborts
  SetOperatingChannel (0, frequency, 0);
}

uint16_t
WifiPhy::GetFrequency (void) const
{
  return m_operatingChannel.GetFrequency ();
}

void
WifiPhy::SetChannelNumber (uint8_t nch)
{
  NS_LOG_FUNCTION (this << +nch);

  if (!m_operatingChannel.IsSet ())
    {
      // ConfigureStandardAndBand has not been called yet, so store the channel
      // into m_initialChannelNumber
      NS_LOG_DEBUG ("Saving channel number configuration for initialization");
      m_initialChannelNumber = nch;
      return;
    }

  if (GetChannelNumber () == nch)
    {
      NS_LOG_DEBUG ("No channel change requested");
      return;
    }

  // if the channel number does not uniquely identify an operating channel,
  // the simulation aborts
  SetOperatingChannel (nch, 0, 0);
}

uint8_t
WifiPhy::GetChannelNumber (void) const
{
  return m_operatingChannel.GetNumber ();
}

void
WifiPhy::SetChannelWidth (uint16_t channelWidth)
{
  NS_LOG_FUNCTION (this << channelWidth);

  if (channelWidth != 0)
    {
      AddSupportedChannelWidth (channelWidth);
    }

  if (!m_operatingChannel.IsSet ())
    {
      // ConfigureStandardAndBand has not been called yet, so store the channel width
      // into m_initialChannelWidth
      NS_LOG_DEBUG ("Saving channel width configuration for initialization");
      m_initialChannelWidth = channelWidth;
      return;
    }

  if (GetChannelWidth () == channelWidth)
    {
      NS_LOG_DEBUG ("No channel width change requested");
      return;
    }

  NS_ABORT_MSG ("The channel width does not uniquely identify an operating channel.");
}

uint16_t
WifiPhy::GetChannelWidth (void) const
{
  return m_operatingChannel.GetWidth ();
}

void
WifiPhy::SetPrimary20Index (uint8_t index)
{
  NS_LOG_FUNCTION (this << +index);

  if (!m_operatingChannel.IsSet ())
    {
      // ConfigureStandardAndBand has not been called yet, so store the primary20
      // index into m_initialPrimary20Index
      NS_LOG_DEBUG ("Saving primary20 index configuration for initialization");
      m_initialPrimary20Index = index;
      return;
    }

  m_operatingChannel.SetPrimary20Index (index);
}

void
WifiPhy::SetOperatingChannel (uint8_t number, uint16_t frequency, uint16_t width)
{
  Time delay = Seconds (0);

  if (IsInitialized ())
    {
      delay = DoChannelSwitch ();
    }

  if (delay.IsStrictlyNegative ())
    {
      // switching channel is not possible now
      return;
    }
  if (delay.IsStrictlyPositive ())
    {
      // switching channel has been postponed
      Simulator::Schedule (delay, &WifiPhy::SetOperatingChannel, this, number, frequency, width);
      return;
    }

  // channel can be switched now.
  uint16_t prevChannelWidth = 0;
  if (m_operatingChannel.IsSet ())
    {
      prevChannelWidth = GetChannelWidth ();
    }

  m_operatingChannel.Set (number, frequency, width, m_standard, m_band);

  if (GetChannelWidth () != prevChannelWidth)
    {
      AddSupportedChannelWidth (GetChannelWidth ());

      // If channel width changed after initialization, invoke the capabilities changed callback
      if (IsInitialized () && !m_capabilitiesChangedCallback.IsNull ())
        {
          m_capabilitiesChangedCallback ();
        }
    }
}

Time
WifiPhy::DoChannelSwitch (void)
{
  m_powerRestricted = false;
  m_channelAccessRequested = false;
  m_currentEvent = 0;
  m_currentPreambleEvents.clear ();
  if (!IsInitialized ())
    {
      //this is not channel switch, this is initialization
      NS_LOG_DEBUG ("Before initialization, nothing to do");
      return Seconds (0);
    }

  Time delay = Seconds (0);

  NS_ASSERT (!IsStateSwitching ());
  switch (m_state->GetState ())
    {
    case WifiPhyState::RX:
      NS_LOG_DEBUG ("drop packet because of channel switching while reception");
      m_endPhyRxEvent.Cancel ();
      for (auto & phyEntity : m_phyEntities)
        {
          phyEntity.second->CancelAllEvents ();
        }
      break;
    case WifiPhyState::TX:
      NS_LOG_DEBUG ("channel switching postponed until end of current transmission");
      delay = GetDelayUntilIdle ();
      break;
    case WifiPhyState::CCA_BUSY:
    case WifiPhyState::IDLE:
      for (auto & phyEntity : m_phyEntities)
        {
          phyEntity.second->CancelAllEvents ();
        }
      break;
    case WifiPhyState::SLEEP:
      NS_LOG_DEBUG ("channel switching ignored in sleep mode");
      delay = Seconds (-1);  // negative value to indicate switching not possible
      break;
    default:
      NS_ASSERT (false);
      break;
    }

  if (delay.IsZero ())
    {
      // channel switch can be done now
      NS_LOG_DEBUG ("switching channel");
      m_state->SwitchToChannelSwitching (GetChannelSwitchDelay ());
      m_interference.EraseEvents ();
      /*
      * Needed here to be able to correctly sensed the medium for the first
      * time after the switching. The actual switching is not performed until
      * after m_channelSwitchDelay. Packets received during the switching
      * state are added to the event list and are employed later to figure
      * out the state of the medium after the switching.
      */
    }

  return delay;
}

void
WifiPhy::SetNumberOfAntennas (uint8_t antennas)
{
  NS_ASSERT_MSG (antennas > 0 && antennas <= 4, "unsupported number of antennas");
  m_numberOfAntennas = antennas;
  m_interference.SetNumberOfReceiveAntennas (antennas);
}

uint8_t
WifiPhy::GetNumberOfAntennas (void) const
{
  return m_numberOfAntennas;
}

void
WifiPhy::SetMaxSupportedTxSpatialStreams (uint8_t streams)
{
  NS_ASSERT (streams <= GetNumberOfAntennas ());
  bool changed = (m_txSpatialStreams != streams);
  m_txSpatialStreams = streams;
  if (changed)
    {
      auto phyEntity = m_phyEntities.find (WIFI_MOD_CLASS_HT);
      if (phyEntity != m_phyEntities.end ())
        {
          Ptr<HtPhy> htPhy = DynamicCast<HtPhy> (phyEntity->second);
          if (htPhy)
            {
              htPhy->SetMaxSupportedNss (m_txSpatialStreams); //this is essential to have the right MCSs configured
            }

          if (!m_capabilitiesChangedCallback.IsNull ())
            {
              m_capabilitiesChangedCallback ();
            }
        }
    }
}

uint8_t
WifiPhy::GetMaxSupportedTxSpatialStreams (void) const
{
  return m_txSpatialStreams;
}

void
WifiPhy::SetMaxSupportedRxSpatialStreams (uint8_t streams)
{
  NS_ASSERT (streams <= GetNumberOfAntennas ());
  bool changed = (m_rxSpatialStreams != streams);
  m_rxSpatialStreams = streams;
  if (changed && !m_capabilitiesChangedCallback.IsNull ())
    {
      m_capabilitiesChangedCallback ();
    }
}

uint8_t
WifiPhy::GetMaxSupportedRxSpatialStreams (void) const
{
  return m_rxSpatialStreams;
}

std::list<uint8_t>
WifiPhy::GetBssMembershipSelectorList (void) const
{
  std::list<uint8_t> list;
  for (const auto & phyEntity : m_phyEntities)
    {
      Ptr<HtPhy> htPhy = DynamicCast<HtPhy> (phyEntity.second);
      if (htPhy)
        {
          list.emplace_back (htPhy->GetBssMembershipSelector ());
        }
    }
  return list;
}

void
WifiPhy::AddSupportedChannelWidth (uint16_t width)
{
  NS_LOG_FUNCTION (this << width);
  for (std::vector<uint32_t>::size_type i = 0; i != m_supportedChannelWidthSet.size (); i++)
    {
      if (m_supportedChannelWidthSet[i] == width)
        {
          return;
        }
    }
  NS_LOG_FUNCTION ("Adding " << width << " to supported channel width set");
  m_supportedChannelWidthSet.push_back (width);
}

std::vector<uint16_t>
WifiPhy::GetSupportedChannelWidthSet (void) const
{
  return m_supportedChannelWidthSet;
}

void
WifiPhy::SetSleepMode (void)
{
  NS_LOG_FUNCTION (this);
  m_powerRestricted = false;
  m_channelAccessRequested = false;
  switch (m_state->GetState ())
    {
    case WifiPhyState::TX:
      NS_LOG_DEBUG ("setting sleep mode postponed until end of current transmission");
      Simulator::Schedule (GetDelayUntilIdle (), &WifiPhy::SetSleepMode, this);
      break;
    case WifiPhyState::RX:
      NS_LOG_DEBUG ("setting sleep mode postponed until end of current reception");
      Simulator::Schedule (GetDelayUntilIdle (), &WifiPhy::SetSleepMode, this);
      break;
    case WifiPhyState::SWITCHING:
      NS_LOG_DEBUG ("setting sleep mode postponed until end of channel switching");
      Simulator::Schedule (GetDelayUntilIdle (), &WifiPhy::SetSleepMode, this);
      break;
    case WifiPhyState::CCA_BUSY:
    case WifiPhyState::IDLE:
      NS_LOG_DEBUG ("setting sleep mode");
      m_state->SwitchToSleep ();
      break;
    case WifiPhyState::SLEEP:
      NS_LOG_DEBUG ("already in sleep mode");
      break;
    default:
      NS_ASSERT (false);
      break;
    }
}

void
WifiPhy::SetOffMode (void)
{
  NS_LOG_FUNCTION (this);
  m_powerRestricted = false;
  m_channelAccessRequested = false;
  m_endPhyRxEvent.Cancel ();
  m_endTxEvent.Cancel ();
  for (auto & phyEntity : m_phyEntities)
    {
      phyEntity.second->CancelAllEvents ();
    }
  m_state->SwitchToOff ();
}

void
WifiPhy::ResumeFromSleep (void)
{
  NS_LOG_FUNCTION (this);
  m_currentPreambleEvents.clear ();
  switch (m_state->GetState ())
    {
    case WifiPhyState::TX:
    case WifiPhyState::RX:
    case WifiPhyState::IDLE:
    case WifiPhyState::CCA_BUSY:
    case WifiPhyState::SWITCHING:
      {
<<<<<<< HEAD
        switch (txVector.GetChannelWidth ())
          {
          case 20:
          default:
            //(Section 18.3.3 "PLCP preamble (SYNC))" and Figure 18-4 "OFDM training structure"; IEEE Std 802.11-2012)
            //also (Section 18.3.2.4 "Timing related parameters" Table 18-5 "Timing-related parameters"; IEEE Std 802.11-2012)
            //We return the duration of the SIGNAL field only, since the
            //SERVICE field (which strictly speaking belongs to the PLCP
            //header, see Section 18.3.2 and Figure 18-1) is sent using the
            //payload mode.
            return MicroSeconds (4);
          case 10:
            //(Section 18.3.2.4 "Timing related parameters" Table 18-5 "Timing-related parameters"; IEEE Std 802.11-2012)
            return MicroSeconds (8);
          case 5:
            //(Section 18.3.2.4 "Timing related parameters" Table 18-5 "Timing-related parameters"; IEEE Std 802.11-2012)
            return MicroSeconds (16);
          }
=======
        NS_LOG_DEBUG ("not in sleep mode, there is nothing to resume");
        break;
>>>>>>> origin
      }
    case WifiPhyState::SLEEP:
      {
        NS_LOG_DEBUG ("resuming from sleep mode");
        Time delayUntilCcaEnd = m_interference.GetEnergyDuration (m_ccaEdThresholdW, GetPrimaryBand (GetMeasurementChannelWidth (nullptr)));
        m_state->SwitchFromSleep (delayUntilCcaEnd);
        break;
      }
<<<<<<< HEAD
    case WIFI_MOD_CLASS_VHT:
    case WIFI_MOD_CLASS_ERP_OFDM:
      return MicroSeconds (4);
    case WIFI_MOD_CLASS_DSSS:
    case WIFI_MOD_CLASS_HR_DSSS:
      if ((preamble == WIFI_PREAMBLE_SHORT) && (txVector.GetMode ().GetDataRate (22, 0, 1) > 1000000))
        {
          //(Section 17.2.2.3 "Short PPDU format" and Figure 17-2 "Short PPDU format"; IEEE Std 802.11-2012)
          return MicroSeconds (24);
        }
      else //WIFI_PREAMBLE_LONG
        {
          //(Section 17.2.2.2 "Long PPDU format" and Figure 17-1 "Short PPDU format"; IEEE Std 802.11-2012)
          return MicroSeconds (48);
        }
=======
>>>>>>> origin
    default:
      {
        NS_ASSERT (false);
        break;
      }
    }
}

void
WifiPhy::ResumeFromOff (void)
{
  NS_LOG_FUNCTION (this);
  switch (m_state->GetState ())
    {
    case WifiPhyState::TX:
    case WifiPhyState::RX:
    case WifiPhyState::IDLE:
    case WifiPhyState::CCA_BUSY:
    case WifiPhyState::SWITCHING:
    case WifiPhyState::SLEEP:
      {
        NS_LOG_DEBUG ("not in off mode, there is nothing to resume");
        break;
      }
    case WifiPhyState::OFF:
      {
        NS_LOG_DEBUG ("resuming from off mode");
        Time delayUntilCcaEnd = m_interference.GetEnergyDuration (m_ccaEdThresholdW, GetPrimaryBand (GetMeasurementChannelWidth (nullptr)));
        m_state->SwitchFromOff (delayUntilCcaEnd);
        break;
      }
    default:
      {
        NS_ASSERT (false);
        break;
      }
    }
}

Time
WifiPhy::GetPreambleDetectionDuration (void)
{
<<<<<<< HEAD
  if (preamble == WIFI_PREAMBLE_NONE)
    {
      return MicroSeconds (0);
    }
  switch (txVector.GetMode ().GetModulationClass ())
    {
    case WIFI_MOD_CLASS_OFDM:
      {
        switch (txVector.GetChannelWidth ())
          {
          case 20:
          default:
            //(Section 18.3.3 "PLCP preamble (SYNC))" Figure 18-4 "OFDM training structure"
            //also Section 18.3.2.3 "Modulation-dependent parameters" Table 18-4 "Modulation-dependent parameters"; IEEE Std 802.11-2012)
            return MicroSeconds (16);
          case 10:
            //(Section 18.3.3 "PLCP preamble (SYNC))" Figure 18-4 "OFDM training structure"
            //also Section 18.3.2.3 "Modulation-dependent parameters" Table 18-4 "Modulation-dependent parameters"; IEEE Std 802.11-2012)
            return MicroSeconds (32);
          case 5:
            //(Section 18.3.3 "PLCP preamble (SYNC))" Figure 18-4 "OFDM training structure"
            //also Section 18.3.2.3 "Modulation-dependent parameters" Table 18-4 "Modulation-dependent parameters"; IEEE Std 802.11-2012)
            return MicroSeconds (64);
          }
      }
    case WIFI_MOD_CLASS_VHT:
    case WIFI_MOD_CLASS_HT:
      //IEEE 802.11n Figure 20.1 the training symbols before L_SIG or HT_SIG
      return MicroSeconds (16);
    case WIFI_MOD_CLASS_ERP_OFDM:
      return MicroSeconds (16);
    case WIFI_MOD_CLASS_DSSS:
    case WIFI_MOD_CLASS_HR_DSSS:
      if ((preamble == WIFI_PREAMBLE_SHORT) && (txVector.GetMode ().GetDataRate (22, 0, 1) > 1000000))
        {
          //(Section 17.2.2.3 "Short PPDU format)" Figure 17-2 "Short PPDU format"; IEEE Std 802.11-2012)
          return MicroSeconds (72);
        }
      else //WIFI_PREAMBLE_LONG
        {
          //(Section 17.2.2.2 "Long PPDU format)" Figure 17-1 "Long PPDU format"; IEEE Std 802.11-2012)
          return MicroSeconds (144);
        }
    default:
      NS_FATAL_ERROR ("unsupported modulation class");
      return MicroSeconds (0);
    }
}

Time
WifiPhy::GetPayloadDuration (uint32_t size, WifiTxVector txVector, WifiPreamble preamble, double frequency)
{
  return GetPayloadDuration (size, txVector, preamble, frequency, NORMAL_MPDU, 0);
}

Time
WifiPhy::GetPayloadDuration (uint32_t size, WifiTxVector txVector, WifiPreamble preamble, double frequency, enum mpduType mpdutype, uint8_t incFlag)
{
  WifiMode payloadMode = txVector.GetMode ();
  NS_LOG_FUNCTION (size << payloadMode);

  switch (payloadMode.GetModulationClass ())
    {
    case WIFI_MOD_CLASS_OFDM:
    case WIFI_MOD_CLASS_ERP_OFDM:
      {
        //(Section 18.3.2.4 "Timing related parameters" Table 18-5 "Timing-related parameters"; IEEE Std 802.11-2012
        //corresponds to T_{SYM} in the table)
        Time symbolDuration;

        switch (txVector.GetChannelWidth ())
          {
          case 20:
          default:
            symbolDuration = MicroSeconds (4);
            break;
          case 10:
            symbolDuration = MicroSeconds (8);
            break;
          case 5:
            symbolDuration = MicroSeconds (16);
            break;
          }

        //(Section 18.3.2.3 "Modulation-dependent parameters" Table 18-4 "Modulation-dependent parameters"; IEEE Std 802.11-2012)
        //corresponds to N_{DBPS} in the table
        double numDataBitsPerSymbol = payloadMode.GetDataRate (txVector.GetChannelWidth (), 0, 1) * symbolDuration.GetNanoSeconds () / 1e9;
        double numSymbols;

        if (mpdutype == MPDU_IN_AGGREGATE && preamble != WIFI_PREAMBLE_NONE)
          {
            //First packet in an A-MPDU
            numSymbols = ((16 + size * 8.0 + 6) / numDataBitsPerSymbol);
            if (incFlag == 1)
              {
                m_totalAmpduSize += size;
                m_totalAmpduNumSymbols += numSymbols;
              }
          }
        else if (mpdutype == MPDU_IN_AGGREGATE && preamble == WIFI_PREAMBLE_NONE)
          {
            //consecutive packets in an A-MPDU
            numSymbols = ((size * 8.0) / numDataBitsPerSymbol);
            if (incFlag == 1)
              {
                m_totalAmpduSize += size;
                m_totalAmpduNumSymbols += numSymbols;
              }
          }
        else if (mpdutype == LAST_MPDU_IN_AGGREGATE && preamble == WIFI_PREAMBLE_NONE)
          {
            //last packet in an A-MPDU
            uint32_t totalAmpduSize = m_totalAmpduSize + size;
            numSymbols = lrint (ceil ((16 + totalAmpduSize * 8.0 + 6) / numDataBitsPerSymbol));
            NS_ASSERT (m_totalAmpduNumSymbols <= numSymbols);
            numSymbols -= m_totalAmpduNumSymbols;
            if (incFlag == 1)
              {
                m_totalAmpduSize = 0;
                m_totalAmpduNumSymbols = 0;
              }
          }
        else if (mpdutype == NORMAL_MPDU && preamble != WIFI_PREAMBLE_NONE)
          {
            //Not an A-MPDU
            numSymbols = lrint (ceil ((16 + size * 8.0 + 6.0) / numDataBitsPerSymbol));
          }
        else
          {
            NS_FATAL_ERROR ("Wrong combination of preamble and packet type");
          }

        //Add signal extension for ERP PHY
        if (payloadMode.GetModulationClass () == WIFI_MOD_CLASS_ERP_OFDM)
          {
            return FemtoSeconds (numSymbols * symbolDuration.GetFemtoSeconds ()) + MicroSeconds (6);
          }
        else
          {
            return FemtoSeconds (numSymbols * symbolDuration.GetFemtoSeconds ());
          }
      }
    case WIFI_MOD_CLASS_HT:
    case WIFI_MOD_CLASS_VHT:
      {
        Time symbolDuration;
        double m_Stbc;
        //if short GI data rate is used then symbol duration is 3.6us else symbol duration is 4us
        //In the future has to create a stationmanager that only uses these data rates if sender and reciever support GI
        if (txVector.IsShortGuardInterval ())
          {
            symbolDuration = NanoSeconds (3600);
          }
        else
          {
            symbolDuration = MicroSeconds (4);
          }

        if (txVector.IsStbc ())
          {
            m_Stbc = 2;
          }
        else
          {
            m_Stbc = 1;
          }

        //check tables 20-35 and 20-36 in the .11n standard to get cases when nes = 2
        double Nes = 1;
        if (payloadMode.GetUniqueName () == "HtMcs21"
           || payloadMode.GetUniqueName () == "HtMcs22"
           || payloadMode.GetUniqueName () == "HtMcs23"
           || payloadMode.GetUniqueName () == "HtMcs28"
           || payloadMode.GetUniqueName () == "HtMcs29"
           || payloadMode.GetUniqueName () == "HtMcs30"
           || payloadMode.GetUniqueName () == "HtMcs31")
          {
            Nes = 2;
          }
        //check tables 22-30 to 22-61 in the .11ac standard to get cases when nes > 1
        //todo: improve logic to reduce the number of if cases
        //todo: extend to NSS > 4 for VHT rates
        if (txVector.GetChannelWidth () == 40
            && txVector.GetNss () == 3
            && payloadMode.GetMcsValue () >= 8)
          {
            Nes = 2;
          }
        if (txVector.GetChannelWidth () == 80
            && txVector.GetNss () == 2
            && payloadMode.GetMcsValue () >= 7)
          {
            Nes = 2;
          }
        if (txVector.GetChannelWidth () == 80
            && txVector.GetNss () == 3
            && payloadMode.GetMcsValue () >= 7)
          {
            Nes = 2;
          }
        if (txVector.GetChannelWidth () == 80
            && txVector.GetNss () == 3
            && payloadMode.GetMcsValue () == 9)
          {
            Nes = 3;
          }
        if (txVector.GetChannelWidth () == 80
            && txVector.GetNss () == 4
            && payloadMode.GetMcsValue () >= 4)
          {
            Nes = 2;
          }
        if (txVector.GetChannelWidth () == 80
            && txVector.GetNss () == 4
            && payloadMode.GetMcsValue () >= 7)
          {
            Nes = 3;
          }
        if (txVector.GetChannelWidth () == 160
            && payloadMode.GetMcsValue () >= 7)
          {
            Nes = 2;
          }
        if (txVector.GetChannelWidth () == 160
            && txVector.GetNss () == 2
            && payloadMode.GetMcsValue () >= 4)
          {
            Nes = 2;
          }
        if (txVector.GetChannelWidth () == 160
            && txVector.GetNss () == 2
            && payloadMode.GetMcsValue () >= 7)
          {
            Nes = 3;
          }
        if (txVector.GetChannelWidth () == 160
            && txVector.GetNss () == 3
            && payloadMode.GetMcsValue () >= 3)
          {
            Nes = 2;
          }
        if (txVector.GetChannelWidth () == 160
            && txVector.GetNss () == 3
            && payloadMode.GetMcsValue () >= 5)
          {
            Nes = 3;
          }
        if (txVector.GetChannelWidth () == 160
            && txVector.GetNss () == 3
            && payloadMode.GetMcsValue () >= 7)
          {
            Nes = 4;
          }
        if (txVector.GetChannelWidth () == 160
            && txVector.GetNss () == 4
            && payloadMode.GetMcsValue () >= 2)
          {
            Nes = 2;
          }
        if (txVector.GetChannelWidth () == 160
            && txVector.GetNss () == 4
            && payloadMode.GetMcsValue () >= 4)
          {
            Nes = 3;
          }
        if (txVector.GetChannelWidth () == 160
            && txVector.GetNss () == 4
            && payloadMode.GetMcsValue () >= 5)
          {
            Nes = 4;
          }
        if (txVector.GetChannelWidth () == 160
            && txVector.GetNss () == 4
            && payloadMode.GetMcsValue () >= 7)
          {
            Nes = 6;
          }

        //IEEE Std 802.11n, section 20.3.11, equation (20-32)
        double numDataBitsPerSymbol = payloadMode.GetDataRate (txVector.GetChannelWidth (), txVector.IsShortGuardInterval (), txVector.GetNss ()) * symbolDuration.GetNanoSeconds () / 1e9;
        double numSymbols;

        if (mpdutype == MPDU_IN_AGGREGATE && preamble != WIFI_PREAMBLE_NONE)
          {
            //First packet in an A-MPDU
            numSymbols = (m_Stbc * (16 + size * 8.0 + 6 * Nes) / (m_Stbc * numDataBitsPerSymbol));
            if (incFlag == 1)
              {
                m_totalAmpduSize += size;
                m_totalAmpduNumSymbols += numSymbols;
              }
          }
        else if (mpdutype == MPDU_IN_AGGREGATE && preamble == WIFI_PREAMBLE_NONE)
          {
            //consecutive packets in an A-MPDU
            numSymbols = (m_Stbc * size * 8.0) / (m_Stbc * numDataBitsPerSymbol);
            if (incFlag == 1)
              {
                m_totalAmpduSize += size;
                m_totalAmpduNumSymbols += numSymbols;
              }
          }
        else if (mpdutype == LAST_MPDU_IN_AGGREGATE && preamble == WIFI_PREAMBLE_NONE)
          {
            //last packet in an A-MPDU
            uint32_t totalAmpduSize = m_totalAmpduSize + size;
            numSymbols = lrint (m_Stbc * ceil ((16 + totalAmpduSize * 8.0 + 6 * Nes) / (m_Stbc * numDataBitsPerSymbol)));
            NS_ASSERT (m_totalAmpduNumSymbols <= numSymbols);
            numSymbols -= m_totalAmpduNumSymbols;
            if (incFlag == 1)
              {
                m_totalAmpduSize = 0;
                m_totalAmpduNumSymbols = 0;
              }
          }
        else if (mpdutype == NORMAL_MPDU && preamble != WIFI_PREAMBLE_NONE)
          {
            //Not an A-MPDU
            numSymbols = lrint (m_Stbc * ceil ((16 + size * 8.0 + 6.0 * Nes) / (m_Stbc * numDataBitsPerSymbol)));
          }
        else
          {
            NS_FATAL_ERROR ("Wrong combination of preamble and packet type");
          }

        if (payloadMode.GetModulationClass () == WIFI_MOD_CLASS_HT && frequency >= 2400 && frequency <= 2500 && ((mpdutype == NORMAL_MPDU && preamble != WIFI_PREAMBLE_NONE) || (mpdutype == LAST_MPDU_IN_AGGREGATE && preamble == WIFI_PREAMBLE_NONE))) //at 2.4 GHz
          {
            return FemtoSeconds (numSymbols * symbolDuration.GetFemtoSeconds ()) + MicroSeconds (6);
          }
        else //at 5 GHz
          {
            return FemtoSeconds (numSymbols * symbolDuration.GetFemtoSeconds ());
          }
      }
    case WIFI_MOD_CLASS_DSSS:
    case WIFI_MOD_CLASS_HR_DSSS:
      //(Section 17.2.3.6 "Long PLCP LENGTH field"; IEEE Std 802.11-2012)
      NS_LOG_LOGIC (" size=" << size
                             << " mode=" << payloadMode
                             << " rate=" << payloadMode.GetDataRate (22, 0, 1));
      return MicroSeconds (lrint (ceil ((size * 8.0) / (payloadMode.GetDataRate (22, 0, 1) / 1.0e6))));
    default:
      NS_FATAL_ERROR ("unsupported modulation class");
      return MicroSeconds (0);
    }
=======
  return MicroSeconds (4);
}

Time
WifiPhy::GetStartOfPacketDuration (const WifiTxVector& txVector)
{
  return MicroSeconds (4);
>>>>>>> origin
}

Time
WifiPhy::GetPayloadDuration (uint32_t size, const WifiTxVector& txVector, WifiPhyBand band, MpduType mpdutype, uint16_t staId)
{
  uint32_t totalAmpduSize;
  double totalAmpduNumSymbols;
  return GetPayloadDuration (size, txVector, band, mpdutype, false, totalAmpduSize, totalAmpduNumSymbols, staId);
}

Time
WifiPhy::GetPayloadDuration (uint32_t size, const WifiTxVector& txVector, WifiPhyBand band, MpduType mpdutype,
                             bool incFlag, uint32_t &totalAmpduSize, double &totalAmpduNumSymbols,
                             uint16_t staId)
{
  return GetStaticPhyEntity (txVector.GetModulationClass ())->GetPayloadDuration (size, txVector, band, mpdutype,
                                                                                  incFlag, totalAmpduSize, totalAmpduNumSymbols,
                                                                                  staId);
}

Time
WifiPhy::CalculatePhyPreambleAndHeaderDuration (const WifiTxVector& txVector)
{
  return GetStaticPhyEntity (txVector.GetModulationClass ())->CalculatePhyPreambleAndHeaderDuration (txVector);
}

Time
WifiPhy::CalculateTxDuration (uint32_t size, const WifiTxVector& txVector, WifiPhyBand band, uint16_t staId)
{
  Time duration = CalculatePhyPreambleAndHeaderDuration (txVector)
    + GetPayloadDuration (size, txVector, band, NORMAL_MPDU, staId);
  NS_ASSERT (duration.IsStrictlyPositive ());
  return duration;
}

Time
<<<<<<< HEAD
WifiPhy::CalculateTxDuration (uint32_t size, WifiTxVector txVector, WifiPreamble preamble, double frequency, enum mpduType mpdutype, uint8_t incFlag)
{
  Time duration = CalculatePlcpPreambleAndHeaderDuration (txVector, preamble)
    + GetPayloadDuration (size, txVector, preamble, frequency, mpdutype, incFlag);
  return duration;
=======
WifiPhy::CalculateTxDuration (Ptr<const WifiPsdu> psdu, const WifiTxVector& txVector, WifiPhyBand band)
{
  return CalculateTxDuration (GetWifiConstPsduMap (psdu, txVector), txVector, band);
}

Time
WifiPhy::CalculateTxDuration (WifiConstPsduMap psduMap, const WifiTxVector& txVector, WifiPhyBand band)
{
  return GetStaticPhyEntity (txVector.GetModulationClass ())->CalculateTxDuration (psduMap, txVector, band);
}

uint32_t
WifiPhy::GetMaxPsduSize (WifiModulationClass modulation)
{
  return GetStaticPhyEntity (modulation)->GetMaxPsduSize ();
>>>>>>> origin
}

Time
WifiPhy::CalculateTxDuration (uint32_t size, WifiTxVector txVector, WifiPreamble preamble, double frequency)
{
  return CalculateTxDuration (size, txVector, preamble, frequency, NORMAL_MPDU, 0);
}

void
WifiPhy::NotifyTxBegin (WifiConstPsduMap psdus, double txPowerW)
{
<<<<<<< HEAD
  m_phyTxBeginTrace (packet);
}

void
WifiPhy::NotifyTxEnd (Ptr<const Packet> packet)
{
  m_phyTxEndTrace (packet);
}

void
WifiPhy::NotifyTxDrop (Ptr<const Packet> packet)
{
  m_phyTxDropTrace (packet);
}

void
WifiPhy::NotifyRxBegin (Ptr<const Packet> packet)
{
  m_phyRxBeginTrace (packet);
}

void
WifiPhy::NotifyRxEnd (Ptr<const Packet> packet)
{
  m_phyRxEndTrace (packet);
}

void
WifiPhy::NotifyRxDrop (Ptr<const Packet> packet)
{
  m_phyRxDropTrace (packet);
}

void
WifiPhy::NotifyMonitorSniffRx (Ptr<const Packet> packet, uint16_t channelFreqMhz, uint16_t channelNumber, uint32_t rate, WifiPreamble preamble, WifiTxVector txVector, struct mpduInfo aMpdu, struct signalNoiseDbm signalNoise)
{
  m_phyMonitorSniffRxTrace (packet, channelFreqMhz, channelNumber, rate, preamble, txVector, aMpdu, signalNoise);
}

void
WifiPhy::NotifyMonitorSniffTx (Ptr<const Packet> packet, uint16_t channelFreqMhz, uint16_t channelNumber, uint32_t rate, WifiPreamble preamble, WifiTxVector txVector, struct mpduInfo aMpdu)
{
  m_phyMonitorSniffTxTrace (packet, channelFreqMhz, channelNumber, rate, preamble, txVector, aMpdu);
}


// Clause 15 rates (DSSS)

WifiMode
WifiPhy::GetDsssRate1Mbps ()
{
  static WifiMode mode =
    WifiModeFactory::CreateWifiMode ("DsssRate1Mbps",
                                     WIFI_MOD_CLASS_DSSS,
                                     true,
                                     WIFI_CODE_RATE_UNDEFINED,
                                     2);
  return mode;
}

WifiMode
WifiPhy::GetDsssRate2Mbps ()
{
  static WifiMode mode =
    WifiModeFactory::CreateWifiMode ("DsssRate2Mbps",
                                     WIFI_MOD_CLASS_DSSS,
                                     true,
                                     WIFI_CODE_RATE_UNDEFINED,
                                     4);
  return mode;
}


// Clause 18 rates (HR/DSSS)

WifiMode
WifiPhy::GetDsssRate5_5Mbps ()
{
  static WifiMode mode =
    WifiModeFactory::CreateWifiMode ("DsssRate5_5Mbps",
                                     WIFI_MOD_CLASS_HR_DSSS,
                                     true,
                                     WIFI_CODE_RATE_UNDEFINED,
                                     16);
  return mode;
}

WifiMode
WifiPhy::GetDsssRate11Mbps ()
{
  static WifiMode mode =
    WifiModeFactory::CreateWifiMode ("DsssRate11Mbps",
                                     WIFI_MOD_CLASS_HR_DSSS,
                                     true,
                                     WIFI_CODE_RATE_UNDEFINED,
                                     256);
  return mode;
}


// Clause 19.5 rates (ERP-OFDM)

WifiMode
WifiPhy::GetErpOfdmRate6Mbps ()
{
  static WifiMode mode =
    WifiModeFactory::CreateWifiMode ("ErpOfdmRate6Mbps",
                                     WIFI_MOD_CLASS_ERP_OFDM,
                                     true,
                                     WIFI_CODE_RATE_1_2,
                                     2);
  return mode;
}

WifiMode
WifiPhy::GetErpOfdmRate9Mbps ()
{
  static WifiMode mode =
    WifiModeFactory::CreateWifiMode ("ErpOfdmRate9Mbps",
                                     WIFI_MOD_CLASS_ERP_OFDM,
                                     false,
                                     WIFI_CODE_RATE_3_4,
                                     2);
  return mode;
}

WifiMode
WifiPhy::GetErpOfdmRate12Mbps ()
{
  static WifiMode mode =
    WifiModeFactory::CreateWifiMode ("ErpOfdmRate12Mbps",
                                     WIFI_MOD_CLASS_ERP_OFDM,
                                     true,
                                     WIFI_CODE_RATE_1_2,
                                     4);
  return mode;
}

WifiMode
WifiPhy::GetErpOfdmRate18Mbps ()
{
  static WifiMode mode =
    WifiModeFactory::CreateWifiMode ("ErpOfdmRate18Mbps",
                                     WIFI_MOD_CLASS_ERP_OFDM,
                                     false,
                                     WIFI_CODE_RATE_3_4,
                                     4);
  return mode;
}

WifiMode
WifiPhy::GetErpOfdmRate24Mbps ()
{
  static WifiMode mode =
    WifiModeFactory::CreateWifiMode ("ErpOfdmRate24Mbps",
                                     WIFI_MOD_CLASS_ERP_OFDM,
                                     true,
                                     WIFI_CODE_RATE_1_2,
                                     16);
  return mode;
}

WifiMode
WifiPhy::GetErpOfdmRate36Mbps ()
{
  static WifiMode mode =
    WifiModeFactory::CreateWifiMode ("ErpOfdmRate36Mbps",
                                     WIFI_MOD_CLASS_ERP_OFDM,
                                     false,
                                     WIFI_CODE_RATE_3_4,
                                     16);
  return mode;
}

WifiMode
WifiPhy::GetErpOfdmRate48Mbps ()
{
  static WifiMode mode =
    WifiModeFactory::CreateWifiMode ("ErpOfdmRate48Mbps",
                                     WIFI_MOD_CLASS_ERP_OFDM,
                                     false,
                                     WIFI_CODE_RATE_2_3,
                                     64);
  return mode;
}

WifiMode
WifiPhy::GetErpOfdmRate54Mbps ()
{
  static WifiMode mode =
    WifiModeFactory::CreateWifiMode ("ErpOfdmRate54Mbps",
                                     WIFI_MOD_CLASS_ERP_OFDM,
                                     false,
                                     WIFI_CODE_RATE_3_4,
                                     64);
  return mode;
}


// Clause 17 rates (OFDM)

WifiMode
WifiPhy::GetOfdmRate6Mbps ()
{
  static WifiMode mode =
    WifiModeFactory::CreateWifiMode ("OfdmRate6Mbps",
                                     WIFI_MOD_CLASS_OFDM,
                                     true,
                                     WIFI_CODE_RATE_1_2,
                                     2);
  return mode;
}

WifiMode
WifiPhy::GetOfdmRate9Mbps ()
{
  static WifiMode mode =
    WifiModeFactory::CreateWifiMode ("OfdmRate9Mbps",
                                     WIFI_MOD_CLASS_OFDM,
                                     false,
                                     WIFI_CODE_RATE_3_4,
                                     2);
  return mode;
}

WifiMode
WifiPhy::GetOfdmRate12Mbps ()
{
  static WifiMode mode =
    WifiModeFactory::CreateWifiMode ("OfdmRate12Mbps",
                                     WIFI_MOD_CLASS_OFDM,
                                     true,
                                     WIFI_CODE_RATE_1_2,
                                     4);
  return mode;
}

WifiMode
WifiPhy::GetOfdmRate18Mbps ()
{
  static WifiMode mode =
    WifiModeFactory::CreateWifiMode ("OfdmRate18Mbps",
                                     WIFI_MOD_CLASS_OFDM,
                                     false,
                                     WIFI_CODE_RATE_3_4,
                                     4);
  return mode;
}

WifiMode
WifiPhy::GetOfdmRate24Mbps ()
{
  static WifiMode mode =
    WifiModeFactory::CreateWifiMode ("OfdmRate24Mbps",
                                     WIFI_MOD_CLASS_OFDM,
                                     true,
                                     WIFI_CODE_RATE_1_2,
                                     16);
  return mode;
}

WifiMode
WifiPhy::GetOfdmRate36Mbps ()
{
  static WifiMode mode =
    WifiModeFactory::CreateWifiMode ("OfdmRate36Mbps",
                                     WIFI_MOD_CLASS_OFDM,
                                     false,
                                     WIFI_CODE_RATE_3_4,
                                     16);
  return mode;
}

WifiMode
WifiPhy::GetOfdmRate48Mbps ()
{
  static WifiMode mode =
    WifiModeFactory::CreateWifiMode ("OfdmRate48Mbps",
                                     WIFI_MOD_CLASS_OFDM,
                                     false,
                                     WIFI_CODE_RATE_2_3,
                                     64);
  return mode;
}

WifiMode
WifiPhy::GetOfdmRate54Mbps ()
{
  static WifiMode mode =
    WifiModeFactory::CreateWifiMode ("OfdmRate54Mbps",
                                     WIFI_MOD_CLASS_OFDM,
                                     false,
                                     WIFI_CODE_RATE_3_4,
                                     64);
  return mode;
}


// 10 MHz channel rates

WifiMode
WifiPhy::GetOfdmRate3MbpsBW10MHz ()
{
  static WifiMode mode =
    WifiModeFactory::CreateWifiMode ("OfdmRate3MbpsBW10MHz",
                                     WIFI_MOD_CLASS_OFDM,
                                     true,
                                     WIFI_CODE_RATE_1_2,
                                     2);
  return mode;
}

WifiMode
WifiPhy::GetOfdmRate4_5MbpsBW10MHz ()
{
  static WifiMode mode =
    WifiModeFactory::CreateWifiMode ("OfdmRate4_5MbpsBW10MHz",
                                     WIFI_MOD_CLASS_OFDM,
                                     false,
                                     WIFI_CODE_RATE_3_4,
                                     2);
  return mode;
}

WifiMode
WifiPhy::GetOfdmRate6MbpsBW10MHz ()
{
  static WifiMode mode =
    WifiModeFactory::CreateWifiMode ("OfdmRate6MbpsBW10MHz",
                                     WIFI_MOD_CLASS_OFDM,
                                     true,
                                     WIFI_CODE_RATE_1_2,
                                     4);
  return mode;
}

WifiMode
WifiPhy::GetOfdmRate9MbpsBW10MHz ()
{
  static WifiMode mode =
    WifiModeFactory::CreateWifiMode ("OfdmRate9MbpsBW10MHz",
                                     WIFI_MOD_CLASS_OFDM,
                                     false,
                                     WIFI_CODE_RATE_3_4,
                                     4);
  return mode;
}

WifiMode
WifiPhy::GetOfdmRate12MbpsBW10MHz ()
{
  static WifiMode mode =
    WifiModeFactory::CreateWifiMode ("OfdmRate12MbpsBW10MHz",
                                     WIFI_MOD_CLASS_OFDM,
                                     true,
                                     WIFI_CODE_RATE_1_2,
                                     16);
  return mode;
}

WifiMode
WifiPhy::GetOfdmRate18MbpsBW10MHz ()
{
  static WifiMode mode =
    WifiModeFactory::CreateWifiMode ("OfdmRate18MbpsBW10MHz",
                                     WIFI_MOD_CLASS_OFDM,
                                     false,
                                     WIFI_CODE_RATE_3_4,
                                     16);
  return mode;
}

WifiMode
WifiPhy::GetOfdmRate24MbpsBW10MHz ()
{
  static WifiMode mode =
    WifiModeFactory::CreateWifiMode ("OfdmRate24MbpsBW10MHz",
                                     WIFI_MOD_CLASS_OFDM,
                                     false,
                                     WIFI_CODE_RATE_2_3,
                                     64);
  return mode;
}

WifiMode
WifiPhy::GetOfdmRate27MbpsBW10MHz ()
{
  static WifiMode mode =
    WifiModeFactory::CreateWifiMode ("OfdmRate27MbpsBW10MHz",
                                     WIFI_MOD_CLASS_OFDM,
                                     false,
                                     WIFI_CODE_RATE_3_4,
                                     64);
  return mode;
}


// 5 MHz channel rates

WifiMode
WifiPhy::GetOfdmRate1_5MbpsBW5MHz ()
{
  static WifiMode mode =
    WifiModeFactory::CreateWifiMode ("OfdmRate1_5MbpsBW5MHz",
                                     WIFI_MOD_CLASS_OFDM,
                                     true,
                                     WIFI_CODE_RATE_1_2,
                                     2);
  return mode;
}

WifiMode
WifiPhy::GetOfdmRate2_25MbpsBW5MHz ()
{
  static WifiMode mode =
    WifiModeFactory::CreateWifiMode ("OfdmRate2_25MbpsBW5MHz",
                                     WIFI_MOD_CLASS_OFDM,
                                     false,
                                     WIFI_CODE_RATE_3_4,
                                     2);
  return mode;
}

WifiMode
WifiPhy::GetOfdmRate3MbpsBW5MHz ()
{
  static WifiMode mode =
    WifiModeFactory::CreateWifiMode ("OfdmRate3MbpsBW5MHz",
                                     WIFI_MOD_CLASS_OFDM,
                                     true,
                                     WIFI_CODE_RATE_1_2,
                                     4);
  return mode;
}

WifiMode
WifiPhy::GetOfdmRate4_5MbpsBW5MHz ()
{
  static WifiMode mode =
    WifiModeFactory::CreateWifiMode ("OfdmRate4_5MbpsBW5MHz",
                                     WIFI_MOD_CLASS_OFDM,
                                     false,
                                     WIFI_CODE_RATE_3_4,
                                     4);
  return mode;
}

WifiMode
WifiPhy::GetOfdmRate6MbpsBW5MHz ()
{
  static WifiMode mode =
    WifiModeFactory::CreateWifiMode ("OfdmRate6MbpsBW5MHz",
                                     WIFI_MOD_CLASS_OFDM,
                                     true,
                                     WIFI_CODE_RATE_1_2,
                                     16);
  return mode;
}

WifiMode
WifiPhy::GetOfdmRate9MbpsBW5MHz ()
{
  static WifiMode mode =
    WifiModeFactory::CreateWifiMode ("OfdmRate9MbpsBW5MHz",
                                     WIFI_MOD_CLASS_OFDM,
                                     false,
                                     WIFI_CODE_RATE_3_4,
                                     16);
  return mode;
}

WifiMode
WifiPhy::GetOfdmRate12MbpsBW5MHz ()
{
  static WifiMode mode =
    WifiModeFactory::CreateWifiMode ("OfdmRate12MbpsBW5MHz",
                                     WIFI_MOD_CLASS_OFDM,
                                     false,
                                     WIFI_CODE_RATE_2_3,
                                     64);
  return mode;
}

WifiMode
WifiPhy::GetOfdmRate13_5MbpsBW5MHz ()
{
  static WifiMode mode =
    WifiModeFactory::CreateWifiMode ("OfdmRate13_5MbpsBW5MHz",
                                     WIFI_MOD_CLASS_OFDM,
                                     false,
                                     WIFI_CODE_RATE_3_4,
                                     64);
  return mode;
}


// Clause 20

WifiMode
WifiPhy::GetHtMcs0 ()
{
  static WifiMode mcs =
    WifiModeFactory::CreateWifiMcs ("HtMcs0", 0, WIFI_MOD_CLASS_HT);
  return mcs;
}

WifiMode
WifiPhy::GetHtMcs1 ()
{
  static WifiMode mcs =
    WifiModeFactory::CreateWifiMcs ("HtMcs1", 1, WIFI_MOD_CLASS_HT);
  return mcs;
}

WifiMode
WifiPhy::GetHtMcs2 ()
{
  static WifiMode mcs =
    WifiModeFactory::CreateWifiMcs ("HtMcs2", 2, WIFI_MOD_CLASS_HT);
  return mcs;
}

WifiMode
WifiPhy::GetHtMcs3 ()
{
  static WifiMode mcs =
    WifiModeFactory::CreateWifiMcs ("HtMcs3", 3, WIFI_MOD_CLASS_HT);
  return mcs;
}

WifiMode
WifiPhy::GetHtMcs4 ()
{
  static WifiMode mcs =
    WifiModeFactory::CreateWifiMcs ("HtMcs4", 4, WIFI_MOD_CLASS_HT);
  return mcs;
}

WifiMode
WifiPhy::GetHtMcs5 ()
{
  static WifiMode mcs =
    WifiModeFactory::CreateWifiMcs ("HtMcs5", 5, WIFI_MOD_CLASS_HT);
  return mcs;
}

WifiMode
WifiPhy::GetHtMcs6 ()
{
  static WifiMode mcs =
    WifiModeFactory::CreateWifiMcs ("HtMcs6", 6, WIFI_MOD_CLASS_HT);
  return mcs;
}

WifiMode
WifiPhy::GetHtMcs7 ()
{
  static WifiMode mcs =
    WifiModeFactory::CreateWifiMcs ("HtMcs7", 7, WIFI_MOD_CLASS_HT);
  return mcs;
}

WifiMode
WifiPhy::GetHtMcs8 ()
{
  static WifiMode mcs =
    WifiModeFactory::CreateWifiMcs ("HtMcs8", 8, WIFI_MOD_CLASS_HT);
  return mcs;
}

WifiMode
WifiPhy::GetHtMcs9 ()
{
  static WifiMode mcs =
    WifiModeFactory::CreateWifiMcs ("HtMcs9", 9, WIFI_MOD_CLASS_HT);
  return mcs;
}

WifiMode
WifiPhy::GetHtMcs10 ()
{
  static WifiMode mcs =
    WifiModeFactory::CreateWifiMcs ("HtMcs10", 10, WIFI_MOD_CLASS_HT);
  return mcs;
}

WifiMode
WifiPhy::GetHtMcs11 ()
{
  static WifiMode mcs =
    WifiModeFactory::CreateWifiMcs ("HtMcs11", 11, WIFI_MOD_CLASS_HT);
  return mcs;
}

WifiMode
WifiPhy::GetHtMcs12 ()
{
  static WifiMode mcs =
    WifiModeFactory::CreateWifiMcs ("HtMcs12", 12, WIFI_MOD_CLASS_HT);
  return mcs;
}

WifiMode
WifiPhy::GetHtMcs13 ()
{
  static WifiMode mcs =
    WifiModeFactory::CreateWifiMcs ("HtMcs13", 13, WIFI_MOD_CLASS_HT);
  return mcs;
}

WifiMode
WifiPhy::GetHtMcs14 ()
{
  static WifiMode mcs =
    WifiModeFactory::CreateWifiMcs ("HtMcs14", 14, WIFI_MOD_CLASS_HT);
  return mcs;
}

WifiMode
WifiPhy::GetHtMcs15 ()
{
  static WifiMode mcs =
    WifiModeFactory::CreateWifiMcs ("HtMcs15", 15, WIFI_MOD_CLASS_HT);
  return mcs;
}

WifiMode
WifiPhy::GetHtMcs16 ()
{
  static WifiMode mcs =
    WifiModeFactory::CreateWifiMcs ("HtMcs16", 16, WIFI_MOD_CLASS_HT);
  return mcs;
}

WifiMode
WifiPhy::GetHtMcs17 ()
{
  static WifiMode mcs =
    WifiModeFactory::CreateWifiMcs ("HtMcs17", 17, WIFI_MOD_CLASS_HT);
  return mcs;
}

WifiMode
WifiPhy::GetHtMcs18 ()
{
  static WifiMode mcs =
    WifiModeFactory::CreateWifiMcs ("HtMcs18", 18, WIFI_MOD_CLASS_HT);
  return mcs;
}

WifiMode
WifiPhy::GetHtMcs19 ()
{
  static WifiMode mcs =
    WifiModeFactory::CreateWifiMcs ("HtMcs19", 19, WIFI_MOD_CLASS_HT);
  return mcs;
}

WifiMode
WifiPhy::GetHtMcs20 ()
{
  static WifiMode mcs =
    WifiModeFactory::CreateWifiMcs ("HtMcs20", 20, WIFI_MOD_CLASS_HT);
  return mcs;
}

WifiMode
WifiPhy::GetHtMcs21 ()
{
  static WifiMode mcs =
    WifiModeFactory::CreateWifiMcs ("HtMcs21", 21, WIFI_MOD_CLASS_HT);
  return mcs;
}

WifiMode
WifiPhy::GetHtMcs22 ()
{
  static WifiMode mcs =
    WifiModeFactory::CreateWifiMcs ("HtMcs22", 22, WIFI_MOD_CLASS_HT);
  return mcs;
}

WifiMode
WifiPhy::GetHtMcs23 ()
{
  static WifiMode mcs =
    WifiModeFactory::CreateWifiMcs ("HtMcs23", 23, WIFI_MOD_CLASS_HT);
  return mcs;
}

WifiMode
WifiPhy::GetHtMcs24 ()
{
  static WifiMode mcs =
    WifiModeFactory::CreateWifiMcs ("HtMcs24", 24, WIFI_MOD_CLASS_HT);
  return mcs;
}

WifiMode
WifiPhy::GetHtMcs25 ()
{
  static WifiMode mcs =
    WifiModeFactory::CreateWifiMcs ("HtMcs25", 25, WIFI_MOD_CLASS_HT);
  return mcs;
}

WifiMode
WifiPhy::GetHtMcs26 ()
{
  static WifiMode mcs =
    WifiModeFactory::CreateWifiMcs ("HtMcs26", 26, WIFI_MOD_CLASS_HT);
  return mcs;
}

WifiMode
WifiPhy::GetHtMcs27 ()
{
  static WifiMode mcs =
    WifiModeFactory::CreateWifiMcs ("HtMcs27", 27, WIFI_MOD_CLASS_HT);
  return mcs;
}

WifiMode
WifiPhy::GetHtMcs28 ()
{
  static WifiMode mcs =
    WifiModeFactory::CreateWifiMcs ("HtMcs28", 28, WIFI_MOD_CLASS_HT);
  return mcs;
}

WifiMode
WifiPhy::GetHtMcs29 ()
{
  static WifiMode mcs =
    WifiModeFactory::CreateWifiMcs ("HtMcs29", 29, WIFI_MOD_CLASS_HT);
  return mcs;
}

WifiMode
WifiPhy::GetHtMcs30 ()
{
  static WifiMode mcs =
    WifiModeFactory::CreateWifiMcs ("HtMcs30", 30, WIFI_MOD_CLASS_HT);
  return mcs;
}

WifiMode
WifiPhy::GetHtMcs31 ()
{
  static WifiMode mcs =
    WifiModeFactory::CreateWifiMcs ("HtMcs31", 31, WIFI_MOD_CLASS_HT);
  return mcs;
}


// Clause 22

WifiMode
WifiPhy::GetVhtMcs0 ()
{
  static WifiMode mcs =
    WifiModeFactory::CreateWifiMcs ("VhtMcs0", 0, WIFI_MOD_CLASS_VHT);
  return mcs;
}

WifiMode
WifiPhy::GetVhtMcs1 ()
{
  static WifiMode mcs =
    WifiModeFactory::CreateWifiMcs ("VhtMcs1", 1, WIFI_MOD_CLASS_VHT);
  return mcs;
}

WifiMode
WifiPhy::GetVhtMcs2 ()
{
  static WifiMode mcs =
    WifiModeFactory::CreateWifiMcs ("VhtMcs2", 2, WIFI_MOD_CLASS_VHT);
  return mcs;
}

WifiMode
WifiPhy::GetVhtMcs3 ()
{
  static WifiMode mcs =
    WifiModeFactory::CreateWifiMcs ("VhtMcs3", 3, WIFI_MOD_CLASS_VHT);
  return mcs;
}

WifiMode
WifiPhy::GetVhtMcs4 ()
{
  static WifiMode mcs =
    WifiModeFactory::CreateWifiMcs ("VhtMcs4", 4, WIFI_MOD_CLASS_VHT);
  return mcs;
}

WifiMode
WifiPhy::GetVhtMcs5 ()
{
  static WifiMode mcs =
    WifiModeFactory::CreateWifiMcs ("VhtMcs5", 5, WIFI_MOD_CLASS_VHT);
  return mcs;
}

WifiMode
WifiPhy::GetVhtMcs6 ()
{
  static WifiMode mcs =
    WifiModeFactory::CreateWifiMcs ("VhtMcs6", 6, WIFI_MOD_CLASS_VHT);
  return mcs;
}

WifiMode
WifiPhy::GetVhtMcs7 ()
{
  static WifiMode mcs =
    WifiModeFactory::CreateWifiMcs ("VhtMcs7", 7, WIFI_MOD_CLASS_VHT);
  return mcs;
}

WifiMode
WifiPhy::GetVhtMcs8 ()
{
  static WifiMode mcs =
    WifiModeFactory::CreateWifiMcs ("VhtMcs8", 8, WIFI_MOD_CLASS_VHT);
  return mcs;
}

WifiMode
WifiPhy::GetVhtMcs9 ()
{
  static WifiMode mcs =
    WifiModeFactory::CreateWifiMcs ("VhtMcs9", 9, WIFI_MOD_CLASS_VHT);
  return mcs;
}

bool
WifiPhy::IsValidTxVector (WifiTxVector txVector)
{
  uint32_t chWidth = txVector.GetChannelWidth();
  uint8_t nss = txVector.GetNss();
  std::string modeName = txVector.GetMode().GetUniqueName();

  if (chWidth == 20)
    {
      if (nss != 3 && nss != 6)
        {
          return (modeName != "VhtMcs9");
        }
    }
  else if (chWidth == 80)
    {
      if (nss == 3 || nss == 7)
        {
          return (modeName != "VhtMcs6");
        }
      else if (nss == 6)
        {
          return (modeName != "VhtMcs9");
        }
    }
  else if (chWidth == 160)
    {
      if (nss == 3)
        {
          return (modeName != "VhtMcs9");
        }
    }

  return true;
}

bool
WifiPhy::IsModeSupported (WifiMode mode) const
{
  for (uint32_t i = 0; i < GetNModes (); i++)
    {
      if (mode == GetMode (i))
        {
          return true;
        }
    }
  return false;
}

bool
WifiPhy::IsMcsSupported (WifiMode mcs) const
{
  for (uint32_t i = 0; i < GetNMcs (); i++)
    {
      if (mcs == GetMcs (i))
        {
          return true;
        }
    }
  return false;
}

uint32_t
WifiPhy::GetNModes (void) const
{
  return m_deviceRateSet.size ();
}

WifiMode
WifiPhy::GetMode (uint32_t mode) const
{
  return m_deviceRateSet[mode];
}

uint8_t
WifiPhy::GetNMcs (void) const
{
  return m_deviceMcsSet.size ();
}

WifiMode
WifiPhy::GetMcs (uint8_t mcs) const
{
  return m_deviceMcsSet[mcs];
}

double
WifiPhy::DbToRatio (double dB) const
{
  double ratio = std::pow (10.0, dB / 10.0);
  return ratio;
}

double
WifiPhy::DbmToW (double dBm) const
{
  double mW = std::pow (10.0, dBm / 10.0);
  return mW / 1000.0;
}

double
WifiPhy::WToDbm (double w) const
{
  return 10.0 * std::log10 (w * 1000.0);
}

double
WifiPhy::RatioToDb (double ratio) const
{
  return 10.0 * std::log10 (ratio);
}

bool
WifiPhy::IsStateCcaBusy (void)
{
  return m_state->IsStateCcaBusy ();
}

bool
WifiPhy::IsStateIdle (void)
{
  return m_state->IsStateIdle ();
}

bool
WifiPhy::IsStateBusy (void)
{
  return m_state->IsStateBusy ();
}

bool
WifiPhy::IsStateRx (void)
{
  return m_state->IsStateRx ();
}

bool
WifiPhy::IsStateTx (void)
{
  return m_state->IsStateTx ();
}

bool
WifiPhy::IsStateSwitching (void)
{
  return m_state->IsStateSwitching ();
}

bool
WifiPhy::IsStateSleep (void)
{
  return m_state->IsStateSleep ();
}

Time
WifiPhy::GetStateDuration (void)
{
  return m_state->GetStateDuration ();
}

Time
WifiPhy::GetDelayUntilIdle (void)
{
  return m_state->GetDelayUntilIdle ();
}

Time
WifiPhy::GetLastRxStartTime (void) const
{
  return m_state->GetLastRxStartTime ();
}

int64_t
WifiPhy::AssignStreams (int64_t stream)
{
  NS_LOG_FUNCTION (this << stream);
  m_random->SetStream (stream);
  return 1;
}

std::ostream& operator<< (std::ostream& os, enum WifiPhy::State state)
{
  switch (state)
=======
  if (!m_phyTxBeginTrace.IsEmpty ())
>>>>>>> origin
    {
      for (auto const& psdu : psdus)
        {
          for (auto& mpdu : *PeekPointer (psdu.second))
            {
              m_phyTxBeginTrace (mpdu->GetProtocolDataUnit (), txPowerW);
            }
        }
    }
}

void
WifiPhy::NotifyTxEnd (WifiConstPsduMap psdus)
{
  if (!m_phyTxEndTrace.IsEmpty ())
    {
      for (auto const& psdu : psdus)
        {
          for (auto& mpdu : *PeekPointer (psdu.second))
            {
              m_phyTxEndTrace (mpdu->GetProtocolDataUnit ());
            }
        }
    }
}

void
WifiPhy::NotifyTxDrop (Ptr<const WifiPsdu> psdu)
{
  if (!m_phyTxDropTrace.IsEmpty ())
    {
      for (auto& mpdu : *PeekPointer (psdu))
        {
          m_phyTxDropTrace (mpdu->GetProtocolDataUnit ());
        }
    }
}

void
WifiPhy::NotifyRxBegin (Ptr<const WifiPsdu> psdu, const RxPowerWattPerChannelBand& rxPowersW)
{
  if (psdu && !m_phyRxBeginTrace.IsEmpty ())
    {
      for (auto& mpdu : *PeekPointer (psdu))
        {
          m_phyRxBeginTrace (mpdu->GetProtocolDataUnit (), rxPowersW);
        }
    }
}

void
WifiPhy::NotifyRxEnd (Ptr<const WifiPsdu> psdu)
{
  if (psdu && !m_phyRxEndTrace.IsEmpty ())
    {
      for (auto& mpdu : *PeekPointer (psdu))
        {
          m_phyRxEndTrace (mpdu->GetProtocolDataUnit ());
        }
    }
}

void
WifiPhy::NotifyRxDrop (Ptr<const WifiPsdu> psdu, WifiPhyRxfailureReason reason)
{
  if (psdu && !m_phyRxDropTrace.IsEmpty ())
    {
      for (auto& mpdu : *PeekPointer (psdu))
        {
          m_phyRxDropTrace (mpdu->GetProtocolDataUnit (), reason);
        }
    }
}

void
WifiPhy::NotifyMonitorSniffRx (Ptr<const WifiPsdu> psdu, uint16_t channelFreqMhz, WifiTxVector txVector,
                               SignalNoiseDbm signalNoise, std::vector<bool> statusPerMpdu, uint16_t staId)
{
  MpduInfo aMpdu;
  if (psdu->IsAggregate ())
    {
      //Expand A-MPDU
      NS_ASSERT_MSG (txVector.IsAggregation (), "TxVector with aggregate flag expected here according to PSDU");
      aMpdu.mpduRefNumber = ++m_rxMpduReferenceNumber;
      size_t nMpdus = psdu->GetNMpdus ();
      NS_ASSERT_MSG (statusPerMpdu.size () == nMpdus, "Should have one reception status per MPDU");
      if (!m_phyMonitorSniffRxTrace.IsEmpty ())
        {
          aMpdu.type = (psdu->IsSingle ()) ? SINGLE_MPDU : FIRST_MPDU_IN_AGGREGATE;
          for (size_t i = 0; i < nMpdus;)
            {
              if (statusPerMpdu.at (i)) //packet received without error, hand over to sniffer
                {
                  m_phyMonitorSniffRxTrace (psdu->GetAmpduSubframe (i), channelFreqMhz, txVector, aMpdu, signalNoise, staId);
                }
              ++i;
              aMpdu.type = (i == (nMpdus - 1)) ? LAST_MPDU_IN_AGGREGATE : MIDDLE_MPDU_IN_AGGREGATE;
            }
        }
    }
  else
    {
      NS_ASSERT_MSG (statusPerMpdu.size () == 1, "Should have one reception status for normal MPDU");
      if (!m_phyMonitorSniffRxTrace.IsEmpty ())
        {
          aMpdu.type = NORMAL_MPDU;
          m_phyMonitorSniffRxTrace (psdu->GetPacket (), channelFreqMhz, txVector, aMpdu, signalNoise, staId);
        }
    }
}

void
WifiPhy::NotifyMonitorSniffTx (Ptr<const WifiPsdu> psdu, uint16_t channelFreqMhz, WifiTxVector txVector, uint16_t staId)
{
  MpduInfo aMpdu;
  if (psdu->IsAggregate ())
    {
      //Expand A-MPDU
      NS_ASSERT_MSG (txVector.IsAggregation (), "TxVector with aggregate flag expected here according to PSDU");
      aMpdu.mpduRefNumber = ++m_rxMpduReferenceNumber;
      if (!m_phyMonitorSniffTxTrace.IsEmpty ())
        {
          size_t nMpdus = psdu->GetNMpdus ();
          aMpdu.type = (psdu->IsSingle ()) ? SINGLE_MPDU: FIRST_MPDU_IN_AGGREGATE;
          for (size_t i = 0; i < nMpdus;)
            {
              m_phyMonitorSniffTxTrace (psdu->GetAmpduSubframe (i), channelFreqMhz, txVector, aMpdu, staId);
              ++i;
              aMpdu.type = (i == (nMpdus - 1)) ? LAST_MPDU_IN_AGGREGATE : MIDDLE_MPDU_IN_AGGREGATE;
            }
        }
    }
  else
    {
      if (!m_phyMonitorSniffTxTrace.IsEmpty ())
        {
          aMpdu.type = NORMAL_MPDU;
          m_phyMonitorSniffTxTrace (psdu->GetPacket (), channelFreqMhz, txVector, aMpdu, staId);
        }
    }
}

WifiConstPsduMap
WifiPhy::GetWifiConstPsduMap (Ptr<const WifiPsdu> psdu, const WifiTxVector& txVector)
{
  return GetStaticPhyEntity (txVector.GetModulationClass ())->GetWifiConstPsduMap (psdu, txVector);
}

void
WifiPhy::Send (Ptr<const WifiPsdu> psdu, const WifiTxVector& txVector)
{
  NS_LOG_FUNCTION (this << *psdu << txVector);
  Send (GetWifiConstPsduMap (psdu, txVector), txVector);
}

void
WifiPhy::Send (WifiConstPsduMap psdus, WifiTxVector txVector)
{
  NS_LOG_FUNCTION (this << psdus << txVector);
  /* Transmission can happen if:
   *  - we are syncing on a packet. It is the responsibility of the
   *    MAC layer to avoid doing this but the PHY does nothing to
   *    prevent it.
   *  - we are idle
   */
  NS_ASSERT (!m_state->IsStateTx () && !m_state->IsStateSwitching ());
  NS_ASSERT (m_endTxEvent.IsExpired ());

  if (txVector.GetNssMax () > GetMaxSupportedTxSpatialStreams ())
    {
      NS_FATAL_ERROR ("Unsupported number of spatial streams!");
    }

  if (m_state->IsStateSleep ())
    {
      NS_LOG_DEBUG ("Dropping packet because in sleep mode");
      for (auto const& psdu : psdus)
        {
          NotifyTxDrop (psdu.second);
        }
      return;
    }
  
  // Set RU PHY indices
  if (txVector.IsMu ())
    {
      for (auto& heMuUserInfo : txVector.GetHeMuUserInfoMap ())
        {
          heMuUserInfo.second.ru.SetPhyIndex (txVector.GetChannelWidth (),
                                              m_operatingChannel.GetPrimaryChannelIndex (20));
        }
    }

  Time txDuration = CalculateTxDuration (psdus, txVector, GetPhyBand ());

  bool noEndPreambleDetectionEvent = true;
  for (const auto & it : m_phyEntities)
    {
      noEndPreambleDetectionEvent &= it.second->NoEndPreambleDetectionEvents ();
    }
  if (!noEndPreambleDetectionEvent || ((m_currentEvent != 0) && (m_currentEvent->GetEndTime () > (Simulator::Now () + m_state->GetDelayUntilIdle ()))))
    {
      AbortCurrentReception (RECEPTION_ABORTED_BY_TX);
      //that packet will be noise _after_ the transmission.
      SwitchMaybeToCcaBusy (GetMeasurementChannelWidth (m_currentEvent != 0 ? m_currentEvent->GetPpdu () : nullptr));
    }

  for (auto & it : m_phyEntities)
    {
      it.second->CancelRunningEndPreambleDetectionEvents ();
    }
  m_currentPreambleEvents.clear ();
  m_endPhyRxEvent.Cancel ();

  if (m_powerRestricted)
    {
      NS_LOG_DEBUG ("Transmitting with power restriction for " << txDuration.As (Time::NS));
    }
  else
    {
      NS_LOG_DEBUG ("Transmitting without power restriction for " << txDuration.As (Time::NS));
    }

  if (m_state->GetState () == WifiPhyState::OFF)
    {
      NS_LOG_DEBUG ("Transmission canceled because device is OFF");
      return;
    }

  Ptr<WifiPpdu> ppdu = GetPhyEntity (txVector.GetModulationClass ())->BuildPpdu (psdus, txVector, txDuration);
  m_previouslyRxPpduUid = UINT64_MAX; //reset (after creation of PPDU) to use it only once

  double txPowerW = DbmToW (GetTxPowerForTransmission (ppdu) + GetTxGain ());
  NotifyTxBegin (psdus, txPowerW);
  if (!m_phyTxPsduBeginTrace.IsEmpty ())
    {
      m_phyTxPsduBeginTrace (psdus, txVector, txPowerW);
    }
  for (auto const& psdu : psdus)
    {
      NotifyMonitorSniffTx (psdu.second, GetFrequency (), txVector, psdu.first);
    }
  m_state->SwitchToTx (txDuration, psdus, GetPowerDbm (txVector.GetTxPowerLevel ()), txVector);

  if (m_wifiRadioEnergyModel != 0 && m_wifiRadioEnergyModel->GetMaximumTimeInState (WifiPhyState::TX) < txDuration)
    {
      ppdu->SetTruncatedTx ();
    }

  m_endTxEvent = Simulator::Schedule (txDuration, &WifiPhy::NotifyTxEnd, this, psdus); //TODO: fix for MU

  StartTx (ppdu);

  m_channelAccessRequested = false;
  m_powerRestricted = false;

  Simulator::Schedule (txDuration, &WifiPhy::Reset, this);
}

uint64_t
WifiPhy::GetPreviouslyRxPpduUid (void) const
{
  return m_previouslyRxPpduUid;
}

void
WifiPhy::Reset (void)
{
  NS_LOG_FUNCTION (this);
  m_currentPreambleEvents.clear ();
  m_currentEvent = 0;
  for (auto & phyEntity : m_phyEntities)
    {
      phyEntity.second->CancelAllEvents ();
    }
}

void
WifiPhy::StartReceivePreamble (Ptr<WifiPpdu> ppdu, RxPowerWattPerChannelBand& rxPowersW, Time rxDuration)
{
  WifiModulationClass modulation = ppdu->GetTxVector ().GetModulationClass ();
  auto it = m_phyEntities.find (modulation);
  if (it != m_phyEntities.end ())
    {
      it->second->StartReceivePreamble (ppdu, rxPowersW, rxDuration);
    }
  else
    {
      //TODO find a fallback PHY for receiving the PPDU (e.g. 11a for 11ax due to preamble structure)
      NS_LOG_DEBUG ("Unsupported modulation received (" << modulation << "), consider as noise");
      if (ppdu->GetTxDuration () > m_state->GetDelayUntilIdle ())
        {
          m_interference.Add (ppdu, ppdu->GetTxVector (), rxDuration, rxPowersW);
          SwitchMaybeToCcaBusy (GetMeasurementChannelWidth (nullptr));
        }
    }
}

WifiSpectrumBand
WifiPhy::ConvertHeRuSubcarriers (uint16_t bandWidth, uint16_t guardBandwidth,
                                 HeRu::SubcarrierRange range, uint8_t bandIndex) const
{
  NS_ASSERT_MSG (false, "802.11ax can only be used with SpectrumWifiPhy");
  WifiSpectrumBand convertedSubcarriers;
  return convertedSubcarriers;
}

void
WifiPhy::EndReceiveInterBss (void)
{
  NS_LOG_FUNCTION (this);
  if (!m_channelAccessRequested)
    {
      m_powerRestricted = false;
    }
}

void
WifiPhy::ResetReceive (Ptr<Event> event)
{
  NS_LOG_FUNCTION (this << *event);
  NS_ASSERT (!IsStateRx ());
  m_interference.NotifyRxEnd (Simulator::Now ());
  m_currentEvent = 0;
  m_currentPreambleEvents.clear ();
  SwitchMaybeToCcaBusy (GetMeasurementChannelWidth (event->GetPpdu ()));
}

void
WifiPhy::NotifyChannelAccessRequested (void)
{
  NS_LOG_FUNCTION (this);
  m_channelAccessRequested = true;
}

bool
WifiPhy::IsModeSupported (WifiMode mode) const
{
  for (const auto & phyEntity : m_phyEntities)
    {
      if (phyEntity.second->IsModeSupported (mode))
        {
          return true;
        }
    }
  return false;
}

WifiMode
WifiPhy::GetDefaultMode (void) const
{
  //Start from oldest standards and move up (guaranteed by fact that WifModulationClass is ordered)
  for (const auto & phyEntity : m_phyEntities)
    {
      for (const auto & mode : *(phyEntity.second))
        {
          return mode;
        }
    }
  NS_ASSERT_MSG (false, "Should have found at least one default mode");
  return WifiMode ();
}

bool
WifiPhy::IsMcsSupported (WifiModulationClass modulation, uint8_t mcs) const
{
  const auto phyEntity = m_phyEntities.find (modulation);
  if (phyEntity == m_phyEntities.end ())
    {
      return false;
    }
  return phyEntity->second->IsMcsSupported (mcs);
}

std::list<WifiMode>
WifiPhy::GetModeList (void) const
{
  std::list<WifiMode> list;
  for (const auto & phyEntity : m_phyEntities)
    {
      if (!phyEntity.second->HandlesMcsModes ()) //to exclude MCSs from search
        {
          for (const auto & mode : *(phyEntity.second))
            {
              list.emplace_back (mode);
            }
        }
    }
  return list;
}

std::list<WifiMode>
WifiPhy::GetModeList (WifiModulationClass modulation) const
{
  std::list<WifiMode> list;
  const auto phyEntity = m_phyEntities.find (modulation);
  if (phyEntity != m_phyEntities.end ())
    {
      if (!phyEntity->second->HandlesMcsModes ()) //to exclude MCSs from search
        {
          for (const auto & mode : *(phyEntity->second))
            {
              list.emplace_back (mode);
            }
        }
    }
  return list;
}

uint16_t
WifiPhy::GetNMcs (void) const
{
  uint16_t numMcs = 0;
  for (const auto & phyEntity : m_phyEntities)
    {
      if (phyEntity.second->HandlesMcsModes ()) //to exclude non-MCS modes from search
        {
          numMcs += phyEntity.second->GetNumModes ();
        }
    }
  return numMcs;
}

std::list<WifiMode>
WifiPhy::GetMcsList (void) const
{
  std::list<WifiMode> list;
  for (const auto & phyEntity : m_phyEntities)
    {
      if (phyEntity.second->HandlesMcsModes ()) //to exclude non-MCS modes from search
        {
          for (const auto & mode : *(phyEntity.second))
            {
              list.emplace_back (mode);
            }
        }
    }
  return list;
}

std::list<WifiMode>
WifiPhy::GetMcsList (WifiModulationClass modulation) const
{
  std::list<WifiMode> list;
  auto phyEntity = m_phyEntities.find (modulation);
  if (phyEntity != m_phyEntities.end ())
    {
      if (phyEntity->second->HandlesMcsModes ()) //to exclude non-MCS modes from search
        {
          for (const auto & mode : *(phyEntity->second))
            {
              list.emplace_back (mode);
            }
        }
    }
  return list;
}

WifiMode
WifiPhy::GetMcs (WifiModulationClass modulation, uint8_t mcs) const
{
  NS_ASSERT_MSG (IsMcsSupported (modulation, mcs), "Unsupported MCS");
  return m_phyEntities.at (modulation)->GetMcs (mcs);
}

bool
WifiPhy::IsStateCcaBusy (void) const
{
  return m_state->IsStateCcaBusy ();
}

bool
WifiPhy::IsStateIdle (void) const
{
  return m_state->IsStateIdle ();
}

bool
WifiPhy::IsStateRx (void) const
{
  return m_state->IsStateRx ();
}

bool
WifiPhy::IsStateTx (void) const
{
  return m_state->IsStateTx ();
}

bool
WifiPhy::IsStateSwitching (void) const
{
  return m_state->IsStateSwitching ();
}

bool
WifiPhy::IsStateSleep (void) const
{
  return m_state->IsStateSleep ();
}

bool
WifiPhy::IsStateOff (void) const
{
  return m_state->IsStateOff ();
}

Time
WifiPhy::GetDelayUntilIdle (void)
{
  return m_state->GetDelayUntilIdle ();
}

Time
WifiPhy::GetLastRxStartTime (void) const
{
  return m_state->GetLastRxStartTime ();
}

Time
WifiPhy::GetLastRxEndTime (void) const
{
  return m_state->GetLastRxEndTime ();
}

void
WifiPhy::SwitchMaybeToCcaBusy (uint16_t channelWidth)
{
  NS_LOG_FUNCTION (this << channelWidth);
  //We are here because we have received the first bit of a packet and we are
  //not going to be able to synchronize on it
  //In this model, CCA becomes busy when the aggregation of all signals as
  //tracked by the InterferenceHelper class is higher than the CcaBusyThreshold
  Time delayUntilCcaEnd = m_interference.GetEnergyDuration (m_ccaEdThresholdW, GetPrimaryBand (channelWidth));
  if (!delayUntilCcaEnd.IsZero ())
    {
      NS_LOG_DEBUG ("Calling SwitchMaybeToCcaBusy for " << delayUntilCcaEnd.As (Time::S));
      m_state->SwitchMaybeToCcaBusy (delayUntilCcaEnd);
    }
}

void
WifiPhy::AbortCurrentReception (WifiPhyRxfailureReason reason)
{
  NS_LOG_FUNCTION (this << reason);
  if (reason != OBSS_PD_CCA_RESET || m_currentEvent) //Otherwise abort has already been called previously
    {
      for (auto & phyEntity : m_phyEntities)
        {
          phyEntity.second->CancelAllEvents ();
        }
      if (m_endPhyRxEvent.IsRunning ())
        {
          m_endPhyRxEvent.Cancel ();
        }
      m_interference.NotifyRxEnd (Simulator::Now ());
      if (!m_currentEvent)
        {
          return;
        }
      NotifyRxDrop (GetAddressedPsduInPpdu (m_currentEvent->GetPpdu ()), reason);
      if (reason == OBSS_PD_CCA_RESET)
        {
          m_state->SwitchFromRxAbort ();
        }
      for (auto it = m_currentPreambleEvents.begin (); it != m_currentPreambleEvents.end (); ++it)
        {
          if (it->second == m_currentEvent)
            {
              it = m_currentPreambleEvents.erase (it);
              break;
            }
        }
      m_currentEvent = 0;
    }
}

void
WifiPhy::ResetCca (bool powerRestricted, double txPowerMaxSiso, double txPowerMaxMimo)
{
  NS_LOG_FUNCTION (this << powerRestricted << txPowerMaxSiso << txPowerMaxMimo);
  // This method might be called multiple times when receiving TB PPDUs with a BSS color
  // different than the one of the receiver. The first time this method is called, the call
  // to AbortCurrentReception sets m_currentEvent to 0. Therefore, we need to check whether
  // m_currentEvent is not 0 before executing the instructions below.
  if (m_currentEvent != 0)
    {
      m_powerRestricted = powerRestricted;
      m_txPowerMaxSiso = txPowerMaxSiso;
      m_txPowerMaxMimo = txPowerMaxMimo;
      NS_ASSERT ((m_currentEvent->GetEndTime () - Simulator::Now ()).IsPositive ());
      Simulator::Schedule (m_currentEvent->GetEndTime () - Simulator::Now (), &WifiPhy::EndReceiveInterBss, this);
      Simulator::ScheduleNow (&WifiPhy::AbortCurrentReception, this, OBSS_PD_CCA_RESET); //finish processing field first
    }
}

double
WifiPhy::GetTxPowerForTransmission (Ptr<const WifiPpdu> ppdu) const
{
  NS_LOG_FUNCTION (this << m_powerRestricted << ppdu);
  const WifiTxVector& txVector = ppdu->GetTxVector ();
  // Get transmit power before antenna gain
  double txPowerDbm;
  if (!m_powerRestricted)
    {
      txPowerDbm = GetPowerDbm (txVector.GetTxPowerLevel ());
    }
  else
    {
      if (txVector.GetNssMax () > 1)
        {
          txPowerDbm = std::min (m_txPowerMaxMimo, GetPowerDbm (txVector.GetTxPowerLevel ()));
        }
      else
        {
          txPowerDbm = std::min (m_txPowerMaxSiso, GetPowerDbm (txVector.GetTxPowerLevel ()));
        }
    }

  //Apply power density constraint on EIRP
  uint16_t channelWidth = ppdu->GetTransmissionChannelWidth ();
  double txPowerDbmPerMhz = (txPowerDbm + GetTxGain ()) - RatioToDb (channelWidth); //account for antenna gain since EIRP
  NS_LOG_INFO ("txPowerDbm=" << txPowerDbm << " with txPowerDbmPerMhz=" << txPowerDbmPerMhz << " over " << channelWidth << " MHz");
  txPowerDbm = std::min (txPowerDbmPerMhz, m_powerDensityLimit) + RatioToDb (channelWidth);
  txPowerDbm -= GetTxGain (); //remove antenna gain since will be added right afterwards
  NS_LOG_INFO ("txPowerDbm=" << txPowerDbm << " after applying m_powerDensityLimit=" << m_powerDensityLimit);
  return txPowerDbm;
}

Ptr<const WifiPsdu>
WifiPhy::GetAddressedPsduInPpdu (Ptr<const WifiPpdu> ppdu) const
{
  //TODO: wrapper. See if still needed
  return GetPhyEntity (ppdu->GetModulation ())->GetAddressedPsduInPpdu (ppdu);
}

uint16_t
WifiPhy::GetMeasurementChannelWidth (const Ptr<const WifiPpdu> ppdu) const
{
  if (ppdu == nullptr)
    {
      // Here because PHY was not receiving anything (e.g. resuming from OFF) nor expecting anything (e.g. sleep)
      // nor processing a Wi-Fi signal.
      return GetChannelWidth () >= 40 ? 20 : GetChannelWidth ();
    }
  return GetPhyEntity (ppdu->GetModulation ())->GetMeasurementChannelWidth (ppdu);
}

WifiSpectrumBand
WifiPhy::GetBand (uint16_t /*bandWidth*/, uint8_t /*bandIndex*/)
{
  WifiSpectrumBand band;
  band.first = 0;
  band.second = 0;
  return band;
}

WifiSpectrumBand
WifiPhy::GetPrimaryBand (uint16_t bandWidth)
{
  if (GetChannelWidth () % 20 != 0)
    {
      return GetBand (bandWidth);
    }

  return GetBand (bandWidth, m_operatingChannel.GetPrimaryChannelIndex (bandWidth));
}

int64_t
WifiPhy::AssignStreams (int64_t stream)
{
  NS_LOG_FUNCTION (this << stream);
  int64_t currentStream = stream;
  m_random->SetStream (currentStream++);
  currentStream += m_interference.GetErrorRateModel ()->AssignStreams (currentStream);
  return (currentStream - stream);
}

std::ostream& operator<< (std::ostream& os, RxSignalInfo rxSignalInfo)
{
  os << "SNR:" << RatioToDb (rxSignalInfo.snr) << " dB"
     << ", RSSI:" << rxSignalInfo.rssi << " dBm";
  return os;
}

} //namespace ns3

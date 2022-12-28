/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2011 CTTC
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
 * Modified by Marco Miozzo <mmiozzo@cttc.es> (add data and ctrl diversity)
 */

#ifndef WIFI_SPECTRUM_SIGNAL_PARAMETERS_H
#define WIFI_SPECTRUM_SIGNAL_PARAMETERS_H

<<<<<<< HEAD
#include <ns3/spectrum-signal-parameters.h>

namespace ns3 {

class Packet;
=======
#include "ns3/spectrum-signal-parameters.h"

namespace ns3 {

class WifiPpdu;
>>>>>>> origin

/**
 * \ingroup wifi
 *
 * Signal parameters for wifi
 */
struct WifiSpectrumSignalParameters : public SpectrumSignalParameters
{

<<<<<<< HEAD
  // inherited from SpectrumSignalParameters
  virtual Ptr<SpectrumSignalParameters> Copy ();
=======
  Ptr<SpectrumSignalParameters> Copy () override;
>>>>>>> origin

  /**
   * default constructor
   */
  WifiSpectrumSignalParameters ();

  /**
   * copy constructor
<<<<<<< HEAD
   */
  WifiSpectrumSignalParameters (const WifiSpectrumSignalParameters& p);

  /**
   * The packet being transmitted with this signal
   */
  Ptr<Packet> packet;
=======
   *
   * \param p the wifi spectrum signal parameters
   */
  WifiSpectrumSignalParameters (const WifiSpectrumSignalParameters& p);

  Ptr<WifiPpdu> ppdu;                  ///< The PPDU being transmitted
>>>>>>> origin
};

}  // namespace ns3

#endif /* WIFI_SPECTRUM_SIGNAL_PARAMETERS_H */

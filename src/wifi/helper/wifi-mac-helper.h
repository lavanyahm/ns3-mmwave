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

#ifndef WIFI_MAC_HELPER_H
#define WIFI_MAC_HELPER_H

<<<<<<< HEAD
#include <string>
#include "ns3/attribute.h"
#include "ns3/object-factory.h"
=======
#include "ns3/object-factory.h"
#include "ns3/wifi-standards.h"
>>>>>>> origin

namespace ns3 {

class WifiMac;
<<<<<<< HEAD
=======
class NetDevice;
>>>>>>> origin

/**
 * \brief create MAC layers for a ns3::WifiNetDevice.
 *
 * This class can create MACs of type ns3::ApWifiMac, ns3::StaWifiMac and ns3::AdhocWifiMac.
<<<<<<< HEAD
 * Its purpose is to allow a WifiHelper to configure and install WifiMac objects on a collection 
 * of nodes. The WifiMac objects themselves are mainly composed of TxMiddle, RxMiddle, DcfManager, 
 * MacLow, WifiRemoteStationManager, MpduAggregator and MsduAggregartor objects, so this helper 
 * offers the opportunity to configure attribute values away from their default values, on a 
 * per-NodeContainer basis. By default, it creates an Adhoc MAC layer without QoS. Typically, 
 * it is used to set type and attribute values, then hand this object over to the WifiHelper that
 * finishes the job of installing.
 *
 * This class is a merge of two previous helpers (ns3::NqosWifiMacHelper and ns::3 QosWifiMacHelper)
 * that Mirko Banchi (mk.banchi@gmail.com) originally contributed.
 * It should now be used instead of those two deprecated helpers.
 *
=======
 * Its purpose is to allow a WifiHelper to configure and install WifiMac objects on a collection
 * of nodes. The WifiMac objects themselves are mainly composed of TxMiddle, RxMiddle, ChannelAccessManager,
 * FrameExchangeManager, WifiRemoteStationManager, MpduAggregator and MsduAggregartor objects, so this helper
 * offers the opportunity to configure attribute values away from their default values, on a
 * per-NodeContainer basis. By default, it creates an Adhoc MAC layer without QoS. Typically,
 * it is used to set type and attribute values, then hand this object over to the WifiHelper that
 * finishes the job of installing.
 *
>>>>>>> origin
 * This class may be further subclassed (WaveMacHelper is an example of this).
 *
 */
class WifiMacHelper
{
public:
  /**
   * Create a WifiMacHelper to make life easier for people who want to
   * work with Wifi MAC layers.
   */
  WifiMacHelper ();
  /**
   * Destroy a WifiMacHelper.
   */
  virtual ~WifiMacHelper ();

  /**
<<<<<<< HEAD
   * \param type the type of ns3::WifiMac to create.
   * Valid values of the type field must be a type subclassed from WifiMac.
   *
   * \param n0 the name of the attribute to set
   * \param v0 the value of the attribute to set
   * \param n1 the name of the attribute to set
   * \param v1 the value of the attribute to set
   * \param n2 the name of the attribute to set
   * \param v2 the value of the attribute to set
   * \param n3 the name of the attribute to set
   * \param v3 the value of the attribute to set
   * \param n4 the name of the attribute to set
   * \param v4 the value of the attribute to set
   * \param n5 the name of the attribute to set
   * \param v5 the value of the attribute to set
   * \param n6 the name of the attribute to set
   * \param v6 the value of the attribute to set
   * \param n7 the name of the attribute to set
   * \param v7 the value of the attribute to set
   * \param n8 the name of the attribute to set
   * \param v8 the value of the attribute to set
   * \param n9 the name of the attribute to set
   * \param v9 the value of the attribute to set
   * \param n10 the name of the attribute to set
   * \param v10 the value of the attribute to set
   *
   * All the attributes specified in this method should exist
   * in the requested mac.
   */
  virtual void SetType (std::string type,
                        std::string n0 = "", const AttributeValue &v0 = EmptyAttributeValue (),
                        std::string n1 = "", const AttributeValue &v1 = EmptyAttributeValue (),
                        std::string n2 = "", const AttributeValue &v2 = EmptyAttributeValue (),
                        std::string n3 = "", const AttributeValue &v3 = EmptyAttributeValue (),
                        std::string n4 = "", const AttributeValue &v4 = EmptyAttributeValue (),
                        std::string n5 = "", const AttributeValue &v5 = EmptyAttributeValue (),
                        std::string n6 = "", const AttributeValue &v6 = EmptyAttributeValue (),
                        std::string n7 = "", const AttributeValue &v7 = EmptyAttributeValue (),
                        std::string n8 = "", const AttributeValue &v8 = EmptyAttributeValue (),
                        std::string n9 = "", const AttributeValue &v9 = EmptyAttributeValue (),
                        std::string n10 = "", const AttributeValue &v10 = EmptyAttributeValue ());

  /**
=======
   * \tparam Args \deduced Template type parameter pack for the sequence of name-value pairs.
   * \param type the type of ns3::WifiMac to create.
   * \param args A sequence of name-value pairs of the attributes to set.
   *
   * All the attributes specified in this method should exist
   * in the requested MAC.
   */
  template <typename... Args>
  void SetType (std::string type, Args&&... args);

  /**
   * Helper function used to set the Protection Manager.
   *
   * \tparam Args \deduced Template type parameter pack for the sequence of name-value pairs.
   * \param type the type of Protection Manager
   * \param args A sequence of name-value pairs of the attributes to set.
   */
  template <typename... Args>
  void SetProtectionManager (std::string type, Args&&... args);

  /**
   * Helper function used to set the Acknowledgment Manager.
   *
   * \tparam Args \deduced Template type parameter pack for the sequence of name-value pairs.
   * \param type the type of Acknowledgment Manager
   * \param args A sequence of name-value pairs of the attributes to set.
   */
  template <typename... Args>
  void SetAckManager (std::string type, Args&&... args);

  /**
   * Helper function used to set the Multi User Scheduler that can be aggregated
   * to an HE AP's MAC.
   *
   * \tparam Args \deduced Template type parameter pack for the sequence of name-value pairs.
   * \param type the type of Multi User Scheduler
   * \param args A sequence of name-value pairs of the attributes to set.
   */
  template <typename... Args>
  void SetMultiUserScheduler (std::string type, Args&&... args);

  /**
   * \param device the device within which the MAC object will reside
   * \param standard the standard to configure during installation
>>>>>>> origin
   * \returns a new MAC object.
   *
   * This allows the ns3::WifiHelper class to create MAC objects from ns3::WifiHelper::Install.
   */
<<<<<<< HEAD
  virtual Ptr<WifiMac> Create (void) const;


protected:
  ObjectFactory m_mac;
=======
  virtual Ptr<WifiMac> Create (Ptr<NetDevice> device, WifiStandard standard) const;


protected:
  ObjectFactory m_mac;                ///< MAC object factory
  ObjectFactory m_protectionManager;  ///< Factory to create a protection manager
  ObjectFactory m_ackManager;         ///< Factory to create an acknowledgment manager
  ObjectFactory m_muScheduler;        ///< Multi-user Scheduler object factory
>>>>>>> origin
};

} // namespace ns3

<<<<<<< HEAD
=======

/***************************************************************
 *  Implementation of the templates declared above.
 ***************************************************************/

namespace ns3 {

template <typename... Args>
void
WifiMacHelper::SetType (std::string type, Args&&... args)
{
  m_mac.SetTypeId (type);
  m_mac.Set (args...);
}

template <typename... Args>
void
WifiMacHelper::SetProtectionManager (std::string type, Args&&... args)
{
  m_protectionManager.SetTypeId (type);
  m_protectionManager.Set (args...);
}

template <typename... Args>
void
WifiMacHelper::SetAckManager (std::string type, Args&&... args)
{
  m_ackManager.SetTypeId (type);
  m_ackManager.Set (args...);
}

template <typename... Args>
void
WifiMacHelper::SetMultiUserScheduler (std::string type, Args&&... args)
{
  m_muScheduler.SetTypeId (type);
  m_muScheduler.Set (args...);
}

} // namespace ns3

>>>>>>> origin
#endif /* WIFI_MAC_HELPER_H */

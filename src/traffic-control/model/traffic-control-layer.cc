/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2015 Natale Patriciello <natale.patriciello@gmail.com>
 *               2016 Stefano Avallone <stavallo@unina.it>
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
 */

#include "traffic-control-layer.h"
<<<<<<< HEAD
=======
#include "ns3/net-device-queue-interface.h"
>>>>>>> origin
#include "ns3/log.h"
#include "ns3/object-map.h"
#include "ns3/packet.h"
#include "ns3/socket.h"
#include "ns3/queue-disc.h"
<<<<<<< HEAD
=======
#include <tuple>
>>>>>>> origin

namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("TrafficControlLayer");

NS_OBJECT_ENSURE_REGISTERED (TrafficControlLayer);

TypeId
TrafficControlLayer::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::TrafficControlLayer")
    .SetParent<Object> ()
    .SetGroupName ("TrafficControl")
    .AddConstructor<TrafficControlLayer> ()
    .AddAttribute ("RootQueueDiscList", "The list of root queue discs associated to this Traffic Control layer.",
                   ObjectMapValue (),
                   MakeObjectMapAccessor (&TrafficControlLayer::GetNDevices,
                                          &TrafficControlLayer::GetRootQueueDiscOnDeviceByIndex),
                   MakeObjectMapChecker<QueueDisc> ())
  ;
  return tid;
}

TypeId
TrafficControlLayer::GetInstanceTypeId (void) const
{
  return GetTypeId ();
}

TrafficControlLayer::TrafficControlLayer ()
  : Object ()
{
<<<<<<< HEAD
  NS_LOG_FUNCTION_NOARGS ();
=======
  NS_LOG_FUNCTION (this);
}

TrafficControlLayer::~TrafficControlLayer ()
{
  NS_LOG_FUNCTION (this);
>>>>>>> origin
}

void
TrafficControlLayer::DoDispose (void)
{
  NS_LOG_FUNCTION (this);
  m_node = 0;
  m_handlers.clear ();
  m_netDevices.clear ();
  Object::DoDispose ();
}

void
TrafficControlLayer::DoInitialize (void)
{
  NS_LOG_FUNCTION (this);
<<<<<<< HEAD
  std::map<Ptr<NetDevice>, NetDeviceInfo>::iterator ndi;
  for (ndi = m_netDevices.begin (); ndi != m_netDevices.end (); ndi++)
    {
      if (ndi->second.rootQueueDisc)
        {
          Ptr<NetDeviceQueueInterface> devQueueIface = ndi->second.ndqi;
          NS_ASSERT (devQueueIface);

          // set the wake callbacks on netdevice queues
           if (ndi->second.rootQueueDisc->GetWakeMode () == QueueDisc::WAKE_ROOT)
            {
              for (uint32_t i = 0; i < devQueueIface->GetNTxQueues (); i++)
                {
                  devQueueIface->GetTxQueue (i)->SetWakeCallback (MakeCallback (&QueueDisc::Run, ndi->second.rootQueueDisc));
                  ndi->second.queueDiscsToWake.push_back (ndi->second.rootQueueDisc);
                }
            }
          else if (ndi->second.rootQueueDisc->GetWakeMode () == QueueDisc::WAKE_CHILD)
            {
              NS_ASSERT_MSG (ndi->second.rootQueueDisc->GetNQueueDiscClasses () == devQueueIface->GetNTxQueues (),
                             "The number of child queue discs does not match the number of netdevice queues");
              for (uint32_t i = 0; i < devQueueIface->GetNTxQueues (); i++)
                {
                  devQueueIface->GetTxQueue (i)->SetWakeCallback (MakeCallback (&QueueDisc::Run,
                                                                  ndi->second.rootQueueDisc->GetQueueDiscClass (i)->GetQueueDisc ()));
                  ndi->second.queueDiscsToWake.push_back (ndi->second.rootQueueDisc->GetQueueDiscClass (i)->GetQueueDisc ());
                }
            }

          // initialize the queue disc
          ndi->second.rootQueueDisc->Initialize ();
        }
    }
=======

  ScanDevices ();

  // initialize the root queue discs
  for (auto& ndi : m_netDevices)
    {
      if (ndi.second.m_rootQueueDisc)
        {
          ndi.second.m_rootQueueDisc->Initialize ();
        }
    }

>>>>>>> origin
  Object::DoInitialize ();
}

void
<<<<<<< HEAD
TrafficControlLayer::SetupDevice (Ptr<NetDevice> device)
{
  NS_LOG_FUNCTION (this << device);

  // ensure this setup is done just once. SetupDevice is called by Ipv4L3Protocol
  // and Ipv6L3Protocol when they add an interface, thus it might be called twice
  // in case of dual stack nodes. Also, SetupDevice might be called twice if the
  // tc helper is invoked (to install a queue disc) before the creation of the
  // Ipv{4,6}Interface, since SetRootQueueDiscOnDevice calls SetupDevice
  if (device->GetObject<NetDeviceQueueInterface> ())
    {
      NS_LOG_DEBUG ("The setup for this device has been already done.");
      return;
    }

  // create a NetDeviceQueueInterface object and aggregate it to the device
  Ptr<NetDeviceQueueInterface> devQueueIface = CreateObject<NetDeviceQueueInterface> ();
  device->AggregateObject (devQueueIface);

  // multi-queue devices must set the number of transmission queues in their
  // NotifyNewAggregate method. Since we have just aggregated the netdevice
  // queue interface to the device, we can create the transmission queues
  devQueueIface->CreateTxQueues ();

  // devices can set a select queue callback in their NotifyNewAggregate method
  SelectQueueCallback cb = devQueueIface->GetSelectQueueCallback ();

  // create an entry in the m_netDevices map for this device
  NS_ASSERT_MSG (m_netDevices.find (device) == m_netDevices.end (), "This is a bug,"
                 << "  SetupDevice only can insert an entry in the m_netDevices map");

  NetDeviceInfo entry = {0, devQueueIface, QueueDiscVector (), cb};
  m_netDevices[device] = entry;
}

void
=======
>>>>>>> origin
TrafficControlLayer::RegisterProtocolHandler (Node::ProtocolHandler handler,
                                              uint16_t protocolType, Ptr<NetDevice> device)
{
  NS_LOG_FUNCTION (this << protocolType << device);

  struct ProtocolHandlerEntry entry;
  entry.handler = handler;
  entry.protocol = protocolType;
  entry.device = device;
  entry.promiscuous = false;

  m_handlers.push_back (entry);

  NS_LOG_DEBUG ("Handler for NetDevice: " << device << " registered for protocol " <<
                protocolType << ".");
}

void
<<<<<<< HEAD
=======
TrafficControlLayer::ScanDevices (void)
{
  NS_LOG_FUNCTION (this);

  NS_ASSERT_MSG (m_node, "Cannot run ScanDevices without an aggregated node");

  NS_LOG_DEBUG ("Scanning devices on node " << m_node->GetId ());
  for (uint32_t i = 0; i < m_node->GetNDevices (); i++)
    {
      NS_LOG_DEBUG ("Scanning devices on node " << m_node->GetId ());
      Ptr<NetDevice> dev = m_node->GetDevice (i);
      NS_LOG_DEBUG ("Checking device " << i << " with pointer " << dev << " of type " << dev->GetInstanceTypeId ().GetName ());

      // note: there may be no NetDeviceQueueInterface aggregated to the device
      Ptr<NetDeviceQueueInterface> ndqi = dev->GetObject<NetDeviceQueueInterface> ();
      NS_LOG_DEBUG ("Pointer to NetDeviceQueueInterface: " << ndqi);

      std::map<Ptr<NetDevice>, NetDeviceInfo>::iterator ndi = m_netDevices.find (dev);

      if (ndi != m_netDevices.end ())
        {
          NS_LOG_DEBUG ("Device entry found; installing NetDeviceQueueInterface pointer " << ndqi << " to internal map");
          ndi->second.m_ndqi = ndqi;
        }
      else if (ndqi)
      // if no entry for the device is found, it means that no queue disc has been
      // installed. Nonetheless, create an entry for the device and store a pointer
      // to the NetDeviceQueueInterface object if the latter is not null, because
      // the Traffic Control layer checks whether the device queue is stopped even
      // when there is no queue disc.
        {
          NS_LOG_DEBUG ("No device entry found; create entry for device and store pointer to NetDeviceQueueInterface: " << ndqi);
          m_netDevices[dev] = {nullptr, ndqi, QueueDiscVector ()};
          ndi = m_netDevices.find (dev);
        }

      // if a queue disc is installed, set the wake callbacks on netdevice queues
      if (ndi != m_netDevices.end () && ndi->second.m_rootQueueDisc)
        {
          NS_LOG_DEBUG ("Setting the wake callbacks on NetDevice queues");
          ndi->second.m_queueDiscsToWake.clear ();

          if (ndqi)
            {
              for (uint16_t i = 0; i < ndqi->GetNTxQueues (); i++)
                {
                  Ptr<QueueDisc> qd;

                  if (ndi->second.m_rootQueueDisc->GetWakeMode () == QueueDisc::WAKE_ROOT)
                    {
                      qd = ndi->second.m_rootQueueDisc;
                    }
                  else if (ndi->second.m_rootQueueDisc->GetWakeMode () == QueueDisc::WAKE_CHILD)
                    {
                      NS_ABORT_MSG_IF (ndi->second.m_rootQueueDisc->GetNQueueDiscClasses () != ndqi->GetNTxQueues (),
                                      "The number of child queue discs does not match the number of netdevice queues");

                      qd = ndi->second.m_rootQueueDisc->GetQueueDiscClass (i)->GetQueueDisc ();
                    }
                  else
                    {
                      NS_ABORT_MSG ("Invalid wake mode");
                    }

                  ndqi->GetTxQueue (i)->SetWakeCallback (MakeCallback (&QueueDisc::Run, qd));
                  ndi->second.m_queueDiscsToWake.push_back (qd);
                }
            }
          else
            {
              ndi->second.m_queueDiscsToWake.push_back (ndi->second.m_rootQueueDisc);
            }

          // set the NetDeviceQueueInterface object and the SendCallback on the queue discs
          // into which packets are enqueued and dequeued by calling Run
          for (auto& q : ndi->second.m_queueDiscsToWake)
            {
              q->SetNetDeviceQueueInterface (ndqi);
              q->SetSendCallback ([dev] (Ptr<QueueDiscItem> item)
                                  { dev->Send (item->GetPacket (), item->GetAddress (), item->GetProtocol ()); });
            }
        }
    }
}

void
>>>>>>> origin
TrafficControlLayer::SetRootQueueDiscOnDevice (Ptr<NetDevice> device, Ptr<QueueDisc> qDisc)
{
  NS_LOG_FUNCTION (this << device << qDisc);

  std::map<Ptr<NetDevice>, NetDeviceInfo>::iterator ndi = m_netDevices.find (device);

  if (ndi == m_netDevices.end ())
    {
<<<<<<< HEAD
      // SetupDevice has not been called yet. This may happen when the tc helper is
      // invoked (to install a queue disc) before the creation of the Ipv{4,6}Interface.
      // Since queue discs require that a netdevice queue interface is aggregated
      // to the device, call SetupDevice
      SetupDevice (device);
      ndi = m_netDevices.find (device);
      NS_ASSERT (ndi != m_netDevices.end ());
    }

  NS_ASSERT_MSG (ndi->second.rootQueueDisc == 0, "Cannot install a root queue disc on a "
                  << "device already having one. Delete the existing queue disc first.");
  ndi->second.rootQueueDisc = qDisc;
=======
      // No entry found for this device. Create one.
      m_netDevices[device] = {qDisc, nullptr, QueueDiscVector ()};
    }
  else
    {
      NS_ABORT_MSG_IF (ndi->second.m_rootQueueDisc,
                       "Cannot install a root queue disc on a device already having one. "
                       "Delete the existing queue disc first.");

      ndi->second.m_rootQueueDisc = qDisc;
    }
>>>>>>> origin
}

Ptr<QueueDisc>
TrafficControlLayer::GetRootQueueDiscOnDevice (Ptr<NetDevice> device) const
{
  NS_LOG_FUNCTION (this << device);

  std::map<Ptr<NetDevice>, NetDeviceInfo>::const_iterator ndi = m_netDevices.find (device);

  if (ndi == m_netDevices.end ())
    {
      return 0;
    }
<<<<<<< HEAD
  return ndi->second.rootQueueDisc;
=======
  return ndi->second.m_rootQueueDisc;
>>>>>>> origin
}

Ptr<QueueDisc>
TrafficControlLayer::GetRootQueueDiscOnDeviceByIndex (uint32_t index) const
{
  NS_LOG_FUNCTION (this << index);
  return GetRootQueueDiscOnDevice (m_node->GetDevice (index));
}

void
TrafficControlLayer::DeleteRootQueueDiscOnDevice (Ptr<NetDevice> device)
{
  NS_LOG_FUNCTION (this << device);

  std::map<Ptr<NetDevice>, NetDeviceInfo>::iterator ndi = m_netDevices.find (device);

<<<<<<< HEAD
  NS_ASSERT_MSG (ndi != m_netDevices.end () && ndi->second.rootQueueDisc != 0, "No root queue disc"
                 << " installed on device " << device);

  // remove the root queue disc
  ndi->second.rootQueueDisc = 0;
  ndi->second.queueDiscsToWake.clear ();
=======
  NS_ASSERT_MSG (ndi != m_netDevices.end () && ndi->second.m_rootQueueDisc != 0,
                 "No root queue disc installed on device " << device);

  // remove the root queue disc
  ndi->second.m_rootQueueDisc = 0;
  for (auto& q : ndi->second.m_queueDiscsToWake)
    {
      q->SetNetDeviceQueueInterface (nullptr);
      q->SetSendCallback (nullptr);
    }
  ndi->second.m_queueDiscsToWake.clear ();

  Ptr<NetDeviceQueueInterface> ndqi = ndi->second.m_ndqi;
  if (ndqi)
    {
      // remove configured callbacks, if any
      for (uint16_t i = 0; i < ndqi->GetNTxQueues (); i++)
        {
          ndqi->GetTxQueue (i)->SetWakeCallback (MakeNullCallback <void> ());
        }
    }
  else
    {
      // remove the empty entry
      m_netDevices.erase (ndi);
    }
>>>>>>> origin
}

void
TrafficControlLayer::SetNode (Ptr<Node> node)
{
  NS_LOG_FUNCTION (this << node);
  m_node = node;
}

void
TrafficControlLayer::NotifyNewAggregate ()
{
  NS_LOG_FUNCTION (this);
  if (m_node == 0)
    {
      Ptr<Node> node = this->GetObject<Node> ();
      //verify that it's a valid node and that
      //the node was not set before
      if (node != 0)
        {
          this->SetNode (node);
        }
    }
  Object::NotifyNewAggregate ();
}

uint32_t
TrafficControlLayer::GetNDevices (void) const
{
  return m_node->GetNDevices ();
}


void
TrafficControlLayer::Receive (Ptr<NetDevice> device, Ptr<const Packet> p,
                              uint16_t protocol, const Address &from, const Address &to,
                              NetDevice::PacketType packetType)
{
  NS_LOG_FUNCTION (this << device << p << protocol << from << to << packetType);

  bool found = false;

  for (ProtocolHandlerList::iterator i = m_handlers.begin ();
       i != m_handlers.end (); i++)
    {
      if (i->device == 0
          || (i->device != 0 && i->device == device))
        {
          if (i->protocol == 0
              || i->protocol == protocol)
            {
              NS_LOG_DEBUG ("Found handler for packet " << p << ", protocol " <<
                            protocol << " and NetDevice " << device <<
                            ". Send packet up");
              i->handler (device, p, protocol, from, to, packetType);
              found = true;
            }
        }
    }

<<<<<<< HEAD
  if (! found)
    {
      NS_FATAL_ERROR ("Handler for protocol " << p << " and device " << device <<
                      " not found. It isn't forwarded up; it dies here.");
    }
=======
  NS_ABORT_MSG_IF (!found, "Handler for protocol " << p << " and device " << device <<
                           " not found. It isn't forwarded up; it dies here.");
>>>>>>> origin
}

void
TrafficControlLayer::Send (Ptr<NetDevice> device, Ptr<QueueDiscItem> item)
{
  NS_LOG_FUNCTION (this << device << item);

  NS_LOG_DEBUG ("Send packet to device " << device << " protocol number " <<
                item->GetProtocol ());

<<<<<<< HEAD
  std::map<Ptr<NetDevice>, NetDeviceInfo>::iterator ndi = m_netDevices.find (device);
  NS_ASSERT (ndi != m_netDevices.end ());
  Ptr<NetDeviceQueueInterface> devQueueIface = ndi->second.ndqi;
  NS_ASSERT (devQueueIface);

  // determine the transmission queue of the device where the packet will be enqueued
  uint8_t txq = 0;
  if (devQueueIface->GetNTxQueues () > 1)
    {
      if (!ndi->second.selectQueueCallback.IsNull ())
        {
          txq = ndi->second.selectQueueCallback (item);
        }
=======
  Ptr<NetDeviceQueueInterface> devQueueIface;
  std::map<Ptr<NetDevice>, NetDeviceInfo>::iterator ndi = m_netDevices.find (device);

  if (ndi != m_netDevices.end ())
    {
      devQueueIface = ndi->second.m_ndqi;
    }

  // determine the transmission queue of the device where the packet will be enqueued
  std::size_t txq = 0;
  if (devQueueIface && devQueueIface->GetNTxQueues () > 1)
    {
      txq = devQueueIface->GetSelectQueueCallback () (item);
>>>>>>> origin
      // otherwise, Linux determines the queue index by using a hash function
      // and associates such index to the socket which the packet belongs to,
      // so that subsequent packets of the same socket will be mapped to the
      // same tx queue (__netdev_pick_tx function in net/core/dev.c). It is
      // pointless to implement this in ns-3 because currently the multi-queue
      // devices provide a select queue callback
    }

<<<<<<< HEAD
  NS_ASSERT (txq < devQueueIface->GetNTxQueues ());

  if (ndi->second.rootQueueDisc == 0)
    {
      // The device has no attached queue disc, thus add the header to the packet and
      // send it directly to the device if the selected queue is not stopped
      if (!devQueueIface->GetTxQueue (txq)->IsStopped ())
        {
          item->AddHeader ();
          // a single queue device makes no use of the priority tag
          if (devQueueIface->GetNTxQueues () == 1)
=======
  NS_ASSERT (!devQueueIface || txq < devQueueIface->GetNTxQueues ());

  if (ndi == m_netDevices.end () || ndi->second.m_rootQueueDisc == 0)
    {
      // The device has no attached queue disc, thus add the header to the packet and
      // send it directly to the device if the selected queue is not stopped
      if (!devQueueIface || !devQueueIface->GetTxQueue (txq)->IsStopped ())
        {
          item->AddHeader ();
          // a single queue device makes no use of the priority tag
          if (!devQueueIface || devQueueIface->GetNTxQueues () == 1)
>>>>>>> origin
            {
              SocketPriorityTag priorityTag;
              item->GetPacket ()->RemovePacketTag (priorityTag);
            }
          device->Send (item->GetPacket (), item->GetAddress (), item->GetProtocol ());
        }
    }
  else
    {
      // Enqueue the packet in the queue disc associated with the netdevice queue
      // selected for the packet and try to dequeue packets from such queue disc
      item->SetTxQueueIndex (txq);

<<<<<<< HEAD
      Ptr<QueueDisc> qDisc = ndi->second.queueDiscsToWake[txq];
=======
      Ptr<QueueDisc> qDisc = ndi->second.m_queueDiscsToWake[txq];
>>>>>>> origin
      NS_ASSERT (qDisc);
      qDisc->Enqueue (item);
      qDisc->Run ();
    }
}

} // namespace ns3

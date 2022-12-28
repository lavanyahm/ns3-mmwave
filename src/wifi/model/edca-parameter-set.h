/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2016 Sébastien Deronne
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

#ifndef EDCA_PARAMETER_SET_H
#define EDCA_PARAMETER_SET_H

<<<<<<< HEAD
#include <stdint.h>
#include <ostream>
#include "ns3/buffer.h"
#include "ns3/wifi-information-element.h"
=======
#include "wifi-information-element.h"
>>>>>>> origin

namespace ns3 {

/**
 * \brief The EDCA Parameter Set
 * \ingroup wifi
 *
 * This class knows how to serialise and deserialise the EDCA Parameter Set.
 */
class EdcaParameterSet : public WifiInformationElement
{
public:
  EdcaParameterSet ();
<<<<<<< HEAD
  void SetQosSupported (uint8_t qosSupported);
  
=======

  // Implementations of pure virtual methods of WifiInformationElement
  WifiInformationElementId ElementId () const override;
  uint8_t GetInformationFieldSize () const override;
  void SerializeInformationField (Buffer::Iterator start) const override;
  uint8_t DeserializeInformationField (Buffer::Iterator start, uint8_t length) override;
  /* This information element is a bit special in that it is only
     included if the STA is a QoS STA. To support this we
     override the Serialize and GetSerializedSize methods of
     WifiInformationElement. */
  Buffer::Iterator Serialize (Buffer::Iterator start) const override;
  uint16_t GetSerializedSize () const override;

  /**
   * Set QOS supported function
   * \param qosSupported the QOS supported indicator
   */
  void SetQosSupported (uint8_t qosSupported);
  /**
   * Is QOS supported function
   * \returns the is QOS supported indicator
   */
  uint8_t IsQosSupported (void) const;

>>>>>>> origin
  /**
   * Set the QoS Info field in the EdcaParameterSet information element.
   *
   * \param qosInfo the QoS Info field in the EdcaParameterSet information element
   */
  void SetQosInfo (uint8_t qosInfo);
  /**
   * Set the AC_BE AIFSN field in the EdcaParameterSet information element.
   *
   * \param aifsn the AC_BE AIFSN field in the EdcaParameterSet information element
   */
  void SetBeAifsn (uint8_t aifsn);
  /**
<<<<<<< HEAD
   * Set the AC_BE ACM field in the EdcaParameterSet information element.
   *
   * \param aifsn the AC_BE ACM field in the EdcaParameterSet information element
   */
  void SetBeAcm (uint8_t acm);
  /**
   * Set the AC_BE ACI field in the EdcaParameterSet information element.
   *
   * \param aifsn the AC_BE ACI field in the EdcaParameterSet information element
=======
   * Set the AC_BE ACI field in the EdcaParameterSet information element.
   *
   * \param aci the AC_BE ACI field in the EdcaParameterSet information element
>>>>>>> origin
   */
  void SetBeAci (uint8_t aci);
  /**
   * Set the AC_BE CWmin field in the EdcaParameterSet information element.
   *
<<<<<<< HEAD
   * \param aifsn the AC_BE CWmin field in the EdcaParameterSet information element
   */
  void SetBeCWmin (uint8_t cwMin);
  /**
   * Set the AC_BE CWmax field in the EdcaParameterSet information element.
   *
   * \param aifsn the AC_BE CWmax field in the EdcaParameterSet information element
   */
  void SetBeCWmax (uint8_t cwMax);
  /**
   * Set the AC_BE TXOP Limit field in the EdcaParameterSet information element.
   *
   * \param aifsn the AC_BE TXOP Limit field in the EdcaParameterSet information element
   */
  void SetBeTXOPLimit (uint16_t txop);
=======
   * \param cwMin the AC_BE CWmin field in the EdcaParameterSet information element
   */
  void SetBeCWmin (uint32_t cwMin);
  /**
   * Set the AC_BE CWmax field in the EdcaParameterSet information element.
   *
   * \param cwMax the AC_BE CWmax field in the EdcaParameterSet information element
   */
  void SetBeCWmax (uint32_t cwMax);
  /**
   * Set the AC_BE TXOP Limit field in the EdcaParameterSet information element.
   *
   * \param txop the AC_BE TXOP Limit field in the EdcaParameterSet information element
   */
  void SetBeTxopLimit (uint16_t txop);
>>>>>>> origin
  /**
   * Set the AC_BK AIFSN field in the EdcaParameterSet information element.
   *
   * \param aifsn the AC_BB AIFSN field in the EdcaParameterSet information element
   */
  void SetBkAifsn (uint8_t aifsn);
  /**
<<<<<<< HEAD
   * Set the AC_BK ACM field in the EdcaParameterSet information element.
   *
   * \param aifsn the AC_BK ACM field in the EdcaParameterSet information element
   */
  void SetBkAcm (uint8_t acm);
  /**
   * Set the AC_BK ACI field in the EdcaParameterSet information element.
   *
   * \param aifsn the AC_BK ACI field in the EdcaParameterSet information element
=======
   * Set the AC_BK ACI field in the EdcaParameterSet information element.
   *
   * \param aci the AC_BK ACI field in the EdcaParameterSet information element
>>>>>>> origin
   */
  void SetBkAci (uint8_t aci);
  /**
   * Set the AC_BK CWmin field in the EdcaParameterSet information element.
   *
<<<<<<< HEAD
   * \param aifsn the AC_BK CWmin field in the EdcaParameterSet information element
   */
  void SetBkCWmin (uint8_t cwMin);
  /**
   * Set the AC_BK CWmax field in the EdcaParameterSet information element.
   *
   * \param aifsn the AC_BK CWmax field in the EdcaParameterSet information element
   */
  void SetBkCWmax (uint8_t cwMax);
  /**
   * Set the AC_BK TXOP Limit field in the EdcaParameterSet information element.
   *
   * \param aifsn the AC_BK TXOP Limit field in the EdcaParameterSet information element
   */
  void SetBkTXOPLimit (uint16_t txop);
=======
   * \param cwMin the AC_BK CWmin field in the EdcaParameterSet information element
   */
  void SetBkCWmin (uint32_t cwMin);
  /**
   * Set the AC_BK CWmax field in the EdcaParameterSet information element.
   *
   * \param cwMax the AC_BK CWmax field in the EdcaParameterSet information element
   */
  void SetBkCWmax (uint32_t cwMax);
  /**
   * Set the AC_BK TXOP Limit field in the EdcaParameterSet information element.
   *
   * \param txop the AC_BK TXOP Limit field in the EdcaParameterSet information element
   */
  void SetBkTxopLimit (uint16_t txop);
>>>>>>> origin
  /**
   * Set the AC_VI AIFSN field in the EdcaParameterSet information element.
   *
   * \param aifsn the AC_VI AIFSN field in the EdcaParameterSet information element
   */
  void SetViAifsn (uint8_t aifsn);
  /**
<<<<<<< HEAD
   * Set the AC_VI ACM field in the EdcaParameterSet information element.
   *
   * \param aifsn the AC_VI ACM field in the EdcaParameterSet information element
   */
  void SetViAcm (uint8_t acm);
  /**
   * Set the AC_VI ACI field in the EdcaParameterSet information element.
   *
   * \param aifsn the AC_VI ACI field in the EdcaParameterSet information element
=======
   * Set the AC_VI ACI field in the EdcaParameterSet information element.
   *
   * \param aci the AC_VI ACI field in the EdcaParameterSet information element
>>>>>>> origin
   */
  void SetViAci (uint8_t aci);
  /**
   * Set the AC_VI CWmin field in the EdcaParameterSet information element.
   *
<<<<<<< HEAD
   * \param aifsn the AC_VI CWmin field in the EdcaParameterSet information element
   */
  void SetViCWmin (uint8_t cwMin);
  /**
   * Set the AC_VI CWmax field in the EdcaParameterSet information element.
   *
   * \param aifsn the AC_VI CWmax field in the EdcaParameterSet information element
   */
  void SetViCWmax (uint8_t cwMax);
  /**
   * Set the AC_VI TXOP Limit field in the EdcaParameterSet information element.
   *
   * \param aifsn the AC_VI TXOP Limit field in the EdcaParameterSet information element
   */
  void SetViTXOPLimit (uint16_t txop);
=======
   * \param cwMin the AC_VI CWmin field in the EdcaParameterSet information element
   */
  void SetViCWmin (uint32_t cwMin);
  /**
   * Set the AC_VI CWmax field in the EdcaParameterSet information element.
   *
   * \param cwMax the AC_VI CWmax field in the EdcaParameterSet information element
   */
  void SetViCWmax (uint32_t cwMax);
  /**
   * Set the AC_VI TXOP Limit field in the EdcaParameterSet information element.
   *
   * \param txop the AC_VI TXOP Limit field in the EdcaParameterSet information element
   */
  void SetViTxopLimit (uint16_t txop);
>>>>>>> origin
  /**
   * Set the AC_VO AIFSN field in the EdcaParameterSet information element.
   *
   * \param aifsn the AC_VO AIFSN field in the EdcaParameterSet information element
   */
  void SetVoAifsn (uint8_t aifsn);
  /**
<<<<<<< HEAD
   * Set the AC_VO ACM field in the EdcaParameterSet information element.
   *
   * \param aifsn the AC_VO ACM field in the EdcaParameterSet information element
   */
  void SetVoAcm (uint8_t acm);
  /**
   * Set the AC_VO ACI field in the EdcaParameterSet information element.
   *
   * \param aifsn the AC_VO ACI field in the EdcaParameterSet information element
=======
   * Set the AC_VO ACI field in the EdcaParameterSet information element.
   *
   * \param aci the AC_VO ACI field in the EdcaParameterSet information element
>>>>>>> origin
   */
  void SetVoAci (uint8_t aci);
  /**
   * Set the AC_VO CWmin field in the EdcaParameterSet information element.
   *
<<<<<<< HEAD
   * \param aifsn the AC_VO CWmin field in the EdcaParameterSet information element
   */
  void SetVoCWmin (uint8_t cwMin);
  /**
   * Set the AC_VO CWmax field in the EdcaParameterSet information element.
   *
   * \param aifsn the AC_VO CWmax field in the EdcaParameterSet information element
   */
  void SetVoCWmax (uint8_t cwMax);
  /**
   * Set the AC_VO TXOP Limit field in the EdcaParameterSet information element.
   *
   * \param aifsn the AC_VO TXOP Limit field in the EdcaParameterSet information element
   */
  void SetVoTXOPLimit (uint16_t txop);
  
  /*
=======
   * \param cwMin the AC_VO CWmin field in the EdcaParameterSet information element
   */
  void SetVoCWmin (uint32_t cwMin);
  /**
   * Set the AC_VO CWmax field in the EdcaParameterSet information element.
   *
   * \param cwMax the AC_VO CWmax field in the EdcaParameterSet information element
   */
  void SetVoCWmax (uint32_t cwMax);
  /**
   * Set the AC_VO TXOP Limit field in the EdcaParameterSet information element.
   *
   * \param txop the AC_VO TXOP Limit field in the EdcaParameterSet information element
   */
  void SetVoTxopLimit (uint16_t txop);

  /**
>>>>>>> origin
   * Return the QoS Info field in the EdcaParameterSet information element.
   *
   * \return the QoS Info field in the EdcaParameterSet information element
   */
  uint8_t GetQosInfo (void) const;
<<<<<<< HEAD
  /*
=======
  /**
>>>>>>> origin
   * Return the AC_BE AIFSN field in the EdcaParameterSet information element.
   *
   * \return the AC_BE AIFSN field in the EdcaParameterSet information element
   */
  uint8_t GetBeAifsn (void) const;
<<<<<<< HEAD
  /*
   * Return the AC_BE ACM field in the EdcaParameterSet information element.
   *
   * \return the AC_BE ACM field in the EdcaParameterSet information element
   */
  uint8_t GetBeAcm (void) const;
  /*
   * Return the AC_BE ACI field in the EdcaParameterSet information element.
   *
   * \return the AC_BE ACI field in the EdcaParameterSet information element
   */
  uint8_t GetBeAci (void) const;
  /*
=======
  /**
>>>>>>> origin
   * Return the AC_BE CWmin field in the EdcaParameterSet information element.
   *
   * \return the AC_BE CWmin field in the EdcaParameterSet information element
   */
<<<<<<< HEAD
  uint8_t GetBeCWmin (void) const;
  /*
=======
  uint32_t GetBeCWmin (void) const;
  /**
>>>>>>> origin
   * Return the AC_BE CWmax field in the EdcaParameterSet information element.
   *
   * \return the AC_BE CWmax field in the EdcaParameterSet information element
   */
<<<<<<< HEAD
  uint8_t GetBeCWmax (void) const;
  /*
=======
  uint32_t GetBeCWmax (void) const;
  /**
>>>>>>> origin
   * Return the AC_BE TXOP Limit field in the EdcaParameterSet information element.
   *
   * \return the AC_BE TXOP Limit field in the EdcaParameterSet information element
   */
<<<<<<< HEAD
  uint16_t GetBeTXOPLimit (void) const;
  /*
=======
  uint16_t GetBeTxopLimit (void) const;
  /**
>>>>>>> origin
   * Return the AC_BK AIFSN field in the EdcaParameterSet information element.
   *
   * \return the AC_BK AIFSN field in the EdcaParameterSet information element
   */
  uint8_t GetBkAifsn (void) const;
<<<<<<< HEAD
  /*
   * Return the AC_BK ACM field in the EdcaParameterSet information element.
   *
   * \return the AC_BK ACM field in the EdcaParameterSet information element
   */
  uint8_t GetBkAcm (void) const;
  /*
   * Return the AC_BK ACI field in the EdcaParameterSet information element.
   *
   * \return the AC_BK ACI field in the EdcaParameterSet information element
   */
  uint8_t GetBkAci (void) const;
  /*
=======
  /**
>>>>>>> origin
   * Return the AC_BK CWmin field in the EdcaParameterSet information element.
   *
   * \return the AC_BK CWmin field in the EdcaParameterSet information element
   */
<<<<<<< HEAD
  uint8_t GetBkCWmin (void) const;
  /*
=======
  uint32_t GetBkCWmin (void) const;
  /**
>>>>>>> origin
   * Return the AC_BK CWmax field in the EdcaParameterSet information element.
   *
   * \return the AC_BK CWmax field in the EdcaParameterSet information element
   */
<<<<<<< HEAD
  uint8_t GetBkCWmax (void) const;
  /*
=======
  uint32_t GetBkCWmax (void) const;
  /**
>>>>>>> origin
   * Return the AC_BK TXOP Limit field in the EdcaParameterSet information element.
   *
   * \return the AC_BK TXOP Limit field in the EdcaParameterSet information element
   */
<<<<<<< HEAD
  uint16_t GetBkTXOPLimit (void) const;
  /*
=======
  uint16_t GetBkTxopLimit (void) const;
  /**
>>>>>>> origin
   * Return the AC_VI AIFSN field in the EdcaParameterSet information element.
   *
   * \return the AC_VI AIFSN field in the EdcaParameterSet information element
   */
  uint8_t GetViAifsn (void) const;
<<<<<<< HEAD
  /*
   * Return the AC_VI ACM field in the EdcaParameterSet information element.
   *
   * \return the AC_VI ACM field in the EdcaParameterSet information element
   */
  uint8_t GetViAcm (void) const;
  /*
   * Return the AC_VI ACI field in the EdcaParameterSet information element.
   *
   * \return the AC_VI ACI field in the EdcaParameterSet information element
   */
  uint8_t GetViAci (void) const;
  /*
=======
  /**
>>>>>>> origin
   * Return the AC_VI CWmin field in the EdcaParameterSet information element.
   *
   * \return the AC_VI CWmin field in the EdcaParameterSet information element
   */
<<<<<<< HEAD
  uint8_t GetViCWmin (void) const;
  /*
=======
  uint32_t GetViCWmin (void) const;
  /**
>>>>>>> origin
   * Return the AC_VI CWmax field in the EdcaParameterSet information element.
   *
   * \return the AC_VI CWmax field in the EdcaParameterSet information element
   */
<<<<<<< HEAD
  uint8_t GetViCWmax (void) const;
  /*
=======
  uint32_t GetViCWmax (void) const;
  /**
>>>>>>> origin
   * Return the AC_VI TXOP Limit field in the EdcaParameterSet information element.
   *
   * \return the AC_VI TXOP Limit field in the EdcaParameterSet information element
   */
<<<<<<< HEAD
  uint16_t GetViTXOPLimit (void) const;
  /*
=======
  uint16_t GetViTxopLimit (void) const;
  /**
>>>>>>> origin
   * Return the AC_VO AIFSN field in the EdcaParameterSet information element.
   *
   * \return the AC_VO AIFSN field in the EdcaParameterSet information element
   */
  uint8_t GetVoAifsn (void) const;
<<<<<<< HEAD
  /*
   * Return the AC_VO ACM field in the EdcaParameterSet information element.
   *
   * \return the AC_VO ACM field in the EdcaParameterSet information element
   */
  uint8_t GetVoAcm (void) const;
  /*
   * Return the AC_VO ACI field in the EdcaParameterSet information element.
   *
   * \return the AC_VO ACI field in the EdcaParameterSet information element
   */
  uint8_t GetVoAci (void) const;
  /*
=======
  /**
>>>>>>> origin
   * Return the AC_VO CWmin field in the EdcaParameterSet information element.
   *
   * \return the AC_VO CWmin field in the EdcaParameterSet information element
   */
<<<<<<< HEAD
  uint8_t GetVoCWmin (void) const;
  /*
=======
  uint32_t GetVoCWmin (void) const;
  /**
>>>>>>> origin
   * Return the AC_VO CWmax field in the EdcaParameterSet information element.
   *
   * \return the AC_VO CWmax field in the EdcaParameterSet information element
   */
<<<<<<< HEAD
  uint8_t GetVoCWmax (void) const;
  /*
=======
  uint32_t GetVoCWmax (void) const;
  /**
>>>>>>> origin
   * Return the AC_VO TXOP Limit field in the EdcaParameterSet information element.
   *
   * \return the AC_VO TXOP Limit field in the EdcaParameterSet information element
   */
<<<<<<< HEAD
  uint16_t GetVoTXOPLimit (void) const;
  
  WifiInformationElementId ElementId () const;
  uint8_t GetInformationFieldSize () const;
  void SerializeInformationField (Buffer::Iterator start) const;
  uint8_t DeserializeInformationField (Buffer::Iterator start, uint8_t length);
    
  /**
   * This information element is a bit special in that it is only
   * included if the STA is a QoS STA. To support this we
   * override the Serialize and GetSerializedSize methods of
   * WifiInformationElement.
   *
   * \param start
   *
   * \return an iterator
   */
  Buffer::Iterator Serialize (Buffer::Iterator start) const;
  /**
   * Return the serialized size of this EDCA Parameter Set.
   *
   * \return the serialized size of this EDCA Parameter Set
   */
  uint16_t GetSerializedSize () const;

private:
  uint8_t m_qosInfo;
  uint8_t m_reserved;
  uint32_t m_acBE;
  uint32_t m_acBK;
  uint32_t m_acVI;
  uint32_t m_acVO;

  //This is used to decide whether this element should be added to the frame or not
  bool m_qosSupported;
};

std::ostream &operator << (std::ostream &os, const EdcaParameterSet &edcaParameterSet);
std::istream &operator >> (std::istream &is, EdcaParameterSet &edcaParameterSet);

ATTRIBUTE_HELPER_HEADER (EdcaParameterSet);

=======
  uint16_t GetVoTxopLimit (void) const;


private:
  uint8_t m_qosInfo;  ///< QOS info
  uint8_t m_reserved; ///< reserved
  uint32_t m_acBE;    ///< AC_BE
  uint32_t m_acBK;    ///< AC_BK
  uint32_t m_acVI;    ///< AC_VI
  uint32_t m_acVO;    ///< AC_VO

  /// This is used to decide whether this element should be added to the frame or not
  bool m_qosSupported;
};

>>>>>>> origin
} //namespace ns3

#endif /* EDCA_PARAMETER_SET_H */

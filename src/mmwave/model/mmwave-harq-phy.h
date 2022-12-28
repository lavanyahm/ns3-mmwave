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
 *   Adapted from the release 1.0 of the 5G-LENA simulator, please refer to https://5g-lena.cttc.es/ for further details 
 *   and https://gitlab.com/cttc-lena/nr/-/tree/v1.0 for the reference code.
 * 
 *   Copyright (c) 2019 Centre Tecnologic de Telecomunicacions de Catalunya (CTTC)
 *   Copyright (c) 2021 University of Padova, Dep. of Information Engineering, SIGNET lab.
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


#ifndef SRC_MMWAVE_HARQ_PHY_MODULE_H
#define SRC_MMWAVE_HARQ_PHY_MODULE_H

#include <vector>
#include <unordered_map>
#include <ns3/simple-ref-count.h>
#include <ns3/mmwave-error-model.h>

namespace ns3 {

<<<<<<< HEAD


struct MmWaveHarqProcessInfoElement_t
{
   double m_mi;
   uint8_t m_rv;
   uint32_t m_infoBits;
   uint32_t m_codeBits;
};

typedef std::vector <MmWaveHarqProcessInfoElement_t> MmWaveHarqProcessInfoList_t;
=======
namespace mmwave{
>>>>>>> origin

/**
 * \ingroup error-models
 *
 * \brief HARQ functionalities for the PHY layer
 *
 * (i.e., decodification buffers for incremental redundancy managment)
 *
*/
class MmWaveHarqPhy : public SimpleRefCount<MmWaveHarqPhy>
{
public:
  /**
    * \brief Constructor
    */
  ~MmWaveHarqPhy ();

  /**
  * \brief Return the info of the HARQ procId in case of retranmissions
  * for DL (asynchronous)
  * \param rnti the RNTI
  * \param harqProcId the HARQ proc id
  * \return the vector of the info related to HARQ proc Id
  */
<<<<<<< HEAD
  MmWaveHarqProcessInfoList_t GetHarqProcessInfoDl (uint16_t rnti, uint8_t harqProcId);

  /**
  * \brief Return the cumulated MI of the HARQ procId in case of retranmissions
  * for UL (synchronous)
  * \return the MI accumulated
  */
  double GetAccumulatedMiUl (uint16_t rnti, uint8_t harqId);
=======
  const MmWaveErrorModel::MmWaveErrorModelHistory & GetHarqProcessInfoDl (uint16_t rnti, uint8_t harqProcId);
>>>>>>> origin

  /**
  * \brief Return the info of the HARQ procId in case of retranmissions
  * for UL (asynchronous)
  * \param rnti the RNTI
  * \param harqProcId the HARQ process id
  * \return the vector of the info related to HARQ proc Id
  */
<<<<<<< HEAD
  MmWaveHarqProcessInfoList_t GetHarqProcessInfoUl (uint16_t rnti, uint8_t harqProcId);
=======
  const MmWaveErrorModel::MmWaveErrorModelHistory & GetHarqProcessInfoUl (uint16_t rnti, uint8_t harqProcId);
>>>>>>> origin

  /**
  * \brief Update the Info associated to the decodification of an HARQ process
  * for DL (asynchronous)
  * \param rnti the RNTI
  * \param harqProcId the HARQ process id
  * \param output output of the error model
  */
  void UpdateDlHarqProcessStatus (uint16_t rnti, uint8_t harqProcId,
                                  const Ptr<MmWaveErrorModelOutput> &output);

  /**
  * \brief Reset the info associated to the decodification of an HARQ process
  * for DL (asynchronous)
  * \param rnti the RNTI
  * \param id the HARQ process id
  */
  void ResetDlHarqProcessStatus (uint16_t rnti, uint8_t id);

  /**
  * \brief Update the Info associated to the decodification of an HARQ process
  * for UL (asynchronous)
  * \param rnti the RNTI
  * \param harqProcId the HARQ process id
  * \param output output of the error model
  */
  void UpdateUlHarqProcessStatus (uint16_t rnti, uint8_t harqProcId,
                                  const Ptr<MmWaveErrorModelOutput> &output);

  /**
  * \brief Reset the info associated to the decodification of an HARQ process
  * for UL (asynchronous)
  * \param rnti the RNTI
  * \param id the HARQ process id
  */
  void ResetUlHarqProcessStatus (uint16_t rnti, uint8_t id);

private:

<<<<<<< HEAD
  uint32_t m_harqNum;
  std::map <uint16_t, std::vector <MmWaveHarqProcessInfoList_t> > m_miDlHarqProcessesInfoMap;
  std::map <uint16_t, std::vector <MmWaveHarqProcessInfoList_t> > m_miUlHarqProcessesInfoMap;
  
=======
  /**
   * \brief Map between a process id and its HARQ history (a vector of pointers)
   *
   * The HARQ history depends on the error model (LTE error model stores MI (MIESM-based), while NR
   * error model stores SINR (EESM-based)) as well as on the HARQ combining method.
   */
  typedef std::unordered_map <uint8_t, MmWaveErrorModel::MmWaveErrorModelHistory> ProcIdHistoryMap;
  /**
   * \brief Map between an RNTI and its ProcIdHistoryMap
   */
  typedef std::unordered_map <uint16_t, ProcIdHistoryMap> HistoryMap;
  /**
  * \brief Return the HARQ history map of the retransmissions of all process ids of a particular RNTI
  * \param rnti the RNTI
  * \param map the Map between RNTIs and their history
  * \return the HistoryMap of such RNTI
  */
  HistoryMap::iterator GetHistoryMapOf (HistoryMap *map, uint16_t rnti) const;
  /**
  * \brief Return the HARQ history of a particular process id
  * \param procId the process id
  * \param map the Map between processes ids and their history
  * \return the ProcIdHistoryMap of such process id
  */
  ProcIdHistoryMap::iterator GetProcIdHistoryMapOf (ProcIdHistoryMap *map, uint16_t procId) const;
>>>>>>> origin

  /**
  * \brief Reset the HARQ history of a particular process id
  * \param rnti the RNTI
  * \param id the HARQ process id
  * \param map the Map between RNTIs and their history
  */
  void ResetHarqProcessStatus (HistoryMap *map, uint16_t rnti, uint8_t harqProcId) const;
  /**
  * \brief Update the HARQ history of a particular process id
  * \param rnti the RNTI
  * \param id the HARQ process id
  * \param map the Map between RNTIs and their history
  * \param output the new HARQ history to be included
  */
  void UpdateHarqProcessStatus (HistoryMap *map, uint16_t rnti, uint8_t harqProcId, const Ptr<MmWaveErrorModelOutput> &output) const;
  /**
  * \brief Return the HARQ history of a particular process id
  * \param rnti the RNTI
  * \param id the HARQ process id
  * \param map the Map between RNTIs and their history
  * \return the HARQ history of such process id
  */
  const MmWaveErrorModel::MmWaveErrorModelHistory & GetHarqProcessInfo (HistoryMap *map, uint16_t rnti, uint8_t harqProcId) const;

  HistoryMap m_dlHistory; //!< HARQ history map for DL
  HistoryMap m_ulHistory; //!< HARQ history map for UL
};


} // namespace ns3
} // namespace mmwave

#endif /* SRC_MMWAVE_HARQ_PHY_MODULE_H */

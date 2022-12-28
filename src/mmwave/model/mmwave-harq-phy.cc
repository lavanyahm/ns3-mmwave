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


#include "mmwave-harq-phy.h"
#include <ns3/log.h>
#include <ns3/assert.h>

NS_LOG_COMPONENT_DEFINE ("MmWaveHarqPhy");

namespace ns3 {

namespace mmwave{

MmWaveHarqPhy::~MmWaveHarqPhy ()
{
  NS_LOG_FUNCTION (this);
  m_dlHistory.clear ();
  m_ulHistory.clear ();
}

<<<<<<< HEAD

double
MmWaveHarqPhy::GetAccumulatedMiDl (uint16_t rnti, uint8_t harqId)
{
  NS_LOG_FUNCTION (this << (uint16_t)rnti << (uint16_t)harqId);
  std::map <uint16_t, std::vector <MmWaveHarqProcessInfoList_t> >::iterator it;
  it = m_miDlHarqProcessesInfoMap.find (rnti);
  NS_ASSERT_MSG (it!=m_miDlHarqProcessesInfoMap.end (), " Does not find MI for RNTI");
  MmWaveHarqProcessInfoList_t list = (*it).second.at (harqId);
  double mi = 0.0;
  for (uint8_t i = 0; i < list.size (); i++)
  {
  	mi += list.at (i).m_mi;
  }
  return (mi);
}

MmWaveHarqProcessInfoList_t
MmWaveHarqPhy::GetHarqProcessInfoDl (uint16_t rnti, uint8_t harqProcId)
{
	NS_LOG_FUNCTION (this << rnti << (uint16_t)harqProcId);
	std::map <uint16_t, std::vector <MmWaveHarqProcessInfoList_t> >::iterator it;
	it = m_miDlHarqProcessesInfoMap.find (rnti);
	if (it==m_miDlHarqProcessesInfoMap.end ())
	{
		// new entry
		std::vector <MmWaveHarqProcessInfoList_t> harqList;
		harqList.resize (m_harqNum);
		m_miDlHarqProcessesInfoMap.insert (std::pair <uint16_t, std::vector <MmWaveHarqProcessInfoList_t> > (rnti, harqList));
		return (harqList.at (harqProcId));
	}
	else
	{
		return ((*it).second.at (harqProcId));
	}
}


double
MmWaveHarqPhy::GetAccumulatedMiUl (uint16_t rnti, uint8_t harqId)
{
  NS_LOG_FUNCTION (this << rnti);

  std::map <uint16_t, std::vector <MmWaveHarqProcessInfoList_t> >::iterator it;
  it = m_miUlHarqProcessesInfoMap.find (rnti);
  NS_ASSERT_MSG (it!=m_miUlHarqProcessesInfoMap.end (), " Does not find MI for RNTI");
  MmWaveHarqProcessInfoList_t list = (*it).second.at (harqId);
  double mi = 0.0;
  for (uint8_t i = 0; i < list.size (); i++)
  {
  	mi += list.at (i).m_mi;
  }
  return (mi);
}

MmWaveHarqProcessInfoList_t
MmWaveHarqPhy::GetHarqProcessInfoUl (uint16_t rnti, uint8_t harqProcId)
{
	NS_LOG_FUNCTION (this << rnti << (uint16_t)harqProcId);
	std::map <uint16_t, std::vector <MmWaveHarqProcessInfoList_t> >::iterator it;
	it = m_miUlHarqProcessesInfoMap.find (rnti);
	if (it==m_miUlHarqProcessesInfoMap.end ())
	{
		// new entry
		std::vector <MmWaveHarqProcessInfoList_t> harqList;
		harqList.resize (m_harqNum);
		m_miUlHarqProcessesInfoMap.insert (std::pair <uint16_t, std::vector <MmWaveHarqProcessInfoList_t> > (rnti, harqList));
		return (harqList.at (harqProcId));
	}
	else
	{
		return ((*it).second.at (harqProcId));
	}
=======
const MmWaveErrorModel::MmWaveErrorModelHistory &
MmWaveHarqPhy::GetHarqProcessInfoDl (uint16_t rnti, uint8_t harqProcId)
{
  NS_LOG_FUNCTION (this);
  return GetHarqProcessInfo (&m_dlHistory, rnti, harqProcId);
}

const MmWaveErrorModel::MmWaveErrorModelHistory &
MmWaveHarqPhy::GetHarqProcessInfoUl (uint16_t rnti, uint8_t harqProcId)
{
  NS_LOG_FUNCTION (this);
  return GetHarqProcessInfo (&m_ulHistory, rnti, harqProcId);
>>>>>>> origin
}

void
MmWaveHarqPhy::UpdateDlHarqProcessStatus (uint16_t rnti, uint8_t harqProcId,
                                          const Ptr<MmWaveErrorModelOutput> &output)
{
<<<<<<< HEAD
  NS_LOG_FUNCTION (this << (uint16_t) harqId << mi);
  std::map <uint16_t, std::vector <MmWaveHarqProcessInfoList_t> >::iterator it;
    it = m_miDlHarqProcessesInfoMap.find (rnti);
    if (it==m_miDlHarqProcessesInfoMap.end ())
      {
        // new entry
        std::vector <MmWaveHarqProcessInfoList_t> harqList;
        harqList.resize (m_harqNum);
        MmWaveHarqProcessInfoElement_t el;
        el.m_mi = mi;
        el.m_rv = 0;
        el.m_infoBits = infoBytes * 8;
        el.m_codeBits = codeBytes * 8;
        harqList.at (harqId).push_back (el);
        m_miDlHarqProcessesInfoMap.insert (std::pair <uint16_t, std::vector <MmWaveHarqProcessInfoList_t> > (rnti, harqList));
      }
    else
      {
        if ((*it).second.at (harqId).size () == 3) // MAX HARQ RETX
          {
            // HARQ should be disabled -> discard info
            return;
          }
        MmWaveHarqProcessInfoElement_t el;
        el.m_mi = mi;
        if(!(*it).second.at (harqId).empty ())
        {
        	el.m_rv = (*it).second.at (harqId).back().m_rv + 1;
        }
        else
        {
        	el.m_rv = 0;
        }
        el.m_infoBits = infoBytes * 8;
        el.m_codeBits = codeBytes * 8;
        (*it).second.at (harqId).push_back (el);
      }
=======
  NS_LOG_FUNCTION (this);
  UpdateHarqProcessStatus (&m_dlHistory, rnti, harqProcId, output);
>>>>>>> origin
}


void
MmWaveHarqPhy::ResetDlHarqProcessStatus (uint16_t rnti, uint8_t id)
{
<<<<<<< HEAD
  NS_LOG_FUNCTION (this << (uint16_t) id);

  NS_LOG_FUNCTION (this << rnti << (uint16_t)id);
  std::map <uint16_t, std::vector <MmWaveHarqProcessInfoList_t> >::iterator it;
  it = m_miDlHarqProcessesInfoMap.find (rnti);
  if (it==m_miDlHarqProcessesInfoMap.end ())
  {
  	// new entry
  	std::vector <MmWaveHarqProcessInfoList_t> harqList;
  	harqList.resize (m_harqNum);
  	m_miDlHarqProcessesInfoMap.insert (std::pair <uint16_t, std::vector <MmWaveHarqProcessInfoList_t> > (rnti, harqList));
  }
  else
  {
  	(*it).second.at (id).clear ();
  }
=======
  NS_LOG_FUNCTION (this);
  ResetHarqProcessStatus (&m_dlHistory, rnti, id);
>>>>>>> origin
}

void
MmWaveHarqPhy::UpdateUlHarqProcessStatus (uint16_t rnti, uint8_t harqProcId,
                                          const Ptr<MmWaveErrorModelOutput> &output)
{
<<<<<<< HEAD
  NS_LOG_FUNCTION (this << rnti << mi);
  std::map <uint16_t, std::vector <MmWaveHarqProcessInfoList_t> >::iterator it;
  it = m_miUlHarqProcessesInfoMap.find (rnti);
  if (it==m_miUlHarqProcessesInfoMap.end ())
    {
      // new entry
      std::vector <MmWaveHarqProcessInfoList_t> harqList;
      harqList.resize (m_harqNum);
      MmWaveHarqProcessInfoElement_t el;
      el.m_mi = mi;
      el.m_rv = 0;
      el.m_infoBits = infoBytes * 8;
      el.m_codeBits = codeBytes * 8;
      harqList.at (harqId).push_back (el);
      m_miUlHarqProcessesInfoMap.insert (std::pair <uint16_t, std::vector <MmWaveHarqProcessInfoList_t> > (rnti, harqList));
    }
  else
    {
      if ((*it).second.at (harqId).size () == 3) // MAX HARQ RETX
        {
          // HARQ should be disabled -> discard info
          return;
        }
      MmWaveHarqProcessInfoElement_t el;
      el.m_mi = mi;
      if(!(*it).second.at (harqId).empty ())
      {
      	el.m_rv = (*it).second.at (harqId).back().m_rv + 1;
      }
      else
      {
      	el.m_rv = 0;
      }
      el.m_infoBits = infoBytes * 8;
      el.m_codeBits = codeBytes * 8;
      (*it).second.at (harqId).push_back (el);
    }
=======
  NS_LOG_FUNCTION (this);
  UpdateHarqProcessStatus (&m_ulHistory, rnti, harqProcId, output);
>>>>>>> origin
}

void
MmWaveHarqPhy::ResetUlHarqProcessStatus (uint16_t rnti, uint8_t id)
{
<<<<<<< HEAD
	NS_LOG_FUNCTION (this << rnti << (uint16_t)id);
	std::map <uint16_t, std::vector <MmWaveHarqProcessInfoList_t> >::iterator it;
	it = m_miUlHarqProcessesInfoMap.find (rnti);
	if (it==m_miUlHarqProcessesInfoMap.end ())
	{
		// new entry
		std::vector <MmWaveHarqProcessInfoList_t> harqList;
		harqList.resize (m_harqNum);
		m_miUlHarqProcessesInfoMap.insert (std::pair <uint16_t, std::vector <MmWaveHarqProcessInfoList_t> > (rnti, harqList));
	}
	else
	{
		(*it).second.at (id).clear ();
	}
=======
  NS_LOG_FUNCTION (this);
  ResetHarqProcessStatus (&m_ulHistory, rnti, id);
}

MmWaveHarqPhy::HistoryMap::iterator
MmWaveHarqPhy::GetHistoryMapOf (MmWaveHarqPhy::HistoryMap *map, uint16_t rnti) const
{
  NS_LOG_FUNCTION (this);

  MmWaveHarqPhy::HistoryMap::iterator it = map->find (rnti);
  if (it == map->end ())
    {
      auto ret = map->insert (std::make_pair (rnti, ProcIdHistoryMap ()));
      NS_ASSERT (ret.second);

      it = ret.first;
    }

  return it;
}

MmWaveHarqPhy::ProcIdHistoryMap::iterator
MmWaveHarqPhy::GetProcIdHistoryMapOf (MmWaveHarqPhy::ProcIdHistoryMap *map, uint16_t procId) const
{
  NS_LOG_FUNCTION (this);

  MmWaveHarqPhy::ProcIdHistoryMap::iterator it = map->find (procId);
  if (it == map->end())
    {
      auto ret = map->insert (std::make_pair (procId, MmWaveErrorModel::MmWaveErrorModelHistory ()));
      NS_ASSERT (ret.second);

      it = ret.first;
    }

  return it;
}

void
MmWaveHarqPhy::ResetHarqProcessStatus (MmWaveHarqPhy::HistoryMap *map, uint16_t rnti,
                                       uint8_t harqProcId) const
{
  NS_LOG_FUNCTION (this);

  MmWaveHarqPhy::HistoryMap::iterator historyMap = GetHistoryMapOf (map, rnti);

  ProcIdHistoryMap * procIdMap = &(historyMap->second);

  GetProcIdHistoryMapOf (procIdMap, harqProcId)->second.clear ();
}

void
MmWaveHarqPhy::UpdateHarqProcessStatus (MmWaveHarqPhy::HistoryMap *map, uint16_t rnti,
                                        uint8_t harqProcId, const Ptr<MmWaveErrorModelOutput> &output) const
{
  NS_LOG_FUNCTION (this);

  MmWaveHarqPhy::HistoryMap::iterator historyMap = GetHistoryMapOf (map, rnti);

  ProcIdHistoryMap * procIdMap = &(historyMap->second);

  GetProcIdHistoryMapOf (procIdMap, harqProcId)->second.emplace_back (output);
}

const MmWaveErrorModel::MmWaveErrorModelHistory &
MmWaveHarqPhy::GetHarqProcessInfo (MmWaveHarqPhy::HistoryMap *map, uint16_t rnti,
                                   uint8_t harqProcId) const
{
  NS_LOG_FUNCTION (this);

  MmWaveHarqPhy::HistoryMap::iterator historyMap = GetHistoryMapOf (map, rnti);

  ProcIdHistoryMap * procIdMap = &(historyMap->second);

  return GetProcIdHistoryMapOf (procIdMap, harqProcId)->second;
>>>>>>> origin
}




} // namespace ns3
} // namespace mmwave

/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2008 Drexel University
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
 * Author: Joe Kopena (tjkopena@cs.drexel.edu)
 */

#include "sqlite-data-output.h"
#include <sstream>

#include "ns3/log.h"
#include "ns3/nstime.h"

#include "data-collector.h"
#include "data-calculator.h"
#include "sqlite-output.h"

namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("SqliteDataOutput");

SqliteDataOutput::SqliteDataOutput ()
  : DataOutputInterface ()
{
  NS_LOG_FUNCTION (this);

  m_filePrefix = "data";
}
SqliteDataOutput::~SqliteDataOutput ()
{
  NS_LOG_FUNCTION (this);
}
/* static */
TypeId
SqliteDataOutput::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::SqliteDataOutput")
    .SetParent<DataOutputInterface> ()
    .SetGroupName ("Stats")
    .AddConstructor<SqliteDataOutput> ();
  return tid;
}

//----------------------------------------------
void
SqliteDataOutput::Output (DataCollector &dc)
{
  NS_LOG_FUNCTION (this << &dc);

  std::string m_dbFile = m_filePrefix + ".db";
<<<<<<< HEAD

  if (sqlite3_open (m_dbFile.c_str (), &m_db)) {
      NS_LOG_ERROR ("Could not open sqlite3 database \"" << m_dbFile << "\"");
      NS_LOG_ERROR ("sqlite3 error \"" << sqlite3_errmsg (m_db) << "\"");
      sqlite3_close (m_db);
      /// \todo Better error reporting, management!
      return;
    }

  Exec ("create table if not exists Experiments (run, experiment, strategy, input, description text)");

  sqlite3_stmt *stmt;
  sqlite3_prepare_v2 (m_db,
    "insert into Experiments (run, experiment, strategy, input, description) values (?, ?, ?, ?, ?)",
    -1,
    &stmt,
    NULL
  );

  std::string run = dc.GetRunLabel ();
  sqlite3_bind_text (stmt, 1, run.c_str (), run.length (), SQLITE_TRANSIENT);
  sqlite3_bind_text (stmt, 2, dc.GetExperimentLabel ().c_str (),
                              dc.GetExperimentLabel ().length (), SQLITE_TRANSIENT);
  sqlite3_bind_text (stmt, 3, dc.GetStrategyLabel ().c_str (),
                              dc.GetStrategyLabel ().length (), SQLITE_TRANSIENT);
  sqlite3_bind_text (stmt, 4, dc.GetInputLabel ().c_str (),
                              dc.GetInputLabel ().length (), SQLITE_TRANSIENT);
  sqlite3_bind_text (stmt, 5, dc.GetDescription ().c_str (),
                              dc.GetDescription ().length (), SQLITE_TRANSIENT);
  sqlite3_step (stmt);
  sqlite3_finalize (stmt);
=======
  std::string run = dc.GetRunLabel ();
  bool res;

  m_sqliteOut = new SQLiteOutput (m_dbFile, "ns-3-sqlite-data-output-sem");
>>>>>>> origin

  res = m_sqliteOut->SpinExec ("CREATE TABLE IF NOT EXISTS Experiments (run, experiment, strategy, input, description text)");
  NS_ASSERT (res);

  sqlite3_stmt *stmt;
  res = m_sqliteOut->WaitPrepare (&stmt,
                                  "INSERT INTO Experiments " \
                                  "(run, experiment, strategy, input, description)" \
                                  "values (?, ?, ?, ?, ?)");
  NS_ASSERT (res);

  res = m_sqliteOut->Bind (stmt, 1, run);
  NS_ASSERT (res);
  res = m_sqliteOut->Bind (stmt, 2, dc.GetExperimentLabel ());
  NS_ASSERT (res);
  res = m_sqliteOut->Bind (stmt, 3, dc.GetStrategyLabel ());
  NS_ASSERT (res);
  res = m_sqliteOut->Bind (stmt, 4, dc.GetInputLabel ());
  NS_ASSERT (res);
  res = m_sqliteOut->Bind (stmt, 5, dc.GetDescription ());
  NS_ASSERT (res);

  res = m_sqliteOut->SpinStep (stmt);
  NS_ASSERT (res);
  res = m_sqliteOut->SpinFinalize (stmt);
  NS_ASSERT (res);

  res = m_sqliteOut->WaitExec ("CREATE TABLE IF NOT EXISTS " \
                               "Metadata ( run text, key text, value)");
  NS_ASSERT (res);

  res = m_sqliteOut->WaitPrepare (&stmt,
                                  "INSERT INTO Metadata " \
                                  "(run, key, value)" \
                                  "values (?, ?, ?)");
  NS_ASSERT (res);

  sqlite3_prepare_v2 (m_db,
    "insert into Metadata (run, key, value) values (?, ?, ?)",
    -1,
    &stmt,
    NULL
  );
  for (MetadataList::iterator i = dc.MetadataBegin ();
       i != dc.MetadataEnd (); i++)
    {
      std::pair<std::string, std::string> blob = (*i);
<<<<<<< HEAD

      sqlite3_reset (stmt);
      sqlite3_bind_text (stmt, 1, run.c_str (),
                                  run.length (), SQLITE_TRANSIENT);
      sqlite3_bind_text (stmt, 2, blob.first.c_str (),
                                  blob.first.length (), SQLITE_TRANSIENT);
      sqlite3_bind_text (stmt, 3, blob.second.c_str (),
                                  blob.second.length (), SQLITE_TRANSIENT);
      sqlite3_step (stmt);
=======
      m_sqliteOut->SpinReset (stmt);
      m_sqliteOut->Bind (stmt, 1, run);
      m_sqliteOut->Bind (stmt, 2, blob.first);
      m_sqliteOut->Bind (stmt, 3, blob.second);
      m_sqliteOut->SpinStep (stmt);
>>>>>>> origin
    }
  sqlite3_finalize (stmt);

  m_sqliteOut->SpinFinalize (stmt);

  m_sqliteOut->SpinExec ("BEGIN");
  SqliteOutputCallback callback (m_sqliteOut, run);
  for (DataCalculatorList::iterator i = dc.DataCalculatorBegin ();
       i != dc.DataCalculatorEnd (); i++)
    {
      (*i)->Output (callback);
    }
  m_sqliteOut->SpinExec ("COMMIT");
  // end SqliteDataOutput::Output
}

SqliteDataOutput::SqliteOutputCallback::SqliteOutputCallback
  (const Ptr<SQLiteOutput> &db, std::string run)
  : m_db (db),
    m_runLabel (run)
{
  NS_LOG_FUNCTION (this << db << run);

  m_db->WaitExec ("CREATE TABLE IF NOT EXISTS Singletons " \
                  "( run text, name text, variable text, value )");

<<<<<<< HEAD
  sqlite3_prepare_v2 (m_owner->m_db,
    "insert into Singletons (run, name, variable, value) values (?, ?, ?, ?)",
    -1,
    &m_insertSingletonStatement,
    NULL
  );
  sqlite3_bind_text (m_insertSingletonStatement, 1, m_runLabel.c_str (), m_runLabel.length (), SQLITE_TRANSIENT);

  // end SqliteDataOutput::SqliteOutputCallback::SqliteOutputCallback
=======
  m_db->WaitPrepare (&m_insertSingletonStatement, "INSERT INTO Singletons " \
                     "(run, name, variable, value)" \
                     "values (?, ?, ?, ?)");
  m_db->Bind (m_insertSingletonStatement, 1, m_runLabel);
}

SqliteDataOutput::SqliteOutputCallback::~SqliteOutputCallback ()
{
  m_db->SpinFinalize (m_insertSingletonStatement);
>>>>>>> origin
}

SqliteDataOutput::SqliteOutputCallback::~SqliteOutputCallback ()
{
  sqlite3_finalize (m_insertSingletonStatement);
}

void
SqliteDataOutput::SqliteOutputCallback::OutputStatistic (std::string key,
                                                         std::string variable,
                                                         const StatisticalSummary *statSum)
{
  NS_LOG_FUNCTION (this << key << variable << statSum);

  OutputSingleton (key,variable + "-count", static_cast<double> (statSum->getCount ()));
  if (!isNaN (statSum->getSum ()))
    {
      OutputSingleton (key,variable + "-total", statSum->getSum ());
    }
  if (!isNaN (statSum->getMax ()))
    {
      OutputSingleton (key,variable + "-max", statSum->getMax ());
    }
  if (!isNaN (statSum->getMin ()))
    {
      OutputSingleton (key,variable + "-min", statSum->getMin ());
    }
  if (!isNaN (statSum->getSqrSum ()))
    {
      OutputSingleton (key,variable + "-sqrsum", statSum->getSqrSum ());
    }
  if (!isNaN (statSum->getStddev ()))
    {
      OutputSingleton (key,variable + "-stddev", statSum->getStddev ());
    }
}


void
SqliteDataOutput::SqliteOutputCallback::OutputSingleton (std::string key,
                                                         std::string variable,
                                                         int val)
{
  NS_LOG_FUNCTION (this << key << variable << val);

<<<<<<< HEAD
  sqlite3_reset (m_insertSingletonStatement);
  sqlite3_bind_text (m_insertSingletonStatement, 2, key.c_str (), key.length (), SQLITE_TRANSIENT);
  sqlite3_bind_text (m_insertSingletonStatement, 3, variable.c_str (), variable.length (), SQLITE_TRANSIENT);
  sqlite3_bind_int (m_insertSingletonStatement, 4, val);
  sqlite3_step (m_insertSingletonStatement);
=======
  m_db->SpinReset (m_insertSingletonStatement);
  m_db->Bind (m_insertSingletonStatement, 2, key);
  m_db->Bind (m_insertSingletonStatement, 3, variable);
  m_db->Bind (m_insertSingletonStatement, 4, val);
  m_db->SpinStep (m_insertSingletonStatement);
>>>>>>> origin
}
void
SqliteDataOutput::SqliteOutputCallback::OutputSingleton (std::string key,
                                                         std::string variable,
                                                         uint32_t val)
{
  NS_LOG_FUNCTION (this << key << variable << val);

<<<<<<< HEAD
  sqlite3_reset (m_insertSingletonStatement);
  sqlite3_bind_text (m_insertSingletonStatement, 2, key.c_str (), key.length (), SQLITE_TRANSIENT);
  sqlite3_bind_text (m_insertSingletonStatement, 3, variable.c_str (), variable.length (), SQLITE_TRANSIENT);
  sqlite3_bind_int64 (m_insertSingletonStatement, 4, val);
  sqlite3_step (m_insertSingletonStatement);
=======
  m_db->SpinReset (m_insertSingletonStatement);
  m_db->Bind (m_insertSingletonStatement, 2, key);
  m_db->Bind (m_insertSingletonStatement, 3, variable);
  m_db->Bind (m_insertSingletonStatement, 4, val);
  m_db->SpinStep (m_insertSingletonStatement);
>>>>>>> origin
}

void
SqliteDataOutput::SqliteOutputCallback::OutputSingleton (std::string key,
                                                         std::string variable,
                                                         double val)
{
  NS_LOG_FUNCTION (this << key << variable << val);

<<<<<<< HEAD
  sqlite3_reset (m_insertSingletonStatement);
  sqlite3_bind_text (m_insertSingletonStatement, 2, key.c_str (), key.length (), SQLITE_TRANSIENT);
  sqlite3_bind_text (m_insertSingletonStatement, 3, variable.c_str (), variable.length (), SQLITE_TRANSIENT);
  sqlite3_bind_double (m_insertSingletonStatement, 4, val);
  sqlite3_step (m_insertSingletonStatement);
=======
  m_db->SpinReset (m_insertSingletonStatement);
  m_db->Bind (m_insertSingletonStatement, 2, key);
  m_db->Bind (m_insertSingletonStatement, 3, variable);
  m_db->Bind (m_insertSingletonStatement, 4, val);
  m_db->SpinStep (m_insertSingletonStatement);
>>>>>>> origin
}

void
SqliteDataOutput::SqliteOutputCallback::OutputSingleton (std::string key,
                                                         std::string variable,
                                                         std::string val)
{
  NS_LOG_FUNCTION (this << key << variable << val);

<<<<<<< HEAD
  sqlite3_reset (m_insertSingletonStatement);
  sqlite3_bind_text (m_insertSingletonStatement, 2, key.c_str (), key.length (), SQLITE_TRANSIENT);
  sqlite3_bind_text (m_insertSingletonStatement, 3, variable.c_str (), variable.length (), SQLITE_TRANSIENT);
  sqlite3_bind_text (m_insertSingletonStatement, 4, val.c_str (), val.length (), SQLITE_TRANSIENT);
  sqlite3_step (m_insertSingletonStatement);
=======
  m_db->SpinReset (m_insertSingletonStatement);
  m_db->Bind (m_insertSingletonStatement, 2, key);
  m_db->Bind (m_insertSingletonStatement, 3, variable);
  m_db->Bind (m_insertSingletonStatement, 4, val);
  m_db->SpinStep (m_insertSingletonStatement);
>>>>>>> origin
}

void
SqliteDataOutput::SqliteOutputCallback::OutputSingleton (std::string key,
                                                         std::string variable,
                                                         Time val)
{
  NS_LOG_FUNCTION (this << key << variable << val);

<<<<<<< HEAD
  sqlite3_reset (m_insertSingletonStatement);
  sqlite3_bind_text (m_insertSingletonStatement, 2, key.c_str (), key.length (), SQLITE_TRANSIENT);
  sqlite3_bind_text (m_insertSingletonStatement, 3, variable.c_str (), variable.length (), SQLITE_TRANSIENT);
  sqlite3_bind_int64 (m_insertSingletonStatement, 4, val.GetTimeStep ());
  sqlite3_step (m_insertSingletonStatement);
=======
  m_db->SpinReset (m_insertSingletonStatement);
  m_db->Bind (m_insertSingletonStatement, 2, key);
  m_db->Bind (m_insertSingletonStatement, 3, variable);
  m_db->Bind (m_insertSingletonStatement, 4, val.GetTimeStep ());
  m_db->SpinStep (m_insertSingletonStatement);
>>>>>>> origin
}

} // namespace ns3

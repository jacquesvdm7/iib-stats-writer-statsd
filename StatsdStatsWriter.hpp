/********************************************************* {COPYRIGHT-TOP} ***
* Copyright 2016 IBM Corporation
*
* All rights reserved. This program and the accompanying materials
* are made available under the terms of the MIT License
* which accompanies this distribution, and is available at
* http://opensource.org/licenses/MIT
********************************************************** {COPYRIGHT-END} **/

#ifndef StatsdStatsWriter_hpp
#define StatsdStatsWriter_hpp

#include <BipCsi.h>
#include <memory>
#include <string>

class UdpSocket;

class StatsdStatsWriter {

public:

  StatsdStatsWriter();
  ~StatsdStatsWriter();

  CciSize getAttributeName(int* rc, int index, CciChar* buffer, CciSize bufferLength) const;
  CciSize getAttribute(int* rc, const CciChar* name, CciChar* buffer, CciSize bufferLength) const;
  void setAttribute(int* rc, const CciChar* name, const CciChar* value);

  void write(const CsiStatsRecord* record);

  CsiStatsWriter* writer() const { return iWriter; }

private:

  CsiStatsWriter* iWriter;
  std::u16string iHostname;
  std::u16string iPort;
  std::unique_ptr<UdpSocket> iSocket;

  uint64_t calculateMillis(const CciDate& date, const CciTime& time);

  void writeMessageFlowMetrics(const std::u16string& metricbase, const CsiStatsRecord* record, uint64_t duration);

  template <class T>
  void writeMetric(const std::u16string& metricbase, const std::u16string& metricname, T value);

};

#endif // StatsdStatsWriter_hpp

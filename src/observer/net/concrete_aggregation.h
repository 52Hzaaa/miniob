#pragma once

#include "net/aggregation_result.h"

class AvgResult : public AggregationResult
{
public:
  AvgResult()  = default;
  ~AvgResult() = default;

  void        processDate(Value &value) override;
  std::string getResult() override;

private:
  Value valueSum_;
  int   tupleNum_ = 0;
};

class MaxResult : public AggregationResult
{
public:
  MaxResult()  = default;
  ~MaxResult() = default;

  void        processDate(Value &value) override;
  std::string getResult() override;

private:
  Value valueSum_;
};

class MinResult : public AggregationResult
{
public:
  MinResult()  = default;
  ~MinResult() = default;

  void        processDate(Value &value) override;
  std::string getResult() override;

private:
  Value valueSum_;
};

class CountResult : public AggregationResult
{
public:
  CountResult()  = default;
  ~CountResult() = default;

  void        processDate(Value &value) override;
  std::string getResult() override;

private:
  int tupleNum_ = 0;
};
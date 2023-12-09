#pragma once
#include <iostream>
#include "sql/parser/value.h"

class AggregationResult
{
public:
  AggregationResult() = default;
  ~AggregationResult() = default;
  virtual void processDate(Value &value)=0;
  virtual std::string getResult()=0;

private:
};

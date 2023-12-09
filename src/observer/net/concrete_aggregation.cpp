#include "net/concrete_aggregation.h"

void AvgResult::processDate(Value &value)
{
  if (valueSum_.attr_type() == UNDEFINED) {
    valueSum_.set_type(value.attr_type());
  }
  if (valueSum_.attr_type() == INTS) {
    valueSum_.set_int(valueSum_.get_int() + value.get_int());
  }
  if (valueSum_.attr_type() == FLOATS) {
    valueSum_.set_float(valueSum_.get_float() + value.get_float());
  }
  tupleNum_++;
}
std::string AvgResult::getResult()
{
  if (valueSum_.attr_type() == INTS) {
    valueSum_.set_int(valueSum_.get_int() / tupleNum_);
    return valueSum_.to_string();
  }
  if (valueSum_.attr_type() == FLOATS) {
    valueSum_.set_float(valueSum_.get_float() / tupleNum_);
    return valueSum_.to_string();
  }
  return "error";
}
///////////////////////////////////////////////////////////////
void MaxResult::processDate(Value &value)
{
  if (valueSum_.attr_type() == UNDEFINED) {
    valueSum_.set_type(value.attr_type());
    if (valueSum_.attr_type() == INTS) {
      valueSum_.set_int(value.get_int());
    } else {
      valueSum_.set_float(value.get_float());
    }
    return;
  }
  if (valueSum_.attr_type() == INTS) {
    int t1 = valueSum_.get_int();
    int t2 = value.get_int();
    valueSum_.set_int(t1 > t2 ? t1 : t2);
  }
  if (valueSum_.attr_type() == FLOATS) {
    float t1 = valueSum_.get_float();
    float t2 = value.get_float();
    valueSum_.set_float(t1 > t2 ? t1 : t2);
  }
}
std::string MaxResult::getResult()
{
  if (valueSum_.attr_type() == INTS) {
    return valueSum_.to_string();
  }
  if (valueSum_.attr_type() == FLOATS) {
    return valueSum_.to_string();
  }
  return "error";
}
//////////////////////////////////////////////
void MinResult::processDate(Value &value)
{
  if (valueSum_.attr_type() == UNDEFINED) {
    valueSum_.set_type(value.attr_type());
    if (valueSum_.attr_type() == INTS) {
      valueSum_.set_int(value.get_int());
    } else {
      valueSum_.set_float(value.get_float());
    }
    return;
  }
  if (valueSum_.attr_type() == INTS) {
    int t1 = valueSum_.get_int();
    int t2 = value.get_int();
    valueSum_.set_int(t1 < t2 ? t1 : t2);
  }
  if (valueSum_.attr_type() == FLOATS) {
    float t1 = valueSum_.get_float();
    float t2 = value.get_float();
    valueSum_.set_float(t1 < t2 ? t1 : t2);
  }
}

std::string MinResult::getResult()
{
  if (valueSum_.attr_type() == INTS) {
    return valueSum_.to_string();
  }
  if (valueSum_.attr_type() == FLOATS) {
    return valueSum_.to_string();
  }
  return "error";
}
//////////////////////////////////////////////////
void        CountResult::processDate(Value &value) { tupleNum_++; }
std::string CountResult::getResult() { return std::to_string(tupleNum_); }
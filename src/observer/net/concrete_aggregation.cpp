#include "net/concrete_aggregation.h"

void AvgResult::processDate(Value &value)
{
  if (value.attr_type() == CHARS&&value.get_string()=="null") {
    hasNull=true;
    return;
  }
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
  if(hasNull){
    return "NULL";
  }
  return "error";
}
///////////////////////////////////////////////////////////////
void MaxResult::processDate(Value &value)
{
  if (value.attr_type() == CHARS&&value.get_string()=="null") {
    hasNull=true;
    return;
  }
  if (valueSum_.attr_type() == UNDEFINED) {
      valueSum_.set_type(value.attr_type());
      if (valueSum_.attr_type() == INTS) {
        valueSum_.set_int(value.get_int());
      } else if (valueSum_.attr_type() == CHARS) {
        valueSum_.set_string(value.get_string().c_str());
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
    if (valueSum_.attr_type() == CHARS) {
      std::string t1 = valueSum_.get_string();
      std::string t2 = value.get_string();
      valueSum_.set_string((t1 > t2 ? t1 : t2).c_str());
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
    if (valueSum_.attr_type() == CHARS) {
      return valueSum_.to_string();
    }
    if(hasNull){
      return "NULL";
    }
    return "error";
}
//////////////////////////////////////////////
void MinResult::processDate(Value &value)
{
  if (value.attr_type() == CHARS&&value.get_string()=="null") {
    hasNull =true;
    return;
  }
  if (valueSum_.attr_type() == UNDEFINED) {
      valueSum_.set_type(value.attr_type());
      if (valueSum_.attr_type() == INTS) {
        valueSum_.set_int(value.get_int());
      } else if (valueSum_.attr_type() == CHARS) {
        valueSum_.set_string(value.get_string().c_str());
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
    if (valueSum_.attr_type() == CHARS) {
      std::string t1 = valueSum_.get_string();
      std::string t2 = value.get_string();
      valueSum_.set_string((t1 < t2 ? t1 : t2).c_str());
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
    if (valueSum_.attr_type() == CHARS) {
      return valueSum_.to_string();
    }
    if(hasNull){
      return "NULL";
    }
    return "error";
}
//////////////////////////////////////////////////
void        CountResult::processDate(Value &value)
{ 
  if (value.attr_type() == CHARS&&value.get_string()=="null") {
    return;
  }
  tupleNum_++; 
}
std::string CountResult::getResult() { return std::to_string(tupleNum_); }
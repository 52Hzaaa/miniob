
//
// Created by Dom 2023 11 17
//

#pragma once

#include "sql/operator/logical_operator.h"
#include "storage/field/field.h"
#include "sql/parser/parse_defs.h"
/**
 * @brief 逻辑算子，用于执行update语句
 * @ingroup LogicalOperator
 */
class UpdateLogicalOperator : public LogicalOperator
{
public:
  UpdateLogicalOperator(Table *table, Value &value, Field *field);
  virtual ~UpdateLogicalOperator() = default;

  LogicalOperatorType type() const override { return LogicalOperatorType::UPDATE; }
  Table              *table() const { return table_; }
  Field* field() {return field_;};
  Value& value(){return value_;};
private:
  Table *table_ = nullptr;
  Value  value_;
  Field *field_ = nullptr;
};

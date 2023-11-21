

//
// Created by Dom on 2023/11/18.
//

#pragma once

#include "sql/operator/physical_operator.h"
#include "storage/field/field.h"
#include "sql/parser/parse_defs.h"
class Trx;
class UpdateStmt;

/**
 * @brief 物理算子，更新
 * @ingroup PhysicalOperator
 */
class UpdatePhysicalOperator : public PhysicalOperator
{
public:
  UpdatePhysicalOperator(Table *table,Field* field,Value &value) : table_(table),field_(field),value_(value) {}

  virtual ~UpdatePhysicalOperator() = default;

  PhysicalOperatorType type() const override { return PhysicalOperatorType::UPDATE; }

  RC open(Trx *trx) override;
  RC next() override;
  RC close() override;

  Tuple *current_tuple() override { return nullptr; }

private:
  Table *table_ = nullptr;
  Value  value_;
  Field *field_ = nullptr;
  Trx   *trx_   = nullptr;
};

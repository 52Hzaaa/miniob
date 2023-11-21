
//
// Created by Dom 2023 11 17
//

#include "sql/operator/update_logical_operator.h"

UpdateLogicalOperator::UpdateLogicalOperator(Table *table, Value &value, Field *field)
    : table_(table), value_(value), field_(field)
{}

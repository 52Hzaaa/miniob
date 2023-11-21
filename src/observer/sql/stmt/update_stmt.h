//
// Created by dom 2023/11/17
//

#pragma once


#include "common/rc.h"
#include "sql/stmt/stmt.h"
#include "storage/field/field.h"
#include "sql/parser/parse_defs.h"
class FieldMeta;
class FilterStmt;
class Db;
class Table;
/**
 * @brief Update 语句
 * @ingroup Statement
 */
class UpdateStmt : public Stmt
{
public:
  UpdateStmt(Table *table, Value &value, Field *field, FilterStmt *filter_stmt);
  ~UpdateStmt() override;

  Table      *table() const { return table_; }
  FilterStmt *filter_stmt() const { return filter_stmt_; }
  Value       value() const { return value_; }
  Field      *field() const { return field_; }

  StmtType type() const override { return StmtType::UPDATE; }

public:
  static RC create(Db *db, const UpdateSqlNode &update_sql, Stmt *&stmt);

private:
  Table      *table_       = nullptr;  // 更新的表
  Value       value_;  // 更新的值（单个字段）
  Field      *field_       = nullptr;  // 更新的属性（单个属性）
  FilterStmt *filter_stmt_ = nullptr;  // 过滤条件
};

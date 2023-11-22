
//
// Created by Dom on 2023/11/17.
//

#include "common/log/log.h"
#include "sql/stmt/update_stmt.h"
#include "sql/stmt/filter_stmt.h"
#include "storage/db/db.h"
#include "storage/table/table.h"

UpdateStmt::UpdateStmt(Table *table, Value &value, Field *field, FilterStmt *filter_stmt)
    : table_(table), filter_stmt_(filter_stmt), value_(value), field_(field)
{}

UpdateStmt::~UpdateStmt()
{
  if (nullptr != filter_stmt_) {
    delete filter_stmt_;
    filter_stmt_ = nullptr;
  }
}

RC UpdateStmt::create(Db *db, const UpdateSqlNode &update_sql, Stmt *&stmt)
{
  const char *table_name = update_sql.relation_name.c_str();
  if (nullptr == db || nullptr == table_name) {
    LOG_WARN("invalid argument. db=%p, table_name=%p", db, table_name);
    return RC::INVALID_ARGUMENT;
  }

  // check whether the table exists
  Table *table = db->find_table(table_name);
  if (nullptr == table) {
    LOG_WARN("no such table. db=%s, table_name=%s", db->name(), table_name);
    return RC::SCHEMA_TABLE_NOT_EXIST;
  }
  // 设置field

  const FieldMeta *field_meta = table->table_meta().field(update_sql.attribute_name.c_str());
  if (nullptr == field_meta) {
    //LOG_WARN("no such field. field=%s.%s.%s", db->name(), table->name(), field_name);
    return RC::SCHEMA_FIELD_MISSING;
  }
  // 判断设置的value和field是否对应
  if (field_meta->type() != update_sql.value.attr_type()) {
    return RC::INVALID_ARGUMENT;
  }
  Field *field = new Field(table, field_meta);
  // 设置过滤stmt
  std::unordered_map<std::string, Table *> table_map;
  table_map.insert(std::pair<std::string, Table *>(std::string(table_name), table));

  FilterStmt *filter_stmt = nullptr;
  RC rc = FilterStmt::create(
      db, table, &table_map, update_sql.conditions.data(), static_cast<int>(update_sql.conditions.size()), filter_stmt);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to create filter statement. rc=%d:%s", rc, strrc(rc));
    return rc;
  }
  //设置value
  Value value=update_sql.value;
  stmt = new UpdateStmt(table,value, field, filter_stmt);
  return rc;
}

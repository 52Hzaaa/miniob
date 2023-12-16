/* Copyright (c) 2021OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by Wangyunlai on 2022/5/22.
//

#include "sql/stmt/insert_stmt.h"
#include "common/log/log.h"
#include "storage/db/db.h"
#include "storage/table/table.h"

using namespace std;

InsertStmt::InsertStmt(Table *table,  const vector<Value> *records, int value_amount,int record_amount)
    : table_(table), records_(records), value_amount_(value_amount), record_amount_(record_amount)
{}

RC InsertStmt::create(Db *db, const InsertSqlNode &inserts, Stmt *&stmt)
{
  const char *table_name = inserts.relation_name.c_str();
  if (nullptr == db || nullptr == table_name || inserts.records.empty()) {
    LOG_WARN("invalid argument. db=%p, table_name=%p, value_num=%d",
        db, table_name, static_cast<int>(inserts.records.size()));
    return RC::INVALID_ARGUMENT;
  }

  // check whether the table exists
  Table *table = db->find_table(table_name);
  if (nullptr == table) {
    LOG_WARN("no such table. db=%s, table_name=%s", db->name(), table_name);
    return RC::SCHEMA_TABLE_NOT_EXIST;
  }

  // check the fields number
  const int value_num = static_cast<int>(inserts.records[0].size());//值数量
  const int record_num = static_cast<int>(inserts.records.size());//记录数量


  const TableMeta &table_meta = table->table_meta();
  const int field_num = table_meta.field_num() - table_meta.sys_field_num();

  for(int i=0;i<record_num;++i){
    const int tmp = static_cast<int>(inserts.records[i].size());
    if (field_num != tmp) {
      LOG_WARN("schema mismatch. value num=%d, field num in schema=%d", tmp, field_num);
      return RC::SCHEMA_FIELD_MISSING;
    }
  }

  // check fields type
  const int sys_field_num = table_meta.sys_field_num();
  for(int j=0;j<record_num;++j){
    for (int i = 0; i < value_num; i++) {
      const FieldMeta *field_meta = table_meta.field(i + sys_field_num);
      const AttrType field_type = field_meta->type();
      const AttrType value_type = inserts.records[j][i].attr_type();
      bool isNull=inserts.records[j][i].isNull();
      bool nullable=field_meta->nullable();
      //类型不同且不为null
      if (field_type != value_type && !(isNull && nullable) ) {  // TODO try to convert the value type to field type
        LOG_WARN("field type mismatch. table=%s, field=%s, field type=%d, value_type=%d",
            table_name, field_meta->name(), field_type, value_type);
        return RC::SCHEMA_FIELD_TYPE_MISMATCH;
      }
    }
  }
  // everything alright
  stmt = new InsertStmt(table, inserts.records.data(), value_num, record_num);
  return RC::SUCCESS;
}

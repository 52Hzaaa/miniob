
//
// Created by Dom on 2023/10/20.
//
#pragma once

#include "common/rc.h"

class SQLStageEvent;

/**
 * @brief s删除表的执行器
 * @ingroup Executor
 */
class DropTableExecutor
{
public:
  DropTableExecutor()          = default;
  virtual ~DropTableExecutor() = default;

  RC execute(SQLStageEvent *sql_event);
};
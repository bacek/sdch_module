// Copyright (c) 2015 Yandex LLC. All rights reserved.
// Author: Vasily Chekalkin <bacek@yandex-team.ru>

#include "sdch_autoauto_handler.h"

namespace sdch {

AutoautoHandler::AutoautoHandler(RequestContext* ctx, Handler* next)
    : Handler(next) {
  // TODO
}

AutoautoHandler::~AutoautoHandler() {}

bool AutoautoHandler::init(RequestContext* ctx) {
  return true;
}

ssize_t AutoautoHandler::on_data(const char* buf, size_t len) {
  ssize_t res = 0;
  // TODO Implement it
  if (next_)
    res = next_->on_data(buf, len);
  return res;
}

void AutoautoHandler::on_finish() {
  // TODO Implement it
  next_->on_finish();
}

}  // namespace sdch

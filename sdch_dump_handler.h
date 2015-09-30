// Copyright (c) 2015 Yandex LLC. All rights reserved.
// Author: Vasily Chekalkin <bacek@yandex-team.ru>

#ifndef SDCH_DUMP_HANDLER_H_
#define SDCH_DUMP_HANDLER_H_

#include "sdch_handler.h"

namespace sdch {

class RequestContext;

// Dumps data into temporary directory
class DumpHandler : public Handler {
 public:
  DumpHandler(RequestContext* ctx, Handler* next);
  ~DumpHandler();

  bool init(RequestContext* ctx) override;

  ssize_t on_data(const char* buf, size_t len) override;

  void on_finish() override;

 private:
};


}  // namespace sdch

#endif  // SDCH_DUMP_HANDLER_H_


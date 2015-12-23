// Copyright (c) 2015 Yandex LLC. All rights reserved.
// Author: Vasily Chekalkin <bacek@yandex-team.ru>

#include "sdch_config.h"

#include "sdch_dictionary_factory.h"
#include "sdch_module.h"

namespace sdch {

Config::Config(ngx_pool_t* pool)
    : dict_factory(pool_alloc<DictionaryFactory>(pool, pool)) { new(dict_factory) DictionaryFactory(pool);}

Config::~Config() {}

Config* Config::get(ngx_http_request_t* r) {
  return static_cast<Config*>(ngx_http_get_module_loc_conf(r, sdch_module));
}

}  // namespace sdch

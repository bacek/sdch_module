#include <cassert>

#include "sdch_storage.h"

namespace sdch {

Storage::Value::~Value() {}

Storage::Storage() : max_size_(10000000) {}

bool Storage::clear(time_t ts) { return true; }

bool Storage::store(const Dictionary::id_t& key, Value value) {
  auto r = values_.emplace(std::move(key), std::move(value));
  if (!r.second) {
#if 0
        if (r.first->second.ts < ts)
            r.first->second.ts = ts;
#endif
    return false;
  }

  lru_.insert(LRUType::value_type(r.first->second.ts, key));
  total_size_ += r.first->second.dict.size();

  // Remove oldest entries if we exceeded max_size_
  for (auto i = lru_.begin(); total_size_ > max_size_ && i != lru_.end(); ) {
    auto si = values_.find(i->second);
    if (si == values_.end()) {
      assert(0);
      continue;
    }

    if (si->second.locked) {  // XXX
      ++i;
      continue;
    }

    total_size_ -= si->second.dict.size();
    values_.erase(si);
    lru_.erase(i++);
  }

  return true;
}

Storage::ValueHolder Storage::find(const Dictionary::id_t& key) {
  auto i = values_.find(key);
  if (i == values_.end())
    return nullptr;

  i->second.locked = true;

  // TODO Update LRU?
  return std::unique_ptr<Value, Unlocker>(&i->second, Unlocker(this));
}

void Storage::unlock(Value* v) {
  v->locked = false;
}

}  // namespace sdch
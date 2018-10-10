#include "base/std.h"

#include <chrono>

volatile int outoftime = 0;
uint64_t max_eval_cost;

namespace {
    std::chrono::steady_clock::time_point deadline;
}

void set_eval(uint64_t etime) {
  debug_message("p: set_eval(%d)\n",etime);
  if (etime > std::chrono::microseconds::max().count()) {
    etime = std::chrono::microseconds::max().count();
  }
  
  deadline = std::chrono::steady_clock::now() + std::chrono::microseconds(etime);
  outoftime = 0;
}

int64_t get_eval() {
  auto now = std::chrono::steady_clock::now();
  int64_t retval = 0;
  
  if (now < deadline) {
    retval = std::chrono::duration_cast<std::chrono::microseconds>(deadline - now).count();
  }
  debug_message("p: get_eval() returns %d\n",retval);
  return retval;
}

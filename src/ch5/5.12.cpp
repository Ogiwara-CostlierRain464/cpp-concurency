#include "common.h"
#include <vector>
#include <atomic>
#include <iostream>
#include <thread>

namespace {
  std::atomic<bool> x,y;
  std::atomic<int> z;

  void write_x_then_y(){
    x.store(true, std::memory_order_relaxed);
    std::atomic_thread_fence(std::memory_order_release);
    y.store(true, std::memory_order_relaxed);
  }

  void read_y_then_x(){
    while(!y.load(std::memory_order_relaxed));
    std::atomic_thread_fence(std::memory_order_acquire);
    if(x.load(std::memory_order_relaxed)){
      ++z;
    }
  }
}

TEST_F(Ch5, 5_12){
  x = false, y = false;
  z = 0;
  std::thread a(write_x_then_y);
  std::thread b(read_y_then_x);
  std::thread c(write_x_then_y);
  std::thread d(read_y_then_x);

  a.join();
  b.join();
  c.join();
  d.join();

  assert(z.load() != 0);
}
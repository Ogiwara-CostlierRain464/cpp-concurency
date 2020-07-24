#include "common.h"
#include <vector>
#include <atomic>
#include <iostream>
#include <thread>

std::vector<int> data;
std::atomic<bool> data_ready(false);

void reader_thread(){
  while(!data_ready.load(std::memory_order_relaxed)){
    //std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }
  EXPECT_EQ(data[0],42);
}

void writer_thread(){
  data.push_back(42);
  data_ready.store(true, std::memory_order_relaxed);
}


std::string ver_string(int a, int b, int c) {
  std::ostringstream ss;
  ss << a << '.' << b << '.' << c;
  return ss.str();
}

TEST_F(Ch5, 5_2){
  std::thread a(reader_thread);
  std::thread b(writer_thread);

  a.join();
  b.join();
}
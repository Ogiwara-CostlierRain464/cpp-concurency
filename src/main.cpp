#include <gtest/gtest.h>

bool x,y,z,w;

void a(){
  x = true;
  std::atomic_thread_fence(std::memory_order_seq_cst);
  y = true;
}

int main(int argc, char **argv){
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
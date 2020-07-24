#include <atomic>
#include <thread>
#include <iostream>
#include <x86intrin.h>

using namespace std;

atomic<int> x;
atomic<int> y;
int r, s1, s2, s3, t1, t2, t3;
//atomic_bool start;

void w1(){
  //while(!start.load(memory_order_acquire));

  x.store(1, memory_order_relaxed);
  x.store(2, memory_order_seq_cst);
  y.store(1, memory_order_seq_cst);
}

void w2(){
  //while(!start.load(memory_order_acquire));

  x.store(3, memory_order_relaxed);
  y.store(2, memory_order_seq_cst);
}

void w3(){
  //while(!start.load(memory_order_acquire));

  y.store(3, memory_order_seq_cst);
  r = x.load(memory_order_seq_cst);
}

void w4(){
  //while(!start.load(memory_order_acquire));

  s1 = x.load(memory_order_relaxed);
  s2 = x.load(memory_order_relaxed);
  s3 = x.load(memory_order_relaxed);
  t1 = y.load(memory_order_relaxed);
  t2 = y.load(memory_order_relaxed);
  t3 = y.load(memory_order_relaxed);
}

int main(){
  std::thread a(w1);
  std::thread b(w2);
  std::thread c(w3);
  std::thread d(w4);

  //start.store(true, memory_order_release);

  a.join(); b.join();
  c.join(); d.join();

  printf("r: %d, s1: %d, t1: %d,s2: %d, t2: %d, s3: %d, t3: %d\n", r, s1, t1, s2, t2, s3, t3);
}
#include <iostream>
#include <thread>
#include <array>
#include <atomic>
#include <mutex>

std::mutex m;

std::atomic_int atomic_counter = 0;
int counter = 0;
int mutex_counter = 0;

void add_one(size_t n){
	for(size_t i = 0; i < n; i++){
		++counter;

		++atomic_counter;

		std::lock_guard<std::mutex> lock(m);
		++mutex_counter;
	}
}

int main(){
  constexpr size_t n = 10;
  std::array<std::thread, n> threads;

  for(auto& t: threads){
    t = std::thread([](){return add_one(10000);});
  }

   
  for(auto& t: threads){
    t.join();
  }

  std::cout << "Counter: " << counter << '\n';
  std::cout << "Atomic counter: " << atomic_counter << '\n';
  std::cout << "Mutex counter: " << mutex_counter << '\n';
}

#include <iostream>
#include <thread>
#include <array>
#include <chrono>

void hello_lazy(){
  std::this_thread::sleep_for(std::chrono::seconds(1));
	std::cout << "Hello!\n";
}

void hello_work(){
  for(size_t i = 0; i < 1e10; i++){};
	std::cout << "Hello!\n";
}

int main(){
  constexpr size_t n = 10;
  std::array<std::thread, n> threads;

  for(auto& t: threads){
    t = std::thread(hello_work);
  }

  for(auto& t: threads){
    t.join();
  }
}

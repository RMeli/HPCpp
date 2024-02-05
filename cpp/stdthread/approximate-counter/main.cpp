#include <mutex>
#include <chrono>
#include <array>
#include <stdexcept>
#include <thread>
#include <vector>
#include <iostream>

constexpr size_t n = 1e7;
constexpr size_t n_cpus = 4;
constexpr std::array n_threads = {1, 2, 3, 4};

class concurrent_counter_t{
public:

  void operator++(){
    std::lock_guard<std::mutex> lock(m);
    ++counter; 
  }

  void operator--(){
    std::lock_guard<std::mutex> lock(m);
    --counter; 
  }
  
  int count(){
    std::lock_guard<std::mutex> lock(m);
    return counter;
  }

private:
	int counter = 0;
  std::mutex m;
  
};

class concurrent_approximate_counter_t{
public:
  concurrent_approximate_counter_t(int threshold_) : threashold(threshold_){
    std::fill(local_counter.begin(), local_counter.end(), 0);
  }

  void update(int thread_id){
    int cpu = thread_id % n_cpus;

    std::lock_guard<std::mutex> lock(local_mutex[cpu]);
    ++local_counter[cpu];
    if(local_counter[cpu] >= threashold){
      {
        std::lock_guard<std::mutex> lock(m);
        counter += local_counter[cpu];
      }
      local_counter[cpu] = 0;
    }
  }

  int count(){
    std::lock_guard<std::mutex> lock(m);
    return counter;
  }

private:
	int counter = 0;
  std::mutex m;
  std::array<int, n_cpus> local_counter;
  std::array<std::mutex, n_cpus> local_mutex;
  int threashold; // Update frequency
  int thread_id;
};

void count_with_concurrent_counter(concurrent_counter_t& cc){
  for(size_t i = 0; i < n; i++){
    ++cc;
  }
}

void count_with_concurrent_approximate_counter(concurrent_approximate_counter_t& cac, int thread_id){

  for(size_t i = 0; i < n; i++){
    cac.update(thread_id);
  }
}


int main(){
  std::chrono::high_resolution_clock clock;

  concurrent_counter_t cc;
  concurrent_approximate_counter_t cac(1024);

  for(auto nt: n_threads){
    std::vector<std::thread> threads(nt);

    auto start = clock.now();

    for(auto& t: threads){
	    // Need std::ref reference wrapper to make the reference copiable
      t = std::thread(count_with_concurrent_counter, std::ref(cc));
    }
    for(auto& t: threads){
      t.join(); 
    }

    auto duration = clock.now() - start;
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(duration);
  
    if(cc.count() != static_cast<int>(n * nt)){
      std::runtime_error("Wrong result!");
    }
    
    std::cout << "Concurrent counter with " << nt << " threads: " << ms.count() << " ms\n";
    
    start = clock.now();

    for(size_t thread_id = 0; thread_id < threads.size(); thread_id++){
	    // Need std::ref reference wrapper to make the reference copiable
      threads[thread_id] = std::thread(count_with_concurrent_approximate_counter, std::ref(cac), thread_id);
    }

    for(auto& t: threads){
      t.join(); 
    }
    
    duration = clock.now() - start;
    ms = std::chrono::duration_cast<std::chrono::milliseconds>(duration);
    
    if(cac.count() != static_cast<int>(n * nt)){
      std::runtime_error("Wrong result!");
    }
    
    std::cout << "Concurrent approximate counter with " << nt << " threads: " << ms.count() << " ms\n";

  }
}

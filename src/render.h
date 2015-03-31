#pragma once

extern const int window_width;
extern const int window_height;

#include <queue>
#include <thread>
#include <mutex>

extern std::queue<int> renderMessageQueue;
extern std::mutex renderMessageQueueMutex;

namespace renderspace{

  void initialize();
  void  display();


}

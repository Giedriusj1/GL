#pragma once

#include "../render.h"
#include <pthread.h>

class network {

public:
    pthread_t thread;
    // void * task_code();
    network();
    ~network();
};

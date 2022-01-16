#include "network.h"
#include <stdio.h>

#include <chrono>
#include <thread>


void *task_code(void *argument)
{
    int tid;
 
    tid = *((int *) argument);
    while(true){
        printf("Hello World! It's me, thread %d!\n", tid);

        std::this_thread::sleep_for(std::chrono::milliseconds(1));
     
        renderMessageQueueMutex.lock();
        renderMessageQueue.push(123);
     
        renderMessageQueueMutex.unlock();

     
    }
    return NULL;
}

// std::this_thread::sleep_for(std::chrono::milliseconds(x));

// int main(void)
// {
//    pthread_t threads[NUM_THREADS];
//    int thread_args[NUM_THREADS];
//    int rc, i;
 
//    // create all threads one by one
//    for (i=0; i<NUM_THREADS; ++i) {
//       thread_args[i] = i;
//       printf("In main: creating thread %d\n", i);
//       rc = pthread_create(&threads[i], NULL, task_code, (void *) &thread_args[i]);
//       assert(0 == rc);
//    }
 
//    // wait for each thread to complete
//    for (i=0; i<NUM_THREADS; ++i) {
//       // block until thread i completes
//       rc = pthread_join(threads[i], NULL);
//       printf("In main: thread %d is complete\n", i);
//       assert(0 == rc);
//    }
 
//    printf("In main: All threads completed successfully\n");
//    exit(EXIT_SUCCESS);
// }

// pthread_t network::thread;
// int network

network::network(){


    int * thread_args = new int;
    *thread_args = 123;
    pthread_create(&thread, NULL, task_code, (void *) thread_args);
    // rc = pthread_create(&threads[i], NULL, task_code, (void *) &thread_args[i]);
}


network::~network(){
    // pthread_join(thread, NULL);
}

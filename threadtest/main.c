/*  Write one line in main loop, then wait for all threads to be done,
        then write the rest of the lines in main loop.

    This behaviour is unexpected to me. I would expect all of the main
    writes to go through (in the for loop).

*/

#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <semaphore.h>

#define FILENAME "out3.txt"

sem_t mutex;
int timer = 8;

void* thread(void* arg) {
    FILE* fout = fopen(FILENAME, "a");
    sem_wait(&mutex);
    printf("Inside mutex for %d\n", *(int*)arg);

    fprintf(fout, "Hello, World %d!\n", *(int*)arg);
    printf("Hello, World %d!\n", *(int*)arg);

    fclose(fout);
    printf("Exiting mutex for %d\n", *(int*)arg);
    sem_post(&mutex);

    timer--;
    return NULL;
}

int main() {
    // open file in w to delete prev
    FILE* rmfile = fopen(FILENAME, "w");
    fclose(rmfile);

    // create all threads, num array for pointers to pass to thread funcs
    pthread_t t0, t1, t2, t3, t4, t5, t6, t7;
    int nums [8] = {0, 1, 2, 3, 4, 5, 6, 7};

    sem_init(&mutex, 0, 1);

    pthread_create(&t0, NULL, thread, &nums[0]);
    pthread_create(&t1, NULL, thread, &nums[1]);
    pthread_create(&t2, NULL, thread, &nums[2]);
    pthread_create(&t3, NULL, thread, &nums[3]);
    pthread_create(&t4, NULL, thread, &nums[4]);
    pthread_create(&t5, NULL, thread, &nums[5]);
    pthread_create(&t6, NULL, thread, &nums[6]);
    pthread_create(&t7, NULL, thread, &nums[7]);

    int done = 1;

    // timer decremented on thread death, so loop
    // hangs until all threads are done.
    // 
    // on first iteration, do the main writes
    while(timer) {
    
        if (done)  {
            for (int i = 0; i < 4; i++) {
                FILE* fout = fopen(FILENAME, "a");
                sem_wait(&mutex);
                printf("Inside mutex in main %d\n", i);

                fprintf(fout, "Hello, %d from main!\n", i);
                printf("Hello, %d from main!\n", i);

                fclose(fout);
                printf("Exiting mutex in main %d\n", i);
                sem_post(&mutex);
            }
            done = 0;
        }
    }


    sem_destroy(&mutex);

    return 0;
}

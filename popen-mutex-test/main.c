#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>

sem_t mutex;

void* thread(void* filename) {
    // lock sem
    sem_wait(&mutex);
    FILE* f = fopen((char*)filename, "r");

    printf("in lock\n");

    // run python script
    FILE* p = popen("python3 pymain.py", "w");
    sleep(3);

    // release sem
    fclose(f);
    pclose(p);
    sem_post(&mutex);

    printf("out lock\n");

    return NULL;
}



int main() {
    // no stdout buffer
    setbuf(stdout, NULL);

    sem_init(&mutex, 1, 1);
    pthread_t th;

    char filename[10] = ".flag/new";

    // start thread: it immediately locks the semaphore
    pthread_create(&th, NULL, thread, filename);
    
    printf("attempt to open file in main:\n");
    sem_wait(&mutex);
    FILE* f = fopen(filename, "r");
    printf("opened\n");

    // print all lines in file
    char line[100];
    while (fgets(line, sizeof(line), f) != NULL) {
        printf("%s", line);
    }

    // unlock sem
    sem_post(&mutex);
    fclose(f);

    // resolutions
    sem_destroy(&mutex);
    printf("Ending\n");
    return 0;
}

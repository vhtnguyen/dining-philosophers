#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define N 5
#define LEFT (i + N - 1) % N
#define RIGHT (i + 1) % N
#define THINKING 0
#define HUNGRY 1
#define EATING 2

int state[N];
pthread_mutex_t mutex;
pthread_mutex_t s[N];
pthread_t philosophers[N];
int id[N] = {0, 1, 2, 3, 4};
// int id = 0;
int cnt_test = 0;
void think(int i);
void eat(int i);
void test(int i);
void take_forks(int i);
void put_forks(int i);
void *philosopher(void *id);

int main() {
    int i;
    srand(time(NULL));
    pthread_mutex_init(&mutex, NULL);
    for (i = 0; i < N; i++) {
        state[i] = THINKING;
    }
    for (i = 0; i < N; i++) {
        pthread_mutex_init(&s[i], NULL);
    }

    for (i = 0; i < N; i++) {
        pthread_create(&philosophers[i], NULL, philosopher, &id[i]);
    }
    for (i = 0; i < N; i++) {
        pthread_join(philosophers[i], NULL);
    }

    // pthread_exit(NULL);
    return 0;
}

void think(int i) {
    int thinking_time = 1;
    // printf("Philosopher %d begin thingking for %d seconds...\n", i + 1, thinking_time);
    // sleep(thinking_time);
    // printf("Philosopher %d think done\n", i + 1);
    sleep(thinking_time);
}
void eat(int i) {
    // int eat_time = 1;
    int eating_time = rand() % 2 + 1;
    // printf("Philosopher %d begin eating for %d seconds...\n", i + 1, eating_time);
    // sleep(eating_time);
    // printf("Philosopher %d done\n\n", i + 1);
    sleep(eating_time);
}

void test(int i) {
    if (state[i] == HUNGRY && state[LEFT] != EATING && state[RIGHT] != EATING) {
        state[i] = EATING;
        printf("Philosopher %d took from %d and %d then begin EATING...\n", i + 1, LEFT + 1, RIGHT + 1);
        sleep(1);
        pthread_mutex_unlock(&s[i]);
        printf("Philosopher %d ate...\n", i + 1);
    }
    else if (state[i] == EATING) {
        printf("Philosopher %d hasn't put back forks yet...\n", i + 1);
    }
    else {
        printf("Philosopher %d fail to taking forks ...\n", i + 1);
    }
}
void take_forks(int i) {

    pthread_mutex_lock(&mutex);

    state[i] = HUNGRY;
    printf("Philosopher %d is HUNGRY...\n", i + 1);
    test(i);
    pthread_mutex_unlock(&mutex);
    pthread_mutex_lock(&s[i]);
    // printf("Philosopher %d take forks done\n", i + 1);
}

void put_forks(int i) {
    pthread_mutex_lock(&mutex);

    state[i] = THINKING;
    printf("Philosopher %d finished then THINKING...\n\n", i + 1);
    printf("test %d and %d from %d\n", LEFT + 1, RIGHT + 1, i + 1);
    test(LEFT);
    test(RIGHT);
    pthread_mutex_unlock(&mutex);
}

void *philosopher(void *id) {
    // pthread_mutex_lock(&mutex);

    // pthread_mutex_unlock(&mutex);
    while (1) {
        int i = *(int *)id;
        // printf("%d\n", i);
        think(i);
        take_forks(i);
        eat(i);
        put_forks(i);
    }
}

// void *moniter(void *x) {
// }
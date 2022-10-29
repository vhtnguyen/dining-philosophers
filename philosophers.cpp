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
int id = 0;
int cnt_test = 0;
void think(int i);
void eat(int i);
void test(int i);
void take_forks(int i);
void put_forks(int i);
void *philosopher(void *x);

int main() {
    int i;
    pthread_mutex_init(&mutex, NULL);
    for (i = 0; i < N; i++) {
        state[i] = THINKING;
    }
    for (i = 0; i < N; i++) {
        pthread_mutex_init(&s[i], NULL);
    }

    for (i = 0; i < N; i++) {
        pthread_create(&philosophers[i], NULL, philosopher, NULL);
    }
    for (i = 0; i < N; i++) {
        pthread_join(philosophers[i], NULL);
    }

    // pthread_exit(NULL);
    return 0;
}

void think(int i) {
}
void eat(int i) {
    // int eat_time = 1;
    int eat_time = rand() % 3 + 1;
    printf("Philosopher %d begin eating for %d seconds...\n", i + 1, eat_time);
    sleep(eat_time);
    printf("Philosopher %d done\n\n", i + 1);
}

void test(int i) {
    if (state[i] == HUNGRY && state[LEFT] != EATING && state[RIGHT] != EATING) {
        state[i] = EATING;
        pthread_mutex_unlock(&s[i]);
    }
}
void take_forks(int i) {
    pthread_mutex_lock(&mutex);
    state[i] = HUNGRY;
    test(i);
    cnt_test++;
    // if (cnt_test > 20) {
    //     exit(0);
    // }
    pthread_mutex_unlock(&mutex);
    pthread_mutex_lock(&s[i]);
}

void put_forks(int i) {
    pthread_mutex_lock(&mutex);
    state[i] = THINKING;
    test(LEFT);
    test(RIGHT);
    pthread_mutex_unlock(&mutex);
}

void *philosopher(void *x) {
    pthread_mutex_lock(&mutex);
    int i = id;
    id++;
    pthread_mutex_unlock(&mutex);
    while (1) {
        think(i);
        take_forks(i);
        eat(i);
        put_forks(i);
    }
}

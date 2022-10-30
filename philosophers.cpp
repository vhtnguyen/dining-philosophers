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
#define MAXTURN 100 // limited for test
int state[N];
pthread_mutex_t mutex;
pthread_mutex_t s[N];
pthread_t philosophers[N];
pthread_attr_t attributes[N];
int id[N] = {0, 1, 2, 3, 4};
int cnt_turn = 0;

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
    for (i = 0; i < N; ++i) {
        pthread_attr_init(&attributes[i]);
    }

    for (i = 0; i < N; i++) {
        pthread_create(&philosophers[i], &attributes[i], philosopher, &id[i]);
    }
    for (i = 0; i < N; i++) {
        pthread_join(philosophers[i], NULL);
    }
    return 0;
}

void think(int i) {
    int thinking_time = rand() % 2 + 1;
    printf("Philosopher %d THINKING for %d seconds...\n", i + 1, thinking_time);
    sleep(thinking_time);
    printf("Philosopher %d HUNGRY\n", i + 1);
}
void eat(int i) {
    int eating_time = rand() % 2 + 1;
    sleep(eating_time);
}

void test(int i) {
    if (state[i] == HUNGRY && state[LEFT] != EATING && state[RIGHT] != EATING) {
        state[i] = EATING;
        printf("*** Philosopher %d took from %d and %d then begin EATING...\n", i + 1, LEFT + 1, RIGHT + 1);
        pthread_mutex_unlock(&s[i]);
    }
    else if (state[i] == EATING) {
        printf("Philosopher %d is still EATING...\n", i + 1);
    }
    else {
        printf("Philosopher %d fail to taking forks ...\n", i + 1);
    }
}
void take_forks(int i) {
    pthread_mutex_lock(&mutex);
    state[i] = HUNGRY;
    test(i);
    cnt_turn++;
    if (cnt_turn > MAXTURN) {
        exit(0);
    }
    pthread_mutex_unlock(&mutex);
    pthread_mutex_lock(&s[i]);
}

void put_forks(int i) {
    pthread_mutex_lock(&mutex);
    printf("*** Philosopher %d finished EATING...\n", i + 1);
    state[i] = THINKING;
    printf("Philosopher %d puts down forks and then asks his neighbor wonder if they need\n", i + 1);
    test(LEFT);
    test(RIGHT);
    pthread_mutex_unlock(&mutex);
}

void *philosopher(void *id) {
    while (1) {
        int i = *(int *)id;
        think(i);
        take_forks(i);
        eat(i);
        put_forks(i);
    }
}

# About some definitions and variables in this solution

| type              | name     | declared value                | means                                                            |
| ----------------- | -------- | ---------------------------- | ---------------------------------------------------------------- |
| int               | N        | 5                            | number of philosophers                                           |
| int               | LEFT     | (i + N - 1) % N              | philosopher left-side of (i+1)th philosopher                     |
| int               | RIGHT    | i + 1) % N                   | philosopher right-side of (i+1)th philosopher                    |
| int []            | state    | an array of N elements       | state[i]= state of (i+1)th philosopher                           |
| int               | THINKING | 0                            | state of a philosopher is thinking                               |
| int               | HUNGRY   | 1                            | state of a philosopher is hungry                                 |
| int               | EATING   | 2                            | state of a philosopher is eating                                 |
| int               | MAXTURN  | 100                          | limit of eating turn (for testing purpose)                       |
| pthread_mutex_t   | mutex    | 1                            | semaphore protect critical section                               |
| pthread_mutex_t[] | s        | an array of N mutex elements | s[i] = semaphore project critical section of (i+1)th philosopher |

---

pthread_t philosophers[N], pthread_attr_t attributes[N] : For multi-threading in linux.

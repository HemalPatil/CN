static struct sembuf downEmpty = { EMPTY_ID, -1, 0 };
static struct sembuf upEmpty = { EMPTY_ID, 1, 0 };
static struct sembuf upFull = { FULL_ID, 1, 0 };
static struct sembuf downFull = { FULL_ID, -1, 0 };
static struct sembuf downMutex = { MUTEX_ID, -1, 0 };
static struct sembuf upMutex = { MUTEX_ID, 1, 0 };

key_t key = ftok(SEM_KEY, 'E');
  
  int semid = semget(key, NSEM_SIZE, 0600 | IPC_CREAT);
  if (errno > 0) {
    perror("failed to create semaphore array");
    exit (EXIT_FAILURE);
  } 

  semctl(semid, FULL_ID, SETVAL, 0);
  if (errno > 0) {
    perror("failed to set FULL semaphore");
    exit (EXIT_FAILURE);
  }

  semctl(semid, EMPTY_ID, SETVAL, BUFFER_SIZE);
  if (errno > 0) {
    perror("failed to set EMPTY sempahore");
    exit (EXIT_FAILURE);
  }

  semctl(semid, MUTEX_ID, SETVAL, 1);
  if (errno > 0) {
    perror("failed to create mutex");
  }

semop(semid, &downFull, 1);
    semop(semid, &downMutex, 1);
    item = remove_item(semid, shared_buffer);
    debug_buffer(shared_buffer);
    semop(semid, &upMutex, 1);
    semop(semid, &upEmpty, 1);

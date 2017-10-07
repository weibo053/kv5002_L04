#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <assert.h>

int globvar = 6;

void *simple_thr(void *arg) {
      globvar++; 
      // var++; Notice this variable is not accessible
      printf("New thread : pid = %d, tid = 0x%lx, globvar = %d, "
              "var = %s\n", getpid(), (unsigned long)pthread_self(),
              globvar, "Not accessible");
      pthread_exit((void *)(((unsigned long) arg) * 2));
}

int main(void) {
  int rc;
  int var = 88;
  pthread_t thread;
  void *retval;

  printf("before thread create\n");
  rc = pthread_create(&thread, NULL, simple_thr, (void *)42);
  assert(rc == 0);
  pthread_join(thread, &retval);
  printf("Main thread: pid = %d, tid = 0x%lx, globvar = %d, " 
         "var = %d\n", getpid(), (unsigned long)pthread_self(), globvar, var);
  printf("Thread termination status = %ld\n", (unsigned long)retval);
  exit(0);
}


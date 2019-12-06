#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

void* thread1(void *arg);
void* thread2(void *arg);

int count;
sem_t bin_sem; // Semaphore variable

int main() {
	pthread_t a_thread, b_thread;
	int res;
	void* thread_result;

	res = sem_init(&bin_sem, 0, 1);

	res = pthread_create(&a_thread, NULL, thread1, NULL);
	res = pthread_create(&b_thread, NULL, thread2, NULL);

	res = pthread_join(a_thread, &thread_result);
	res = pthread_join(b_thread, &thread_result);

	printf("Count = %d\n", count);

	sem_destroy(&bin_sem);

	return 0;
}

void* thread1(void *arg) {
	for (int i = 0; i < 1000000000; i++) {
		sem_wait(&bin_sem);
		count++;
		sem_post(&bin_sem);
	}
}

void* thread1(void *arg) {
	for (int i = 0; i < 1000000000; i++) {
		sem_wait(&bin_sem);
		count--;
		sem_post(&bin_sem);
	}
}
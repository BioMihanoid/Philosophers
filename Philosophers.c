#include "Philosophers.h"

void* test(void *args)
{
	printf ("test\n");
	return 0;
}

int main(int argc, char **argv)
{
	pthread_t thread;
	int status;
	int status_addr;

	status = pthread_create(&thread, NULL, test, NULL);
	if (status != 0)
	{
		printf("main error: can't create thread, status = %d\n", status);
		exit(-11);
	}
	printf("Hello from main!\n");

	status = pthread_join(thread, (void **)status_addr);
	if (status != 0)
	{
		printf("main error: can't join thread, status = %d\n", status);
		exit(-12);
	}

	printf("joined with address %d\n", status_addr);
}


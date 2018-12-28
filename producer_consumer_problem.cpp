#include "semaphore_in_c++.cpp"
#include <iostream>
#include <thread>
#define BUFFER_SIZE 10
using namespace std;
/*
P =decress the value of semaphore
V = incress the valueo f semaphore

Semaphore init value:
exclusive_mutex=0; empty=10; full=0;

Producer:
P(empty)
P(exclusive_mutex)
Produce
V(exclusive_mutex)
V(full)

Consumer:
P(full)
P(exclusive_mutex)
Consume
V(exclusive_mutex)
V(empty)

*/
int buffer[BUFFER_SIZE];

mutex mutex_exclusive;
semaphore sem_full(0);
semaphore sem_empty(BUFFER_SIZE);

void producer()
{
	int BUFFER_COUNTER=BUFFER_SIZE;
	while(BUFFER_COUNTER)
	{
		sem_empty.wait();
			mutex_exclusive.lock();
				cout<<"Producing "<<BUFFER_COUNTER<<endl;
				buffer[BUFFER_COUNTER-1]=BUFFER_COUNTER;
				BUFFER_COUNTER--;
			mutex_exclusive.unlock();
		sem_full.notify();
	}
}

void consumer()
{
	int BUFFER_COUNTER=BUFFER_SIZE;
	while(BUFFER_COUNTER)
	{
		sem_full.wait();
			mutex_exclusive.lock();
				cout<<"\t\t Consuming "<<buffer[BUFFER_COUNTER-1]<<endl;
				BUFFER_COUNTER--;
			mutex_exclusive.unlock();
		sem_empty.notify();
	}
}

int main()
{	
	thread 	t_producer(&producer);
	thread 	t_consumer(&consumer);
	t_producer.join();
	t_consumer.join();	
}

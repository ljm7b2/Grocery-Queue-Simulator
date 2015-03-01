#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
using namespace std;

template<class T>
class Queue
{
public:
	Queue(){ size = 0; }

	Queue(T theData, Queue<T>* theLink)
		: data(theData), link(theLink) {}

	Queue<T>* getLink() const { return link; }

	const T getData() const{ return data; }

	void setData(const T& theData) { data = theData; }

	void setLink(Queue<T>* pointer){ link = pointer; }

	void enqueue(T item);

	T dequeue();

	void addToFront(T item);

	bool isEmpty() const{ return size == 0; }

	int getSize(){ return size; }

	void clear();

	void displayQ();

	T seeTop();

	
	//big three
	~Queue(){ clear(); }
	
	const Queue<T>& operator = (const Queue<T>& rhs);
	
	Queue(const Queue<T>& rhs);

private:
	int size;

	T data;

	Queue<T> *link;

	Queue<T> *front; //points to items at the head

	Queue<T> *back; //points to items at the end
};

template<class T>
void Queue<T>::enqueue(T item)
{
	if (size == 0)
	{
		front = back = new Queue<T>(item, NULL);
	}
	else
	{
		back->link = new Queue<T>(item, NULL);
		back = back->link;
	}
	size++;
}

template<class T>
void Queue<T>::addToFront(T item)
{
	Queue<T> *P = new Queue<T>(item, NULL);
	P->link = front;
	front = P;
	size++;
	if (size == 1)
		back = front;

}

template<class T>
T Queue<T>::seeTop()
{
	T thing = dequeue();

	addToFront(thing);

	return thing;

	
}

template<class T>
T Queue<T>::dequeue()
{
	if (size == 0)
	{
		cout << "ERROR: Removing an Item from An Empty Queue.";
		system("PAUSE");
		exit(1);
	}

	T result = front->data;

	Queue<T> *discard;

	discard = front;

	front = front->link;

	delete discard;
	size--;

	if (front == NULL)
	{
		back = NULL;
	}
	return result;
}

template<class T>
void Queue<T>::clear()
{
	Queue<T> *pointer = front;

	while (front != NULL)
	{
		front = front->link;
		delete pointer;
		pointer = front;
	}
	back = NULL;
	size = 0;
}

template<class T>
const Queue<T>& Queue<T>::operator = (const Queue<T>& rhs)
{
	Queue<T>* pointer;

	if (this != &rhs)
	{
		clear();
		pointer = rhs.front;

		while (pointer != NULL)
		{
			enqueue(pointer->data);
			pointer = pointer->link;
		}
	}
	return *this;
}

template<class T>
Queue<T>::Queue(const Queue<T>& rhs)
{
	*this = rhs;
}


template<class T>
void Queue<T>::displayQ()
{
	Queue<T>* pointer;

	pointer = front;

	while (pointer != NULL)
	{
		cout << pointer->data << ' ';
		pointer = pointer->link;
	}

	delete pointer;
}
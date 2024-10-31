#ifndef _QUEUE_H_
#define _QUEUE_H_
#include <stdio.h>
#include "Car.h"
#define QueueElem Car
struct QueueUnit{
	QueueElem elem;
	QueueUnit* next;
};
struct Queue{
	QueueUnit *head, *rear;
	int size;
	Queue():head(NULL),rear(NULL){}
	void Push(const QueueElem);
	void Pop(QueueElem&);
	bool Search(const QueueElem);
	int calculate(void);
};
#endif /* Queue.h */
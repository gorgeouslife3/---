#include "Queue.h"

/**
 * @return:		elem
 * @brief:		push the elem into the queue
 */
void Queue::Push(const QueueElem elem){
	QueueUnit *p;
	p = new QueueUnit;
	p->elem = elem;
	p->next = NULL;
	if (head == NULL) {
		head = p;
		rear = p;
	}
	else {
	rear->next = p;
	rear = p;
	}
}//无头结点的队列

/**
 * @return:		elem
 * @brief:		pop the front element
 */
void Queue::Pop(QueueElem& elem){
	if(head==NULL) return ;
	QueueUnit *p = head;
	elem = p->elem;
	head = p->next;
	if(rear == p) rear = head;
	delete p;
	//TODO: Fill your code here.
}

bool Queue::Search(const QueueElem elem_){
	if(head == NULL) return false;
	QueueUnit *p = head;
	while(p != NULL)
	{
		if(p->elem.Plate == elem_.Plate)
		return true;
		p = p->next;
	}
	return false;
}

int Queue::calculate(void){
	if(head == NULL) return 0;
	int i=0;
	QueueUnit *p = head;
	while(p != NULL)
	{
		p=p->next;
		i++;
	}
	return i;
}
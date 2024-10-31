#ifndef _STACK_H_
#define _STACK_H_
#include <stdio.h>
#include "Car.h"
#define StackElem Car
struct Stack{
	StackElem *elem;
	int size,rear;
	Stack(int n) : size(n), rear(0) {
		elem = new StackElem[n];
		// TODO: distribute memory to elem.
	}
	void Push(const StackElem);
	void Pop(StackElem&);
	bool Search(const StackElem);
};
#endif /* Stack.h */
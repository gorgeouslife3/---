#include "Stack.h"

/**
 * @return:		elem
 * @brief:		push the elem into the stack
 */
void Stack::Push(const StackElem elem_){
	rear++;
	elem[rear] = elem_;
	//TODO: Fill your code here.
}

/**
 * @return:		elem
 * @brief:		pop the top element
 */
void Stack::Pop(StackElem& elem_){
	elem_ = elem[rear];
	rear--;
	//TODO: Fill your code here.
}

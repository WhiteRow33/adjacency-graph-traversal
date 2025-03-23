#include <iostream>
#include "DynamicIntStack.h"
using namespace std;

DynamicIntStack::DynamicIntStack()
{
	top=nullptr;
}

StackNode* DynamicIntStack::GetTopPointer(DynamicIntStack myStack)
{
	return myStack.top;
}

//Push back elements to the stack
void DynamicIntStack::push(int elmt)
{
	StackNode *newNode;

	newNode = new StackNode;
	newNode->value = elmt;

	if(isEmpty())
	{
		top = newNode;
		newNode->next = nullptr;
	}
	else
	{
		newNode->next = top;
		top = newNode;
	}
}

//Pop up elements from the stack
void DynamicIntStack::pop(int &elmt)
{
	StackNode *temp;

	if(isEmpty())
	{
		cout<<"Stack is empty!\n";
	}

	else 
	{
		elmt = top->value;
		temp = top->next;
		delete top;
		top = temp;
	}
}



//If the stack is empty check function
bool DynamicIntStack::isEmpty()
{
	bool status;

	if(top==nullptr)
		status=true;

	else 
		status=false;

	return status;
}

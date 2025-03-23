#ifndef DYNAMICINTSTACK_H
#define DYNAMICINTSTACK_H

using namespace std;

struct StackNode
{
	int value;
	StackNode *next;
};


class DynamicIntStack
{
	private:
		StackNode *top;
		StackNode* GetTopPointer(DynamicIntStack myStack);

	public:
		DynamicIntStack(void);
		void push(int);
		void pop(int &);
		bool isEmpty(void);
};


#endif
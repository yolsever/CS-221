
#include "Stack.h"

Stack::Stack(int size) {
  top = -1;
	MAX_SIZE = size;
	data = new MazeLocation [size];
}

bool Stack::isEmpty() const {
  return (top == -1);
}

bool Stack::isFull() const {
	return top == MAX_SIZE - 1;
}

Stack::~Stack() {
	delete[] data;
}

void Stack::push(MazeLocation m) {
	if ( isFull()) return;

	top++;

	data[top] = m;
}

void Stack::pop() {
	if (isEmpty()) {
		return;
	}

	top --;
}

void Stack::printTop() {
	if (isEmpty()) {
		return;
	}

	cout << data[top];
}


/**
 *
 * CPSC 221 Summer 2018
 * Array-based stack
 *
 */

#ifndef _STACK_H_
#define _STACK_H_

#include "MazeLocation.h"

/**
 * Stack: This is a container class for MazeLocation elements. 
 * You should not remove anything from this class definition.
 */

class Stack {
  public:

	/**
     * Stack constructor.
     * Creates an array with size 'size' to hold MazeLocation items.     * 
     */
	Stack(int size);

	/**
 	 * Determines if the current Stack is empty
	 * const because it promises not to modify the current Stack.
	 *
	 * @return Boolean value of whether the current Stack is empty.
	 */
	bool isEmpty() const;

	/**
 	 * Determines if the current Stack is full
	 * const because it promises not to modify the current Stack.
	 *
	 * @return Boolean value of whether the current Stack is full.
	 */
	bool isFull() const;

    /**
     * Stack destructor.
     * Destroys all of the memory associated with the
     * current stack. This function should ensure that
     * memory does not leak on destruction of a stack.
     */
	~Stack();

	/**
     * Inserts a new item on to the top of the current stack.
     *
     * @param m The element to be inserted.
     */
	void push(MazeLocation m);

	/**
     * Removes an item from the top of the current stack.
     *
     * @param m The element to be inserted.
     */
	void pop();

	/**
     * Prints the MazeLocation at the top of the stack.
     */
	void printTop();

private:
   /**
    * Private member variables.    *
    * You must use these as specified in the spec and may not rename them.
	*/
    MazeLocation* data;
    int MAX_SIZE;
    int top;
};

#endif


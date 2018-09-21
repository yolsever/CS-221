
/**
 *
 * CPSC 221 Summer 2018
 * Doubly Linked List (PA 1)
 * with head and tail pointers.
 *
 */

#ifndef _CHAIN_H_
#define _CHAIN_H_

#include <algorithm>
#include <iostream>
#include "block.h"
using namespace std;

/**
 * Chain: This is a container class for blocks. It is implemented
 * as a linked list of nodes, each of which contains a block.
 *
 * You should not remove anything from this class definition, but
 * you will find it helpful to add your own private helper functions to it.
 */

class Chain {
private:

   /**
    * The Node class is private to the List class via the principle of
    * encapsulation---the end user does not need to know our node-based
    * implementation details.
    */
   class Node {
   public:
      Node(); // default constructor--GIVEN
      Node(const Block & ndata); // data provided constructor--GIVEN

      Node * next; // pointer to next node in chain if one exists, or NULL
      Node * prev; // pointer to prev node in chain if one exists, or NULL
      const Block data; // data held by Node. must stay const for this assignment
   };

public:

   /* =============== public given functions ====================*/
   /**
    * Default Chain constructor. GIVEN
    * Creates an empty Chain. Implemented for you.
    * @see chain_given.cpp
    */
   Chain();

   /**
    * Constructor that breaks the given PNG into
    * rows x cols blocks and builds a chain of those
    * blocks. This constructor is GIVEN
    * @see chain_given.cpp
    */
   Chain(PNG & imIn, int rows, int cols);

   /**
    * Copy constructor for a Chain. GIVEN
    * Since Chains allocate dynamic memory (i.e., they use "new", we
    * must define the Big Three). This depends on your implementation
    * of the copy funtion.
    * @see chain_given.cpp
    *
    * @param other The Chain  we are copying.
    */
   Chain(const Chain & other);

   /**
    * Overloaded assignment operator for Chains. GIVEN
    * Part of the Big Three that we must define because the class
    * allocates dynamic memory. This depends on your implementation
    * of the copy and clear funtions.
    * @see chain_given.cpp
    *
    * @param rhs The right hand side of the assignment statement.
    */
   Chain & operator=(const Chain & rhs);

   /**
    * Gets the size of the Chain. GIVEN
    * Defined as a const function because it promises not to modify
    * the current Chain in any way.
    * @see chain_given.cpp
    *
    * @return The number of data elements in the current Chain.
    */
   int size() const;

   /**
    * Determines if the current Chain is empty. GIVEN
    * Const because it promises not to modify the current Chain.
    * @see chain_given.cpp
    *
    * @return Boolean value of whether the current Chain is empty.
    */
   bool empty() const;

   /**
    * Render returns an image consisting of the first rows *
    * cols blocks in the chain. Returns an empty image if
    * the chain is too short. GIVEN
    * @see chain_given.cpp
    */
   PNG render(int rows, int cols);

   /* =============== end of given functions ====================*/

   /* =============== public PA1 FUNCTIONS =========================*/

   /**
    * Chain destructor.
    * Destroys all of the memory associated with the
    * current Chain. This function should ensure that
    * memory does not leak on destruction of a chain.
    */
   ~Chain();

   /**
    * Inserts a new node at the front of the Chain.
    * This function **SHOULD** create one new Node.
    *
    * @param ndata The data to be inserted.
    */
   void insertFront(const Block & ndata);

   /**
    * Inserts a new node at the back of the List.
    * This function **SHOULD** create one new Node.
    *
    * @param ndata The data to be inserted.
    */
   void insertBack(const Block & ndata);
   
   /**
    * Returns a pointer to the block data at 
	* nth position in the list. Does not modify
	* the List in any way.
	*
	* @param n The index of the node to grab block data from
	* @return Pointer to block (that cannot be modified) at index n
	*/
   const Block* getBlock(int n);
   
   /**
    * Removes the node at the front of the List.
	*  **ENSURE** a memory leak does not occur.
    */
   void removeFront();
   
   /**
    * Removes the node at the back of the List.
	* **ENSURE** a memory leak does not occur.
    */
   void removeBack();

   /**
    * Removes the nth node in the list and replaces it with a new Node. 
	* Function **SHOULD** create one new node and **ENSURE** a memory 
	* leak does not occur replacing former node.
	*
	* @param n index of node being replaced
	* @param newB The data to be inserted into new Node.
    */
   void replaceBlock(int n, const Block& newB);
   
   /**
    * Modifies the Chain by moving a contiguous subset to the end of the
    * chain. The subset of len nodes from startPos are moved so
    * that they occupy the last len positions of the chain. Their
    * order is not changed in the moxve.
	*
	* @param startPos Index of first node to be moved
	* @param len Number of nodes in a row to be moved
    */
   void moveToBack(int startPos, int len);
   
   /**
    * Rotates the current Chain by k nodes: removes the first
    * k nodes from the Chain and attaches them, in order, at
    * the end of the chain.
	*
	* @param k Number of nodes to be rotated
    */
   void rotate(int k);

   /**
    * Modifies the current chain by swapping the Node at pos1
    * with the Node at pos2. the positions are 1-based.
	*
	* @param pos1 index of first node to be swapped
	* @param pos2 index of second node to be swapped
    */
   void swap(int pos1, int pos2);

   /**
    * Modifies both the current and input chains by swapping
    * nodes in even positions between chains. The length of 
    * each chain stays the same. Function fails if block sizes 
	* are different: cout << "Block sizes differ." << endl;
	*
	* @param other Chain to swap nodes with
    */  
   void checkeredSwap(Chain &other);
   

   /* =============== end of public PA1 FUNCTIONS =========================*/

private:
   /*
    * Private member variables.
    *
    * You must use these as specified in the spec and may not rename them.
    * You may add more if you need them.
    */

   Node* head_; // ptr to the node at front of chain
   Node* tail_; // ptr to the node at end of chain

   int length_; // count of data elements in chain. 

   /*
    * Private helper functions.
    *
    * You must use these as specified in the spec and may not rename them.
    * You may place more functions here as you need them.
    */

   /* =================== private given functions ============== */

   /**
	* Returns a pointer to the node in the kth position of the list.
	* beyond curr. It effectively walks forward k steps from curr.
	* You may use this function in your solutions
	* to the PA1 functions. GIVEN in chain_given.cpp.
	*/
	Node * walk(Node * curr, int k);


   /* =================== end of private given functions ============== */

   /* =================== private PA1 functions ============== */

   /**
    * Destroys all dynamically allocated memory associated with the
    * current Chain class. Complete for PA1.
    */
   void clear();

   void swapTwo(Node * & node1, Node * & node2);

   /**
   * Copies the parameter other Chain into the current Chain.
   * Does not free any memory. Called by copy constructor and op=.
   * @param other The Chain to be copied.
   */
   void copy(const Chain & other);
	Node * copyHelper(Node * other, Node * prev); //remove for provided
   /* =================== end of private PA1 functions ============== */
};

#endif


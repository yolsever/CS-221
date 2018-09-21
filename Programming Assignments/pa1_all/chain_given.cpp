
#include "chain.h"

/* no-argument constructor */
Chain::Chain() : length_(0) {
	head_ = NULL;
	tail_ = NULL;
}

/**
 * Constructor you will likely use most often. 
 * requires implementation of insertBack.
 * Builds a chain out of the blocks in the
 * given image. The blocks we create
 * have width equal to imIn.width()/cols,
 * and height equal to imIn.height()/rows.
 */
Chain::Chain(PNG & imIn, int rows, int cols){

	int width = imIn.width()/cols;
	int height = imIn.height()/rows;

	length_ = 0;
	head_ = NULL;
	tail_ = NULL;

	for (int i = 0; i < rows; i++){
		for (int j = 0; j < cols; j++){
			Block b;
			b.build(imIn , j*width, i*height, width, height);
			insertBack(b);
		}
	}
}

/* Accessor for the length of the chain. */
int Chain::size() const {
	return length_;
}

/* copy constructor */
Chain::Chain(Chain const& other) {
	copy(other);
}

/* assignment operator */
Chain & Chain::operator=(Chain const& rhs) {
	if (this != &rhs) {
		clear(); // you'll implement clear
		copy(rhs);
	}
	return *this;
}

/* checks for empty list */
bool Chain::empty() const {
   return length_ == 0;
}

/**
 * Takes the current chain and renders it into a
 * correctly sized PNG. The Blocks in the Chain
 * are placed in the image across each row,
 * top to bottom. If the chain is not long enough
 * to create a PNG with the right number of rows
 * and columns, the message "Chain is too short."
 * is printed and an empty PNG is returned.
 *
 * For simplicity, it is assumed all Blocks have
 * the same dimensions (height and width), as the
 * data in the first Node of the Chain.
 */
PNG Chain::render(int rows, int cols){

	PNG retVal;
	int width, height;

	if (rows * cols <= length_){
		width = head_->data.width();
		height = head_->data.height();
		retVal.resize(cols*width,rows*height);
		Node * curr = head_;
		for (int i = 0; i < rows; i++){
			for (int j = 0; j < cols; j++){   
				curr->data.render(retVal, j*width, i*height);
				curr = curr->next;
			}
		}
	} else {
		cout << "Chain is too short." << endl;
	}
	return retVal;
}


typename Chain::Node * Chain::walk(Node * curr, int k){

   if (k < 0) {
	   return NULL;
   } else if (k == 0 || curr->next == NULL)
      return curr;
   else
      return walk(curr->next,k-1);
}

void Chain::clear() {
   while (head_ != NULL) {
	   Node* temp = head_-> next;
	   delete head_;
	   head_ = temp;
   }
}

void Chain::copy(Chain const& other) {
   head_=copyHelper(other.head_,NULL);
   Node * curr = head_;
   while (curr->next != NULL) {
      curr = curr->next;
   }
   tail_ = curr;	
   length_ = other.length_;
}

typename Chain::Node * Chain::copyHelper(Node * other,Node * prev){
   Node * curr;
   if (other == NULL)
      curr = NULL;
   else{
      curr = new Node(other->data);
      curr->next = copyHelper(other->next,curr);
      curr->prev = prev;
   }
   return curr;
}

// Node constructors
Chain::Node::Node() : next(NULL), prev(NULL), data(Block()){}

Chain::Node::Node(const Block& ndata) : next(NULL), prev(NULL), data(ndata){}

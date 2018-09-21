#include "chain.h"
#include "chain_given.cpp"

// PA1 functions you need to implement:

Chain::~Chain(){
	clear();
	length_ = 0;
}

void Chain::insertFront(const Block & ndata){
	Node* nBlock = new Node(ndata);
	length_++;
	if(head_ != NULL){
		head_->prev = nBlock;
		nBlock->next = head_;
		head_ = nBlock;
	}
	else {
		cout << "setting head" << endl;
		head_ = nBlock;
		tail_ = nBlock;
		}
}

void Chain::insertBack(const Block & ndata){
	length_++;
   	Node* nBlock = new Node(ndata);
if(tail_ != NULL){
	tail_->next = nBlock;
	nBlock->prev = tail_;
	tail_ = nBlock;
}
else {
	head_ = nBlock;
	tail_ = nBlock;
}
}

const Block* Chain::getBlock(int index) {
	if(head_ != NULL){
	Node* cur = head_;}
	if(index > length_ - 1){
		return NULL;
	}
	else {
	Node* cur = walk(head_,index);
	return &cur->data;
	}
}

void Chain::removeFront() {
	if(head_ != NULL){
		if(head_->next != NULL){
	Node* second = head_->next;
	delete head_;
	second->prev = NULL;
	head_ = second;
	}
else{
	clear();
}
length_ = length_ - 1;
}
}

void Chain::removeBack(){
	if(tail_ != NULL){
		if(tail_->prev != NULL){
		Node* onebefore = tail_->prev;
		onebefore->next = NULL;
		delete tail_;
		tail_ = onebefore;
			}
		else{
			clear();
		}
	}
	length_=length_-1;
}

void Chain::replaceBlock(int index, const Block& newB) {
	if(index > length_-1){
		cout << "replaceBlock index too high" << endl;
	}
	else{
	Node* nBlock = new Node(newB);
	Node *cur = walk(head_,index);
	cur->prev->next = nBlock;
	cur->next->prev = nBlock;
	nBlock->next = cur->next;
	nBlock->prev = cur->prev;
	delete cur;
}
}

void Chain::swap(int pos1, int pos2){
	 if (pos1 == pos2)  return;

	 Node * node1 = walk (head_, pos1);
	 Node * node2 = walk (head_, pos2);

	 swapTwo(node1, node2);
}

void Chain::swapTwo(Node * & node1, Node * & node2) {
	Node * node1_prev = node1 -> prev;
	Node * node1_next = node1 -> next;
	Node * node2_prev = node2 -> prev;
  Node * node2_next = node2 -> next;

	node1-> next = node2_next;

	if (node2_next!=NULL) {
		node2_next->prev = node1;
	}

	node1->prev = node2_prev;

	if (node2_prev!=NULL) {
		node2_prev->next = node1;
	}

	node2->next = node1_next;

	if (node1_next!=NULL) {
		node1_next -> prev = node2;
	}

	node2->prev = node1_prev;

	if (node1_prev!=NULL) {
		node1_prev->next = node2;
	}

}


void Chain::checkeredSwap(Chain &other) {
	if (head_->data.height() != other.head_->data.height() ||
      head_->data.width()  != other.head_->data.width()) {

		std::cout << "Block sizes differ." << endl;
		return;
	}

	//assume length of the chains are equal
		Node* node1 = walk(head_,0);
		Node* node2 = walk(other.head_, 0);
		swapTwo(node1,node2);

		while (1) {
			node1 = walk(node1, 2);
			node2 = walk(node2, 2);
			if ((node1!=NULL and node2!=NULL)
					and (node1->next != NULL and node2->next != NULL)){
						swapTwo(node1,node2);
					} else {
						break;
					}
		}
}

void Chain::moveToBack(int startPos, int len){
		Node * lead = walk(head_, startPos);
		Node * end = walk(lead, len - 1);

		if (lead == end){
			if (lead == head_) {
					head_ = lead -> next;
					head_ -> prev = NULL;
			} else {
					lead -> prev -> next = lead -> next;
					lead -> next -> prev = lead -> prev;
			}

			tail_ -> next = lead;
			lead -> prev = tail_;
			tail_ = lead;
			tail_ -> next = NULL;

		} else {

			if (lead == head_) {
					head_ = end -> next;
					head_ -> prev = NULL;
			} else {
					lead -> prev -> next = end -> next;
					end -> next -> prev = lead -> prev;
			}

			tail_ -> next = lead;
			lead -> prev = tail_;
			tail_ = end;
			tail_ -> next = NULL;


		}
}

void Chain::rotate(int k){
   moveToBack(0, k);

}
/*
void Chain::swap(int pos1, int pos2){
	if(pos1,pos2 < length_){
	Node* toSwap1 = walk(head_,pos1);
	Node* toSwap2 = walk(head_,pos2);
	toSwap1->next = toSwap2->next;
}
}

void Chain::checkeredSwap(Chain &other){
}

void Chain::moveToBack(int startPos, int len){



	/*
	if(tail_ != NULL){
		Node* tail = tail_;
	}

	if(head_ = NULL){
		cout << "-moveToBack-chain is empty" << endl;
		return;
	}
	else if(startPos+len <= length_){
		Node* head = walk(head_,startPos+len);
		for(int i =0; i<len; i++){
		Node* startingNode = walk(head_,startPos);
		Node* rightAfter = startingNode->next;
		Node* rightBefore = startingNode->prev;
		startingNode->prev = tail_;
		if(i=len){
		startingNode->next = NULL;
	}
		else {startingNode->next = rightAfter;
		}
		if(rightAfter != NULL && rightBefore != NULL){
		rightBefore->next = rightAfter;
		rightAfter->prev = rightBefore;
	}
		tail_->next = startingNode;
		}
		if(startPos == 0 && startPos+len < length_+1){
		head_ = head;
		}
	}

	else{
		cout << "-moveToBack-Chain is not long enough to do that";
	}
	*/
	/*)
	}
	

void Chain::rotate(int k){
   if(k <= length_){
   	if(head_ != NULL){
	for(int i=0; i<k; i++){
		Node* rightAfter = head_->next;
		head_->prev = tail_;
		head_->next = NULL;
		tail_->next = head_;

		head_ = rightAfter;
		rightAfter->prev = NULL;
		
	}
		}
}
else {
	cout << "-rotate-Chain is too short" << endl;
}
*/


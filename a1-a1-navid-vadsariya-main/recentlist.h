/*******************************************************************/
/*                                                                 */
/*  A1 Part 2: RecentList starter file                             */
/*                                                                 */
/*  Author1 Name: Navid Najarali Vadsariya		 				   */
/*      - class/function list/main author or main checker          */
/*                                                                 */
/*******************************************************************/
#include<iostream>

template <typename T>
//class RecentList
class RecentList{
	struct Node{
		T data_;
		Node* next_;
		Node* prev_;
		Node(const T& data=T{},Node* nx=nullptr,Node* pr=nullptr){
			data_ = data;
			next_ = nx;
			prev_ = pr;
		}
	};
	Node* front_;
	Node* back_;

public:
	class const_iterator{
		friend class RecentList<T>;
		Node* curr_;
		const RecentList<T>* myList_;
		const_iterator(Node* curr, const RecentList<T>* theList)
		{
			curr_ = curr;
			myList_ = theList;
		}
	public:
		const_iterator(){
			myList_ = nullptr;
			curr_ = nullptr;
		}
		const_iterator operator++(){
			curr_ = curr_->next_;
			return *this;
		}
		const_iterator operator++(int){
			const_iterator old = *this;
			curr_ = curr_->next_;
			return old;
		}
		const_iterator operator--(){
			if (curr_) {
				curr_ = curr_->prev_;
			}
			else {
				if (myList_) {
					curr_ = myList_->back_;
				}
			}
			return *this;
		}
		const_iterator operator--(int){
			const_iterator old = *this;
			if (curr_) {
				curr_ = curr_->prev_;
			}
			else {
				if (myList_) {
					curr_ = myList_->back_;
				}
			}
			return old;
		}
		bool operator==(const_iterator rhs){
			bool rc = false;
			if (myList_ == rhs.myList_ && curr_ == rhs.curr_) {
				rc = true;
			}
			return rc;
		}
		bool operator!=(const_iterator rhs){
			return !(*this == rhs);
		}
		const T& operator*()const{
			return curr_->data_;
		}
	};
	class iterator:public const_iterator{
		friend class RecentList<T>;
		iterator(Node* curr, RecentList<T>* theList) :const_iterator(curr, theList)
		{
		}
	public:
		iterator() :const_iterator() {}
		iterator operator++(){
			this->curr_ = this->curr_->next_;
			return *this;
		}
		iterator operator++(int){
			iterator old = *this;
			this->curr_ = this->curr_->next_;
			return old;
		}
		iterator operator--(){
			if (this->curr_) {
				this->curr_ = this->curr_->prev_;
			}
			else {
				if (this->myList_) {
					this->curr_ = this->myList_->back_;
				}
			}
			return *this;
		}
		iterator operator--(int){
			iterator old = *this;
			if (this->curr_) {
				this->curr_ = this->curr_->prev_;
			}
			else {
				if (this->myList_) {
					this->curr_ = this->myList_->back_;
				}
			}
			return old;
		}
		T& operator*(){
			return this->curr_->data_;
		}
		const T& operator*()const{
			return this->curr_->data_;
		}
	};
	RecentList();
	~RecentList();
	RecentList(const RecentList& rhs);
	RecentList& operator=(const RecentList& rhs);
	RecentList(RecentList&& rhs);
	RecentList& operator=(RecentList&& rhs);
	iterator begin(){
		return iterator(front_->next_, this);
	}
	iterator end(){
		return iterator(back_, this);
	}
	const_iterator cbegin() const{
		return const_iterator(front_->next_, this);
	}
	const_iterator cend() const{
		return const_iterator(back_, this);
	}
	void insert(const T& data);
	iterator search(const T& data);
	iterator erase(iterator it);
	iterator erase(iterator first, iterator last);
	bool empty() const;
	int size() const;
};
//constructor
template <typename T>
RecentList<T>::RecentList(){
	front_ = new Node();
	back_ = new Node();
	front_->next_ = back_;
	back_->prev_ = front_;
}
//destructor
template <typename T>
RecentList<T>::~RecentList(){
	while (front_->next_ != back_) {
		if (front_->next_ != back_) {
			Node* rm = front_->next_;
			Node* B = rm->next_;
			front_->next_ = B;
			B->prev_ = front_;
			delete rm;
		}
	}
	front_ = nullptr;
	back_ = nullptr;
}
//copy constructor
template <typename T>
RecentList<T>::RecentList(const RecentList& rhs){
	*this = rhs;
}
//copy assignment operator
template <typename T>
RecentList<T>& RecentList<T>::operator=(const RecentList& rhs){
	front_ = new Node();
	back_ = new Node();
	front_->next_ = back_;
	back_->prev_ = front_;

	Node* prev = front_;
	const_iterator it;
	for (it = rhs.cbegin(); it != rhs.cend(); it++) {

		Node* node = new Node(it.curr_->data_, back_, prev);
		prev->next_ = node;
		prev = node;
	}
	return *this;
}
//move constructor
template <typename T>
RecentList<T>::RecentList(RecentList&& rhs){
	front_ = new Node();
	back_ = new Node();
	*this = std::move(rhs);
}
//move operator
template <typename T>
RecentList<T>& RecentList<T>::operator=(RecentList&& rhs){
	front_->next_ = rhs.front_->next_;
	front_->next_->prev_ = front_;
	back_->prev_ = rhs.back_->prev_;
	back_->prev_->next_ = back_;

	rhs.front_->next_ = rhs.back_;
	rhs.back_->prev_ = rhs.front_;
	return *this;
}

//inserts node in front
template <typename T>
void RecentList<T>::insert(const T& data){
	Node* nn = new Node(data, front_->next_, front_);
	front_->next_->prev_ = nn;
	front_->next_ = nn;
}
//searches data and returns it
template <typename T>
typename RecentList<T>::iterator RecentList<T>::search(const T& data){
	bool found = false;
	iterator it;
	
	for (it = begin(); it != end() && !found; it++) {
		if (it.curr_->data_ == data) {
			found = true;
		}
	}
	it--;
	if (found) {

		Node* prev = it.curr_->prev_;
		Node* next = it.curr_->next_;

		prev->next_ = next;
		next->prev_ = prev;

		it.curr_->next_ = front_->next_;
		it.curr_->prev_ = front_;
		
		front_->next_->prev_ = it.curr_;
		front_->next_ = it.curr_;

		return it;
	}
	return end();
}
//removes node and returns it
template <typename T>
typename RecentList<T>::iterator RecentList<T>::erase(iterator it){
	
	Node* nodeToDelete = it.curr_;

	Node* prev = nodeToDelete->prev_;
	Node* next = nodeToDelete->next_;

	prev->next_ = next;
	next->prev_ = prev;

	delete nodeToDelete;

	it.curr_ = next;

	return it;

}
//removes node from first to last. Does not remove last node
template <typename T>
typename RecentList<T>::iterator RecentList<T>::erase(iterator first, iterator last){

	Node* nodeToDelete = first.curr_;
	nodeToDelete->prev_->next_ = last.curr_;
	last.curr_->prev_ = nodeToDelete->prev_;

	Node* temp = nodeToDelete->next_;
	while (temp != last.curr_) {
		delete nodeToDelete;
		nodeToDelete = temp;
		temp = temp->next_;
	}
	return last;
}
//returns true if list is empty
template <typename T>
bool RecentList<T>::empty() const{
	return this->front_->next_ == this->back_;
}
//returns size
template <typename T>
int RecentList<T>::size() const{
	int size = 0;
	Node* temp = front_->next_;
	while (temp != nullptr && temp != back_)
	{
		temp = temp->next_;
		size++;
	}
	return size;
}

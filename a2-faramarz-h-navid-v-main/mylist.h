/*******************************************************/
/*                                                     */
/*  Put your linked list code from A1/lab3/lab4 into   */
/*  this file                                          */
/*                                                     */
/*******************************************************/
#include<iostream>
#include <typeinfo>

template <typename T>
//class RecentList
class RecentList
{
	struct Node
	{
		T data_;
		std::string key_;
		Node* next_;
		Node* prev_;
		Node(const T& data = T{}, Node* nx = nullptr, Node* pr = nullptr)
		{
			data_ = data;
			next_ = nx;
			prev_ = pr;
		}
	};
	
	Node* front_;
	Node* back_;
public:

	class const_iterator
	{
		friend class RecentList<T>;
		
		const RecentList<T>* myList_;
		const_iterator(Node* curr, const RecentList<T>* theList)
		{
			curr_ = curr;
			myList_ = theList;
		}
		Node* curr_;
	public:
	//default constructor
		const_iterator()
		{
			myList_ = nullptr;
			curr_ = nullptr;
		}
	//returns current
		Node* getCurrent() {
			return curr_;
		}
	//returns incremented value
		const_iterator operator++()
		{
			curr_ = curr_->next_;
			return *this;
		}
	//returns currents and then increments
		const_iterator operator++(int)
		{
			const_iterator old = *this;
			curr_ = curr_->next_;
			return old;
		}
		//returns decremented value 
		const_iterator operator--()
		{
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
		//reuturns current and then decrements
		const_iterator operator--(int)
		{
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
		//returns true if lhs equal rhs
		bool operator==(const_iterator rhs)
		{
			bool rc = false;
			if (myList_ == rhs.myList_ && curr_ == rhs.curr_) {
				rc = true;
			}
			return rc;
		}
		//retuns bool depending if lhs != rhs
		bool operator!=(const_iterator rhs)
		{
			return !(*this == rhs);
		}
		const T& operator*()const
		{
			return curr_->data_;
		}
	};
	class iterator :public const_iterator
	{
		friend class RecentList<T>;
		iterator(Node* curr, RecentList<T>* theList) :const_iterator(curr, theList)
		{
		}
	public:
	//default constructor 
		iterator() :const_iterator() {}
	//returns current
		Node* getCurrent() {
			return const_iterator::curr_;
		}
		//returns incremented value
		iterator operator++()
		{
			this->curr_ = this->curr_->next_;
			return *this;
		}
		//returns currents and then increments
		iterator operator++(int)
		{
			iterator old = *this;
			this->curr_ = this->curr_->next_;
			return old;
		}
			//returns decremented value 
		iterator operator--()
		{
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
			//reuturns current and then decrements
		iterator operator--(int)
		{
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
		T& operator*()
		{
			return this->curr_->data_;
		}
		const T& operator*()const
		{
			return this->curr_->data_;
		}
		//updates value in current
		void updateValue(const T& value)
		{
			this->curr_->data_ = value;
		}
		//returns current value
		const T& getValue()
		{
			return this->curr_->data_;
		}
	};
	//default constructor
	RecentList();
	//destructor
	~RecentList();
	//copy constructor
	RecentList(const RecentList& rhs);
	//copy assignment operator
	RecentList& operator=(const RecentList& rhs);
	//move constructor
	RecentList(RecentList&& rhs);
	//move assignment operator
	RecentList& operator=(RecentList&& rhs);
	//returns first node
	iterator begin()
	{
		return iterator(front_->next_, this);
	}
	//returns last node
	iterator end()
	{
		return iterator(back_, this);
	}
	//returns const iterator to first node 
	const_iterator cbegin() const
	{
		return const_iterator(front_->next_, this);
	}
	//returns const iterator to last node 
	const_iterator cend() const
	{
		return const_iterator(back_, this);
	}
	//inserts node
	void insert(const T& data, const std::string& key);
	//returns iterator if data is found
	iterator search(std::string data);
	//removes node it
	iterator erase(iterator it);
	//removes nodes from first to last. not including last
	iterator erase(iterator first, iterator last);
	//returns true if empty
	bool empty() const;
	//returns size
	int size() const;
	//prints string format for node(used for debugging)
	std::string getStr()
	{
		std::string str;
		if (front_ != nullptr && front_->next_ != nullptr) {

			Node* temp = front_->next_;
			while (temp != nullptr && temp != back_)
			{
				std::cout << temp->key_  << ":" << temp->data_ << ",";
				temp = temp->next_;
			}
		}
		return str;
	}


};
//constructor
template <typename T>
RecentList<T>::RecentList()
{
	front_ = new Node();
	back_ = new Node();
	front_->next_ = back_;
	back_->prev_ = front_;
}
//destructor
template <typename T>
RecentList<T>::~RecentList()
{
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
RecentList<T>::RecentList(const RecentList& rhs)
{
	*this = rhs;
}
//copy assignment operator
template <typename T>
RecentList<T>& RecentList<T>::operator=(const RecentList& rhs)
{
	if (this != &rhs) {

		while (front_->next_ != back_) {
			if (front_->next_ != back_) {
				Node* rm = front_->next_;
				Node* B = rm->next_;
				front_->next_ = B;
				B->prev_ = front_;
				delete rm;
			}
		}

		front_ = new Node();
		back_ = new Node();
		front_->next_ = back_;
		back_->prev_ = front_;

		Node* prev = front_;
		const_iterator it;
		for (it = rhs.cbegin(); it != rhs.cend(); it++) {

			Node* node = new Node(it.curr_->data_, back_, prev);
			node->key_ = it.curr_->key_;
			prev->next_ = node;
			prev = node;
		}
	}
	return *this;
}
//move constructor
template <typename T>
RecentList<T>::RecentList(RecentList&& rhs)
{
	//front_ = new Node();
	//back_ = new Node();
	*this = std::move(rhs);
}
//move operator
template <typename T>
RecentList<T>& RecentList<T>::operator=(RecentList&& rhs)
{
	while (front_ != nullptr)
	{
		Node* next = front_;
		front_ = front_->next_;
		delete next;
	}
	//then copy the new nodes
	if (rhs.front_ == nullptr)
	{
		front_ = nullptr;
		back_ = nullptr;
	}
	else {
		front_ = new Node();
		Node* rhsNext = rhs.front_->next_;
		Node* temp = front_;
		while (rhsNext != nullptr)
		{
			
			temp->next_ = new Node(rhsNext->data_);
			temp->next_->key_ = rhsNext->key_;
			temp->next_->prev_ = temp;
			temp = temp->next_;
			rhsNext = rhsNext->next_;
		}
		back_ = temp;
	}
	return *this;
}

//inserts node in front
template <typename T>
void RecentList<T>::insert(const T& data, const std::string& key)
{
	Node* nn = new Node(data, front_->next_, front_);
	nn->key_ = key;
	front_->next_->prev_ = nn;
	front_->next_ = nn;
}

//searches data and returns it
template <typename T>
typename RecentList<T>::iterator RecentList<T>::search(std::string key)
{
	iterator it;
	for (it = begin(); it != end(); it++) {
		if (it.curr_->key_ == key) {
			return it;
		}
	}
	return end();
}
//removes node and returns it
template <typename T>
typename RecentList<T>::iterator RecentList<T>::erase(iterator it)
{

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
typename RecentList<T>::iterator RecentList<T>::erase(iterator first, iterator last)
{
	RecentList<T>::iterator iter;
	bool goBack = false;
	Node* temp = nullptr;
	//the loop doesn't need an increment as the deleted nodes point to the next node
	for (iter = first; iter != last;) {
		iter.curr_->prev_->next_ = iter.curr_->next_;
		iter.curr_->next_->prev_ = iter.curr_->prev_;
		temp = iter.curr_;
		iter.curr_ = temp->next_;
		delete temp;
	}
	return iter;
}
//returns true if list is empty
template <typename T>
bool RecentList<T>::empty() const
{
	return this->front_->next_ == this->back_;
}
//returns size
template <typename T>
int RecentList<T>::size() const
{
	int size = 0;
	if (front_ != nullptr && front_->next_ != nullptr) {

		Node* temp = front_->next_;
		while (temp != nullptr && temp != back_)
		{
			temp = temp->next_;
			size++;
		}
	}
	return size;
}

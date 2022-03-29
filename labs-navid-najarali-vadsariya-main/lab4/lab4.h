#include <iostream>

template <typename T>
class DList
{
	struct Node
	{
		T data_;
		Node* next_;
		Node* prev_;
		Node(const T& data = T{}, Node* next = nullptr, Node* prev = nullptr)
		{
			data_ = data;
			next_ = next;
			prev_ = prev;
		}
	};
	Node* front_;
	Node* back_;
public:
	DList()
	{
		front_ = nullptr;
		back_ = nullptr;
	}
	void push_front(const T& data);
	~DList();

	class const_iterator
	{
		Node* curr_;
		friend class DList;
		const DList* myList_;
		const_iterator(Node* n, const DList* theList)
		{
			curr_ = n;
			myList_ = theList;
		}
	public:
		const_iterator()
		{
			curr_ = nullptr;
			myList_ = nullptr;
		}
		const_iterator operator++()
		{
			curr_ = curr_->next_;
			return *this;
		}
		const_iterator operator++(int)
		{
			const_iterator old = *this;
			curr_ = curr_->next_;
			return old;
		}
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
		bool operator==(const_iterator rhs)
		{
			bool rc = false;
			if (myList_ == rhs.myList_ && curr_ == rhs.curr_) {
				rc = true;
			}
			return rc;
		}
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
		friend class DList;
		iterator(Node* curr, DList* theList) :const_iterator(curr, theList)
		{
		}
	public:
		iterator() :const_iterator() {};
		iterator operator++()
		{
			this->curr_ = this->curr_->next_;
			return *this;
		}
		iterator operator++(int)
		{
			iterator old = *this;
			this->curr_ = this->curr_->next_;
			return old;
		}
		iterator operator--()
		{
			if (this->curr_) {
				this->curr_ = this->curr_->prev_;
			}
			else {
				if (this->myList_) {
					this->curr_ = this->myList->back_;
				}
			}
			return *this;
		}
		iterator operator--(int)
		{
			iterator old = *this;
			if (this->curr_) {
				this->curr_ = this->curr_->prev_;
			}
			else {
				if (this->myList_) {
					this->curr_ = this->myList->back_;
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

	};
	const_iterator cbegin() const
	{
		return const_iterator(front_, this);
	}
	iterator begin()
	{
		return iterator(front_, this);
	}
	const_iterator cend() const
	{
		return const_iterator(nullptr, this);
	}
	iterator end()
	{
		return iterator(nullptr, this);
	}
};


template <typename T>
void DList<T>::push_front(const T& data)
{
	Node* nn = new Node(data, front_);
	if (front_ != nullptr)
	{
		front_->prev_ = nn;
	}
	else
	{
		back_ = nn;
	}
	front_ = nn;
}


template <typename T>
DList<T>::~DList()
{
	while (front_ != nullptr)
	{
		if (front_ != nullptr) {
			Node* rm = front_;
			front_ = rm->next_;
			if (front_ != nullptr) {
				front_->prev_ = nullptr;
			}
			else {
				back_ = nullptr;
			}
			delete rm;
		}
	}
	front_ = nullptr;
	back_ = nullptr;
}
template <typename T>
class Sentinel
{
	struct Node
	{
		T data_;
		Node* next_;
		Node* prev_;
		Node(const T& data = T{}, Node* next = nullptr, Node* prev = nullptr)
		{
			data_ = data;
			next_ = next;
			prev_ = prev;
		}
	};
	Node* front_;
	Node* back_;
public:
	Sentinel()
	{
		front_ = new Node();
		back_ = new Node();
		front_->next_ = back_;
		back_->prev_ = front_;
	}
	void push_front(const T& data);
	~Sentinel();

	class const_iterator
	{
		friend class Sentinel<T>;
		Node* curr_;
		const Sentinel<T>* myList_;
		const_iterator(Node* curr, const Sentinel<T>* theList)
		{
			curr_ = curr;
			myList_ = theList;
		}
	public:
		const_iterator()
		{
			myList_ = nullptr;
			curr_ = nullptr;
		}
		const_iterator operator++()
		{
			curr_ = curr_->next_;
			return *this;
		}
		const_iterator operator++(int)
		{
			const_iterator old = *this;
			curr_ = curr_->next_;
			return old;
		}
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
		bool operator==(const_iterator rhs)
		{
			bool rc = false;
			if (myList_ == rhs.myList_ && curr_ == rhs.curr_) {
				rc = true;
			}
			return rc;
		}
		bool operator!=(const_iterator rhs)
		{
			return !(*this == rhs);
		}
		const T& operator*()const { return curr_->data_; }
	};
	class iterator :public const_iterator
	{
		friend class Sentinel<T>;
		iterator(Node* curr, Sentinel<T>* theList) :const_iterator(curr, theList)
		{
		}
	public:
		iterator() :const_iterator() {};
		iterator operator++()
		{
			this->curr_ = this->curr_->next_;
			return *this;
		}
		iterator operator++(int)
		{
			iterator old = *this;
			this->curr_ = this->curr_->next_;
			return old;
		}
		iterator operator--()
		{
			if (this->curr_) {
				this->curr_ = this->curr_->prev_;
			}
			else {
				if (this->myList_) {
					this->curr_ = this->myList->back_;
				}
			}
			return *this;
		}
		iterator operator--(int)
		{
			iterator old = *this;
			if (this->curr_) {
				this->curr_ = this->curr_->prev_;
			}
			else {
				if (this->myList_) {
					this->curr_ = this->myList->back_;
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
	};
	const_iterator cbegin() const
	{
		return const_iterator(front_->next_, this);
	}
	iterator begin()
	{
		return iterator(front_->next_, this);
	}
	const_iterator cend() const
	{
		return const_iterator(back_, this);
	}
	iterator end()
	{
		return iterator(back_, this);
	}
};


template <typename T>
void Sentinel<T>::push_front(const T& data)
{
	Node* nn = new Node(data, front_->next_, front_);
	front_->next_->prev_ = nn;
	front_->next_ = nn;
}


template <typename T>
Sentinel<T>::~Sentinel()
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

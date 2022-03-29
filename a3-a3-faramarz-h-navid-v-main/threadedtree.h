#include <iostream>
using namespace std;

template <class T>
class ThreadedTree
{
	struct Node
	{

		T data_;						//stores data
		Node* left_;					//pointer to left
		Node* right_;					//pointer to right
		bool threadedRight = false;		//true if node is threaded right 
		bool threadedLeft = false;		//true if node is threaded left 

		//constructor with 3 arguments
		Node(const T& data = T{}, Node* left = nullptr, Node* right = nullptr)
		{
			data_ = data;
			left_ = left;
			right_ = right;
		}
	};

	Node* root_;
	int size_;

	//prints tree
	void print(const Node* rt, int lvl) const
	{
		//This function won't be tested, but you may find it useful to implement this so
		//that you can see what the tree looks like.  lvl will allow you to use dashes to
		//better show shape of tree.  Feel free to modify this to print in any way that will
		//help you debug.  Feel free to copy the pretty print function from lab 8 that will draw
		//the tree (though it won't draw threads)
	}

	//Tries to insert a new node recursively and accepts a data to insert and a node to start from
	void recursiveInsert(const T& data, Node* node)
	{
		//if the data is less than the node's data
		if (data < node->data_) {
			//Check if the left of the node is empty
			if (node->left_ == nullptr) {
				//create a new node at the left of the node with the data and set its right to point to the node and make it right threaded
				node->left_ = new Node(data);
				node->left_->right_ = node;
				node->left_->threadedRight = true;
			}
			//Check if the node is left threaded
			else if (node->threadedLeft) {
				//Create a node at the left of the node and set its left to the node's left and its right to the node and make it left and right threaded
				node->left_ = new Node(data, node->left_, node);
				node->left_->threadedLeft = true;
				node->left_->threadedRight = true;
				node->threadedLeft = false;
			}
			//if non of the above were true  then call the function and pass in the left of the node
			else {
				recursiveInsert(data, node->left_);
			}
		}
		//if the data is greater than the node's data
		else {
			//Check if the right of the node is empty
			if (node->right_ == nullptr) {
				//create a new node at the right of the node with the data and set its left to point to the node and make it left threaded
				node->right_ = new Node(data);
				node->right_->left_ = node;
				node->right_->threadedLeft = true;
			}
			//Check if the node is right threaded
			else if (node->threadedRight) {
				//Create a node at the right of the node and set its left to the node and its right to the node's right and make it left and right threaded
				node->right_ = new Node(data, node, node->right_);
				node->right_->threadedLeft = true;
				node->right_->threadedRight = true;
				node->threadedRight = false;
			}
			//if non of the above were true  then call the function and pass in the right of the node
			else {
				recursiveInsert(data, node->right_);
			}
		}
	}


public:
	class const_iterator
	{
	protected:
		Node* curr_;
		const ThreadedTree<T>* myTree_;

	public:

		//constructor
		const_iterator()
		{
			curr_ = nullptr;
			myTree_ = nullptr;
		}

		//constructor with 2 argument
		const_iterator(Node* curr, const ThreadedTree<T>* tree)
		{
			curr_ = curr;
			myTree_ = tree;
		}

		//pre increment operator. This operator advances to next biggest value in the tree if the iterator is not the biggest
		const_iterator operator++(int)
		{
			const_iterator ret = *this;
			//if curr is not end of tree find next biggest
			if (curr_ != this->myTree_->cend().curr_)
			{
				//if current is threaded right set current to its right
				if (curr_->threadedRight)
				{
					curr_ = curr_->right_;
				}
				else
				{
					//move right
					curr_ = curr_->right_;
					//move to left as much possible until threaded left is true and this curr to find next biggest
					while (this->curr_ && !curr_->threadedLeft)
					{
						curr_ = curr_->left_;
					}
				}
			}
			return ret;
		}

		//pre decrement operator. This operator goes to next smallest value in the tree if the iterator is not the smallest
		const_iterator operator--(int)
		{
			const_iterator ret = *this;
			//curr is not null
			if (this->curr_) {
				//checks if curr is not the first node
				if (this->curr_ != this->myTree_->cbegin().curr_)
				{	//set curr to left if threadedLeft is true	
					if (this->curr_->threadedLeft)
					{
						this->curr_ = this->curr_->left_;
					}
					else
					{	//move left
						this->curr_ = this->curr_->left_;
						//move right as much possible until threadedRight is true to find next smallest
						while (!this->curr_->threadedRight)
						{
							this->curr_ = this->curr_->right_;
						}
					}
				}
			}
			else {
				Node* temp = this->myTree_->root_;
				//find the extreme right node
				while (temp->right_ != nullptr)
				{
					temp = temp->right_;
				}
				ret.curr_ = temp;
				this->curr_ = temp;
			}
			return ret;
		}

		//post increment operator. This operator advances to next biggest value in the tree if the iterator is not the biggest
		const_iterator operator++()
		{	//if curr is not end of tree find next biggest
			if (curr_ != this->myTree_->cend().curr_)
			{	//if current is threaded right set current to its right
				if (curr_->threadedRight)
				{
					curr_ = curr_->right_;
				}
				else
				{	//move right
					curr_ = curr_->right_;
					//move to left as much possible until threaded left to find next biggest is true and this curr
					while (this->curr_ && !curr_->threadedLeft)
					{
						curr_ = curr_->left_;
					}
				}
			}
			return *this;
		}

		//post decrement operator. This operator goes to next smallest value in the tree if the iterator is not the smallest
		const_iterator operator--()
		{	//curr is not null
			if (this->curr_) {
				//checks if curr is not the first node
				if (this->curr_ != this->myTree_->cbegin().curr_)
				{	//set curr to left if threadedLeft is true	
					if (this->curr_->threadedLeft)
					{
						this->curr_ = this->curr_->left_;
					}
					else
					{	//move left
						this->curr_ = this->curr_->left_;
						//move right as much possible until threadedRight is true to find next smallest
						while (!this->curr_->threadedRight)
						{
							this->curr_ = this->curr_->right_;
						}
					}
				}
			}
			else {
				Node* temp = this->myTree_->root_;
				//find the extreme right node
				while (temp->right_ != nullptr)
				{
					temp = temp->right_;
				}
				this->curr_ = temp;
			}
			return *this;
		}

		//returns const reference to data in current node
		const T& operator*() const
		{
			return curr_->data_;
		}

		//returns true if rhs and current object refer to the same node
		bool operator==(const const_iterator& rhs) const
		{
			return curr_ == rhs.curr_;
		}

		//returns true if rhsand current object does not refer to the same node
		bool operator!=(const const_iterator& rhs) const
		{
			return curr_ != rhs.curr_;
		}

		friend class ThreadedTree;
	};
	class iterator : public const_iterator
	{
	public:

		//The default construcctor that uses the const_iterator constructor
		iterator() : const_iterator() {}

		//The two argument construcctor that uses the const_iterator constructor and passes curr and tree to it
		iterator(Node* curr, const ThreadedTree<T>* tree) : const_iterator(curr, tree) {}

		// * operator returns the constant data in the current node
		const T& operator*() const
		{
			return this->curr_->data_;
		}

		// * operator returns the data in the current node
		T& operator*()
		{
			return this->curr_->data_;
		}

		//++ postfix operator returns an iterator to the current node and points the current node to the next biggest node
		iterator operator++(int)
		{
			//keeping the current node
			iterator ret = *this;

			// if the current node is not pointing to the end of the tree
			if (this->curr_ != this->myTree_->cend().curr_)
			{
				//if the current node is right threaded then it's poining to the next biggest
				if (this->curr_->threadedRight)
				{
					this->curr_ = this->curr_->right_;
				}

				//if not go right once and then go as much left as possible
				else
				{
					this->curr_ = this->curr_->right_;
					while (this->curr_ && !this->curr_->threadedLeft)
					{
						this->curr_ = this->curr_->left_;
					}
				}
			}
			return ret;
		}

		//-- postfix operator returns an iterator to the the current node and points the current node to the next smallest node
		iterator operator--(int)
		{
			//keeping the current node
			iterator ret = *this;
			//current shouldn't be nullptr as it could be if we are at the end of the tree
			if (this->curr_) {
				// if the current node is not pointing to the beginning of the tree
				if (this->curr_ != this->myTree_->cbegin().curr_)
				{
					//if the current node is left threaded then it's poining to the next smallest
					if (this->curr_->threadedLeft)
					{
						this->curr_ = this->curr_->left_;
					}

					//if not go left once and then go as much right as possible
					else
					{
						this->curr_ = this->curr_->left_;
						while (!this->curr_->threadedRight)
						{
							this->curr_ = this->curr_->right_;
						}
					}
				}
			}

			//if current is nullptr point to the last node
			else {
				Node* temp = this->myTree_->root_;
				while (temp->right_ != nullptr)
				{
					temp = temp->right_;
				}
				ret.curr_ = temp;
				this->curr_ = temp;
			}
			return ret;
		}

		//++ prefix operator points the current node to the next biggest node and returns itself
		iterator operator++()
		{
			// if the current node is not pointing to the end of the tree
			if (this->curr_ != this->myTree_->cend().curr_)
			{
				//if the current node is right threaded then it's poining to the next biggest
				if (this->curr_->threadedRight)
				{
					this->curr_ = this->curr_->right_;
				}

				//if not go right once and then go as much left as possible
				else
				{
					this->curr_ = this->curr_->right_;
					while (this->curr_ && !this->curr_->threadedLeft)
					{
						this->curr_ = this->curr_->left_;
					}
				}
			}
			return *this;
		}

		//-- prefix operator points the current node to the next smallest node and returns itself
		iterator operator--()
		{
			//current shouldn't be nullptr as it could be if we are at the end of the tree
			if (this->curr_) {
				// if the current node is not pointing to the beginning of the tree
				if (this->curr_ != this->myTree_->cbegin().curr_)
				{
					//if the current node is left threaded then it's poining to the next smallest
					if (this->curr_->threadedLeft)
					{
						this->curr_ = this->curr_->left_;
					}

					//if not go left once and then go as much right as possible
					else
					{
						this->curr_ = this->curr_->left_;
						while (!this->curr_->threadedRight)
						{
							this->curr_ = this->curr_->right_;
						}
					}
				}
			}
			//if current is nullptr point to the last node
			else {
				Node* temp = this->myTree_->root_;
				while (temp->right_ != nullptr)
				{
					temp = temp->right_;
				}
				this->curr_ = temp;
			}
			return *this;
		}

		friend class ThreadedTree;
	};

	//TreadedTree default constructor
	ThreadedTree()
	{
		root_ = nullptr;
		size_ = 0;
	}

	//Inserts data into the tree
	void insert(const T& data)
	{
		//adds to the size
		size_++;

		//if the tree is empty insert at root
		if (empty())
			root_ = new Node(data);

		//if not call recursiveInsert and pass in the data and the root
		else
			recursiveInsert(data, root_);
	}

	//find function. This functions find the key and returns iterator to that node else returns end()
	iterator find(const T& key)
	{
		Node* curr = root_;
		bool found = false;
		iterator it = end();
		//loop till the key is not found or curr is nullptr
		while (!found && curr)
		{
			//if key found the set flag to true and it to curr
			if (key == curr->data_)
			{
				found = true;
				it.curr_ = curr;

			}
			//if key is smaller than curr data and curr is not left threaded then move left. If the key is present in the tree it will be on left side
			else if (key < curr->data_ && !curr->threadedLeft)
			{
				curr = curr->left_;
			}
			//if key is greater than curr data and curr is not right threaded then move right. If the key is present in the tree it will be on right side
			else if (curr->data_ < key && !curr->threadedRight)
			{
				curr = curr->right_;
			}
			//if the program reaches this else then it means that key does not exists in the tree and found is set to true in order to stop the loop
			else {
				found = true;
			}
		}
		return it;
	}

	//find function. This functions find the key and returns const iterator to that node else returns end()
	const_iterator find(const T& key) const
	{
		Node* curr = root_;
		bool found = false;
		const_iterator it = cend();
		//loop till the key is not found or curr is nullptr
		while (!found && curr)
		{
			//if key found the set flag to true and it to curr
			if (key == curr->data_)
			{
				found = true;
				it.curr_ = curr; 
			}
			//if key is smaller than curr data and curr is not left threaded then move left. If the key is present in the tree it will be on left side
			else if (key < curr->data_ && !curr->threadedLeft)
			{
				curr = curr->left_;
			}
			//if key is greater than curr data and curr is not right threaded then move right. If the key is present in the tree it will be on right side
			else if (curr->data_ < key && !curr->threadedRight)
			{
				curr = curr->right_;
			}
			//if the program reaches this else then it means that key does not exists in the tree and found is set to true in order to stop the loop
			else {
				found = true;
			}
			
		}
		return it;
	}

	//returns an iterator to the beginning of the tree
	iterator begin()
	{
		//if the tree is empty return an iterator to the root
		if (empty())
		{
			return iterator(root_, this);
		}

		//else go as left as possible
		else
		{
			Node* temp = root_;
			while (temp->left_ != nullptr)
			{
				temp = temp->left_;
			}
			return iterator(temp, this);
		}
	}

	//returns an iterator to the end of the tree
	iterator end()
	{
		//if the tree is empty return an iterator to the root
		if (empty())
		{
			return iterator(root_, this);
		}

		//else go as right as possible
		else
		{
			Node* temp = root_;
			while (temp != nullptr)
			{
				temp = temp->right_;
			}
			return iterator(temp, this);
		}
	}

	//returns a const_iterator to the beginning of the tree
	const_iterator cbegin() const
	{
		//if the tree is empty return a const_iterator to the root
		if (empty())
		{
			return const_iterator(root_, this);
		}
		//else go as left as possible
		else
		{
			Node* temp = root_;
			while (temp->left_ != nullptr)
			{
				temp = temp->left_;
			}
			return const_iterator(temp, this);
		}
	}

	//returns a const_iterator to the end of the tree
	const_iterator cend() const
	{
		//if the tree is empty return a const_iterator to the root
		if (empty())
		{
			return const_iterator(root_, this);
		}

		//else go as right as possible
		else
		{
			Node* temp = root_;
			while (temp != nullptr)
			{
				temp = temp->right_;
			}
			return const_iterator(temp, this);
		}
	}

	void print() const
	{
		//this function won't be tested, but you may wish to implement this
		//to help you debug.  You won't need to implement this for submission
	}

	//returns number of values stored in tree
	int size() const
	{
		return size_;
	}

	//returns true if tree is empty
	bool empty() const
	{
		return root_ == nullptr;
	}

	//destructor
	~ThreadedTree()
	{
		destroyTree(root_);
	}

	//helper function for destructor
	void destroyTree(Node* subroot_)
	{	//starts deleting if the tree is not empty
		if (subroot_)
		{
			//performs recursive call to destroyTree function with left node
			if (subroot_->left_ && !subroot_->threadedLeft)
			{
				destroyTree(subroot_->left_);
			}
			//performs recursive call to destroyTree function with right node
			if (subroot_->right_ && !subroot_->threadedRight) {
				destroyTree(subroot_->right_);
			}
			delete subroot_;
		}
	}
};


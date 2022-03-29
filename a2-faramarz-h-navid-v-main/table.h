/*************************************************************/
/*                                                           */
/*  Starter file for a2                                      */
/*                                                           */
/*  Author1 Name: Navid Vadsariya                            */
/*      - class/function list/main author or main checker    */
/*  Author2 Name: Faramarz Hosseini                          */
/*      - class/function list/main author or main checker    */
/*                                                           */
/*************************************************************/

#include <string>
#include <utility>
#include <functional>
#include "mylist.h"

template <class TYPE>
class Table{
public:
	Table(){}
	virtual void update(const std::string& key, const TYPE& value)=0;
	virtual bool remove(const std::string& key)=0;
	virtual bool find(const std::string& key, TYPE& value)=0;
	virtual int numRecords() const = 0;
	virtual bool isEmpty() const = 0;
    virtual int capacity() const = 0;
	virtual ~Table(){}
};

template <class TYPE>
class SimpleTable:public Table<TYPE>{

	struct Record{
		TYPE data_;
		std::string key_;
		Record(const std::string& key, const TYPE& data){
			key_=key;
			data_=data;
		}

	};

	Record** records_;   //the table
	int capacity_;       //capacity of the array

	void grow(){
		Record** tmp=new Record*[capacity_*2 +1];
		for(int i=0;i<capacity_;i++){
			tmp[i]=records_[i];
		}
		for(int i=capacity_;i <capacity_*2+1;i++){
			tmp[i]=nullptr;
		}
		delete[] records_;
		records_=tmp;
		capacity_*=2;
	}
public:
	SimpleTable(int capacity);
	SimpleTable(const SimpleTable& rhs);
	SimpleTable(SimpleTable&& rhs);
	virtual void update(const std::string& key, const TYPE& value);
	virtual bool remove(const std::string& key);
	virtual bool find(const std::string& key, TYPE& value);
	virtual const SimpleTable& operator=(const SimpleTable& rhs);
	virtual const SimpleTable& operator=(SimpleTable&& rhs);
	virtual ~SimpleTable();
	virtual bool isEmpty() const{return numRecords()==0;}
	virtual int numRecords() const;
    virtual int capacity() const {return capacity_;}

};

template <class TYPE>
int SimpleTable<TYPE>::numRecords() const{
	int rc=0;
	for(int i=0;records_[i]!=nullptr;i++){
		rc++;
	}
	return rc;
}



template <class TYPE>
SimpleTable<TYPE>::SimpleTable(int capacity): Table<TYPE>(){
	records_=new Record*[capacity+1];
	capacity_=capacity;
	for(int i=0;i<capacity_+1;i++){
		records_[i]=nullptr;
	}
}

template <class TYPE>
SimpleTable<TYPE>::SimpleTable(const SimpleTable<TYPE>& rhs){
	records_=new Record*[rhs.capacity_+1];
	capacity_=rhs.capacity_;
    for(int i=0;i<capacity_+1;i++){
        records_[i]=nullptr;
    }
	for(int i=0;i<rhs.numRecords();i++){
		update(rhs.records_[i]->key_,rhs.records_[i]->data_);
	}
}
template <class TYPE>
SimpleTable<TYPE>::SimpleTable(SimpleTable<TYPE>&& rhs){
	capacity_=rhs.capacity_;
	records_=rhs.records_;
	rhs.records_=nullptr;
	rhs.capacity_=0;
}

template <class TYPE>
void SimpleTable<TYPE>::update(const std::string& key, const TYPE& value){
	int idx=-1;

	for(int i=0;i<numRecords();i++){
		if(records_[i]->key_ == key){
			idx=i;
		}
	}
	if(idx==-1){
		if(numRecords() == capacity_){
			grow();
		}
		records_[numRecords()]=new Record(key,value);
		for(int i=numRecords()-1;i>0 && records_[i]->key_ < records_[i-1]->key_;i--){
			Record* tmp=records_[i];
			records_[i]=records_[i-1];
			records_[i-1]=tmp;
		}

	}
	else{
		records_[idx]->data_=value;
	}

}

template <class TYPE>
bool SimpleTable<TYPE>::remove(const std::string& key){
	int idx=-1;
	for(int i=0;i<numRecords();i++){
		if(records_[i]->key_ == key){
			idx=i;
		}
	}
	if(idx!=-1){
		int size=numRecords();
		delete records_[idx];
		for(int i=idx;i<size-1;i++){
			records_[i]=records_[i+1];
		}
		records_[size-1]=nullptr;
		return true;
	}
	else{
		return false;
	}
}

template <class TYPE>
bool SimpleTable<TYPE>::find(const std::string& key, TYPE& value){
	int idx=-1;
	for(int i=0;i<numRecords();i++){
		if(records_[i]->key_ == key){
			idx=i;
		}
	}
	if(idx==-1)
		return false;
	else{
		value=records_[idx]->data_;
		return true;
	}
}

template <class TYPE>
const SimpleTable<TYPE>& SimpleTable<TYPE>::operator=(const SimpleTable<TYPE>& rhs){
	if(this!=&rhs){
		if(records_){
			while(numRecords() != 0){
				remove(records_[0]->key_);
			}
			delete [] records_;
		}
		records_=new Record*[rhs.capacity_+1];
		capacity_=rhs.capacity_;
        for(int i=0;i<capacity_;i++){
            records_[i]=nullptr;
        }
		for(int i=0;i<rhs.numRecords();i++){
			update(rhs.records_[i]->key_,rhs.records_[i]->data_);
		}

	}
	return *this;
}
template <class TYPE>
const SimpleTable<TYPE>& SimpleTable<TYPE>::operator=(SimpleTable<TYPE>&& rhs){
	if(records_){
		while(numRecords() != 0){
			remove(records_[0]->key_);
		}
		delete [] records_;
	}
	records_=rhs.records_;
	capacity_=rhs.capacity_;
	rhs.records_=nullptr;
	rhs.capacity_=0;

	return *this;
}
template <class TYPE>
SimpleTable<TYPE>::~SimpleTable(){
	if(records_){
		int sz=numRecords();
		for(int i=0;i<sz;i++){
			remove(records_[0]->key_);
		}
		delete [] records_;
	}
}


template <class TYPE>
class ChainingTable:public Table<TYPE>{
	//Record struct is a member of ChaningTable that contains a linked list
	struct Record {
		RecentList<TYPE> list_;
		//Default constructor initializes all the linked lists
		Record() {}
	};
	
	//An array of records
	Record* records_;
	//Table's capacity
	float capacity_;
	//table's maximum nober of records based on capacity
	float maxLoadFactor_;
	//Number of records in the table
	float noRecords;
	
	//Increases the size of the table and relocates every node based on a newly generated index
	void grow() {
		std::hash<std::string> hashFunction;
		capacity_ *= 2;
		Record* tmp = new Record[(int)(capacity_) + 1];
		for (int i = 0; i < capacity_ / 2; i++) {
			if (records_[i].list_.size() > 0) {
				typename RecentList<TYPE>::iterator iter = records_[i].list_.begin();
				while (iter.getCurrent()->next_ != nullptr) {
					int idx = hashFunction(iter.getCurrent()->key_) % capacity();
					tmp[idx].list_.insert(iter.getCurrent()->data_, iter.getCurrent()->key_);
					iter++;
				}
			}
			
		}
		delete[] records_;
		records_ = tmp;
	}


public:
	ChainingTable(int maxExpected, double maxLoadFactor);
	ChainingTable(const ChainingTable& other);
	ChainingTable(ChainingTable&& other);
	virtual void update(const std::string& key, const TYPE& value);
	virtual bool remove(const std::string& key);
	virtual bool find(const std::string& key, TYPE& value);
	virtual const ChainingTable& operator=(const ChainingTable& other);
	virtual const ChainingTable& operator=(ChainingTable&& other);
	virtual ~ChainingTable();
	virtual bool isEmpty() const;
	virtual int numRecords() const;
  virtual int capacity() const;

  
};

//Two arument constructor that accepts a capacity and a maximum load factor and initializes the members of the table
template <class TYPE>
ChainingTable<TYPE>::ChainingTable(int maxExpected,double maxLoadFactor): Table<TYPE>(){
	records_ = nullptr;
	records_ = new Record [maxExpected + 1];
	capacity_ = maxExpected;
	maxLoadFactor_ = maxLoadFactor;
	noRecords = 0;
}

//Copy constructor that accepts a constant ChainingTable as a parameter and initializes the table based on its members
template <class TYPE>
ChainingTable<TYPE>::ChainingTable(const ChainingTable<TYPE>& other){
	this->capacity_ = other.capacity_;
	this->maxLoadFactor_ = other.maxLoadFactor_;
	this->noRecords = other.noRecords;
	this->records_ = new Record[(int)(other.capacity_) + 1];
	
	for (int i = 0 ; i < this->capacity_; i++) {
		if (other.records_[i].list_.size() != 0) {
			this->records_[i].list_ = other.records_[i].list_;
		}
		
	}
}

//Move constructor that accepts a ChainingTable as a parameter and moves all the members to the table and dealocates the other table
template <class TYPE>
ChainingTable<TYPE>::ChainingTable(ChainingTable<TYPE>&& other){
	records_ = nullptr;
	this->capacity_ = other.capacity_;
	this->maxLoadFactor_ = other.maxLoadFactor_;
	this->noRecords = other.noRecords;

	this->records_ = new Record[(int)(other.capacity_) + 1];
	for (int i = 0 ; i < this->capacity_ ; i++) {
		this->records_[i].list_ = std::move(other.records_[i].list_);
	}

	other.maxLoadFactor_ = 0;
	other.noRecords = 0;
	other.capacity_ = 0;
	other.records_ = nullptr;
}

//Update function accepts a key and a value and tries to find a record based on the given key
//If successful, it then sets the value of the node to the recieved value
//If not, it creates a node and sets the key and value of it to the recieved key and value
template <class TYPE>
void ChainingTable<TYPE>::update(const std::string& key, const TYPE& value) {
	std::hash<std::string> hashFunction;
	int idx = hashFunction(key) % capacity();
	if (records_[idx].list_.size() != 0)
	{
		typename RecentList<TYPE>::iterator iter = records_[idx].list_.begin();
		while (iter.getCurrent()->key_.compare(key) != 0 && iter.getCurrent()->next_ != nullptr) {
			iter++;
		}
		if (iter.getCurrent()->next_ != nullptr)
			iter.getCurrent()->data_ = value;
		else {
			
			if (noRecords / capacity_ >= maxLoadFactor_) {
				grow();
				idx = hashFunction(key) % capacity();
			}
			records_[idx].list_.insert(value, key);
			noRecords++;
		}
	}
	else
	{
		
		if ( (float)(noRecords / capacity_) >= maxLoadFactor_) {
			grow();
			idx = hashFunction(key) % capacity();
		}

		records_[idx].list_.insert(value, key);
		noRecords++;
	}
}

//Remove function accepts a key and searches for a node with that key
//If successful, it then deletes the node and returns true
//If not, it returns false
template <class TYPE>
bool ChainingTable<TYPE>::remove(const std::string& key){

	std::hash<std::string> hashFunction;
	int idx = hashFunction(key) % capacity();

	if (records_[idx].list_.size() != 0) {
		typename RecentList<TYPE>::iterator iter = records_[idx].list_.search(key);
		records_[idx].list_.erase(iter);
		noRecords--;
		return true;
	}

	return false;
}

//Find function accepts a key and a value and searches for a node with that key
//If successful, it sets the value of the recieved value to the value of the node and returns true
//If not, it returns false
template <class TYPE>
bool ChainingTable<TYPE>::find(const std::string& key, TYPE& value) {
	std::hash<std::string> hashFunction;
	int idx = hashFunction(key) % capacity();
	if (records_[idx].list_.size() != 0)
	{
		typename RecentList<TYPE>::iterator iter = records_[idx].list_.begin();
		while (iter.getCurrent()->key_.compare(key) != 0 && iter.getCurrent()->next_ != nullptr) {
			iter++;
		}
		if (iter.getCurrent()->next_ != nullptr)
		{
			value = iter.getCurrent()->data_;
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}

//Copy assignment operator that recieves a constant ChainingTable and sets the members of the table to the values of the accepted table's members
template <class TYPE>
const ChainingTable<TYPE>& ChainingTable<TYPE>::operator=(const ChainingTable<TYPE>& other){
	if (this != &other){
		if (records_ != nullptr && noRecords > 0) {
			for (int i = 0 ; i < this->capacity_; i++){
				if (records_[i].list_.size() != 0) {
					records_[i].list_.erase(records_[i].list_.begin(),records_[i].list_.end());
				}
			}
			delete[] records_;
		}
		this->capacity_ = other.capacity_;
		this->maxLoadFactor_ = other.maxLoadFactor_;
		this->noRecords = other.noRecords;
		this->records_ = new Record[(int)(other.capacity_) + 1];
		
		for (int i = 0 ; i < this->capacity_; i++) {
			if (other.records_[i].list_.size() != 0) {
				this->records_[i].list_ = other.records_[i].list_;
			}
		}

	}
	return *this;
}

//Move assignment operator that accepts a ChaningTable and moves all the members to the table and dealocates the other table
template <class TYPE>
const ChainingTable<TYPE>& ChainingTable<TYPE>::operator=(ChainingTable<TYPE>&& other){
	if (this != &other){

		if (records_ != nullptr && noRecords > 0) {
			for (int i = 0 ; i < this->capacity_ ; i++){
				if (records_[i].list_.size() != 0) {
					records_[i].list_.erase(records_[i].list_.begin(),records_[i].list_.end());
				}
			}
			delete[] records_;
		}
		records_ = nullptr;
		this->capacity_ = other.capacity_;
		this->maxLoadFactor_ = other.maxLoadFactor_;
		this->noRecords = other.noRecords;

		this->records_ = new Record[(int)(other.capacity_) + 1];
		for (int i = 0 ; i < this->capacity_ ; i++) {
			this->records_[i].list_ = std::move(other.records_[i].list_);
		}

		other.maxLoadFactor_ = 0;
		other.noRecords = 0;
		other.capacity_ = 0;
		other.records_ = nullptr;
	}
	return *this;

}

//ChainingTable deconstructor dealocates all the nodes of the linked lists and then dealocates all the records
template <class TYPE>
ChainingTable<TYPE>::~ChainingTable(){
	if (records_ != nullptr) {
		for (int i = 0 ; i < this->capacity_ ; i++){
			records_[i].list_.erase(records_[i].list_.begin(),records_[i].list_.end());
		}
		delete[] records_;
	}
}

//Returns whether the table is emty or not based on the number of records
template <class TYPE>
bool ChainingTable<TYPE>::isEmpty() const {
    return numRecords() == 0;
}

//Returns the number of records in the table
template <class TYPE>
int ChainingTable<TYPE>::numRecords() const {
	return noRecords;
}

//Returns the capacity of the table
template <class TYPE>
int ChainingTable<TYPE>::capacity() const {
    return capacity_;
}

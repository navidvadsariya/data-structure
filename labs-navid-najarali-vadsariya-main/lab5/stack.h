
template <typename T>
class Stack
{
    T data_[15];
    int top_;

public:
    //constructor
    Stack()
    {
        top_ = 0;
    }
    //adds data to stack
    void push(T data)
    {
        if (top_ != 15) {
            data_[top_] = data;
            top_++;
        }
    }
    //removes data from top of stack
    void pop()
    {
        if (top_ > 0) {
            top_--;
        }
    }
    //retruns true if stack is empty
    bool isEmpty() const
    {
        return top_ == 0;
    }
    //returns true if stack is full
    bool isFull() const
    {
        return top_ == 15;
    }
    //returns top 
    T top() const
    {
        if (top_ != 0) {
            return data_[top_ - 1];
        }
    }
    
};
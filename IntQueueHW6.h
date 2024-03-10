#ifndef INTQUEUEHW6
#define INTQUEUEHW6

class IntQueueHW6
{
private:
    int *queueArray;
    int queueSize;  //capacity of queue
    int front;
    int rear;
    int numItems;  //# of elements currently in the queue
public:
    IntQueueHW6(int);  //constructor, parameter is capacity
    IntQueueHW6(const IntQueueHW6&);  //constructor, parameter is capacity
    IntQueueHW6& operator=(const IntQueueHW6&);
    void enqueue(int);
    void dequeue(int &);
    bool isEmpty() const;
    bool isFull() const;
    void clear();  //removes all elements
    ~IntQueueHW6();
};
#endif
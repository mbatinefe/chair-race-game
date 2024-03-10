#include <iostream>
#include "IntQueueHW6.h"
using namespace std;

//*****************************************
// Constructor - creates an empty queue   *
// with given number of elements          *
//*****************************************
IntQueueHW6::IntQueueHW6(int s)
{
    queueArray = new int[s];
    queueSize = s;
    front = -1;
    rear = -1;
    numItems = 0;
}

/**
 * @brief Deep-copy constructor
 * @param s
 */
IntQueueHW6::IntQueueHW6(const IntQueueHW6 & q)
{
    queueArray = new int[q.queueSize];
    queueSize = q.queueSize;
    // Deep copy operation
    for (int i = 0; i < q.queueSize; ++i) {
        queueArray[i] = q.queueArray[i];
    }
    front = q.front;
    rear = q.rear;
    numItems = q.numItems;
}

//********************************************
// Function enqueue inserts the value in num *
// at the rear of the queue.                 *
//********************************************
void IntQueueHW6::enqueue(int num)
{
    if (isFull())
    {
        cout << "ERROR: Trying to enqueue to a full queue! Terminating..." << endl;
        exit(5);
    }
    else
    {
        // Calculate the new rear position circularly.
        rear = (rear + 1) % queueSize;
        // Insert new item.
        queueArray[rear] = num;
        // Update item count.
        numItems++;
    }
}

//**********************************************
// Function dequeue removes the value at the   *
// front of the queue, and copies it into num. *
//**********************************************
void IntQueueHW6::dequeue(int &num)
{
    if (isEmpty())
    {
        cout << "ERROR: Trying to dequeue from an empty queue! Terminating..." << endl;
        exit(6);
    }
    else
    {
        // Move front.
        front = (front + 1) % queueSize;
        // Retrieve the front item.
        num = queueArray[front];
        // Update item count.
        numItems--;
    }
}

//*********************************************
// Function isEmpty returns true if the queue *
// is empty, and false otherwise.             *
//*********************************************
bool IntQueueHW6::isEmpty() const
{
    if (numItems > 0)
        return false;
    else
        return true;
}

//********************************************
// Function isFull returns true if the queue *
// is full, and false otherwise.             *
//********************************************
bool IntQueueHW6::isFull() const
{
    if (numItems < queueSize)
        return false;
    else
        return true;
}

//*******************************************
// Function clear resets the front and rear *
// indices, and sets numItems to 0.         *
//*******************************************
void IntQueueHW6::clear()
{
    front =  - 1;
    rear =  - 1;
    numItems = 0;
}

/**
 * @brief Destructor
 */
IntQueueHW6::~IntQueueHW6() {
    delete [] queueArray;
    queueSize = 0;
    front = -1;
    rear = -1;
    numItems = 0;
}

IntQueueHW6 &IntQueueHW6::operator=(const IntQueueHW6 & rhs) {
    if (this == &rhs){
    }
    else
    {
        if (this->queueSize != rhs.queueSize)
        {
            delete [] queueArray;
            queueArray = new int[rhs.queueSize];
            queueSize = rhs.queueSize;
            // Deep assignment
            for (int i = 0; i < queueSize; i++) {
                queueArray[i] = rhs.queueArray[i];
            }
            front = rhs.front;
            rear = rhs.rear;
            numItems = rhs.numItems;
        }
    }
    return *this;
}

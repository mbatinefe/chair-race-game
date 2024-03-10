// Mustafa Batin Efe

#include <iostream>
#include <thread>
#include <string>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <mutex>
#include <vector>
#include "IntQueueHW6.h"

using namespace std;

mutex helpMutex;
void adder(int id, struct tm *ptm, IntQueueHW6 & myQue, vector<int>&myVec) {
    this_thread::sleep_until(chrono::system_clock::from_time_t(mktime(ptm)));
    helpMutex.lock();
    if (myQue.isFull() != true) {
        cout << "Player " << id << " captured a chair at " << put_time(ptm, "%X") << endl;
        myQue.enqueue(id);
    } else {
        cout << "Player " << id << " couldn't capture a chair." << endl;
        int idx = 0;
        // While index is smaller than size of the vector
        while (idx < myVec.size()) {
            if (myVec[idx] == id) { // If Id matches on that index
                myVec.erase(myVec.begin() + idx); // Delete that index
            } else {
                ++idx; // Pre-increment index value
            }
        }
    }
    helpMutex.unlock();
}

int main() {
    cout << "Welcome to Musical Chairs game!" << endl;
    cout << "Enter the number of players in the game:" << endl;
    int num_player;
    cin >> num_player; // get number of player from user
    // The number of chairs is one less than the number of players.
    int seat_num = num_player - 1;
    cout << "Game Start!" << endl;

    IntQueueHW6 myQueue(seat_num); // Start first queue
    thread threads[num_player]; // Create num_player times thread

    /* Begin: Following code taken from threads8.cpp */
    time_t tt = chrono::system_clock::to_time_t(chrono::system_clock::now());
    struct tm *ptm = new struct tm;
    localtime_s(ptm, &tt);
    cout << "Time is now " << put_time(ptm, "%X") << endl;
    /* Finish: Following code taken from threads8.cpp */

    ptm->tm_sec = ptm->tm_sec + 2;

    // Create a vector to store player's id
    vector<int> mySet;

    bool isFirst = false;
    // Start first round
    for(int y = 0; y < num_player; y++){
        mySet.push_back(y);
        threads[y] = thread(&adder, y, ptm, ref(myQueue), ref(mySet));
    }
    isFirst = true;

    // While all seats are not captured
    while(seat_num != 0){
        if(isFirst != true){
            IntQueueHW6 myQueue2(seat_num);
            myQueue = myQueue2; // Set new seat number
            /* Begin: Following code taken from threads8.cpp */
            tt = chrono::system_clock::to_time_t(chrono::system_clock::now());
            ptm = new struct tm;
            localtime_s(ptm, &tt);
            cout << "Time is now " << put_time(ptm, "%X") << endl;
            /* Finish: Following code taken from threads8.cpp */
            ptm->tm_sec = ptm->tm_sec + 2; // Add 2 second waiting time

            // Start other rounds
            for(int y = 0; y < num_player; y++){
                int m = mySet[y];
                threads[y] = thread(&adder, m, ptm, ref(myQueue), ref(mySet));
            }

        }

        // Let s wait all threads to join
        for(int y = 0; y < num_player; y++){
            threads[y].join();
        }

        ostringstream oss;
        while(myQueue.isEmpty() != true){
            int temps; // to dequeue myQueue
            myQueue.dequeue(temps);
            oss << " " << temps;

        }

        cout << "Remaining players are as follows:" << oss.str();
        cout << endl << endl;
        num_player--; // Player decreased
        seat_num--; // Seat decreased
        isFirst = false; // It is not the first one anymore
        myQueue.clear(); // Make sure and clear inside, they release the seats

    }
    cout << "Game over!" << endl;
    cout << "Winner is Player "<< mySet[0]; // Last id stored in vector

    return 0;
}

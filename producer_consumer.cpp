#include <iostream>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
using namespace std;

queue<int> q;
mutex mtx;
condition_variable cv;
int count=0;


const int MaxItems = 20; // Maximum number of items in the queue

void producer() {
    
    while(true){
        unique_lock<mutex> lock(mtx);
    while (count == MaxItems) {
      cv.wait(lock);
    }
        int number = rand() % 100;
        q.push(number);
        count++;
        
        cout << "Producer produced: " << number << endl;
        cv.notify_one();
    }
}

void consumer() {
    while (true) {
    unique_lock<mutex> lock(mtx);
    while (count == 0) {
      cv.wait(lock);
    }

    int number = q.front();
    q.pop();
    count--;

    cout << "Consumer consumed: " << number << endl;
    cv.notify_one();
    
    if(number== MaxItems -1){
        break;
    }
  }
}

int main() {
    thread producerThread(producer);
    thread consumerThread(consumer);

    producerThread.join();
    consumerThread.join();

    return 0;
}

#ifndef BLOCKING_QUEUE_H
#define BLOCKING_QUEUE_H

#include <mutex>
#include <condition_variable>
#include <queue>

namespace asynctask{

template<class T>
class BlockingQueue{
    typedef T ValueType;

public:
    BlockingQueue() : queue_(), mutex_(), cond_() {}

    void push(ValueType newValue){
        std::lock_guard<std::mutex> lock(mutex_);
        queue_.push(std::move(newValue));
        cond_.notify_one();
    }

    bool empty() const{
        std::lock_guard<std::mutex> lock(mutex_);
        return queue_.empty();
    }

    ValueType pop(){
        std::unique_lock<std::mutex> lock(mutex_);
        cond_.wait(lock, [this]{ return !queue_.empty(); });
        ValueType value = std::move(queue_.front());
        queue_.pop();
        return value;
    }

    //front和pop不可以分开,因为可能会有竞争
    //所以这里不提供front()函数

//    ValueType front(){
//        std::unique_lock<std::mutex> lock(mutex_);
//        cond_.wait(lock, [this]{return !queue_.empty();});
//        return queue_.front();
//    }

private:
    std::queue<ValueType> queue_;
    mutable std::mutex mutex_;
    std::condition_variable cond_;
};

}

#endif // BLOCKING_QUEUE_H


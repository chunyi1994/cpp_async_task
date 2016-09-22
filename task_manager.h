#ifndef TASKMANAGER_H
#define TASKMANAGER_H

#include <thread>
#include <memory>
#include <atomic>
#include <set>

#include "blocking_queue.h"

namespace asynctask{

class Task;
class EventTask;

class TaskManager
{
    typedef std::shared_ptr<Task> TaskPtr;

public:
    TaskManager();

    ~TaskManager();

    void close();  //stop是把一个线程安全的flag变量设置为true,并没有kill掉线程
                         //所以stop()了以后,不会立即关闭,而是等到while(!isStop)下一次循环线程会自动退出.

    void submit(const TaskPtr& task);
    void deleteEventTask(const std::shared_ptr<const EventTask>& task);

private:
    void executeFunctions();

    //nocopyable,我不认为这个类需要拷贝
    TaskManager(const TaskManager&) = delete;
    TaskManager& operator=(const TaskManager&) = delete;
    TaskManager& operator=(TaskManager&&) = delete;

    std::atomic_bool isStop_;  //原子操作的bool
    BlockingQueue<TaskPtr> taskQueue_;  //线程安全的阻塞队列

    //EventTask中保存着lambda表达式中所有需要的变量,至关重要,所以他不能先牺牲
    //为了不让EventTask的shared_ptr的引用计数变为零,这里用set保存,
    //可以让EventTask的生命周期保持到finish结束以后
    //finish任务会删除set中保存的指针,然后销毁所有TaskEvent开销,避免内存泄露
    std::set<std::shared_ptr<const EventTask> > taskSet_;
};

}

#endif // TASKMANAGER_H

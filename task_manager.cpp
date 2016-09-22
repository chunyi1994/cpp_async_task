#include <unistd.h>
#include <iostream>
#include <assert.h>

#include "task_manager.h"
#include "task.h"
#include "event_task.h"

namespace asynctask{
TaskManager::TaskManager() :
    isStop_(false),
     taskQueue_(),
    taskSet_()
{
    std::thread t(&TaskManager::executeFunctions, this);
    t.detach();
}

TaskManager::~TaskManager()
{
    close();
}

void TaskManager::close()
{
    isStop_ = true;
}

void TaskManager::submit(const TaskPtr& task)
{
    //如果传递进来的是EventTask,则加入到set里
    if(dynamic_cast<EventTask*>( task.get()))
    {
        std::shared_ptr<EventTask> eventTaskPtr = std::dynamic_pointer_cast<EventTask>(task);
        taskSet_.insert(eventTaskPtr);
    }

    taskQueue_.push(task);
}

void TaskManager::deleteEventTask(const std::shared_ptr<const EventTask>& task)
{
    auto iter = taskSet_.find(task);
    assert(iter != taskSet_.end());
    taskSet_.erase(iter);
}

void TaskManager::executeFunctions()
{
    while(!isStop_)
    {
        while(!taskQueue_.empty())
        {
            TaskPtr task = taskQueue_.pop();
            task->execute();
        }
    }
}

}

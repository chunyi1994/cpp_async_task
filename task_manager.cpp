#include <unistd.h>
#include <iostream>
#include <assert.h>

#include "task_manager.h"
#include "task.h"
#include "event_task.h"

namespace asynctask{
TaskManager::TaskManager() : taskQueue_(), isStop_(false), taskSet_()
{
    std::thread t(&TaskManager::executeFunctions, this);
    t.detach();
}

TaskManager::~TaskManager()
{
    stop();
}

void TaskManager::stop()
{
    isStop_ = true;
}

void TaskManager::submit(const TaskPtr& task)
{
    taskQueue_.push(task);
}

void TaskManager::registerEventTask(const std::shared_ptr<EventTask>& task)
{
    taskSet_.insert(task);
    //shared_ptr的向下转型
    TaskPtr taskPtr = std::dynamic_pointer_cast<Task>(task);
    submit(taskPtr);
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

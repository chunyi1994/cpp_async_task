#include <assert.h>

#include "event_task.h"
#include "task_manager.h"

namespace asynctask{

EventTask::EventTask(TaskManager *manager) : manager_(manager), taskMap_()
{

}

EventTask::~EventTask()
{

}

void EventTask::execute() const
{

}

void EventTask::on(int event, const TaskFunction& func)
{
    taskMap_[event] = func;
}

void EventTask::emit(int event) const
{
    auto iter = taskMap_.find(event);
    assert(iter != taskMap_.end());
    manager_->submit(std::make_shared<FunctionTask>(iter->second));

    //为了避免内存泄露,要求使用者对每个任务都要注册一个finish,以通知执行完毕,并执行销毁操作
    if(event == ON_EVENT_FINISH)
    {
        //不直接从manager中删除自己,而是添加一个任务
        //可以让自己的生命周期延长到finish执行完毕以后再销毁
        //如果不这样做,EventTask的析构函数会先于finish任务执行
        std::shared_ptr<const EventTask> myself = shared_from_this();
        manager_->submit(std::make_shared<FunctionTask>([myself, this](){
            manager_->deleteEventTask(myself);
        }));
    }
}
}

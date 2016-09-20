#ifndef EVENT_TASK_H
#define EVENT_TASK_H

#include <iostream>
#include <unistd.h>
#include <map>

#include "task.h"
#include "function_task.h"

namespace asynctask{

class TaskManager;
//说明:
//由于EventTask继承了enable_shared_from_this
//所以这个类只能用shared_ptr来管理,不能声明在栈上
class EventTask : public Task,  public std::enable_shared_from_this<EventTask>
{
public:

    EventTask(TaskManager* manager);

    virtual ~EventTask();

    virtual void execute() const;

    void on(int event, const TaskFunction& func);

    void emit(int event) const;

private:
    TaskManager* manager_;
    std::map<int,  TaskFunction> taskMap_;
};

const int ON_EVENT_FINISH = -1;
}

#endif // EVENT_TASK_H


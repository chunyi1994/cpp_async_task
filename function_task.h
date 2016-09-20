#ifndef SIMPLE_TASK_H
#define SIMPLE_TASK_H

#include "task.h"

namespace asynctask{

typedef std::function<void()> TaskFunction;

class FunctionTask : public Task
{

public:
    FunctionTask(){}

    virtual ~FunctionTask() {}

    FunctionTask(const TaskFunction& func) : func_(func) {}

    virtual void execute() const
    {
        if(func_)
        {
            func_();
        }
    }

    void setTaskFunction(const TaskFunction& func)
    {
        func_ = func;
    }

private:
    TaskFunction func_;
};

typedef std::shared_ptr<FunctionTask> FunctionTaskPtr;

}
#endif // SIMPLE_TASK_H


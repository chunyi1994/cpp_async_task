#ifndef TASK_H
#define TASK_H
#include <functional>
#include <memory>
#include <iostream>

namespace asynctask{

class Task
{
public:
    Task(){}

    virtual ~Task(){}

    virtual void execute() const
    {
       // std::cout<<"Task execute"<<std::endl;
    }

};

typedef std::shared_ptr<Task> TaskPtr;

}
#endif // TASK_H

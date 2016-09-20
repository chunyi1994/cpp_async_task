#ifndef IO_TASK_H
#define IO_TASK_H
#include <iostream>
#include <unistd.h>

#include "event_task.h"

//这里定义了两个类来测试用,
//IOTask 的任务顺序是 task1 task2 task3 task4 finish
//IOTask2任务的顺序是taskA taskB taskC taskD finish
//两个注册到manager里去,就会发现两者的任务是交替进行的.
//交替方式可能是 task1 -> taskA -> taskB  -> task2 -> taskC - > task3 ->  taskD -> task4 ->  finish -> finish
namespace asynctask{

enum Task1Events
{
    ON_EVENT_TASK1,
    ON_EVENT_TASK2,
    ON_EVENT_TASK3,
    ON_EVENT_TASK4,
};

enum Task2Events
{
    ON_EVENT_TASKA,
    ON_EVENT_TASKB,
    ON_EVENT_TASKC,
    ON_EVENT_TASKD,
};


class IOTask : public EventTask
{
public:
    IOTask(TaskManager* manager) : EventTask(manager)
    {
        on(ON_EVENT_TASK1, [this]()
        {
            std::cout<<"task1正在执行"<<std::endl;
            sleep(1);
            emit(ON_EVENT_TASK2);
        });

        on(ON_EVENT_TASK2, [this]()
        {
            std::cout<<"task2正在执行"<<std::endl;
            sleep(1);
            emit(ON_EVENT_TASK3);
        });

        on(ON_EVENT_TASK3, [this]()
        {
            std::cout<<"task3正在执行"<<std::endl;
            sleep(1);
            emit(ON_EVENT_TASK4);
        });

        on(ON_EVENT_TASK4, [this]()
        {
            std::cout<<"task4正在执行"<<std::endl;
            sleep(1);
            emit(ON_EVENT_FINISH);
        });

        on(ON_EVENT_FINISH, [this]()
        {
            std::cout<<"finish正在执行"<<std::endl;
            sleep(1);
        });
    }

    virtual ~IOTask() {
        std::cout<<"~iotask"<<std::endl;
    }

    virtual void execute() const
    {
       emit(ON_EVENT_TASK1);
    }
};


class IOTask2 : public EventTask
{
public:
    IOTask2(TaskManager* manager) : EventTask(manager)
    {
        on(ON_EVENT_TASKA, [this]()
        {
            std::cout<<"taskA正在执行"<<std::endl;
            sleep(1);
            emit(ON_EVENT_TASKB);
        });

        on(ON_EVENT_TASKB, [this]()
        {
            std::cout<<"taskB正在执行"<<std::endl;
            sleep(1);
            emit(ON_EVENT_TASKC);
        });

        on(ON_EVENT_TASKC, [this]()
        {
            std::cout<<"taskC正在执行"<<std::endl;
            sleep(1);
            emit(ON_EVENT_TASKD);
        });

        on(ON_EVENT_TASKD, [this]()
        {
            std::cout<<"taskD正在执行"<<std::endl;
            sleep(1);
            emit(ON_EVENT_FINISH);
        });

        on(ON_EVENT_FINISH, [this]()
        {
            std::cout<<"finish2正在执行"<<std::endl;
            sleep(1);
        });
    }

    virtual ~IOTask2() {
        std::cout<<"~iotask2"<<std::endl;
    }

    virtual void execute() const
    {
       emit(ON_EVENT_TASKA);
    }
};

}
#endif // IO_TASK_H


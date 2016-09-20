#include <iostream>
#include <thread>
#include <unistd.h>

#include "task_manager.h"
#include "io_task.h"
#include "file_task.h"
using namespace std;
using namespace asynctask;

void example1()
{
    TaskManager manager;
    {
        //iotask不会马上销毁,因为manager持有1个他们的引用计数
        //iotask销毁的时机是在执行完finish任务以后
        std::shared_ptr<EventTask> iotask = std::make_shared<IOTask>(&manager);
        std::shared_ptr<EventTask> iotask2 = std::make_shared<IOTask2>(&manager);

        manager.registerEventTask(iotask);
        manager.registerEventTask(iotask2);
    }
    sleep(20);
}

void example2()
{
    TaskManager manager;
    //EventTask是高级的Task,他可以向manager投递新的任务
    {
        std::shared_ptr<EventTask> fileTask = std::make_shared<FileTask>(&manager);
        manager.registerEventTask(fileTask);
    }

    sleep(20);
}

void example3()
{
    //最简单的生产者消费者模式
    //manager等待投递task,当有人submit以后,manager就会取出他,然后执行taskPtr->execute();
    TaskManager manager;
    std::shared_ptr<Task> taskPtr = std::make_shared<FunctionTask>([](){
        cout<<"执行了一个任务"<<endl;
    });
    manager.submit(taskPtr);

    sleep(20);
}


int main()
{
     example1();
}






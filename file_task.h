#ifndef FILE_TASK_H
#define FILE_TASK_H

#include <fstream>
#include <string>

#include "event_task.h"

namespace asynctask{

enum FileTaskEvents{
    ON_EVENT_OPEN,
    ON_EVENT_LOOP,
};

class FileTask : public EventTask
{
public:
    FileTask(TaskManager* manager) :
        EventTask(manager),
        file_(),
        count_(1)
    {
        //我觉得用enum或者const int 代替string性能会比较高.
        //为了图省事我依然还是用了string
        on(ON_EVENT_OPEN, [this]()
        {
            std::cout<<"打开文件"<<std::endl;
            file_.open("1.txt");
            emit(ON_EVENT_LOOP);
        });

        on(ON_EVENT_LOOP, [this]()
        {
            std::cout<<"第"<<count_++<<"次写入文件"<<std::endl;
            file_<<"我写!";
            if(count_ == 10)
            {
                emit(ON_EVENT_FINISH);
            }
            else
            {
                emit(ON_EVENT_LOOP);
            }
        });

        on(ON_EVENT_FINISH, [this]()
        {
            std::cout<<"关闭文件"<<std::endl;
            file_.close();
        });

    }

    virtual ~FileTask() {
        std::cout<<"~FileTask"<<std::endl;
    }

    virtual void execute() const
    {
       emit(ON_EVENT_OPEN);
    }

private:
    std::ofstream file_;
    int count_;
};
}
#endif // FILE_TASK_H


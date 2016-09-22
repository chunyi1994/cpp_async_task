# cpp_async_task
c++11 单线程异步小框架

最近更新的东西:

简化了TaskManager的接口, 现在只有submit 和 close 接口. 删去了registerEventTask, 并将deleteEventTask设为私有.

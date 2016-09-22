TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt
QMAKE_CXXFLAGS += -std=c++11
LIBS += -lpthread

SOURCES += main.cpp \
    task_manager.cpp \
    event_task.cpp

HEADERS += \
    task.h \
    blocking_queue.h \
    task_manager.h \
    function_task.h \
    io_task.h \
    event_task.h \
    file_task.h


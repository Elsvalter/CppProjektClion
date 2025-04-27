#ifndef TASK_H
#define TASK_H
#include <ctime>
#include <chrono>
#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

class Task {
    std::string mname;
    int mdeadlineDay;
    int mdeadlineMonth;
    int mdeadlineYear;
    bool mdone;

public:
    Task(std::string name, int deadlineDay, int deadlineMonth, int deadlineYear);
    int timeToComplete() const;
    std::string getName() const;
    int getDeadlineDay() const;
    int getDeadlineMonth() const;
    int getDeadlineYear() const;
    bool isDone() const;
    friend std::ostream& operator<<(std::ostream& os, const Task& t);
};


#endif // TASK_H

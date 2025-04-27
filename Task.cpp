#include "task.h"
#include <chrono>
#include <cmath>
#include <iostream>
#include <string>
#include <iomanip>
#include <ctime>

using namespace std;

Task::Task(std::string name, int deadlineDay, int deadlineMonth, int deadlineYear){
    this->mname = name;
    this->mdeadlineDay = deadlineDay;
    this->mdeadlineMonth = deadlineMonth;
    this->mdeadlineYear = deadlineYear;
    this->mdone = false;
};

int Task::timeToComplete() const{
    time_t now = time(nullptr);

    tm deadlineTm = {};
    deadlineTm.tm_mday = mdeadlineDay;
    deadlineTm.tm_mon = mdeadlineMonth - 1; // tm_mon is 0-based
    deadlineTm.tm_year = mdeadlineYear - 1900; // tm_year is years since 1900
    deadlineTm.tm_hour = 0;
    deadlineTm.tm_min = 0;
    deadlineTm.tm_sec = 0;

    // Convert to time_t
    time_t deadlineTime = mktime(&deadlineTm);

    // Calculate difference in seconds, convert to days
    double secondsDiff = difftime(deadlineTime, now);
    int daysLeft = static_cast<int>(std::floor(secondsDiff / (60 * 60 * 24)));

    return daysLeft;
};

std::string Task::getName() const {
    return mname;
}
int Task::getDeadlineDay() const {
    return mdeadlineDay;
}
int Task::getDeadlineMonth() const {
    return mdeadlineMonth;
}
int Task::getDeadlineYear() const {
    return mdeadlineYear;
}
bool Task::isDone() const {
    return mdone;
}

std::ostream& operator<<(std::ostream& os, const Task& t) {
    os << "Task title: " << t.mname << ", Deadline: "
       << std::setfill('0') << std::setw(2) << t.mdeadlineDay << "."
       << std::setfill('0') << std::setw(2) << t.mdeadlineMonth << "."
       << t.mdeadlineYear
       << ",\n Completed: " << (t.mdone ? "Yes" : "No");
    return os;
};


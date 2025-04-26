#include "task.h"
#include <ctime>
#include <chrono>
#include <iostream>
#include <string>
#include <iomanip>

int main(int argc, char *argv[])
{
    std::string name{};
    int day, month, year;

    std::cout << "Welcome to your to-do list!\n";
    std::cout << "Enter new task name: ";
    std::getline(std::cin, name);  // Use getline in case the task name contains spaces

    std::cout << "Enter deadline (day month year): ";
    std::cin >> day >> month >> year;

    Task task(name, day, month, year);

    std::cout << "\n" << task << std::endl;
    int daysLeft = task.timeToComplete();

    if (daysLeft > 0)
        std::cout << "You have " << daysLeft << " day(s) to complete this task.\n";
    else if (daysLeft == 0)
        std::cout << "The deadline is today!\n";
    else
        std::cout << "The deadline has passed by " << -daysLeft << " day(s).\n";

    return 0;
}

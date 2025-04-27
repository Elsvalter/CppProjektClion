//
// Created by elsvalte on 4/26/2025.
//

#ifndef INPUTCONTROLLER_H
#define INPUTCONTROLLER_H
#include <vector>
#include "Task.h"


class TodoListManager {

private:
    std::vector<Task> tasks;

public:
    void displayUserMenu();
    void loadFromFile(const std::string& filename);
    void saveToFile(const std::string& filename);
    Task& addTask();
    void viewAllTasks() const;
    void markTaskDone(const std::string& taskname);
    void deleteAllTasks(const std::string& filename);
    void sortByDeadline();
    std::vector<Task> searchByName(const std::string& keyword) const;
};


#endif //INPUTCONTROLLER_H

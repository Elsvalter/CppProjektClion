//
// Created by elsvalte on 4/26/2025.
//

#include "TodoListManager.h"
#include <fstream>

/**
 * Reading previously saved tasks from a text file
 * and adding them to a vector as Task objects
 * @param filename
 */
void TodoListManager::loadFromFile(const std::string &filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        cout << "File could not be opened" << endl;
        return;
    }

    tasks.clear(); // clearing excisting tasks
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string name;
        int day, month, year;
        bool done;

        if (std::getline(iss, name, ',') &&
            (iss >> day) && iss.get() &&
            (iss >> month) && iss.get() &&
            (iss >> year) && iss.get() &&
            (iss >> done)) {

            Task task(name, day, month, year);
            tasks.push_back(task);
            }
        else {
            std::cout << "Invalid line format: " << line << "\n";
        }
    }
    file.close();
};

/**
 * Writining (saving) Tasks from the task vector
 * to a text file
 * @param filename
 */
void TodoListManager::saveToFile(const std::string &filename) {
    std::ofstream file(filename); // overwrites the existing file
    if (!file.is_open()) {
        cout << "File could not be opened for writing" << endl;
        return;
    }

    for (Task task : tasks) {
        file << task.getName() << ','
             << task.getDeadlineDay() << ','
             << task.getDeadlineMonth() << ','
             << task.getDeadlineYear() << ','
             << (task.isDone() ? 1 : 0)
             << '\n';
    }

    file.close();
};

Task& TodoListManager::addTask() {
    std::string name{};
    int day, month, year;

    std::cout << "Enter new task name: ";
    std::getline(std::cin, name);  // Use getline in case the task name contains spaces

    std::cout << "Enter deadline (day month year): ";
    std::cin >> day >> month >> year;

    tasks.emplace_back(name, day, month, year);

    cout << "\nNew task added" << endl;
    return tasks.back();
};


void TodoListManager::sortByDeadline() {
    std::sort(tasks.begin(), tasks.end(), [](const Task& a, const Task& b) {
        if (a.getDeadlineYear() != b.getDeadlineYear())
            return a.getDeadlineYear() < b.getDeadlineYear();
        if (a.getDeadlineMonth() != b.getDeadlineMonth())
            return a.getDeadlineMonth() < b.getDeadlineMonth();
        return a.getDeadlineDay() < b.getDeadlineDay();
    });
};

std::vector<Task> TodoListManager::searchByName(const std::string& keyword) const {
    std::vector<Task> results;

    for (const auto& task : tasks) {
        if (task.getName().find(keyword) != std::string::npos) {
            results.push_back(task);
        }
    }
    return results;
}









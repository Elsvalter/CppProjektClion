//
// Created by elsvalte on 4/26/2025.
//

#include "TodoListManager.h"
#include <fstream>

void TodoListManager::displayUserMenu() {
    std::cout << "\n";
    std::cout << "============================================\n";
    std::cout << "            🛠️  TO-DO LIST MENU            \n";
    std::cout << "============================================\n";
    std::cout << "1. Add a new task\n";
    std::cout << "2. View all tasks\n";
    std::cout << "3. Mark a task as done\n";
    std::cout << "4. Delete all tasks\n";
    std::cout << "5. Sort tasks by deadline\n";
    std::cout << "6. Search tasks by name\n";
    std::cout << "7. Exit\n";
    std::cout << "--------------------------------------------\n";
    std::cout << "Enter your choice number: ";
};

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

/**
 * Add new task to Tasks vector and return the task
 */
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

/**
 * View all tasks in the Tasks vector
 */
void TodoListManager::viewAllTasks() const {
    std::cout << "=====================================\n";
    std::cout << "           YOUR TASK LIST            \n";
    std::cout << "=====================================\n\n";
    for (const auto& task : tasks) {
        int daysLeft = task.timeToComplete();

        std::cout << task;
        if (daysLeft > 0)
            std::cout << " - Until deadline: " << daysLeft << " day(s).\n";
        else if (daysLeft == 0)
            std::cout << " - The deadline is today!\n";
        else
            std::cout << " - The deadline has passed!\n";
    }
    if (tasks.empty()) {
        std::cout << "No tasks found!\n";
    }
}

/**
 * Delete all tasks both from the vector and the file
 */
void TodoListManager::deleteAllTasks(const std::string& filename) {
    tasks.clear();
    std::ofstream ofs(filename, std::ofstream::trunc);
    if (!ofs) {
        std::cerr << "Error clearing file: " << filename << "\n";
    }
    cout << "\nAll tasks have been deleted.";
};

/**
 * Find task by name from the vector and delete it
 */
void TodoListManager::markTaskDone(const std::string &taskname) {
    auto it = std::find_if(tasks.begin(), tasks.end(), [&taskname](const Task& task) {
       return task.getName() == taskname;
   });
    if (it != tasks.end()) {
        tasks.erase(it);
        std::cout << "Task \"" << taskname << "\" has been removed from active tasks.\n";
    } else {
        std::cout << "Task \"" << taskname << "\" not found.\n";
    }
}












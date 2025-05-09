#include "task.h"
#include <ctime>
#include <chrono>
#include <iostream>
#include <string>
#include <iomanip>
#include "TodoListManager.h"
#include "Task.h"
using namespace std;


int main(int argc, char *argv[]){
    TodoListManager manager;
    std::string filename = "tasks.txt";
    manager.loadFromFile(filename);

    bool running = true;

    while (running) {
        manager.displayUserMenu();

        int choice{};
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Try again!\n";
            continue;
        }

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {
            case 1:
                manager.addTask();
            break;
            case 2:
                manager.viewAllTasks();
            break;
            case 3: {
                std::string taskName;
                std::cout << "Enter the name of the task to mark as done: ";
                std::getline(std::cin, taskName);
                manager.markTaskDone(taskName);
                break;
            }
            case 4:
                manager.deleteAllTasks("tasks.txt");
            break;
            case 5:
                manager.sortByDeadline();
            std::cout << "Tasks sorted by deadline!\n";
            break;
            case 6: {
                std::string keyword;
                std::cout << "Enter keyword to search tasks by name: ";
                std::getline(std::cin, keyword);
                auto results = manager.searchByName(keyword);
                if (!results.empty()) {
                    std::cout << "Tasks matching your search:\n";
                    manager.displayTasks(results);
                } else {
                    std::cout << "No tasks found with that keyword.\n";
                }
                break;
            }
            case 7:
                manager.saveToFile(filename);
                std::cout << "Exiting. Goodbye!\n";
            running = false;
            break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
            break;
        }

        std::cout << "\n";
    }



}

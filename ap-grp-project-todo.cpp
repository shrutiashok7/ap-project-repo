// team members: Shruti Ashok, Thirulokesh A
// roll nos.: 220200027, 220200030

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <ctime>
#include <iomanip>
#include <algorithm>

struct Task {
    std::string description;
    bool completed;
    std::string dueDate;
    
    Task(const std::string& desc, const std::string& date = "") 
        : description(desc), completed(false), dueDate(date) {}
};

class TodoList {
private:
    std::vector<Task> tasks;
    std::string filename;

public:
    TodoList(const std::string& file = "todo.txt") : filename(file) {
        loadFromFile();
    }
    
    ~TodoList() {
        saveToFile();
    }
    
    void addTask(const std::string& description, const std::string& dueDate = "") {
        tasks.push_back(Task(description, dueDate));
        std::cout << "Task added successfully!\n";
    }
    
    void viewTasks() const {
        if (tasks.empty()) {
            std::cout << "No tasks in the list.\n";
            return;
        }
        
        std::cout << "\n TO-DO LIST \n";
        for (size_t i = 0; i < tasks.size(); ++i) {
            std::cout << i + 1 << ". ";
            if (tasks[i].completed) {
                std::cout << "[X] ";
            } else {
                std::cout << "[ ] ";
            }
            
            std::cout << tasks[i].description;
            
            if (!tasks[i].dueDate.empty()) {
                std::cout << " (Due: " << tasks[i].dueDate << ")";
            }
            
            std::cout << "\n";
        }
        std::cout << "---\n";
    }
    
    void markAsComplete(int taskIndex) {
        if (taskIndex >= 1 && taskIndex <= static_cast<int>(tasks.size())) {
            tasks[taskIndex - 1].completed = true;
            std::cout << "Task marked as complete!\n";
        } else {
            std::cout << "Invalid task number.\n";
        }
    }
    
    void removeTask(int taskIndex) {
        if (taskIndex >= 1 && taskIndex <= static_cast<int>(tasks.size())) {
            tasks.erase(tasks.begin() + (taskIndex - 1));
            std::cout << "Task removed successfully!\n";
        } else {
            std::cout << "Invalid task number.\n";
        }
    }
    
    void saveToFile() const {
        std::ofstream file(filename);
        if (!file) {
            std::cout << "Error: Unable to save to file.\n";
            return;
        }
        
        for (const auto& task : tasks) {
            file << (task.completed ? "1" : "0") << "|"
                 << task.description << "|"
                 << task.dueDate << "\n";
        }
        
        file.close();
    }
    
    void loadFromFile() {
        std::ifstream file(filename);
        if (!file) {
            return;
        }
        
        tasks.clear();
        std::string line;
        
        while (std::getline(file, line)) {
            if (line.empty()) continue;
            
            size_t pos1 = line.find('|');
            if (pos1 == std::string::npos) continue;
            
            size_t pos2 = line.find('|', pos1 + 1);
            if (pos2 == std::string::npos) continue;
            
            bool completed = (line.substr(0, pos1) == "1");
            std::string description = line.substr(pos1 + 1, pos2 - pos1 - 1);
            std::string dueDate = line.substr(pos2 + 1);
            
            Task task(description, dueDate);
            task.completed = completed;
            tasks.push_back(task);
        }
        
        file.close();
    }
    
    void searchTasks(const std::string& keyword) const {
        bool found = false;
        std::cout << "\n SEARCH RESULTS \n";
        
        for (size_t i = 0; i < tasks.size(); ++i) {
            if (tasks[i].description.find(keyword) != std::string::npos) {
                std::cout << i + 1 << ". ";
                if (tasks[i].completed) {
                    std::cout << "[X] ";
                } else {
                    std::cout << "[ ] ";
                }
                
                std::cout << tasks[i].description;
                
                if (!tasks[i].dueDate.empty()) {
                    std::cout << " (Due: " << tasks[i].dueDate << ")";
                }
                
                std::cout << "\n";
                found = true;
            }
        }
        
        if (!found) {
            std::cout << "No matching tasks found.\n";
        }
        
        std::cout << "---\n";
    }
};

void displayMenu() {
    std::cout << "\n TO-DO LIST MENU \n";
    std::cout << "1. Add Task\n";
    std::cout << "2. View Tasks\n";
    std::cout << "3. Mark Task as Complete\n";
    std::cout << "4. Remove Task\n";
    std::cout << "5. Search Tasks\n";
    std::cout << "6. Save and Exit\n";
    std::cout << "Enter your choice: ";
}

std::string getDateInput() {
    std::string date;
    std::cout << "Enter due date (YYYY-MM-DD) or leave empty for no due date: ";
    std::getline(std::cin, date);
    return date;
}

int main() {
    TodoList todoList;
    int choice;
    std::string input;
    
    std::cout << "Welcome to the To-Do List Application!\n";
    
    while (true) {
        displayMenu();
        
        std::getline(std::cin, input);
        try {
            choice = std::stoi(input);
        } catch (...) {
            choice = 0;
        }
        
        switch (choice) {
            case 1: {
                std::string description;
                std::cout << "Enter task description: ";
                std::getline(std::cin, description);
                
                if (!description.empty()) {
                    std::string dueDate = getDateInput();
                    todoList.addTask(description, dueDate);
                } else {
                    std::cout << "Task description cannot be empty.\n";
                }
                break;
            }
            
            case 2:
                todoList.viewTasks();
                break;
                
            case 3: {
                todoList.viewTasks();
                std::cout << "Enter task number to mark as complete: ";
                std::getline(std::cin, input);
                
                try {
                    int taskIndex = std::stoi(input);
                    todoList.markAsComplete(taskIndex);
                } catch (...) {
                    std::cout << "Invalid input.\n";
                }
                break;
            }
            
            case 4: {
                todoList.viewTasks();
                std::cout << "Enter task number to remove: ";
                std::getline(std::cin, input);
                
                try {
                    int taskIndex = std::stoi(input);
                    todoList.removeTask(taskIndex);
                } catch (...) {
                    std::cout << "Invalid input.\n";
                }
                break;
            }
            
            case 5: {
                std::string keyword;
                std::cout << "Enter keyword to search: ";
                std::getline(std::cin, keyword);
                todoList.searchTasks(keyword);
                break;
            }
            
            case 6:
                std::cout << "Saving and exiting...\n";
                todoList.saveToFile();
                return 0;
                
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    }
    
    return 0;
}
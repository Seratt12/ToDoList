#include "stdafx.h"

#include "Task.h"
#include "FileStorage.h"
#include "TaskManager.h"
#include "cxxopts/cxxopts.hpp"

namespace
{
const std::string VERSION = "0.1.0";

bool isDateValid(const std::string& date)
{
  std::regex dateRegex(R"(^\d{4}-(0[1-9]|1[0-2])-(0[1-9]|[12][0-9]|3[01])$)");
  return std::regex_match(date, dateRegex);
}

cxxopts::Options GetOptions()
{
  cxxopts::Options options("ToDo", "ToDo list");
  options.add_options()
    ("h, help", "Print usage")
    ("v, version", "Print version")
    ("a, add", "Add task")
    ("rm, remove", "Remove task")
    ("l, list", "List tasks")
    ("sh, shell", "REPL shell")
    ("s, status", "Mark task as done or undone")
    ("i, index", "task index", cxxopts::value<int>())
    ("file", "File name for input and output", cxxopts::value<std::string>()->default_value("tasks.json"))
    ;

  options.parse_positional({ "index" });

  return options;
}

void ParseTaskTags(std::vector<std::string>& taskTags)
{
  std::cout << "Task tags: " << std::endl;
  std::string tag;
  std::getline(std::cin, tag);
  do
  {
    std::getline(std::cin, tag);
    if (!tag.empty())
      taskTags.push_back(tag);
  } while (!tag.empty());
}

Task ParseTask()
{
  std::string taskName, taskDescription, strDue;
  std::optional<std::string> taskDueDate;
  int taskPriority;
  std::vector<std::string> taskTags;

  std::cout << "Task name: " << std::endl;
  std::getline(std::cin, taskName);

  std::cout << "Task description: " << std::endl;
  std::getline(std::cin, taskDescription);

  std::cout << "Task due date (example: 2025-08-10): " << std::endl;
  std::cin >> strDue;
  if (isDateValid(strDue))
    taskDueDate = strDue;

  std::cout << "Task priority: " << std::endl;
  std::cin >> taskPriority;

  ParseTaskTags(taskTags);

  return Task(1, taskName, taskDescription, taskDueDate, taskPriority, false, taskTags);
}

void PrintTask(const TaskManager& taskManager)
{
  std::cout << "+------+--------------------+--------------------------+------------+----------+---------------+----------------+" << std::endl;
  std::cout << "| ID   | Name               | Description              | Deadline   | Priority | Status        | Tags           |" << std::endl;
  std::cout << "+------+--------------------+--------------------------+------------+----------+---------------+----------------+" << std::endl;

  for (const auto& task : taskManager.GetAll())
  {
    std::cout << task << std::endl;
  }
}

void CheckCommand(const cxxopts::ParseResult& result, const cxxopts::Options options, const std::string& filePath)
{
  std::cout << std::unitbuf;
  if (result.count("help"))
  {
    std::cout << options.help() << std::endl;
    exit(0);
  }

  if (result.count("version"))
  {
    std::cout << "ToDo version " << VERSION << std::endl;
    exit(0);
  }

  std::unique_ptr<ITaskStorage> storage = std::make_unique<FileStorageJSON>(filePath);
  TaskManager taskManager(std::move(storage));

  if (result.count("list"))
  {
    PrintTask(taskManager);
    exit(0);
  }

  if (result.count("add"))
  {
    Task task = ParseTask();
    taskManager.AddTask(task);
    exit(0);
  }

  if (result.count("remove"))
  {
    int index = result["index"].as<int>();
    taskManager.RemoveTask(index);
    exit(0);
  }

  if (result.count("status"))
  {
    int index = result["index"].as<int>();
    taskManager.ToggleDone(index);
    exit(0);
  }

  if (result.count("shell"))
  {
    std::cout << "Type 'help' for commands." << std::endl;
    while (true)
    {
      std::cout << "> ";
      std::string line;
      if (!std::getline(std::cin, line)) break;

      // Разбиваем строку на слова
      std::istringstream iss(line);
      std::string command;
      iss >> command;

      if (command == "exit" || command == "quit")
      {
        std::cout << "Bye!" << std::endl;
        exit(0);
      }
      else if (command == "help")
      {
        std::cout << "Available commands:\n"
          << "  add              - add new task\n"
          << "  list             - list tasks\n"
          << "  remove <id>      - remove task by id\n"
          << "  status <id>      - toggle done/undone\n"
          << "  exit/quit        - leave shell\n";
      }
      else if (command == "add")
      {
        taskManager.AddTask(ParseTask());
      }
      else if (command == "list")
      {
        PrintTask(taskManager);
      }
      else if (command == "remove")
      {
        int index;
        if (iss >> index)
        {
          taskManager.RemoveTask(index);
        }
        else
        {
          std::cout << "Usage: remove <id>" << std::endl;
        }
      }
      else if (command == "status")
      {
        int index;
        if (iss >> index)
        {
          taskManager.ToggleDone(index);
        }
        else
        {
          std::cout << "Usage: status <id>" << std::endl;
        }
      }
      else if (command.empty())
      {
        continue;
      }
      else
      {
        std::cout << "Unknown command. Type 'help' for list." << std::endl;
      }
    }
  }

  std::cout << "Unknown command" << std::endl;
  exit(1);
}
}

int main(int argc, char* argv[])
{
  cxxopts::Options options = GetOptions();

  try
  {
    auto result = options.parse(argc, argv);

    // Файл для ввода/вывода
    std::string fileName = result["file"].as<std::string>();
    // Полный путь
    std::string fullPath = std::string(DATA_DIR_PATH) + "/" + fileName;

    CheckCommand(result, options, fullPath);

    return 0;
  }
  catch (const std::exception& e)
  {
    std::cout << "Error: " << e.what() << std::endl;
    return 1;
  }
}
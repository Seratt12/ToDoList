#include "stdafx.h"

#include "Task.h"
#include "FileStorage.h"
#include "TaskManager.h"

int main(int, char **)
{
  std::unique_ptr<IStorage> storage = std::make_unique<FileStorageJSON>("data/tasks.json");
  TaskManager taskManager(std::move(storage));

  for (const auto &task : taskManager.GetAll())
  {
    std::cout << task << std::endl;
  }

  std::cout << "---------------------------------------------" << std::endl
            << std::endl;

  /*
  taskManager.AddTask(Task(1, "New task", "", std::nullopt, 3, false, {}));
  */

  /*
  Task *t = taskManager.GetTask(3);
  t->m_description = "New description";
  t->m_priority = 1;
  t->MarkDone();
  t->m_due = "2020-01-01";
  t->m_tags.push_back("tag1");
  taskManager.Save();
  */

  /*
  taskManager.RemoveTask(4);
  */

  for (const auto &task : taskManager.GetAll())
  {
    std::cout << task << std::endl;
  }

  return 0;
}
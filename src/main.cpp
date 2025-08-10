#include "stdafx.h"

#include "Task.h"
#include "FileStorage.h"

int main(int, char **)
{
  json j = j.parse(R"(
    {
      "id": 5,
      "name": "Buy milk",
      "description": "Buy 2L milk",
      "due": "2025-08-15",
      "priority": 2,
      "done": false,
      "tags": ["shopping"]
    })");

  std::cout << j.dump(4) << std::endl;

  Task task2 = from_json(j);
  std::cout << std::endl
            << task2 << std::endl;

  std::unique_ptr<FileStorageJSON> storageJSON = std::make_unique<FileStorageJSON>("data/tasks.json");
  std::vector<Task> tasks = storageJSON->Load();
  std::cout << "Loaded tasks: " << tasks.size() << std::endl;
  for (const auto& task : tasks)
  {
	  std::cout << task << std::endl;
  }

  storageJSON->ChangeFile("data/save.json");
  storageJSON->Save(tasks);
  return 0;
}
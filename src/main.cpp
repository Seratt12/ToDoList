#include "stdafx.h"

#include "Task.h"

int main(int, char **)
{
    Task task{1};
    std::cout << task << std::endl;

    json j = to_json(task);
    std::cout << j.dump(4) << std::endl << std::endl;
    
    j = j.parse(R"(
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
	std::cout << std::endl << task2 << std::endl;
    return 0;
}
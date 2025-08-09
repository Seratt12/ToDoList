#include "stdafx.h"

#include "Task.h"

int main(int, char **)
{
    Task task{1, "Task 1", "Task 1 description", "2024-01-01", 1, false, {}};
    std::cout << task << std::endl;
    return 0;
}
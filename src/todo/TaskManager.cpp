#include "stdafx.h"

#include "TaskManager.h"

#include "Task.h"
#include "FileStorage.h"

TaskManager::TaskManager(std::unique_ptr<IStorage> storage)
    : m_storage(std::move(storage))
{
    m_tasks = m_storage->Load();
}

void TaskManager::AddTask(Task t)
{
    if (GetTask(t.GetId()))
        t.SetId(GenerateId());

    m_tasks.emplace_back(t);
    m_storage->Save(m_tasks);
}

Task *TaskManager::GetTask(uint id)
{
    for (auto &task : m_tasks)
    {
        if (task.GetId() == id)
        {
            return &task;
        }
    }
    return nullptr;
}

bool TaskManager::RemoveTask(uint id)
{
    for (auto it = m_tasks.begin(); it != m_tasks.end(); ++it)
    {
        if (it->GetId() == id)
        {
            m_tasks.erase(it);
            Save();
            return true;
        }
    }
    return false;
}

bool TaskManager::ToggleDone(uint id)
{
    for (auto &task : m_tasks)
    {
        if (task.GetId() == id)
        {
            if (task.GetStatus())
                task.MarkUndone();
            else
                task.MarkDone();
            Save();
            return true;
        }
    }
    return false;
}

std::vector<Task> TaskManager::GetAll() const
{
    return m_tasks;
}

void TaskManager::Save() const
{
    m_storage->Save(m_tasks);
}

uint TaskManager::GenerateId()
{
    if (m_tasks.empty())
        return 1;

    uint maxId = m_tasks[0].GetId();
    for (const auto &task : m_tasks)
    {
        if (task.GetId() > maxId)
            maxId = task.GetId();
    }
    return maxId + 1;
}
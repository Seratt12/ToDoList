#include "stdafx.h"

#include "Task.h"

namespace
{
    /// Получить текущую дату
    std::string GetCurrentDate()
    {
        auto now = std::chrono::system_clock::now();
        std::time_t nowTime = std::chrono::system_clock::to_time_t(now);
        std::tm local_tm = *std::localtime(&nowTime);

        std::stringstream timeStringStream;
        timeStringStream << std::put_time(&local_tm, "%Y-%m-%d");

        return timeStringStream.str();
    }

    /// Проверить, содержит ли JSON все необходимые атрибуты для создания задачи
    bool CheckContainsAttributes(const json &j)
    {
        return j.contains("id") && j.contains("name") && j.contains("description") &&
               j.contains("due") && j.contains("priority") && j.contains("done") && j.contains("tags");
    }
}

json to_json(const Task &t)
{
    json j = {
        {"id", t.GetId()},
        {"name", t.m_name},
        {"description", t.m_description},
        {"due", t.m_due},
        {"priority", t.m_priority},
        {"done", t.GetStatus()},
        {"tags", t.m_tags}};

    return j;
}

Task from_json(const json &j)
{
    if (CheckContainsAttributes(j))
    {
        uint id = j["id"].get<uint>();
        std::string name = j["name"].get<std::string>();
        std::string description = j["description"].get<std::string>();
        std::optional<std::string> due = j["due"].is_null() ? std::nullopt : std::make_optional(j["due"].get<std::string>());
        int priority = j["priority"].get<int>();
        bool done = j["done"].get<bool>();
        std::vector<std::string> tags = j["tags"].get<std::vector<std::string>>();

        return Task(id, name, description, due, priority, done, tags);
    }
    throw std::exception("Invalid JSON for Task");
}

std::ostream &operator<<(std::ostream &os, const Task &task)
{
    task.Print(os);
    return os;
}

//
// Task
//

Task::Task(const uint id) : m_id(id)
{
}

Task::Task(
    const uint id,
    const std::string &name,
    const std::string &description,
    const std::optional<std::string> &due,
    const int priority,
    const bool done,
    const std::vector<std::string> tags)
    : m_id(id),
      m_name(name),
      m_description(description),
      m_due(due),
      m_priority(priority),
      m_done(done),
      m_tags(tags)
{
}

uint Task::GetId() const
{
    return m_id;
}

bool Task::GetStatus() const
{
    return m_done;
}

void Task::MarkDone()
{
    if (m_done)
    {
        std::cout << "Task is already done" << std::endl;
        return;
    }
    m_done = true;
}
void Task::MarkUndone()
{
    if (!m_done)
    {
        std::cout << "Task is already undone" << std::endl;
        return;
    }
    m_done = false;
}

bool Task::IsOverdue() const
{
    std::string currDate = GetCurrentDate();
    return m_due < currDate;
}

void Task::Print(std::ostream &os) const
{
    os << "Task " << m_id << ": " << m_name << std::endl;
    os << "Description: " << m_description << std::endl;
    if (m_due)
        os << "Deadline: " << m_due.value() << std::endl;
    os << "Priority: " << m_priority << std::endl;
    os << "Status: " << (m_done ? "Complete" : "Not completed") << std::endl;
    if (m_tags.size() > 0)
    {
        os << "Tags: ";
        for (const std::string &tag : m_tags)
        {
            os << tag << " ";
        }
        os << std::endl;
    }
}

void Task::SetId(const uint newId)
{
    m_id = newId;
}

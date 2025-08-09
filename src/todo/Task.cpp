#include "stdafx.h"
#include "Task.h"

namespace
{
    std::string GetCurrentDate()
    {
        auto now = std::chrono::system_clock::now();
        std::time_t nowTime = std::chrono::system_clock::to_time_t(now);
        std::tm local_tm = *std::localtime(&nowTime);

        std::stringstream timeStringStream;
        timeStringStream << std::put_time(&local_tm, "%Y-%m-%d");

        return timeStringStream.str();
    }
}

std::ostream &operator<<(std::ostream &os, const Task &task)
{
    task.Print(os);
    return os;
}

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

void Task::markDone()
{
    if (m_done)
    {
        std::cout << "Task is already done" << std::endl;
        return;
    }
    m_done = true;
}
void Task::markUndone()
{
    if (!m_done)
    {
        std::cout << "Task is already undone" << std::endl;
        return;
    }
    m_done = false;
}

bool Task::isOverdue() const
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

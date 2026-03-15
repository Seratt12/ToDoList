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
bool CheckContainsAttributes(const json& j)
{
    return j.contains("id") && j.contains("name") && j.contains("description") &&
        j.contains("due") && j.contains("priority") && j.contains("done") && j.contains("tags");
}

size_t displayWidth(const std::string& str)
{
    size_t width = 0;
    for (size_t i = 0; i < str.size(); )
    {
        unsigned char c = str[i];
        if (c <= 0x7F)
        { // ASCII
            width += 1;
            i += 1;
        }
        else if ((c & 0xE0) == 0xC0)
        { // 2-byte UTF-8
            width += 1;
            i += 2;
        }
        else if ((c & 0xF0) == 0xE0)
        { // 3-byte UTF-8 (русские)
            width += 1;
            i += 3;
        }
    }
    return width;
}

std::string padRight(const std::string& s, size_t w)
{
    size_t len = displayWidth(s);
    if (len >= w) return s.substr(0, w);
    return s + std::string(w - len, ' ');
}
}

json to_json(const Task& task)
{
    json jsonTask;

    jsonTask["id"] = task.GetId();
    jsonTask["name"] = task.m_name;
    jsonTask["description"] = task.m_description;
    jsonTask["due"] = task.m_due.value_or(nullptr);
    jsonTask["priority"] = task.m_priority;
    jsonTask["done"] = task.GetStatus();
    jsonTask["tags"] = task.m_tags;

    return jsonTask;
}

Task from_json(const json& j)
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

std::ostream& operator<<(std::ostream& os, const Task& task)
{
    task.Print(os);
    return os;
}

//
// Task
//

Task::Task(const uint id) : m_id(id)
{ }

Task::Task(
    const uint id,
    const std::string& name,
    const std::string& description,
    const std::optional<std::string>& due,
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
{ }

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

void Task::Print(std::ostream& os) const
{
    std::string deadlineStr = m_due ? m_due.value() : "-";
    std::string statusStr = m_done ? "\033[32mComplete\033[0m" : "\033[33mNot completed\033[0m";

    if (m_due && IsOverdue() && !m_done)
    {
        deadlineStr = "\033[31m" + deadlineStr + "\033[0m"; // красный для просроченных
    }

    // Склеиваем теги
    std::ostringstream tags;
    for (size_t i = 0; i < m_tags.size(); ++i)
    {
        tags << m_tags[i];
        if (i + 1 < m_tags.size()) tags << ", ";
    }

    os << "| " << std::setw(4) << std::right << m_id
        << " | " << padRight(m_name, 18)
        << " | " << padRight(m_description, 24)
        << " | " << std::setw(10) << std::left << deadlineStr
        << " | " << std::setw(8) << std::right << m_priority
        << " | " << padRight(statusStr, 22)
        << " | " << padRight(tags.str(), 14)
        << " |";
}

void Task::SetId(const uint newId)
{
    m_id = newId;
}

#include "stdafx.h"
#include "FileStorage.h"
#include "Task.h"

FileStorageJSON::FileStorageJSON(const std::string& filename)
    : m_filename(filename)
{ }

std::vector<Task> FileStorageJSON::Load()
{
    std::ifstream file(m_filename);
    if (file.is_open() && file.peek() != std::ifstream::traits_type::eof())
    {
        try
        {
            json j;
            file >> j;

            std::vector<Task> tasks;
            if (j.is_array())
            {
                for (const auto& task : j)
                    tasks.emplace_back(from_json(task));
                return tasks;
            }
        }
        catch (const json::parse_error& e)
        {
            throw std::runtime_error("JSON parse error: " + std::string(e.what()) + " in file: " + m_filename);
        }
        catch (const std::exception& e)
        {
            throw std::runtime_error("Error loading tasks from file: " + m_filename + ". " + e.what());
        }
    }
    return {};
}

void FileStorageJSON::Save(const std::vector<Task>& tasks)
{
    if (tasks.empty())
        return;

    std::ofstream file(m_filename);
    if (!file.is_open())
        throw std::runtime_error("Failed to open file for writing: " + m_filename);

    json j = json::array();
    for (const auto& task : tasks)
        j.emplace_back(to_json(task));

    file << std::setw(4) << j << std::endl;
}
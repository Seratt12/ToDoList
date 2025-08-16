#include "stdafx.h"

#include "Localization.h"

Localization::Localization(Language l)
{
    m_lang = l;
    if (m_lang == Language::RU)
    {
        m_strings["name"] = u8"Список задач";
        m_strings["task_name"] = u8"Имя задачи";
        m_strings["task_description"] = u8"Описание задачи";
        m_strings["task_due"] = u8"Дата выполнения (пример: 2025-08-10)";
        m_strings["task_priority"] = u8"Приоритет задачи";
        m_strings["task_tags"] = u8"Теги задачи (пустая строка для завершения ввода)";
        m_strings["help"] = u8"Вывести помощь";
        m_strings["version"] = u8"Версия программы";
        m_strings["add"] = u8"Добавить задачу";
        m_strings["list"] = u8"Список задач";
        m_strings["rm"] = u8"Удалить задачу";
		m_strings["mark"] = u8"Отметить задачу как выполненную или невыполненную";
		m_strings["shell"] = u8"Интерактивная оболочка (REPL) для работы с задачами";
		m_strings["index"] = u8"Индекс задачи (для удаления или изменения статуса)";
		m_strings["file"] = u8"Имя файла для ввода и вывода задач";
    }
    else if (m_lang == Language::EN)
    {
		m_strings["name"] = "ToDo List";
        m_strings["task_name"] = "Task name";
        m_strings["task_description"] = "Task description";
        m_strings["task_due"] = "Task due date (example: 2025-08-10)";
        m_strings["task_priority"] = "Task priority";
        m_strings["task_tags"] = "Task tags (empty line to finish)";
        m_strings["help"] = "Print help";
        m_strings["version"] = "Version";
        m_strings["add"] = "Add task";
        m_strings["list"] = "List tasks";
        m_strings["rm"] = "Remove task";
        m_strings["mark"] = "Mark task as done or undone";
		m_strings["shell"] = "Interactive shell (REPL) for task management";
		m_strings["index"] = "Task index (for removal or status change)";
		m_strings["file"] = "File name for input and output tasks";
	}
	else
	{
		throw std::invalid_argument("Unsupported language");
    }
}

std::string Localization::operator[](const std::string& key) const
{
    return m_strings.at(key);
}
#pragma once

#pragma warning(disable : 4996)

class TaskManager;

/**
 * @class Task
 * @brief Базовый класс задачи
 */
class Task
{
public:
    Task(const uint id);

    Task(
        const uint id,
        const std::string& name,
        const std::string& description,
        const std::optional<std::string>& due,
        const int priority,
        const bool done,
        const std::vector<std::string> tags);

    /**
     * @brief Возвращает ID задачи
     * @return ID задачи
     */
    uint GetId() const;

    /**
     * @brief Узнать статус задачи
     * @return Статус задачи
     */
    bool GetStatus() const;

    /**
     * @brief Изменить статус задачи на выполнено
     */
    void MarkDone();

    /**
     * @brief Изменить статус задачи на не выполнено
     * @note По умолчанию задача не выполнена
     */
    void MarkUndone();

    /**
     * @brief Узнать просрочена ли задача
     * @return true - задача просрочена, false - нет
     */
    bool IsOverdue() const;

    /**
     * @brief Вывести информацию о задаче
     */
    void Print(std::ostream& os) const;

    /// @brief Крайняя дата выполнения задачи
    /// @note Строка в формате YYYY-MM-DD
    std::optional<std::string> m_due = std::nullopt;
    /// Название задачи
    std::string m_name = "New task";
    /// Описание задачи
    std::string m_description;
    /// Приоритет задачи
    int m_priority = 0;
    /// Теги задачи
    std::vector<std::string> m_tags;

private:
    /**
     * @brief Изменяет ID задачи
     */
    void SetId(const uint newId);

    /// ID задачи
    unsigned int m_id;
    /// Статус задачи
    bool m_done = false;

    friend class TaskManager;
};

std::ostream& operator<<(std::ostream& os, const Task& task);

/**
 * @brief Сериализует в json
 * @param t Таск, который нужно сериализовать
 */
json to_json(const Task& t);

/**
 * @brief Десериализует из json
 * @param j Объект откуда будет прочтён таск
 * @return Нужный таск
 */
Task from_json(const json& j);

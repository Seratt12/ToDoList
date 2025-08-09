#pragma once

#pragma warning(disable : 4996)

using uint = unsigned int;

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
        const std::string &name,
        const std::string &description,
        const std::optional<std::string> &due,
        const int priority,
        const bool done,
        const std::vector<std::string> tags
    );

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
    void markDone();

    /**
     * @brief Изменить статус задачи на не выполнено
     * @note По умолчанию задача не выполнена
     */
    void markUndone();

    /**
     * @brief Узнать просрочена ли задача
     * @return true - задача просрочена, false - нет
     */
    bool isOverdue() const;

    /**
     * @brief Вывести информацию о задаче
     */
    void Print(std::ostream &os) const;

    /// @brief Крайняя дата выполнения задачи
    /// @note Строка в формате YYYY-MM-DD
    std::optional<std::string> m_due = std::nullopt;
    /// Название задачи
    std::string m_name = "New task";
    /// Описание задачи
    std::string m_description;
    /// Приоритет задачи
    int m_priority = 0;

private:
    /// Теги задачи
    std::vector<std::string> m_tags;
    /// ID задачи
    unsigned int m_id;
    /// Статус задачи
    bool m_done = false;
};

std::ostream &operator<<(std::ostream &os, const Task &task);
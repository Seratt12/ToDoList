#pragma once

class Task;
class IStorage;

/**
 * @class TaskManager
 * @brief Класс для управления задачами
 */
class TaskManager
{
public:
    /**
     * @brief Конструктор для инициализации менеджера задач
     * @param storage Указатель на хранилище задач'
     */
    TaskManager(std::unique_ptr<IStorage> storage);

    /**
     * @brief Добавляет и сохраняет задачу.
     * @param t Добавляемая задача
     * @warning Если id уже есть в коллекции, то будет присвоен новый уникальный id
     */
    void AddTask(Task t);

    /**
     * @brief Получить задачу по ID
     * @param id Идентификатор задачи
     */
    Task* GetTask(uint id);

    /**
     * @brief Удаляет задачу по ID.
     * @param id Идентификатор задачи
     * @return true, если задача была найдена и удалена, иначе false
     */
    bool RemoveTask(uint id);

    /**
     * @brief Изменяет статус задачи
     * @param id Идентификатор задачи
     * @return true, если задача была найдена и статус изменен, иначе false
     */
    bool ToggleDone(uint id);

    /**
     * @brief Получить все задачи
     * @return Вектор всех задач
     */
    std::vector<Task> GetAll() const;

    /**
     * @brief Сохранить состояние вектора задач в хранилище
     */
    void Save() const;

private:
    /**
     * @brief Генерирует уникальный идентификатор задачи
     */
    uint GenerateId();

    /// Вектор задач
    std::vector<Task> m_tasks;
    /// Хранилище задач
    std::unique_ptr<IStorage> m_storage;
};
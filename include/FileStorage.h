#pragma once

class Task;

/**
 * @class ITaskStorage
 * @brief Интерфейс хранения задач
 */
class ITaskStorage
{
public:
    virtual std::vector<Task> Load() = 0;
    virtual void Save(const std::vector<Task>& tasks) = 0;
    virtual ~ITaskStorage() = default;
};

/**
 * @class FileStorageJSON
 * @brief Класс для хранения задач в формате JSON
 */
class FileStorageJSON : public ITaskStorage
{
public:
    /**
     * @brief Конструктор для инициализации хранилища задач JSON
     * @param filename Путь к файлу для хранения задач в формате JSON
     */
    FileStorageJSON(const std::string& filename);
    ~FileStorageJSON() override = default;

    /**
     * @brief Загружает задачи из файла
     * @return Вектор задач
     */
    std::vector<Task> Load() override;

    /**
     * @brief Сохраняет список задач в файл
     * @param tasks Вектор задач для сохранения
     */
    void Save(const std::vector<Task>& tasks) override;
    void ChangeFile(const std::string& filename) { m_filename = filename; }

private:
    /// Поле хранит путь до файла
    std::string m_filename;
};
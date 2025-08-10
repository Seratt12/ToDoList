#pragma once

class Task;

class IStorage
{
public:
    virtual std::vector<Task> Load() = 0;
    virtual void Save(const std::vector<Task> &tasks) = 0;
    virtual ~IStorage() = default;
};

class FileStorageJSON : public IStorage
{
public:
    FileStorageJSON(const std::string &filename);
    ~FileStorageJSON() override = default;

    std::vector<Task> Load() override;
    void Save(const std::vector<Task> &tasks) override;
	void ChangeFile(const std::string& filename) { m_filename = filename; }

private:
    std::string m_filename;
};
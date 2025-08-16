#pragma once

enum class Language { RU, EN };

struct Localization
{
    Localization(Language l);
    std::string operator[](const std::string& key) const;
private:
    Language m_lang;
    std::unordered_map<std::string, std::string> m_strings;
};
#pragma once

#include <vector>
#include <string>
#include <map>
#include <mutex>

struct Entry {
    size_t doc_id;
    size_t count;

    bool operator==(const Entry& other) const {
        return (doc_id == other.doc_id && count == other.count);
    }
};

class InvertedIndex {
public:
    InvertedIndex() = default;

    /**
     * Обновление или заполнение базы документов
     * @param input_docs Содержимое документов
     */
    void UpdateDocumentBase(std::vector<std::string> input_docs);

    /**
     * Получение частоты вхождений слова
     * @param word Искомое слово
     * @return Вектор пар {doc_id, count}
     */
    std::vector<Entry> GetWordCount(const std::string& word);

private:
    std::vector<std::string> docs; // Хранит исходные тексты документов
    std::map<std::string, std::vector<Entry>> freq_dictionary; // Частотный словарь
    std::mutex dict_mutex; // Для thread-safe доступа к freq_dictionary

    /**
     * Индексация одного документа
     * @param doc_id Идентификатор документа
     */
    void IndexDocument(size_t doc_id);
};
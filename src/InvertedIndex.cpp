#include "invertedindex.h"
#include <algorithm>
#include <sstream>
#include <thread>
#include <unordered_map>

void InvertedIndex::UpdateDocumentBase(std::vector<std::string> input_docs) {
    docs = std::move(input_docs);
    freq_dictionary.clear();

    std::vector<std::thread> threads;
    for (size_t doc_id = 0; doc_id < docs.size(); ++doc_id) {
        threads.emplace_back(&InvertedIndex::IndexDocument, this, doc_id);
    }

    for (auto& thread : threads) {
        thread.join();
    }
}

std::vector<Entry> InvertedIndex::GetWordCount(const std::string& word) {
    auto it = freq_dictionary.find(word);
    if (it != freq_dictionary.end()) {
        return it->second;
    }
    return {};
}

void InvertedIndex::IndexDocument(size_t doc_id) {
    const std::string& text = docs[doc_id];
    std::unordered_map<std::string, size_t> word_counts;

    // Разбиение текста на слова и подсчет частот
    std::istringstream iss(text);
    std::string word;
    while (iss >> word) {
        ++word_counts[word];
    }

    // Обновление основного словаря с синхронизацией
    std::lock_guard<std::mutex> lock(dict_mutex);
    for (const auto& [word, count] : word_counts) {
        freq_dictionary[word].push_back({doc_id, count});
    }
}
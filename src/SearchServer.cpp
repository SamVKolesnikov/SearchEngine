#include "searchserver.h"
#include <algorithm>
#include <map>
#include <sstream>

std::vector<std::vector<RelativeIndex>> SearchServer::search(const std::vector<std::string>& queries_input) {
    std::vector<std::vector<RelativeIndex>> results;

    for (const auto& query : queries_input) {
        if (query.empty()) continue;

        // Разбиваем запрос на слова
        std::vector<std::string> words;
        std::istringstream iss(query);
        std::string word;
        while (iss >> word) {
            words.push_back(word);
        }

        // Получаем уникальные слова, отсортированные по редкости
        auto sorted_words = sortWordsByRarity(words);

        if (!sorted_words.empty()) {
            results.push_back(processQuery(sorted_words));
        }
    }

    return results;
}

std::vector<RelativeIndex> SearchServer::processQuery(const std::vector<std::string>& query_words) {
    std::vector<size_t> candidate_docs;
    std::vector<RelativeIndex> result;

    // Поиск документов-кандидатов
    for (const auto& word : query_words) {
        auto entries = _index.GetWordCount(word);
        if (entries.empty()) {
            return {};
        }

        if (candidate_docs.empty()) {
            // Первое слово - добавляем все документы
            for (const auto& entry : entries) {
                candidate_docs.push_back(entry.doc_id);
            }
        } else {
            // Фильтрация: оставляем только docs, содержащие текущее слово
            std::vector<size_t> new_candidates;
            for (const auto& entry : entries) {
                if (std::find(candidate_docs.begin(), candidate_docs.end(), entry.doc_id) != candidate_docs.end()) {
                    new_candidates.push_back(entry.doc_id);
                }
            }
            candidate_docs = std::move(new_candidates);

            if (candidate_docs.empty()) {
                return {};
            }
        }
    }

    // Расчет релевантности
    std::vector<size_t> abs_relevance(candidate_docs.size(), 0);
    size_t max_relevance = 0;

    for (size_t i = 0; i < candidate_docs.size(); ++i) {
        for (const auto& word : query_words) {
            auto entries = _index.GetWordCount(word);
            for (const auto& entry : entries) {
                if (entry.doc_id == candidate_docs[i]) {
                    abs_relevance[i] += entry.count;
                }
            }
        }
        if (abs_relevance[i] > max_relevance) {
            max_relevance = abs_relevance[i];
        }
    }

    // Формирование результатов
    for (size_t i = 0; i < candidate_docs.size(); ++i) {
        if (max_relevance > 0) {
            result.push_back({
                                     candidate_docs[i],
                                     static_cast<float>(abs_relevance[i]) / max_relevance
                             });
        }
    }

    // Сортировка по убыванию релевантности
    std::sort(result.begin(), result.end(), [](const RelativeIndex& a, const RelativeIndex& b) {
        return a.rank > b.rank || (a.rank == b.rank && a.doc_id < b.doc_id);
    });

    return result;
}

std::vector<std::string> SearchServer::sortWordsByRarity(const std::vector<std::string>& words) {
    std::vector<std::string> unique_words;
    std::map<std::string, size_t> word_rarity;

    // Получаем уникальные слова и их общую частоту
    for (const auto& word : words) {
        if (word_rarity.find(word) == word_rarity.end()) {
            word_rarity[word] = 0;
            auto entries = _index.GetWordCount(word);
            for (const auto& entry : entries) {
                word_rarity[word] += entry.count;
            }
            unique_words.push_back(word);
        }
    }

    // Сортировка по возрастанию частоты (от самых редких)
    std::sort(unique_words.begin(), unique_words.end(),
              [&word_rarity](const std::string& a, const std::string& b) {
                  return word_rarity[a] < word_rarity[b];
              });

    return unique_words;
}
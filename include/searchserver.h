#pragma once
#ifndef SEARCHSERVER_H
#define SEARCHSERVER_H

#include "invertedindex.h"
#include <vector>
#include <string>
#include <algorithm>

struct RelativeIndex {
    size_t doc_id;
    float rank;

    bool operator==(const RelativeIndex& other) const {
        return (doc_id == other.doc_id && rank == other.rank);
    }
};

class SearchServer {
public:
    /**
     * @param idx Ссылка на инвертированный индекс
     */
    explicit SearchServer(InvertedIndex& idx, size_t max_resp = 5) : _index(idx), max_responses(max_resp) {}
//    SearchServer(InvertedIndex& idx) : _index(idx) {} //Было изначально

    /**
     * Обработка поисковых запросов
     * @param queries_input Вектор запросов из requests.json
     * @return Вектор результатов для каждого запроса
     */
    std::vector<std::vector<RelativeIndex>> search(const std::vector<std::string>& queries_input);

private:
    InvertedIndex& _index;
    size_t max_responses; //Добавлено

    /**
     * Обработка одного запроса
     * @param query_words Уникальные слова запроса
     * @return Отсортированный вектор результатов
     */
    std::vector<RelativeIndex> processQuery(const std::vector<std::string>& query_words);

    /**
     * Сортировка слов по возрастанию частоты встречаемости
     * @param words Вектор слов
     * @return Отсортированный вектор слов
     */
    std::vector<std::string> sortWordsByRarity(const std::vector<std::string>& words);
};

#endif // SEARCHSERVER_H
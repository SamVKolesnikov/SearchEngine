#pragma once

#include "searchserver.h"  // Для доступа к RelativeIndex
#include <vector>
#include <string>
#include <utility> // для std::pair
#include "nlohmann/json.hpp" // для работы с JSON

class ConverterJSON {
public:
    ConverterJSON();

    /**
     * Получение содержимого файлов
     * @return Список с содержимым файлов из config.json
     * @throws std::exception Если файлы не найдены или config.json некорректен
     */
    std::vector<std::string> GetTextDocuments();

    /**
     * Получение максимального количества ответов
     * @return Лимит ответов из config.json (по умолчанию 5)
     */
    int GetResponsesLimit();

    /**
     * Получение поисковых запросов
     * @return Список запросов из requests.json
     * @throws std::exception Если файл имеет неверный формат
     */
    std::vector<std::string> GetRequests();

    /**
     * Запись результатов поиска
     * @param answers Вектор результатов для каждого запроса:
     *        Каждый элемент - вектор пар {docid, rank}, отсортированный по убыванию rank
     */
    void putAnswers(const std::vector<std::vector<RelativeIndex>>& answers);

    void putRequests(const std::vector<std::string>& requests);

private:
    nlohmann::json config_;
    nlohmann::json requests_;

    /**
     * Загрузка и валидация config.json
     * @throws std::exception Если файл отсутствует или некорректен
     */
    void LoadConfig();

    /**
     * Загрузка и валидация requests.json
     * @throws std::exception Если файл имеет неверный формат
     */
    void LoadRequests();

    /**
     * Нормализация запроса
     * @param request Входной запрос
     * @return Запрос с одиночными пробелами
     */
    std::string NormalizeRequest(const std::string& request);
};
#include "converterjson.h"
#include "invertedindex.h"
#include "searchserver.h"
#include <iostream>
#include <string>
#include <iomanip>

void printWelcomeMessage() {
    std::cout << "========================================\n"
              << "      Search Engine v1.0\n"
              << "========================================\n\n";
}

void printConfigStatus(const std::vector<std::string>& docs, int max_responses) {
    std::cout << "Configuration loaded successfully:\n"
              << "- Documents to index: " << docs.size() << "\n"
              << "- Max responses per query: " << max_responses << "\n\n";
}

void processUserQueries(SearchServer& server, ConverterJSON& converter) {
    std::vector<std::string> all_queries;

    while (true) {
        std::cout << "\nEnter search query (or 'exit' to finish): ";
        std::string query;
        std::getline(std::cin, query);

        if (query == "exit") break;
        if (query.empty()) continue;

        // Добавляем запрос в общий список
        all_queries.push_back(query);

        // Обработка запроса
        std::cout << "\nProcessing query: \"" << query << "\"\n";
        auto results = server.search({query});

        // Вывод результатов
        if (results.empty() || results[0].empty()) {
            std::cout << "No documents found.\n";
        } else {
            std::cout << "Found " << results[0].size() << " result(s):\n";
            for (const auto& result : results[0]) {
                std::cout << "- Document ID: " << result.doc_id
                          << ", Relevance: " << std::fixed << std::setprecision(3)
                          << result.rank << "\n";
            }
        }

        // Записываем все накопленные запросы в файл
        converter.putRequests(all_queries);

        // Сохраняем результаты (перезаписываем файл)
        auto all_results = server.search(all_queries);
        converter.putAnswers(all_results);
    }
}

int main() {
    try {
        printWelcomeMessage();

        // Инициализация конвертера
        ConverterJSON converter;

        // Загрузка конфигурации
        std::cout << "Loading configuration...\n";
        auto docs = converter.GetTextDocuments();
        int max_responses = converter.GetResponsesLimit();
        printConfigStatus(docs, max_responses);

        // Индексация документов
        std::cout << "Indexing documents...\n";
        InvertedIndex index;
        index.UpdateDocumentBase(docs);
        std::cout << "Indexing completed!\n";

        // Инициализация поискового сервера
        SearchServer server(index, max_responses);

        // Очистка/создание файлов
        std::cout << "\nPreparing output files...\n";
        converter.putRequests({});  // Очищаем requests.json
        converter.putAnswers({});   // Очищаем answers.json

        // Обработка запросов из файла (если есть)
        auto file_requests = converter.GetRequests();
        if (!file_requests.empty()) {
            std::cout << "\nProcessing " << file_requests.size() << " requests from file...\n";
            auto file_results = server.search(file_requests);
            converter.putAnswers(file_results);
            std::cout << "File requests processed.\n";
        }

        // Интерактивный режим
        std::cout << "\n=== Interactive mode ===\n";
        processUserQueries(server, converter);

        std::cout << "\nAll results saved to:\n- requests.json\n- answers.json\n";
        std::cout << "\nThank you for using SearchEngine!\n";
    } catch (const std::exception& e) {
        std::cerr << "\nError: " << e.what() << "\n";
        return 1;
    }

    return 0;
}
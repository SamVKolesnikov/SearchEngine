#include "converterjson.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <iomanip>

using namespace std;

ConverterJSON::ConverterJSON() {
    try {
        LoadConfig();
    } catch (const exception& e) {
        cerr << "Config error: " << e.what() << endl;
        throw;
    }
}

vector<string> ConverterJSON::GetTextDocuments() {
    vector<string> documents;

    for (const auto& file_path : config_["files"]) {
        ifstream file(file_path.get<string>());
        if (file.is_open()) {
            string content((istreambuf_iterator<char>(file)),
                           istreambuf_iterator<char>());
            documents.push_back(content);
        } else {
            cerr << "Warning: File not found - " << file_path << endl;
        }
    }

    return documents;
}

int ConverterJSON::GetResponsesLimit() {
    return config_["config"].value("max_responses", 5);
}

vector<string> ConverterJSON::GetRequests() {
    if (!std::ifstream("requests.json").good()) {               // Добавлена проверка
        return {}; // Возвращаем пустой список, если файла нет
    }
    try {
        LoadRequests();
    } catch (const exception& e) {
        cerr << "Requests error: " << e.what() << endl;
        return {};
    }

    vector<string> requests;
    for (const auto& request : requests_["requests"]) {
        string normalized = NormalizeRequest(request.get<string>());
        if (!normalized.empty()) {
            requests.push_back(normalized);
        }
    }

    return requests;
}

void ConverterJSON::putAnswers(const std::vector<std::vector<RelativeIndex>>& answers) {
    nlohmann::json result;

    for (size_t i = 0; i < answers.size(); ++i) {
        std::string req_id = "request" + std::to_string(i + 1);
        if (req_id.size() < 9) req_id.insert(7, 3 - (req_id.size() - 7), '0');

        if (answers[i].empty()) {
            result["answers"][req_id]["result"] = false;
        }
        else if (answers[i].size() == 1) {
            result["answers"][req_id]["result"] = true;
            result["answers"][req_id]["docid"] = answers[i][0].doc_id;  // Используем doc_id вместо first
            result["answers"][req_id]["rank"] = round(answers[i][0].rank * 1000) / 1000.0;  // Используем rank вместо second
        }
        else {
            result["answers"][req_id]["result"] = true;
            for (const RelativeIndex& entry : answers[i]) {
                result["answers"][req_id]["relevance"].push_back({
                                                                         {"docid", entry.doc_id},  // Используем doc_id
                                                                         {"rank", round(entry.rank * 1000) / 1000.0}  // Используем rank
                                                                 });
            }
        }
    }

    ofstream("answers.json") << setw(2) << result << endl;
}

void ConverterJSON::LoadConfig() {
    ifstream config_file("config.json");
    if (!config_file.is_open()) {
        throw runtime_error("config file is missing");
    }

    config_file >> config_;

    if (config_.empty() || !config_.contains("config")) {
        throw runtime_error("config file is empty");
    }

    if (config_["config"].value("version", "") != "1.0") {
        throw runtime_error("config.json has incorrect file version");
    }
}

void ConverterJSON::putRequests(const std::vector<std::string>& requests) {
    nlohmann::json json_requests;
    json_requests["requests"] = requests;
    std::ofstream("requests.json") << std::setw(2) << json_requests << std::endl;
}

void ConverterJSON::LoadRequests() {
    ifstream requests_file("requests.json");
    if (!requests_file.is_open()) {
        requests_ = nlohmann::json::object();
        return;
    }

    requests_file >> requests_;

    if (!requests_.contains("requests") || !requests_["requests"].is_array()) {
        throw runtime_error("requests.json has invalid format");
    }
}

string ConverterJSON::NormalizeRequest(const string& request) {
    string normalized;
    bool space_flag = false;

    for (char c : request) {
        if (c == ' ') {
            if (!space_flag) {
                normalized += ' ';
                space_flag = true;
            }
        } else if (isalpha(c) && islower(c)) {
            normalized += c;
            space_flag = false;
        }
    }

    // Удаляем начальные/конечные пробелы
    size_t start = normalized.find_first_not_of(' ');
    if (start == string::npos) return "";

    size_t end = normalized.find_last_not_of(' ');
    return normalized.substr(start, end - start + 1);
}
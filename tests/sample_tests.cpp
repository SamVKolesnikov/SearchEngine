#include "nlohmann/json.hpp"
#include "gtest/gtest.h"
#include "../include/invertedindex.h"
#include "../include/searchserver.h"
#include "../include/converterjson.h"

#include <iostream>

// Простейший тест для проверки инфраструктуры
TEST(InfrastructureTest, GTestWorking) {
    EXPECT_TRUE(true);
}

// Тест доступности заголовков проекта
TEST(ProjectHeadersTest, HeadersAvailable) {
// Просто проверяем, что заголовки компилируются
    EXPECT_NO_THROW({
        ConverterJSON converter;
        InvertedIndex index;
        SearchServer server(index);
    });
}

TEST(SampleTestSuite, SampleTestCase) {
    EXPECT_EQ(1, 1);
}

TEST(ProjectTests, JsonHeaderAvailable) {
    // Тест, проверяющий доступность JSON
    nlohmann::json j;
    j["test"] = 123;
    EXPECT_EQ(j["test"], 123);
}

// ТЕСТЫ ИНВЕРТИРОВАННОГО ИНДЕКСА
using namespace std;

void TestInvertedIndexFunctionality(
        const vector<string>& docs,
        const vector<string>& requests,
        const std::vector<vector<Entry> > & expected
) {
    std::vector<std::vector<Entry> > result;
    InvertedIndex idx;
    idx.UpdateDocumentBase(docs);
    for(auto& request : requests) {
        std::vector<Entry> word_count = idx.GetWordCount(request);
        result.push_back(word_count);
    }
    ASSERT_EQ(result, expected);
}

TEST(TestCaseInvertedIndex, TestBasic) {
    const vector<string> docs = {
            "london is the capital of great britain",
            "big ben is the nickname for the Great bell of the striking clock"
    };
    const vector<string> requests = {"london", "the"};
            const vector<vector<Entry>> expected = {
                    {
                            {0, 1}
                    },
                    {
                            {0, 1}, {1, 3}
                    }
            };
            TestInvertedIndexFunctionality(docs, requests, expected);
    }

TEST(TestCaseInvertedIndex, TestBasic2) {
    const vector<string> docs = {
            "milk milk milk milk water water water",
            "milk water water",
            "milk milk milk milk milk water water water water water",
            "americano cappuccino"
    };
    const vector<string> requests = {"milk", "water", "cappuccino"};
        const vector<vector<Entry>> expected = {
            {
            {0, 4}, {1, 1}, {2, 5}
        }, {
            {0, 3}, {1, 2}, {2, 5}
        }, {
            {3, 1}
        }
    };
    TestInvertedIndexFunctionality(docs, requests, expected);
}

TEST(TestCaseInvertedIndex, TestInvertedIndexMissingWord) {
    const vector<string> docs = {
            "a b c d e f g h i j k l",
            "statement"
    };
    const vector<string> requests = {"m", "statement"};
            const vector<vector<Entry>> expected = {
            {

            }, {
                    {1, 1}
            }

    };
    TestInvertedIndexFunctionality(docs, requests, expected);
}



// ТЕСТЫ РАССЧЁТА АБСОЛЮТНОЙ И ОТНОСИТЕЛЬНОЙ РЕЛЕВАНТНОСТЕЙ
TEST(TestCaseSearchServer, TestSimple) {
    const vector<string> docs = {
            "milk milk milk milk water water water",
            "milk water water",
            "milk milk milk milk milk water water water water water",
            "americano cappuccino"
    };
    const vector<string> request = {"milk water", "sugar"};
    const std::vector<vector<RelativeIndex>> expected = {
            {
                    {2, 1},
                    {0, 0.7},
                    {1, 0.3}
            },
            {

            }
    };

    InvertedIndex idx;
    idx.UpdateDocumentBase(docs);

    SearchServer srv(idx);
    std::vector<vector<RelativeIndex> > result = srv.search(request);

    ASSERT_EQ(result, expected);
}

TEST(TestCaseSearchServer, TestTop5) {
    const vector<string> docs = {
            "london is the capital great britain",
            "paris is the capital france",
            "berlin is the capital germany",
            "rome is the capital italy",
            "madrid is the capital spain",
            "moscow is the capital russia"
    };
    const vector<string> request = {"moscow is the capital russian federation"};
    const std::vector<vector<RelativeIndex>> expected = {
            {
                    {5, 1},
                    {0, 0.5},
                    {1, 0.5},
                    {3, 0.5},
            }
    };

    InvertedIndex idx;
    idx.UpdateDocumentBase(docs);

    SearchServer srv(idx);

    std::vector<vector<RelativeIndex> > result = srv.search(request);

    ASSERT_EQ(result, expected);
}



int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);  // Инициализация Google Test
    std::cout << std::endl << "The tests have been launched!\n" << std::endl;
    return RUN_ALL_TESTS();                  // Запуск всех тестов
}
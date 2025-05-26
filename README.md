# Поисковый Движок - 搜索引擎 - SearchEngine
This Project is designed for a wide range of interested users

## 🌍 Мультиязычное описание | 多语言描述 | Multilingual Description
|           🇷🇺 Русский |                                🇨🇳 中文 (简体) |                                🇺🇳 English |
|---------|------------|---------|
| [Описание](#-описание-проекта) |                  [项目描述](#-项目描述) |               [Project Description](#-project-description) |
| [Запуск](#-сборка-и-запуск) |                     [构建与运行](#-构建与运行) |            [Building and Running](#-building-and-running) |
| [Требования](#-стек-технологий-и-требования) |    [技术栈与要求](#-技术栈与要求) |        [Tech Stack & Req-s](#-technology-stack-and-requirements) |
---
---
---
# 🇷🇺 Русский
> ### 📌 Поисковый движок представляет консольное приложение, цель которого – поиск заданных пользователем слов(-а) среди текстовых документов пользователя с выдачей ответа в виде наиболее подходящих запросу документов.

## 📝 Описание проекта
**`SearchEngine`** - это высокопроизводительная поисковая система по текстовым файлам с:
- многопоточным инвертированным индексом для быстрого поиска
- автоматической переиндексацией при изменении файлов 
- ранжированием по релевантности
- поддержкой JSON-конфигурации
- тестированием корректной работы функционала ПО
- поддержкой латиницы для работы пользователя

## 🚀 Сборка и запуск

**1) выполнить следующие команды в терминале:**
```bash
git clone https://github.com/SamVKolesnikov/SearchEngine.git
cd SearchEngine
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build . --config Release
```
**2) дождаться процесса завершения индексирования 6 тестовых файлов;**

**3) следуя инструкциям на экране, ввести слово или слова на английском языке, разделяя их одним пробелом, и нажать клавишу *Enter*;**

**4) результат поиска будет представлен сразу на экране и записан в новые файлы `requests.json` и `answers.json`, созданные программой в коне проекта;**

**5) введение команды `exit` завершает работу программы нажатием клавиши *Enter*.**

### 💡 С результатом работы можно ознакомиться в файлах из пункта 4.
---
**Для использования программы со своими документами необходимо:**

 **1) поместить их в папку `resources` в корне проекта, документы должны содержать набор от 10 до 1000 английских слов, начинающихся со строчной буквы и разделённых одним пробелом; имена документов должны соответствовать шаблону (смотри далее);**
 
 **2) в конфигурационном файле `config.json` (в корне проекта) перед запуском приложения задать названия файлов по шаблону:**
```json
{
    "config": {
            "name": "SearchEngine",
            "version": "1.0",
            "max_responses": 5
    },
    "files": [
            "resources/file001.txt",
            "resources/file002.txt",
            ...
            "resources/fileNNN.txt"
            ]
}
```
---

## 🛠 Стек технологий и требования
- **Язык**: C++17
- **Библиотеки**: 
  - `nlohmann/json` для работы с JSON
  - `Google Test` для модульного тестирования
#### ❗️ Требуется доступ к сети Интернет для подключения библиотек к проекту
- **Сборка**: CMake ≥ 3.14
- **Многопоточность**: std::thread
- **Компилятор:** MinGW (g++) GCC ≥ 9.3 / Clang ≥ 17 / MSVC ≥ 2019
---
---
---
# 🇨🇳 中文 (简体)
> ### 📌 该搜索引擎是一个控制台应用程序，旨在通过用户提供的文本文件中搜索用户输入的关键词，并返回最匹配的文档列表。

## 📝 项目描述
**`SearchEngine`** 是一个高性能的文本文件搜索引擎，具有以下特点：
- 使用多线程倒排索引实现快速搜索
- 文件变更时自动重新索引 
- 按相关性排序结果
- 支持JSON配置文件
- 包含功能测试确保正确性
- 支持拉丁字母用户输入

## 🚀 构建与运行

**1) 在终端执行以下命令：**
```bash
git clone https://github.com/SamVKolesnikov/SearchEngine.git
cd SearchEngine
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build . --config Release
```
**2) 等待程序完成对6个测试文件的索引过程；**

**3) 按照屏幕提示输入英文单词（多个单词用空格分隔），按*Enter*键确认;**

**4) 搜索结果将立即显示在屏幕上，并写入项目根目录新生成的`requests.json`和`answers.json`文件中；**

**5)  输入`exit`命令后按*Enter*键可退出程序。**

### 💡  运行结果可参考第4步生成的文件。
---
**如需使用自定义文档进行搜索，请按以下步骤操作：**

 **1) 将文档放入项目根目录的`resources`文件夹中，文档应包含10-1000个英文单词（小写字母开头，空格分隔），文件名需符合规范（见下文）；**
 
 **2) 在程序运行前，修改项目根目录的`config.json`配置文件，按以下格式指定文件名：**
```json
{
    "config": {
            "name": "SearchEngine",
            "version": "1.0",
            "max_responses": 5
    },
    "files": [
            "resources/file001.txt",
            "resources/file002.txt",
            ...
            "resources/fileNNN.txt"
            ]
}
```
---

## 🛠 技术栈与要求
- **编程语言**: C++17
- **依赖库:**: 
  - `nlohmann/json`用于JSON处理
  - `Google Test`用于单元测试
#### ❗️ 需要联网以下载项目依赖库
- **构建工具:**: CMake ≥ 3.14
- **多线程:**: std::thread
- **编译器:** MinGW (g++) GCC ≥ 9.3 / Clang ≥ 17 / MSVC ≥ 2019
---
---
---
# 🇺🇳 English
> ### 📌 The search engine is a console application designed to find user-specified words within text documents and return the most relevant results.

## 📝 Project Description
**`SearchEngine`** is a high-performance text file search engine with the following features:
- Multi-threaded inverted index for fast searching
- Automatic re-indexing when files are modified 
- Relevance ranking of results
- JSON configuration support
- Unit testing for functionality verification
- Latin alphabet support for user input

## 🚀 Building and Running

**1) Execute the following commands in the terminal:**
```bash
git clone https://github.com/SamVKolesnikov/SearchEngine.git
cd SearchEngine
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build . --config Release
```
**2) Wait for the indexing process to complete (6 test files will be indexed);**

**3) Follow on-screen instructions to enter a word or multiple words (separated by a single space) and press *Enter*;**

**4) Search results will be displayed immediately and saved in newly generated `requests.json` and `answers.json` files in the project root directory;**

**5) To exit the program, type `exit` and press *Enter*.**

### 💡 Results can be reviewed in the files mentioned in step 4.
---
**To use the program with custom documents:**

 **1) Place your files in the `resources` folder (in the project root). Documents must:**

- Contain 10 to 1000 English words (lowercase, space-separated)
- Follow the naming convention (see below)
**
 
 **2) Before running, update the `config.json` file (in the project root) with your filenames:**
```json
{
    "config": {
            "name": "SearchEngine",
            "version": "1.0",
            "max_responses": 5
    },
    "files": [
            "resources/file001.txt",
            "resources/file002.txt",
            ...
            "resources/fileNNN.txt"
            ]
}
```
---

## 🛠 Technology Stack and Requirements
- **Language**: C++17
- **Libraries**: 
  - `nlohmann/json` for JSON processing
  - `Google Test` for unit testing
#### ❗️ Internet connection required for library dependencies
- **Build System**: CMake ≥ 3.14
- **Multithreading**: std::thread
- **Compilers:** MinGW (g++) GCC ≥ 9.3 / Clang ≥ 17 / MSVC ≥ 2019
---
---
---
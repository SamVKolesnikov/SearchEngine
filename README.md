# Поисковый Движок - 搜索引擎 - `SearchEngine`
This Project is designed for a wide range of interested users

## 🌍 Мультиязычное описание | 多语言描述 | Multilingual Description
|           🇷🇺 Русский |                                🇨🇳 中文 (简体) |                                🇺🇳 English |
|---------|------------|---------|
| [Описание](#-описание-проекта) |                  [项目描述](#-项目描述) |               [Project Description](#-project-description) |
| [Запуск](#-сборка-и-запуск) |                     [构建与运行](#-构建与运行) |            [Building and Running](#-building-and-running) |
| [Требования](#-стек-технологий-и-требования) |    [技术栈与要求](#-技术栈与要求) |        [Tech Stack & Requirements](#-technology-stack-and-requirements) |
---
---
---
# 🇷🇺 Русский
> ### 📌 Поисковый Движок представляет консольное приложение, цель которого – быстрый поиск заданных(-ого) пользователем слов(-а) среди множества текстовых документов с выявлением наиболее подходящих запросу файлов.

## 📝 Описание проекта
**`SearchEngine`** - это высокопроизводительная система поиска по текстовым файлам с:
- многопоточным инвертированным индексом для быстрого поиска;
- автоматической переиндексацией при изменении файлов;
- ранжированием по релевантности;
- поддержкой JSON-конфигурации;
- тестированием корректной работы функционала ПО;
- поддержкой латиницы для работы пользователя.

## 🚀 Сборка и запуск

**1) скопировать и выполнить следующие команды в терминале:**
```bash
git clone https://github.com/SamVKolesnikov/SearchEngine.git
cd SearchEngine
mkdir build
cd build
cmake .. -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++
cmake --build .
cd src
./SearchEngine_exe
```
**2) дождаться завершения процесса сборки проекта и индексирования 6 тестовых файлов;**

**3) следуя инструкциям на экране, ввести слово или слова на английском языке, разделяя их одним пробелом, и нажать клавишу *Enter*;**

**4) результат поиска будет представлен сразу на экране и записан в новые файлы `requests.json` и `answers.json`, созданные программой в директории:**
```bash
cd SearchEngine/build/src
```

**5) введение команды `exit` завершает работу программы нажатием клавиши *Enter*.**

### 💡 С результатом работы можно ознакомиться в файлах из пункта 4.

## 🎮 Для использования программы со своими документами необходимо:

 **1) поместить их в папку `resources` в директории выше (пункт 4), документы должны содержать набор от 10 до 1000 английских слов, начинающихся со строчной буквы и разделённых одним пробелом;**

 **1.1) имена документов должны соответствовать шаблону (смотрите далее);**
 
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
### ❗️ После запуска программы прежние файлы `requests.json` и `answers.json` будут безвозвратно утеряны.
 **Запустите собранный проект повторно:**
```bash
./SearchEngine_exe
```
---

## 🛠 Стек технологий и требования
- **Язык**: `C++17`
- **Библиотеки**: 
  - `nlohmann/json` для работы с JSON
  - `Google Test` для модульного тестирования
### ❗️ Требуется доступ к сети Интернет для подключения библиотек к проекту
- **Сборка**: `CMake ≥ 3.14` ([Скачать](https://cmake.org/download/))
- **Многопоточность**: `std::thread`
- **Компилятор:** `MinGW (g++) GCC ≥ 9.3` / `Clang ≥ 17` / `MSVC ≥ 2019`
### ✅ Для тестирования основного функционала проекта запустить в терминале следующий код (если проект собран):
```bash
cd SearchEngine/build/tests
./SearchEngineTests
```
**Результат будет выведен на экран незамедлительно.**

---
## 🫶🏼 Благодарю за внимание и пользование данным пограммным обеспечением!
## **📲 Обратная связь:**

**👨🏼‍💻 Sam V.**

**📨 samvkolesnikov@outlook.com**

---
---
---
# 🇨🇳 中文 (简体)
> ### 📌 本搜索引擎是一个控制台应用程序，旨在快速从大量文本文档中检索用户指定的关键词，并找出最匹配查询的文件。

## 📝 项目描述
**`SearchEngine`** 是一个高性能的文本文件搜索系统，具有以下特点：
- 采用多线程倒排索引实现快速搜索
- 文件修改时自动重新索引 
- 基于相关度进行结果排序
- 支持JSON配置文件
- 包含功能测试确保系统正确性
- 支持拉丁字母用户输入

## 🚀 构建与运行

**1) 复制并执行以下终端命令：**
```bash
git clone https://github.com/SamVKolesnikov/SearchEngine.git
cd SearchEngine
mkdir build
cd build
cmake .. -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++
cmake --build .
cd src
./SearchEngine_exe
```
**2) 等待项目构建完成并完成6个测试文件的索引；**

**3) 按照屏幕提示输入英文单词（多个词用空格分隔），按*Enter*键确认;**

**4) 搜索结果将立即显示并保存到以下目录的新建`requests.json`和`answers.json`文件中：**
```bash
cd SearchEngine/build/src
```

**5)  输入`exit`命令后按*Enter*键可退出程序。**

### 💡  运行结果可查看第4步生成的文件。

## 🎮 使用自定义文档的方法：

 **1) 将文档放入上级目录（第4步）的`resources`文件夹中，文档应包含10-1000个英文单词（小写字母开头，空格分隔）；**
 
 **1.1) 文件名需符合规范（见下文）；**

 **2) 运行前在项目根目录的`config.json`配置文件中按以下格式指定文件：**
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
### ❗️  程序运行后，原有的`requests.json`和`answers.json`文件将被永久覆盖
 **重新运行已构建的项目：**
```bash
./SearchEngine_exe
```
---

## 🛠 技术栈与要求
- **编程语言**: `C++17`
- **依赖库:**: 
  - `nlohmann/json`用于JSON处理
  - `Google Test`用于单元测试
### ❗️ 需要联网以下载项目依赖库
- **构建工具:**: `CMake ≥ 3.14`([下载链接](https://cmake.org/download/))
- **多线程:**: `std::thread`
- **编译器:** `MinGW (g++) GCC ≥ 9.3` / `Clang ≥ 17` / `MSVC ≥ 2019`
### ✅ 测试项目主要功能（项目构建完成后执行）：
```bash
cd SearchEngine/build/tests
./SearchEngineTests
```
**测试结果将立即显示在屏幕上**

---
## 🫶🏼 感谢您对本软件的关注和使用！
## **📲 反馈方式：**

**👨🏼‍💻 Sam V.**

**📨 samvkolesnikov@outlook.com**

---
---
---
# 🇺🇳 English
> ### 📌 The `SearchEngine` is a console application designed for fast retrieval of user-specified keywords across multiple text documents, identifying the most query-relevant files.

## 📝 Project Description
**`SearchEngine`** is a high-performance text file search engine with the following features:
- Multi-threaded inverted index for fast searching;
- Automatic re-indexing upon file modifications;
- Relevance-based ranking of results;
- JSON configuration support;
- Unit testing for functionality verification;
- Latin alphabet support for user input.

## 🚀 Building and Running

**1) Execute the following commands in the terminal:**
```bash
git clone https://github.com/SamVKolesnikov/SearchEngine.git
cd SearchEngine
mkdir build
cd build
cmake .. -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++
cmake --build .
cd src
./SearchEngine_exe
```
**2) Wait for the project compilation and indexing processes to complete (6 test files will be indexed);**

**3) Follow on-screen instructions to input a word or multiple English words (separated by a single space) and press *Enter*;**

**4) Search results will be displayed immediately and saved in newly generated `requests.json` and `answers.json` files in the project directory:**
```bash
cd SearchEngine/build/src
```

**5) To terminate the session, type `exit` and press *Enter*.**

### 💡 Results can be reviewed in the files generated at step 4.

## 🎮 Using Custom Documents:

 **1) Place your files in the parent directory's `resources` folder (from step 4). The documents must:**

- Contain 10 to 1000 English words (lowercase, space-separated);
- Follow the naming convention (see below).
 
 **2) Before running, update the `config.json` file (in the `build/src` directory) with your filenames as follows:**
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
### ❗️ Program execution will permanently overwrite existing `requests.json` and `answers.json` files.
 **Relaunch the built project:**
```bash
./SearchEngine_exe
```
---

## 🛠 Technology Stack and Requirements
- **Language**: `C++17`
- **Libraries**: 
  - `nlohmann/json` for JSON processing
  - `Google Test` for unit testing
### ❗️ Internet connection required for library dependencies
- **Build System**: `CMake ≥ 3.14` ([Download](https://cmake.org/download/))
- **Multithreading**: `std::thread`
- **Compilers:** `MinGW (g++) GCC ≥ 9.3` / `Clang ≥ 17` / `MSVC ≥ 2019`
### ✅ Core functionality testing (after successful build):
```bash
cd SearchEngine/build/tests
./SearchEngineTests
```
**Test results will be displayed immediately.**

---
## 🫶🏼 Thank you for your attention and use of this software!
## **📲 Feedback:**

**👨🏼‍💻 Sam V.**

**📨 samvkolesnikov@outlook.com**

---
---
---
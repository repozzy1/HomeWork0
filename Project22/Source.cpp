#include <iostream>
#include <string>
#include <vector>
#include <algorithm>



// Интерфейс для модуля анализа текста
class IAnalysisModule {
public:
    virtual ~IAnalysisModule() {}
    virtual std::string getName() const = 0;
    virtual void analyze(const std::string& text) = 0;
    virtual std::string getResults() const = 0;
};

// Модуль подсчета слов
class WordCountModule : public IAnalysisModule {
private:
    int wordCount = 0;

public:
    std::string getName() const override { return "Word Count"; }

    void analyze(const std::string& text) override {
        wordCount = 0;
        std::stringstream ss(text);
        std::string word;
        while (ss >> word) {
            wordCount++;
        }
    }

    std::string getResults() const override {
        return "Word count: " + std::to_string(wordCount);
    }
};

// Модуль подсчета символов
class CharacterCountModule : public IAnalysisModule {
private:
    int charCount = 0;

public:
    std::string getName() const override { return "Character Count"; }

    void analyze(const std::string& text) override {
        charCount = text.length();
    }

    std::string getResults() const override {
        return "Character count: " + std::to_string(charCount);
    }
};

// Класс для анализа текста
class TextAnalyzer {
private:
    std::vector<IAnalysisModule*> modules;

public:
    void addAnalysisModule(IAnalysisModule* module) {
        modules.push_back(module);
    }

    void analyzeText(const std::string& text) {
        for (IAnalysisModule* module : modules) {
            module->analyze(text);
        }
    }

    std::string getAnalysisResults() const {
        std::string results;
        for (IAnalysisModule* module : modules) {
            results += module->getName() + ": " + module->getResults() + "\n";
        }
        return results;
    }

    ~TextAnalyzer() {
        for (IAnalysisModule* module : modules) {
            delete module;
        }
    }
};

// Класс для управления выводом данных
class OutputManager {
public:
    void displayResults(const std::string& results) const {
        std::cout << "--- Analysis Results ---" << std::endl;
        std::cout << results << std::endl;
    }
};

int main() {
    // Создаем объекты анализа
    WordCountModule* wordCount = new WordCountModule();
    CharacterCountModule* charCount = new CharacterCountModule();

    // Создаем анализатор текста и добавляем модули
    TextAnalyzer analyzer;
    analyzer.addAnalysisModule(wordCount);
    analyzer.addAnalysisModule(charCount);

    // Получаем текст от пользователя
    std::string text;
    std::cout << "Введите текст для анализа: ";
    std::getline(std::cin, text);

    // Анализируем текст
    analyzer.analyzeText(text);

    // Получаем результаты анализа
    std::string results = analyzer.getAnalysisResults();

    // Выводим результаты
    OutputManager outputManager;
    outputManager.displayResults(results);
}

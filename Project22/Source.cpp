#include <iostream>
#include <string>
#include <vector>
#include <algorithm>



// ��������� ��� ������ ������� ������
class IAnalysisModule {
public:
    virtual ~IAnalysisModule() {}
    virtual std::string getName() const = 0;
    virtual void analyze(const std::string& text) = 0;
    virtual std::string getResults() const = 0;
};

// ������ �������� ����
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

// ������ �������� ��������
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

// ����� ��� ������� ������
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

// ����� ��� ���������� ������� ������
class OutputManager {
public:
    void displayResults(const std::string& results) const {
        std::cout << "--- Analysis Results ---" << std::endl;
        std::cout << results << std::endl;
    }
};

int main() {
    // ������� ������� �������
    WordCountModule* wordCount = new WordCountModule();
    CharacterCountModule* charCount = new CharacterCountModule();

    // ������� ���������� ������ � ��������� ������
    TextAnalyzer analyzer;
    analyzer.addAnalysisModule(wordCount);
    analyzer.addAnalysisModule(charCount);

    // �������� ����� �� ������������
    std::string text;
    std::cout << "������� ����� ��� �������: ";
    std::getline(std::cin, text);

    // ����������� �����
    analyzer.analyzeText(text);

    // �������� ���������� �������
    std::string results = analyzer.getAnalysisResults();

    // ������� ����������
    OutputManager outputManager;
    outputManager.displayResults(results);
}

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>

// Класс Книга
class Book {
public:
    int id;
    std::string title;
    std::string author;
    int year;

    Book(int id, const std::string& title, const std::string& author, int year)
        : id(id), title(title), author(author), year(year) {
    }

    // Перегрузка оператора вывода для удобного отображения информации о книге
    friend std::ostream& operator<<(std::ostream& os, const Book& book) {
        os << "ID: " << book.id << ", Название: " << book.title
            << ", Автор: " << book.author << ", Год: " << book.year;
        return os;
    }
};

// Класс Библиотека
class Library {
private:
    std::unordered_map<int, Book> books; // Используем словарь: id -> Book

public:
    // Добавление книги
    void addBook(const Book& book) {
        if (books.find(book.id) != books.end()) {
            std::cout << "Ошибка: Книга с ID " << book.id << " уже существует." << std::endl;
            return;
        }
        books[book.id] = book;
        std::cout << "Книга \"" << book.title << "\" добавлена в библиотеку." << std::endl;
    }

    // Удаление книги
    void removeBook(int id) {
        if (books.erase(id)) {
            std::cout << "Книга с ID " << id << " удалена из библиотеки." << std::endl;
        }
        else {
            std::cout << "Ошибка: Книга с ID " << id << " не найдена." << std::endl;
        }
    }

    // Поиск книги по ID
    Book* findBook(int id) {
        auto it = books.find(id);
        if (it != books.end()) {
            return &it->second; // Возвращаем указатель на найденную книгу
        }
        return nullptr; // Книга не найдена
    }

    // Поиск книги по названию (неэффективный, но показывает подход)
    std::vector<Book*> findBooksByTitle(const std::string& title) {
        std::vector<Book*> foundBooks;
        for (auto& pair : books) {
            if (pair.second.title == title) {
                foundBooks.push_back(&pair.second);
            }
        }
        return foundBooks;
    }

    // Вывод списка книг
    void displayBooks() const {
        if (books.empty()) {
            std::cout << "Библиотека пуста." << std::endl;
            return;
        }
        std::cout << "Список книг в библиотеке:" << std::endl;
        for (const auto& pair : books) {
            std::cout << pair.second << std::endl;
        }
    }
};

int main() {
    Library library;

    // Добавление книг
    library.addBook(Book(1, "Война и мир", "Лев Толстой", 1869));
    library.addBook(Book(2, "Преступление и наказание", "Федор Достоевский", 1866));
    library.addBook(Book(3, "1984", "Джордж Оруэлл", 1949));

    // Вывод списка книг
    library.displayBooks();

    // Поиск книги
    Book* foundBook = library.findBook(2);
    if (foundBook) {
        std::cout << "Найдена книга: " << *foundBook << std::endl;
    }
    else {
        std::cout << "Книга не найдена." << std::endl;
    }

    // Поиск книг по названию
    std::vector<Book*> foundBooksByTitle = library.findBooksByTitle("Война и мир");
    if (!foundBooksByTitle.empty()) {
        std::cout << "Найдено книг с названием 'Война и мир':" << std::endl;
        for (Book* book : foundBooksByTitle) {
            std::cout << *book << std::endl;
        }
    }
    else {
        std::cout << "Книги с названием 'Война и мир' не найдены." << std::endl;
    }

    // Удаление книги
    library.removeBook(1);
    library.displayBooks();

    return 0;
}
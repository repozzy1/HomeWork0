#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>

// ����� �����
class Book {
public:
    int id;
    std::string title;
    std::string author;
    int year;

    Book(int id, const std::string& title, const std::string& author, int year)
        : id(id), title(title), author(author), year(year) {
    }

    // ���������� ��������� ������ ��� �������� ����������� ���������� � �����
    friend std::ostream& operator<<(std::ostream& os, const Book& book) {
        os << "ID: " << book.id << ", ��������: " << book.title
            << ", �����: " << book.author << ", ���: " << book.year;
        return os;
    }
};

// ����� ����������
class Library {
private:
    std::unordered_map<int, Book> books; // ���������� �������: id -> Book

public:
    // ���������� �����
    void addBook(const Book& book) {
        if (books.find(book.id) != books.end()) {
            std::cout << "������: ����� � ID " << book.id << " ��� ����������." << std::endl;
            return;
        }
        books[book.id] = book;
        std::cout << "����� \"" << book.title << "\" ��������� � ����������." << std::endl;
    }

    // �������� �����
    void removeBook(int id) {
        if (books.erase(id)) {
            std::cout << "����� � ID " << id << " ������� �� ����������." << std::endl;
        }
        else {
            std::cout << "������: ����� � ID " << id << " �� �������." << std::endl;
        }
    }

    // ����� ����� �� ID
    Book* findBook(int id) {
        auto it = books.find(id);
        if (it != books.end()) {
            return &it->second; // ���������� ��������� �� ��������� �����
        }
        return nullptr; // ����� �� �������
    }

    // ����� ����� �� �������� (�������������, �� ���������� ������)
    std::vector<Book*> findBooksByTitle(const std::string& title) {
        std::vector<Book*> foundBooks;
        for (auto& pair : books) {
            if (pair.second.title == title) {
                foundBooks.push_back(&pair.second);
            }
        }
        return foundBooks;
    }

    // ����� ������ ����
    void displayBooks() const {
        if (books.empty()) {
            std::cout << "���������� �����." << std::endl;
            return;
        }
        std::cout << "������ ���� � ����������:" << std::endl;
        for (const auto& pair : books) {
            std::cout << pair.second << std::endl;
        }
    }
};

int main() {
    Library library;

    // ���������� ����
    library.addBook(Book(1, "����� � ���", "��� �������", 1869));
    library.addBook(Book(2, "������������ � ���������", "����� �����������", 1866));
    library.addBook(Book(3, "1984", "������ ������", 1949));

    // ����� ������ ����
    library.displayBooks();

    // ����� �����
    Book* foundBook = library.findBook(2);
    if (foundBook) {
        std::cout << "������� �����: " << *foundBook << std::endl;
    }
    else {
        std::cout << "����� �� �������." << std::endl;
    }

    // ����� ���� �� ��������
    std::vector<Book*> foundBooksByTitle = library.findBooksByTitle("����� � ���");
    if (!foundBooksByTitle.empty()) {
        std::cout << "������� ���� � ��������� '����� � ���':" << std::endl;
        for (Book* book : foundBooksByTitle) {
            std::cout << *book << std::endl;
        }
    }
    else {
        std::cout << "����� � ��������� '����� � ���' �� �������." << std::endl;
    }

    // �������� �����
    library.removeBook(1);
    library.displayBooks();

    return 0;
}
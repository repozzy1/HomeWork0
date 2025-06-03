#include <iostream>
#include <string>
#include <vector>
#include <cmath> // Для pow, M_PI
#include <limits> // Для std::numeric_limits

// Абстрактный класс Shape
class Shape {
private:
    int id;
    std::string name;
    static int nextId; // Статический член для генерации ID

protected:
    // Конструктор (protected, чтобы нельзя было создать объект Shape напрямую)
    Shape(const std::string& name) : name(name), id(nextId++) {
        std::cout << "Shape (constructor) id: " << id << std::endl;
    }

public:
    // Чисто виртуальный метод для вычисления площади
    virtual double getArea() const = 0;

    // Геттер для id
    int getId() const { return id; }

    // Геттер для имени
    std::string getName() const { return name; }

    // Виртуальный деструктор (обязательно!)
    virtual ~Shape() {
        std::cout << "~Shape() - Deconstructor, id: " << id << std::endl;
        //  Не нужно сбрасывать nextId здесь, это приведет к проблемам.  ID генерируются автоматически при создании.
    }

    // Перегрузка оператора вывода
    friend std::ostream& operator<<(std::ostream& os, const Shape& shape) {
        os << "ID: " << shape.getId() << ", Name: " << shape.getName() << ", Area: " << shape.getArea();
        return os;
    }

    // Перегрузка оператора сравнения (по площади)
    bool operator==(const Shape& other) const {
        return std::abs(getArea() - other.getArea()) < 1e-6; // Сравниваем с учетом погрешности
    }

    // Перегрузка оператора сложения (для демонстрации, объединяет площади)
    virtual Shape* operator+(const Shape& other) const = 0;

};

// Инициализация статического члена
int Shape::nextId = 1;

// Класс Circle (наследуется от Shape)
class Circle : public Shape {
private:
    double radius;

public:
    Circle(double radius) : Shape("Circle"), radius(radius) {
        if (radius <= 0) {
            std::cerr << "Ошибка: Радиус должен быть положительным числом." << std::endl;
            this->radius = 1.0; // Устанавливаем минимальное значение по умолчанию
        }
        std::cout << "Circle (constructor) radius: " << radius << std::endl;
    }

    double getRadius() const { return radius; }

    // Переопределение метода вычисления площади
    double getArea() const override {
        return M_PI * radius * radius;
    }

    // Дополнительный метод, специфичный для Circle
    double getDiameter() const {
        return 2 * radius;
    }

    // Перегрузка оператора вывода
    friend std::ostream& operator<<(std::ostream& os, const Circle& circle) {
        os << " [Circle] " << static_cast<const Shape&>(circle) << ", Radius: " << circle.getRadius();
        return os;
    }

    // Перегрузка оператора сложения (объединение площадей)
    Shape* operator+(const Shape& other) const override {
        const Circle* otherCircle = dynamic_cast<const Circle*>(&other);
        if (otherCircle) {
            return new Circle(std::sqrt(getArea() + otherCircle->getArea() / M_PI)); // Создаем новый круг с суммарной площадью
        }
        return nullptr; // Нельзя сложить с другой фигурой
    }

    ~Circle() override {
        std::cout << "~Circle() - Deconstructor, radius: " << radius << std::endl;
    }
};

// Класс Sphere (наследуется от Circle) - трехмерная версия
class Sphere : public Circle {
public:
    Sphere(double radius) : Circle(radius), Shape("Sphere") {
        if (radius <= 0) {
            std::cerr << "Ошибка: Радиус должен быть положительным числом." << std::endl;
            this->Circle::setRadius(1.0); // Используем setRadius, т.к. radius - private
        }
        std::cout << "Sphere (constructor) radius: " << radius << std::endl;
    }

    // Переопределение метода вычисления площади (поверхности сферы)
    double getArea() const override {
        return 4 * M_PI * getRadius() * getRadius(); // Используем getRadius() из Circle
    }

    // Метод для вычисления объема
    double getVolume() const {
        return (4.0 / 3.0) * M_PI * pow(getRadius(), 3); // Используем getRadius()
    }

    // Перегрузка оператора вывода
    friend std::ostream& operator<<(std::ostream& os, const Sphere& sphere) {
        os << " [Sphere] " << static_cast<const Circle&>(sphere) << ", Volume: " << sphere.getVolume();
        return os;
    }

    // Перегрузка оператора сложения (сложение объемов, упрощенно)
    Shape* operator+(const Shape& other) const override {
        const Sphere* otherSphere = dynamic_cast<const Sphere*>(&other);
        if (otherSphere) {
            // Упрощенный вариант:  Объем сложения = сумма объемов, радиус не вычисляется
            double combinedVolume = getVolume() + otherSphere->getVolume();
            return new Sphere(pow((3 * combinedVolume) / (4 * M_PI), 1.0 / 3.0));
        }
        return nullptr; // Нельзя сложить с другой фигурой
    }


    ~Sphere() override {
        std::cout << "~Sphere() - Deconstructor, radius: " << getRadius() << std::endl;
    }
};


// Класс Rectangle (наследуется от Shape)
class Rectangle : public Shape {
private:
    double width;
    double height;

public:
    Rectangle(double width, double height) : Shape("Rectangle"), width(width), height(height) {
        if (width <= 0 || height <= 0) {
            std::cerr << "Ошибка: Ширина и высота должны быть положительными числами." << std::endl;
            this->width = 1.0;
            this->height = 1.0;
        }
        std::cout << "Rectangle (constructor) width: " << width << ", height: " << height << std::endl;
    }

    double getWidth() const { return width; }
    double getHeight() const { return height; }

    // Переопределение метода вычисления площади
    double getArea() const override {
        return width * height;
    }

    // Дополнительный метод, специфичный для Rectangle
    double getDiagonal() const {
        return std::sqrt(width * width + height * height);
    }

    // Перегрузка оператора вывода
    friend std::ostream& operator<<(std::ostream& os, const Rectangle& rectangle) {
        os << " [Rectangle] " << static_cast<const Shape&>(rectangle) << ", Width: " << rectangle.getWidth() << ", Height: " << rectangle.getHeight();
        return os;
    }

    // Перегрузка оператора сложения (объединение площадей)
    Shape* operator+(const Shape& other) const override {
        const Rectangle* otherRectangle = dynamic_cast<const Rectangle*>(&other);
        if (otherRectangle) {
            return new Rectangle(width + otherRectangle->width, height + otherRectangle->height);  //  Создаем новый прямоугольник
        }
        return nullptr; // Нельзя сложить с другой фигурой
    }

    ~Rectangle() override {
        std::cout << "~Rectangle() - Deconstructor, width: " << width << ", height: " << height << std::endl;
    }
};

// Класс Cuboid (наследуется от Rectangle) - трехмерная версия
class Cuboid : public Rectangle {
private:
    double depth;

public:
    Cuboid(double width, double height, double depth) : Rectangle(width, height), Shape("Cuboid"), depth(depth) {
        if (depth <= 0) {
            std::cerr << "Ошибка: Глубина должна быть положительным числом." << std::endl;
            this->depth = 1.0;
        }
        std::cout << "Cuboid (constructor) width: " << getWidth() << ", height: " << getHeight() << ", depth: " << depth << std::endl;
    }

    double getDepth() const { return depth; }

    // Переопределение метода вычисления площади (поверхности параллелепипеда)
    double getArea() const override {
        return 2 * (getWidth() * getHeight() + getWidth() * depth + getHeight() * depth);
    }

    // Метод для вычисления объема
    double getVolume() const {
        return getWidth() * getHeight() * depth; // Используем getWidth() и getHeight() из Rectangle
    }

    // Перегрузка оператора вывода
    friend std::ostream& operator<<(std::ostream& os, const Cuboid& cuboid) {
        os << " [Cuboid] " << static_cast<const Rectangle&>(cuboid) << ", Depth: " << cuboid.getDepth() << ", Volume: " << cuboid.getVolume();
        return os;
    }


    // Перегрузка оператора сложения (сложение объемов, упрощенно)
    Shape* operator+(const Shape& other) const override {
        const Cuboid* otherCuboid = dynamic_cast<const Cuboid*>(&other);
        if (otherCuboid) {
            // Упрощенный вариант: Объем сложения = сумма объемов, размеры не вычисляются
            double combinedVolume = getVolume() + otherCuboid->getVolume();
            // Некорректный способ определения новых размеров (просто для примера)
            //double newWidth = getWidth() + otherCuboid->getWidth();
            //double newHeight = getHeight() + otherCuboid->getHeight();
            //double newDepth = depth;
            return new Cuboid(getWidth(), getHeight(), depth); // (3 * combinedVolume) / (getWidth() * getHeight));
        }
        return nullptr; // Нельзя сложить с другой фигурой
    }

    ~Cuboid() override {
        std::cout << "~Cuboid() - Deconstructor, depth: " << depth << std::endl;
    }
};

// Функция для очистки буфера ввода
void clearInputBuffer() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// Функция для отображения меню
void displayMenu() {
    std::cout << "\nМеню:" << std::endl;
    std::cout << "1. Добавить круг" << std::endl;
    std::cout << "2. Добавить сферу" << std::endl;
    std::cout << "3. Добавить прямоугольник" << std::endl;
    std::cout << "4. Добавить параллелепипед" << std::endl;
    std::cout << "5. Вывести информацию о всех фигурах" << std::endl;
    std::cout << "6. Сравнить две фигуры по площади" << std::endl;
    std::cout << "7. Сложить две фигуры (объединить площади/объемы)" << std::endl;
    std::cout << "8. Завершить работу" << std::endl;
    std::cout << "Выберите пункт меню: ";
}

// Функция для добавления фигуры (универсальная)
void addShape(std::vector<Shape*>& shapes) {
    int choice;
    std::cout << "\nВыберите тип фигуры для добавления:" << std::endl;
    std::cout << "1. Круг" << std::endl;
    std::cout << "2. Сфера" << std::endl;
    std::cout << "3. Прямоугольник" << std::endl;
    std::cout << "4. Параллелепипед" << std::endl;
    std::cout << "Выберите пункт: ";
    std::cin >> choice;
    clearInputBuffer();

    switch (choice) {
    case 1: {
        double radius;
        std::cout << "Введите радиус круга: ";
        std::cin >> radius;
        clearInputBuffer();
        if (radius > 0) {
            shapes.push_back(new Circle(radius));
        }
        else {
            std::cout << "Некорректный радиус." << std::endl;
        }
        break;
    }
    case 2: {
        double radius;
        std::cout << "Введите радиус сферы: ";
        std::cin >> radius;
        clearInputBuffer();
        if (radius > 0) {
            shapes.push_back(new Sphere(radius));
        }
        else {
            std::cout << "Некорректный радиус." << std::endl;
        }
        break;
    }
    case 3: {
        double width, height;
        std::cout << "Введите ширину прямоугольника: ";
        std::cin >> width;
        std::cout << "Введите высоту прямоугольника: ";
        std::cin >> height;
        clearInputBuffer();
        if (width > 0 && height > 0) {
            shapes.push_back(new Rectangle(width, height));
        }
        else {
            std::cout << "Некорректные размеры." << std::endl;
        }

        break;
    }
    case 4: {
        double width, height, depth;
        std::cout << "Введите ширину параллелепипеда: ";
        std::cin >> width;
        std::cout << "Введите высоту параллелепипеда: ";
        std::cin >> height;
        std::cout << "Введите глубину параллелепипеда: ";
        std::cin >> depth;
        clearInputBuffer();

        if (width > 0 && height > 0 && depth > 0) {
            shapes.push_back(new Cuboid(width, height, depth));
        }
        else {
            std::cout << "Некорректные размеры." << std::endl;
        }
        break;
    }
    default:
        std::cout << "Неверный выбор." << std::endl;
        break;
    }
}

// Функция для вывода информации о всех фигурах
void displayAllShapes(const std::vector<Shape*>& shapes) {
    if (shapes.empty()) {
        std::cout << "Нет фигур для отображения." << std::endl;
        return;
    }
    for (const Shape* shape : shapes) {
        std::cout << *shape << std::endl; // Используем перегруженный оператор <<
    }
}

// Функция для сравнения двух фигур по площади
void compareShapes(const std::vector<Shape*>& shapes) {
    if (shapes.size() < 2) {
        std::cout << "Недостаточно фигур для сравнения." << std::endl;
        return;
    }

    int index1, index2;
    std::cout << "Введите индекс первой фигуры: ";
    std::cin >> index1;
    clearInputBuffer();
    std::cout << "Введите индекс второй фигуры: ";
    std::cin >> index2;
    clearInputBuffer();

    if (index1 < 0 || index1 >= shapes.size() || index2 < 0 || index2 >= shapes.size()) {
        std::cout << "Неверный индекс." << std::endl;
        return;
    }

    if (*shapes[index1] == *shapes[index2]) { // Используем перегруженный оператор ==
        std::cout << "Фигуры имеют примерно одинаковую площадь." << std::endl;
    }
    else {
        std::cout << "Фигуры имеют разную площадь." << std::endl;
    }
}

// Функция для сложения двух фигур (объединения площадей/объемов)
void sumShapes(std::vector<Shape*>& shapes) {
    if (shapes.size() < 2) {
        std::cout << "Недостаточно фигур для сложения." << std::endl;
        return;
    }

    int index1, index2;
    std::cout << "Введите индекс первой фигуры: ";
    std::cin >> index1;
    clearInputBuffer();
    std::cout << "Введите индекс второй фигуры: ";
    std::cin >> index2;
    clearInputBuffer();

    if (index1 < 0 || index1 >= shapes.size() || index2 < 0 || index2 >= shapes.size()) {
        std::cout << "Неверный индекс." << std::endl;
        return;
    }

    Shape* result = nullptr;
    result = *shapes[index1] + *shapes[index2];

    if (result != nullptr) {
        std::cout << "Результат сложения: " << *result << std::endl;
        shapes.push_back(result); // Добавляем результат в вектор
    }
    else {
        std::cout << "Сложение этих фигур невозможно." << std::endl;
    }
}


int main() {
    std::vector<Shape*> shapes;
    int choice;

    do {
        displayMenu();
        std::cin >> choice;
        clearInputBuffer();

        switch (choice) {
        case 1:
        case 2:
        case 3:
        case 4:
            addShape(shapes);
            break;
        case 5:
            displayAllShapes(shapes);
            break;
        case 6:
            compareShapes(shapes);
            break;
        case 7:
            sumShapes(shapes);
            break;
        case 8:
            std::cout << "Завершение работы." << std::endl;
            break;
        default:
            std::cout << "Неверный выбор. Пожалуйста, попробуйте еще раз." << std::endl;
        }
    } while (choice != 8);

    // Освобождение памяти (важно!)
    for (Shape* shape : shapes) {
        delete shape;
    }
    shapes.clear();

    return 0;
}
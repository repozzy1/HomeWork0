#include <iostream>
#include <string>
#include <vector>
#include <cmath> // ��� pow, M_PI
#include <limits> // ��� std::numeric_limits

// ����������� ����� Shape
class Shape {
private:
    int id;
    std::string name;
    static int nextId; // ����������� ���� ��� ��������� ID

protected:
    // ����������� (protected, ����� ������ ���� ������� ������ Shape ��������)
    Shape(const std::string& name) : name(name), id(nextId++) {
        std::cout << "Shape (constructor) id: " << id << std::endl;
    }

public:
    // ����� ����������� ����� ��� ���������� �������
    virtual double getArea() const = 0;

    // ������ ��� id
    int getId() const { return id; }

    // ������ ��� �����
    std::string getName() const { return name; }

    // ����������� ���������� (�����������!)
    virtual ~Shape() {
        std::cout << "~Shape() - Deconstructor, id: " << id << std::endl;
        //  �� ����� ���������� nextId �����, ��� �������� � ���������.  ID ������������ ������������� ��� ��������.
    }

    // ���������� ��������� ������
    friend std::ostream& operator<<(std::ostream& os, const Shape& shape) {
        os << "ID: " << shape.getId() << ", Name: " << shape.getName() << ", Area: " << shape.getArea();
        return os;
    }

    // ���������� ��������� ��������� (�� �������)
    bool operator==(const Shape& other) const {
        return std::abs(getArea() - other.getArea()) < 1e-6; // ���������� � ������ �����������
    }

    // ���������� ��������� �������� (��� ������������, ���������� �������)
    virtual Shape* operator+(const Shape& other) const = 0;

};

// ������������� ������������ �����
int Shape::nextId = 1;

// ����� Circle (����������� �� Shape)
class Circle : public Shape {
private:
    double radius;

public:
    Circle(double radius) : Shape("Circle"), radius(radius) {
        if (radius <= 0) {
            std::cerr << "������: ������ ������ ���� ������������� ������." << std::endl;
            this->radius = 1.0; // ������������� ����������� �������� �� ���������
        }
        std::cout << "Circle (constructor) radius: " << radius << std::endl;
    }

    double getRadius() const { return radius; }

    // ��������������� ������ ���������� �������
    double getArea() const override {
        return M_PI * radius * radius;
    }

    // �������������� �����, ����������� ��� Circle
    double getDiameter() const {
        return 2 * radius;
    }

    // ���������� ��������� ������
    friend std::ostream& operator<<(std::ostream& os, const Circle& circle) {
        os << " [Circle] " << static_cast<const Shape&>(circle) << ", Radius: " << circle.getRadius();
        return os;
    }

    // ���������� ��������� �������� (����������� ��������)
    Shape* operator+(const Shape& other) const override {
        const Circle* otherCircle = dynamic_cast<const Circle*>(&other);
        if (otherCircle) {
            return new Circle(std::sqrt(getArea() + otherCircle->getArea() / M_PI)); // ������� ����� ���� � ��������� ��������
        }
        return nullptr; // ������ ������� � ������ �������
    }

    ~Circle() override {
        std::cout << "~Circle() - Deconstructor, radius: " << radius << std::endl;
    }
};

// ����� Sphere (����������� �� Circle) - ���������� ������
class Sphere : public Circle {
public:
    Sphere(double radius) : Circle(radius), Shape("Sphere") {
        if (radius <= 0) {
            std::cerr << "������: ������ ������ ���� ������������� ������." << std::endl;
            this->Circle::setRadius(1.0); // ���������� setRadius, �.�. radius - private
        }
        std::cout << "Sphere (constructor) radius: " << radius << std::endl;
    }

    // ��������������� ������ ���������� ������� (����������� �����)
    double getArea() const override {
        return 4 * M_PI * getRadius() * getRadius(); // ���������� getRadius() �� Circle
    }

    // ����� ��� ���������� ������
    double getVolume() const {
        return (4.0 / 3.0) * M_PI * pow(getRadius(), 3); // ���������� getRadius()
    }

    // ���������� ��������� ������
    friend std::ostream& operator<<(std::ostream& os, const Sphere& sphere) {
        os << " [Sphere] " << static_cast<const Circle&>(sphere) << ", Volume: " << sphere.getVolume();
        return os;
    }

    // ���������� ��������� �������� (�������� �������, ���������)
    Shape* operator+(const Shape& other) const override {
        const Sphere* otherSphere = dynamic_cast<const Sphere*>(&other);
        if (otherSphere) {
            // ���������� �������:  ����� �������� = ����� �������, ������ �� �����������
            double combinedVolume = getVolume() + otherSphere->getVolume();
            return new Sphere(pow((3 * combinedVolume) / (4 * M_PI), 1.0 / 3.0));
        }
        return nullptr; // ������ ������� � ������ �������
    }


    ~Sphere() override {
        std::cout << "~Sphere() - Deconstructor, radius: " << getRadius() << std::endl;
    }
};


// ����� Rectangle (����������� �� Shape)
class Rectangle : public Shape {
private:
    double width;
    double height;

public:
    Rectangle(double width, double height) : Shape("Rectangle"), width(width), height(height) {
        if (width <= 0 || height <= 0) {
            std::cerr << "������: ������ � ������ ������ ���� �������������� �������." << std::endl;
            this->width = 1.0;
            this->height = 1.0;
        }
        std::cout << "Rectangle (constructor) width: " << width << ", height: " << height << std::endl;
    }

    double getWidth() const { return width; }
    double getHeight() const { return height; }

    // ��������������� ������ ���������� �������
    double getArea() const override {
        return width * height;
    }

    // �������������� �����, ����������� ��� Rectangle
    double getDiagonal() const {
        return std::sqrt(width * width + height * height);
    }

    // ���������� ��������� ������
    friend std::ostream& operator<<(std::ostream& os, const Rectangle& rectangle) {
        os << " [Rectangle] " << static_cast<const Shape&>(rectangle) << ", Width: " << rectangle.getWidth() << ", Height: " << rectangle.getHeight();
        return os;
    }

    // ���������� ��������� �������� (����������� ��������)
    Shape* operator+(const Shape& other) const override {
        const Rectangle* otherRectangle = dynamic_cast<const Rectangle*>(&other);
        if (otherRectangle) {
            return new Rectangle(width + otherRectangle->width, height + otherRectangle->height);  //  ������� ����� �������������
        }
        return nullptr; // ������ ������� � ������ �������
    }

    ~Rectangle() override {
        std::cout << "~Rectangle() - Deconstructor, width: " << width << ", height: " << height << std::endl;
    }
};

// ����� Cuboid (����������� �� Rectangle) - ���������� ������
class Cuboid : public Rectangle {
private:
    double depth;

public:
    Cuboid(double width, double height, double depth) : Rectangle(width, height), Shape("Cuboid"), depth(depth) {
        if (depth <= 0) {
            std::cerr << "������: ������� ������ ���� ������������� ������." << std::endl;
            this->depth = 1.0;
        }
        std::cout << "Cuboid (constructor) width: " << getWidth() << ", height: " << getHeight() << ", depth: " << depth << std::endl;
    }

    double getDepth() const { return depth; }

    // ��������������� ������ ���������� ������� (����������� ���������������)
    double getArea() const override {
        return 2 * (getWidth() * getHeight() + getWidth() * depth + getHeight() * depth);
    }

    // ����� ��� ���������� ������
    double getVolume() const {
        return getWidth() * getHeight() * depth; // ���������� getWidth() � getHeight() �� Rectangle
    }

    // ���������� ��������� ������
    friend std::ostream& operator<<(std::ostream& os, const Cuboid& cuboid) {
        os << " [Cuboid] " << static_cast<const Rectangle&>(cuboid) << ", Depth: " << cuboid.getDepth() << ", Volume: " << cuboid.getVolume();
        return os;
    }


    // ���������� ��������� �������� (�������� �������, ���������)
    Shape* operator+(const Shape& other) const override {
        const Cuboid* otherCuboid = dynamic_cast<const Cuboid*>(&other);
        if (otherCuboid) {
            // ���������� �������: ����� �������� = ����� �������, ������� �� �����������
            double combinedVolume = getVolume() + otherCuboid->getVolume();
            // ������������ ������ ����������� ����� �������� (������ ��� �������)
            //double newWidth = getWidth() + otherCuboid->getWidth();
            //double newHeight = getHeight() + otherCuboid->getHeight();
            //double newDepth = depth;
            return new Cuboid(getWidth(), getHeight(), depth); // (3 * combinedVolume) / (getWidth() * getHeight));
        }
        return nullptr; // ������ ������� � ������ �������
    }

    ~Cuboid() override {
        std::cout << "~Cuboid() - Deconstructor, depth: " << depth << std::endl;
    }
};

// ������� ��� ������� ������ �����
void clearInputBuffer() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// ������� ��� ����������� ����
void displayMenu() {
    std::cout << "\n����:" << std::endl;
    std::cout << "1. �������� ����" << std::endl;
    std::cout << "2. �������� �����" << std::endl;
    std::cout << "3. �������� �������������" << std::endl;
    std::cout << "4. �������� ��������������" << std::endl;
    std::cout << "5. ������� ���������� � ���� �������" << std::endl;
    std::cout << "6. �������� ��� ������ �� �������" << std::endl;
    std::cout << "7. ������� ��� ������ (���������� �������/������)" << std::endl;
    std::cout << "8. ��������� ������" << std::endl;
    std::cout << "�������� ����� ����: ";
}

// ������� ��� ���������� ������ (�������������)
void addShape(std::vector<Shape*>& shapes) {
    int choice;
    std::cout << "\n�������� ��� ������ ��� ����������:" << std::endl;
    std::cout << "1. ����" << std::endl;
    std::cout << "2. �����" << std::endl;
    std::cout << "3. �������������" << std::endl;
    std::cout << "4. ��������������" << std::endl;
    std::cout << "�������� �����: ";
    std::cin >> choice;
    clearInputBuffer();

    switch (choice) {
    case 1: {
        double radius;
        std::cout << "������� ������ �����: ";
        std::cin >> radius;
        clearInputBuffer();
        if (radius > 0) {
            shapes.push_back(new Circle(radius));
        }
        else {
            std::cout << "������������ ������." << std::endl;
        }
        break;
    }
    case 2: {
        double radius;
        std::cout << "������� ������ �����: ";
        std::cin >> radius;
        clearInputBuffer();
        if (radius > 0) {
            shapes.push_back(new Sphere(radius));
        }
        else {
            std::cout << "������������ ������." << std::endl;
        }
        break;
    }
    case 3: {
        double width, height;
        std::cout << "������� ������ ��������������: ";
        std::cin >> width;
        std::cout << "������� ������ ��������������: ";
        std::cin >> height;
        clearInputBuffer();
        if (width > 0 && height > 0) {
            shapes.push_back(new Rectangle(width, height));
        }
        else {
            std::cout << "������������ �������." << std::endl;
        }

        break;
    }
    case 4: {
        double width, height, depth;
        std::cout << "������� ������ ���������������: ";
        std::cin >> width;
        std::cout << "������� ������ ���������������: ";
        std::cin >> height;
        std::cout << "������� ������� ���������������: ";
        std::cin >> depth;
        clearInputBuffer();

        if (width > 0 && height > 0 && depth > 0) {
            shapes.push_back(new Cuboid(width, height, depth));
        }
        else {
            std::cout << "������������ �������." << std::endl;
        }
        break;
    }
    default:
        std::cout << "�������� �����." << std::endl;
        break;
    }
}

// ������� ��� ������ ���������� � ���� �������
void displayAllShapes(const std::vector<Shape*>& shapes) {
    if (shapes.empty()) {
        std::cout << "��� ����� ��� �����������." << std::endl;
        return;
    }
    for (const Shape* shape : shapes) {
        std::cout << *shape << std::endl; // ���������� ������������� �������� <<
    }
}

// ������� ��� ��������� ���� ����� �� �������
void compareShapes(const std::vector<Shape*>& shapes) {
    if (shapes.size() < 2) {
        std::cout << "������������ ����� ��� ���������." << std::endl;
        return;
    }

    int index1, index2;
    std::cout << "������� ������ ������ ������: ";
    std::cin >> index1;
    clearInputBuffer();
    std::cout << "������� ������ ������ ������: ";
    std::cin >> index2;
    clearInputBuffer();

    if (index1 < 0 || index1 >= shapes.size() || index2 < 0 || index2 >= shapes.size()) {
        std::cout << "�������� ������." << std::endl;
        return;
    }

    if (*shapes[index1] == *shapes[index2]) { // ���������� ������������� �������� ==
        std::cout << "������ ����� �������� ���������� �������." << std::endl;
    }
    else {
        std::cout << "������ ����� ������ �������." << std::endl;
    }
}

// ������� ��� �������� ���� ����� (����������� ��������/�������)
void sumShapes(std::vector<Shape*>& shapes) {
    if (shapes.size() < 2) {
        std::cout << "������������ ����� ��� ��������." << std::endl;
        return;
    }

    int index1, index2;
    std::cout << "������� ������ ������ ������: ";
    std::cin >> index1;
    clearInputBuffer();
    std::cout << "������� ������ ������ ������: ";
    std::cin >> index2;
    clearInputBuffer();

    if (index1 < 0 || index1 >= shapes.size() || index2 < 0 || index2 >= shapes.size()) {
        std::cout << "�������� ������." << std::endl;
        return;
    }

    Shape* result = nullptr;
    result = *shapes[index1] + *shapes[index2];

    if (result != nullptr) {
        std::cout << "��������� ��������: " << *result << std::endl;
        shapes.push_back(result); // ��������� ��������� � ������
    }
    else {
        std::cout << "�������� ���� ����� ����������." << std::endl;
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
            std::cout << "���������� ������." << std::endl;
            break;
        default:
            std::cout << "�������� �����. ����������, ���������� ��� ���." << std::endl;
        }
    } while (choice != 8);

    // ������������ ������ (�����!)
    for (Shape* shape : shapes) {
        delete shape;
    }
    shapes.clear();

    return 0;
}
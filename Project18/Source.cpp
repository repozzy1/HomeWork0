#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <limits>

class Shape {
private:
    int id;
    std::string name;
    static int nextId;

public:
    Shape(const std::string& name) : name(name), id(nextId++) {}
    virtual ~Shape() { std::cout << "Shape destructor id: " << id << std::endl; }

    int getId() const { return id; }
    std::string getName() const { return name; }

    virtual double getArea() const = 0;
    virtual Shape* operator+(const Shape& other) const = 0;

    bool operator==(const Shape& other) const {
        return getArea() == other.getArea();
    }

    virtual std::ostream& print(std::ostream& os) const {
        os << "ID: " << id << ", Name: " << name << ", Area: " << getArea();
        return os;
    }
    friend std::ostream& operator<<(std::ostream& os, const Shape& shape) {
        return shape.print(os);
    }
};

int Shape::nextId = 1;

class Circle : public Shape {
private:
    double radius;

public:
    Circle(double radius) : Shape("Circle"), radius(radius) {}
    ~Circle() override { std::cout << "Circle destructor" << std::endl; }

    double getRadius() const { return radius; }
    double getArea() const override { return M_PI * radius * radius; }
    double getCircumference() const { return 2 * M_PI * radius; }

    Shape* operator+(const Shape& other) const override {
        if (const Circle* otherCircle = dynamic_cast<const Circle*>(&other)) {
            return new Circle(sqrt(radius * radius + otherCircle->radius * otherCircle->radius));
        }
        return nullptr;
    }
    std::ostream& print(std::ostream& os) const override {
        Shape::print(os);
        os << ", Radius: " << radius << ", Circumference: " << getCircumference();
        return os;
    }
};

class Sphere : public Circle {
public:
    Sphere(double radius) : Circle(radius), Shape("Sphere") {}
    ~Sphere() override { std::cout << "Sphere destructor" << std::endl; }

    double getVolume() const { return (4.0 / 3.0) * M_PI * getRadius() * getRadius() * getRadius(); }
    double getArea() const override { return 4 * M_PI * getRadius() * getRadius(); }

    std::ostream& print(std::ostream& os) const override {
        Circle::print(os);
        os << ", Volume: " << getVolume();
        return os;
    }
    Shape* operator+(const Shape& other) const override {
        if (const Sphere* otherSphere = dynamic_cast<const Sphere*>(&other)) {
            return new Sphere(std::cbrt(getRadius() * getRadius() * getRadius() + otherSphere->getRadius() * otherSphere->getRadius() * otherSphere->getRadius()));
        }
        return nullptr;
    }
};

class Rectangle : public Shape {
private:
    double width;
    double height;

public:
    Rectangle(double width, double height) : Shape("Rectangle"), width(width), height(height) {}
    ~Rectangle() override { std::cout << "Rectangle destructor" << std::endl; }

    double getWidth() const { return width; }
    double getHeight() const { return height; }
    double getArea() const override { return width * height; }
    double getPerimeter() const { return 2 * (width + height); }

    Shape* operator+(const Shape& other) const override {
        if (const Rectangle* otherRectangle = dynamic_cast<const Rectangle*>(&other)) {
            return new Rectangle(width + otherRectangle->width, height + otherRectangle->height);
        }
        return nullptr;
    }

    std::ostream& print(std::ostream& os) const override {
        Shape::print(os);
        os << ", Width: " << width << ", Height: " << height << ", Perimeter: " << getPerimeter();
        return os;
    }
};

class Cuboid : public Rectangle {
private:
    double depth;

public:
    Cuboid(double width, double height, double depth) : Rectangle(width, height), Shape("Cuboid"), depth(depth) {}
    ~Cuboid() override { std::cout << "Cuboid destructor" << std::endl; }

    double getDepth() const { return depth; }
    double getVolume() const { return getWidth() * getHeight() * depth; }
    double getArea() const override {
        return 2 * (getWidth() * getHeight() + getWidth() * depth + getHeight() * depth);
    }

    Shape* operator+(const Shape& other) const override {
        if (const Cuboid* otherCuboid = dynamic_cast<const Cuboid*>(&other)) {
            return new Cuboid(getWidth() + otherCuboid->getWidth(), getHeight() + otherCuboid->getHeight(), depth + otherCuboid->depth);
        }
        return nullptr;
    }

    std::ostream& print(std::ostream& os) const override {
        Rectangle::print(os);
        os << ", Depth: " << depth << ", Volume: " << getVolume();
        return os;
    }
};

void clearInputBuffer() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int getIntInput(const std::string& prompt) {
    int value;
    while (true) {
        std::cout << prompt;
        std::cin >> value;

        if (std::cin.fail()) {
            std::cout << "Invalid input. Please enter a number." << std::endl;
            std::cin.clear();
            clearInputBuffer();
        }
        else {
            clearInputBuffer();
            return value;
        }
    }
}

double getDoubleInput(const std::string& prompt) {
    double value;
    while (true) {
        std::cout << prompt;
        std::cin >> value;

        if (std::cin.fail()) {
            std::cout << "Invalid input. Please enter a number." << std::endl;
            std::cin.clear();
            clearInputBuffer();
        }
        else {
            clearInputBuffer();
            return value;
        }
    }
}

void displayMenu() {
    std::cout << "\nMenu:" << std::endl;
    std::cout << "1. Add new shape" << std::endl;
    std::cout << "2. Output all shapes" << std::endl;
    std::cout << "3. Compare two shapes" << std::endl;
    std::cout << "4. Add two shapes" << std::endl;
    std::cout << "5. Exit" << std::endl;
    std::cout << "Enter your choice: ";
}

void addShape(std::vector<Shape*>& shapes) {
    int choice;
    std::cout << "Choose shape type:" << std::endl;
    std::cout << "1. Circle" << std::endl;
    std::cout << "2. Sphere" << std::endl;
    std::cout << "3. Rectangle" << std::endl;
    std::cout << "4. Cuboid" << std::endl;
    std::cout << "Enter your choice: ";
    std::cin >> choice;
    clearInputBuffer();

    switch (choice) {
    case 1: {
        double radius = getDoubleInput("Enter radius: ");
        shapes.push_back(new Circle(radius));
        break;
    }
    case 2: {
        double radius = getDoubleInput("Enter radius: ");
        shapes.push_back(new Sphere(radius));
        break;
    }
    case 3: {
        double width = getDoubleInput("Enter width: ");
        double height = getDoubleInput("Enter height: ");
        shapes.push_back(new Rectangle(width, height));
        break;
    }
    case 4: {
        double width = getDoubleInput("Enter width: ");
        double height = getDoubleInput("Enter height: ");
        double depth = getDoubleInput("Enter depth: ");
        shapes.push_back(new Cuboid(width, height, depth));
        break;
    }
    default:
        std::cout << "Invalid choice" << std::endl;
    }
}

void outputShapes(const std::vector<Shape*>& shapes) {
    if (shapes.empty()) {
        std::cout << "No shapes to display." << std::endl;
        return;
    }
    for (const Shape* shape : shapes) {
        std::cout << *shape << std::endl;
    }
}

void compareShapes(const std::vector<Shape*>& shapes) {
    if (shapes.size() < 2) {
        std::cout << "Not enough shapes to compare." << std::endl;
        return;
    }

    int index1 = getIntInput("Enter first index: ");
    int index2 = getIntInput("Enter second index: ");

    if (index1 >= 0 && index1 < shapes.size() && index2 >= 0 && index2 < shapes.size()) {
        if (*shapes[index1] == *shapes[index2]) {
            std::cout << "Shapes have the same area." << std::endl;
        }
        else {
            std::cout << "Shapes have different areas." << std::endl;
        }
    }
    else {
        std::cout << "Invalid index." << std::endl;
    }
}

void addShapes(std::vector<Shape*>& shapes) {
    if (shapes.size() < 2) {
        std::cout << "Not enough shapes to add." << std::endl;
        return;
    }

    int index1 = getIntInput("Enter first index: ");
    int index2 = getIntInput("Enter second index: ");

    if (index1 >= 0 && index1 < shapes.size() && index2 >= 0 && index2 < shapes.size()) {
        Shape* sum = (*shapes[index1]) + (*shapes[index2]);
        if (sum != nullptr) {
            shapes.push_back(sum);
            std::cout << "Shapes added. Result: " << *sum << std::endl;
        }
        else {
            std::cout << "Cannot add these shapes." << std::endl;
        }
    }
    else {
        std::cout << "Invalid index." << std::endl;
    }
}

int main() {
    std::vector<Shape*> shapes;
    int choice;

    do {
        displayMenu();
        choice = getIntInput("");

        switch (choice) {
        case 1:
            addShape(shapes);
            break;
        case 2:
            outputShapes(shapes);
            break;
        case 3:
            compareShapes(shapes);
            break;
        case 4:
            addShapes(shapes);
            break;
        case 5:
            std::cout << "Exiting." << std::endl;
            break;
        default:
            std::cout << "Invalid choice." << std::endl;
        }
    } while (choice != 5);

    for (Shape* shape : shapes) {
        delete shape;
    }
    shapes.clear();

    return 0;
}
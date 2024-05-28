#include <iostream>
#include <cmath>
#include <string>

using namespace std;

void executeRhombus();
void executeVector();

// Код 1: Rhombus
class Rhombus {
private:
    double side; //cторона ромба
    double diagonal; //діагональ ромба
    string color; //колір ромба

public:
    //конструктор за замовчуванням
    Rhombus() : side(0), diagonal(0), color("white") {}

    //конструктор, що ініціалізує всі поля
    Rhombus(double s, double d, const string& c) {
        setSide(s);
        setDiagonal(d);
        setColor(c);
    }

    //функція обчислення площі ромба
    double area() {
        return (side * diagonal) / 2;
    }

    //функція обчислення периметру ромба
    double perimeter() {
        return 4 * side;
    }

    //функції-члени встановлення значення сторони, діагоналі та кольору
    void setSide(double s) { //встановлює значення сторони ромба
        if (s > 0)
            side = s;
        else
            cout << "Error: Side must be positive." << endl;
    }

    void setDiagonal(double d) { //встановлює значення діагоналі ромба
        if (d > 0)
            diagonal = d;
        else
            cout << "Error: Diagonal must be positive." << endl;
    }

    void setColor(const string& c) { //встановлює колір ромба
        color = c;
    }

    //функції повернення значення полів
    double getSide() { //повертає значення сторони ромба
        return side;
    }

    double getDiagonal() { //повертає значення діагоналі ромба
        return diagonal;
    }

    string getColor() { //повертає колір ромба
        return color;
    }

    //функція друку
    void print() { //виводить інформацію про ромб
        cout << "Side: " << side << endl;
        cout << "Diagonal: " << diagonal << endl;
        cout << "Color: " << color << endl;
        cout << "Area: " << area() << endl;
        cout << "Perimeter: " << perimeter() << endl;
    }
};

// Код 2: Vector
class Vector {
private:
    float x, y, z;
    int state; // код стану: 0 - нормальний стан, 1 - помилка (нульовий вказівник), 2 - помилка (ділення на 0)

public:
    static int count; // змінна для підрахунку кількості об'єктів даного класу

    // конструктор без параметрів
    Vector() : x(0.0f), y(0.0f), z(0.0f), state(0) {
        count++;
    }

    // конструктор з одним параметром типу float
    Vector(float value) : x(value), y(value), z(value), state(0) {
        count++;
    }

    // конструктор з одним параметром вказівником на масив
    Vector(float* arr) : state(0) {
        if (arr == nullptr) {
            state = 1; // помилка: нульовий вказівник
        }
        else {
            x = arr[0];
            y = arr[1];
            z = arr[2];
        }
        count++;
    }

    // конструктор для введення значень вектора
    Vector(float x_val, float y_val, float z_val) : x(x_val), y(y_val), z(z_val), state(0) {
        count++;
    }

    // деструктор
    ~Vector() {
        std::cout << "Destructor called. State: " << state << std::endl;
        count--;
    }

    // функція для введення значень вектора
    void input() {
        std::cout << "Enter the value of x: ";
        std::cin >> x;
        std::cout << "Enter the value of y: ";
        std::cin >> y;
        std::cout << "Enter the value of z: ";
        std::cin >> z;
    }

    //функція для присвоєння значення полю (x, y або z)
    void set(float value, char coordinate = 'x') {
        if (coordinate == 'x')
            x = value;
        else if (coordinate == 'y')
            y = value;
        else if (coordinate == 'z')
            z = value;
        else
            std::cerr << "Invalid coordinate specified!" << std::endl;
    }

    // функція для отримання значення поля
    float getValue(char coordinate = 'x') {
        if (coordinate == 'x')
            return x;
        else if (coordinate == 'y')
            return y;
        else if (coordinate == 'z')
            return z;
        return 0.0f; // повертаємо 0 в разі некоректного індексу
    }

    // конструктор копіювання
    Vector(const Vector& other) : x(other.x), y(other.y), z(other.z), state(other.state) {
        count++;
    }

    // оператор присвоєння
    Vector& operator=(const Vector& other) {
        if (this == &other)
            return *this;
        x = other.x;
        y = other.y;
        z = other.z;
        state = other.state;
        return *this;
    }

    // функція друку
    void print() {
        std::cout << "(" << x << ", " << y << ", " << z << ")" << std::endl;
    }

    // функція додавання
    Vector add(const Vector& other) {
        Vector result;
        result.x = x + other.x;
        result.y = y + other.y;
        result.z = z + other.z;
        return result;
    }

    // функція віднімання
    Vector subtract(const Vector& other) {
        Vector result;
        result.x = x - other.x;
        result.y = y - other.y;
        result.z = z - other.z;
        return result;
    }

    // функція векторного добутку
    Vector crossProduct(const Vector& other) {
        Vector result;
        result.x = y * other.z - z * other.y;
        result.y = z * other.x - x * other.z;
        result.z = x * other.y - y * other.x;
        return result;
    }

    // функція ділення на ціле число типу short
    void divide(short divisor) {
        if (divisor != 0) {
            x /= divisor;
            y /= divisor;
            z /= divisor;
        }
        else {
            state = 2; // помилка: ділення на 0
        }
    }

    // функції порівняння
    bool operator==(const Vector& other) {
        return (x == other.x && y == other.y && z == other.z);
    }

    bool operator!=(const Vector& other) {
        return !(*this == other);
    }

    bool operator<(const Vector& other) {
        return (magnitude() < other.magnitude());
    }

    bool operator>(const Vector& other) {
        return (magnitude() > other.magnitude());
    }

    bool operator<=(const Vector& other) {
        return (magnitude() <= other.magnitude());
    }

    bool operator>=(const Vector& other) {
        return (magnitude() >= other.magnitude());
    }

private:
    // функція для обчислення модуля вектора
    float magnitude() const {
        return std::sqrt(x * x + y * y + z * z);
    }
};

int Vector::count = 0;

void executeRhombus() {
    double side, diagonal;
    string color;

    cout << "Enter the side of the rhombus: ";
    cin >> side;

    cout << "Enter the diagonal of the rhombus: ";
    cin >> diagonal;

    cout << "Enter the color of the rhombus: ";
    cin >> color;

    Rhombus r(side, diagonal, color);
    r.print();
}

void executeVector() {
    Vector v1; // виклик конструктора без параметрів
    v1.input(); // виклик методу для введення значень вектора
    v1.print(); // виведення значень вектора
}

int main() {
    setlocale(LC_CTYPE, "ukr");
    int choice;

    cout << "Enter 1 to execute Rhombus code or 2 to execute Vector code: ";
    cin >> choice;

    switch (choice) {
    case 1: {
        executeRhombus();
        break;
    }
    case 2: {
        executeVector();
        break;
    }
    default:
        cout << "Invalid choice!" << endl;
    }

    return 0;
}

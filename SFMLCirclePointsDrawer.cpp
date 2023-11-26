#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include <vector>
#include <limits>
#include <SFML/Graphics.hpp>

// Определение структуры для представления точки
struct Point {
    double x, y;
};

// Функция для ввода координат, радиуса, количества точек и направления обхода
void inputPoints(Point& P1, Point& P2, double& R, int& N, bool& clockwise) {

    // Ввод координат точки P1
    std::cout << "Введите координаты точки P1 (x y): ";
    while (!(std::cin >> P1.x >> P1.y)) {
        std::cout << "Ошибка ввода! Введите корректные числа: ";
        // Сброс состояния ошибки ввода
        std::cin.clear (); 
        // Очистка буфера ввода
        std::cin.ignore(); 
    }

    // Ввод координат точки P2
    std::cout << "Введите координаты точки P2 (x y): ";
    while (!(std::cin >> P2.x >> P2.y)) {
        std::cout << "Ошибка ввода! Введите корректные числа: ";
        std::cin.clear ();
        std::cin.ignore();
    }

    // Ввод радиуса R
    do {
        std::cout << "Введите радиус R (должен быть положительным): ";
        while (!(std::cin >> R) || R <= 0) {
            std::cout << "Ошибка ввода! Введите корректное положительное число: ";
            std::cin.clear();
            std::cin.ignore();
        }
    } while (R <= 0);

    // Ввод количества точек N
    do {
        std::cout << "Введите количество точек N (должно быть положительным): ";
        while (!(std::cin >> N) || N <= 0) {
            std::cout << "Ошибка ввода! Введите корректное положительное число: ";
            std::cin.clear ();
            std::cin.ignore();
        }
    } while (N <= 0);

    // Ввод направления обхода (по часовой стрелке или против часовой)
    std::cout << "Введите 1 для по часовой стрелке или 0 для против часовой: ";
    while (!(std::cin >> clockwise) || (clockwise != 0 && clockwise != 1)) {
        std::cout << "Ошибка ввода! Введите 0 или 1: ";
        std::cin.clear ();
        std::cin.ignore();
    }
}

// Функция для вычисления координат точек на окружности
std::vector<Point> calculatePoints(const Point& P1, const Point& P2, double R, int N, bool clockwise) {
    std::vector<Point> points;

    // Вычисление центра окружности
    double centerX = (P1.x + P2.x) / 2;
    double centerY = (P1.y + P2.y) / 2;

    // Вычисление угла между P1 и P2
    double angleP1P2 = std::atan2(P2.y - P1.y, P2.x - P1.x);

    // Вычисление угла шага в зависимости от количества точек и направления обхода
    double step = (clockwise) ? -2 * M_PI / N : 2 * M_PI / N;

    // Вычисление координат N точек на окружности
    for (int i = 0; i < N; ++i) {
        double angle = angleP1P2 + i * step;
        double x = centerX + R * std::cos(angle);
        double y = centerY + R * std::sin(angle);
        points.push_back({ x, y });
    }

    return points;
}

// Функция для вычисления и отображения точек с использованием SFML
void calculateAndDisplayPoints(const std::vector<Point>& points) {
    // Создание окна SFML
    sf::RenderWindow window(sf::VideoMode(800, 600), "Pointer in Circle");

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            // Закрытие окна при нажатии на кнопку закрытия
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        window.clear();

        // Рисование центра окружности
        // Создание объекта sf::CircleShape с радиусом 5, представляющего центр окружности
        sf::CircleShape center(5);
        // Установка цвета заливки центра окружности в красный
        center.setFillColor(sf::Color::Red);
        // Установка позиции центра окружности в координаты первой точки на окружности
        center.setPosition(points[0].x - 5, points[0].y - 5);
        // Отрисовка центра окружности на SFML-окне
        window.draw(center);

        // Рисование точек на окружности
        // Перебор всех точек на окружности
        for (const auto& point : points) {
            // Создание объекта sf::CircleShape с радиусом 2, представляющего точку на окружности
            sf::CircleShape circle(2);
            // Установка цвета заливки точки на окружности в синий
            circle.setFillColor(sf::Color::Blue);
            // Установка позиции точки на окружности в соответствии с её координатами
            circle.setPosition(point.x - 2, point.y - 2);
            // Отрисовка точки на окружности на SFML-окне
            window.draw(circle);
        }
        window.display();
    }
}

// Функция для вывода координат точек
void displayCoordinates(const std::vector<Point>& points) {
    std::cout << "Координаты точек на окружности:\n";
    for (const auto& point : points) {
        std::cout << "(" << point.x << ", " << point.y << ")\n";
    }
}

int main() {
    setlocale(LC_ALL, "ru");
    // Объявление переменных для точек, радиуса, количества точек и направления обхода
    Point P1, P2;
    double R{ 0.0 };
    int N   { 0 };
    bool clockwise;

    // Ввод значений от пользователя
    inputPoints(P1, P2, R, N, clockwise);

    // Вычисление точек на окружности
    std::vector<Point> points = calculatePoints(P1, P2, R, N, clockwise);

    // Вывод координат точек
    displayCoordinates(points);

    // Вычисление и отображения точек с использованием SFML
    calculateAndDisplayPoints(points);

    return 0;
}
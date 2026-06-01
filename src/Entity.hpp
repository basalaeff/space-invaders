#pragma once

// Перечисление направлений
enum class Direction {
    NONE = 0,
    LEFT = -1,
    RIGHT = 1,
    UP = -1,
    DOWN = 1
};


class Entity {
protected:
    int x_, y_;           // Координаты
    char symbol_;        // Символ отрисовки
    bool alive_;         // Жив ли объект
    int speedDelay_;     // Задержка движения (чем больше, тем медленнее)
    int tickCounter_;    // Внутренний счетчик кадров

public:
    Entity(int x, int y, char sym, int speed = 1)
        : x_(x), y_(y), symbol_(sym), alive_(true), speedDelay_(speed), tickCounter_(0) {}

    virtual ~Entity() = default;

    // Геттеры
    int getX() const { return x_; }
    int getY() const { return y_; }
    char getSymbol() const { return symbol_; }
    bool isAlive() const { return alive_; }

    // Сеттеры
    void setPos(int newX, int newY) { x_ = newX; y_ = newY; }
    void kill() { alive_ = false; }

    // Полиморфное обновление
    // Каждый наследник будет двигаться по-своему
    virtual void update() = 0;
};
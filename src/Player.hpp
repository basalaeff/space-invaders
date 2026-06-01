#pragma once
#include "Entity.hpp"
#include "Bullet.hpp"

class Player : public Entity {
private:
    int lives_;
    int widthLimit_;
    int lastShotTick_; // Чтобы не стрелять слишком часто
    const int shootCooldown_ = 15; // Задержка между выстрелами (в тиках)

public:
    Player(int x, int y, int screenWidth)
        : Entity(x, y, '^', 0), lives_(3), widthLimit_(screenWidth), lastShotTick_(0) {}

    void update() override {
        lastShotTick_++;
    }

    void moveLeft() {
        if (x_ > 1) x_--;
    }

    void moveRight() {
        if (x_ < widthLimit_ - 2) x_++;
    }

    // Возвращает указатель на новую пулю или nullptr
    Bullet* shoot() {
        if (lastShotTick_ >= shootCooldown_) {
            lastShotTick_ = 0;
            // Создаем пулю чуть выше игрока
            return new Bullet(x_, y_ - 1, 1, -1);
        }
        return nullptr;
    }

    int getLives() const { return lives_; }
    void loseLife() { if (lives_ > 0) lives_--; }
};
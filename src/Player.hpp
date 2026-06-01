#pragma once
#include "Entity.hpp"

class Player : public Entity {
private:
    int lives_;
    int widthLimit_;

public:
    Player(int x, int y, int screenWidth)
        : Entity(x, y, '|-o-|', 0), lives_(3), widthLimit_(screenWidth) {}

    void update() override {
        // Игрок обновляется через ввод
    }

    void moveLeft() {
        if (x_ > 1) x_--;
    }

    void moveRight() {
        if (x_ < widthLimit_ - 2) x_++;
    }

    int getLives() const { return lives_; }
    void loseLife() { if (lives_ > 0) lives_--; }
};
#pragma once
#include "Entity.hpp"

class Alien : public Entity {
protected:
    Direction dir_; //направление движения

public:
    Alien(int x, int y, char sym, int speed)
        : Entity(x, y, sym, speed), dir_(Direction::RIGHT) {}

    void moveHorizontal() {
        tickCounter_++;
        if (tickCounter_ >= speedDelay_) {
            x_ += static_cast<int>(dir_);
            tickCounter_ = 0;
        }
    }

    void checkWallBounce(int minX, int maxX) {
        if (x_ <= minX) {
            dir_ = Direction::RIGHT;
            y_++;
        } else if (x_ >= maxX) {
            dir_ = Direction::LEFT;
            y_++;
        }
    }

    void update() override {
        moveHorizontal();
    }
};
#pragma once
#include "Entity.hpp"

class Bullet : public Entity {
private:
    int dy_; // Направление движения по вертикали (-1 вверх, 1 вниз)

public:
    // x, y - где появилась пуля
    // speed - как быстро летит
    // dy - направление (для игрока обычно -1)
    Bullet(int x, int y, int speed, int dy)
        : Entity(x, y, '|', speed), dy_(dy) {}

    void update() override {
        // Пуля летит каждый кадр (или через speedDelay)
        tickCounter_++;
        if (tickCounter_ >= speedDelay_) {
            y_ += dy_;
            tickCounter_ = 0;

            // Если пуля улетела за границы экрана - убиваем её
            if (y_ < 0 || y_ > 24) {
                alive_ = false;
            }
        }
    }
};
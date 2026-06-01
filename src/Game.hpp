#include "ScreenManager.hpp"
#include "Entity.hpp"
#include "Player.hpp"
#include "Alient.hpp"
#include "Bullet.hpp"
#include <list>
#include <thread>
#include <chrono>
#include <iostream>

class Game {
private:
    ScreenManager screen_;
    std::list<Entity*> entities_; // Список всех сущностей
    Player* player_;
    int width_ = 80;
    int height_ = 24;
    bool running_ = true;

public:
    Game() {
        player_ = new Player(40, 22, width_);
        entities_.push_back(player_);

        // Создаем врагов
        for (int i = 0; i < 6; ++i) {
            entities_.push_back(new Alien(10 + i * 10, 3, 'V', 5));
        }
    }

    ~Game() {
        for (auto* e : entities_) delete e;
    }

    void input() {
        int key = getch();
        if (key == 'q') running_ = false;

        if (key == KEY_LEFT) player_->moveLeft();
        if (key == KEY_RIGHT) player_->moveRight();

        // стрельба
        if (key == ' ') {
            Bullet* b = player_->shoot();
            if (b) {
                entities_.push_back(b); // Добавляем пулю в общий список
            }
        }
    }

    void update() {
        // Обновляем все сущности
        for (auto* e : entities_) {
            if (e->isAlive()) {
                e->update();

                // Проверка стен для пришельцев
                if (Alien* alien = dynamic_cast<Alien*>(e)) {
                    alien->checkWallBounce(1, width_ - 2);
                }
            }
        }

        // Очистка мертвых сущностей (пуль, улетевших за экран, и убитых врагов)
        // Используем remove_if для безопасного удаления из списка
        entities_.remove_if([](Entity* e) {
            return !e->isAlive();
        });
    }

    void draw() {
        screen_.clearScreen();

        for (auto* e : entities_) {
            if (e->isAlive()) {
                screen_.printAt(e->getY(), e->getX(), std::string(1, e->getSymbol()).c_str());
            }
        }

        screen_.printAt(0, 0, ("Lives: " + std::to_string(player_->getLives())).c_str());
        screen_.refreshScreen();
    }

    void run() {
        while (running_) {
            input();
            update();
            draw();
            std::this_thread::sleep_for(std::chrono::milliseconds(30));
        }
    }
};
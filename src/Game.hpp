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
    int score_ = 0;

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
        int aliensAlive = 0;

        // Обновление и подсчет врагов
        for (auto* e : entities_) {
            if (e->isAlive()) {
                e->update();

                if (Alien* alien = dynamic_cast<Alien*>(e)) {
                    aliensAlive++;
                    alien->checkWallBounce(1, width_ - 2);

                    // Проверка достижения земли
                    if (alien->getY() >= height_ - 2) {
                        player_->loseLife();
                        alien->kill();
                    }
                }
            }
        }

        // Коллизии (Пули vs Пришельцы)
        for (auto* bullet : entities_) {
            // Пропускаем, если это не пуля или она мертва
            if (!bullet->isAlive()) continue;

            // Пытаемся привести к Bullet*. Если не получилось (это игрок или пришелец) — skip
            Bullet* b = dynamic_cast<Bullet*>(bullet);
            if (!b) continue;

            // Пули игрока летят вверх (dy_ < 0).
            // Если у тебя будут пули врагов, нужно будет проверить направление.
            // Пока считаем, что все пули в списке — наши, или проверяем тип.

            for (auto* target : entities_) {
                if (target == bullet || !target->isAlive()) continue;

                if (dynamic_cast<Alien*>(target)) {
                    int dx = std::abs(bullet->getX() - target->getX());
                    int dy = std::abs(bullet->getY() - target->getY());

                    if (dx <= 1 && dy <= 1) {
                        // ПОПАДАНИЕ
                        bullet->kill();   // Убиваем пулю
                        target->kill();   // Убиваем пришельца
                        score_ += 10;     // Добавляем очки
                    }
                }
            }
        }

        // Очистка мертвых
        entities_.remove_if([](Entity* e) { return !e->isAlive(); });

        // Проверка условий конца игры
        if (player_->getLives() <= 0) {
            gameOver(false); // false = проигрыш
        } else if (aliensAlive == 0) {
            gameOver(true);  // true = победа
        }
    }

    void draw() {
        screen_.clearScreen();

        for (auto* e : entities_) {
            if (e->isAlive()) {
                screen_.printAt(e->getY(), e->getX(), std::string(1, e->getSymbol()).c_str());
            }
        }
        screen_.printAt(0, 0, ("Score: " + std::to_string(score_)).c_str());
        screen_.printAt(0, 10, ("Lives: " + std::to_string(player_->getLives())).c_str());
        screen_.refreshScreen();
    }

    // Новый метод для обработки конца игры
    void gameOver(bool isWin) {
        running_ = false;

        screen_.clearScreen();

        int centerY = height_ / 2;
        int centerX = width_ / 2;

        if (isWin) {
            screen_.printAt(centerY - 1, centerX - 5, "VICTORY!", 1); // Зеленый
            screen_.printAt(centerY + 1, centerX - 10, "All aliens destroyed!");
        } else {
            screen_.printAt(centerY - 1, centerX - 5, "GAME OVER", 2); // Красный
            screen_.printAt(centerY + 1, centerX - 8, "Aliens invaded Earth...");
        }

        screen_.printAt(centerY + 3, centerX - 8, ("Final Score: " + std::to_string(score_)).c_str());
        screen_.printAt(centerY + 5, centerX - 12, "Press any key to exit...");

        screen_.refreshScreen();

        // Ждем нажатия любой клавиши, чтобы игрок успел прочитать
        nodelay(stdscr, false); // Включаем блокирующий режим ввода
        getch();
        nodelay(stdscr, true);  // Возвращаем неблокирующий (на всякий случай)
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
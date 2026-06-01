#include "ScreenManager.hpp"
#include <thread>
#include <chrono>

int main() {
    ScreenManager screen;

    int playerX = 40;
    int playerY = 20;

    bool running = true;

    // 2. Игровой цикл
    while (running) {
        int key = getch(); // Считываем нажатие (не блокирует)

        if (key == KEY_LEFT) {
            if (playerX > 0) playerX--;
        }
        else if (key == KEY_RIGHT) {
            if (playerX < 78) playerX++; // 80 символов ширина, индекс с 0
        }
        else if (key == 'q' || key == 'Q') {
            running = false; // Выход по Q
        }

        screen.clearScreen();

        // Рисуем игрока
        screen.printAt(playerY, playerX, "|-o-|", 1); // 1 = зеленый цвет

        screen.refreshScreen();

        // Задержка ~33мс = 30 кадров в секунду
        std::this_thread::sleep_for(std::chrono::milliseconds(33));
    }

    return 0;
}
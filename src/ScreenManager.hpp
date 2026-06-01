// src/ScreenManager.hpp
#pragma once
#include <ncurses.h>

#include <iostream>

// RAII-класс для управления ncurses
class ScreenManager {
 public:
  ScreenManager() {
    initscr();  // Инициализация
    cbreak();  // Отключаем буферизацию ввода (символы идут сразу)
    noecho();  // Не дублируем нажатые клавиши на экран
    curs_set(0);            // Скрываем курсор
    nodelay(stdscr, true);  // getch() не блокирует выполнение
    keypad(stdscr, true);  // Включаем поддержку спец-клавиш (стрелки)

    if (has_colors()) {
      start_color();
      init_pair(1, COLOR_GREEN, COLOR_BLACK);   // Цвет игрока
      init_pair(2, COLOR_RED, COLOR_BLACK);     // Цвет врагов
      init_pair(3, COLOR_YELLOW, COLOR_BLACK);  // Цвет пуль
    }
  }

  ~ScreenManager() { endwin(); }

  // Очистка экрана
  void clearScreen() { clear(); }

  // Обновление экрана
  void refreshScreen() { refresh(); }

  // Помощник для вывода текста в координаты
  void printAt(int y, int x, const char* str, int colorPair = 0) {
    attron(COLOR_PAIR(colorPair));
    mvprintw(y, x, "%s", str);
    attroff(COLOR_PAIR(colorPair));
  }
};
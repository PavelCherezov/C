#include "../../my_tetris.h"

void print_game(GameInfo_t* game, Figure* currentFigure) {
  int sym = 0;
  for (int i = 0; i < FIELD_HEIGHT; i++) {
    for (int j = 0; j < FIELD_WIDTH; j++) {
      sym = 0;
      if (game->field[i][j] != 0) {
        sym = game->field[i][j];
      } else {
        int x = j - currentFigure->x;
        int y = i - currentFigure->y;
        if (x >= 0 && x <= 5 && y >= 0 && y < 5) {
          if (currentFigure->figure[y][x] != 0) {
            sym = currentFigure->figure[y][x];
          }
        }
      }
      if (sym == 99) {
        mvaddch(i, j * 2, ACS_VLINE);
      } else if (sym == 98) {
        mvaddch(i, (j * 2) - 1, ACS_HLINE);
        mvaddch(i, (j * 2) + 1, ACS_HLINE);
        mvaddch(i, j * 2, ACS_HLINE);
      } else {
        attron(COLOR_PAIR(sym));
        mvaddstr(i, j * 2, "  ");
        attroff(COLOR_PAIR(sym));
      }
    }
  }
  mvaddch(0, 0, ACS_ULCORNER);
  mvaddch(0, 22, ACS_URCORNER);
  mvaddch(21, 0, ACS_LLCORNER);
  mvaddch(21, 22, ACS_LRCORNER);
}

void print_pole(int left_x, int right_x, int up_y, int down_y) {
  mvaddch(up_y, left_x, ACS_ULCORNER);
  mvaddch(up_y, right_x, ACS_URCORNER);
  mvaddch(down_y, left_x, ACS_LLCORNER);
  mvaddch(down_y, right_x, ACS_LRCORNER);
  for (int i = left_x + 1; i < right_x; i++) {
    mvaddch(up_y, i, ACS_HLINE);
  }

  for (int i = up_y + 1; i < down_y; i++) {
    mvaddch(i, left_x, ACS_VLINE);
    mvaddch(i, right_x, ACS_VLINE);
  }

  for (int i = left_x + 1; i < right_x; i++) {
    mvaddch(down_y, i, ACS_HLINE);
  }
}

void print_next_fig(GameInfo_t* game) {
  for (int i = 1; i < 4; i++) {
    for (int j = 0; j < 5; j++) {
      if (game->next[i][j] != 0) {
        attron(COLOR_PAIR(game->next[i][j]));
        mvaddstr(i + 11, (j + 13) * 2, "  ");
        attroff(COLOR_PAIR(game->next[i][j]));
      } else {
        attron(COLOR_PAIR(0));
        mvaddstr(i + 11, (j + 13) * 2, "   ");
        attroff(COLOR_PAIR(0));
      }
    }
  }
}

void print_info(GameInfo_t* game) {
  print_pole(23, 37, 1, 3);
  print_pole(23, 37, 4, 6);
  print_pole(23, 37, 7, 9);
  print_pole(23, 37, 10, 15);

  mvprintw(1, 24, " Score ");
  mvprintw(2, 25, "%d", game->score);

  mvprintw(4, 24, " High score ");
  mvprintw(5, 25, "%d", game->high_score);

  mvprintw(7, 24, " Level ");
  mvprintw(8, 25, "%d", game->level);

  if (game->next != NULL) {
    mvprintw(10, 24, " Next figure ");
    print_next_fig(game);
  }
  mvprintw(16, 24, "Action  Space");
  mvprintw(17, 24, "Pause   p");
  mvprintw(18, 24, "Exit    q");
}

void pause_game() {
  while (getch() != 'p') {
    mvaddstr(10, 4, "Pause");
    refresh();
  }
}

void start_game() {
  while (getch() != '\n') {
    mvaddstr(10, 4, "To start the game, press Enter");
    refresh();
  }
}

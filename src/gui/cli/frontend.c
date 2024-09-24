#include "frontend.h"

void printField(WINDOW *w, Tgame *game) {
  box(w, 0, 0);
  for (int i = 0; i < game->rows; i++) {
    wmove(w, 1 + i, 1);
    for (int j = 0; j < game->cols; j++) {
      if (ISFILLED(getBlock(game, i, j))) {
        ADDBLOCK(w, getBlock(game, i, j));
      } else {
        ADDEMPTY(w);
      }
    }
  }
  wnoutrefresh(w);
}

void printNext(WINDOW *w, Tgame *game) {
  wclear(w);
  box(w, 0, 0);
  if (game->next->type == -1) {
    wnoutrefresh(w);
    return;
  }
  for (int i = 0; i < CELLS; i++) {
    Tlocation temple = getTetr(game->next->type, game->next->orintation, i);
    wmove(w, temple.row + 1, temple.col * COLSPERCELL + 2);
    ADDBLOCK(w, TYPETOCELL(game->next->type));
  }
  wnoutrefresh(w);
}

void printStat(WINDOW *w, Tgame *game) {
  wclear(w);
  box(w, 1, 1);
  wmove(w, 1, 5);
  wprintw(w, "Level: %d\n", game->level);
  wprintw(w, "     Score: %d\n", game->score);
  wprintw(w, "   High score: %d\n", game->highScore);

  wnoutrefresh(w);
}

void initColors() {
  start_color();
  init_pair(TCELLI, COLOR_RED, COLOR_BLACK);
  init_pair(TCELLJ, COLOR_WHITE, COLOR_BLACK);
  init_pair(TCELLL, COLOR_YELLOW, COLOR_BLACK);
  init_pair(TCELLO, COLOR_MAGENTA, COLOR_BLACK);
  init_pair(TCELLS, COLOR_GREEN, COLOR_BLACK);
  init_pair(TCELLT, COLOR_BLUE, COLOR_BLACK);
  init_pair(TCELLZ, COLOR_CYAN, COLOR_BLACK);
}

void start() {
  int row = 0, col = 0;
  getmaxyx(stdscr, row, col);
  move(row / 2, col / 2);
  printw("START");
  refresh();
  bool status = true;
  while (status) {
    switch (getch()) {
      case ' ':
        status = false;
        break;
      default:
        break;
    }
  }
  clear();
}

void pause() {
  clear();
  int row = 0, col = 0;
  getmaxyx(stdscr, row, col);
  move(row / 2, col / 2);
  printw("PAUSE");
  refresh();
  bool status = true;
  while (status) {
    switch (getch()) {
      case ' ':
        status = false;
        break;
      default:
        break;
    }
  }
  clear();
}

Gstatus again(Tgame *game) {
  clear();
  int row = 0, col = 0;
  getmaxyx(stdscr, row, col);
  move(row / 2, col / 4);
  printw("The game is over, you have %d points. Want to start over?[y/n]",
         game->score);
  refresh();
  Gstatus status = END;
  if (againGame(game)) {
    status = GO;
  }
  clear();

  return status;
}
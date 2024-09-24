#include <stdio.h>

#include "brick_game/tetris/backend.h"
#include "gui/cli/frontend.h"

void gameLoop() {
  start();

  WINDOW *board = NULL, *next = NULL, *score = NULL;
  WINDOWINIT(board, next, score);

  Tgame game = gameInit();
  Gstatus status = GO;

  while (status != END) {
    if (status == PAUSE) {
      pause();
    }

    status = tick(&game, action());

    PRINT(board, next, score, &game);

    if (status == AGAIN) {
      status = again(&game);
    }
  }
}

int main() {
  CURSINIT();
  gameLoop();
  wclear(stdscr);
  endwin();

  return 0;
}
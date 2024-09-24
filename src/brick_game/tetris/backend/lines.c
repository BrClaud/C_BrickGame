#include "../backend.h"

bool isFullLines(Tgame *game, int index) {
  bool status = true;
  for (int i = 0; i < game->cols; i++) {
    if (getBlock(game, index, i) == 0) {
      status = false;
      break;
    }
  }

  return status;
}

void shiftLines(Tgame *game, int index) {
  for (int i = index - 1; i >= 0; i--) {
    for (int j = 0; j < game->cols; j++) {
      setBlock(game, i + 1, j, getBlock(game, i, j));
      setBlock(game, i, j, 0);
    }
  }
}

int checkLines(Tgame *game) {
  int lines = 0;
  rmTetramino(game, game->falling);
  for (int i = game->rows - 1; i >= 0; i--) {
    if (isFullLines(game, i)) {
      shiftLines(game, i);
      i++;
      lines++;
    }
  }
  putTetramino(game, game->falling);

  return lines;
}
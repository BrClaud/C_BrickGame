#include "../backend.h"

Tlocation getTetr(int tetramino, int orintation, int cells) {
  static const Tlocation info[TETRAMINOS][ORI][CELLS] = {
      // I - палочка
      {{{1, 0}, {1, 1}, {1, 2}, {1, 3}},
       {{0, 2}, {1, 2}, {2, 2}, {3, 2}},
       {{3, 0}, {3, 1}, {3, 2}, {3, 3}},
       {{0, 1}, {1, 1}, {2, 1}, {3, 1}}},
      // J - L с хвостиком влево
      {{{0, 0}, {1, 0}, {1, 1}, {1, 2}},
       {{0, 1}, {0, 2}, {1, 1}, {2, 1}},
       {{1, 0}, {1, 1}, {1, 2}, {2, 2}},
       {{0, 1}, {1, 1}, {2, 0}, {2, 1}}},
      // L - хвостик вправо
      {{{0, 2}, {1, 0}, {1, 1}, {1, 2}},
       {{0, 1}, {1, 1}, {2, 1}, {2, 2}},
       {{1, 0}, {1, 1}, {1, 2}, {2, 0}},
       {{0, 0}, {0, 1}, {1, 1}, {2, 1}}},
      // O - квадратик
      {{{0, 1}, {0, 2}, {1, 1}, {1, 2}},
       {{0, 1}, {0, 2}, {1, 1}, {1, 2}},
       {{0, 1}, {0, 2}, {1, 1}, {1, 2}},
       {{0, 1}, {0, 2}, {1, 1}, {1, 2}}},
      // S - лево право
      {{{0, 1}, {0, 2}, {1, 0}, {1, 1}},
       {{0, 1}, {1, 1}, {1, 2}, {2, 2}},
       {{1, 1}, {1, 2}, {2, 0}, {2, 1}},
       {{0, 0}, {1, 0}, {1, 1}, {2, 1}}},
      // T - в виде буквы Т
      {{{0, 1}, {1, 0}, {1, 1}, {1, 2}},
       {{0, 1}, {1, 1}, {1, 2}, {2, 1}},
       {{1, 0}, {1, 1}, {1, 2}, {2, 1}},
       {{0, 1}, {1, 0}, {1, 1}, {2, 1}}},
      // Z - право лево
      {{{0, 0}, {0, 1}, {1, 1}, {1, 2}},
       {{0, 2}, {1, 1}, {1, 2}, {2, 1}},
       {{1, 0}, {1, 1}, {2, 1}, {2, 2}},
       {{0, 1}, {1, 0}, {1, 1}, {2, 0}}},
  };
  return info[tetramino][orintation][cells];
}

int getBlock(Tgame *game, int row, int col) {
  return game->field[game->cols * row + col];
}

void setBlock(Tgame *game, int row, int col, int value) {
  game->field[game->cols * row + col] = value;
}

bool checkBlock(const Tgame *game, int row, int col) {
  bool status = false;
  if (0 <= row && row < game->rows && 0 <= col && col < game->cols) {
    status = true;
  }

  return status;
}

void putTetramino(Tgame *game, Tblock *block) {
  int index = 0;
  for (; index < CELLS; index++) {
    Tlocation cell = getTetr(block->type, block->orintation, index);
    setBlock(game, block->loc.row + cell.row, block->loc.col + cell.col,
             TYPETOCELL(block->type));
  }
}

void rmTetramino(Tgame *game, Tblock *block) {
  for (int index = 0; index < CELLS; index++) {
    Tlocation cell = getTetr(block->type, block->orintation, index);
    setBlock(game, block->loc.row + cell.row, block->loc.col + cell.col, 0);
  }
}

bool checkMovesTetramino(Tgame *game, const Tblock *block) {
  bool status = true;
  for (int index = 0; index < CELLS; index++) {
    Tlocation cell = getTetr(block->type, block->orintation, index);
    int templ_row = block->loc.row + cell.row;
    int templ_col = block->loc.col + cell.col;
    if (!checkBlock(game, templ_row, templ_col) ||
        ISFILLED(getBlock(game, templ_row, templ_col))) {
      status = false;
      break;
    }
  }

  return status;
}

void newFalling(Tgame *game) {
  *game->falling = *game->next;
  game->next->type = randomTetr();
  game->next->orintation = 0;
  game->next->loc.row = 0;
  game->next->loc.col = game->cols / 2 - 2;
}

int randomTetr() { return rand() % TETRAMINOS; }
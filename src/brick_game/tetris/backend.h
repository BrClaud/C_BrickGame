/**
 * @file backend.h
 * @brief Файл содержит объявления структур игры, всех функций backend'а и
 * макросов.
 */
#ifndef BACKEND_H
#define BACKEND_H
/**
 * @brief Для ncurses
 */
#define _POSIX_C_SOURCE 199309L

#include <math.h>
#include <ncurses.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/**
 * @brief Количество строк
 */
#define ROWS 20

/**
 * @brief Количество столбцов
 */
#define COLUMNS 10

/**
 * @brief Обозначение налево
 */
#define LEFT -1

/**
 * @brief Обозначение направо
 */
#define RIGHT 1

/**
 * @brief Количество уникальных тетрамино
 */
#define TETRAMINOS 7

/**
 * @brief Количество ориентаций у тетрамино
 */
#define ORI 4

/**
 * @brief Количество блоков в каждом тетрамино
 */
#define CELLS 4

/**
 * @brief Начальное значение скорости
 */
#define STARTSPEED 1

/**
 * @brief Начальное значение количества очков
 */
#define STARTSCORE 0

/**
 * @brief Начальное значение уровня
 */
#define STARTLEVEL 1

/**
 * @brief Начальное значение тиков гравитации
 */
#define STARTGRAVITY 50

/**
 * @brief Большее значение
 */
#define MAX(X, Y) ((X) > (Y) ? (X) : (Y))

/**
 * @brief Меньшее значение
 */
#define MIN(X, Y) ((X) < (Y) ? (X) : (Y))

/**
 * @brief Преобразование типа тетрамино в нужный блок
 */
#define TYPETOCELL(x) ((x) + 1)

/**
 * @brief Пустой ли блок
 */
#define ISEMPTY(x) ((x) == TEMPTY)

/**
 * @brief Заполнен ли блок
 */
#define ISFILLED(x) (!ISEMPTY(x))

/**
 * @brief Всевозможные действия
 */
typedef enum {
  TLEFT,
  TRIGHT,
  TUP,
  TCOUNTER,
  TDOWN,
  TDROP,
  TCLOCK,
  TPAUSE,
  TEND,
  TNONE
} Tmove;

/**
 * @brief Статусы игры
 */
typedef enum { END, AGAIN, GO, PAUSE } Gstatus;

/**
 * @brief Структура, содержащая пару чисел - строчка и столбец
 */
typedef struct Tlocation {
  int row;
  int col;
} Tlocation;

/**
 * @brief Структура, описывающая тетрамино
 * @param type Тип тетрамино
 * @param orintation Ориентация
 * @param loc Структура столбца и строчки каждого блока
 */
typedef struct Tblock {
  int type;
  int orintation;
  Tlocation loc;
} Tblock;

/**
 * @brief Перечесление всевозможных тетрамино
 */
typedef enum {
  TEMPTY,
  TCELLI,
  TCELLJ,
  TCELLL,
  TCELLO,
  TCELLS,
  TCELLT,
  TCELLZ
} Tcell;

/**
 * @brief Основная структура тетриса
 * @param rows Количество строк
 * @param cols Количество столбцов
 * @param field Игровое поле
 * @param score Количество очков
 * @param highScore Рекордное количество очков
 * @param level Уровень
 * @param speed Скорость
 * @param gravityTicks Сколько внутреигровых тиков необходимо до падения
 * @param falling Структура падающего тетрамино
 * @param next Структура следующего тетрамино
 */
typedef struct Tgame {
  int rows;
  int cols;
  int *field;
  int score;
  int highScore;
  int level;
  int speed;
  int gravityTicks;
  Tblock *falling;
  Tblock *next;
} Tgame;

/**
 * @brief Инициализация игровой структуры.
 * Приравние начальных значений, выделения памяти под матрицу и структуры.
 * @return Структуру со всеми значениями.
 */
Tgame gameInit();

/**
 * @brief Хранит в себе массив со всей информацией о тетромино
 * @param tetramino Тип тетрамино
 * @param orintation Ориентация тетрамино
 * @param cells Индекс координат блока
 * @return Структуру с координатами блока
 */
Tlocation getTetr(int tetramino, int orintation, int cells);

/**
 * @brief Рандомайзер
 * @return Возвращает рандомный число
 */
int randomTetr();

/**
 * @brief Чистка памяти
 * @param game Структура игры
 */
void gameDelete(Tgame *game);

/**
 * @brief Выдает символ из игрового поля по координатам
 * @param game Структура игры
 * @param row Строка
 * @param col Столбец
 * @return Символ(число)
 */
int getBlock(Tgame *game, int row, int col);

/**
 * @brief Выставляет значение блока по координатам
 * @param game Структура игры
 * @param row Строка
 * @param col Столбец
 * @param value Значение
 */
void setBlock(Tgame *game, int row, int col, int value);

/**
 * @brief Проверяет начилие блока по координатам
 * @param game Структура игры
 * @param row Строка
 * @param col Столбец
 * @return true || false
 */
bool checkBlock(const Tgame *game, int row, int col);

/**
 * @brief Добавляет тетрамино на игровое поле
 * @param game Структура игры
 * @param block Структура Тетрамино
 */
void putTetramino(Tgame *game, Tblock *block);

/**
 * @brief Убирает тетрамино с игрового поля
 * @param game Структура игры
 * @param block Структура Тетрамино
 */
void rmTetramino(Tgame *game, Tblock *block);

/**
 * @brief Проверяет, может ли тетрамино двигаться
 * @param game Структура игры
 * @param block Структура Тетрамино
 * @return true || false
 */
bool checkMovesTetramino(Tgame *game, const Tblock *block);

/**
 * @brief Выставляет новое тетрамино в falling и next
 * @param game Структура игры
 */
void newFalling(Tgame *game);

/**
 * @brief Движение тетрамино влево/вправо
 * @param game Структура игры
 * @param place значение LEFT/RIGHT
 */
void moveX(Tgame *game, int place);

/**
 * @brief Ротация тетрамино
 * @param game Структура игры
 * @param orint Направление -1/1
 */
void moveRotate(Tgame *game, int orint);

/**
 * @brief Падение тетрамино вниз на 1
 * @param game Структура игры
 */
void moveDown(Tgame *game);

/**
 * @brief Проверка на заполненую линию
 * @param game Структура игры
 * @param index Индекс строки
 * @return true || false
 */
bool isFullLines(Tgame *game, int index);

/**
 * @brief Удаление и сдвиг линий
 * @param game Структура игры
 * @param index Индекс строки
 */
void shiftLines(Tgame *game, int index);

/**
 * @brief Выполняет проверку на заполненные линии,
 * удаляет их и сдвигает
 * @param game Структура игры
 * @return Количество удаленных линий
 */
int checkLines(Tgame *game);

/**
 * @brief Прокерка на достижение верхней границы поля -> конец игры
 * @param game Структура игры
 * @return true || false
 */
bool gameOver(Tgame *game);

/**
 * @brief Падение тетрамино под действием гравитации
 * @param game Структура игры
 */
void gravityBySpeed(Tgame *game);

/**
 * @brief Основная функция игры, выполняет 1 игровой тик.
 * Гравитационный сдвиг, действие, проверка линий, обновление статистики
 * @param game Структура игры
 * @param move Действие над тетрамино
 * @return Актуальный статус игры
 */
Gstatus tick(Tgame *game, Tmove move);

/**
 * @brief Сохранение достигнутого счета в файл
 * @param game Структура игры
 */
void saveScore(const Tgame *game);

/**
 * @brief Выставление рекордного счета прошлой игры
 * @return Рекордное значение прошлой игры
 */
int getHighScore();

/**
 * @brief Обнуление полей структуры игры(начало новой игры)
 * @param game Структура игры
 */
void newGame(Tgame *game);

/**
 * @brief Обрабатывает действие игрока
 * @return Действиеие игрока
 */
Tmove action();

/**
 * @brief Обновление параметров игры
 * @param game Структура игры
 * @param clearlines Количество удаленных линий
 */
void upper(Tgame *game, int clearLines);

/**
 * @brief Падение тетрамино то соприкосновения
 * @param game Структура игры
 */
void moveDrop(Tgame *game);

/**
 * @brief Задержка времени(таймер)
 * @param milliseconds Количество миллисекунд
 */
void sleepMilli(int milliseconds);

/**
 * @brief Выполняет действие игрока
 * @param game Структура игры
 *  @param move Действие
 */
void moving(Tgame *game, Tmove move);

/**
 * @brief Содержит в себе массив, который хранит значение тиков гравитации.
 * @param inddex Индекс массива(значение скорости)
 * @return Значение массива по индексу
 */
int getGravity(int index);

/**
 * @brief Сообщает о начале новой игры
 * @param game Структура игры
 * @return true || false
 */
bool againGame(Tgame *game);

#endif
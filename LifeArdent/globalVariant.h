#include "player.h"
#include "enum.h"
#include "image.h"
#include "setting.h"
#include "form.h"

Arduboy ab;
Player p[4];

Setting setting;
long tStop = 3000000;
long tPressed = 0;
Form* menu;
Form* life;
Form* util;
Form* sett;

bool isTitle = false;
bool isMain = false;
bool isSound = true;
bool isInvertOpponent = false;
bool isTimer = false;
bool isTwoSideFromt = true;
bool pressFirst = true;
bool pressPole = false;
int changeLife = 0;
byte pCount = 0;
byte mode = PM_HEAD;

// FPS
#define FPS_SLEEP 3

// LifeArdent.ino
#define BUTTON_REPEAT 330
#define TONE_LIFE     40
#define TIME_TITLE    3000
#define TONE_ONELIFE  20
#define TONE_MIN      200
#define PLAYER_COUNT  4

// displayMenu.h
#define MENU_ICON_SIZE_X  11
#define MENU_ICON_SIZE_Y  14
#define LIFE_RESET_SECOND 5000

// displayLife.h
#define CURSOR_RECT_W 9
#define CURSOR_RECT_H 7
#define EDH_GENERAL_DAMAGE_RIMIT 21

//displayUtil.h
#define DICE_ALL_MAX 8
#define DICE_MAX     3
#define CARD_MAX     11
#define DISCARD_MAX  9
#define STORM_MAX    7
#define MATCH_MAX    6

//displaySetting.h
#define HIGHT 8
#define IND   12

//format.h
#define INIT_LIFE_NORMAL 20
#define INIT_LIFE_ARCH   40
#define INIT_LIFE_EDH    40

#include "player.h"
#include "time.h"
#include "enum.h"
#include "image.h"
#include "setting.h"
#include "form.h"

Arduboy ab;
Player p[4];

Setting setting;
TimeFormat tPressed;
TimeFormat tTimer;
Form* menu;
Form* life;
Form* util;
Form* sett;

bool isTitle = false;
bool isMain = false;
bool isSound = true;
bool pressFirst = true;

byte pCount = 0;
const byte PLAYER_COUNT = 4;
byte mode = PM_HEAD;
int changeLife = 0;

// LifeArdent.ino
#define BUTTON_REPEAT 350
#define TONE_LIFE 40
#define TIME_TITLE 3000
#define TONE_ONELIFE 20
#define TONE_MIN 200

// displayMenu.h
#define imageSizeX 11
#define imageSizeY 14
#define LIFE_RESET_SECOND 5

// displayLife.h
#define rectW 9
#define rectH 7

//displayUtil.h
#define DICE_ALL_MAX 8
#define DICE_MAX 3
#define CARD_MAX 11
#define DISCARD_MAX 9
#define STORM_MAX 7
#define MATCH_MAX 6

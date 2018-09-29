#include "Arduboy2.h"
#include "time.h"
#include "enum.h"
#include "drawUtil.h"
#include "image_form.h"
#include "image_icon.h"
#include "player.h"
#include "format.h"
#include "form.h"
#include "displayMenu.h"
#include "displayLife.h"
#include "displayUtil.h"
#include "displaySetting.h"

Arduboy2 ab;
BeepPin1 beep1;
BeepPin2 beep2;

#define BUTTON_REPEAT 350
#define TONE_LIFE 40
#define TIME_TITLE 3000
#define BASE_TONE 1000
#define TONE_ONELIFE 20
#define TONE_MIN 200

Form* activeForm = NULL;

DisplayMenu menu;
DisplayLife life;
DisplayUtil util;
DisplaySetting sett;
Format format;

bool isTitle = false;
bool isMain = true;
bool isSetting = false;
bool pressFirst = true;

void setup()
{
  init();

  menu.ab = &ab;
  life.ab = &ab;
  util.ab = &ab;
  sett.ab = &ab;
  menu.format = &format;
  life.format = &format;
  util.format = &format;
  sett.format = &format;
  menu.menu = &menu;
  life.menu = &menu;
  util.menu = &menu;
  sett.menu = &menu;
  menu.life = &life;
  util.life = &life;
  life.life = &life;
  sett.life = &life;
  menu.util = &util;
  life.util = &util;
  util.util = &util;
  sett.util = &util;
  menu.sett = &sett;
  life.sett = &sett;
  util.sett = &sett;
  sett.sett = &sett;
  
  format.initMode(sett.defaultFormat);
  ab.setFrameRate(sett.frameRateMain);
  ab.invert(sett.blackScreen);
  isTitle = (sett.showTitle == 0x01);
  format.isSound = (sett.isDefaultSoundOn == 0x01);
  util.isLedTimer = (sett.isLedTimer == 0x01);
  util.isLedStorm = (sett.isLedStorm == 0x01);
  
  menu.activeMenu();

  ab.boot();
  ab.audio.begin();
  beep1.begin();
  beep2.begin();
}

void loop()
{
  if (!(ab.nextFrame()))
  {
    return;
  }
  ab.clear();
  button();
  disp();
  ab.display();
  beep1.timer();
  beep2.timer();
}

void disp()
{
  if (isTitle)
  {
    dispTitle();
  }
  else if (isMain)
  {
    menu.display();
    life.display();
    util.display();
  }
  else if (isSetting)
  {
    sett.display();
  }
}

void dispTitle()
{
  if (isTitle && millis() > TIME_TITLE)
  {
    isTitle = false;
    isMain = true;
    return;
  }

  ab.drawBitmap(0, 17, mtg_logo, 128, 34, WHITE);
}

void button()
{
  if (!someButtonPressed())
  {
    ab.setFrameRate(sett.frameRateMain);
    format.tPressed.setDefaultTime();
    pressFirst = true;
    return;
  }

  if (!arrowButtonPress())
  {
    return;
  }

  if (isTitle)
  {
    isTitle = false;
    isMain = true;
    return true;
  }

  ab.setFrameRate(sett.frameRateRepeat);

  pressButton();
  buttonSound();
}

bool someButtonPressed()
{
  return (ab.pressed(UP_BUTTON)   || ab.pressed(DOWN_BUTTON)  ||
          ab.pressed(LEFT_BUTTON) || ab.pressed(RIGHT_BUTTON) ||
          ab.pressed(A_BUTTON)    || ab.pressed(B_BUTTON));
}

bool arrowButtonPress()
{
  format.tPressed.setStopTime();

  if (pressFirst)
  {
    pressFirst = false;
    return true;
  }

  return (abs(format.tPressed.getSubMillisecond()) >= BUTTON_REPEAT);
}

void buttonSound()
{
  if (!format.isSound)
  {
    return;
  }

  short t1 = sett.baseTone1;
  short t2 = sett.baseTone2;
  if (life.isCursor)
  {
    short l = format.p[life.cursor].life;
    // t = BASE_TONE - (TONE_LIFE * TONE_ONELIFE) - ((l <= 0) ? 0 : ((l > TONE_MIN) ? TONE_MIN : l) * TONE_LIFE);
    // t =
  }
  beep1.tone(beep1.freq(t1), 1);
  beep2.tone(beep2.freq(t2), 1);
}

void setActiveForm()
{
  activeForm = NULL;

  if (menu.isCursor)
  {
    activeForm = &menu;
  }
  else if (life.isCursor)
  {
    activeForm = &life;
  }
  else if (util.isCursor)
  {
    activeForm = &util;
  }
  else if (sett.isCursor)
  {
    activeForm = &sett;
  }
}

void pressButton()
{
  setActiveForm();

  if (activeForm == NULL)
  {
    return;
  }

  if (ab.pressed(UP_BUTTON))
  {
    activeForm->upButton();
  }
  else if (ab.pressed(DOWN_BUTTON))
  {
    activeForm->downButton();
  }
  else if (ab.pressed(LEFT_BUTTON))
  {
    activeForm->leftButton();
  }
  else if (ab.pressed(RIGHT_BUTTON))
  {
    activeForm->rightButton();
  }

  if (ab.pressed(A_BUTTON) && ab.pressed(B_BUTTON))
  {
    activeForm->abButton();
  }
  else if (ab.pressed(A_BUTTON))
  {
    activeForm->aButton();
  }
  else if (ab.pressed(B_BUTTON))
  {
    activeForm->bButton();
  }
}

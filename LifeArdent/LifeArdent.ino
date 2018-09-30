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

#define BUTTON_REPEAT 350
#define TONE_LIFE 40
#define TIME_TITLE 3000
#define TONE_ONELIFE 20
#define TONE_MIN 200

const byte LEDpin[3] = {
  RED_LED,
  GREEN_LED,
  BLUE_LED
};

Form* activeForm = NULL;

DisplayMenu menu;
DisplayLife life;
DisplayUtil util;
DisplaySetting sett;
Format format;

bool isTitle = false;
bool isMain = false;
bool pressFirst = true;

void setup()
{
  ab.setRGBled(0, 0, 0);
  init();
  ab.boot();

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
  isMain = !isTitle;
  format.isSound = (sett.isSoundDefault == 0x01);

  menu.activeMenu();

  ab.audio.begin();
  beep1.begin();
}

void loop()
{
  beep1.timer();
  if (!(ab.nextFrame()))
  {
    return;
  }
  ab.clear();
  button();
  disp();
  alarm();
  ab.display();
}

void disp()
{
  if (isMain)
  {
    menu.display();
    life.display();
    util.display();
  }
  else if (sett.isCursor)
  {
    sett.display();
  }
  else if (isTitle)
  {
    dispTitle();
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

  pressButton();
  buttonSound();
}

void alarm()
{
  if (util.isAlarm)
  {
    util.isAlarm = false;
    for (byte i = 0; i < format.tTimer.m / 10; i++)
    {
      if (sett.isLedTimer != 0x00)
      {
        ab.setRGBled(LEDpin[sett.isLedTimer - 1], format.tTimer.m);
      }
      if (sett.isSoundTimer != 0x00)
      {
        beep1.tone(beep1.freq(sett.baseTone), 1);
      }
      delay(250);
      ab.setRGBled(LEDpin[sett.isLedTimer - 1], 0);
    }
  }
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

  short t1 = sett.baseTone;
  if (life.isCursor)
  {
    short l = format.p[life.cursor].life;
    t1 += (l >= 100) ? (TONE_ONELIFE * 80) : (l <= -20) ? (TONE_ONELIFE * -40) : ((l - 20) * TONE_ONELIFE);
  }
  beep1.tone(beep1.freq(t1), 1);
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

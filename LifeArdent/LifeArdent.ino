#include "Arduboy.h"
#include "time.h"
#include "enum.h"
#include "drawUtil.h"
#include "image_form.h"
#include "image_icon.h"
#include "player.h"
#include "setting.h"
#include "form.h"
#include "displayMenu.h"
#include "displayLife.h"
#include "displayUtil.h"

Arduboy ab;

const char FRAME_RATE = 20;
const short BUTTON_REPEAT = 350;
const char TONE_LIFE = 40;
const short TIME_TITLE = 3000;
const short BASE_TONE = 1000;

Form* activeForm = NULL;

DisplayMenu menu;
DisplayLife life;
DisplayUtil util;
Setting setting;

bool isTitle = true;
bool isMain = false;
bool isSetting = false;

bool pressFirst = true;

void setup()
{
  init();

  ab.beginNoLogo();
  ab.setFrameRate(FRAME_RATE);

  menu.ab = &ab;
  life.ab = &ab;
  util.ab = &ab;
  menu.setting = &setting;
  life.setting = &setting;
  util.setting = &setting;
  menu.menu = &menu;
  life.menu = &menu;
  util.menu = &menu;
  menu.life = &life;
  util.life = &life;
  life.life = &life;
  menu.util = &util;
  life.util = &util;
  util.util = &util;

  setting.initMode(P2);
  menu.activeMenu();
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
}

void dispTitle()
{
  if (millis() > TIME_TITLE)
  {
    isTitle = false;
    isMain = true;
    return;
  }

  ab.drawBitmap(0, 0, mtg_logo, 128, 64, WHITE);
}

void button()
{
  if (!someButtonPressed())
  {
    setting.tPressed.setDefaultTime();
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

bool someButtonPressed()
{
  return (ab.pressed(UP_BUTTON)   || ab.pressed(DOWN_BUTTON)  ||
          ab.pressed(LEFT_BUTTON) || ab.pressed(RIGHT_BUTTON) ||
          ab.pressed(A_BUTTON)    || ab.pressed(B_BUTTON));
}

bool arrowButtonPress()
{
  setting.tPressed.setStopTime();

  if (pressFirst)
  {
    pressFirst = false;
    return true;
  }

  return (abs(setting.tPressed.getSubMillisecond()) >= BUTTON_REPEAT);
}

void buttonSound()
{
  if (setting.isSound)
  {
    short tone = BASE_TONE;
    if (life.isCursor)
    {
      tone = life.getLifeTone(BASE_TONE, TONE_LIFE);
    }
    ab.tunes.tone(tone, 20);
  }
}

void setActiveForm()
{
  activeForm = NULL;

  if (menu.isCursor)
  {
    activeForm = &menu;
  }

  if (life.isCursor)
  {
    activeForm = &life;
  }

  if (util.isCursor)
  {
    activeForm = &util;
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

  if (ab.pressed(DOWN_BUTTON))
  {
    activeForm->downButton();
  }

  if (ab.pressed(LEFT_BUTTON))
  {
    activeForm->leftButton();
  }

  if (ab.pressed(RIGHT_BUTTON))
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


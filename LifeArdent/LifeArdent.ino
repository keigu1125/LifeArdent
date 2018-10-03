#include "Arduboy.h"
#include "string.h"
#include "globalVariant.h"
#include "util.h"
#include "format.h"
#include "displayMenu.h"
#include "displayLife.h"
#include "displayUtil.h"
#include "displaySetting.h"

void setup()
{
  init();
  ab.beginNoLogo();
  ab.setRGBled(0, 0, 0);

  menu = new DisplayMenu();
  life = new DisplayLife();
  util = new DisplayUtil();
  sett = new DisplaySetting();

  setting.readEepRomSetting();

  initMode(setting.defaultFormat);
  ab.setFrameRate(setting.frameRateMain);
  ab.invert(setting.blackScreen);
  isTitle = (setting.showTitle == 0x01);
  isMain = !isTitle;
  isSound = (setting.isSoundDefault == 0x01);

  activeMenu();
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
  if (sett->isCursor)
  {
    sett->display();
  }
  else if (isMain)
  {
    menu->display();
    life->display();
    util->display();
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
    tPressed.setStop();
    pressFirst = true;
    return;
  }

  if (!allowButtonPress())
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

bool allowButtonPress()
{
  tPressed.setNow();

  if (pressFirst)
  {
    pressFirst = false;
    return true;
  }

  return (tPressed.getMillis() >= BUTTON_REPEAT);
}

void buttonSound()
{
  if (!isSound)
  {
    return;
  }

  int t1 = setting.baseTone;
  if (life->isCursor)
  {
    int l = p[life->cursor].life;
    t1 += (l >= 100) ? (TONE_ONELIFE * 80) : (l <= -20) ? (TONE_ONELIFE * -40) : ((l - 20) * TONE_ONELIFE);
  }
  ab.tunes.tone(t1, 20);
}

Form* setActiveForm()
{
  Form* activeForm = NULL;

  if (menu->isCursor)
  {
    activeForm = menu;
  }
  else if (life->isCursor)
  {
    activeForm = life;
  }
  else if (util->isCursor)
  {
    activeForm = util;
  }
  else if (sett->isCursor)
  {
    activeForm = sett;
  }

  return activeForm;
}

void pressButton()
{
  Form* activeForm = setActiveForm();

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

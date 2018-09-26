#include "Arduboy.h"
#include "time.h"
#include "enum.h"
#include "drawUtil.h"
#include "image_form.h"
#include "image_icon.h"
#include "player.h"
#include "form.h"
#include "displayMenu.h"
#include "displayLife.h"
#include "displayUtil.h"

Arduboy ab;

const int FRAME_RATE = 20;
const int BUTTON_REPEAT = 350;
const int BEEP_LIFE = 40;
const int TIME_TITLE = 3000;

DisplayMenu menu;
DisplayLife life;
DisplayUtil util;

bool isTitle = true;
bool isMain = false;
bool isSetting = false;

bool isFlash = false;

int pressCnt = 0;

int changeLife = 0;

Time tStw;
Time tPressed;

String time = "0:00:00";

void setup()
{
  ab.beginNoLogo();
  ab.setFrameRate(FRAME_RATE);

  menu.ab = &ab;
  life.ab = &ab;
  util.ab = &ab;
  util.menu = &menu;
  util.life = &life;

  menu.isCursor = true;

  life.initMode(P2);
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
  }

  ab.drawBitmap(0, 0, mtg_logo, 128, 64, WHITE);
}

void button()
{
  if (isTitle && someButtonPressed())
  {
    isTitle = false;
    isMain = true;
    return;
  }

  if (buttonPressOnce())
  {
    return;
  }

  upButton();
  downButton();
  leftButton();
  rightButton();

  aButton();
  bButton();

  buttonSound();
}

bool someButtonPressed()
{
  return (ab.pressed(UP_BUTTON)   || ab.pressed(DOWN_BUTTON)  ||
          ab.pressed(LEFT_BUTTON) || ab.pressed(RIGHT_BUTTON) ||
          ab.pressed(A_BUTTON)    || ab.pressed(B_BUTTON));
}

bool buttonPressOnce()
{
  if (!someButtonPressed())
  {
    menu.tPressed.setDefaultTime();
    pressCnt = 0;
    return false;
  }

  menu.tPressed.setStopTime();

  if (abs(menu.tPressed.getSubMillisecond()) >= BUTTON_REPEAT)
  {
    return false;
  }

  pressCnt++;

  return pressCnt != 1;
}

void buttonSound()
{
  if (!someButtonPressed())
  {
    return;
  }

  if (menu.isSound)
  {
    int tone = 1000;
    if (life.isCursor)
    {
      int l = life.p[life.cursorP].life;
      tone = 1000 - (BEEP_LIFE * 20) + ((l <= 0) ? 0 : ((l > 200) ? 200 : l) * BEEP_LIFE);
    }
    ab.tunes.tone(tone, 20);
  }
}

void upButton()
{
  if (!ab.pressed(UP_BUTTON))
  {
    return;
  }

  if (menu.isCursor)
  {
    menu.setCursor(-1);
  }

  if (life.isCursor)
  {
    if (life.isCursorC)
    {
      if (life.cursorC != life.cursorP && life.p[life.cursorP].c[life.cursorC] < 21)
      {
        life.p[life.cursorP].c[life.cursorC]++;
        life.p[life.cursorP].life--;
        menu.changeLife--;
      }
    }
    else
    {
      life.p[life.cursorP].life++;
      menu.changeLife++;
    }
  }
}

void downButton()
{
  if (!ab.pressed(DOWN_BUTTON))
  {
    return;
  }

  if (menu.isCursor)
  {
    menu.setCursor(+1);
  }

  if (life.isCursor)
  {
    if (life.isCursorC)
    {
      if (life.cursorC != life.cursorP && life.p[life.cursorP].c[life.cursorC] > 0)
      {
        life.p[life.cursorP].c[life.cursorC]--;
        life.p[life.cursorP].life++;
        menu.changeLife++;
      }
    }
    else
    {
      life.p[life.cursorP].life--;
      menu.changeLife--;
    }
  }
}

void leftButton()
{
  if (!ab.pressed(LEFT_BUTTON))
  {
    return;
  }

  if (!isMain)
  {
    return;
  }

  menu.changeLife = 0;

  if (menu.isCursor)
  {
    menu.isCursor = false;
    life.isCursor = true;
    life.cursorP = life.pCount - 1;
    return;
  }

  if (util.isCursor)
  {
    switch (menu.cursorM)
    {
      case 0:
        life.initMode(life.mode - 1);
        break;
    }
    return;
  }

  if (life.isCursor)
  {
    if (life.isCursorC)
    {
      life.cursorC--;
      if (life.cursorC < 0)
      {
        life.cursorC = 3;
      }
    }
    else
    {
      if (life.cursorP > 0)
      {
        life.cursorP--;
      }
      else
      {
        menu.isCursor = true;
        life.isCursor = false;
      }
    }
    return;
  }
}

void rightButton()
{
  if (!ab.pressed(RIGHT_BUTTON))
  {
    return;
  }

  if (!isMain)
  {
    return;
  }

  menu.changeLife = 0;

  if (menu.isCursor)
  {
    menu.isCursor = false;
    life.isCursor = true;
    life.cursorP = PM_HEAD;
    return;
  }

  if (util.isCursor)
  {
    switch (menu.cursorM)
    {
      case 0:
        life.initMode(life.mode + 1);
        break;
    }
    return;
  }

  if (life.isCursor)
  {
    if (life.isCursorC)
    {
      life.cursorC++;
      if (life.cursorC >= 4)
      {
        life.cursorC = 0;
      }
    }
    else
    {
      if (life.cursorP < life.pCount - 1)
      {
        life.cursorP++;
      }
      else
      {
        menu.isCursor = true;
        life.isCursor = false;
      }
      return;
    }
  }
}

void aButton()
{
  if (!ab.pressed(A_BUTTON))
  {
    return;
  }

  if (ab.pressed(B_BUTTON))
  {
    abButton();
    return;
  }

  if (menu.isCursor)
  {
    switch (menu.cursorM)
    {
      case M_PLAYER:
        util.isCursor = false;
        menu.isCursor = true;
        life.isCursor = false;
        break;
      case M_DICE:
        break;
      case M_MATCH:
        break;
      case M_TIME:
        break;
      case M_DISCARD:
        break;
      case M_STORM:
        break;
      case M_COUNT:
        break;
      case M_SOUND:
        menu.isSound = !menu.isSound;
        break;
      case M_SETTING:
        break;
    }
    return;
  }

  if (util.isCursor)
  {

    util.isCursor = false;
    menu.isCursor = true;
    life.isCursor = false;

    return;
  }

  if (life.isCursor)
  {
    if (life.mode == P2)
    {
      int value = (life.cursorP == 0) ? - 1 : + 1;

      life.p[0].life += value;
      life.p[1].life -= value;
      menu.changeLife--;
    }
    else if (life.mode == EDH)
    {
      life.isCursorC = !life.isCursorC;
      life.cursorC = life.cursorP;
    }
  }
}

void bButton()
{
  if (!ab.pressed(B_BUTTON))
  {
    return;
  }

  if (ab.pressed(A_BUTTON))
  {
    abButton();
    return;
  }

  if (menu.isCursor)
  {
    switch (menu.cursorM) {
      case M_PLAYER:
        util.isCursor = true;
        menu.isCursor = false;
        life.isCursor = false;
        break;
      case M_DICE:
        break;
      case M_MATCH:
        break;
      case M_TIME:
        break;
      case M_DISCARD:
        break;
      case M_STORM:
        break;
      case M_COUNT:
        break;
      case M_SOUND:
        menu.isSound = !menu.isSound;
        break;
      case M_SETTING:
        break;
    }
    return;
  }

  if (life.isCursor)
  {
    if (life.mode == P2)
    {
      int value = (life.cursorP == 0) ? + 1 : - 1;

      life.p[0].life += value;
      life.p[1].life -= value;
      menu.changeLife++;
    }
    else if (life.mode == EDH)
    {
      life.isCursorC = !life.isCursorC;
      life.cursorC = life.cursorP;
    }
  }
}

void abButton()
{
  if (!ab.pressed(A_BUTTON) || !ab.pressed(B_BUTTON))
  {
    return;
  }

  if (life.isCursor)
  {
    life.initPlayerLife();
    menu.changeLife = 0;
  }
}


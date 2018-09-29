class DisplayUtil : public Form {
  private:
#define DICE_ALL_MAX 8
#define DICE_MAX 3
#define CARD_MAX 11
#define DISCARD_MAX 9
#define STORM_MAX 7
  public:
    byte hand = 7;
    byte discard = 2;
    byte card[11];
    byte cursorC = 0;
    byte storm[7];
    byte dCount = 2;
    byte d[8];
    byte cPage = 0;
    byte mPage = 0;
    String stopTime = "0:00:00";
    bool isTimer = false;
    bool isLedTimer = false;
    bool isLedStorm = false;

    DisplayUtil()
    {
      x = 1;
      y = 55;
      // isCursor = false;
      // cursor = 0;
      // cursorMax = 0;

      // 乱数生成
      Serial.begin(9600);
      randomSeed(analogRead(0));
      Serial.end();
    }

    void DisplayUtil::display()
    {
      String out = "";
      if (isCursor)
      {
        switch (menu->cursor)
        {
          case Menu::M_PLAYER:
            out += format->getModeName(format->mode - 1);
            out += (format->mode > PM_HEAD) ? " << " : "    ";
            out += format->getModeName(format->mode);
            out += (format->mode < PM_TAIL) ? " >> " : "    ";
            out += format->getModeName(format->mode + 1);
            break;
          case Menu::M_DICE:
            dispDice();
            break;
          case Menu::M_MATCH:
            dispMatch();
            break;
          case Menu::M_TIME:
            dispTimer();
            break;
          case Menu::M_DISCARD:
            dispDiscard();
            break;
          case Menu::M_STORM:
            dispStorm();
            break;
          case Menu::M_COUNT:
            dispCounter();
            break;
          case Menu::M_SOUND:
            activeMenu();
            break;
          case Menu::M_SETTING:
            out = "Life Ardent Settings.";
            break;
        }
      }
      else if (menu->isCursor)
      {
        switch (menu->cursor)
        {
          case Menu::M_PLAYER:
            out = "Select Format.";
            break;
          case Menu::M_DICE:
            out = "Dice Roll, max 5D6.";
            break;
          case Menu::M_MATCH:
            out = "Count Match win.";
            break;
          case Menu::M_TIME:
            if (isTimer)
            {
              dispTimer();
            }
            else
            {
              out = "50 min stopwatch.";
            }
            break;
          case Menu::M_DISCARD:
            out = "Choose Random Discard.";
            break;
          case Menu::M_STORM:
            out = "Count Storm & mana.";
            break;
          case Menu::M_COUNT:
            if (format->isCounterUsed())
            {
              dispCounter();
            }
            else
            {
              out = "Count Player Counter.";
            }
            break;
          case Menu::M_SOUND:
            out = (format->isSound) ? "Set Sound. [ ON ]" : "Set Sound. [MUTE]";
            break;
          case Menu::M_SETTING:
            out = "Life Ardent Settings.";
            break;
        }
      }
      else if (life->isCursor)
      {
        switch (menu->cursor)
        {
          case Menu::M_PLAYER:
            break;
          case Menu::M_DICE:
            break;
          case Menu::M_MATCH:
            break;
          case Menu::M_TIME:
            if (isTimer)
            {
              dispTimer();
            }
            break;
          case Menu::M_DISCARD:
            break;
          case Menu::M_STORM:
            break;
          case Menu::M_COUNT:
            if (format->isCounterUsed())
            {
              dispCounter();
            }
            break;
          case Menu::M_SOUND:
            break;
          case Menu::M_SETTING:
            break;
        }
      }
      drawText(ab, x, y, 1, out);
    }

    virtual void upButton()
    {
      byte max = 0;
      switch (menu->cursor)
      {
        case Menu::M_PLAYER:
          break;
        case Menu::M_DICE:
          addValue(&dCount, DICE_MAX);
          break;
        case Menu::M_MATCH:
          switch (cursorC)
          {
            case 0:
              addValue(&mPage, 4);
              addValue(&mPage, 4);
              break;
            case 1:
              addValue(&format->p[mPage].win, 4);
              break;
            case 2:
              addValue(&format->p[mPage + 1].win, 4);
              break;
          }
          break;
        case Menu::M_TIME:
          break;
        case Menu::M_DISCARD:
          switch (cursorC)
          {
            case 0:
              addValue(&hand, CARD_MAX);
              break;
            case 1:
              max = (DISCARD_MAX < hand) ? DISCARD_MAX : hand;
              addValue(&discard, max);
              break;
          }
          break;
        case Menu::M_STORM:
          max = (cursorC == 0) ? 99 : 9;
          addValue(&storm[cursorC], max);
          break;
        case Menu::M_COUNT:
          switch (cursorC)
          {
            case 0:
              addValue(&cPage, (format->PLAYER_COUNT) - 1);
              break;
            case 1:
              addValue(&format->p[cPage].counter1, 10);
              break;
            case 2:
              addValue(&format->p[cPage].counter2, 10);
              break;
          }
          break;
        case Menu::M_SOUND:
          break;
        case Menu::M_SETTING:
          break;
      }
    }

    virtual void downButton()
    {
      byte max = 0;
      switch (menu->cursor)
      {
        case Menu::M_PLAYER:
          break;
        case Menu::M_DICE:
          subValue(&dCount, 1);
          break;
        case Menu::M_MATCH:
          switch (cursorC)
          {
            case 0:
              subValue(&mPage, 0);
              subValue(&mPage, 0);
              break;
            case 1:
              subValue(&format->p[mPage].win, 0);
              break;
            case 2:
              subValue(&format->p[mPage + 1].win, 0);
              break;
          }
          break;
          break;
        case Menu::M_TIME:
          break;
        case Menu::M_DISCARD:
          switch (cursorC)
          {
            case 0:
              subValue(&hand, 1);
              if (hand < discard)
              {
                discard = hand;
              }
              break;
            case 1:
              subValue(&discard, 1);
              break;
          }
          break;
        case Menu::M_STORM:
          subValue(&storm[cursorC], 0);
          break;
        case Menu::M_COUNT:
          switch (cursorC)
          {
            case 0:
              subValue(&cPage, 0);
              break;
            case 1:
              subValue(&format->p[cPage].counter1, 0);
              break;
            case 2:
              subValue(&format->p[cPage].counter2, 0);
              break;
          }
          break;
        case Menu::M_SOUND:
          break;
        case Menu::M_SETTING:
          break;
      }
    }

    virtual void leftButton()
    {
      byte max = 0;
      switch (menu->cursor)
      {
        case Menu::M_PLAYER:
          format->initMode(format->mode - 1);
          return;
        case Menu::M_SOUND:
        case Menu::M_SETTING:
          return;
        case Menu::M_DICE:
          max = UtilMenuMax::MAX_DICE;
          break;
        case Menu::M_MATCH:
          max = UtilMenuMax::MAX_MATCH;
          break;
        case Menu::M_TIME:
          max = UtilMenuMax::MAX_TIME;
          break;
        case Menu::M_DISCARD:
          max = UtilMenuMax::MAX_DISCARD;
          break;
        case Menu::M_STORM:
          max = UtilMenuMax::MAX_STORM;
          break;
        case Menu::M_COUNT:
          max = UtilMenuMax::MAX_COUNT;
          break;
      }

      rotateDown(&cursorC, 0, max);
    }

    virtual void rightButton()
    {
      byte max = 0;
      switch (menu->cursor)
      {
        case Menu::M_PLAYER:
          format->initMode(format->mode + 1);
          return;
        case Menu::M_SOUND:
        case Menu::M_SETTING:
          return;
        case Menu::M_DICE:
          max = UtilMenuMax::MAX_DICE;
          break;
        case Menu::M_MATCH:
          max = UtilMenuMax::MAX_MATCH;
          break;
        case Menu::M_TIME:
          max = UtilMenuMax::MAX_TIME;
          break;
        case Menu::M_DISCARD:
          max = UtilMenuMax::MAX_DISCARD;
          break;
        case Menu::M_STORM:
          max = UtilMenuMax::MAX_STORM;
          break;
        case Menu::M_COUNT:
          max = UtilMenuMax::MAX_COUNT;
          break;
      }

      rotateUp(&cursorC, 0, max);
    }

    virtual void aButton()
    {
      cursorC = 0;
      hand = 7;
      discard = 1;
      dCount = 2;
      initDiscard();
      initStorm();
      initDice();

      activeMenu();
    }

    virtual void bButton()
    {
      switch (menu->cursor)
      {
        case Menu::M_PLAYER:
          activeMenu();
          break;
        case Menu::M_DICE:
          diceRoll();
          break;
        case Menu::M_TIME:
          if (!isTimer)
          {
            stopTime = format->tTimer.getSubTimeString();
            format->tTimer.setStopTime();
            format->tTimer.addHour(-format->tTimer.h);
            format->tTimer.addMinute(-format->tTimer.m);
            format->tTimer.addSecond(-format->tTimer.s);
          }
          isTimer = !isTimer;
          break;
        case Menu::M_DISCARD:
          discardRoll();
          break;
        case Menu::M_MATCH:
        case Menu::M_STORM:
        case Menu::M_COUNT:
        case Menu::M_SOUND:
        case Menu::M_SETTING:
          break;
      }
    }

    virtual void abButton()
    {
      switch (menu->cursor)
      {
        case Menu::M_TIME:
          isTimer = false;
          format->tTimer.setDefaultTime();
          format->tTimer.setStopTime();
          stopTime = format->tTimer.getSubTimeString();
          break;
        case Menu::M_DISCARD:
          initDiscard();
          break;
        case Menu::M_STORM:
          initStorm();
          break;
        case Menu::M_PLAYER:
        case Menu::M_DICE:
          initDice();
          break;
        case Menu::M_MATCH:
          break;
        case Menu::M_COUNT:
          format->initCounter();
          break;
        case Menu::M_SOUND:
        case Menu::M_SETTING:
          break;
      }
    }

  private:
    void DisplayUtil::initStorm()
    {
      for (byte i = 0; i < STORM_MAX; i++)
      {
        storm[i] = 0;
      }
    }

    void DisplayUtil::initDiscard()
    {
      for (byte i = 0; i < CARD_MAX; i++)
      {
        card[i] = 0;
      }
    }

    void DisplayUtil::initDice()
    {
      for (byte i = 0; i < DICE_ALL_MAX; i++)
      {
        d[i] = 0;
      }
    }

    void DisplayUtil::discardRoll()
    {
      initDiscard();

      byte dc = 0;
      while (dc < discard)
      {
        byte r = random(hand);
        if (card[r] == 0)
        {
          card[r] = 1;
          dc++;
        }
      }
    }

    void DisplayUtil::diceRoll()
    {
      for (byte i = 0; i < DICE_ALL_MAX; i++)
      {
        d[i] = random(6) + 1;
      }
    }

    void DisplayUtil::dispCounter()
    {
      if (isCursor)
      {
        drawArrowLeft(ab, x + ((cursorC == 0) ? 0 : x + 30 + ((cursorC - 1) * 49)), y, WHITE);
      }

      drawText(ab, x + 9, y, 1, "P");
      drawText(ab, x + 19, y, 1, cPage + 1);
      ab->drawLine(x + 29, y, x + 29, y + 6, WHITE);
      ab->drawLine(x + 78, y, x + 78, y + 6, WHITE);

      for (byte i = 0; i < format->p[cPage].counter1; i++)
      {
        byte drawX = x + 37 + (i * 4);
        byte drawY = y + 7;

        byte w = 2;
        byte h = (i == 4) ? 4 : (i == 9) ? 7 : 2;

        ab->fillRect(drawX, drawY - h, w, h, WHITE);
      }
      for (byte i = 0; i < format->p[cPage].counter2; i++)
      {
        byte drawX = x + 86 + (i * 4);
        byte drawY = y + 7;

        byte w = 2;
        byte h = (i == 4) ? 4 : (i == 9) ? 7 : 2;

        ab->fillRect(drawX, drawY - h, w, h, WHITE);
      }
    }

    void DisplayUtil::dispMatch()
    {
      if (isCursor)
      {
        drawArrowLeft(ab, x + ((cursorC == 0) ? 0 : x + 30 + ((cursorC - 1) * 49)), y, WHITE);
      }

      drawText(ab, x + 6, y, 1, String(mPage + 1) + " " + String(mPage + 2));
      drawText(ab, x + 12, y + 2, 1, "~");
      ab->drawLine(x + 29, y, x + 29, y + 6, WHITE);
      ab->drawLine(x + 78, y, x + 78, y + 6, WHITE);

      for (byte i = 0; i < format->p[mPage].win; i++)
      {
        byte drawX = x + 36 + (i * 10);
        byte drawY = y - 1;

        ab->drawBitmap(drawX, drawY, i_s_win, 9, 9, WHITE);
      }
      for (byte i = 0; i < format->p[mPage + 1].win; i++)
      {
        byte drawX = x + 85 + (i * 10);
        byte drawY = y - 1;

        ab->drawBitmap(drawX, drawY, i_s_win, 9, 9, WHITE);
      }
    }

    void DisplayUtil::dispStorm()
    {
      ab->drawBitmap(x +   2, y - 1, i_s_storm, 9, 9, WHITE);
      ab->drawBitmap(x +  26, y - 1, i_s_white, 9, 9, WHITE);
      ab->drawBitmap(x +  43, y - 1, i_s_blue , 9, 9, WHITE);
      ab->drawBitmap(x +  60, y - 1, i_s_black, 9, 9, WHITE);
      ab->drawBitmap(x +  77, y - 1, i_s_red  , 9, 9, WHITE);
      ab->drawBitmap(x +  94, y - 1, i_s_green, 9, 9, WHITE);
      ab->drawBitmap(x + 111, y - 1, i_s_less , 9, 9, WHITE);

      drawText(ab, x +  12, y, 1, storm[0]);
      for (byte i = 1; i < STORM_MAX; i++)
      {
        drawText(ab, x + 18 + (i * 17), y, 1, storm[i]);
      }

      ab->drawRect(x + ((cursorC == 0) ? 0 : x + 6 + (cursorC * 17)), y, 2, 7, WHITE);
    }

    void DisplayUtil::dispDice()
    {
      byte dSum1 = 0;
      byte dSum2 = 0;
      drawArrowLeft(ab, x, y, WHITE);
      drawText(ab, x + 7, y, 1, dCount);
      drawText(ab, x + 13, y, 1, "d6");
      ab->drawLine(x + 29, y, x + 29, y + 6, WHITE);
      ab->drawLine(x + 78, y, x + 78, y + 6, WHITE);
      for (byte i = 0; i < dCount; i++)
      {
        drawBigDice(ab, x + 33 + (10 * i), y, d[i]);
        dSum1 += d[i];
      }
      drawText(ab, x + 64, y, 1, dSum1);
      for (byte i = 0; i < dCount; i++)
      {
        drawBigDice(ab, x + 82 + (10 * i), y, d[i + 4]);
        dSum2 += d[i + 4];
      }
      drawText(ab, x + 113, y, 1, dSum2);
    }

    void DisplayUtil::dispDiscard()
    {
      drawArrowLeft(ab, x + ((cursorC == 0) ? 0 : 27), y, WHITE);
      ab->drawBitmap(x +  5, y - 1, i_s_hand, 9, 9, WHITE);
      ab->drawBitmap(x + 31, y - 1, i_s_down, 9, 9, WHITE);
      drawText(ab, x + 14, y, 1, hand);
      drawText(ab, x + 40, y, 1, discard);
      ab->drawLine(x + 47, y, x + 47, y + 6, WHITE);
      for (byte i = 0; i < hand; i++)
      {
        ab->drawBitmap(x + 41 + (CARD_MAX - i) * 7, y - 1, (card[i] == 0) ? i_s_card : i_s_discard, 9, 9, WHITE);
      }
    }

    void DisplayUtil::dispTimer()
    {
      if (isTimer)
      {
        format->tTimer.setDefaultTime();
      }
      if (isCursor)
      {
        drawArrowLeft(ab, x, y, WHITE);
      }
      ab->drawBitmap(x + 51, y - 1, (isTimer) ? i_s_play : i_s_stop, 9, 9, WHITE);
      drawText(ab, x + 6, y, 1, (isTimer) ? format->tTimer.getSubTimeString() : stopTime);
      ab->fillRect(x + 64, y, format->tTimer.m, 3, WHITE);
      ab->drawLine(x + 64, y + 6, x + 124, y + 6, WHITE);
      for (byte i = 0; i <= 60; i += 5)
      {
        byte hight = (i % 10 == 0) ? 2 : 1;
        byte lineX = x + 64 + i;
        byte lineY = y + 6;
        ab->drawLine(lineX, lineY - hight, lineX, lineY, WHITE);
      }
    }

};

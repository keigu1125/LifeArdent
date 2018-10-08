class DisplayUtil : public Form
{
  private:
  public:
    byte hand = 7;
    byte discard = 2;
    byte card[11] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    byte storm[7] = {0, 0, 0, 0, 0, 0, 0};
    byte dCount = 2;
    byte d[8] = {0, 0, 0, 0, 0, 0, 0, 0};
    byte cPage = 0;
    byte mPage = 0;
    // MAX_PLAYER, MAX_DICE, MAX_TIME, MAX_DISCARD, MAX_STORM, MAX_COUNR, MAX_SOUND, MAX_SETTING
    const PROGMEM byte utilMenuMax[9] = {0, 1, 0, 1, 6, 2, 0, 0};

    DisplayUtil()
    {
      x = 1;
      y = 55;
      // isCursor = false;
      // cursor = 0;
      // cursorMax = 0;

      ab.initRandomSeed();
    }

    void DisplayUtil::display()
    {
      String out = "";
      if (isCursor)
      {
        switch (menu->cursor)
        {
          case Menu::M_PLAYER:
            out = getModeName(mode - 1)
                  + (mode > PM_HEAD ? " << " : "    ")
                  + getModeName(mode)
                  + (mode < PM_TAIL ? " >> " : "    ")
                  + getModeName(mode + 1);
            break;
          case Menu::M_DICE:
            dispDice();
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
            out = "Dice Roll, max 3D6.";
            break;
          case Menu::M_TIME:
            if (isTimer)
            {
              dispTimer();
            }
            else
            {
              out = "Clock Timer.";
            }
            break;
          case Menu::M_DISCARD:
            out = "Choose Random Cards.";
            break;
          case Menu::M_STORM:
            out = "Count Storm & mana.";
            break;
          case Menu::M_COUNT:
            if (isCounterUsed())
            {
              dispCounter();
            }
            else
            {
              out = "Count Player Counter.";
            }
            break;
          case Menu::M_SOUND:
            out = "Set Sound. ";
            out += ((isSound) ? "[ ON ]" : "[MUTE]");
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
          case Menu::M_TIME:
            if (isTimer)
            {
              dispTimer();
            }
            break;
          case Menu::M_COUNT:
            if (isCounterUsed())
            {
              dispCounter();
            }
            break;
        }
      }
      drawText(x, y, 1, out);
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
        case Menu::M_TIME:
          if (!isTimer)
          {
            tStop += 60000;
          }
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
              addValue(&cPage, (pCount) - 1);
              break;
            case 1:
              addValue(&p[cPage].counter1, 10);
              break;
            case 2:
              addValue(&p[cPage].counter2, 10);
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
        case Menu::M_TIME:
          if (!isTimer)
          {
            tStop -= 60000;
            if (tStop < 0)
            {
              tStop = 0;
            }
          }
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
              subValue(&p[cPage].counter1, 0);
              break;
            case 2:
              subValue(&p[cPage].counter2, 0);
              break;
          }
          break;
      }
    }

    virtual void leftButton()
    {
      if (menu->cursor == 0)
      {
        initMode(mode - 1);
        return;
      }
      rotateDown(&cursorC, 0, utilMenuMax[menu->cursor]);
    }

    virtual void rightButton()
    {
      if (menu->cursor == Menu::M_PLAYER)
      {
        initMode(mode + 1);
        return;
      }
      rotateUp(&cursorC, 0, utilMenuMax[menu->cursor]);
    }

    virtual void aButton()
    {
      cursorC = 0;
      hand = 7;
      discard = 1;
      dCount = 2;

      initArray(card, CARD_MAX);
      initArray(storm, STORM_MAX);
      initArray(d, DICE_ALL_MAX);

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
          isTimer = !isTimer;
          if (isTimer)
          {
            tStop += millis();
          }
          else
          {
            tStop -= millis();
          }
          break;
        case Menu::M_DISCARD:
          discardRoll();
          break;
      }
    }

    virtual void abButton()
    {
      switch (menu->cursor)
      {
        case Menu::M_TIME:
          isTimer = false;
          tStop = 0;
          break;
        case Menu::M_DISCARD:
          initArray(card, CARD_MAX);
          break;
        case Menu::M_STORM:
          initArray(storm, STORM_MAX);
          break;
        case Menu::M_DICE:
          initArray(d, DICE_ALL_MAX);
          break;
        case Menu::M_COUNT:
          initCounter();
          break;
      }
    }

  private:
    void DisplayUtil::discardRoll()
    {
      initArray(card, CARD_MAX);
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
      for (auto &dice : d)
      {
        dice = random(6) + 1;
      }
    }

    void DisplayUtil::dispCounter()
    {
      if (isCursor)
      {
        drawArrowLeft(x + ((cursorC == 0) ? 0 : x + 30 + ((cursorC - 1) * 49)), y, WHITE);
      }

      drawText(x + 9, y, 1, "P");
      drawText(x + 19, y, 1, cPage + 1);
      ab.drawLine(x + 29, y, x + 29, y + 6, WHITE);
      ab.drawLine(x + 78, y, x + 78, y + 6, WHITE);

      for (byte i = 0; i < p[cPage].counter1; i++)
      {
        byte drawX = x + 37 + (i * 4);
        byte drawY = y + 7;

        byte w = 2;
        byte h = (i == 4) ? 4 : (i == 9) ? 7 : 2;

        ab.fillRect(drawX, drawY - h, w, h, WHITE);
      }
      for (byte i = 0; i < p[cPage].counter2; i++)
      {
        byte drawX = x + 86 + (i * 4);
        byte drawY = y + 7;

        byte w = 2;
        byte h = (i == 4) ? 4 : (i == 9) ? 7 : 2;

        ab.fillRect(drawX, drawY - h, w, h, WHITE);
      }
    }

    void DisplayUtil::dispStorm()
    {
      ab.drawBitmap(x +   2, y - 1, i_s_storm, 9, 9, WHITE);
      ab.drawBitmap(x +  26, y - 1, i_s_white, 9, 9, WHITE);
      ab.drawBitmap(x +  43, y - 1, i_s_blue , 9, 9, WHITE);
      ab.drawBitmap(x +  60, y - 1, i_s_black, 9, 9, WHITE);
      ab.drawBitmap(x +  77, y - 1, i_s_red  , 9, 9, WHITE);
      ab.drawBitmap(x +  94, y - 1, i_s_green, 9, 9, WHITE);
      ab.drawBitmap(x + 111, y - 1, i_s_less , 9, 9, WHITE);

      drawText(x +  12, y, 1, storm[0]);
      for (byte i = 1; i < STORM_MAX; i++)
      {
        drawText(x + 18 + (i * 17), y, 1, storm[i]);
      }

      ab.drawRect(x + ((cursorC == 0) ? 0 : x + 6 + (cursorC * 17)), y, 2, 7, WHITE);
    }

    void DisplayUtil::dispDice()
    {
      byte dSum1 = 0;
      byte dSum2 = 0;
      drawArrowLeft(x, y, WHITE);
      drawText(x + 7, y, 1, dCount);
      drawText(x + 13, y, 1, "d6");
      ab.drawLine(x + 29, y, x + 29, y + 6, WHITE);
      ab.drawLine(x + 78, y, x + 78, y + 6, WHITE);
      for (byte i = 0; i < dCount; i++)
      {
        drawBigDice(x + 33 + (10 * i), y, d[i]);
        dSum1 += d[i];
      }
      drawText(x + 64, y, 1, dSum1);
      for (byte i = 0; i < dCount; i++)
      {
        drawBigDice(x + 82 + (10 * i), y, d[i + 4]);
        dSum2 += d[i + 4];
      }
      drawText(x + 113, y, 1, dSum2);
    }

    void DisplayUtil::dispDiscard()
    {
      drawArrowLeft(x + ((cursorC == 0) ? 0 : 27), y, WHITE);
      ab.drawBitmap(x +  5, y - 1, i_s_hand, 9, 9, WHITE);
      ab.drawBitmap(x + 31, y - 1, i_s_down, 9, 9, WHITE);
      drawText(x + 14, y, 1, hand);
      drawText(x + 40, y, 1, discard);
      ab.drawLine(x + 47, y, x + 47, y + 6, WHITE);
      for (byte i = 0; i < hand; i++)
      {
        ab.drawBitmap(x + 41 + (CARD_MAX - i) * 7, y - 1, (card[i] == 0) ? i_s_card : i_s_discard, 9, 9, WHITE);
      }
    }

    void DisplayUtil::dispTimer()
    {
      if (isCursor)
      {
        drawArrowLeft(x, y, WHITE);
      }

      ab.drawBitmap(x + 51, y - 1, (isTimer) ? i_s_play : i_s_stop, 9, 9, WHITE);
      byte w = 0;
      if (isTimer)
      {
        drawText(x + 6, y, 1, getHMS(tStop - millis()));
        w = getMinute(tStop - millis());
      }
      else
      {
        drawText(x + 6, y, 1, getHMS(tStop));
        w = getMinute(tStop);
      }
      ab.fillRect(x + 64, y, w > 60 ? 60 : w, 3, WHITE);
      ab.drawLine(x + 64, y + 6, x + 124, y + 6, WHITE);

      for (byte i = 0; i <= 60; i += 5)
      {
        byte hight = (i % 10 == 0) ? 2 : 1;
        byte lineX = x + 64 + i;
        byte lineY = y + 6;
        ab.drawLine(lineX, lineY - hight, lineX, lineY, WHITE);
      }
    }
};

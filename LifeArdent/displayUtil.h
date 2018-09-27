class DisplayUtil : public Form {
  private:
    const char HAND_MAX = 11;
    const char DISCARD_MAX = 9;
    const char STORM_MAX = 7;
  public:
    char hand = 7;
    char discard = 2;
    char card[11];
    char cursorC = 0;
    char storm[7];

    String stopTime = "0:00:00";

    bool isTimer = false;

    void DisplayUtil::initStorm()
    {
      for (int i = 0; i < STORM_MAX; i++)
      {
        storm[i] = 0;
      }
    }

    void DisplayUtil::initDiscard()
    {
      for (int i = 0; i < HAND_MAX; i++)
      {
        card[i] = 0;
      }
    }

    void DisplayUtil::discardRoll()
    {
      initDiscard();

      int dc = 0;
      while (dc < discard)
      {
        int r = random(hand);
        if (card[r] == 0)
        {
          card[r] = 1;
          dc++;
        }
      }
    }

    DisplayUtil()
    {
      x = 0;
      y = 53;
      isCursor = false;
      cursor = 0;
      cursorMax = 0;

      // 乱数生成
      Serial.begin(9600);
      randomSeed(analogRead(0));
      Serial.end();
    }

    void DisplayUtil::dispTimer()
    {
      if (isTimer)
      {
        setting->tTimer.setDefaultTime();
      }
      if (isCursor)
      {
        drawArrowLeft(ab, x + 1, y + 2, WHITE);
      }
      ab->drawBitmap(x + 52, y + 1, (isTimer) ? i_s_play : i_s_stop, 9, 9, WHITE);
      ab->drawBitmap(x + 65, y + 6, i_timer_meter, 61, 3, WHITE);
      drawText(ab, x + 7, y + 2, 1, (isTimer) ? setting->tTimer.getSubTimeString() : stopTime);
      ab->fillRect(x + 65, y + 2, setting->tTimer.m, 3, WHITE);
    }

    void DisplayUtil::display()
    {
      if (isCursor)
      {
        String out = "";
        short drawX = 0;
        short drawY = y + 2;
        switch (menu->cursor)
        {
          case M_PLAYER:
            out += setting->getModeName(setting->mode - 1);
            out += (setting->mode > PM_HEAD) ? " << " : "    ";
            out += setting->getModeName(setting->mode);
            out += (setting->mode < PM_TAIL) ? " >> " : "    ";
            out += setting->getModeName(setting->mode + 1);
            text(out);
            break;
          case M_DICE:
            text("Dice Roll, max 5D6.");
            break;
          case M_MATCH:
            text("Count Match win.");
            break;
          case M_TIME:
            dispTimer();
            break;
          case M_DISCARD:
            drawX = x + ((cursorC == 0) ? 1 : 28);
            drawArrowLeft(ab, drawX, drawY, WHITE);
            ab->drawBitmap(x +  6, drawY - 1, i_s_hand, 9, 9, WHITE);
            ab->drawBitmap(x + 32, drawY - 1, i_s_down, 9, 9, WHITE);
            drawText(ab, x + 15, drawY, 1, hand);
            drawText(ab, x + 41, drawY, 1, discard);
            ab->drawLine(x + 48, drawY, x + 48, drawY + 6, WHITE);
            for (int i = 0; i < hand; i++)
            {
              drawX = x + 42 + (HAND_MAX - i) * 7;
              ab->drawBitmap(drawX, drawY - 1, (card[i] == 0) ? i_s_card : i_s_discard, 9, 9, WHITE);
            }
            break;
          case M_STORM:
            ab->drawBitmap(x +   3, drawY - 1, i_s_storm, 9, 9, WHITE);
            ab->drawBitmap(x +  27, drawY - 1, i_s_white, 9, 9, WHITE);
            ab->drawBitmap(x +  44, drawY - 1, i_s_blue , 9, 9, WHITE);
            ab->drawBitmap(x +  61, drawY - 1, i_s_black, 9, 9, WHITE);
            ab->drawBitmap(x +  78, drawY - 1, i_s_red  , 9, 9, WHITE);
            ab->drawBitmap(x +  95, drawY - 1, i_s_green, 9, 9, WHITE);
            ab->drawBitmap(x + 112, drawY - 1, i_s_less , 9, 9, WHITE);

            drawText(ab, x +  13, drawY, 1, storm[0]);
            for (int i = 1; i < STORM_MAX; i++)
            {
              drawText(ab, x + 19 + (i * 17), drawY, 1, storm[i]);
            }
            
            drawX = (cursorC == 0) ? 1 : x + 8 + (cursorC * 17);
            ab->drawRect(drawX, drawY, 2, 7, WHITE);

            break;
          case M_COUNT:
            text("Count Poison,Energy.");
            break;
          case M_SOUND:
            activeMenu();
            break;
          case M_SETTING:
            text("Life Ardent Settings.");
            break;
        }
      }
      else if (menu->isCursor)
      {
        switch (menu->cursor)
        {
          case M_PLAYER:
            text("Select Format.");
            break;
          case M_DICE:
            text("Dice Roll, max 5D6.");
            break;
          case M_MATCH:
            text("Count Match win.");
            break;
          case M_TIME:
            if (isTimer)
            {
              dispTimer();
            }
            else
            {
              text("50 min stopwatch.");
            }
            break;
          case M_DISCARD:
            text("Choose Random Discard.");
            break;
          case M_STORM:
            text("Count Storm & mana.");
            break;
          case M_COUNT:
            text("Count Poison,Energy.");
            break;
          case M_SOUND:
            if (setting->isSound)
            {
              text("Set Sound. [ ON ]");
            }
            else
            {
              text("Set Sound. [MUTE]");
            }
            break;
          case M_SETTING:
            text("Life Ardent Settings.");
            break;
        }
      }
      else if (life->isCursor)
      {
        switch (menu->cursor)
        {
          case M_PLAYER:
            break;
          case M_DICE:
            break;
          case M_MATCH:
            break;
          case M_TIME:
            if (isTimer)
            {
              dispTimer();
            }
            break;
          case M_DISCARD:
            break;
          case M_STORM:
            break;
          case M_COUNT:
            break;
          case M_SOUND:
            break;
          case M_SETTING:
            break;
        }
      }
    }

    virtual void upButton()
    {
      switch (menu->cursor)
      {
        case M_PLAYER:
          break;
        case M_DICE:
          break;
        case M_MATCH:
          break;
        case M_TIME:
          break;
        case M_DISCARD:
          switch (cursorC)
          {
            case 0:
              if (hand < HAND_MAX)
              {
                hand++;
              }
              break;
            case 1:
              if (discard < hand && discard < DISCARD_MAX)
              {
                discard++;
              }
              break;
          }
          break;
        case M_STORM:
          if (cursorC == 0)
          {
            if (storm[cursorC] < 99)
            {
              storm[cursorC]++;
            }
          }
          else
          {
            if (storm[cursorC] < 9)
            {
              storm[cursorC]++;
            }
          }
          break;
        case M_COUNT:
          break;
        case M_SOUND:
          break;
        case M_SETTING:
          break;
      }
    }

    virtual void downButton()
    {
      switch (menu->cursor)
      {
        case M_PLAYER:
          break;
        case M_DICE:
          break;
        case M_MATCH:
          break;
        case M_TIME:
          break;
        case M_DISCARD:
          switch (cursorC)
          {
            case 0:
              if (hand > 1)
              {
                hand--;
                if (hand < discard)
                {
                  discard = hand;
                }
              }
              break;
            case 1:
              if (discard > 1)
              {
                discard--;
              }
              break;
          }
          break;
        case M_STORM:
          if (storm[cursorC] > 0)
          {
            storm[cursorC]--;
          }
          break;
        case M_COUNT:
          break;
        case M_SOUND:
          break;
        case M_SETTING:
          break;
      }
    }

    virtual void leftButton()
    {
      short max = 0;
      switch (menu->cursor)
      {
        case M_PLAYER:
          setting->initMode(setting->mode - 1);
          return;
        case M_SOUND:
        case M_SETTING:
          return;
        case M_DICE:
          max = UtilMenuMax::MAX_DICE;
          break;
        case M_MATCH:
          max = UtilMenuMax::MAX_MATCH;
          break;
        case M_TIME:
          max = UtilMenuMax::MAX_TIME;
          break;
        case M_DISCARD:
          max = UtilMenuMax::MAX_DISCARD;
          break;
        case M_STORM:
          max = UtilMenuMax::MAX_STORM;
          break;
        case M_COUNT:
          max = UtilMenuMax::MAX_COUNT;
          break;
      }

      cursorC--;
      if (cursorC < 0)
      {
        cursorC = max - 1;
      }
    }

    virtual void rightButton()
    {
      short max = 0;
      switch (menu->cursor)
      {
        case M_PLAYER:
          setting->initMode(setting->mode + 1);
          return;
        case M_SOUND:
        case M_SETTING:
          return;
        case M_DICE:
          max = UtilMenuMax::MAX_DICE;
          break;
        case M_MATCH:
          max = UtilMenuMax::MAX_MATCH;
          break;
        case M_TIME:
          max = UtilMenuMax::MAX_TIME;
          break;
        case M_DISCARD:
          max = UtilMenuMax::MAX_DISCARD;
          break;
        case M_STORM:
          max = UtilMenuMax::MAX_STORM;
          break;
        case M_COUNT:
          max = UtilMenuMax::MAX_COUNT;
          break;
      }

      cursorC++;
      if (cursorC >= max)
      {
        cursorC = 0;
      }
    }

    virtual void aButton()
    {
      cursorC = 0;

      hand = 7;
      discard = 1;
      initDiscard();
      initStorm();

      activeMenu();
    }

    virtual void bButton()
    {
      switch (menu->cursor)
      {
        case M_PLAYER:
          activeMenu();
          break;
        case M_DICE:
          break;
        case M_MATCH:
          break;
        case M_TIME:
          isTimer = !isTimer;
          if (isTimer)
          {
            setting->tTimer.setStopTime();
            setting->tTimer.addHour(-setting->tTimer.h);
            setting->tTimer.addMinute(-setting->tTimer.m);
            setting->tTimer.addSecond(-setting->tTimer.s);
          }
          else
          {
            stopTime = setting->tTimer.getSubTimeString();
          }
          break;
        case M_DISCARD:
          discardRoll();
          break;
        case M_STORM:
          break;
        case M_COUNT:
          break;
        case M_SOUND:
          break;
        case M_SETTING:
          break;
      }
    }

    virtual void abButton()
    {
      switch (menu->cursor)
      {
        case M_PLAYER:
          break;
        case M_DICE:
          break;
        case M_MATCH:
          break;
        case M_TIME:
          isTimer = false;
          stopTime = "0:00:00";
          break;
        case M_DISCARD:
          initDiscard();
          break;
        case M_STORM:
          initStorm();
          break;
        case M_COUNT:
          break;
        case M_SOUND:
          break;
        case M_SETTING:
          break;
      }
    }

  private:
    void DisplayUtil::text(String text)
    {
      drawText(ab, x + 1, y + 2, 1, text);
    }
};


class DisplayUtil : public Form {
  private:
    int HAND_MAX = 11;
    int DISCARD_MAX = 9;
  public:
    int hand = 7;
    int discard = 2;
    int card[11];
    int cursorC = 0;

    void DisplayUtil::discardRoll()
    {
      for (int i = 0; i < HAND_MAX; i++)
      {
        card[i] = 0;
      }

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

    void DisplayUtil::display()
    {
      if (isCursor)
      {
        String out = "";
        int drawX = 0;
        int drawY = 0;
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
            text("50 min stopwatch.");
            break;
          case M_DISCARD:
            drawY = y + 2;
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
              char* image = (card[i] == 0) ? i_s_card : i_s_discard;
              ab->drawBitmap(drawX, drawY - 1, image, 9, 9, WHITE);
            }
            break;
          case M_STORM:
            text("Count Storm & mana.");
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
            text("50 min stopwatch.");
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
      int max = 0;
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
      int max = 0;
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
      hand = 7;
      discard = 1;
      cursorC = 0;

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
    }

  private:
    void DisplayUtil::text(String text)
    {
      drawText(ab, x + 1, y + 2, 1, text);
    }
};


class DisplayMenu : public Form {
  private:
    char* image;
    const char imageSizeX = 11;
    const char imageSizeY = 14;
  public:
    short LIFE_RESET_SECOND = 5000;

    DisplayMenu()
    {
      x = 0;
      y = 0;
      isCursor = false;
      cursor = M_HEAD;
      cursorMax = M_TAIL;
    }

    void DisplayMenu::display()
    {
      setImage();

      ab->drawBitmap(x, y, f_menu, 29, 53, WHITE);

      if (setting->changeLife == 0)
      {
        ab->drawBitmap(x + 9, y + 19, image, imageSizeX, imageSizeY, WHITE);
      }
      else
      {
        dispChangeLife();
      }

      if (isCursor)
      {
        ab->drawRect(x + 2, y + 13, 25, 27, WHITE);
        ab->drawBitmap(x + 9, x + 2, i_arrow_up, 11, 7, WHITE);
        ab->drawBitmap(x + 9, x + 44, i_arrow_down, 11, 7, WHITE);
      }
    }

    void DisplayMenu::setCursor(int value)
    {
      cursor += value;
      if (cursor < M_HEAD)
      {
        cursor = M_TAIL;
      }
      else if (cursor > M_TAIL)
      {
        cursor = M_HEAD;
      }
    }

    void dispChangeLife()
    {
      if (abs(setting->tPressed.getSubMillisecond()) >= LIFE_RESET_SECOND)
      {
        setting->changeLife = 0;
      }

      short life = setting->changeLife;
      
      if (life == 0)
      {
        return;
      }

      short addX = (life >= 100 || life <= -100) ? 3 : (life >= 10 || life <= -10) ? 6 : 11;
      short addY = 23;
      String txt = (life > 0) ? "+" + String(life) : life;

      drawText(ab, x + addX, y + addY, 1, txt);
    }

    virtual void upButton()
    {
      setCursor(-1);
    }

    virtual void downButton()
    {
      setCursor(+1);
    }

    virtual void leftButton()
    {
      life->cursor = life->setting->pCount - 1;
      activeLife();
    }

    virtual void rightButton()
    {
      life->cursor = PM_HEAD;
      activeLife();
    }

    virtual void aButton()
    {
      switch (cursor)
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
          break;
        case M_STORM:
          break;
        case M_COUNT:
          break;
        case M_SOUND:
          setting->isSound = !setting->isSound;
          break;
        case M_SETTING:
          break;
      }
    }

    virtual void bButton()
    {
      switch (cursor) {
        case M_PLAYER:
        case M_DICE:
        case M_MATCH:
        case M_TIME:
        case M_DISCARD:
        case M_STORM:
        case M_COUNT:
          activeUtil();
          break;
        case M_SOUND:
          setting->isSound = !setting->isSound;
          break;
        case M_SETTING:
          break;
      }
    }

    virtual void abButton()
    {
    }

  private:
    void DisplayMenu::setImage()
    {
      switch (cursor) {
        case M_PLAYER:
          image = i_player;
          break;
        case M_DICE:
          image = i_dice;
          break;
        case M_MATCH:
          image = i_match;
          break;
        case M_TIME:
          image = i_timer;
          break;
        case M_DISCARD:
          image = i_discard;
          break;
        case M_STORM:
          image = i_storm;
          break;
        case M_COUNT:
          image = i_poison;
          break;
        case M_SOUND:
          image =  (setting->isSound) ? i_sound_on : i_sound_mute;
          break;
        case M_SETTING:
          image = i_setting;
          break;
      }
    }
};


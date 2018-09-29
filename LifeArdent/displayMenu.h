class DisplayMenu : public Form {
  private:
    char* image;
#define imageSizeX 11
#define imageSizeY 14
#define LIFE_RESET_SECOND 5000
  public:
    DisplayMenu()
    {
      x = 0;
      y = 0;
      isCursor = false;
      cursor = Menu::M_HEAD;
      cursorMax = M_TAIL;
    }

    void DisplayMenu::display()
    {
      setImage();

      ab->drawBitmap(x, y, f_menu, 29, 53, WHITE);

      if (format->changeLife == 0)
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

    virtual void upButton()
    {
      subValue(&cursor, Menu::M_HEAD);
    }

    virtual void downButton()
    {
      addValue(&cursor, Menu::M_TAIL);
    }

    virtual void leftButton()
    {
      life->cursor = life->format->pCount - 1;
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
        case Menu::M_PLAYER:
        case Menu::M_DICE:
        case Menu::M_MATCH:
        case Menu::M_TIME:
        case Menu::M_DISCARD:
        case Menu::M_STORM:
        case Menu::M_COUNT:
          break;
        case Menu::M_SOUND:
          format->isSound = !format->isSound;
          break;
        case Menu::M_SETTING:
          break;
      }
    }

    virtual void bButton()
    {
      switch (cursor) {
        case Menu::M_PLAYER:
        case Menu::M_DICE:
        case Menu::M_MATCH:
        case Menu::M_TIME:
        case Menu::M_DISCARD:
        case Menu::M_STORM:
        case Menu::M_COUNT:
          activeUtil();
          break;
        case Menu::M_SOUND:
          format->isSound = !format->isSound;
          break;
        case Menu::M_SETTING:
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
        case Menu::M_PLAYER:
          image = i_player;
          break;
        case Menu::M_DICE:
          image = i_dice;
          break;
        case Menu::M_MATCH:
          image = i_match;
          break;
        case Menu::M_TIME:
          image = i_timer;
          break;
        case Menu::M_DISCARD:
          image = i_discard;
          break;
        case Menu::M_STORM:
          image = i_storm;
          break;
        case Menu::M_COUNT:
          image = i_poison;
          break;
        case Menu::M_SOUND:
          image =  (format->isSound) ? i_sound_on : i_sound_mute;
          break;
        case Menu::M_SETTING:
          image = i_setting;
          break;
      }
    }

    void dispChangeLife()
    {
      if (abs(format->tPressed.getSubMillisecond()) >= LIFE_RESET_SECOND)
      {
        format->changeLife = 0;
      }

      short life = format->changeLife;

      if (life == 0)
      {
        return;
      }

      byte addX = (life >= 100 || life <= -100) ? 3 : (life >= 10 || life <= -10) ? 6 : 11;
      byte addY = 23;
      String txt = (life > 0) ? "+" + String(life) : life;

      drawText(ab, x + addX, y + addY, 1, txt);
    }

};


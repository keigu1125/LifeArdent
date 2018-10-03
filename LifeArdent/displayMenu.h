class DisplayMenu : public Form
{
  private:
    char* image;
  public:
    DisplayMenu()
    {
      // x = 0;
      // y = 0;
      // isCursor = false;
      // cursor = Menu::M_HEAD;
      cursorMax = M_TAIL;
    }

    void DisplayMenu::display()
    {
      setImage();

      ab.drawRect(x, y, 30, 10, WHITE);
      ab.drawRect(x, y + 43, 30, 10, WHITE);
      ab.drawRect(x + 2, y + 12, 27, 29, WHITE);

      if (changeLife == 0)
      {
        ab.drawBitmap(x + 10, y + 19, image, imageSizeX, imageSizeY, WHITE);
      }
      else
      {
        dispChangeLife();
      }

      if (isCursor)
      {
        ab.drawRect(x + 3, y + 13, 25, 27, WHITE);
        ab.drawBitmap(x + 10, y + 1, i_arrow_up, 11, 7, WHITE);
        ab.drawBitmap(x + 10, y + 45, i_arrow_down, 11, 7, WHITE);
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
      life->cursor = pCount - 1;
      activeLife();
    }

    virtual void rightButton()
    {
      life->cursor = PM_HEAD;
      activeLife();
    }

    virtual void aButton()
    {
      if (cursor == Menu::M_SOUND)
      {
        isSound = !isSound;
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
          isSound = !isSound;
          break;
        case Menu::M_SETTING:
          activeSetting();
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
          image =  (isSound) ? i_sound_on : i_sound_mute;
          break;
        case Menu::M_SETTING:
          image = i_setting;
          break;
      }
    }

    void dispChangeLife()
    {
      if (tPressed.getSecond() >= LIFE_RESET_SECOND)
      {
        changeLife = 0;
      }

      int life = changeLife;

      if (life == 0)
      {
        return;
      }

      byte addX = (life >= 100 || life <= -100) ? 4 : (life >= 10 || life <= -10) ? 7 : 10;
      byte addY = 23;
      drawText(x + addX, y + addY, 1, (life > 0) ? "+" + String(life) : life);
    }

};

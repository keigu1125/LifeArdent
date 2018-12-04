class DisplayMenu : public Form
{
  private:
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
      ab.drawRect(x    , y     , 30, 10, WHITE);
      ab.drawRect(x    , y + 43, 30, 10, WHITE);
      ab.drawRect(x + 2, y + 12, 27, 29, WHITE);

      if (isCursor)
      {
        ab.drawRect(x + 3, y + 13, 25, 27, WHITE);
        ab.drawBitmap(x + 10, y + 1, i_arrow_up, 11, 7, WHITE);
        ab.drawBitmap(x + 10, y + 45, i_arrow_down, 11, 7, WHITE);
      }

      if (changeLife == 0)
      {
        ab.drawBitmap(x + 10, y + 19, setImage(), MENU_ICON_SIZE_X, MENU_ICON_SIZE_Y, WHITE);
      }
      else
      {
        dispChangeLife();
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
      switch (cursor)
      {
        case Menu::M_PLAYER:
          setting.invertOpponent = !setting.invertOpponent;
          break;
        case Menu::M_SOUND:
          isSound = !isSound;
          break;
      }
    }

    virtual void bButton()
    {
      switch (cursor) {
        case Menu::M_PLAYER:
        case Menu::M_DICE:
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

    virtual void abButton() {}

  private:
    char* DisplayMenu::setImage()
    {
      switch (cursor) {
        case Menu::M_PLAYER:
          return i_player;
        case Menu::M_DICE:
          return i_dice;
        case Menu::M_TIME:
          return i_timer;
        case Menu::M_DISCARD:
          return i_discard;
        case Menu::M_STORM:
          return i_storm;
        case Menu::M_COUNT:
          return i_poison;
        case Menu::M_SOUND:
          return  (isSound) ? i_sound_on : i_sound_mute;
        case Menu::M_SETTING:
          return i_setting;
      }
    }

    void dispChangeLife()
    {
      if (tPressed == 0)
      {
        changeLife = 0;
      }

      if (changeLife == 0)
      {
        return;
      }

      byte addX = (changeLife >= 100 || changeLife <= -100) ? 4 : (changeLife >= 10 || changeLife <= -10) ? 7 : 10;
      byte addY = 23;
      drawText(x + addX, y + addY, 1, (changeLife > 0) ? "+" + String(changeLife) : changeLife);
    }

};

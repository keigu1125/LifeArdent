class DisplayMenu : public Form {
  public:
    Form* util;
    Form* life;

    int cursorM = M_HEAD;
    int LIFE_RESET_SECOND = 5;
    int changeLife = 0;
    Time tPressed;
    boolean isCursor = true;
    boolean isSound = true;

    DisplayMenu()
    {
      x = 0;
      y = 0;
      isCursor = false;
    }

    void DisplayMenu::display() {
      setImage();

      ab->drawBitmap(x, y, f_menu, 29, 52, WHITE);

      if (changeLife == 0)
      {
        ab->drawBitmap(x + 9, y + 19, image, imageSizeX, imageSizeY, WHITE);
      }
      else
      {
        dispChangeLife();
      }

      if (isCursor) {
        ab->drawRect(x + 2, y + 13, 25, 26, WHITE);
        ab->drawBitmap(x + 9, x + 2, i_arrow_up, 11, 7, WHITE);
        ab->drawBitmap(x + 9, x + 43, i_arrow_down, 11, 7, WHITE);
      }
    }

    void DisplayMenu::setCursor(int value) {
      cursorM += value;
      if (cursorM < M_HEAD)
      {
        cursorM = M_TAIL;
      }
      else if (cursorM > M_TAIL)
      {
        cursorM = M_HEAD;
      }
    }

    void dispChangeLife()
    {
      if (abs(tPressed.getSubSecond()) >= LIFE_RESET_SECOND)
      {
        changeLife = 0;
      }

      if (changeLife == 0)
      {
        return;
      }

      int addX = (changeLife >= 100 || changeLife <= -100) ? 3 : (changeLife >= 10 || changeLife <= -10) ? 6 : 10;
      int addY = 22;
      String txt = (changeLife > 0) ? "+" + String(changeLife) : changeLife;

      drawText(ab, x + addX, y + addY, 1, txt);
    }

  private:
    char* image;
    int imageSizeX = 11;
    int imageSizeY = 14;

    void DisplayMenu::setImage() {
      switch (cursorM) {
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
          image =  (isSound) ? i_sound_on : i_sound_mute;
          break;
        case M_SETTING:
          image = i_setting;
          break;
      }
    }
};


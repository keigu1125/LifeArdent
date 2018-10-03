class DisplaySetting : public Form
{
  private:
    const byte HIGHT = 8;
    const byte IND   = 12;
  public:
    byte cursorC = 0x00;
    byte cursorCMax = 0x00;

    DisplaySetting()
    {
      // x = 0;
      // y = 0;
      // isCursor = false;
      // cursor = Menu::M_HEAD;
      cursorMax = M_TAIL;
    }


    void DisplaySetting::display()
    {
      displayHead();
      displayDetail();
      drawCursor();
    }

    virtual void upButton()
    {
      subValue(&cursorC, 0);
    }

    virtual void downButton()
    {
      addValue(&cursorC, cursorCMax);
    }

    virtual void leftButton()
    {
      if (cursorC == 0)
      {
        subValue(&cursor, SMT_HEAD);
        return;
      }

      switch (cursor)
      {
        case SMT_GAME:
          subValue(&setting.defaultFormat, PM_HEAD);
          break;
        case SMT_TITLE:
          subValue(&setting.showTitle, 0x00);
          break;
        case SMT_SOUND:
          switch (cursorC)
          {
            case 1:
              subValue(&setting.isSoundDefault, 0x00);
              break;
            case 2:
              if (setting.baseTone > 100)
              {
                setting.baseTone -= 10;
              }
              break;
            case 3:
              subValue(&setting.isSoundTimer, 0x00);
              break;
          }
          break;
        case SMT_DISPLAY:
          subValue(&setting.blackScreen, 0x00);
          break;
        case SMT_LED:
          subValue(&setting.isLedTimer, 0x00);
          break;
        case SMT_FRAME:
          subValue(&setting.frameRateMain, 1);
          ab.setFrameRate(setting.frameRateMain);
          break;
        case SMT_EXIT:
          break;
      }
    }

    virtual void rightButton()
    {
      if (cursorC == 0)
      {
        addValue(&cursor, SMT_TAIL);
        return;
      }

      switch (cursor)
      {
        case SMT_GAME:
          addValue(&setting.defaultFormat, PM_TAIL);
          break;
        case SMT_TITLE:
          addValue(&setting.showTitle, 0x01);
          break;
        case SMT_SOUND:
          switch (cursorC)
          {
            case 1:
              addValue(&setting.isSoundDefault, 0x01);
              break;
            case 2:
              if (setting.baseTone < 6000)
              {
                setting.baseTone += 10;
              }
              break;
            case 3:
              addValue(&setting.isSoundTimer, 0x01);
              break;
          }
          break;
        case SMT_DISPLAY:
          addValue(&setting.blackScreen, 0x01);
          break;
        case SMT_LED:
          addValue(&setting.isLedTimer, 0x01);
          break;
        case SMT_FRAME:
          addValue(&setting.frameRateMain, 60);
          ab.setFrameRate(setting.frameRateMain);
          break;
        case SMT_EXIT:
          break;
      }

    }

    virtual void aButton()
    {

    }

    virtual void bButton()
    {
      if (cursor != SMT_EXIT)
      {
        return;
      }

      switch (cursorC)
      {
        case 1:
          setting.isWritedSetting = 0x01;
          setting.writeEepRomSetting();
          break;
        case 2:
          activeMenu();
          return;
        case 3:
          setting.isWritedSetting = 0x00;
          setting.writeEepRomSetting();
          break;
      }

      delay(1000);
      asm volatile ("   jmp 0");
    }

    virtual void abButton()
    {

    }

  private:

    String getMenuTitle(byte c)
    {
      switch (c)
      {
        case SMT_GAME:
          return "GAME ";
        case SMT_TITLE:
          return "TITLE";
        case SMT_SOUND:
          return "SOUND";
        case SMT_DISPLAY:
          return "DISP ";
        case SMT_LED:
          return "LED  ";
        case SMT_FRAME:
          return "FRAME";
        case SMT_EXIT:
          return "EXIT ";
      }
    }

    void DisplaySetting::displayHead()
    {
      ab.drawLine(0, 10, 128, 10, WHITE);

      byte drawX = 0;
      for (byte i = SMT_HEAD; i <= SMT_TAIL; i++)
      {
        if (i != cursor)
        {
          ab.drawRect(drawX, 2, 10, 6, WHITE);
          drawX += 13;
        }
        else
        {
          ab.drawRect(drawX, 0, 39, 11, WHITE);
          if (cursorC == 0)
          {
            drawArrowLeft(drawX + 3, 2, WHITE);
          }
          drawText(drawX + 8, 2, 1, getMenuTitle(i));
          drawX += 42;
        }
      }
    }

    void DisplaySetting::displayDetail()
    {
      byte row = 0;
      byte drawX = 7;
      byte drawY = 13;
      switch (cursor)
      {
        case SMT_GAME:
          drawText(drawX, drawY + (row++ * HIGHT), 1, "Default Format");
          drawText(drawX + IND, drawY + (row++ * HIGHT) + 1, 1, getModeName(setting.defaultFormat));
          cursorCMax = 1;
          break;
        case SMT_TITLE:
          drawText(drawX, drawY + (row++ * HIGHT), 1, "Show Title");
          drawText(drawX + IND, drawY + (row++ * HIGHT) + 1, 1, getOnOff(setting.showTitle));
          cursorCMax = 1;
          break;
        case SMT_SOUND:
          drawText(drawX, drawY + (row++ * HIGHT), 1, "Sounds Default");
          drawText(drawX + IND, drawY + (row++ * HIGHT) + 1, 1, getOnOff(setting.isSoundDefault));
          drawText(drawX, drawY + (row++ * HIGHT), 1, "Base Tone");
          drawText(drawX + IND, drawY + (row++ * HIGHT) + 1, 1, String(setting.baseTone) + " Hz");
          drawText(drawX, drawY + (row++ * HIGHT), 1, "Alarm");
          drawText(drawX + IND, drawY + (row++ * HIGHT) + 1, 1, getOnOff(setting.isSoundTimer));
          cursorCMax = 3;
          break;
        case SMT_DISPLAY:
          drawText(drawX, drawY + (row++ * HIGHT), 1, "Screen Color");
          drawText(drawX + IND, drawY + (row++ * HIGHT) + 1, 1, getBlackWhite(setting.blackScreen));
          row++;
          cursorCMax = 1;
          break;
        case SMT_LED:
          drawText(drawX, drawY + (row++ * HIGHT), 1, "Timer LED");
          drawText(drawX + IND, drawY + (row++ * HIGHT) + 1, 1, getOnOff(setting.isLedTimer));
          cursorCMax = 1;
          break;
        case SMT_FRAME:
          drawText(drawX, drawY + (row++ * HIGHT), 1, "Main Frame Rate");
          drawText(drawX + IND, drawY + (row++ * HIGHT) + 1, 1, String(setting.frameRateMain) + " fps");
          cursorCMax = 1;
          break;
        case SMT_EXIT:
          drawText(drawX, drawY + (row++ * HIGHT), 1, "Save, and Reboot");
          row++;
          drawText(drawX, drawY + (row++ * HIGHT), 1, "Not Save, Return");
          row++;
          drawText(drawX, drawY + (row++ * HIGHT), 1, "Erase Save, Reboot");
          row++;
          cursorCMax = 3;
          break;
      }
    }

    void DisplaySetting::drawCursor()
    {
      if (cursorC == 0)
      {
        return;
      }

      drawArrowLeft(1, 13 + ((cursorC - 1) * HIGHT * 2), WHITE);
    }

};

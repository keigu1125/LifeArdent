class DisplaySetting : public Form
{
#define DEF_IS_WRITE_SETTING  0x00
#define DEF_SHOW_TITLE        0x00
#define DEF_IS_SOUND_DEFAULT  0x01
#define DEF_IS_SOUND_TIMER    0x01
#define DEF_BASE_TONE_1       864
#define DEF_BASE_TONE_2       1296
#define DEF_IS_LED_TIMER      0x01
#define DEF_DEFAULT_FORMAT    0x01
#define DEF_FRAME_RATE_MAIN   20
#define DEF_FRAME_RATE_REPEAT 20
#define DEF_BLACK_SCREEN      0x00

  public:
    byte isWritedSetting = 0x00;
    byte showTitle = 0x00;
    byte isSoundDefault = 0x00;
    byte isSoundTimer = 0x00;
    short baseTone1 = 0;
    short baseTone2 = 0;
    byte isLedTimer = 0x00;
    byte defaultFormat = 0x00;
    byte frameRateMain = 0x00;
    byte frameRateRepeat = 0x00;
    byte blackScreen = 0x00;

    byte cursorC = 0x00;

    DisplaySetting()
    {
      // x = 0;
      // y = 0;
      // isCursor = false;
      // cursor = Menu::M_HEAD;
      cursorMax = M_TAIL;

      readEepRomSetting();
    }

    void DisplaySetting::display()
    {
      ab->drawLine(0, 12, 128, 12, WHITE);

      byte drawX = 2;
      for (byte i = SMT_HEAD; i <= SMT_TAIL; i++)
      {
        if (i != cursor)
        {
          ab->drawRect(drawX, 3, 13, 6, WHITE);
          drawX += 15;
        }
        else
        {
          ab->drawRect(drawX, 0, 34, 12, WHITE);
          ab->drawLine(drawX, 12, drawX + 34, 12, BLACK);
          drawText(ab, drawX + 3, 3, 1, getMenuTitle(i));
          drawX += 36;
        }
      }

      drawText(ab, 13, 13, 1, "default format");
    }

    virtual void upButton()
    {

    }

    virtual void downButton()
    {

    }

    virtual void leftButton()
    {
      if (cursorC == 0)
      {
        subValue(&cursor, SMT_HEAD);
      }
    }

    virtual void rightButton()
    {
      if (cursorC == 0)
      {
        addValue(&cursor, SMT_TAIL);
      }
    }

    virtual void aButton()
    {

    }

    virtual void bButton()
    {

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

    void readEepRomSetting()
    {
      byte point = 16;
      //isWritedSetting = EEPROM.read(point++);
      if (isWritedSetting == 0x00)
      {
        setDefaultSetting();
        return;
      }

      showTitle = EEPROM.read(point++);
      isSoundDefault = EEPROM.read(point++);
      isSoundTimer = EEPROM.read(point++);
      baseTone1 = (EEPROM.read(point++) << 8) | EEPROM.read(point++);
      baseTone2 = (EEPROM.read(point++) << 8) | EEPROM.read(point++);
      isLedTimer = EEPROM.read(point++);
      defaultFormat = EEPROM.read(point++);
      frameRateMain = EEPROM.read(point++);
      frameRateRepeat = EEPROM.read(point++);
      blackScreen = EEPROM.read(point++);
    }

    void writeEepRomSetting()
    {
      // *** !! BE CAREFUL !! *** //
      byte point = 16;
      EEPROM.write(point++, isWritedSetting);
      EEPROM.write(point++, showTitle);
      EEPROM.write(point++, isSoundDefault);
      EEPROM.write(point++, isSoundTimer);
      EEPROM.write(point++, ((baseTone1 >> 8) & 0xFF));
      EEPROM.write(point++, (baseTone1 & 0xFF));
      EEPROM.write(point++, ((baseTone2 >> 8) & 0xFF));
      EEPROM.write(point++, (baseTone2 & 0xFF));
      EEPROM.write(point++, isLedTimer);
      EEPROM.write(point++, defaultFormat);
      EEPROM.write(point++, frameRateMain);
      EEPROM.write(point++, frameRateRepeat);
      EEPROM.write(point++, blackScreen);
    }

    void setDefaultSetting()
    {
      isWritedSetting = DEF_IS_WRITE_SETTING;
      showTitle = DEF_SHOW_TITLE;
      isSoundDefault = DEF_IS_SOUND_DEFAULT;
      isSoundTimer = DEF_IS_SOUND_TIMER;
      baseTone1 = DEF_BASE_TONE_1;
      baseTone2 = DEF_BASE_TONE_2;
      isLedTimer = DEF_IS_LED_TIMER;
      defaultFormat = DEF_DEFAULT_FORMAT;
      frameRateMain = DEF_FRAME_RATE_MAIN;
      frameRateRepeat = DEF_FRAME_RATE_REPEAT;
      blackScreen = DEF_BLACK_SCREEN;
    }

};

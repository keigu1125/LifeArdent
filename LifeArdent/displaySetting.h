class DisplaySetting : public Form
{
#define DEF_IS_WRITE_SETTING    0x00
#define DEF_SHOW_TITLE          0x01
#define DEF_IS_DEFAULT_SOUND_ON 0x01
#define DEF_BASE_TONE_1         432
#define DEF_BASE_TONE_2         864
#define DEF_IS_LED_TIMER        0x01
#define DEF_IS_LED_STORM        0x01
#define DEF_DEFAULT_FORMAT      0x01
#define DEF_FRAME_RATE_MAIN     20
#define DEF_FRAME_RATE_REPEAT   20
#define DEF_BLACK_SCREEN        0x01

  public:
    byte isWritedSetting = 0x00;
    byte showTitle = 0x00;
    byte isDefaultSoundOn = 0x00;
    short baseTone1 = 0;
    short baseTone2 = 0;
    byte isLedTimer = 0x00;
    byte isLedStorm = 0x00;
    byte defaultFormat = 0x00;
    byte frameRateMain = 0x00;
    byte frameRateRepeat = 0x00;
    byte blackScreen = 0x00;

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

    }

    virtual void upButton()
    {

    }

    virtual void downButton()
    {

    }

    virtual void leftButton()
    {

    }

    virtual void rightButton()
    {

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
    void readEepRomSetting()
    {
      byte point = 16;
      isWritedSetting = EEPROM.read(point++);
      if (isWritedSetting == 0x00)
      {
        setDefaultSetting();
        return;
      }

      showTitle = EEPROM.read(point++);
      isDefaultSoundOn = EEPROM.read(point++);
      baseTone1 = (EEPROM.read(point++) << 8) | EEPROM.read(point++);
      baseTone2 = (EEPROM.read(point++) << 8) | EEPROM.read(point++);
      isLedTimer = EEPROM.read(point++);
      isLedStorm = EEPROM.read(point++);
      defaultFormat = EEPROM.read(point++);
      frameRateMain = EEPROM.read(point++);
      frameRateRepeat = EEPROM.read(point++);
      blackScreen = EEPROM.read(point++);
    }

    void writeEepRomSetting()
    {
      // *** !! BE CAREFUL !! *** //
      byte point = 16;
      EEPROM.write(point++, (isWritedSetting & 0xFF));
      EEPROM.write(point++, (showTitle & 0xFF));
      EEPROM.write(point++, (isDefaultSoundOn & 0xFF));
      EEPROM.write(point++, ((baseTone1 >> 8) & 0xFF));
      EEPROM.write(point++, (baseTone1 & 0xFF));
      EEPROM.write(point++, ((baseTone2 >> 8) & 0xFF));
      EEPROM.write(point++, (baseTone2 & 0xFF));
      EEPROM.write(point++, (isLedTimer & 0xFF));
      EEPROM.write(point++, (isLedStorm & 0xFF));
      EEPROM.write(point++, (defaultFormat & 0xFF));
      EEPROM.write(point++, (frameRateMain & 0xFF));
      EEPROM.write(point++, (frameRateRepeat & 0xFF));
      EEPROM.write(point++, (blackScreen & 0xFF));
    }

    void setDefaultSetting()
    {
      isWritedSetting = DEF_IS_WRITE_SETTING;
      showTitle = DEF_SHOW_TITLE;
      isDefaultSoundOn = DEF_IS_DEFAULT_SOUND_ON;
      baseTone1 = DEF_BASE_TONE_1;
      baseTone2 = DEF_BASE_TONE_2;
      isLedTimer = DEF_IS_LED_TIMER;
      isLedStorm = DEF_IS_LED_STORM;
      defaultFormat = DEF_DEFAULT_FORMAT;
      frameRateMain = DEF_FRAME_RATE_MAIN;
      frameRateRepeat = DEF_FRAME_RATE_REPEAT;
      blackScreen = DEF_BLACK_SCREEN;
    }

};

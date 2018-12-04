class Setting
{
#define DEF_IS_WRITE_SETTING  0x00
#define DEF_SHOW_TITLE        0x01
#define DEF_IS_SOUND_DEFAULT  0x01
#define DEF_IS_SOUND_TIMER    0x01
#define DEF_BASE_TONE         1000
#define DEF_IS_LED_TIMER      0x01
#define DEF_DEFAULT_FORMAT    0x01
#define DEF_FRAME_RATE_MAIN   20
#define DEF_BLACK_SCREEN      0x00
#define DEF_INVERT_OPPONENT   0x00

  public:
    byte isWritedSetting = 0x00;
    byte showTitle = 0x00;
    byte isSoundDefault = 0x00;
    byte isSoundTimer = 0x00;
    int  baseTone = 0;
    byte isLedTimer = 0x00;
    byte defaultFormat = 0x00;
    byte frameRateMain = 0x00;
    byte blackScreen = 0x00;
    byte invertOpponent = 0x00;

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
      isSoundDefault = EEPROM.read(point++);
      isSoundTimer = EEPROM.read(point++);
      baseTone = (EEPROM.read(point++) << 8) | EEPROM.read(point++);
      isLedTimer = EEPROM.read(point++);
      defaultFormat = EEPROM.read(point++);
      frameRateMain = EEPROM.read(point++);
      blackScreen = EEPROM.read(point++);
      invertOpponent = EEPROM.read(point++);
    }

    void writeEepRomSetting()
    {
      // *** !! BE CAREFUL !! *** //
      byte point = 16;
      EEPROM.write(point++, isWritedSetting);
      EEPROM.write(point++, showTitle);
      EEPROM.write(point++, isSoundDefault);
      EEPROM.write(point++, isSoundTimer);
      EEPROM.write(point++, ((baseTone >> 8) & 0xFF));
      EEPROM.write(point++, (baseTone & 0xFF));
      EEPROM.write(point++, isLedTimer);
      EEPROM.write(point++, defaultFormat);
      EEPROM.write(point++, frameRateMain);
      EEPROM.write(point++, blackScreen);
      EEPROM.write(point++, invertOpponent);
    }

  private:
    void setDefaultSetting()
    {
      isWritedSetting = DEF_IS_WRITE_SETTING;
      showTitle = DEF_SHOW_TITLE;
      isSoundDefault = DEF_IS_SOUND_DEFAULT;
      isSoundTimer = DEF_IS_SOUND_TIMER;
      baseTone = DEF_BASE_TONE;
      isLedTimer = DEF_IS_LED_TIMER;
      defaultFormat = DEF_DEFAULT_FORMAT;
      frameRateMain = DEF_FRAME_RATE_MAIN;
      blackScreen = DEF_BLACK_SCREEN;
      invertOpponent = DEF_INVERT_OPPONENT;
    }
};

enum Menu
{
  M_HEAD = 0,
  M_PLAYER = 0,
  M_DICE = 1,
  M_MATCH = 2,
  M_TIME = 3,
  M_DISCARD = 4,
  M_STORM = 5,
  M_COUNT = 6,
  M_SOUND = 7,
  M_SETTING = 8,
  M_TAIL = 8
};

enum SettingMenu
{
  SM_HEAD = 0,
  SM_SHOW_TITLE = 0,
  SM_DEFAULT_SOUND = 1,
  SM_DEFAULT_BASETONE1 = 2,
  SM_DEFAULT_BASETONE2 = 3,
  SM_LED_TIMER = 4,
  SM_LED_STORM = 5,
  SM_DEFAULT_FORMAT = 6,
  SM_FRAME_RATE_BASE = 7,
  SM_FRAME_RATE_REPEAT = 8,
  SM_BLACK_SCREEN = 9,
  SM_TAIL = 9,
};

enum UtilMenuMax
{
  MAX_PLAYER = 0,
  MAX_DICE = 1,
  MAX_MATCH = 2,
  MAX_TIME = 0,
  MAX_DISCARD = 1,
  MAX_STORM = 6,  
  MAX_COUNT = 2,
  MAX_SOUND = 0,
  MAX_SETTING = 0
};

enum PlayMode
{
  PM_HEAD = 0,
  P1   = 0,
  P2   = 1,
  P3   = 2,
  EDH  = 3,
  ARCH = 4,
  EMP  = 5,
  PM_TAIL = 5
};

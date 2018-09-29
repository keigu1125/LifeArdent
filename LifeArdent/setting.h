class Setting
{
  private:
  public:
    byte PLAYER_COUNT = 6;
    Player p[6];
    byte pCount = 0;
    byte mode = PM_HEAD;
    short changeLife = 0;
    TimeFormat tPressed;
    TimeFormat tTimer;
    bool isSound = true;
    
    void Setting::initPlayer()
    {
      for (byte i = 0; i < PLAYER_COUNT; i++)
      {
        short life = (mode == EDH || (i == 0 && mode == ARCH)) ? 40 : 20;
        p[i].init(life);
      }
    }

    void Setting::initPlayerLife()
    {
      for (byte i = 0; i < PLAYER_COUNT; i++)
      {
        short life = (mode == EDH || (i == 0 && mode == ARCH)) ? 40 : 20;
        p[i].life = life;
      }
    }

    void Setting::initMode(byte value)
    {
      if (value > PlayMode::PM_TAIL || value < PlayMode::PM_HEAD)
      {
        return;
      }

      mode = value;

      switch (mode)
      {
        case PlayMode::P1:
          pCount = 1;
          p[0].setXY( 0,  0, 97, 53);
          break;
        case PlayMode::P2:
          pCount = 2;
          p[0].setXY( 0,  0, 48, 53);
          p[1].setXY(49,  0, 48, 53);
          break;
        case PlayMode::P3:
          pCount = 3;
          p[0].setXY( 0,  0, 48, 27);
          p[1].setXY(49,  0, 48, 27);
          p[2].setXY(24, 26, 48, 27);
          break;
        case PlayMode::EDH:
          pCount = 4;
          p[0].setXY( 0,  0, 48, 27);
          p[1].setXY(49,  0, 48, 27);
          p[2].setXY( 0, 26, 48, 27);
          p[3].setXY(49, 26, 48, 27);
          break;
        case PlayMode::ARCH:
          pCount = 4;
          p[0].setXY( 0,  0, 97, 27);
          p[1].setXY( 0, 26, 33, 27);
          p[2].setXY(32, 26, 33, 27);
          p[3].setXY(64, 26, 33, 27);
          break;
        case PlayMode::EMP:
          pCount = 6;
          p[0].setXY( 0,  0, 33, 27);
          p[1].setXY(32,  0, 33, 27);
          p[2].setXY(64,  0, 33, 27);
          p[3].setXY( 0, 26, 33, 27);
          p[4].setXY(32, 26, 33, 27);
          p[5].setXY(64, 26, 33, 27);
          break;
      }

      initPlayer();
    }

    String Setting::getModeName(PlayMode m)
    {
      String ret = "    ";
      switch (m)
      {
        case PlayMode::P1:
          ret = "Solo";
          break;
        case PlayMode::P2:
          ret = "VS 2";
          break;
        case PlayMode::P3:
          ret = "VS 3";
          break;
        case PlayMode::EDH:
          ret = "EDH ";
          break;
        case PlayMode::ARCH:
          ret = "Arch";
          break;
        case PlayMode::EMP:
          ret = "Empr";
          break;
      }

      return ret;
    }

    bool Setting::isCounterUsed()
    {
      for (Player pl : p)
      {
        if (pl.counter1 != 0 || pl.counter2 != 0)
        {
          return true;
        }
      }
      return false;
    }

    void Setting::initCounter()
    {
      for (byte i = 0; i < PLAYER_COUNT; i++)
      {
        p[i].counter1 = 0;
        p[i].counter2 = 0;
      }
    }
};


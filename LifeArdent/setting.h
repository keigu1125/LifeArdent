class Setting
{
  private:
    short PLAYER_COUNT = 6;
  public:
    Player p[6];
    unsigned char pCount = 0;
    short mode = PM_HEAD;
    short changeLife = 0;
    TimeFormat tPressed;
    TimeFormat tTimer;
    boolean isSound = true;
    
    void Setting::initPlayer()
    {
      for (char i = 0; i < PLAYER_COUNT; i++)
      {
        short life = (mode == EDH || (i == 0 && mode == ARCH)) ? 40 : 20;
        p[i].init(life);
      }
    }

    void Setting::initPlayerLife()
    {
      for (char i = 0; i < PLAYER_COUNT; i++)
      {
        short life = (mode == EDH || (i == 0 && mode == ARCH)) ? 40 : 20;
        p[i].life = life;
      }
    }

    void Setting::initMode(char value)
    {
      if (value > PM_TAIL || value < PM_HEAD)
      {
        return;
      }

      mode = value;

      switch (mode)
      {
        case P1:
          pCount = 1;
          p[0].setXY( 0,  0, 97, 53);
          break;
        case P2:
          pCount = 2;
          p[0].setXY( 0,  0, 48, 53);
          p[1].setXY(49,  0, 48, 53);
          break;
        case P3:
          pCount = 3;
          p[0].setXY( 0,  0, 48, 27);
          p[1].setXY(49,  0, 48, 27);
          p[2].setXY(24, 26, 48, 27);
          break;
        case EDH:
          pCount = 4;
          p[0].setXY( 0,  0, 48, 27);
          p[1].setXY(49,  0, 48, 27);
          p[2].setXY( 0, 26, 48, 27);
          p[3].setXY(49, 26, 48, 27);
          break;
        case ARCH:
          pCount = 4;
          p[0].setXY( 0,  0, 97, 27);
          p[1].setXY( 0, 26, 33, 27);
          p[2].setXY(32, 26, 33, 27);
          p[3].setXY(64, 26, 33, 27);
          break;
        case EMP:
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

    String Setting::getModeName(char m)
    {
      String ret = "    ";
      switch (m)
      {
        case P1:
          ret = "Solo";
          break;
        case P2:
          ret = "VS 2";
          break;
        case P3:
          ret = "VS 3";
          break;
        case EDH:
          ret = "EDH ";
          break;
        case ARCH:
          ret = "Arch";
          break;
        case EMP:
          ret = "Empr";
          break;
      }

      return ret;
    }

};


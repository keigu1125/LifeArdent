class Format
{
  private:
  public:
    Player p[4];
    byte pCount = 0;
    const byte PLAYER_COUNT = 4;
    byte mode = PM_HEAD;
    short changeLife = 0;

    void Format::setXY(byte pC, byte x, byte y, byte w, byte h)
    {
      p[pC].x = x;
      p[pC].y = y;
      p[pC].w = w;
      p[pC].h = h;
    }

    void Format::initPlayer()
    {
      for (byte i = 0; i < PLAYER_COUNT; i++)
      {
        short life = (mode == EDH || (mode == ARCH && i == 0)) ? 40 : 20;
        for (byte j = 0; j < PLAYER_COUNT; j++)
        {
          p[i].c[j] = 0;
        }
        p[i].life = life;
        p[i].win = 0;
        p[i].counter1 = 0;
        p[i].counter2 = 0;
      }
    }

    void Format::initPlayerLife()
    {
      for (byte i = 0; i < PLAYER_COUNT; i++)
      {
        short life = (mode == EDH || (i == 0 && mode == ARCH)) ? 40 : 20;
        p[i].life = life;
      }
    }

    void Format::initMode(byte value)
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
          setXY(0,  0,  0, 97, 53);
          break;
        case PlayMode::P2:
          pCount = 2;
          setXY(0,  0,  0, 48, 53);
          setXY(1, 49,  0, 48, 53);
          break;
        case PlayMode::P3:
          pCount = 3;
          setXY(0,  0,  0, 48, 27);
          setXY(1, 49,  0, 48, 27);
          setXY(2, 24, 26, 48, 27);
          break;
        case PlayMode::EDH:
          pCount = 4;
          setXY(0,  0,  0, 48, 27);
          setXY(1, 49,  0, 48, 27);
          setXY(2,  0, 26, 48, 27);
          setXY(3, 49, 26, 48, 27);
          break;
        case PlayMode::ARCH:
          pCount = 4;
          setXY(0,  0,  0, 97, 27);
          setXY(1,  0, 26, 33, 27);
          setXY(2, 32, 26, 33, 27);
          setXY(3, 64, 26, 33, 27);
          break;
      }

      initPlayer();
    }

    String Format::getModeName(PlayMode m)
    {
      switch (m)
      {
        case PlayMode::P1:
          return "Solo";
        case PlayMode::P2:
          return "VS 2";
        case PlayMode::P3:
          return "VS 3";
        case PlayMode::EDH:
          return "EDH ";
        case PlayMode::ARCH:
          return "Arch";
        default:
          return "    ";
      }
    }

    bool Format::isCounterUsed()
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

    void Format::initCounter()
    {
      for (byte i = 0; i < PLAYER_COUNT; i++)
      {
        p[i].counter1 = 0;
        p[i].counter2 = 0;
      }
    }

    void Format::initMatch()
    {
      for (byte i = 0; i < PLAYER_COUNT; i++)
      {
        p[i].win = 0;
      }
    }
};

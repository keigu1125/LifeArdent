void setXY(byte pC, byte x, byte y, byte w, byte h)
{
  p[pC].x = x;
  p[pC].y = y;
  p[pC].w = w;
  p[pC].h = h;
}

void initPlayerLife()
{
  for (auto& pl : p)
  {
    int life = INIT_LIFE_NORMAL;

    if (mode == PM_EDH)
    {
      life = INIT_LIFE_EDH;
    }
    
    for (auto &cu : pl.c)
    {
      cu = 0;
    }

    pl.life = life;
  }

  if (mode == PM_ARCH)
  {
    p[0].life = INIT_LIFE_ARCH;
  }
}

void initCounter()
{
  for (auto &pl : p)
  {
    pl.counter1 = 0;
    pl.counter2 = 0;
  }
}

void initPlayer()
{
  initPlayerLife();
  initCounter();
}

void initMode(byte value)
{
  if (value > PM_TAIL || value < PM_HEAD)
  {
    return;
  }

  mode = value;

  switch (mode)
  {
    case PM_P1:
      pCount = 1;
      setXY(0,  0,  0, 97, 53);
      break;
    case PM_P2:
      pCount = 2;
      setXY(0,  0,  0, 48, 53);
      setXY(1, 49,  0, 48, 53);
      break;
    case PM_P3:
      pCount = 3;
      setXY(0,  0,  0, 48, 27);
      setXY(1, 49,  0, 48, 27);
      setXY(2, 24, 26, 48, 27);
      break;
    case PM_EDH:
      pCount = 4;
      setXY(0,  0,  0, 48, 27);
      setXY(1, 49,  0, 48, 27);
      setXY(2,  0, 26, 48, 27);
      setXY(3, 49, 26, 48, 27);
      break;
    case PM_ARCH:
      pCount = 4;
      setXY(0,  0,  0, 97, 27);
      setXY(1,  0, 26, 33, 27);
      setXY(2, 32, 26, 33, 27);
      setXY(3, 64, 26, 33, 27);
      break;
  }
  initPlayer();
}

String getModeName(byte m)
{
  switch (m)
  {
    case PM_P1:
      return "Solo";
    case PM_P2:
      return "VS 2";
    case PM_P3:
      return "VS 3";
    case PM_EDH:
      return "EDH ";
    case PM_ARCH:
      return "Arch";
    default:
      return "    ";
  }
}

bool isCounterUsed()
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

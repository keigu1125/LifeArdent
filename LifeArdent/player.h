class Player
{
  public:
    byte x = 0;
    byte y = 0;
    byte w = 0;
    byte h = 0;
    short life = 0;
    byte c[4];
    byte win = 0;
    byte counter1 = 0;
    byte counter2 = 0;

    void Player::init(short life)
    {
      this->life = life;
      for (byte i = 0; i < 4; i++)
      {
        c[i] = 0;
      }
      win = 0;
      counter1 = 0;
      counter2 = 0;
    }

    void Player::setXY(byte x, byte y, byte w, byte h)
    {
      this->x = x;
      this->y = y;
      this->w = w;
      this->h = h;
    }
};


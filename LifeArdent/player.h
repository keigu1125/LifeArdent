class Player
{
  public:
    unsigned char x = 0;
    unsigned char y = 0;
    unsigned char w = 0;
    unsigned char h = 0;
    short life = 0;
    short c[4];
    unsigned char win = 0;
    unsigned char counter1 = 0;
    unsigned char counter2 = 0;

    void Player::init(short life)
    {
      this->life = life;
      for (int i = 0; i < 4; i++)
      {
        c[i] = 0;
      }
      win = 0;
      counter1 = 0;
      counter2 = 0;
    }

    void Player::setXY(unsigned char x, unsigned char y, unsigned char w, unsigned char h)
    {
      this->x = x;
      this->y = y;
      this->w = w;
      this->h = h;
    }
};


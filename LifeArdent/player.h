class Player
{
  public:
    int life = 0;
    int x = 0;
    int y = 0;
    int w = 0;
    int h = 0;
    int c[4];
    int win = 0;
    int poison = 0;

    void Player::initC()
    {
      for (int i = 0; i < 4; i++)
      {
        c[i] = 0;
      }
    }

    void Player::setXY(int x, int y, int w, int h)
    {
      this->x = x;
      this->y = y;
      this->w = w;
      this->h = h;
    }
};


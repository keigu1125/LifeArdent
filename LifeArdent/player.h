class Player
{
  public:
    int x = 0;
    int y = 0;
    int w = 0;
    int h = 0;
    int life = 0;
    int c[4];
    int win = 0;
    int counter1 = 0;
    int counter2 = 0;

    void Player::init(int life)
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

    void Player::setXY(int x, int y, int w, int h)
    {
      this->x = x;
      this->y = y;
      this->w = w;
      this->h = h;
    }
};


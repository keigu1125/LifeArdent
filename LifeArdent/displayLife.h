class DisplayLife : public Form {
  private:
    int rectW = 9;
    int rectH = 7;
    int PLAYER_COUNT = 6;
  public:
    boolean isCursorC = false;

    Player p[6];
    int pCount = 0;

    int cursorP = 0;
    int cursorC = 0;

    int mode = PM_HEAD;

    bool isFlash = false;

    DisplayLife()
    {
      x = 30;
      y = 0;
      isCursor = false;
    }

    void DisplayLife::display()
    {
      drawFrame();
      drawLife();

      if (isCursor)
      {
        if (isCursorC)
        {
          drawCursorC();
        }
        drawCursor();
      }
    }

    void DisplayLife::initMode(int value)
    {
      if (value <= PM_TAIL && value >= PM_HEAD)
      {
        mode = value;
        initMode();
      }

      initPlayer();
    }

    void DisplayLife::initPlayer()
    {
      initPlayerLife();

      for (int i = 0; i < PLAYER_COUNT; i++)
      {
        p[i].poison = 0;
        p[i].win = 0;
      }
    }

    void DisplayLife::initPlayerLife()
    {
      int life = (mode == EDH) ? 40 : 20;
      for (int i = 0; i < PLAYER_COUNT; i++)
      {
        p[i].life = life;
        p[i].initC();
      }
      if (mode == ARCH)
      {
        p[0].life = 40;
      }
    }

    String DisplayLife::getModeName(int mode)
    {
      String ret = "    ";
      switch (mode)
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

  private:
    void DisplayLife::initMode()
    {
      switch (mode) {
        case P1:
          pCount = 1;
          p[0].setXY( 0,  0, 97, 52);
          break;
        case P2:
          pCount = 2;
          p[0].setXY( 0,  0, 48, 52);
          p[1].setXY(49,  0, 48, 52);
          break;
        case P3:
          pCount = 3;
          p[0].setXY( 0,  0, 48, 26);
          p[1].setXY(49,  0, 48, 26);
          p[2].setXY(24, 25, 48, 26);
          break;
        case EDH:
          pCount = 4;
          p[0].setXY( 0,  0, 48, 26);
          p[1].setXY(49,  0, 48, 26);
          p[2].setXY( 0, 25, 48, 27);
          p[3].setXY(49, 25, 48, 27);
          break;
        case ARCH:
          pCount = 4;
          p[0].setXY( 0,  0, 97, 26);
          p[1].setXY( 0, 25, 33, 27);
          p[2].setXY(32, 25, 33, 27);
          p[3].setXY(64, 25, 33, 27);
          break;
        case EMP:
          pCount = 6;
          p[0].setXY( 0,  0, 33, 26);
          p[1].setXY(32,  0, 33, 26);
          p[2].setXY(64,  0, 33, 26);
          p[3].setXY( 0, 25, 33, 27);
          p[4].setXY(32, 25, 33, 27);
          p[5].setXY(64, 25, 33, 27);
          break;
      }

      cursorC = 0;
      cursorP = 0;

      initPlayer();
    }

    void DisplayLife::drawFrame()
    {
      int cMax = (mode == EDH) ? 4 : 1;
      for (int i = 0; i < pCount; i++)
      {
        int drawX = x + p[i].x;
        int drawY = y + p[i].y;
        ab->drawRect(drawX, drawY, p[i].w, p[i].h, WHITE);
        for (int j = 0; j < cMax; j++)
        {
          int drawCX = drawX;
          int drawCY = drawY;
          drawCX += (j == 1 || j == 3) ? (p[i].w - rectW - 2) : 0;
          drawCY += (j == 2 || j == 3) ? (p[i].h - rectH - 2) : 0;
          ab->drawRect(drawCX, drawCY, rectW + 2, rectH + 2, WHITE);
        }
      }
      if (mode == ARCH)
      {
        ab->drawBitmap(x + 17, y + 1, symbol_arch, 63, 24, WHITE);
      }
    }

    void DisplayLife::drawCursor()
    {
      int drawX = x + p[cursorP].x + 1;
      int drawY = y + p[cursorP].y + 1;
      if (mode == EDH)
      {
        drawX += (cursorP == 1 || cursorP == 3) ? (p[cursorP].w - rectW - 2) : 0;
        drawY += (cursorP == 2 || cursorP == 3) ? (p[cursorP].h - rectH - 2) : 0;
      }

      ab->fillRect(drawX, drawY, rectW, rectH, 1);
    }

    void DisplayLife::drawLife()
    {
      switch (mode) {
        case P1:
          drawLifeP1();
          break;
        case P2:
          drawLifeP2();
          break;
        case P3:
        case EDH:
          drawLifeP4();
          break;
        case ARCH:
          drawLifeArch();
          break;
        case EMP:
          drawLifeEmp();
          break;
      }
    }

    void DisplayLife::drawCursorC()
    {
      int drawX = x + p[cursorP].x + 3;
      int drawY = y + p[cursorP].y + 1;
      drawX += (cursorC == 1 || cursorC == 3) ? (p[cursorP].w - rectW - 4) : 0;
      drawY += rectH + 3;

      switch (cursorC)
      {
        case 0:
        case 1:
          drawArrowTop(ab, drawX, drawY, true);
          break;
        case 2:
        case 3:
          drawArrowDown(ab, drawX, drawY, true);
          break;
      }
    }

    void DisplayLife::drawLifeP1()
    {
      int life = p[0].life;

      int drawX = x;
      int drawY = y;
      int fSize = 0;

      if (life >= 100 || life <= -10)
      {
        fSize = 4;
        drawX += 14;
        drawY += 11;
      }
      else if (life >= 0 && life <= 9)
      {
        fSize = 5;
        drawX += 36;
        drawY += 8;
      }
      else
      {
        fSize = 5;
        drawX += 21;
        drawY += 8;
      }

      drawText(ab, drawX, drawY, fSize, life);
    }

    void DisplayLife::drawLifeP2()
    {
      int drawX = 0;
      int drawY = 0;
      int fSize = 0;
      int life = 0;

      for (int i = 0; i < 2; i++)
      {
        life = p[i].life;
        drawX = x + p[i].x;
        drawY = y + p[i].y;

        if (life >= 100 || life <= -10)
        {
          drawX += 7;
          drawY += 18;
          fSize = 2;
        }
        else if (life >= 0 && life <= 9)
        {
          drawX += 18;
          drawY += 15;
          fSize = 3;
        }
        else
        {
          drawX += 8;
          drawY += 15;
          fSize = 3;
        }

        drawText(ab, drawX, drawY, fSize, life);
      }
    }

    void DisplayLife:: drawLifeP4()
    {
      int life = 0;
      int drawX = 0;
      int drawY = 0;
      int fSize = 0;

      for (int i = 0; i < pCount; i++)
      {
        bool isLose = false;

        life = p[i].life;

        drawX = x + p[i].x;
        drawY = y + p[i].y;

        if (mode == EDH)
        {
          for (int j = 0; j < 4; j++)
          {
            int drawMiniX = drawX + 1;
            int drawMiniY = drawY + 1;

            drawMiniX += (j == 1 || j == 3) ? (p[i].w - rectW - 2) : 0;
            drawMiniY += (j == 2 || j == 3) ? (p[i].h - rectH - 2) : 0;

            int miniLife = p[i].c[j];

            if (j != i)
            {
              drawSmallNumber(ab, drawMiniX, drawMiniY, miniLife, true);
            }
          }
        }

        if (life >= 100 || life <= -10)
        {
          drawX += 15;
          drawY += 9;
          fSize = 1;
        }
        else if (life >= 0 && life <= 9)
        {
          drawX += + 20;
          drawY += + 6;
          fSize = 2;
        }
        else
        {
          drawX += 13;
          drawY += 6;
          fSize = 2;
        }

        drawText(ab, drawX, drawY, fSize, life);
      }
    }

    void DisplayLife::drawLifeArch()
    {
      int life = 0;
      int drawX = 0;
      int drawY = 0;
      int fSize = 0;

      // DRAW PLAYER
      for (int i = 1; i < pCount; i++)
      {
        life = p[i].life;

        drawX = x + p[i].x;
        drawY = y + p[i].y;

        if (life >= 100 || life <= -10)
        {
          fSize = 1;
          drawX += 8;
          drawY += 14;
        }
        else if (life >= 0 && life <= 9)
        {
          fSize = 2;
          drawX += 12;
          drawY += 10;
        }
        else
        {
          fSize = 2;
          drawX += 5;
          drawY += 10;
        }

        drawText(ab, drawX, drawY, fSize, life);
      }

      // DRAW ARCH
      life = p[0].life;

      drawX = x + p[0].x;
      drawY = y + p[0].y;

      if (life >= 100 || life <= -10)
      {
        fSize = 2;
        drawX += 30;
        drawY += 6;
      }
      else if (life >= 0 && life <= 9)
      {
        fSize = 2;
        drawX += 44;
        drawY += 6;
      }
      else
      {
        fSize = 2;
        drawX += 37;
        drawY += 6;
      }

      if (life > 0)
      {
        drawText(ab, drawX, drawY, fSize, life);
      }
    }

    void DisplayLife::drawLifeEmp()
    {
      int life = 0;
      int drawX = 0;
      int drawY = 0;
      int fSize = 0;

      for (int i = 0; i < pCount; i++)
      {
        life = p[i].life;

        drawX = x + p[i].x;
        drawY = y + p[i].y;

        if (life >= 100 || life <= -10)
        {
          fSize = 1;
          drawX += 8;
          drawY += 14;
        }
        else if (life >= 0 && life <= 9)
        {
          fSize = 2;
          drawX += 12;
          drawY += 10;
        }
        else
        {
          fSize = 2;
          drawX += 5;
          drawY += 10;
        }

        drawText(ab, drawX, drawY, fSize, life);
      }
    }
};


class DisplayLife : public Form {
  private:
    int rectW = 9;
    int rectH = 7;
  public:
    boolean isCursorC = false;
    int cursorC = 0;

    DisplayLife()
    {
      x = 30;
      y = 0;
      isCursor = false;
      cursor = 0;
      cursorMax = PM_TAIL;
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

    int DisplayLife::getLifeTone(int baseTone, int toneLife)
    {
      int l = setting->p[cursor].life;
      return baseTone - (toneLife * 20) + ((l <= 0) ? 0 : ((l > 200) ? 200 : l) * toneLife);
    }

    virtual void upButton()
    {
      if (isCursorC)
      {
        if (cursorC != cursor && setting->p[cursor].c[cursorC] < 21)
        {
          setting->p[cursor].c[cursorC]++;
          setting->p[cursor].life--;
          setting->changeLife--;
        }
      }
      else
      {
        setting->p[cursor].life++;
        setting->changeLife++;
      }
    }

    virtual void downButton()
    {
      if (isCursorC)
      {
        if (cursorC != cursor && setting->p[cursor].c[cursorC] > 0)
        {
          setting->p[cursor].c[cursorC]--;
          setting->p[cursor].life++;
          setting->changeLife++;
        }
      }
      else
      {
        setting->p[cursor].life--;
        setting->changeLife--;
      }
    }

    virtual void leftButton()
    {
      setting->changeLife = 0;

      if (isCursorC)
      {
        cursorC--;
        if (cursorC < 0)
        {
          cursorC = 3;
        }
      }
      else
      {
        if (cursor > 0)
        {
          cursor--;
        }
        else
        {
          activeMenu();
        }
      }
    }

    virtual void rightButton()
    {
      setting->changeLife = 0;

      if (isCursorC)
      {
        cursorC++;
        if (cursorC >= 4)
        {
          cursorC = 0;
        }
      }
      else
      {
        if (cursor < setting->pCount - 1)
        {
          cursor++;
        }
        else
        {
          activeMenu();
        }
      }
    }

    virtual void aButton()
    {
      if (setting->mode == P2)
      {
        int value = (cursor == 0) ? - 1 : + 1;

        setting->p[0].life += value;
        setting->p[1].life -= value;
        setting->changeLife--;
      }
      else if (setting->mode == EDH)
      {
        isCursorC = !isCursorC;
        cursorC = cursor;
      }
    }

    virtual void bButton()
    {
      if (setting->mode == P2)
      {
        int value = (cursor == 0) ? + 1 : - 1;

        setting->p[0].life += value;
        setting->p[1].life -= value;
        setting->changeLife++;
      }
      else if (setting->mode == EDH)
      {
        isCursorC = !isCursorC;
        cursorC = cursor;
      }
    }

    virtual void abButton()
    {
      setting->initPlayerLife();
      setting->changeLife = 0;
    }

  private:
    void DisplayLife::drawFrame()
    {
      int cMax = (setting->mode == EDH) ? 4 : 1;
      for (int i = 0; i < setting->pCount; i++)
      {
        int drawX = x + setting->p[i].x;
        int drawY = y + setting->p[i].y;
        ab->drawRect(drawX, drawY, setting->p[i].w, setting->p[i].h, WHITE);
        for (int j = 0; j < cMax; j++)
        {
          int drawCX = drawX;
          int drawCY = drawY;
          drawCX += (j == 1 || j == 3) ? (setting->p[i].w - rectW - 2) : 0;
          drawCY += (j == 2 || j == 3) ? (setting->p[i].h - rectH - 2) : 0;
          ab->drawRect(drawCX, drawCY, rectW + 2, rectH + 2, WHITE);
        }
      }
      if (setting->mode == ARCH)
      {
        ab->drawBitmap(x + 17, y + 1, symbol_arch, 63, 24, WHITE);
      }
    }

    void DisplayLife::drawCursor()
    {
      int drawX = x + setting->p[cursor].x + 1;
      int drawY = y + setting->p[cursor].y + 1;
      if (setting->mode == EDH)
      {
        drawX += (cursor == 1 || cursor == 3) ? (setting->p[cursor].w - rectW - 2) : 0;
        drawY += (cursor == 2 || cursor == 3) ? (setting->p[cursor].h - rectH - 2) : 0;
      }

      ab->fillRect(drawX, drawY, rectW, rectH, 1);
    }

    void DisplayLife::drawLife()
    {
      switch (setting->mode) {
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
      int drawX = x + setting->p[cursor].x + 3;
      int drawY = y + setting->p[cursor].y + 1;
      drawX += (cursorC == 1 || cursorC == 3) ? (setting->p[cursor].w - rectW - 4) : 0;
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
      int life = setting->p[0].life;

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
        life = setting->p[i].life;
        drawX = x + setting->p[i].x;
        drawY = y + setting->p[i].y;

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

      for (int i = 0; i < setting->pCount; i++)
      {
        bool isLose = false;

        life = setting->p[i].life;

        drawX = x + setting->p[i].x;
        drawY = y + setting->p[i].y;

        if (setting->mode == EDH)
        {
          for (int j = 0; j < 4; j++)
          {
            int drawMiniX = drawX + 1;
            int drawMiniY = drawY + 1;

            drawMiniX += (j == 1 || j == 3) ? (setting->p[i].w - rectW - 2) : 0;
            drawMiniY += (j == 2 || j == 3) ? (setting->p[i].h - rectH - 2) : 0;

            int miniLife = setting->p[i].c[j];

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
      for (int i = 1; i < setting->pCount; i++)
      {
        life = setting->p[i].life;

        drawX = x + setting->p[i].x;
        drawY = y + setting->p[i].y;

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
      life = setting->p[0].life;

      drawX = x + setting->p[0].x;
      drawY = y + setting->p[0].y;

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

      for (int i = 0; i < setting->pCount; i++)
      {
        life = setting->p[i].life;

        drawX = x + setting->p[i].x;
        drawY = y + setting->p[i].y;

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


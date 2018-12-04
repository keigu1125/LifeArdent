class DisplayLife : public Form
{
  private:
  public:
    bool isCursorC = false;

    DisplayLife()
    {
      x = 31;
      // y = 0;
      // isCursor = false;
      // cursor = 0;
      cursorMax = PM_TAIL;
    }

    void DisplayLife::display()
    {
      drawFrame();
      drawLife();
      if (mode == PM_EDH)
      {
        drawMiniC();
      }

      if (isCursor)
      {
        if (isCursorC)
        {
          drawCursorC();
        }
        drawCursor();
      }
    }

    virtual void upButton()
    {
      if (isCursorC)
      {
        if (cursorC != cursor && addValue(&p[cursor].c[cursorC], 21))
        {
          p[cursor].life--;
          changeLife--;
        }
      }
      else
      {
        p[cursor].life++;
        changeLife++;
      }
    }

    virtual void downButton()
    {
      if (isCursorC)
      {
        if (cursorC != cursor && subValue(&p[cursor].c[cursorC],  0))
        {
          p[cursor].life++;
          changeLife++;
        }
      }
      else
      {
        p[cursor].life--;
        changeLife--;
      }
    }

    virtual void leftButton()
    {
      changeLife = 0;

      if (isCursorC)
      {
        rotateDown(&cursorC, 0, 3);
      }
      else if (!subValue(&cursor, 0))
      {
        activeMenu();
      }
    }

    virtual void rightButton()
    {
      changeLife = 0;

      if (isCursorC)
      {
        rotateUp(&cursorC, 0, 3);
      }
      else if (!addValue(&cursor, pCount - 1))
      {
        activeMenu();
      }
    }

    virtual void aButton()
    {
      if (mode == PM_P2)
      {
        char value = (cursor == 0) ? - 1 : + 1;

        p[0].life += value;
        p[1].life -= value;
        changeLife--;
      }
      else if (mode == PM_EDH)
      {
        isCursorC = !isCursorC;
        cursorC = cursor;
      }
    }

    virtual void bButton()
    {
      if (mode == PM_P2)
      {
        char value = (cursor == 0) ? + 1 : - 1;

        p[0].life += value;
        p[1].life -= value;
        changeLife++;
      }
      else if (mode == PM_EDH)
      {
        isCursorC = !isCursorC;
        cursorC = cursor;
      }
    }

    virtual void abButton()
    {
      initPlayerLife();
      changeLife = 0;
    }

  private:
    void DisplayLife::drawFrame()
    {
      byte cMax = (mode == PM_EDH) ? 4 : 1;
      for (byte i = 0; i < pCount; i++)
      {
        Player pl = p[i];
        byte drawX = pl.x + x;
        byte drawY = pl.y + y;
        ab.drawRect(drawX, drawY, pl.w, pl.h, WHITE);
        for (byte j = 0; j < cMax; j++)
        {
          byte drawCX = drawX;
          byte drawCY = drawY;
          drawCX += (j == 1 || j == 3) ? (pl.w - CURSOR_RECT_W - 2) : 0;
          drawCY += (j == 2 || j == 3) ? (pl.h - CURSOR_RECT_H - 2) : 0;
          ab.drawRect(drawCX, drawCY, CURSOR_RECT_W + 2, CURSOR_RECT_H + 2, WHITE);
        }
      }
    }

    void DisplayLife::drawCursor()
    {
      Player pl = p[cursor];
      byte drawX = x + pl.x + 1;
      byte drawY = y + pl.y + 1;
      if (mode == PM_EDH)
      {
        drawX += (cursor == 1 || cursor == 3) ? (pl.w - CURSOR_RECT_W - 2) : 0;
        drawY += (cursor == 2 || cursor == 3) ? (pl.h - CURSOR_RECT_H - 2) : 0;
      }

      ab.fillRect(drawX, drawY, CURSOR_RECT_W, CURSOR_RECT_H, 1);
    }

    void DisplayLife::drawMiniC()
    {
      for (int i = 0; i < PLAYER_COUNT; i++)
      {
        Player pl = p[i];
        for (byte j = 0; j < 4; j++)
        {
          if (i == j)
          {
            continue;
          }
          byte miniLife = pl.c[j];
          byte drawMiniX = pl.x + x + 1;
          byte drawMiniY = pl.y + y + 1;

          drawMiniX += (j == 1 || j == 3) ? (pl.w - CURSOR_RECT_W - 2) : 0;
          drawMiniY += (j == 2 || j == 3) ? (pl.h - CURSOR_RECT_H - 2) : 0;

          drawSmallNumber(drawMiniX, drawMiniY, miniLife, true);
        }
      }
    }

    void DisplayLife::drawLife()
    {
      for (byte i = 0; i < pCount; i++)
      {
        Player pl = p[i];

        int life = pl.life;
        byte fSize = 2;
        byte drawX = pl.x + x;
        byte drawY = pl.y + y;
        bool invert = false;

        switch (mode)
        {
          case PM_P1:
            if (life >= 100 || life <= -10)
            {
              drawX += 14;
              drawY += 11;
              fSize = 4;
            }
            else if (life >= 0 && life <= 9)
            {
              drawX += 36;
              drawY += 8;
              fSize = 5;
            }
            else
            {
              drawX += 21;
              drawY += 8;
              fSize = 5;
            }
            break;
          case PM_P2:
            if (life >= 100 || life <= -10)
            {
              drawX += 7;
              drawY += 19;
              fSize = 2;
            }
            else if (life >= 0 && life <= 9)
            {
              drawX += 17;
              drawY += 16;
              fSize = 3;
            }
            else
            {
              drawX += 8;
              drawY += 16;
              fSize = 3;
            }
            break;
          case PM_P3:
          case PM_EDH:
            if (life >= 100 || life <= -10)
            {
              drawX += 15;
              drawY += 10;
              fSize = 1;
            }
            else if (life >= 0 && life <= 9)
            {
              drawX += 19;
              drawY += 7;
              fSize = 2;
            }
            else
            {
              drawX += 13;
              drawY += 7;
              fSize = 2;
            }
            break;
          case PM_ARCH:
            if (i == 0)
            {
              if (life >= 100 || life <= -10)
              {
                drawX += 30;
                drawY += 6;
                fSize = 2;
              }
              else if (life >= 0 && life <= 9)
              {
                drawX += 44;
                drawY += 6;
                fSize = 2;
              }
              else
              {
                drawX += 37;
                drawY += 6;
                fSize = 2;
              }
            }
            else
            {
              if (life >= 100 || life <= -10)
              {
                drawX += 8;
                drawY += 14;
                fSize = 1;
              }
              else if (life >= 0 && life <= 9)
              {
                drawX += 12;
                drawY += 10;
                fSize = 2;
              }
              else
              {
                drawX += 5;
                drawY += 10;
                fSize = 2;
              }
            }
            break;
        }
        drawText(drawX, drawY, fSize, life, (setting.invertOpponent && pl.invert));
      }
    }

    void DisplayLife::drawCursorC()
    {
      byte drawX = x + p[cursor].x + 3;
      byte drawY = y + p[cursor].y + 1;
      drawX += (cursorC == 1 || cursorC == 3) ? (p[cursor].w - CURSOR_RECT_W - 4) : 0;
      drawY += CURSOR_RECT_H + 3;

      switch (cursorC)
      {
        case 0:
        case 1:
          drawArrowTop(drawX, drawY, true);
          break;
        case 2:
        case 3:
          drawArrowDown(drawX, drawY, true);
          break;
      }
    }
};

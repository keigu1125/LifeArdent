class DisplayLife : public Form
{
  private:
  public:
    bool isCursorC = false;
    byte cursorC = 0;

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
        byte drawX = x + p[i].x;
        byte drawY = y + p[i].y;
        ab.drawRect(drawX, drawY, p[i].w, p[i].h, WHITE);
        for (byte j = 0; j < cMax; j++)
        {
          byte drawCX = drawX;
          byte drawCY = drawY;
          drawCX += (j == 1 || j == 3) ? (p[i].w - rectW - 2) : 0;
          drawCY += (j == 2 || j == 3) ? (p[i].h - rectH - 2) : 0;
          ab.drawRect(drawCX, drawCY, rectW + 2, rectH + 2, WHITE);
        }
      }
    }

    void DisplayLife::drawCursor()
    {
      byte drawX = x + p[cursor].x + 1;
      byte drawY = y + p[cursor].y + 1;
      if (mode == PM_EDH)
      {
        drawX += (cursor == 1 || cursor == 3) ? (p[cursor].w - rectW - 2) : 0;
        drawY += (cursor == 2 || cursor == 3) ? (p[cursor].h - rectH - 2) : 0;
      }

      ab.fillRect(drawX, drawY, rectW, rectH, 1);
    }

    void DisplayLife::drawMiniC(byte i, byte drawX, byte drawY)
    {
      if (mode != PM_EDH)
      {
        return;
      }

      for (byte j = 0; j < 4; j++)
      {
        if (i == j)
        {
          continue;
        }

        byte drawMiniX = drawX + 1;
        byte drawMiniY = drawY + 1;

        drawMiniX += (j == 1 || j == 3) ? (p[i].w - rectW - 2) : 0;
        drawMiniY += (j == 2 || j == 3) ? (p[i].h - rectH - 2) : 0;

        byte miniLife = p[i].c[j];
        drawSmallNumber(drawMiniX, drawMiniY, miniLife, true);
      }
    }

    void DisplayLife::drawLife()
    {
      for (byte i = 0; i < pCount; i++)
      {
        int life = p[i].life;
        byte fSize = 2;
        // 以下、int以外にしない
        int drawX = p[i].x + x;
        int drawY = p[i].y + y;

        switch (mode)
        {
          case PM_P1:
            if (life >= 100 || life <= -10)
            {
              drawText(drawX + 14, drawY + 11, 4, life);
            }
            else if (life >= 0 && life <= 9)
            {
              drawText(drawX + 36, drawY + 8, 5, life);
            }
            else
            {
              drawText(drawX + 21, drawY + 8, 5, life);
            }
            break;
          case PM_P2:
            if (life >= 100 || life <= -10)
            {
              drawText(drawX + 7, drawY + 18, 2, life);
            }
            else if (life >= 0 && life <= 9)
            {
              drawText(drawX + 18, drawY + 15, 3, life);
            }
            else
            {
              drawText(drawX + 8, drawY + 15, 3, life);
            }
            break;
          case PM_P3:
          case PM_EDH:
            drawMiniC(i, drawX, drawY);
            if (life >= 100 || life <= -10)
            {
              drawText(drawX + 15, drawY + 9, 1, life);
            }
            else if (life >= 0 && life <= 9)
            {
              drawText(drawX + 20, drawY + 6, 2, life);
            }
            else
            {
              drawText(drawX + 13, drawY + 6, 2, life);
            }
            break;
          case PM_ARCH:
            if (i == 0)
            {
              if (life >= 100 || life <= -10)
              {
                drawText(drawX + 30, drawY + 6, 2, life);
              }
              else if (life >= 0 && life <= 9)
              {
                drawText(drawX + 44, drawY + 6, 2, life);
              }
              else
              {
                drawText(drawX + 37, drawY + 6, 2, life);
              }
            }
            else
            {
              if (life >= 100 || life <= -10)
              {
                drawText(drawX + 8, drawY + 14, 1, life);
              }
              else if (life >= 0 && life <= 9)
              {
                drawText(drawX + 12, drawY + 10, 2, life);
              }
              else
              {
                drawText(drawX + 5, drawY + 10, 2, life);
              }
            }
            break;
        }
      }
    }

    void DisplayLife::_drawLife()
    {
      for (byte i = 0; i < pCount; i++)
      {
        int life = p[i].life;

        byte fSize = 2;
        byte drawX = p[i].x + x;
        byte drawY = p[i].y + y;

        switch (mode)
        {
          case PM_P1:
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
            break;
          case PM_P2:
            if (life >= 100 || life <= -10)
            {
              // fSize = 2;
              drawX += 7;
              drawY += 18;
            }
            else if (life >= 0 && life <= 9)
            {
              fSize = 3;
              drawX += 18;
              drawY += 15;
            }
            else
            {
              fSize = 3;
              drawX += 8;
              drawY += 15;
            }
            break;
          case PM_P3:
          case PM_EDH:
            drawMiniC(i, drawX, drawY);
            if (life >= 100 || life <= -10)
            {
              fSize = 1;
              drawX += 15;
              drawY += 9;
            }
            else if (life >= 0 && life <= 9)
            {
              // fSize = 2;
              drawX += 20;
              drawY += 6;
            }
            else
            {
              // fSize = 2;
              drawX += 13;
              drawY += 6;
            }
            break;
          case PM_ARCH:
            if (i == 0)
            {
              if (life >= 100 || life <= -10)
              {
                // fSize = 2;
                drawX += 30;
                drawY += 6;
              }
              else if (life >= 0 && life <= 9)
              {
                // fSize = 2;
                drawX += 44;
                drawY += 6;
              }
              else
              {
                // fSize = 2;
                drawX += 37;
                drawY += 6;
              }
            }
            else
            {
              if (life >= 100 || life <= -10)
              {
                fSize = 1;
                drawX += 8;
                drawY += 14;
              }
              else if (life >= 0 && life <= 9)
              {
                // fSize = 2;
                drawX += 12;
                drawY += 10;
              }
              else
              {
                // fSize = 2;
                drawX += 5;
                drawY += 10;
              }
            }
            break;
        }
        String a = String(drawX);
        drawText(drawX, drawY, fSize, life);
      }
    }

    void DisplayLife::drawCursorC()
    {
      byte drawX = x + p[cursor].x + 3;
      byte drawY = y + p[cursor].y + 1;
      drawX += (cursorC == 1 || cursorC == 3) ? (p[cursor].w - rectW - 4) : 0;
      drawY += rectH + 3;

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

    void DisplayLife::drawLife(byte i)
    {

    }

};

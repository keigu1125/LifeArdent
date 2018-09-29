class DisplayLife : public Form {
  private:
    #define rectW 9
    #define rectH 7
  public:
    bool isCursorC = false;
    byte cursorC = 0;

    DisplayLife()
    {
      x = 30;
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
        if (cursorC != cursor && addValue(&format->p[cursor].c[cursorC], 21))
        {
          format->p[cursor].life--;
          format->changeLife--;
        }
      }
      else
      {
        format->p[cursor].life++;
        format->changeLife++;
      }
    }

    virtual void downButton()
    {
      if (isCursorC)
      {
        if (cursorC != cursor && subValue(&format->p[cursor].c[cursorC],  0))
        {
          format->p[cursor].life++;
          format->changeLife++;
        }
      }
      else
      {
        format->p[cursor].life--;
        format->changeLife--;
      }
    }

    virtual void leftButton()
    {
      format->changeLife = 0;

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
      format->changeLife = 0;

      if (isCursorC)
      {
        rotateUp(&cursorC, 0, 3);
      }
      else if (!addValue(&cursor, format->pCount - 1))
      {
        activeMenu();
      }
    }

    virtual void aButton()
    {
      if (format->mode == P2)
      {
        char value = (cursor == 0) ? - 1 : + 1;

        format->p[0].life += value;
        format->p[1].life -= value;
        format->changeLife--;
      }
      else if (format->mode == EDH)
      {
        isCursorC = !isCursorC;
        cursorC = cursor;
      }
    }

    virtual void bButton()
    {
      if (format->mode == P2)
      {
        char value = (cursor == 0) ? + 1 : - 1;

        format->p[0].life += value;
        format->p[1].life -= value;
        format->changeLife++;
      }
      else if (format->mode == EDH)
      {
        isCursorC = !isCursorC;
        cursorC = cursor;
      }
    }

    virtual void abButton()
    {
      format->initPlayerLife();
      format->changeLife = 0;
    }

  private:
    void DisplayLife::drawFrame()
    {
      byte cMax = (format->mode == EDH) ? 4 : 1;
      for (byte i = 0; i < format->pCount; i++)
      {
        byte drawX = x + format->p[i].x;
        byte drawY = y + format->p[i].y;
        ab->drawRect(drawX, drawY, format->p[i].w, format->p[i].h, WHITE);
        for (short j = 0; j < cMax; j++)
        {
          byte drawCX = drawX;
          byte drawCY = drawY;
          drawCX += (j == 1 || j == 3) ? (format->p[i].w - rectW - 2) : 0;
          drawCY += (j == 2 || j == 3) ? (format->p[i].h - rectH - 2) : 0;
          ab->drawRect(drawCX, drawCY, rectW + 2, rectH + 2, WHITE);
        }
      }
      if (format->mode == ARCH)
      {
        ab->drawBitmap(x + 17, y + 1, symbol_arch, 63, 24, WHITE);
      }
    }

    void DisplayLife::drawCursor()
    {
      byte drawX = x + format->p[cursor].x + 1;
      byte drawY = y + format->p[cursor].y + 1;
      if (format->mode == EDH)
      {
        drawX += (cursor == 1 || cursor == 3) ? (format->p[cursor].w - rectW - 2) : 0;
        drawY += (cursor == 2 || cursor == 3) ? (format->p[cursor].h - rectH - 2) : 0;
      }

      ab->fillRect(drawX, drawY, rectW, rectH, 1);
    }

    void DisplayLife::drawLife()
    {
      for (byte i = 0; i < format->pCount; i++)
      {
        drawLife(i);
      }
    }

    void DisplayLife::drawCursorC()
    {
      byte drawX = x + format->p[cursor].x + 3;
      byte drawY = y + format->p[cursor].y + 1;
      drawX += (cursorC == 1 || cursorC == 3) ? (format->p[cursor].w - rectW - 4) : 0;
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

    void DisplayLife::drawLife(byte i)
    {
      short life = format->p[i].life;

      byte fSize = 2;
      byte drawX = x + format->p[i].x;
      byte drawY = y + format->p[i].y;

      switch (format->mode)
      {
        case PlayMode::P1:
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
        case PlayMode::P2:
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
        case PlayMode::P3:
        case PlayMode::EDH:
          if (format->mode == EDH)
          {
            for (byte j = 0; j < 4; j++)
            {
              byte drawMiniX = drawX + 1;
              byte drawMiniY = drawY + 1;

              drawMiniX += (j == 1 || j == 3) ? (format->p[i].w - rectW - 2) : 0;
              drawMiniY += (j == 2 || j == 3) ? (format->p[i].h - rectH - 2) : 0;

              byte miniLife = format->p[i].c[j];

              if (j != i)
              {
                drawSmallNumber(ab, drawMiniX, drawMiniY, miniLife, true);
              }
            }
          }

          if (life >= 100 || life <= -10)
          {
            fSize = 1;
            drawX += 15;
            drawY += 9;
          }
          else if (life >= 0 && life <= 9)
          {
            // fSize = 2;
            drawX += + 20;
            drawY += + 6;
          }
          else
          {
            // fSize = 2;
            drawX += 13;
            drawY += 6;
          }
          break;
        case PlayMode::ARCH:
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
        case PlayMode::EMP:
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
          break;
      }

      drawText(ab, drawX, drawY, fSize, life);
    }

};

class DisplaySetting : public Form
{
  public:
    byte cursorC = 0x00;

    DisplaySetting()
    {
      // x = 0;
      // y = 0;
      // isCursor = false;
      // cursor = Menu::M_HEAD;
      cursorMax = M_TAIL;
    }

    void DisplaySetting::display()
    {
      ab.drawLine(0, 12, 128, 12, WHITE);

      byte drawX = 2;
      for (byte i = SMT_HEAD; i <= SMT_TAIL; i++)
      {
        if (i != cursor)
        {
          ab.drawRect(drawX, 3, 13, 6, WHITE);
          drawX += 15;
        }
        else
        {
          ab.drawRect(drawX, 0, 34, 12, WHITE);
          ab.drawLine(drawX, 12, drawX + 34, 12, BLACK);
          drawText(drawX + 3, 3, 1, getMenuTitle(i));
          drawX += 36;
        }
      }

      drawText(13, 13, 1, "default format");
    }

    virtual void upButton()
    {

    }

    virtual void downButton()
    {

    }

    virtual void leftButton()
    {
      if (cursorC == 0)
      {
        subValue(&cursor, SMT_HEAD);
      }
    }

    virtual void rightButton()
    {
      if (cursorC == 0)
      {
        addValue(&cursor, SMT_TAIL);
      }
    }

    virtual void aButton()
    {

    }

    virtual void bButton()
    {

    }

    virtual void abButton()
    {

    }

  private:

    String getMenuTitle(byte c)
    {
      switch (c)
      {
        case SMT_GAME:
          return "GAME ";
        case SMT_TITLE:
          return "TITLE";
        case SMT_SOUND:
          return "SOUND";
        case SMT_DISPLAY:
          return "DISP ";
        case SMT_LED:
          return "LED  ";
        case SMT_FRAME:
          return "FRAME";
        case SMT_EXIT:
          return "EXIT ";
      }
    }

};

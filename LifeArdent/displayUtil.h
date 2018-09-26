class DisplayUtil : public Form {
  private:
  public:
    DisplayMenu* menu;
    DisplayLife* life;

    DisplayUtil()
    {
      x = 0;
      y = 52;
      isCursor = false;
    }

    void DisplayUtil::display()
    {
      String nm;
      String out = "";
      if (isCursor)
      {
        switch (menu->cursorM)
        {
          case M_PLAYER:
            out += life->getModeName(life->mode - 1);
            out += (life->mode > PM_HEAD) ? " << " : "    ";
            out += life->getModeName(life->mode);
            out += (life->mode < PM_TAIL) ? " >> " : "    ";
            out += life->getModeName(life->mode + 1);
            text(out);
            break;
          case M_DICE:
            text("Dice Roll, max 5D6.");
            break;
          case M_MATCH:
            text("Count Match win.");
            break;
          case M_TIME:
            text("50 min stopwatch.");
            break;
          case M_DISCARD:
            text("Pick Random Discard.");
            break;
          case M_STORM:
            text("Count Storm & mana.");
            break;
          case M_COUNT:
            text("Count Poison,Energy.");
            break;
          case M_SOUND:
            isCursor = false;
            break;
          case M_SETTING:
            text("Life Ardent Settings.");
            break;
        }
      }
      else if (menu->isCursor)
      {
        switch (menu->cursorM)
        {
          case M_PLAYER:
            text("Select Format.");
            break;
          case M_DICE:
            text("Dice Roll, max 5D6.");
            break;
          case M_MATCH:
            text("Count Match win.");
            break;
          case M_TIME:
            text("50 min stopwatch.");
            break;
          case M_DISCARD:
            text("Choose Random Discard.");
            break;
          case M_STORM:
            text("Count Storm & mana.");
            break;
          case M_COUNT:
            text("Count Poison,Energy.");
            break;
          case M_SOUND:
            if (menu->isSound)
            {
              text("Set Sound. [ ON ]");
            }
            else
            {
              text("Set Sound. [MUTE]");
            }
            break;
          case M_SETTING:
            text("Life Ardent Settings.");
            break;
        }
      }
    }

  private:
    void DisplayUtil::text(String text)
    {
      drawText(ab, x + 1, y + 2, 1, text);
    }
};


class Form
{
  public:
    Arduboy2* ab = NULL;
    Format* format = NULL;
    byte x = 0;
    byte y = 0;
    bool isCursor = false;
    byte cursor = 0;
    byte cursorMax = 0;

    Form* menu = NULL;
    Form* util = NULL;
    Form* life = NULL;
    Form* sett = NULL;

    virtual void upButton() = 0;
    virtual void downButton() = 0;
    virtual void leftButton() = 0;
    virtual void rightButton() = 0;
    virtual void aButton() = 0;
    virtual void bButton() = 0;
    virtual void abButton() = 0;

    void activeMenu()
    {
      menu->isCursor = true;
      life->isCursor = false;
      util->isCursor = false;
      sett->isCursor = false;
    }

    void activeLife()
    {
      menu->isCursor = false;
      life->isCursor = true;
      util->isCursor = false;
      sett->isCursor = false;
    }

    void activeUtil()
    {
      menu->isCursor = false;
      life->isCursor = false;
      util->isCursor = true;
      sett->isCursor = false;
    }

    void activeSetting()
    {
      menu->isCursor = false;
      life->isCursor = false;
      util->isCursor = false;
      sett->isCursor = true;
    }
};

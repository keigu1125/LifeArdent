class Form
{
  public:
    Arduboy* ab = NULL;
    Setting* setting = NULL;
    unsigned char x = 0;
    unsigned char y = 0;
    boolean isCursor = false;
    unsigned char cursor = 0;
    unsigned char cursorMax = 0;

    Form* menu = NULL;
    Form* util = NULL;
    Form* life = NULL;

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
    }

    void activeLife()
    {
      menu->isCursor = false;
      life->isCursor = true;
      util->isCursor = false;
    }

    void activeUtil()
    {
      menu->isCursor = false;
      life->isCursor = false;
      util->isCursor = true;
    }
};


class Form
{
  public:
    byte x = 0;
    byte y = 0;
    byte cursor = 0;
    byte cursorMax = 0;
    bool isCursor = false;

    virtual void display() = 0;
    virtual void upButton() = 0;
    virtual void downButton() = 0;
    virtual void leftButton() = 0;
    virtual void rightButton() = 0;
    virtual void aButton() = 0;
    virtual void bButton() = 0;
    virtual void abButton() = 0;
};

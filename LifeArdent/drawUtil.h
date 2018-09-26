void drawArrowLeft(Arduboy* ab, int x, int y, bool white)
{
  ab->drawLine(x + 0, y + 0, x + 0, y + 6, white);
  ab->drawLine(x + 1, y + 1, x + 1, y + 5, white);
  ab->drawLine(x + 2, y + 2, x + 2, y + 4, white);
  ab->drawLine(x + 3, y + 3, x + 3, y + 3, white);
}

void drawArrowTop(Arduboy* ab, int x, int y, bool white)
{
  ab->drawLine(x + 3, y + 0, x + 3, y + 0, white);
  ab->drawLine(x + 2, y + 1, x + 4, y + 1, white);
  ab->drawLine(x + 1, y + 2, x + 5, y + 2, white);
  ab->drawLine(x + 0, y + 3, x + 6, y + 3, white);
}

void drawArrowDown(Arduboy* ab, int x, int y, bool white)
{
  ab->drawLine(x + 3, y + 3, x + 3, y + 3, white);
  ab->drawLine(x + 2, y + 2, x + 4, y + 2, white);
  ab->drawLine(x + 1, y + 1, x + 5, y + 1, white);
  ab->drawLine(x + 0, y + 0, x + 6, y + 0, white);
}

void drawText(Arduboy* ab, int a, int b, int fs, String mes)
{
  ab->setCursor(a, b);
  ab->setTextSize(fs);
  ab->print(mes);
}

void drawText(Arduboy* ab, int a, int b, int fs, int mes)
{
  ab->setCursor(a, b);
  ab->setTextSize(fs);
  ab->print(mes);
}

void drawOneSmallNumber(Arduboy* ab, int x, int y, int number, bool white)
{
  int color = (white) ? "1" : "0";

  switch (number)
  {
    case 0:
      ab->drawPixel(x + 1, y + 1, color);
      ab->drawPixel(x + 2, y + 1, color);
      ab->drawPixel(x + 3, y + 1, color);
      ab->drawPixel(x + 1, y + 2, color);
      ab->drawPixel(x + 3, y + 2, color);
      ab->drawPixel(x + 1, y + 3, color);
      ab->drawPixel(x + 3, y + 3, color);
      ab->drawPixel(x + 1, y + 4, color);
      ab->drawPixel(x + 3, y + 4, color);
      ab->drawPixel(x + 1, y + 5, color);
      ab->drawPixel(x + 2, y + 5, color);
      ab->drawPixel(x + 3, y + 5, color);
      break;
    case 1:
      ab->drawPixel(x + 3, y + 1, color);
      ab->drawPixel(x + 3, y + 2, color);
      ab->drawPixel(x + 3, y + 3, color);
      ab->drawPixel(x + 3, y + 4, color);
      ab->drawPixel(x + 3, y + 5, color);
      break;
    case 2:
      ab->drawPixel(x + 1, y + 1, color);
      ab->drawPixel(x + 2, y + 1, color);
      ab->drawPixel(x + 3, y + 1, color);
      ab->drawPixel(x + 3, y + 2, color);
      ab->drawPixel(x + 1, y + 3, color);
      ab->drawPixel(x + 2, y + 3, color);
      ab->drawPixel(x + 3, y + 3, color);
      ab->drawPixel(x + 1, y + 4, color);
      ab->drawPixel(x + 1, y + 5, color);
      ab->drawPixel(x + 2, y + 5, color);
      ab->drawPixel(x + 3, y + 5, color);
      break;
    case 3:
      ab->drawPixel(x + 1, y + 1, color);
      ab->drawPixel(x + 2, y + 1, color);
      ab->drawPixel(x + 3, y + 1, color);
      ab->drawPixel(x + 3, y + 2, color);
      ab->drawPixel(x + 1, y + 3, color);
      ab->drawPixel(x + 2, y + 3, color);
      ab->drawPixel(x + 3, y + 3, color);
      ab->drawPixel(x + 3, y + 4, color);
      ab->drawPixel(x + 1, y + 5, color);
      ab->drawPixel(x + 2, y + 5, color);
      ab->drawPixel(x + 3, y + 5, color);
      break;
    case 4:
      ab->drawPixel(x + 1, y + 1, color);
      ab->drawPixel(x + 3, y + 1, color);
      ab->drawPixel(x + 1, y + 2, color);
      ab->drawPixel(x + 3, y + 2, color);
      ab->drawPixel(x + 1, y + 3, color);
      ab->drawPixel(x + 2, y + 3, color);
      ab->drawPixel(x + 3, y + 3, color);
      ab->drawPixel(x + 3, y + 4, color);
      ab->drawPixel(x + 3, y + 5, color);
      break;
    case 5:
      ab->drawPixel(x + 1, y + 1, color);
      ab->drawPixel(x + 2, y + 1, color);
      ab->drawPixel(x + 3, y + 1, color);
      ab->drawPixel(x + 1, y + 2, color);
      ab->drawPixel(x + 1, y + 3, color);
      ab->drawPixel(x + 2, y + 3, color);
      ab->drawPixel(x + 3, y + 3, color);
      ab->drawPixel(x + 3, y + 4, color);
      ab->drawPixel(x + 1, y + 5, color);
      ab->drawPixel(x + 2, y + 5, color);
      ab->drawPixel(x + 3, y + 5, color);
      break;
    case 6:
      ab->drawPixel(x + 1, y + 1, color);
      ab->drawPixel(x + 1, y + 2, color);
      ab->drawPixel(x + 1, y + 3, color);
      ab->drawPixel(x + 2, y + 3, color);
      ab->drawPixel(x + 3, y + 3, color);
      ab->drawPixel(x + 1, y + 4, color);
      ab->drawPixel(x + 3, y + 4, color);
      ab->drawPixel(x + 1, y + 5, color);
      ab->drawPixel(x + 2, y + 5, color);
      ab->drawPixel(x + 3, y + 5, color);
      break;
    case 7:
      ab->drawPixel(x + 1, y + 1, color);
      ab->drawPixel(x + 2, y + 1, color);
      ab->drawPixel(x + 3, y + 1, color);
      ab->drawPixel(x + 3, y + 2, color);
      ab->drawPixel(x + 3, y + 3, color);
      ab->drawPixel(x + 3, y + 4, color);
      ab->drawPixel(x + 3, y + 5, color);
      break;
    case 8:
      ab->drawPixel(x + 1, y + 1, color);
      ab->drawPixel(x + 2, y + 1, color);
      ab->drawPixel(x + 3, y + 1, color);
      ab->drawPixel(x + 1, y + 2, color);
      ab->drawPixel(x + 3, y + 2, color);
      ab->drawPixel(x + 1, y + 3, color);
      ab->drawPixel(x + 2, y + 3, color);
      ab->drawPixel(x + 3, y + 3, color);
      ab->drawPixel(x + 1, y + 4, color);
      ab->drawPixel(x + 3, y + 4, color);
      ab->drawPixel(x + 1, y + 5, color);
      ab->drawPixel(x + 2, y + 5, color);
      ab->drawPixel(x + 3, y + 5, color);
      break;
    case 9:
      ab->drawPixel(x + 1, y + 1, color);
      ab->drawPixel(x + 2, y + 1, color);
      ab->drawPixel(x + 3, y + 1, color);
      ab->drawPixel(x + 1, y + 2, color);
      ab->drawPixel(x + 3, y + 2, color);
      ab->drawPixel(x + 1, y + 3, color);
      ab->drawPixel(x + 2, y + 3, color);
      ab->drawPixel(x + 3, y + 3, color);
      ab->drawPixel(x + 3, y + 4, color);
      ab->drawPixel(x + 1, y + 5, color);
      ab->drawPixel(x + 2, y + 5, color);
      ab->drawPixel(x + 3, y + 5, color);
      break;
  }
}

void drawSmallNumber(Arduboy* ab, int x, int y, int num, bool white)
{
  int s = num;
  int maxDigit = 2;
  int digit = 0;

  if (s > 99)
  {
    digit = 2;
  }
  if (s == 0)
  {
    digit = 1;
  }
  else
  {
    while (s != 0)
    {
      s /= 10;
      digit++;
    }
  }

  int sb[digit];
  s = num;
  if (s > 99)
  {
    sb[0] = 9;
    sb[1] = 9;
  }
  else
  {
    for (int i = 0; i < maxDigit; i++)
    {
      if (maxDigit - digit > i)
      {
        sb[i] = 0;
      }

      sb[i] = (s % 10);
      s /= 10;
    }
  }

  for (int i = 0; i < digit; i++)
  {
    drawOneSmallNumber(ab, x + (i * 4), y, sb[digit - 1 - i], white);
  }
}


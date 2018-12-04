bool someButtonPressed()
{
  return (ab.pressed(UP_BUTTON)   || ab.pressed(DOWN_BUTTON)  ||
          ab.pressed(LEFT_BUTTON) || ab.pressed(RIGHT_BUTTON) ||
          ab.pressed(A_BUTTON)    || ab.pressed(B_BUTTON));
}

bool rotateUp(byte* target, byte min, byte max)
{
  if (*target == max)
  {
    *target = min;
    return false;
  }
  else
  {
    (*target)++;
    return true;
  }
}

bool rotateDown(byte* target, byte min, byte max)
{
  if (*target == min)
  {
    *target = max;
    return false;
  }
  else
  {
    (*target)--;
    return true;
  }
}

bool addValue(byte* target, byte max)
{
  if (*target <= max - 1)
  {
    (*target)++;
    return true;
  }
  return false;
}

bool subValue(byte* target, byte min)
{
  if (*target >= min + 1)
  {
    (*target)--;
    return true;
  }
  return false;
}

void initArray(byte* ar, byte size)
{
  for (byte i = 0; i < size; i++)
  {
    *ar++ = 0;
  }
}

byte getMinute(long l)
{
  return (byte)(l / 1000 / 60 % 60);
}

String getHMS(long lStop)
{
  byte h = (byte)(lStop / 1000 / 3600);
  byte m = getMinute(lStop);
  byte s = (byte)(lStop / 1000 % 60);

  return String(h) + ":" + ((m < 10) ? "0" + String(m) : String(m)) + ":" + ((s < 10) ? "0" + String(s) : String(s));
}

void checkAlarm()
{
  if (!isTimer || tStop >= millis())
  {
    return;
  }

  pressPole = true;
  isTimer = false;
  tStop = 0;
  byte toneCnt = 0;
  long toneStart = millis();
  while (!someButtonPressed())
  {
    int time = millis() - toneStart;
    if ((toneCnt == 0 && time >= 0) || (toneCnt == 1 && time >= 250))
    {
      toneCnt++;
      if (setting.isLedTimer)
      {
        ab.setRGBled(1, 0, 0);
      }
      if (setting.isSoundTimer)
      {
        ab.tunes.tone(setting.baseTone, 200);
      }
    }
    else if (toneCnt == 2)
    {
      toneCnt++;
      ab.setRGBled(0, 0, 0);
    }
    else if (time > 1000)
    {
      toneCnt = 0;
      toneStart = millis();
    }
  }

  ab.setRGBled(0, 0, 0);
  pressPole = true;
  pressFirst = false;
}

void drawArrowLeft(byte x, byte y, bool white)
{
  ab.drawLine(x + 0, y + 0, x + 0, y + 6, white);
  ab.drawLine(x + 1, y + 1, x + 1, y + 5, white);
  ab.drawLine(x + 2, y + 2, x + 2, y + 4, white);
  ab.drawLine(x + 3, y + 3, x + 3, y + 3, white);
}

void drawArrowTop(byte x, byte y, bool white)
{
  ab.drawLine(x + 3, y + 0, x + 3, y + 0, white);
  ab.drawLine(x + 2, y + 1, x + 4, y + 1, white);
  ab.drawLine(x + 1, y + 2, x + 5, y + 2, white);
  ab.drawLine(x + 0, y + 3, x + 6, y + 3, white);
}

void drawArrowDown(byte x, byte y, bool white)
{
  ab.drawLine(x + 3, y + 3, x + 3, y + 3, white);
  ab.drawLine(x + 2, y + 2, x + 4, y + 2, white);
  ab.drawLine(x + 1, y + 1, x + 5, y + 1, white);
  ab.drawLine(x + 0, y + 0, x + 6, y + 0, white);
}

void drawText(byte a, byte b, byte fs, String mes)
{
  ab.setCursor(a, b);
  ab.setTextSize(fs);
  ab.print(mes);
}

void drawText(byte a, byte b, byte fs, int mes)
{
  ab.setCursor(a, b);
  ab.setTextSize(fs);
  ab.print(mes);
}

void drawText(byte a, byte b, byte fs, char* mes)
{
  ab.setCursor(a, b);
  ab.setTextSize(fs);
  ab.print(mes);
}

void drawTextInvert(byte a, byte b, byte fs, int num)
{
  bool isMinus = (num < 0);
  char str[10] = {0};
  int i = 0;

  if (isMinus)
  {
    num *= -1;
  }

  do
  {
    str[i++] = num % 10 + 0x10;
    num /= 10;
  }
  while (num > 0);

  if (isMinus)
  {
    str[i++] = '-';
  }
  str[i] = '\0';

  drawText(a, b, fs, str);
}

void drawText(byte a, byte b, byte fs, int num, bool isInvert)
{
  if (isInvert)
  {
    drawTextInvert(a, b, fs, num);
  }
  else
  {
    drawText(a, b, fs, num);
  }
}

void drawOneSmallNumber(byte x, byte y, byte number, bool color)
{
  switch (number)
  {
    case 0:
      ab.drawPixel(x + 1, y + 1, color);
      ab.drawPixel(x + 2, y + 1, color);
      ab.drawPixel(x + 3, y + 1, color);
      ab.drawPixel(x + 1, y + 2, color);
      ab.drawPixel(x + 3, y + 2, color);
      ab.drawPixel(x + 1, y + 3, color);
      ab.drawPixel(x + 3, y + 3, color);
      ab.drawPixel(x + 1, y + 4, color);
      ab.drawPixel(x + 3, y + 4, color);
      ab.drawPixel(x + 1, y + 5, color);
      ab.drawPixel(x + 2, y + 5, color);
      ab.drawPixel(x + 3, y + 5, color);
      break;
    case 1:
      ab.drawPixel(x + 3, y + 1, color);
      ab.drawPixel(x + 3, y + 2, color);
      ab.drawPixel(x + 3, y + 3, color);
      ab.drawPixel(x + 3, y + 4, color);
      ab.drawPixel(x + 3, y + 5, color);
      break;
    case 2:
      ab.drawPixel(x + 1, y + 1, color);
      ab.drawPixel(x + 2, y + 1, color);
      ab.drawPixel(x + 3, y + 1, color);
      ab.drawPixel(x + 3, y + 2, color);
      ab.drawPixel(x + 1, y + 3, color);
      ab.drawPixel(x + 2, y + 3, color);
      ab.drawPixel(x + 3, y + 3, color);
      ab.drawPixel(x + 1, y + 4, color);
      ab.drawPixel(x + 1, y + 5, color);
      ab.drawPixel(x + 2, y + 5, color);
      ab.drawPixel(x + 3, y + 5, color);
      break;
    case 3:
      ab.drawPixel(x + 1, y + 1, color);
      ab.drawPixel(x + 2, y + 1, color);
      ab.drawPixel(x + 3, y + 1, color);
      ab.drawPixel(x + 3, y + 2, color);
      ab.drawPixel(x + 1, y + 3, color);
      ab.drawPixel(x + 2, y + 3, color);
      ab.drawPixel(x + 3, y + 3, color);
      ab.drawPixel(x + 3, y + 4, color);
      ab.drawPixel(x + 1, y + 5, color);
      ab.drawPixel(x + 2, y + 5, color);
      ab.drawPixel(x + 3, y + 5, color);
      break;
    case 4:
      ab.drawPixel(x + 1, y + 1, color);
      ab.drawPixel(x + 3, y + 1, color);
      ab.drawPixel(x + 1, y + 2, color);
      ab.drawPixel(x + 3, y + 2, color);
      ab.drawPixel(x + 1, y + 3, color);
      ab.drawPixel(x + 2, y + 3, color);
      ab.drawPixel(x + 3, y + 3, color);
      ab.drawPixel(x + 3, y + 4, color);
      ab.drawPixel(x + 3, y + 5, color);
      break;
    case 5:
      ab.drawPixel(x + 1, y + 1, color);
      ab.drawPixel(x + 2, y + 1, color);
      ab.drawPixel(x + 3, y + 1, color);
      ab.drawPixel(x + 1, y + 2, color);
      ab.drawPixel(x + 1, y + 3, color);
      ab.drawPixel(x + 2, y + 3, color);
      ab.drawPixel(x + 3, y + 3, color);
      ab.drawPixel(x + 3, y + 4, color);
      ab.drawPixel(x + 1, y + 5, color);
      ab.drawPixel(x + 2, y + 5, color);
      ab.drawPixel(x + 3, y + 5, color);
      break;
    case 6:
      ab.drawPixel(x + 1, y + 1, color);
      ab.drawPixel(x + 1, y + 2, color);
      ab.drawPixel(x + 1, y + 3, color);
      ab.drawPixel(x + 2, y + 3, color);
      ab.drawPixel(x + 3, y + 3, color);
      ab.drawPixel(x + 1, y + 4, color);
      ab.drawPixel(x + 3, y + 4, color);
      ab.drawPixel(x + 1, y + 5, color);
      ab.drawPixel(x + 2, y + 5, color);
      ab.drawPixel(x + 3, y + 5, color);
      break;
    case 7:
      ab.drawPixel(x + 1, y + 1, color);
      ab.drawPixel(x + 2, y + 1, color);
      ab.drawPixel(x + 3, y + 1, color);
      ab.drawPixel(x + 3, y + 2, color);
      ab.drawPixel(x + 3, y + 3, color);
      ab.drawPixel(x + 3, y + 4, color);
      ab.drawPixel(x + 3, y + 5, color);
      break;
    case 8:
      ab.drawPixel(x + 1, y + 1, color);
      ab.drawPixel(x + 2, y + 1, color);
      ab.drawPixel(x + 3, y + 1, color);
      ab.drawPixel(x + 1, y + 2, color);
      ab.drawPixel(x + 3, y + 2, color);
      ab.drawPixel(x + 1, y + 3, color);
      ab.drawPixel(x + 2, y + 3, color);
      ab.drawPixel(x + 3, y + 3, color);
      ab.drawPixel(x + 1, y + 4, color);
      ab.drawPixel(x + 3, y + 4, color);
      ab.drawPixel(x + 1, y + 5, color);
      ab.drawPixel(x + 2, y + 5, color);
      ab.drawPixel(x + 3, y + 5, color);
      break;
    case 9:
      ab.drawPixel(x + 1, y + 1, color);
      ab.drawPixel(x + 2, y + 1, color);
      ab.drawPixel(x + 3, y + 1, color);
      ab.drawPixel(x + 1, y + 2, color);
      ab.drawPixel(x + 3, y + 2, color);
      ab.drawPixel(x + 1, y + 3, color);
      ab.drawPixel(x + 2, y + 3, color);
      ab.drawPixel(x + 3, y + 3, color);
      ab.drawPixel(x + 3, y + 4, color);
      ab.drawPixel(x + 1, y + 5, color);
      ab.drawPixel(x + 2, y + 5, color);
      ab.drawPixel(x + 3, y + 5, color);
      break;
  }
}

void drawSmallNumber(byte x, byte y, byte num, bool color)
{
  byte s = num;
  byte maxDigit = 2;
  byte digit = 0;

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

  byte sb[digit];
  s = num;
  if (s > 99)
  {
    sb[0] = 9;
    sb[1] = 9;
  }
  else
  {
    for (byte i = 0; i < maxDigit; i++)
    {
      if (maxDigit - digit > i)
      {
        sb[i] = 0;
      }

      sb[i] = (s % 10);
      s /= 10;
    }
  }

  for (byte i = 0; i < digit; i++)
  {
    drawOneSmallNumber(x + (i * 4), y, sb[digit - 1 - i], color);
  }
}

void drawBigDice(byte x, byte y, byte number)
{
  if (number == 0)
  {
    return;
  }

  ab.fillRect(x, y, 8, 8, WHITE);

  switch (number)
  {
    case 1:
      ab.drawRect(x + 3, y + 3, 2, 2, BLACK);
      break;
    case 2:
      ab.drawRect(x + 5, y + 1, 2, 2, BLACK);
      ab.drawRect(x + 1, y + 5, 2, 2, BLACK);
      break;
    case 3:
      ab.drawRect(x + 3, y + 3, 2, 2, BLACK);
      ab.drawRect(x + 5, y + 1, 2, 2, BLACK);
      ab.drawRect(x + 1, y + 5, 2, 2, BLACK);
      break;
    case 4:
      ab.drawRect(x + 1, y + 1, 2, 2, BLACK);
      ab.drawRect(x + 5, y + 1, 2, 2, BLACK);
      ab.drawRect(x + 1, y + 5, 2, 2, BLACK);
      ab.drawRect(x + 5, y + 5, 2, 2, BLACK);
      break;
    case 5:
      ab.drawRect(x + 3, y + 3, 2, 2, BLACK);
      ab.drawRect(x + 1, y + 1, 2, 2, BLACK);
      ab.drawRect(x + 5, y + 1, 2, 2, BLACK);
      ab.drawRect(x + 1, y + 5, 2, 2, BLACK);
      ab.drawRect(x + 5, y + 5, 2, 2, BLACK);
      break;
    case 6:
      ab.drawRect(x + 1, y + 0, 2, 2, BLACK);
      ab.drawRect(x + 1, y + 3, 2, 2, BLACK);
      ab.drawRect(x + 1, y + 6, 2, 2, BLACK);
      ab.drawRect(x + 5, y + 0, 2, 2, BLACK);
      ab.drawRect(x + 5, y + 3, 2, 2, BLACK);
      ab.drawRect(x + 5, y + 6, 2, 2, BLACK);
      break;
  }
}

char* getBlackWhite(byte value)
{
  return value == 0x00 ? "BLACK" : "WHITE";
}

char* getOnOff(byte value)
{
  return value == 0x00 ? "OFF" : "0N";
}

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

class TimeFormat
{
  public:
    long defaultMillis = 0;
    short defaultHour = 0;
    short defaultMinute = 0;
    short defaultSecond = 0;

    long stopMillis = 0;
    short stopHour = 0;
    short stopMinute = 0;
    short stopSecond = 0;

    short h = 0;
    short m = 0;
    short s = 0;

    void TimeFormat::addHour(short value)
    {
      stopHour += value;
      while (stopHour >= 24)
      {
        stopHour -= 24;
      }
      while (stopHour < 0)
      {
        stopHour += 24;
      }
    }

    void TimeFormat::addMinute(short value)
    {
      stopMinute += value;
      while (stopMinute >= 60)
      {
        stopMinute -= 60;
        if (stopHour < 24)
        {
          stopHour++;
        }
      }
      while (stopMinute < 0 && stopHour >= 0)
      {
        stopMinute += 60;
        if (stopHour > 0)
        {
          stopHour--;
        }
      }
    }

    void TimeFormat::addSecond(short value)
    {
      stopSecond += value;
      while (stopSecond >= 60)
      {
        stopSecond -= 60;
        if (stopMinute < 60)
        {
          stopMinute++;
        }
      }
      while (stopSecond < 0 && (stopMinute > 0 || stopHour > 0))
      {
        stopSecond += 60;
        if (stopMinute > 0)
        {
          stopMinute--;
        }
      }
    }

    void TimeFormat::setDefaultTime()
    {
      defaultMillis = millis();

      unsigned long t = defaultMillis;
      t /= 1000;
      defaultHour = t / 3600;
      t %= 3600;
      defaultMinute = t / 60;
      t %= 60;
      defaultSecond = t;
    };

    void TimeFormat::setStopTime()
    {
      stopMillis = millis();

      unsigned long t = stopMillis;
      t /= 1000;
      defaultHour = t / 3600;
      t %= 3600;
      defaultMinute = t / 60;
      t %= 60;
      defaultSecond = t;

      stopHour = defaultHour;
      stopMinute = defaultMinute;
      stopSecond = defaultSecond;
    }

    String TimeFormat::getDefaultTimeString()
    {
      return getHMS(defaultHour, defaultMinute, defaultSecond);
    }

    long TimeFormat::getSubMillisecond()
    {
      return defaultMillis - stopMillis;
    }

    String TimeFormat::getSubTimeString()
    {
      h = defaultHour - stopHour;
      m = defaultMinute - stopMinute;
      s = defaultSecond - stopSecond;

      while (s >= 60)
      {
        s -= 60;
        m++;
      }
      while (s < 0)
      {
        m--;
        s += 60;
      }

      while (m >= 60)
      {
        m -= 60;
        h++;
      }
      while (m < 0)
      {
        h--;
        m += 60;
      }

      while (h >= 24)
      {
        h -= 24;
      }
      while (h < 0)
      {
        h = 0;
      }

      return getHMS();
    }

    String TimeFormat::getHMS()
    {
      return String(h) + ":" + ((m < 10) ? "0" + String(m) : String(m)) + ":" + ((s < 10) ? "0" + String(s) : String(s));
    }
    
    String TimeFormat::getHMS(byte hh, byte mm, byte ss)
    {
      return String(hh) + ":" + ((mm < 10) ? "0" + String(mm) : String(mm)) + ":" + ((ss < 10) ? "0" + String(ss) : String(ss));
    }
};

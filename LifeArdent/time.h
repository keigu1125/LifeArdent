class TimeFormat
{
  public: long defaultMillis = 0;
  public: int defaultHour = 0;
  public: int defaultMinute = 0;
  public: int defaultSecond = 0;

  public: long stopMillis = 0;
  public: int stopHour = 0;
  public: int stopMinute = 0;
  public: int stopSecond = 0;

    void TimeFormat::addTime(TimeFormat* tp)
    {
      tp->addHour(stopHour);
      tp->addMinute(stopMinute);
      tp->addSecond(stopSecond);
    }

    void TimeFormat::subTime(TimeFormat* tp)
    {
      tp->addHour(stopHour * -1);
      tp->addMinute(stopMinute * -1);
      tp->addSecond(stopSecond * -1);
    }

    void TimeFormat::addHour(int value)
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

    void TimeFormat::addMinute(int value)
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

    void TimeFormat::addSecond(int value)
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
      String strHour   = String(defaultHour);
      String strMin    = (defaultMinute < 10) ? "0" + String(defaultMinute) : String(defaultMinute);
      String strSecond = (defaultSecond < 10) ? "0" + String(defaultSecond) : String(defaultSecond);

      String strTime = strHour + ":" + strMin + ":" + strSecond;

      return strTime;
    }

    int TimeFormat::getSubHour()
    {
      return getSubMinute() / 60;
    }

    int TimeFormat::getSubMinute()
    {
      return getSubSecond() / 60;
    }

    int TimeFormat::getSubSecond()
    {
      return (getSubMillisecond()) / 1000;
    }

    long TimeFormat::getSubMillisecond()
    {
      return defaultMillis - stopMillis;
    }

    String TimeFormat::getSubTimeString()
    {
      int h = defaultHour - stopHour;
      int m = defaultMinute - stopMinute;
      int s = defaultSecond - stopSecond;

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

      String strHour   = String(h);
      String strMin    = (m < 10) ? "0" + String(m) : String(m);
      String strSecond = (s < 10) ? "0" + String(s) : String(s);

      String strTime = strHour + ":" + strMin + ":" + strSecond;

      return strTime;
    }
};


class TimeFormat
{
  private:
    long now = 0;
    long stop = 0;
    long interval = 0;    
  public:    
    void TimeFormat::reset()
    {
      now = 0;
      stop = 0;
      interval = 0;
    }
  
    void TimeFormat::setNow()
    {
      now = millis();
      interval = now - stop;
    }

    void TimeFormat::setStop()
    {
      stop = millis();
    }

    byte TimeFormat::getHour()
    {
      return (byte)(interval / 1000 / 3600);
    }

    byte TimeFormat::getMinute()
    {
      return (byte)(interval / 1000 / 60 % 60);
    }

    byte TimeFormat::getSecond()
    {
      return (byte)(interval / 1000 % 60);
    }
    
    int TimeFormat::getMillis()
    {
      return (interval >= 1000) ? 1000 : interval % 1000;
    }

    void TimeFormat::addHour(byte value)
    {
      stop += value * 3600 * 1000;
    }

    void TimeFormat::addMinute(byte value)
    {
      stop += value * 60 * 1000;
    }

    void TimeFormat::addSecond(byte value)
    {
      stop += value * 1000;
    }

    void TimeFormat::addInterval()
    {
      stop -= interval;
    }

    String TimeFormat::getHMS()
    {
      byte h = getHour();
      byte m = getMinute();
      byte s = getSecond();

      return getHMS(h, m, s);
    }

    String TimeFormat::getHMS(byte h, byte m, byte s)
    {
      return String(h) + ":" + ((m < 10) ? "0" + String(m) : String(m)) + ":" + ((s < 10) ? "0" + String(s) : String(s));
    }
};

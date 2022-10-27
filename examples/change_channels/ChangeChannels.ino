#include <IBUS_receiver.h>

const int size_ch = 6;
const uint16_t min_val = 1000;
const uint16_t max_val = 2000;
IBUS_receiver rcvr;
uint16_t ch[size_ch];
uint16_t val;
bool increase;

void setup()
{
  Serial2.begin(115200);
  rcvr.begin(&Serial2);
  val = 1000;
  increase = true;
}

void loop()
{
  if (increase)
  {
    val += 5;
    if (val >= max_val)
    {
      increase = false;
    }
  }
  else
  {
    val -= 5;
    if (val <= min_val)
    {
      increase = true;
    }
  }
  for (int i = 0; i < size_ch; i++)
  {
    ch[i] = val;
  }
  rcvr.set_ch(ch, size_ch);
  rcvr.send_data();
  delay(7);
}

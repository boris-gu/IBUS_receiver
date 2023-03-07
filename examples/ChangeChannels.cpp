/*
 * ChangeChannels
 *
 * Changes value of the first 6 IBUS channels from 1000 to 2000
 */
#include <HardwareSerial.h>
#include <IBUS_receiver.h>

const int size_ch = 6;
const uint16_t min_val = 1000;
const uint16_t max_val = 2000;
IBUS_receiver rcvr;
uint16_t ch[size_ch];
uint16_t val;
bool increase;
//
HardwareSerial MySerial(1);
//
void setup()
{
  //
  MySerial.begin(115200, SERIAL_8N1, 18, 17);
  //MySerial.begin(115200, SERIAL_8N1, 44, 43);
  //
  //Serial.begin(115200);
  while (!MySerial)
  {
  }
  rcvr.begin(&MySerial);
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

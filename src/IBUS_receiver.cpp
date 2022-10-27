#include <Arduino.h>
#include "IBUS_receiver.h"

IBUS_receiver::IBUS_receiver()
{
  _is_begin = false;
  _header1 = 0x20;
  _header2 = 0x40;
  for (int i = 0; i < TOTAL_CH; i++)
  {
    _channels[i] = 1234;
  }
}

bool IBUS_receiver::begin(Stream *Serial_IBUS)
{
  if (_is_begin)
  {
    return false;
  }
  _Serial_IBUS = Serial_IBUS;
  _is_begin = true;
  return true;
}

bool IBUS_receiver::set_ch(uint16_t array[], size_t num_of_ch)
{
  if (!_is_begin)
  {
    return false;
  }
  for (int i = 0; i < num_of_ch && i < TOTAL_CH; i++)
  {
    _channels[i] = array[i];
  }
  _calc_checksum();
  return true;
}

bool IBUS_receiver::send_data()
{
  if (!_is_begin)
  {
    return false;
  }
  _Serial_IBUS->write(_header1);
  _Serial_IBUS->write(_header2);
  _Serial_IBUS->write((uint8_t *)&_channels, sizeof(_channels));
  _Serial_IBUS->write((uint8_t *)&_checksum, sizeof(uint16_t));
  return true;
}

void IBUS_receiver::_calc_checksum()
{
  _checksum = 0xFFFF;
  _checksum -= _header1;
  _checksum -= _header2;
  for (int i = 0; i < TOTAL_CH; i++)
  {
    _checksum -= _channels[i] & 0xFF;
    _checksum -= (_channels[i] >> 8) & 0xFF;
  }
}
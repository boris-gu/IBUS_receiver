/*
 * Library for simulating a IBUS RC receiver.
 * connect your microcontroller to flight controller and use it as a receiver.
 *
 * https://www.flyskytech.com/info_detail/18.html
 * https://github.com/betaflight/betaflight/wiki/Single-wire-FlySky-%28IBus%29-telemetry
 *
 * created by Gubanov Boris, 25.10.2022
 */
#ifndef IBUS_RECEIVER_h
#define IBUS_RECEIVER_h
#define TOTAL_CH 14

#include <Arduino.h>

class IBUS_receiver
{
public:
  IBUS_receiver();
  bool begin(Stream *Serial_IBUS);
  bool set_ch(uint16_t array[], size_t num_of_ch);
  bool send_data();

private:
  Stream *_Serial_IBUS;
  bool _is_begin;
  // DATA
  uint8_t _header1;
  uint8_t _header2;
  uint16_t _channels[TOTAL_CH];
  uint16_t _checksum;

  void _calc_checksum();
};

#endif
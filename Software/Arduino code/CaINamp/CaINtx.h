#ifndef CAINTX_H
#define CAINTX_H

#include <Arduino.h>

#define CaINTxGPIO PIO_PC23B_PWML6  //  DigitalPin 7 -> PC23 PWML6_PC23 => PWM_CH6
#define CaINOPWMSW 2
#define OnRadioFlag HIGH
#define OffRadioFlag LOW


byte Address_Node0[8] = { 0, 1, 1, 0, 0, 1, 0, 1 };
byte Address_Node1[8] = { 0, 0, 1, 0, 0, 1, 0, 1 };
byte Address_Node2[8] = { 0, 0, 1, 0, 1, 1, 0, 1 };
byte Address_Node3[8] = { 0, 1, 0, 0, 1, 1, 0, 1 };
byte Address_Node4[8] = { 0, 1, 1, 0, 1, 0, 1, 1 };
byte Address_Node5[8] = { 0, 0, 1, 1, 0, 0, 1, 1 };
volatile boolean state;

const uint32_t BitRate5khz = 100;
const uint8_t BitRate1khz = 1;

/* Generate the PWM (42 MHz) */
const uint8_t Period42Mhz = 2;
const uint8_t Duty42Mhz = 1;

void Enable_CarrierPWM(uint8_t Period, uint8_t Duty);
bool pwmEnable_CarrierPWM(uint8_t Period, uint8_t Duty);
void Disable_CarrierPWM();
bool pwmDisable_CarrierPWM(void);
void Ascii_to_BinaryAarray(char ascii, uint8_t arr[8]);
void Send_sync(int cycles);
boolean Send_load(byte start[], boolean state);
bool pwmSend_load(byte start[], bool state);
void Send_bytes(byte AddressNode[], byte byteload0, byte byteload1, byte byteload2, byte byteload3, byte byteload4, byte byteload5);
void pwmSend_bytes(byte byteload0, byte byteload1, byte byteload2, byte byteload3, byte byteload4, byte byteload5);
#endif

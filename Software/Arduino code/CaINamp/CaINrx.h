#ifndef CAINRX_H
#define CAINRX_H
#include <Arduino.h>

#define CaINRxGPIO  6
const int packetsize = 48;
byte payload[packetsize];
uint32_t CaINBufferSize = 0;
byte CaINBuffer[200];

//
//const  uint32_t Original_T = 400;
//const  uint32_t Tolerance_T = 350;
//const  uint32_t TimeOut = Original_T + Tolerance_T;
//const  uint32_t PeriodDiff01 = Original_T - Tolerance_T;
//const  uint32_t PeriodDiff = 360;


const  uint32_t Original_T = 100;
const  uint32_t Tolerance_T = 50;
const  uint32_t TimeOut = Original_T + Tolerance_T;
const  uint32_t PeriodDiff01 = Original_T - Tolerance_T;
const  uint32_t PeriodDiff = 60;

byte Address8bits0[8] = { 0, 1, 1, 0, 0, 1, 0, 1 };
byte Address8bits1[8] = { 0, 0, 1, 0, 0, 1, 0, 1 };
byte Address8bits2[8] = { 0, 0, 1, 0, 1, 1, 0, 1 };
byte Address8bits3[8] = { 0, 1, 0, 0, 1, 1, 0, 1 };
byte Address8bits4[8] = { 0, 1, 1, 0, 1, 0, 1, 1 };
byte Address8bits5[8] = { 0, 0, 1, 1, 0, 0, 1, 1 };

void Read_bytes(byte load[]);
void Seek_Address8bits(byte Address8bits[]);
byte Read_oneBit(long *start_Time, boolean *init_state);
byte array_to_ascii(byte arr[]);


#endif

#include "CaINrx.h"



void Read_bytes(byte load[])
{
  CaINBufferSize =0; 
  byte testAscii; 
  boolean init_state = digitalReadDirect(CaINRxGPIO);
  long Address8bits_time = micros();

  for (int i=0;i<packetsize;i++)
  {
    load[i]= Read_oneBit(&Address8bits_time, &init_state);
//    Serial.print(load[i]);
//    // *************************** //
//    // The following code just for 20231016 demo test //
//    CaINBuffer[CaINBufferSize] = load[i];
//    CaINBufferSize++;
//    if(CaINBufferSize==8){
//      testAscii = array_to_ascii(CaINBuffer);
//      Serial.print((char)testAscii);
//      Serial.println();
//      CaINBufferSize=0;
    }
    // *************************** //
  }
//  digitalWriteDirect(CaINBeep,HIGH);
//  delay(10);
//  digitalWriteDirect(CaINBeep,LOW);
// } 

void Seek_Address8bits(byte Address8bits[])
/*seek for the Address8bits signal*//*this is a blocking funtion*/
{
  int i=0;
  boolean init_state = digitalReadDirect(CaINRxGPIO);
  long start_Time = micros();
  do
  {  
    if (Read_oneBit(&start_Time, &init_state)==Address8bits[i]) {i++;}
    else {i=0;}
  }  
  while (i<8);
  //Serial.println(i);
  return;
}

byte Read_oneBit(long *start_Time, boolean *init_state)
{
   long Time_delta;
   long new_time;
   long last_edge_time = *start_Time;
   boolean state = *init_state;

do{
    while (state == digitalReadDirect(CaINRxGPIO)) {}
    new_time = micros();

    Time_delta = new_time-*start_Time;
    
    if (Time_delta >= TimeOut)
    {
      //Serial.println(Time_delta);
      *start_Time = new_time;
      return 3;
    }
    else
    {
       state = !state;
    }
    
    if((Time_delta >= PeriodDiff))
    {
      *start_Time = new_time;
      *init_state = state;
      return (byte)state;
    }
    else {
      last_edge_time = new_time;
    }
  }
  while (true);
/****************************/
}

byte array_to_ascii(byte arr[])
/*utility to convert an array of 8 bits to ascii code*/
{
  byte ascii=0;
  for (int i=7;i>=0;i--)
  {
    ascii = ascii << 1;
    ascii = arr[i] | ascii; 
  }
  return ascii;
}

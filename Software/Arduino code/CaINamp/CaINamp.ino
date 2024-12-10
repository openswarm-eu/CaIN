#include "CaINtx.h" 
#include "CaINrx.h"

#define CaINTxRxSwitch 8
#define CaINSwitchGPIO 4
#define CaINBeep 13

volatile boolean TRflag;

inline boolean digitalWriteDirect(int pin, boolean val){
  if(val) g_APinDescription[pin].pPort -> PIO_SODR = g_APinDescription[pin].ulPin;
  else    g_APinDescription[pin].pPort -> PIO_CODR = g_APinDescription[pin].ulPin;
  if(val == HIGH) return OnRadioFlag;
  else return OffRadioFlag;
}

inline int digitalReadDirect(int pin){
  return !!(g_APinDescription[pin].pPort -> PIO_PDSR & g_APinDescription[pin].ulPin);
}

void setup() {
  TRflag = HIGH;
 // TRflag = LOW;  
  
  //pinMode(CaINOPWMSW, OUTPUT);
  //pinMode(CaINTxRxSwitch, OUTPUT);
  //pinMode(CaINBeep, OUTPUT);
  pinMode(CaINRxGPIO,INPUT);
  pinMode(CaINSwitchGPIO, OUTPUT);  
  digitalWrite(CaINSwitchGPIO,LOW);
  //digitalWriteDirect(CaINBeep,LOW);
//  Serial.begin(250000);
//  Serial.println("Receiver OK");
//  if(TRflag){
//    Serial.begin(250000);
//    digitalWriteDirect(CaINSwitchGPIO, LOW); 
//    //digitalWriteDirect(CaINOPWMSW,LOW);   // Diable PWM 
//    Serial.println("Receiver OK");
//    
//  }
//  else {
//    pwmDisable_CarrierPWM();
//    delay(1);
//    //digitalWriteDirect(CaINOPWMSW,HIGH);   // Enable PWM 
//    digitalWriteDirect(CaINSwitchGPIO, HIGH);  
//    pwmEnable_CarrierPWM(Period42Mhz,Duty42Mhz);
//  }
  
//  delay(2000);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(TRflag){
        Seek_Address8bits(Address8bits0);
        //Serial.println("Node Address OK");
        Read_bytes(payload);
        digitalWriteDirect(CaINSwitchGPIO, HIGH); 
        pwmSend_bytes('0', 'A', 'B' , 'C', 'D', 'a');
        //delay(1000); 
 //       delay(1000);
//        delay(5000);
        TRflag=LOW; 
  }
  else {
//    pwmDisable_CarrierPWM();
//    delay(1);
    //digitalWriteDirect(CaINOPWMSW,HIGH);   // Enable PWM 
    //digitalWriteDirect(CaINSwitchGPIO, HIGH);  
   // pwmEnable_CarrierPWM(Period42Mhz,Duty42Mhz);
//    digitalWriteDirect(CaINSwitchGPIO, HIGH);  
    pwmSend_bytes('0', 'A', 'B' , 'C', 'D', 'a');
    delay(1000);
  }
}
//if(uint8_t i =0; i<10;i++){
//}

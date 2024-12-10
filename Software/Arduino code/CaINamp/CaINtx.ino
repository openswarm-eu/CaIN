#include "CaINtx.h"



// ------------------------------------------------------------------------
// Trun on the Radio
// ------------------------------------------------------------------------
// Generate the PWM (42 MHz) as Carrier Frequency From 38.6.5 PWM Controller Operations //
// pin_traits_specialization(pwm_pin::PWML6_PC23, PIOC, PIO_PC23B_PWML6, ID_PIOC, PIO_PERIPH_B, PIO_DEFAULT,  PWM_CH6,true  );

void Enable_CarrierPWM(uint8_t Period, uint8_t Duty) {
  /* Activate clock for PWM controller from PMC, PWM ID =36 ->*/
  REG_PMC_PCER1 = 1 << 4;
  // Activate peripheral functions for pin -> Datasheet 31.7.2 & 31.5.2&3)
  REG_PIOC_PDR |= CaINTxGPIO;
  REG_PIOC_ABSR |= CaINTxGPIO;
  /*   ----------------The following is for configure the PWM ----------------*/
  //38.7.1 Select the MCK (Master clock 84Mhz)
  REG_PWM_CLK = 0;
  //38.7.37 PWM Channel Mode Register PWM channel 6 (pin7) -> (CPOL = 0)  left-aligned
  REG_PWM_CMR6 = 0 << 9;
  //38.7.40 PWM Channel Period Register (16 bits -> Period / 84 = Frequency Output )
  REG_PWM_CPRD6 = Period;
  //38.7.38 PWM Channel Duty Cycle Register
  REG_PWM_CDTY6 = Duty;
  //38.7.2 PWM Enable Register
  REG_PWM_ENA = 1 << 6;
  //return OnRadioFlag;
}

// Trun off the RF
void Disable_CarrierPWM() {
  // Disable all GPIO & peripherals Configuration
  REG_PIOC_PDR = 0;
  REG_PIOC_ABSR = 0;
  // Disable the PWM clock and channel
  REG_PMC_PCDR1 = 1 << 4;
  REG_PWM_DIS = 1 << 6;
  //return OffRadioFlag;
}


// ------------------------------------------------------------------------
// Trun on the Radio
// ------------------------------------------------------------------------
// Generate the PWM (42 MHz) as Carrier Frequency From 38.6.5 PWM Controller Operations //
// pin_traits_specialization(pwm_pin::PWML6_PC23, PIOC, PIO_PC23B_PWML6, ID_PIOC, PIO_PERIPH_B, PIO_DEFAULT,  PWM_CH6,true  );
bool pwmEnable_CarrierPWM(uint8_t Period, uint8_t Duty) {
  /* Activate clock for PWM controller from PMC, PWM ID =36 ->*/
  REG_PMC_PCER1 = 1 << 4;
  // Activate peripheral functions for pin -> Datasheet 31.7.2 & 31.5.2&3)
  REG_PIOC_PDR |= CaINTxGPIO;
  REG_PIOC_ABSR |= CaINTxGPIO;
  /*   ----------------The following is for configure the PWM ----------------*/
  //38.7.1 Select the MCK (Master clock 84Mhz)
  REG_PWM_CLK = 0;
  //38.7.37 PWM Channel Mode Register PWM channel 6 (pin7) -> (CPOL = 0)  left-aligned
  REG_PWM_CMR6 = 0 << 9;
  //38.7.40 PWM Channel Period Register (16 bits -> Period / 84 = Frequency Output )
  REG_PWM_CPRD6 = Period;
  //38.7.38 PWM Channel Duty Cycle Register
  REG_PWM_CDTY6 = Duty;
  //38.7.2 PWM Enable Register
  REG_PWM_ENA = 1 << 6;
  return OnRadioFlag;
}

// Trun off the RF
bool pwmDisable_CarrierPWM(void) {
  // Disable all GPIO & peripherals Configuration
  REG_PIOC_PDR = 0;
  REG_PIOC_ABSR = 0;
  // Disable the PWM clock and channel
  REG_PMC_PCDR1 = 1 << 4;
  REG_PWM_DIS = 1 << 6;

  return OffRadioFlag;
}


void Ascii_to_BinaryAarray(char ascii, uint8_t arr[8]) {

  //Serial.print(ascii);
  byte mask = 0b00000001;
  for (int i = 0; i < 8; i++) {
    arr[i] = ascii & mask;
    arr[i] = arr[i] >> i;
    mask = mask << 1;
  }
}


/*send 32 HIGH LOW edges to synchronize with the receptor*/
void pwmSend_sync(int cycles) {
  //sending a sync signal
  for (byte i = 0; i < cycles; i++) {
    Enable_CarrierPWM(Period42Mhz, Duty42Mhz);
    //digitalWrite(RF_PIN,HIGH);
    delayMicroseconds(BitRate5khz);
    Disable_CarrierPWM();
    //digitalWrite(RF_PIN,LOW);
    delayMicroseconds(BitRate5khz);
  }
  Enable_CarrierPWM(Period42Mhz, Duty42Mhz);
  //digitalWrite(RF_PIN,HIGH);
}



/*send 32 HIGH LOW edges to synchronize with the receptor*/
void Send_sync(int cycles) {
  //sending a sync signal
  for (byte i = 0; i < cycles; i++) {
    digitalWriteDirect(CaINOPWMSW,HIGH);
    delayMicroseconds(BitRate5khz);
    digitalWriteDirect(CaINOPWMSW,LOW);
    delayMicroseconds(BitRate5khz);
  }
  digitalWriteDirect(CaINOPWMSW,HIGH);
}

/*send a byte but without sync; state is the current state of the ouput line*/
bool pwmSend_load(byte start[], bool state) {

  for (byte i = 0; i < 8; i++) {
    //Serial.print(start[i]);
    if (start[i] == 1) {
      if (state == LOW) {
        delayMicroseconds(BitRate5khz);
        state = pwmEnable_CarrierPWM(Period42Mhz, Duty42Mhz);
        //digitalWrite(RF_PIN,HIGH);
        //state = HIGH;
      } else  //state==HIGH
      {
        delayMicroseconds(BitRate5khz / 2);
        // digitalWrite(RF_PIN,LOW);
        pwmDisable_CarrierPWM();
        delayMicroseconds(BitRate5khz / 2);
        //digitalWrite(RF_PIN,HIGH);
        state = pwmEnable_CarrierPWM(Period42Mhz, Duty42Mhz);
      }
    } else  //start[i]==0
    {
      if (state == LOW) {
        delayMicroseconds(BitRate5khz / 2);
        //digitalWrite(RF_PIN,HIGH);
        pwmEnable_CarrierPWM(Period42Mhz, Duty42Mhz);
        delayMicroseconds(BitRate5khz / 2);
        // digitalWrite(RF_PIN,LOW);
        state = pwmDisable_CarrierPWM();
      } else  //state==HIGH
      {
        delayMicroseconds(BitRate5khz);
        state = pwmDisable_CarrierPWM();
        // digitalWrite(RF_PIN,LOW);
      }
    }
  }
  return state;
}


/*send a byte but without sync; state is the current state of the ouput line*/
boolean Send_load(byte start[], boolean state) {
  for (byte i = 0; i < 8; i++) {
    //Serial.print(start[i]);
    if (start[i] == 1) {
        if (state == LOW) 
        {
          delayMicroseconds(BitRate5khz);
          state = digitalWriteDirect(CaINOPWMSW,HIGH);
        } 
        else  //state==HIGH
        {
          delayMicroseconds(BitRate5khz / 2);
          state = digitalWriteDirect(CaINOPWMSW,LOW);
          delayMicroseconds(BitRate5khz / 2);
          state = digitalWriteDirect(CaINOPWMSW,HIGH);
        }
    } 
    else  //start[i]==0
    {
        if (state == LOW) 
        {
          delayMicroseconds(BitRate5khz / 2);
          state = digitalWriteDirect(CaINOPWMSW,HIGH);
          delayMicroseconds(BitRate5khz / 2);
          state = digitalWriteDirect(CaINOPWMSW,LOW);
        } 
        else  //state==HIGH
        {
          delayMicroseconds(BitRate5khz);
          state = digitalWriteDirect(CaINOPWMSW,LOW); 
        }
    }
  }
  return state;
}
/*send a sync signal + a start byte + load ; load is an array of 8 bit, no more no less !!*/
void pwmSend_bytes(byte byteload0, byte byteload1,byte byteload2,byte byteload3,byte byteload4,byte byteload5) {

  byte Dataload0Arr[8];
  byte Dataload1Arr[8];
  byte Dataload2Arr[8];
  byte Dataload3Arr[8];
  byte Dataload4Arr[8];
  byte Dataload5Arr[8];

  Ascii_to_BinaryAarray(byteload0, Dataload0Arr);    //change ascii code to bits array
  Ascii_to_BinaryAarray(byteload1, Dataload1Arr);  //change ascii code to bits array
  Ascii_to_BinaryAarray(byteload2, Dataload2Arr); 
  Ascii_to_BinaryAarray(byteload3, Dataload3Arr); 
  Ascii_to_BinaryAarray(byteload4, Dataload4Arr); 
  Ascii_to_BinaryAarray(byteload5, Dataload5Arr);

  // Send 32 cycles for preamble
  pwmSend_sync(32);
  //line must be high after sync
  state = HIGH;
  //send the start message
  state= pwmSend_load(Address_Node1, state);
  // Serial.println();
  state = pwmSend_load(Dataload0Arr, state);
  // Serial.println();
  state = pwmSend_load(Dataload1Arr, state);
  // Serial.println();
  state = pwmSend_load(Dataload2Arr, state);
  // Serial.println();
  state = pwmSend_load(Dataload3Arr, state);
  // Serial.println();
  state = pwmSend_load(Dataload4Arr, state);
  // Serial.println();
  pwmSend_load(Dataload5Arr, state);
  //Serial.println();
  //Send_syncEnd(4);
  pwmDisable_CarrierPWM();
}

/*send a sync signal + a start byte + load ; load is an array of 8 bit, no more no less !!*/
void Send_bytes(byte AddressNode[], byte byteload0, byte byteload1, byte byteload2, byte byteload3, byte byteload4, byte byteload5) {

  byte Dataload0Arr[8];
  byte Dataload1Arr[8];
  byte Dataload2Arr[8];
  byte Dataload3Arr[8];
  byte Dataload4Arr[8];
  byte Dataload5Arr[8];

  Ascii_to_BinaryAarray(byteload0, Dataload0Arr);    //change ascii code to bits array
  Ascii_to_BinaryAarray(byteload1, Dataload1Arr);    //change ascii code to bits array
  Ascii_to_BinaryAarray(byteload2, Dataload2Arr);
  Ascii_to_BinaryAarray(byteload3, Dataload3Arr);
  Ascii_to_BinaryAarray(byteload4, Dataload4Arr);
  Ascii_to_BinaryAarray(byteload5, Dataload5Arr);

  // Send 32 cycles for preamble
  Send_sync(32);
  //line must be high after sync
  state = HIGH;
  //send the start message
  state = Send_load(AddressNode, state);
  //Serial.println();
  state = Send_load(Dataload0Arr, state);
  //Serial.println();
  state = Send_load(Dataload1Arr, state);
  //Serial.println();
  state = Send_load(Dataload2Arr, state);
  //Serial.println();
  state = Send_load(Dataload3Arr, state);
  //Serial.println();
  state = Send_load(Dataload4Arr, state);
  //Serial.println();
  state = Send_load(Dataload5Arr, state);
  //Serial.println();
  //Send_syncEnd(4);
  digitalWriteDirect(CaINOPWMSW,LOW); 
}

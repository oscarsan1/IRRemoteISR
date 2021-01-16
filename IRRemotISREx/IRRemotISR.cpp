/*************************************************
 Created by Oscar San

 See guide at: https://github.com/oscarsan1/IRRemoteISR

 GNU General Public License v3.0

**************************************************/
#include "IRRemotISR.h"

//#define DEBUG 

volatile uint8_t IRRemotISR::BitIndex;
volatile uint32_t IRRemotISR::ISR_Durations[66];
volatile unsigned long IRRemotISR::AntIRMillis;
uint8_t IRRemotISR::_ISRPin;

IRRemotISR::IRRemotISR(uint8_t ISRPin) {
    _ISRPin = ISRPin;
    BitIndex = 0;
    pinMode(_ISRPin, INPUT);
    attachInterrupt(digitalPinToInterrupt(_ISRPin),  IRRemotISR::ISR_IRReceiverChanging, CHANGE);
}

bool IRRemotISR::receivingCode(){
    if (BitIndex!=0) return true;
    else return false;
}

void IRRemotISR::ISR_IRReceiverChanging(void) {
  unsigned long ActMillis = micros();
  if ((ActMillis - AntIRMillis) > 2100) // start or restart code with 2100 us low level pulse 
  {
    if (!digitalRead(_ISRPin))
      BitIndex = 0;
  }

  if (BitIndex < 66)
  {
    ISR_Durations[BitIndex] = ActMillis - AntIRMillis;
    BitIndex++;
  }
  AntIRMillis = ActMillis;

}

uint32_t IRRemotISR::readIR(void)
{
  uint32_t result = 0;
  if (BitIndex == 66) //finished code
  { 
    BitIndex = 0;
    #ifdef DEBUG
        Serial.print(F("ISr durations-> "));
        Serial.println(ISR_Durations[0]); 
        for (uint8_t i = 0; i < 64; i++) {
        Serial.print(ISR_Durations[i+1]); Serial.print(F(" "));
        if (((i+1)%8)==0) Serial.print(F("\n"));
        } 
    #endif
 
    for (uint8_t i = 0; i < 64; i = i + 2)  // coding bits
    {
      uint8_t b = ISR_Durations[2 + i] < 1000 ? 0 : 1;
      result = ((result) << 1) | b;
    }
    if ((result & 0xFF) != (~(result >> 8) & 0xFF)) // check CRC
    {
      #ifdef DEBUG
        Serial.print(F("CRC KO: "));
        Serial.println(result, HEX);
      #endif
      result = 0;
    }

  }
  else if (BitIndex > 0)  // time out. Restart if no bits received in 50 ms
  {
    cli();
    unsigned long AntIRM = AntIRMillis;
    sei();
    if ((micros() - AntIRM) > 50000)
    { 
      BitIndex = 0;
    }
  }
  return result;
}

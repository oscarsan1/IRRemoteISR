/*************************************************
 Created by Oscar San

 See guide at: https://github.com/oscarsan1/IRRemoteISR

 GNU General Public License v3.0

**************************************************/

#include <avr/power.h>
#include <avr/sleep.h>
#include "IRRemotISR.h"

#define IR_PIN 2     // Pin connected to the IR receiver.
#define IR_PIN_VCC 3 // Pin connected to the IR receiver.

IRRemotISR IRRemot = IRRemotISR(IR_PIN);

void setup(void)
{
  pinMode(IR_PIN_VCC, OUTPUT);
  digitalWrite(IR_PIN_VCC, HIGH);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on
  Serial.begin(115200);
  Serial.println("start");
}

void loop(void)
{
  uint32_t result = IRRemot.readIR();
  if (result > 0)
  {
    Serial.println(result, HEX);
    handleRemote(result);
  }
  if (IRRemot.receivingCode())
    digitalWrite(LED_BUILTIN, LOW);
  else
    digitalWrite(LED_BUILTIN, HIGH);
}

void handleRemote(uint32_t irCode)
{
  switch (irCode) {
    case  KEY_BRIGHTER:
      break;
    case KEY_DARKER:
      break;

    case KEY_POWER:
      Serial.println("power");
      while (true) {
        digitalWrite(LED_BUILTIN, LOW);   // turn the LED on
        power_all_disable();
        set_sleep_mode(SLEEP_MODE_PWR_DOWN);
        sleep_mode();
        // Processor is currently asleep and will wake up when the IR receiver pin
        // is at a low value (i.e. when a IR command is received).
        // Sleep resumes here.  When awake power everything back up.
        power_all_enable();
        Serial.print(".");
        while (IRRemot.receivingCode()) {
          digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on
          uint32_t result = IRRemot.readIR();
          if (result == KEY_POWER) {
            return false;
          }
        }
        digitalWrite(LED_BUILTIN, LOW);   // turn the LED off
      }
      break;
    case KEY_RED:
      break;
    case KEY_GREEN:
      break;
    case KEY_BLUE:
      break;
    case KEY_WHITE:
      break;
    case KEY_BR1:
      break;
    case KEY_BR2:
      break;
    case KEY_BR3:
      break;
    case KEY_FLASH:
      break;
    case KEY_BB1:
      break;
    case KEY_BB2:
      break;
    case KEY_BB3:
      break;
    case KEY_BG1:
      break;
    case KEY_BG2:
      break;
    case KEY_BG3:
      break;
  }
}

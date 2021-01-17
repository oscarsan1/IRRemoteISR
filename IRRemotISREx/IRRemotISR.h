/*************************************************
 Created by Oscar San

 See guide at: https://github.com/oscarsan1/IRRemoteISR

 GNU General Public License v3.0

**************************************************/
#ifndef IR_Remot_ISR
#define IR_Remot_ISR

#include <Arduino.h>

//#define REMOTE_TYPE_APA1616 // Remote labeled APA 1616
//#define REMOTE_TYPE_LED618  // TYPE LED618 or MAGIC LIGHTING REMOTE 24 Button Remote
#define REMOTE_TYPE_44KEYS  // Type 44 keys
//#define REMOTE_TYPE_KEYES   // keyes remote

#ifdef REMOTE_TYPE_KEYES // keyes remote
const int KEY_UP = 0xFF629D;
const int KEY_LEFT = 0xFF22DD;
const int KEY_OK = 0xFF02FD;
const int KEY_RIGHT = 0xFFC23D;
const int KEY_DOWN = 0xFFA857;
const int KEY_1 = 0xFF6897;
const int KEY_2 = 0xFF9867;
const int KEY_3 = 0xFFB04F;
const int KEY_4 = 0xFF30CF;
const int KEY_5 = 0xFF18E7;
const int KEY_6 = 0xFF7A85;
const int KEY_7 = 0xFF10EF;
const int KEY_8 = 0xFF38C7;
const int KEY_9 = 0xFF5AA5;
const int KEY_0 = 0xFF4AB5;
const int KEY_ASTERISK = 0xFF42BD;
const int KEY_POUND = 0xFF52AD;
const int KEY_REPEAT = 0xFFFFFFFF;

#elif defined REMOTE_TYPE_APA1616
/* Remote (labeled APA 1616) (like this):
  brighter  dimmer    off       on
  red       green     blue      white
  .         .         .         flash
  .         teal      purple    strobe
  orange    .         .         fade
  yellow    blue      fuchsia   smooth

  F700FF F7807F F740BF F7C03F
  F720DF F7A05F F7609F F7E01F
  F710EF F7906F F750AF F7D02F
  F730CF F7B04F F7708F F7F00F
  F708F7 F78877 F748B7 F7C837
  F728D7 F7A857 F76897 F7E817*/

const uint32_t KEY_BRIGHTER = 0xF700FF;
const uint32_t KEY_DARKER = 0xF7807F;
const uint32_t KEY_OFF = 0xF740BF;
const uint32_t KEY_ON = 0xF7C03F;
const uint32_t KEY_RED = 0xF720DF;
const uint32_t KEY_GREEN = 0xF7A05F;
const uint32_t KEY_BLUE = 0xF7609F;
const uint32_t KEY_WHITE = 0xF7E01F;
const uint32_t KEY_FLASH = 0xF7D02F;
const uint32_t KEY_STROBE = 0xF7F00F;
const uint32_t KEY_FADE = 0xF7C837;
const uint32_t KEY_SMOOTH = 0xF7E817;
const uint32_t KEY_BR1 = 0xF710EF;
const uint32_t KEY_BR2 = 0xF730CF;
const uint32_t KEY_BR3 = 0xF708F7;
const uint32_t KEY_BR4 = 0xF728D7;

const uint32_t KEY_BG1 = 0xF7906F;
const uint32_t KEY_BG2 = 0xF7B04F;
const uint32_t KEY_BG3 = 0xF78877;
const uint32_t KEY_BG4 = 0xF7A857;

const uint32_t KEY_BB1 = 0xF750AF;
const uint32_t KEY_BB2 = 0xF7708F;
const uint32_t KEY_BB3 = 0xF748B7;
const uint32_t KEY_BB4 = 0xF76897;

#elif defined REMOTE_TYPE_44KEYS
/* Type 44 keys
  FF3AC5 	FFBA45 	FF827D 	FF02FD
  FF1AE5 	FF9A65 	FFA25D 	FF22DD
  FF2AD5 	FFAA55 	FF926D 	FF12ED
  FF0AF5 	FF8A75 	FFB24D 	FF32CD
  FF38C7 	FFB847 	FF7887 	FFF807
  FF18E7 	FF9867 	FF58A7 	FFD827
  FF28D7 	FFA857 	FF6897 	FFE817
  FF08F7 	FF8877 	FF48B7 	FFC837
  FF30CF 	FFB04F 	FF708F 	FFF00F
  FF10EF 	FF906F 	FF50AF 	FFD02F
  FF20DF 	FFA05F 	FF609F 	FFE01F */

const uint32_t KEY_BRIGHTER = 0xFF3AC5;
const uint32_t KEY_DARKER = 0xFFBA45;
const uint32_t KEY_NEXT = 0xFF827D;
const uint32_t KEY_POWER = 0xFF02FD;
const uint32_t KEY_RED = 0xFF1AE5;
const uint32_t KEY_GREEN = 0xFF9A65;
const uint32_t KEY_BLUE = 0xFFA25D;
const uint32_t KEY_WHITE = 0xFF22DD;
const uint32_t KEY_BR1 = 0xFF2AD5;
const uint32_t KEY_BG1 = 0xFFAA55;
const uint32_t KEY_BB1 = 0xFF926D;
const uint32_t KEY_BW1 = 0xFF12ED;
const uint32_t KEY_BR2 = 0xFF0AF5;
const uint32_t KEY_BG2 = 0xFF8A75;
const uint32_t KEY_BB2 = 0xFFB24D;
const uint32_t KEY_BW2 = 0xFF32CD;
const uint32_t KEY_BR3 = 0xFF38C7;
const uint32_t KEY_BG3 = 0xFFB847;
const uint32_t KEY_BB3 = 0xFF7887;
const uint32_t KEY_BW3 = 0xFFF807;
const uint32_t KEY_BR4 = 0xFF18E7;
const uint32_t KEY_BG4 = 0xFF9867;
const uint32_t KEY_BB4 = 0xFF58A7;
const uint32_t KEY_BW4 = 0xFFD827;
const uint32_t KEY_R_UP = 0xFF28D7;
const uint32_t KEY_G_UP = 0xFFA857;
const uint32_t KEY_B_UP = 0xFF6897;
const uint32_t KEY_QUICK = 0xFFE817;
const uint32_t KEY_R_DOWN = 0xFF08F7;
const uint32_t KEY_G_DOWN = 0xFF8877;
const uint32_t KEY_B_DOWN = 0xFF48B7;
const uint32_t KEY_SLOW = 0xFFC837;
const uint32_t KEY_DYI1 = 0xFF30CF;
const uint32_t KEY_DYI2 = 0xFFB04F;
const uint32_t KEY_DYI3 = 0xFF708F;
const uint32_t KEY_AUTO = 0xFFF00F;
const uint32_t KEY_DYI4 = 0xFF10EF;
const uint32_t KEY_DYI5 = 0xFF906F;
const uint32_t KEY_DYI6 = 0xFF50AF;
const uint32_t KEY_FLASH = 0xFFD02F;
const uint32_t KEY_JUMP3 = 0xFF20DF;
const uint32_t KEY_JUMP7 = 0xFFA05F;
const uint32_t KEY_FADE3 = 0xFF609F;
const uint32_t KEY_FADE7 = 0xFFE01F;

#elif defined REMOTE_TYPE_LED618
// TYPE LED618 or MAGIC LIGHTING REMOTE 24 Button Remote
const uint32_t KEY_BRIGHTER = 0xFFA05F;
const uint32_t KEY_DARKER = 0xFF20DF;
const uint32_t KEY_OFF = 0xFF609F;
const uint32_t KEY_ON = 0xFFE01F;
const uint32_t KEY_RED = 0xFF906F;
const uint32_t KEY_GREEN = 0xFF10EF;
const uint32_t KEY_BLUE = 0xFF50AF;
const uint32_t KEY_WHITE = 0xFFD02F;
const uint32_t KEY_FLASH = 0xFFF00F;
const uint32_t KEY_STROBE = 0xFFE817;
const uint32_t KEY_FADE = 0xFFD827;
const uint32_t KEY_SMOOTH = 0xFFC837;
const uint32_t KEY_BR1 = 0xFFB04F;
const uint32_t KEY_BR2 = 0xFFA857;
const uint32_t KEY_BR3 = 0xFF9867;
const uint32_t KEY_BR4 = 0xFF8877;

const uint32_t KEY_BG1 = 0xFF30CF;
const uint32_t KEY_BG2 = 0xFF28D7;
const uint32_t KEY_BG3 = 0xFF18E7;
const uint32_t KEY_BG4 = 0xFF08F7;

const uint32_t KEY_BB1 = 0xFF708F;
const uint32_t KEY_BB2 = 0xFF6897;
const uint32_t KEY_BB3 = 0xFF58A7;
const uint32_t KEY_BB4 = 0xFF48B7;
#endif


class IRRemotISR {

  public:
    /*!
      @brief   Constructor
      @param   Num pin for IR device. Must be a interrupt capable pin
    */
    IRRemotISR(uint8_t ISRPin);
  
  /*!
    @brief   repeat calling this function in a loop to read IR Code
    @param   x  
    @return  0 if no code received
             32 bit unsigned with the code received.
  */
    uint32_t readIR(void);

  /*!
    @brief   test if a code is being read
    @param   x  
    @return  true if a a code is being read
             false if no code is being read
  */
    bool receivingCode();

  private:
    static void ISR_IRReceiverChanging(void) ;
    static volatile uint8_t BitIndex;
    static volatile uint32_t ISR_Durations[66];
    static volatile unsigned long AntIRMillis;
    static uint8_t _ISRPin;
};


#endif // IRRemotISR

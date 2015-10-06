//============================================================================
// DFRobot WiDo + Blynk test
//
// A first test of Blynk with a WiDo from DFRobot
// In Blynk, you can create 
//   - switches to set led on or off on digital pins 11, 12 & 13
//   - a virtual led to see the Heartbeat on virtual pin 1
//
// All you need (apart from the hardware !)
// CC3000 Adafruit's lib : https://github.com/adafruit/Adafruit_CC3000_Library
// WiDo   : http://www.dfrobot.com/index.php?route=product/product&product_id=1159
// Blynk  : http://www.blynk.cc/ 
//============================================================================


// CC3000 / Wido pins
#define ADAFRUIT_CC3000_IRQ   7
#define ADAFRUIT_CC3000_VBAT  5
#define ADAFRUIT_CC3000_CS    10

#include <SPI.h>
#include <Adafruit_CC3000.h>
#include <BlynkSimpleCC3000.h>

#include "config.h"  // Contains wifi and Blynk info

// OUT
#define pinLedRed 13
#define pinLedYellow 12
#define pinLedGreen 11

void setup()
{

  Serial.begin(9600);  //for debugging - disable once live.

  pinMode(pinLedGreen,OUTPUT);
  pinMode(pinLedYellow,OUTPUT);
  pinMode(pinLedRed,OUTPUT);

  // On Leonardo, wait for the Serial monitor to be opened 
  // so we get debug from the begining (for debugging)
  digitalWrite(pinLedGreen,HIGH);  delay(500);
  //while(!Serial);
  digitalWrite(pinLedYellow,HIGH); delay(500);
 
  Serial.println("Initializing Blynk using Wifi (CC3000 compatible)");
  Blynk.begin(auth, WLAN_SSID, WLAN_PASS, WLAN_SECURITY);
  Serial.println("Initialized !");
  
  digitalWrite(pinLedRed,HIGH);    delay(500);
  digitalWrite(pinLedGreen,LOW);
  digitalWrite(pinLedYellow,LOW);
  digitalWrite(pinLedRed,LOW);

}

long lastHB=0;
long valHB=0;

void loop()
{
  Blynk.run();                //start polling the system and reporting to the Blynk app.
  
  // Sends a heartbeat to Blynk
  // and make one of the led real leds blink
  if(millis()-lastHB > 1000) {
    if(valHB==LOW) valHB=HIGH; else valHB=LOW;
    Blynk.virtualWrite(1, valHB);   
    digitalWrite(pinLedGreen,valHB);
    lastHB=millis();
  }
}

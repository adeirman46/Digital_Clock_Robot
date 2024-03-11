#include "DFRobotDFPlayerMini.h"

#define FPSerial Serial1

DFRobotDFPlayerMini myDFPlayer;
void printDetail(uint8_t type, int value);
const int vibration_sensor_pin = 13;
const int touch_pin = 12;

int last_touch_state = LOW;
int current_touch_state;

void setup()
{
  // setting MP3
#if (defined ESP32)
  FPSerial.begin(9600, SERIAL_8N1, 16, 17);
#else
  FPSerial.begin(9600);
#endif

  Serial.begin(115200);

  Serial.println();
  Serial.println(F("DFRobot DFPlayer Mini Demo"));
  Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));
  
  if (!myDFPlayer.begin(FPSerial, /*isACK = */true, /*doReset = */true)) {  //Use serial to communicate with mp3.
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    while(true){
      delay(0); // Code to compatible with ESP8266 watch dog.
    }
  }
  Serial.println(F("DFPlayer Mini online."));
  myDFPlayer.volume(15);  //Set volume value. From 0 to 30
  // setting mp3 end

  // setting vibration sensor
  pinMode(vibration_sensor_pin, INPUT);

  pinMode(touch_pin, INPUT);



}

void loop()
{
  if (digitalRead(vibration_sensor_pin)) {
    Serial.println("vibration detected");
    myDFPlayer.play(3); 
    delay(3000);
    myDFPlayer.stop();
  }
  else {
    Serial.println("vibration not detected");
  }

  current_touch_state = digitalRead(touch_pin);
  if (last_touch_state == LOW &&  current_touch_state == HIGH) {
    Serial.println("The sensor is touched");
    myDFPlayer.play(4); 
    delay(3000);
    myDFPlayer.stop();
  }
  last_touch_state = current_touch_state;

  delay(100);
  
}

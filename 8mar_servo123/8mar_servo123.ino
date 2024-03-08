#include <Servo.h>

int pos = 0;

Servo servo1;
void setup() {
  // put your setup code here, to run once:
  servo1.attach(4);
}

void loop() {
  // put your main code here, to run repeatedly:
  for(pos = 00; pos < 180; pos += 1)  //fungsi perulangan yang akan dijadikan PWM dengan kenaikan 1
  {
  servo1.write(pos); //prosedur penulisan data PWM ke motor servo
  delay(15); //waktu tunda 15 ms                 
  } 
  for(pos = 180; pos>=1; pos-=1)  //fungsi perulangan yang akan dijadikan PWM dengan penurunan 1
  {                              
  servo1.write(pos);                 
  delay(15);                        
  }

}

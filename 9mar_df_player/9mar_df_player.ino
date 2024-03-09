#include <SoftwareSerial.h>             //Library SoftwareSerial
#include <DFPlayer_Mini_Mp3.h>  //Library DFPlayer mini MP3
 
SoftwareSerial serial(10, 11);            //Deklarasi pin TX dan RX
 
void setup (){
  serial.begin (9600);  
  mp3_set_serial (serial);          //Instruksi untuk memulai komunikasi serial
  delay(5); 
  mp3_set_volume (5);           //Instruksi untuk mengatur volume musik
  delay(1000);
}
 
void loop (){  
  mp3_play(1);                         //Instruksi untuk memutar lagu 1
  delay(240000);                      //Memutar lagu selama 4 menit
  // mp3_next();
  // mp3_play(2);                         //Instruksi untuk memutar lagu 2
  // delay(10000);                        //Memutar lagu selama 10 detik
  mp3_stop();                           //Instruksi untuk mematikan lagu
}
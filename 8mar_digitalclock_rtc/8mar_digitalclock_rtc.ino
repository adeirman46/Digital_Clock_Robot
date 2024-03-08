#include <DS3231.h> //mengincludekan library DS3231

DS3231  rtc(SDA, SCL); // inisialisasi penggunaan i2c

void setup()
{
  Serial.begin(9600); //set komunikasi baut serial monitor pada 115200
  rtc.begin();
  
  // //setting pertama download program
  // rtc.setDate(8, 3, 2023);   //mensetting tanggal 07 april 2018
  // rtc.setTime(10, 2, 0);     //menset jam 22:00:00
  // rtc.setDOW(5);     //menset hari "Sabtu"

//setelah didownload awal selesai, download kedua dengan memberi tanda komen "//"
}

void loop()
{
  Serial.print(rtc.getDOWStr()); //prosedur pembacaan hari
  Serial.print(" ");
  
  Serial.print(rtc.getDateStr()); //prosedur pembacaan tanggal
  Serial.print(" -- ");

  Serial.println(rtc.getTimeStr()); //prosedur pembacaan waktu
  
  delay (1000); //waktu tunda 1 detik per cycle
}
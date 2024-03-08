#include <LCDWIKI_GUI.h>
#include <LCDWIKI_SPI.h>
#include <DS3231.h> // Include the DS3231 RTC library

#define MODEL ILI9225
#define CS 10
#define CD 9
#define RST 8
#define SDA2 11
#define SCK2 13
#define LED -1

LCDWIKI_SPI mylcd(MODEL, CS, CD, -1, SDA2, RST, SCK2, LED);
DS3231 rtc(SDA, SCL); // Initialize RTC using I2C pins

void setup() {
  mylcd.Init_LCD();
  mylcd.Fill_Screen(0x0000); // Fill the screen with black color

  Serial.begin(9600);
  rtc.begin(); // Initialize the RTC

  // Uncomment the following lines to set the initial time and date (if needed)
  // rtc.setDate(8, 3, 2023); // Set the date to March 8, 2023
  // rtc.setTime(10, 2, 0); // Set the time to 10:02:00
  // rtc.setDOW(5); // Set the day of the week to Saturday (5)
}

void loop() {
  mylcd.Set_Rotation(1);

  // Draw the outer ring
  mylcd.Set_Draw_color(0xF800); // Set the color to red
  mylcd.Draw_Circle(120, 120, 110); // Draw a circle with radius 110

  // Draw the hour markers
  mylcd.Set_Draw_color(0xFFFF); // Set the color to white
  for (int i = 0; i < 60; i += 5) { // Draw a marker every 5 minutes
    int x1 = 120 + 100 * cos(i * 3.14 / 30);
    int y1 = 120 + 100 * sin(i * 3.14 / 30);
    int x2 = 120 + 90 * cos(i * 3.14 / 30);
    int y2 = 120 + 90 * sin(i * 3.14 / 30);
    mylcd.Draw_Line(x1, y1, x2, y2);
  }

  // Draw the inner circle
  mylcd.Set_Draw_color(0x0000); // Set the color to black
  mylcd.Fill_Circle(120, 120, 80); // Draw a filled circle with radius 80

  // Draw the hands (commented out for now)
  mylcd.Set_Draw_color(0xFFFF); // Set the color to white
  mylcd.Draw_Line(120, 120, 120 + 70 * cos((12 * 3.14 / 6)), 120 + 70 * sin((12 * 3.14 / 6))); // Hour hand
  mylcd.Draw_Line(120, 120, 120 + 90 * cos((0 * 3.14 / 30)), 120 + 90 * sin((0 * 3.14 / 30))); // Minute hand
  mylcd.Draw_Line(120, 120, 120 + 60 * cos((0 * 3.14 / 30)), 120 + 60 * sin((0 * 3.14 / 30))); // Second hand

  // Draw the text
  mylcd.Set_Text_colour(0xFFFF); // Set the text color to white
  mylcd.Set_Text_Size(2);

  // Get the current date and time from the RTC
  String dateStr = rtc.getDateStr();
  String timeStr = rtc.getTimeStr();

  // mylcd.Print_String(dateStr.substring(0, 2), 80, 90); // Print the date
  // mylcd.Print_String(rtc.getDOWStr(FORMAT_SHORT), 80, 110); // Print the day of the week (abbreviated)
  // mylcd.Print_String(timeStr, 180, 90); // Print the time
  Serial.print(rtc.getDOWStr()); //prosedur pembacaan hari
  Serial.print(" ");
  
  Serial.print(rtc.getDateStr()); //prosedur pembacaan tanggal
  Serial.print(" -- ");

  Serial.println(rtc.getTimeStr()); //prosedur pembacaan waktu
  delay(100); // Delay for 1 second
}



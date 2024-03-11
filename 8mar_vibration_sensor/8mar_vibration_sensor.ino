const int sensor_pin = 10;

void setup() {
  Serial.begin(9600);
  pinMode(sensor_pin, INPUT);

}

void loop() {
  if (digitalRead(sensor_pin)) {
    Serial.println("vibration detected");
  }
  else {
    Serial.println("vibration not detected");
  }
  delay(100);
}


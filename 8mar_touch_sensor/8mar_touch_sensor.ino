const int touch_pin = 4;

int last_touch_state = LOW;
int current_touch_state;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(touch_pin, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  current_touch_state = digitalRead(touch_pin);
  if (last_touch_state == LOW &&  current_touch_state == HIGH) {
    Serial.println("The sensor is touched");
  }
  last_touch_state = current_touch_state;

}

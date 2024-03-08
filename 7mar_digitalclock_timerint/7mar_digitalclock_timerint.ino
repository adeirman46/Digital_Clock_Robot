int timer1_compare_match; // 16 bit timer
int hour_;
int minute_;
int second_;

ISR(TIMER1_COMPA_vect) {
  TCNT1 = timer1_compare_match;

  // Increment seconds
  second_++;
}

void set_time(int hour, int minute, int second) {
  hour_ = hour;
  minute_ = minute;
  second_ = second;
}

void setup() {
  // Initialize serial communication
  Serial.begin(9600);

  // Disable all interrupts
  noInterrupts();

  // Set initial time
  set_time(8, 23, 50);

  // Set timer mode to compare
  TIMSK1 |= (1 << OCIE1A);

  // Initialize timer1
  // TCCR1A &= ~(1 << WGM10) & ~(1 << WGM11);
  // TCCR1B &= ~(1  << WGM12) & ~(1 << WGM12);
  TCCR1A = 0;
  TCCR1B = 0;

  // Set compare register
  // timer1_compare_match = 15624;
  timer1_compare_match = 31249;
  TCNT1 = timer1_compare_match;

  // Set prescaler 1024
  // TCCR1B |= (1 << CS12) | (1 << CS10);
  // TCCR1B &= ~(1 << CS11);
  TCCR1B |= (1 << CS12);

  // Enable all interrupts
  interrupts();
}

void loop() {
  // Print time
  if (second_ >= 60) {
  second_ = 0;
  minute_++;
  if (minute_ >= 60) {
    minute_ = 0;
    hour_++;
    if (hour_ >= 24) {
      hour_ = 0;
      }
    }
  }
  Serial.print(hour_);
  Serial.print(":");
  Serial.print(minute_);
  Serial.print(":");
  Serial.println(second_);
}

bool rise = true;
uint16_t cnt_rise;
uint16_t cnt_fall;

ISR(TIM0_CAPT_vect) {
  if (rise) {
    cnt_rise = ICR0;
    TCCR0B &= ~_BV(ICES0); // Input Capture Edge Select: falling edge
  } else {
    cnt_fall = ICR0;
    TCCR0B |= _BV(ICES0); // Input Capture Edge Select: rising edge
    digitalWrite(PB2, cnt_fall - cnt_rise > 1500 ? HIGH : LOW); // 1 MHz * 1.5 ms = 1.5 k
  }
  TIFR0 = _BV(ICF0); // Timer/Counter0, Input Capture Flag: clear
  rise = !rise;
}

void setup() {  
  pinMode(PB0, INPUT_PULLUP); // NC
  pinMode(PB2, OUTPUT);

  // digitalWrite(PB2, HIGH);
  // delay(500);
  // digitalWrite(PB2, LOW);

  TCCR0B |= _BV(ICNC0); // Input Capture Noise Canceler: activate
  TCCR0B |= _BV(ICES0); // Input Capture Edge Select: rising edge
  TCCR0B |= _BV(CS00); // Clock Select: no prescaling
  TIMSK0 |= _BV(ICIE0); // Timer/Counter0, Input Capture Interrupt Enable: enable

  sei();
}

void loop() {
  // digitalWrite(PB2, HIGH);
  // delay(1000);
  // digitalWrite(PB2, LOW);
  // delay(1000);
}

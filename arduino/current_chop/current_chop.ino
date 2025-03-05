byte step = 0;
bool current_on = 0; 

void setup() {
  
  // Timer1 Control Registers, define mode and prescaler
  TCCR1A = 0;
  TCCR1B = 0;
  // Timer2 Control Registers, define mode and prescaler
  TCCR2A = 0;
  TCCR2B = 0; 

  // Timer1 Counter set to 0 
  TCNT1 = 0;
  // Timer2 Counter set to 0
  TCNT2 = 0;

  // Output Compare Register A, determines when Timer1 triggers interrupt
  // 16MHZ / (8 (CS21, prescaler) * 19) = 100kHz
  // WGM12 is for CTC mode, Timer1 resets when reaches 32150
  OCR1A = 45;
  OCR1B = 100;
  TCCR1B |= (1 << WGM12) | (1 << CS21);  
  TIMSK1 |= (1 << OCIE1A) | (1 << OCIE1B); //enables Timer1 compare match A interrupt

  OCR2A = 6249;
  // OCR2A = 31250; 
  TCCR2B |= (1 << WGM12) | (1 << CS11) | (1 << CS10);
  TIMSK2 |= (1 << OCIE2A); //enables Timer2 compare match A interrupt

  sei();
  DDRD |= B11111100;
}

// every 10 us
ISR(TIMER1_COMPA_vect){
  if (current_on) {
    current_on = false;
  }
}

// every 50 us
ISR(TIMER1_COMPB_vect){
  if (!current_on) {
    current_on = true;
  }
}

// every 25 ms
ISR(TIMER2_COMPA_vect){
  step++;
  if (step == 6) {
    step = 0;
  }
}

void loop() {
  switch (step) {
    case 0:
      if(current_on) {
        // Top left on, bottom middle on
        PORTD = B10001100; 
      }
      else {
        // Bottom left on, bottom middle on
        PORTD = B10000000;
      }
    
    case 1:
      if(current_on) {
        // Top right on, bottom middle on
        PORTD = B11001000;
      }
      else {
        // Bottom right on, bottom middle on
        PORTD = B00001000;
      }
    
    case 2:
      if(current_on) {
        // Top right on, bottom left on
        PORTD = B11100000;
      }
      else {
        // Bottom right on, bottom left on
        PORTD = B00100000;
      }

    case 3:
      if(current_on) {
        // Top middle on, bottom left on
        PORTD = B10110000;
      }
      else {
        // Bottom middle on, bottom left on
        PORTD = B10000000;
      }
    
    case 4:
      if(current_on) {
        // Top middle on, bottom right on
        PORTD = B00111000;
      }
      else {
        // Bottom middle on, bottom right on
        PORTD = B00001000;
      }
    
    case 5:
      if(current_on) {
        // Top left on, bottom right on
        PORTD = B00101100;
      }
      else {
        // Bottom left on, bottom right on
        PORTD = B00100000;
      }
  }
}

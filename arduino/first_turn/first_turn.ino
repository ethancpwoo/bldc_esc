unsigned long delay_duration = 25;

void setup() {
  // put your setup code here, to run once:
  DDRD |= B11111100;
  PCICR |= (1 << PCIE0);
}

void loop() {
  // Top left on, bottom middle on
  PORTD = B10001100;
  delay(delay_duration);

  // Top right on, bottom middle on
  PORTD = B11001000;
  delay(delay_duration);

  // Top right on, bottom left on
  PORTD = B11100000;
  delay(delay_duration);

  // Top middle on, bottom left on
  PORTD = B10110000;
  delay(delay_duration);

  // Top middle on, bottom right on
  PORTD = B00111000;
  delay(delay_duration);

  // Top left on, bottom right on
  PORTD = B00101100;
  delay(delay_duration);

}

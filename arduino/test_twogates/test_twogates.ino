void setup() {
  DDRD |= B11111100;
  PORTD &= B00000011;
  PCICR |= (1 << PCIE0);

  // PORTD |= B00000100;  // Set pin 2 to HIGH
  // PORTD &= B11110111;  // Set pin 3 to LOW
  // PORTD = B00000100; // This turns 2 high, 3 low, changes first LED
  // PORTD = B10101000; // Nothing on
  // PORTD = B10001100; // Middle provides ground
  // PORTD = B00101100; // Last provides ground
  // PORTD = B10011000;
  PORTD = B01101000;

}

void loop() {
  // PORTD = B00000100;
  // Nothing to do in the loop, as we only want to set the pins to HIGH once
}

void setup() {
  // Set pins 2 and 3 as output
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);

  // Set pins 2 and 3 to HIGH
  digitalWrite(6, HIGH);
  digitalWrite(7, LOW);
}

void loop() {
  // Nothing to do in the loop, as we only want to set the pins to HIGH once
}
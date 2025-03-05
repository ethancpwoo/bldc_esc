int phase = 1;
int delay_time = 4000;

unsigned long currentMillis = 0;
unsigned long lastMillis = 0;

void setup() {
  // put your setup code here, to run once:
  DDRD |= B11111100;
  PORTD &= B00000011;
  PCICR |= (1 << PCIE0);
  currentMillis = micros();
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:

  // currentMillis = micros();
  // if(currentMillis - previousMillis >= Delay)
  //   previousMillis

  if (Serial.available() > 0) {
    Serial.println("Enter from 1-6 phase choice");

    int phase = Serial.parseInt();
    Serial.println(phase);
    switch(phase) {
      case 1: 
        PORTD = B00000000;
        break;
      case 2:
        PORTD = B11000000;
        break;
      case 3:
        PORTD = B01001000;
        break;
      case 4:
        PORTD = B10000000;
        break;
      case 5:
        PORTD = B00100100;
        break;
      case 6:
        PORTD = B10000100;
        break;
    }

  }
  

}

const int ledPin = 7; 

void setup() {
  pinMode(ledPin, OUTPUT);
  
}

void loop() {
  // 1. 처음 1초 동안 LED 켜기
  digitalWrite(ledPin, LOW);
  delay(1000);

  //
  for (int i = 0; i < 6; i++) {
    digitalWrite(ledPin, LOW);
    delay(100);
    digitalWrite(ledPin, HIGH);
    delay(100);
  }

  // 3. 
  digitalWrite(ledPin, HIGH);
  
  while (1) {
    // 
  }
}

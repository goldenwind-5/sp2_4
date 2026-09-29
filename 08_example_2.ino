
#define PIN_LED  9
#define PIN_TRIG 12   
#define PIN_ECHO 13  


#define SND_VEL 346.0     
#define INTERVAL 25      
#define PULSE_DURATION 10 
#define _DIST_MIN 100.0   
#define _DIST_MAX 300.0  

#define TIMEOUT ((INTERVAL / 2) * 1000.0) 
#define SCALE (0.001 * 0.5 * SND_VEL) 

unsigned long last_sampling_time;   

void setup() {
  // initialize GPIO pins
  pinMode(PIN_LED, OUTPUT);
  pinMode(PIN_TRIG, OUTPUT);  
  pinMode(PIN_ECHO, INPUT);  
  digitalWrite(PIN_TRIG, LOW);  
  
  // initialize serial port
  Serial.begin(57600);
}

void loop() { 
  float distance;
  int pwm_value;

  if (millis() < (last_sampling_time + INTERVAL))
    return;

  distance = USS_measure(PIN_TRIG, PIN_ECHO); // read distance

  if (distance <= _DIST_MIN || distance >= _DIST_MAX || distance == 0.0) {
      pwm_value = 255; 
  } 
  else if (distance < 200.0) {
      
      pwm_value = (int)(255.0 - (255.0 / (200.0 - _DIST_MIN)) * (distance - _DIST_MIN));
  } 
  else {
      pwm_value = (int)((255.0 / (_DIST_MAX - 200.0)) * (distance - 200.0));
  }

  if (pwm_value < 0) pwm_value = 0;
  if (pwm_value > 255) pwm_value = 255;

  analogWrite(PIN_LED, pwm_value);

 
  Serial.print("Min:");        Serial.print(_DIST_MIN);
  Serial.print(",distance:");  Serial.print(distance);
  Serial.print(",PWM:");       Serial.print(pwm_value);
  Serial.print(",Max:");       Serial.print(_DIST_MAX);
  Serial.println("");
  

  last_sampling_time += INTERVAL;
}


float USS_measure(int TRIG, int ECHO)
{
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(PULSE_DURATION);
  digitalWrite(TRIG, LOW);
  
  return pulseIn(ECHO, HIGH, TIMEOUT) * SCALE; // unit: mm
}

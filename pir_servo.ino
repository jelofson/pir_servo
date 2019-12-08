#include <Servo.h>

Servo myservo;
const int LED_PIN = 13;
const int BTN_PIN = 3;
const int PIR_PIN = 8;
const int SERVO_PIN = 10;

const int UP = 100;
const int DOWN = 0;
bool triggered = false;
bool enabled = false;

void setup()
{
  pinMode(LED_PIN, OUTPUT);
  pinMode(PIR_PIN, INPUT);
  pinMode(BTN_PIN, INPUT_PULLUP);
  digitalWrite(LED_PIN, LOW);
  pinMode(SERVO_PIN, OUTPUT);
  
  myservo.attach(SERVO_PIN);
  myservo.write(UP);


  Serial.begin(9600);
}

void loop()
{

  if (digitalRead(BTN_PIN) == LOW && isUp()) 
  {
    reset();
    delay(250);
  }

  if (digitalRead(BTN_PIN) == LOW && ! triggered && ! enabled) 
  {
    enable();  
  }
  
  if (enabled && detected() && ! triggered) 
  {
    triggered = true;
    myservo.write(UP);
  }
  
  delay(10);
  
}

bool isUp()
{
  return myservo.read() == UP;
}

void enable()
{
  enabled = true;
  digitalWrite(LED_PIN, HIGH);
  delay(200);
  digitalWrite(LED_PIN, LOW);
  delay(5000);
  digitalWrite(LED_PIN, HIGH);
}

void reset()
{
  enabled = false;
  triggered = false;
  digitalWrite(LED_PIN, LOW);
  myservo.write(DOWN);
}

bool detected()
{
  
  return digitalRead(PIR_PIN) == HIGH;
}

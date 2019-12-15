#include <Servo.h>

Servo myservo;
const int LED_PIN = 13;
const int BTN_PIN = 3;
const int PIR_PIN = 8;
const int SERVO_PIN = 10;
const int LAUGH_PIN = 6;
const int CROW_PIN = 7;


const int UP = 100;
const int DOWN = 0;
bool triggered = false;
bool enabled = false;

unsigned long previousMillis = 0;
long interval = 60000;


void setup()
{
  pinMode(LED_PIN, OUTPUT);
  pinMode(PIR_PIN, INPUT);
  pinMode(BTN_PIN, INPUT_PULLUP);
  pinMode(LAUGH_PIN, OUTPUT);
  pinMode(CROW_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
  pinMode(SERVO_PIN, OUTPUT);
  
  myservo.attach(SERVO_PIN);
  myservo.write(UP);


  Serial.begin(9600);
}

void loop()
{
  
  unsigned long currentMillis = millis();
  
  if (detected() && intervalPassed(currentMillis, previousMillis, interval)) 
  {
    previousMillis = currentMillis;
    //playSound();
  }


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
    laugh();
  }
  
  delay(50);
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
  delay(15000);
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
  bool detected = digitalRead(PIR_PIN) == HIGH;
  return detected;
}

void playSound()
{
  long randNum = random(0,10);
  
  if (randNum < 6) {
    laugh();
  } else {
    crow();
  }
}


bool intervalPassed(long currentMillis, long previousMillis, long interval)
{
  
  return currentMillis - previousMillis >= interval;
}

void laugh()
{
  digitalWrite(LAUGH_PIN, HIGH);
  delay(200);
  digitalWrite(LAUGH_PIN, LOW);
  
}

void crow()
{
  digitalWrite(CROW_PIN, HIGH);
  delay(200);
  digitalWrite(CROW_PIN, LOW);
  
}

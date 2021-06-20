#include<LiquidCrystal.h>
#include<MQ2.h>
LiquidCrystal lcd(13, 12, 11, 10, 9, 8);
int distance=0;
int smoke=0;
int lpg=0;
int temp=0;
float duration_us;
const int motion_sensor = 7;
const int buzz = 6; 
const int TRIG_PIN = 5; 
const int ECHO_PIN = 4;
const int led =3; 
const int DISTANCE_THRESHOLD = 25; 
const int GAS_SENSOR = A0;
const int TMP_SENSOR = A1; 
const int LPG_SENSOR = A2;
MQ2 mq2(GAS_SENSOR);
void setup() 
{
  lcd.begin(16,2);
  Serial.begin(9600);
  pinMode(led, OUTPUT);
  pinMode(buzz, OUTPUT);
  pinMode(motion_sensor, INPUT);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(GAS_SENSOR, INPUT);
  pinMode(TMP_SENSOR, INPUT);
  pinMode(LPG_SENSOR, INPUT);
 }
void alert1(void)
{
  digitalWrite(led, HIGH);
  digitalWrite(buzz, HIGH);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Motion Detected");
  lcd.setCursor(4,1);
  lcd.print("MSG sent");
  delay(3000);
  digitalWrite(buzz, LOW);
  digitalWrite(led, LOW);
}
void alert2(void)
{
  digitalWrite(led, HIGH);
  digitalWrite(buzz, HIGH);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Chances of Fire");
  lcd.setCursor(4,1);
  lcd.print("MSG sent");
  delay(3000);
  digitalWrite(buzz, LOW);
  digitalWrite(led, LOW);
 }
 void alert3(void)
{
  digitalWrite(led, HIGH);
  digitalWrite(buzz, HIGH);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Someone is Close");
  lcd.setCursor(4,1);
  lcd.print("MSG sent");
  delay(3000);
  digitalWrite(buzz, LOW);
  digitalWrite(led, LOW);
 }
void loop() {
  //anti-theft system
  int motion = digitalRead(motion_sensor);
  if (motion == HIGH)
  {
    alert1();
    }
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  duration_us = pulseIn(ECHO_PIN, HIGH);
  distance = 0.017 * duration_us;
  Serial.print("Distance=");
  Serial.println(distance);
  delay(500);
  if(distance < DISTANCE_THRESHOLD)
  {
    alert3();
  }
 smoke=mq2.readSmoke();
 lpg=mq2.readLPG();
 delay(100);
 Serial.print("Smoke=");
 Serial.println(smoke);
 Serial.print("LPG=");
 Serial.println(lpg);
  if(smoke>=5000)
  {
    lcd.clear();
    lcd.print("Smoke Detected");
    delay(2000);
    lcd.clear();
    alert2();
  }
  if(lpg>=5000)
  {
    lcd.clear();
    lcd.print("LPG Detected");
    delay(2000);
    lcd.clear();
    alert2();
  }
  temp = analogRead(A1);    
  temp = temp/2.048;
  //Serial.println(temp);     
  Serial.print("Temp=");
  Serial.println(temp);  
  if(temp>=50)
  { 
    lcd.clear();
    lcd.print("High Temp:");
    lcd.print(temp);
    lcd.print("C");
    delay(2000);
    lcd.clear();
    alert2();
  }
  lcd.clear();
  lcd.setCursor(5,0);
  lcd.print("SYSTEM");
  lcd.setCursor(5,1);
  lcd.print("READY");
  delay(1000);
  lcd.clear();
  }

#include <LiquidCrystal.h> // includes the LiquidCrystal Library 
LiquidCrystal lcd(17, 18, 19, 20, 21, 22); // Creates an LC object. Parameters: (rs, enable, d4, d5, d6, d7)
int numberFPlots = 4;
int triggerPort1 = 9;
int echoPort1 = 11;
int triggerPort2 = 12;
int echoPort2 = 13;
int car_count = 0;
bool car_enter = false;
bool car_exit = false;
void setup() {
  Serial.begin  (115200);
  lcd.begin(16 , 2);
  lcd.print("* Delifini.lk *");
  delay(500);
  Serial.print("----- Delifini.lk -----");
  pinMode(triggerPort1, OUTPUT); // initialize serial communication:
  pinMode(echoPort1, INPUT);
  pinMode(triggerPort2, OUTPUT);
  pinMode(echoPort2, INPUT);
  for (int i = 2; i <= ((numberFPlots * 2) + 1) ; i += 2) {
    pinMode(i, OUTPUT);
    pinMode(i + 1, INPUT);
  }
}
bool sencOneDist() {
  digitalWrite(triggerPort1, LOW);
  digitalWrite(triggerPort1, HIGH); // The PING))) is triggered by a HIGH pulse of 10 microseconds.
  delayMicroseconds(10); // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  digitalWrite(triggerPort1, LOW);
  long duration = pulseIn(echoPort1, HIGH);
  long r = 3.4 * duration / 2;
  float distance = r / 100.00;  // convert the time into a distance
  delay(100);
  bool sensor;
  if (distance > 5.00 && distance < 45.00) {  //reading from the sensor and understanding if its a vehical of something.
    sensor = true;
  } else {
    sensor = false;
  }
  return sensor;
}
bool senceTwoDist() {
  digitalWrite(triggerPort2, LOW);
  digitalWrite(triggerPort2, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPort2, LOW);
  long duration = pulseIn(echoPort2, HIGH);
  long r = 3.4 * duration / 2;
  float distance = r / 100.00;
  delay(100);
  bool sensor;
  if (distance > 5.00 && distance < 45.00) {  //reading from the sensor and understanding if its a vehical of something.
    sensor = true;
  } else {
    sensor = false;
  }
  return sensor;
}
bool plotChk(int trigger, int echo) {
  digitalWrite (trigger, LOW);
  digitalWrite (trigger, HIGH);
  delayMicroseconds (10);
  digitalWrite (trigger, LOW);
  long duration = pulseIn(echo, HIGH);
  long r = 3.4 * duration / 2;
  float distance = r / 100.00;         //convert the time into a distance
  delay(100);
  bool sensor;
  if (distance > 5.00 && distance < 45.00) {
    sensor = true;
  }
  else {
    sensor = false;
  }
  return sensor;
}
void loop() {
  int i ;
  for (i = 2 ; i <= ((numberFPlots * 2) + 1) ; i += 2) {
    if (plotChk(i, i + 1) == true) {
      break;
    }
  }
  if (sencOneDist() && !senceTwoDist()) {
    car_enter = true;
    car_exit = false;
  }
  if (sencOneDist() && senceTwoDist() && car_enter) {
    car_count++;
    Serial.print(car_count);
    Serial.print("\n");
    car_enter = false;
  }
  if (!sencOneDist() && senceTwoDist()) {
    car_enter = false;
    car_exit = true;
  }
  if (sencOneDist() && senceTwoDist() && car_exit) {
    car_count--;
    Serial.print(car_count);
    Serial.print("\n");
    car_exit = false;
  }
  if (car_count >= 0) {
    lcd.print("Nearest Plot Number : " + i - 1 );
    lcd.setCursor(0, 1);
    lcd.print("Number of Plots Available : " + car_count);
    lcd.setCursor(0, 0);
  } else {
    lcd.print("Parking Full");
  }
}

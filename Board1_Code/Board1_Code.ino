int numberFPlots = 2;

long distanceVarX1 = 0;
long distanceVarX2 = 0;
long distanceVarX3 = 0;
long minX = 0;
int dis_CountKeep[2];
int timesIteration = 10;

void setup() {
  Serial.begin  (115200);

  for (int i = 22; i < ((numberFPlots * 6) + 22 ) ; i += 2) {
    pinMode(i, OUTPUT);
    pinMode(i + 1, INPUT);
  }
}

void loop() {

  for (int i = 22 , j = 0; i < ((numberFPlots * 6) + 22 ) ; i += 7) {
    slotX(i , i + 1 , i + 2 , i + 3 , i + 4 , i + 5 , j);
    j++;
  }

}

long readingSensors(int trigPinx, int echoPinx) {
  long duration, distance;
  digitalWrite(trigPinx, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPinx, HIGH);
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPinx, LOW);
  duration = pulseIn(echoPinx, HIGH);
  distance = (duration * 0.034 / 2);
  return distance;
}

void slotX(int trigPinX, int echoPinX, int trigPinX1, int echoPinX1, int trigPinX2, int echoPinX2 , int slotNumber) {

  distanceVarX1 = readingSensors(trigPinX, echoPinX);
  distanceVarX2 = readingSensors(trigPinX1, echoPinX1);
  distanceVarX3 = readingSensors(trigPinX2, echoPinX2);
  minMeth(distanceVarX1, distanceVarX2, distanceVarX3, slotNumber);
}

void  minMeth(long distanceVarx, long distanceVary, long distanceVarz, int slotNum) {

  int min = 0;

  if (distanceVarx < distanceVary) {
    if (distanceVarx < distanceVarz) {
      min = distanceVarx;
    } else if (distanceVary < distanceVarz) {
      min = distanceVary;
    } else {
      min = distanceVarz;
    }
    min = distanceVarx;
  }

  //  lcd.setCursor(0,0); // Sets the location at which subsequent text written to the LCD will be displayed
  if (min < 30) {

    if (dis_CountKeep[slotNum] <= timesIteration) {
      //    lcd.println("Stop the Car");
      Serial.println("Stop the Car");
      dis_CountKeep[slotNum]++;
    }

  } else {

    //    lcd.print(min);
    //    lcd.println(" cm");

    Serial.print(min);
    Serial.println(" cm");

    dis_CountKeep[slotNum] = 0;
  }
}


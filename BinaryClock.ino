#include <Boards.h>
#include <Firmata.h>
#include <FirmataConstants.h>
#include <FirmataDefines.h>
#include <FirmataMarshaller.h>
#include <FirmataParser.h>
#include <DS3231.h>
#include <Wire.h> 
#include <string.h>

int getMin(int min){
  if (min >= 0 && min < 5){
    return 1;
  }
  else if (min >= 5 && min < 10){
    return 2;
  }
  else if (min >= 10 && min < 15){
    return 3;
  }
  else if (min >= 15 && min < 20){
    return 4;
  }
  else if (min >= 20 && min < 25){
    return 5;
  }
  else if (min >= 25 && min < 30){
    return 6;
  }
  else if (min >= 30 && min < 35){
    return 7;
  }
  else if (min >= 35 && min < 40){
    return 8;
  }
  else if (min >= 40 && min < 45){
    return 9;
  }
  else if (min >= 45 && min < 50){
    return 10;
  }
  else if (min >= 50 && min < 55){
    return 11;
  }
  else if (min >= 55 && min < 60){
    return 12;
  }
}

DS3231  rtc(SDA, SCL);
long ymd_out[3];
int intDelay = 1000;
Time  t;

void showTime(){
  t = rtc.getTime();

  int h = t.hour;
  int m = t.min;

  int newH = h;
  int newM = m;

  int valBH = digitalRead(14);
  int valBM = digitalRead(15);

  if (valBH == HIGH){
    Serial.print("valBH is HIGH: ");
    Serial.println(valBH);
    newH++;
  }
  else{
    Serial.print("valBH is LOW: ");
    Serial.println(valBH);
  }

  if (valBM == HIGH){
    Serial.print("valBM is HIGH: ");
    Serial.println(valBM);
    newM++;
  }
  else{
    Serial.print("valBM is LOW: ");
    Serial.println(valBM);
  }


  if (h != newH || m != newM)
  {
    if (newH > 23) newH = 1;
    if (newM > 59) newM = 1;
    rtc.setTime(newH, newM, 0);

    h = newH;
    m = newM;
  }

  if (h > 12){
    h = h - 12;
  }
  else if (h == 0){
    h = 12;
  }
  
  int mi[10], hr[10], n, i;   
  n = getMin(m);

  Serial.print("h: ");
  Serial.println(h);
  Serial.print("m: ");
  Serial.println(m);

  for(i=0; i<10; i++)    
  {    
    hr[i] = 0;
    mi[i] = 0;    
  }  
  
  for(i=0; n>0; i++)    
  {    
    mi[i] = n%2;    
    n = n/2;  
  }    

  for(i=0; h>0; i++)    
  {    
    hr[i] = h%2;    
    h = h/2;  
  }   

  if (hr[3] == 1){
    digitalWrite(4, LOW);
  }
  else{
    digitalWrite(4, HIGH);
  }

  if (hr[2] == 1){
    digitalWrite(5, LOW);
  }
  else{
    digitalWrite(5, HIGH);
  }

  if (hr[1] == 1){
    digitalWrite(6, LOW);
  }
  else{
    digitalWrite(6, HIGH);
  }

  if (hr[0] == 1){
    digitalWrite(7, LOW);
  }
  else{
    digitalWrite(7, HIGH);
  }

  if (mi[3] == 1){
    digitalWrite(8, LOW);
  }
  else{
    digitalWrite(8, HIGH);
  }

  if (mi[2] == 1){
    digitalWrite(9, LOW);
  }
  else{
    digitalWrite(9, HIGH);
  }

  if (mi[1] == 1){
    digitalWrite(10, LOW);
  }
  else{
    digitalWrite(10, HIGH);
  }

  if (mi[0] == 1){
    digitalWrite(16, LOW);
  }
  else{
    digitalWrite(16, HIGH);
  }
  
  Serial.print(hr[0]);
  Serial.print(hr[1]);
  Serial.print(hr[2]);
  Serial.print(hr[3]);
  Serial.print(":");
  Serial.print(mi[0]);
  Serial.print(mi[1]);
  Serial.print(mi[2]);
  Serial.println(mi[3]);
  
  delay(intDelay);  
}
  
void setup() {
  rtc.begin();
  Serial.begin(115200);
  Serial.println("Start");
  
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(16, OUTPUT);

  pinMode(A0, OUTPUT);
  pinMode(14, INPUT);       
  pinMode(15, INPUT);
  
  digitalWrite(4, HIGH);
  digitalWrite(5, HIGH);
  digitalWrite(6, HIGH);
  digitalWrite(7, HIGH);
  digitalWrite(8, HIGH);
  digitalWrite(9, HIGH);
  digitalWrite(10, HIGH);
  digitalWrite(16, HIGH);

  digitalWrite(A0, HIGH);

  delay(intDelay);
}

void loop() {
  showTime();
}

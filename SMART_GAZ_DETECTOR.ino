#include <Servo.h>
Servo gradus;

#include <LiquidCrystal.h>
LiquidCrystal lcd(7,6,5,4,3,2);

#include <DHT.h>
#define DHTPIN 10
#define DHTTYPE DHT11
DHT dht(DHTPIN,DHTTYPE);
float sensorQiymati;
int c;
void setup() {
  Serial.begin(9600);
  Serial.println("DHT11 datchigi yordamida namlik va temperaturani o'lchash");
  dht.begin();
  lcd.begin(16,2);
  Serial.println("Gaz sensori ishga tushdi");
  pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(11,OUTPUT);
  pinMode(12,OUTPUT);
  gradus.attach(13);
}
void loop() {
  delay(2000);
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  Serial.print("NAMLIK");
  Serial.print(h);
  Serial.print("TEMPERATURA");
  Serial.print(t);
  Serial.println(" *C ");
  if(Serial.available()>0){c=Serial.read()-48; Serial.println(c);}
  if(c==3){digitalWrite(11,1);digitalWrite(12,0);}  
  if(c==2){gradus.write(90);}
  if(c==4){gradus.write(0);} 
  if(c==5){digitalWrite(8,1);delay(200);digitalWrite(8,0);delay(200);} 
   if(c==0){digitalWrite(11,0);digitalWrite(12,0);digitalWrite(8,0);}
  Serial.println(analogRead(A0));delay(1000);
  if(analogRead(A0)<300){sensorQiymati = analogRead(A0);//analog 0 oyoqni o'qish
  lcd.setCursor(0,0);lcd.print("GAZ QIYMATI: ");
  lcd.setCursor(13,0);lcd.print(sensorQiymati);delay(2500);lcd.setCursor(0,0);lcd.print("TEMPERATURA:  ");lcd.setCursor(13,0);lcd.print(t);
  lcd.setCursor(0,1);lcd.print("NAMLIK: ");lcd.setCursor(13,1);lcd.print(h);}
  noTone(8);digitalWrite(9,0);
  if(analogRead(A0)>300){lcd.setCursor(0,0);lcd.print("XAVFLI HUDUD");tone(8,700);delay(1000);noTone(8);delay(1000);tone(8,500);delay(1000);noTone(8);delay(1000);tone(8,500);delay(1000);noTone(8);delay(1000);digitalWrite(9,1);delay(100);digitalWrite(9,0);delay(100);digitalWrite(9,1);delay(100);digitalWrite(9,0);delay(100);digitalWrite(9,1);delay(100);digitalWrite(9,0);delay(100);gradus.write(90);}
  

}

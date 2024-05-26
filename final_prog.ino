#define buzzer 4
#define echoPin 5
#define trigPin 6  
#define DHTPIN 7
#define flame 8
#define relay 9
#define DHTTYPE DHT11
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>
int Input = A0;
int R_LED = 2;
int G_LED = 3;
float new_delay; 
int val;
int MAX = 500;


#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);
DHT dht(DHTPIN, DHTTYPE);

void setup() 
{
  Serial.begin (9600); 
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT);
  pinMode(Input ,INPUT);
  pinMode(R_LED ,OUTPUT);
  pinMode(G_LED ,OUTPUT);
  pinMode(buzzer,OUTPUT);
  pinMode(flame, INPUT);
  pinMode(relay, OUTPUT);
  digitalWrite(relay, HIGH);
  Serial.println("DHTxx test!");

  dht.begin();
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  
}


void loop() 
{
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,0);

  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float f = dht.readTemperature(true);
  
 


  long duration, distance;
  digitalWrite(trigPin, LOW);        
  delayMicroseconds(2);              
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);           
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
  new_delay= (distance *3) +30;
  Serial.print(distance);
  Serial.println("  cm");
  if (distance < 200)
  {
   digitalWrite(buzzer,HIGH);
   delay(new_delay);
   digitalWrite(buzzer,LOW);
   display.clearDisplay();
    display.setCursor(0,0);
    display.println("Intruder");
    display.display(); 
  }
  else
  {
    digitalWrite(buzzer,LOW);

  }
  
 delay(200);

 val = analogRead(A0);
  if (val >= MAX) {
    digitalWrite(R_LED ,HIGH);
    digitalWrite(buzzer ,HIGH);
    digitalWrite(G_LED ,LOW);
    Serial.println("GAS LEAKING");

    display.clearDisplay();
    display.setCursor(0,0);
    display.println("Gas       Leakeage");
    display.display();
  }
  else {
    digitalWrite(R_LED ,LOW);
    digitalWrite(buzzer ,LOW);
    digitalWrite(G_LED ,HIGH);
    display.clearDisplay();
    display.println("Temp:");
    display.print(" ");
    display.print(f);
    display.display();
   
  }

  bool Svalue = digitalRead(flame);

  if (Svalue == 0) {
    digitalWrite(relay, LOW);
    digitalWrite(buzzer, HIGH);
    delay(300);
    digitalWrite(buzzer, LOW);
    delay(300);
    digitalWrite(buzzer, HIGH);
    delay(300);
    digitalWrite(buzzer, LOW);
    delay(300);
    digitalWrite(buzzer, HIGH);
    delay(300);
    digitalWrite(buzzer, LOW);
    display.clearDisplay();
    display.setCursor(0,0);
    display.println("Fire      Hazard");
    display.display();
  } else {
    digitalWrite(relay, HIGH);
  }
  
}

#include <Servo.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>
#include "DHT.h"

#define DHTPIN 8
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

LiquidCrystal_I2C lcd(0x27,20,4); 
float R1 = 30000.0;
float R2 = 7500.0; 
float adc_voltage = 0.0;
float v = 0.0;
float ref_voltage = 5.0;
int adc_value = 0;

int servoPin = 9;
Servo myservo;
int angle = 0; 
int fan1=5;
int fan2=4;
int co2=3;
int wheel=2;
int charger=6;
int alcohol=A3;
int flame=7;
int chargest=A0;
int chrgv=0;
int fan1state=0;
int fan2state=0;
//int c=0;
//int current=A2;
int voltage= A1;
int buzzer=10;
const int ACS712_PIN = A2;     
const float ACS712_SENSITIVITY = 66.0;  

void setup() {
  dht.begin();
lcd.init(); 

lcd.backlight();
lcd.setCursor(3,0);
lcd.print("WAPD-6.0");
lcd.setCursor(0,1);
lcd.print("by ELECTRO-NAUTS");
  delay(2000);
lcd.clear();
delay(500);
lcd.setCursor(0,0);
lcd.print("Calibrating...");
lcd.setCursor(0,1);
lcd.print("all Sensors...");
  delay(2000);
lcd.clear();
   myservo.attach(servoPin);

   pinMode(fan1,OUTPUT);
   pinMode(fan2,OUTPUT);
   pinMode(co2,OUTPUT);
   pinMode(wheel,OUTPUT);
   pinMode(charger,OUTPUT);
   pinMode(buzzer,OUTPUT);

   pinMode(chargest,INPUT);
   pinMode(alcohol,INPUT);
   pinMode(flame,INPUT);
   pinMode(ACS712_PIN,INPUT);
   pinMode(voltage,INPUT);

   Serial.begin(9600);
}

void loop() {
  for(int i=0;i<=5;i++){
  chrgv=digitalRead(chargest);
  int a= analogRead(alcohol);
  int f= digitalRead(flame);
int rawACS712Value = analogRead(ACS712_PIN);

adc_value = analogRead(voltage);
adc_voltage  = (adc_value * ref_voltage) / 1023.0;
v = adc_voltage*(R1+R2)/R2;

float cn= ((float)rawACS712Value - 512.0) / 1024.0 * 5000.0 / ACS712_SENSITIVITY;
/*if (cn<0){
  c=0;
}
else {*/
  float c=cn;
//}
  float h = dht.readHumidity();
  float t = dht.readTemperature();

    if (a>250){
      digitalWrite(wheel,HIGH);
      digitalWrite(buzzer,HIGH);
      lcd.setCursor(0,0);
      lcd.print("V=");
      lcd.setCursor(2,0);
      lcd.print(v,1);
      lcd.setCursor(5,0);
      lcd.print("v");
 lcd.setCursor(7,0);
      lcd.print("C-");
      lcd.setCursor(8,0);
      lcd.print(c,2); 
         lcd.setCursor(14,0);
      lcd.print("mA");    
      lcd.setCursor(0,1);
      lcd.print("Alcohol Detected"); 
Serial.println("Alcohol Detected");
Serial.println("|");
Serial.println(t);
Serial.println("|");
Serial.println(h);
Serial.println("|");
Serial.println(v);
Serial.println("|");
Serial.println(c);
Serial.println("|");
delay(500);
      lcd.setCursor(0,1);
      lcd.print("                ");
    }
    else if(f==0&&chrgv==0){
      digitalWrite(co2,LOW);
      digitalWrite(buzzer,HIGH);
      digitalWrite(wheel,HIGH);
      myservo.write(180);
      delay(100);
           lcd.setCursor(0,0);
      lcd.print("V=");
      lcd.setCursor(2,0);
      lcd.print(v,1);
      lcd.setCursor(5,0);
      lcd.print("v");
 lcd.setCursor(7,0);
      lcd.print("C-");
      lcd.setCursor(8,0);
      lcd.print(c,2); 
         lcd.setCursor(14,0);
      lcd.print("mA");    
      lcd.setCursor(0,1);
      lcd.setCursor(0,1);
      lcd.print("Fire Detected"); 
Serial.println("Fire detected,Evacuate");
Serial.println("|");
Serial.println(t);
Serial.println("|");
Serial.println(h);
Serial.println("|");
Serial.println(v);
Serial.println("|");
Serial.println(c);
Serial.println("|");
delay(500);
      lcd.setCursor(0,1);
      lcd.print("                ");
    }
    else if(t>33){
      digitalWrite(fan1,LOW);
      digitalWrite(fan2,HIGH);
      Serial.println(" ");
Serial.println("|");
Serial.println(t);
Serial.println("|");
Serial.println(h);
Serial.println("|");
Serial.println(v);
Serial.println("|");
Serial.println(c);
Serial.println("|");
delay(500);
      lcd.setCursor(0,1);
      lcd.print("                ");
    }
    else if(t>35){
      digitalWrite(fan1,LOW);
      digitalWrite(fan2,LOW);
      fan1state=1;
      fan2state=1;
      Serial.println(" ");
Serial.println("|");
Serial.println(t);
Serial.println("|");
Serial.println(h);
Serial.println("|");
Serial.println(v);
Serial.println("|");
Serial.println(c);
Serial.println("|");
                  lcd.setCursor(0,0);
      lcd.print("V=");
      lcd.setCursor(2,0);
      lcd.print(v,1);
      lcd.setCursor(5,0);
      lcd.print("v");
 lcd.setCursor(7,0);
      lcd.print("C-");
      lcd.setCursor(8,0);
      lcd.print(c,2); 
         lcd.setCursor(14,0);
      lcd.print("mA");    
      lcd.setCursor(0,1); 
      lcd.setCursor(0,1);
      lcd.print("Temperature Rise"); 
      delay(500);
            lcd.setCursor(0,1);
      lcd.print("                ");
    }
    else if(fan1state==1&&fan2state==2&&t>40){
      digitalWrite(buzzer,HIGH);
      digitalWrite(fan1,LOW);
      digitalWrite(fan2,LOW);
      delay(3000);
            digitalWrite(wheel,HIGH);
Serial.println("High temperature");
Serial.println("|");
Serial.println(t);
Serial.println("|");
Serial.println(h);
Serial.println("|");
Serial.println(v);
Serial.println("|");
Serial.println(c);
Serial.println("|");
delay(500);
      lcd.setCursor(0,1);
      lcd.print("                ");
     
    }
    else if(chrgv==1&&f==1){
      digitalWrite(wheel,HIGH);
      digitalWrite(charger,HIGH);
      digitalWrite(fan1,HIGH);
      myservo.write(0);
digitalWrite(fan2,HIGH);
digitalWrite(co2,HIGH);
digitalWrite(buzzer,LOW);
Serial.println("Charging");
Serial.println("|");
Serial.println(t);
Serial.println("|");
Serial.println(h);
Serial.println("|");
Serial.println(v);
Serial.println("|");
Serial.println(c);
Serial.println("|");
           lcd.setCursor(0,0);
      lcd.print("V=");
      lcd.setCursor(2,0);
      lcd.print(v,1);
      lcd.setCursor(5,0);
      lcd.print("v");
 lcd.setCursor(7,0);
      lcd.print("C-");
      lcd.setCursor(8,0);
      lcd.print(c,2); 
         lcd.setCursor(14,0);
      lcd.print("mA");    
      lcd.setCursor(0,1); 
      lcd.setCursor(0,1);
      lcd.print("Charging"); 
      delay(500);
            lcd.setCursor(0,1);
      lcd.print("                ");
      }
     else if (chrgv==1&&f==0){
      digitalWrite(wheel,HIGH);
      digitalWrite(co2,LOW);
      digitalWrite(buzzer,HIGH);
      digitalWrite(charger,LOW);
      digitalWrite(fan1,HIGH);
digitalWrite(fan2,HIGH);
digitalWrite(co2,LOW);
      myservo.write(180);
           lcd.setCursor(0,0);
      lcd.print("V=");
      lcd.setCursor(2,0);
      lcd.print(v,1);
      lcd.setCursor(5,0);
      lcd.print("v");
      lcd.setCursor(7,0);
      lcd.print("C-");
      lcd.setCursor(8,0);
      lcd.print(c,2); 
         lcd.setCursor(14,0);
      lcd.print("mA");    
      lcd.setCursor(0,1);  
      lcd.setCursor(0,1);
      lcd.print("Fire detected"); 

Serial.println("Fire Detected,Evacuate");
Serial.println("|");
Serial.println(t);
Serial.println("|");
Serial.println(h);
Serial.println("|");
Serial.println(v);
Serial.println("|");
Serial.println(c);
Serial.println("|");
delay(500);
      lcd.setCursor(0,1);
      lcd.print("                ");
    }
    else{
  myservo.write(0);
digitalWrite(fan1,HIGH);
digitalWrite(fan2,HIGH);
digitalWrite(co2,HIGH);
digitalWrite(charger,HIGH);
digitalWrite(wheel,LOW);
digitalWrite(buzzer,LOW);
Serial.println("NORMAL");
Serial.println("|");
Serial.println(t);
Serial.println("|");
Serial.println(h);
Serial.println("|");
Serial.println(v);
Serial.println("|");
Serial.println(c);
Serial.println("|");
           lcd.setCursor(0,0);
      lcd.print("V=");
      lcd.setCursor(2,0);
      lcd.print(v,1);
      lcd.setCursor(5,0);
      lcd.print("v");
 lcd.setCursor(7,0);
      lcd.print("C-");
      lcd.setCursor(8,0);
      lcd.print(c,2); 
         lcd.setCursor(14,0);
      lcd.print("mA");    
      lcd.setCursor(4,1);
      lcd.print(" NORMAL"); 
delay(500);
      lcd.setCursor(0,1);
      lcd.print("                "); 
}
 while(i==3&&v<12&&chrgv==0&&a<300&&f==1){
       digitalWrite(wheel,HIGH);
      digitalWrite(co2,HIGH);
      digitalWrite(buzzer,LOW);
      digitalWrite(charger,LOW);
      digitalWrite(fan1,HIGH);
digitalWrite(fan2,HIGH);
      myservo.write(0);
      digitalWrite(buzzer,HIGH);
           lcd.setCursor(0,0);
      lcd.print("V=");
      lcd.setCursor(2,0);
      lcd.print(v,1);
      lcd.setCursor(5,0);
      lcd.print("v");
      lcd.setCursor(7,0);
      lcd.print("C-");
      lcd.setCursor(8,0);
      lcd.print(c,2); 
         lcd.setCursor(14,0);
      lcd.print("mA");    
      lcd.setCursor(0,1);  
      lcd.setCursor(0,1);
      lcd.print("Voltage Drop"); 

Serial.println("Voltage Drop");
Serial.println("|");
Serial.println(t);
Serial.println("|");
Serial.println(h);
Serial.println("|");
Serial.println(v);
Serial.println("|");
Serial.println(c);
Serial.println("|");
delay(500);
      lcd.setCursor(0,1);
      lcd.print("                ");
    }
    
  }

}
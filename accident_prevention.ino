
#include <SoftwareSerial.h>


#include <LiquidCrystal_I2C.h>

#include <Wire.h>

SoftwareSerial mySerial(3, 2);
char phone_no[]="+254759757339"; 

int sensorThres=460;
int sensorValue;
//alcohol sensor connection
int alcoholsensor = A0;
//lcd connections
const int trigPin = 8;
const int echoPin =9 ;
//relayPin connection

//led connection
int led = 4;
//buzzer connection
int buzzerPin = 6;
//Motor A connection
int enA = 5;
int in1 = 13;
int in2 = 7;
// Motor B connections
int enB =10 ;
int in3 =11 ;
int in4 =12 ;


LiquidCrystal_I2C lcd(0x27,16,2);


float duration;
 float distance_cm;

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);

  Serial.println("Initializing...");
  delay(1000);                

  lcd.init();//initialize the lcd
  lcd.clear();//clears the lcd screen
  lcd.backlight();// initialize the backlight
  
    
    pinMode(trigPin, OUTPUT);//sets lcd trigPin as output
   
    pinMode(echoPin, INPUT);//sets lcd echoPin as input
    pinMode(alcoholsensor , INPUT);// sets alcohol sensor as input
    pinMode(led, OUTPUT);//sets the led as output
    pinMode(buzzerPin, OUTPUT);//sets buzzerPin as output
    pinMode(enA, OUTPUT);
    pinMode(enB, OUTPUT);
    pinMode(in1, OUTPUT);
    pinMode(in2, OUTPUT);
    pinMode(in3, OUTPUT);
    pinMode(in4, OUTPUT);
  

}

void loop() {
   int sensorValue = analogRead(alcoholsensor);
    // reads the analog value from MQ3
   sensorValue = analogRead(A0);
 // sends the value to UART for debugging
   Serial.println(sensorValue);
    
 if ( sensorValue < 460 )
 {
 

// This function lets you control spinning direction of motors
  // Set motors to maximum speed
  // For PWM maximum possible values are 0 to 255
   analogWrite(enA, 255);
   analogWrite(enB, 255);
  
   
      // Turn on motor A & B
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    
    
    
    }
 
 else
 {
  
    Serial.begin(9600);
    Serial.println("DRUNK DRIVER");
    SendMessage();
    
     // Turn off motors - Initial state
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
    
  }
void SendMessage()
  {
    Serial.println("I am in send");
    mySerial.println("AT+CMGF=1"); //Sets the GSM Module in Text Mode
    delay(1000); // Delay of 1000 milli seconds or 1 second
    mySerial.println("AT+CMGS=\"+254704678058\"\r"); // Replace x with mobile number
    delay(1000);
    mySerial.println("DRUNK DRIVER");// The SMS text you want to send
    delay(100);
    mySerial.println((char)26);// ASCII code of CTRL+Z
    delay(1000);

    digitalWrite(trigPin, HIGH);
    delay(10);
    
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    Serial.print("duration  ");
   Serial.println(duration); 
    distance_cm =0.034/2* duration;
    //Serial.println(distance_cm); 
    if(distance_cm <=20)
    {
     lcd.setCursor(0,0);
     lcd.clear();
     lcd.print("SLOW DOWN");
     digitalWrite( led, HIGH);// led lights
     digitalWrite(buzzerPin, HIGH);// buzzer rings
     // Decelerate from maximum speed to zero
   // for (int i = 255; i >= 0; --i) {
   //  analogWrite(enA, i);
     //analogWrite(enB, i);
     //delay(20);
     if(distance_cm <=3){
     lcd.setCursor(0,0);
     lcd.clear();
     lcd.print("DANGER!!");
    Serial.begin(9600);
    Serial.println("AT+CMGF=1");    //select text mode
    delay(10);
    Serial.println("AT+CMGS=\"+254759757339\"");  // enter receipent number
    Serial.println("EMERGENCY ");
    }
     else
    {
      lcd.setCursor(0,0);//lcd cursor at 0,0
      lcd.clear();// 
      lcd.print("SAFE");// SAFE is displayed on the lcd
      digitalWrite(led,LOW);// led doesnt light
      digitalWrite(buzzerPin,LOW);// buzzer is silent
       // Accelerate from zero to maximum speed
   /*for (int i = 0; i < 256; i++) {
      analogWrite(enA, i);
      analogWrite(enB, i);
      delay(20);
      }*/
      }
    Serial.print("distance") ; 
    Serial.println(distance_cm);
   // }
    }
}

//Devin Stukel 400306690
//Danial Lariei 400381952 
//Kevin Nguyen  400389285 
//Zac Belal     400408727 
//James Palmer  400391584

#include "LiquidCrystal_I2C.h"
#include "dht11.h"

#define DHT11PIN 17 // DHT11 data pin
#define MotorPin1 19 // Motor control pin 1
#define MotorPin2 18 // Motor control pin 2
#define Trigpin 12 //connect trig to io12
#define Echopin 13 //connect echo to io13

int duration,distance;

LiquidCrystal_I2C lcd(0x27,16,2);

dht11 DHT11;

// Define the Motor function
void Motor() {
  // Turn left
  analogWrite(MotorPin1, 70); // Set PWM duty cycle to 70 (out of 255)
  analogWrite(MotorPin2, 0);  // Set PWM duty cycle to 0
  delay(2000);

  // Stop
  delay(200);
  analogWrite(MotorPin1, 0);
  analogWrite(MotorPin2, 0);
  delay(200);

  // Turn right
  analogWrite(MotorPin1, 0);
  analogWrite(MotorPin2, 70);
  delay(2000);

  // Stop
  delay(200);
  analogWrite(MotorPin1, 0);
  analogWrite(MotorPin2, 0);
  delay(200);
}

void Ultra(){
  digitalWrite(Trigpin, LOW);
  delayMicroseconds(2);
  digitalWrite(Trigpin, HIGH);
  delayMicroseconds(10); // Trigger the trig pin via a high level lasting at least 10us
  digitalWrite(Trigpin, LOW);

  duration = pulseIn(Echopin, HIGH, 30000); // Timeout set to 30ms (max distance ~5m)
  if (duration == 0) {
    Serial.println("Timeout: No pulse detected");
    distance = 0;
  } else {
    distance = duration / 58; // Convert into distance (cm)
  }

  delay(50);
}

void setup() {
  pinMode(DHT11PIN, INPUT);
  pinMode(MotorPin1, OUTPUT);
  pinMode(MotorPin2, OUTPUT);
  pinMode(Trigpin,OUTPUT);  //set trig pin to output mode
  pinMode(Echopin,INPUT);   //set echo pin to input mode

  Serial.begin(9600);
  Serial.println("DHT11 TEST PROGRAM ");
  Serial.print("LIBRARY VERSION: ");
  Serial.println(DHT11LIB_VERSION);
  Serial.println();

  //Initialize LCD
  lcd.init();
  // Turn the (optional) backlight off/on
  lcd.backlight();
  //lcd.noBacklight();

}

void loop() {
  int chk = DHT11.read(DHT11PIN);

  Serial.print("Read sensor: ");
  switch (chk) {
    case DHTLIB_OK:
      Serial.println("OK");
      break;
    case DHTLIB_ERROR_CHECKSUM:
      Serial.println("Checksum error");
      break;
    case DHTLIB_ERROR_TIMEOUT:
      Serial.println("Time out error");
      break;
    default:
      Serial.println("Unknown error");
      break;
  }

  Serial.print("Temperature (°C): ");
  Serial.println((float)DHT11.temperature, 2);

  delay(1000);

  Motor();

    //Set the position o dcursor
  lcd.setCursor(0, 0);
  //LCD prints
  lcd.print((float)DHT11.temperature, 2);

  Ultra();

  Serial.print("Duration: ");
  Serial.print(duration);
  Serial.print(" us, Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  lcd.setCursor(0, 1);
  lcd.print(distance);

}

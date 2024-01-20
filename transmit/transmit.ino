#include <RH_ASK.h>
#include <SPI.h>

RH_ASK driver;
long duration_us, distance_cm;

int trigPin = 6;    // TRIG pin
int echoPin = 7; 
void setup()
{
    pinMode(trigPin, OUTPUT);
  // configure the echo pin to input mode
    pinMode(echoPin, INPUT);
    Serial.begin(9600);    // Debugging only
    if (!driver.init()){
         Serial.println("init failed");
    }
    else{
      Serial.println("Transmitter ok");
    }
}

void loop(){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // measure duration of pulse from ECHO pin
  duration_us = pulseIn(echoPin, HIGH);

  // calculate the distance
  distance_cm = duration_us * 0.017;
  Serial.print("distance: ");
  Serial.print(distance_cm);
  Serial.println(" cm");
  if (distance_cm<35 && distance_cm >5){
    const char *msg = 1;
    driver.send((uint8_t *)msg, strlen(msg));
    driver.waitPacketSent();
    Serial.println("Message sent!");
    //rial.println((char*(msg)));
    delay(1000);
  }
  delay(500);
  
}

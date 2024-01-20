#include <SD.h>                      // need to include the SD library
#define SD_ChipSelectPin 53  //example uses hardware SS pin 53 on Mega2560
#include <TMRpcm.h>           //  also need to include this library...
#include <SPI.h>
#include <RH_ASK.h>

RH_ASK driver;
TMRpcm tmrpcm;   // create an object for use in this sketch
String strd;

void setup(){

  tmrpcm.speakerPin = 6; //5,6,11 or 46 on Mega, 9 on Uno, Nano, etc
  driver.init();
  
  Serial.begin(9600);
  if (!driver.init()){
    Serial.println("RF driver fails");
  }
  else{
    Serial.println("RF driver init success");
    
  }
  
  if (!SD.begin(SD_ChipSelectPin)) {  // see if the card is present and can be initialized:
    Serial.println("SD fail");  
    return;   // don't do anything more if not
  }
  else{
    Serial.println("SD OK");
    //tmrpcm.setVolume(6);
    //tmrpcm.play("audio1.wav"); 
  }

}



void loop(){
  if (driver.available()) {
    // Read the RF data
    uint8_t buf[RH_ASK_MAX_MESSAGE_LEN];
    uint8_t buflen = sizeof(buf);

    if(driver.recv(buf, &buflen)) {
      Serial.print("Received RF Data (Digital Reading): ");
      strd = String((char*)buf);
      Serial.println(strd);
      Serial.println("HI");
  }
  }
  tmrpcm.setVolume(6);
  tmrpcm.play("audio1.wav"); 
  delay(3000);

}

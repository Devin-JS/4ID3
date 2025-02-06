//Devin Stukel 400306690
//Danial Lariei 400381952 
//Kevin Nguyen  400389285 
//Zac Belal     400408727 
//James Palmer  400391584
#include "lora_a.h"

void setup() {

  Serial.begin(9600);
  Serial_1.begin(9600, SERIAL_8N1, 16, 17);

  Transceiver.init();
  Transceiver.SetAddressH(1);
  Transceiver.SetAddressL(1);
  Transceiver.SetAirDataRate(ADR_9600);
  Transceiver.SetChannel(TRANSCEIVER_CHANNEL);
  Transceiver.SetMode(EBYTE_MODE_NORMAL);
  Transceiver.SetTransmitPower(OPT_TP20);
  Transceiver.SaveParameters(PERMANENT);
  Transceiver.PrintParameters();
  
}




void loop() {
  
  if (Serial2.available() > 1) {
    Serial.println("Receving Data...");
    String incomingData = Serial2.readString();
    Serial.println("PING: " + incomingData);

  }

  if(millis() - startTime > TIME_PER_SEND_MS){
    Serial2.println(group_name + " - " + device_name);
    Serial.println("PONG SENT");
    startTime = millis();
  }

}

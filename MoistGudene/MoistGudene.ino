#include <SoftwareSerial.h>
#define SensorPin A0 
SoftwareSerial ESPserial(2, 3); // RX | TX
 
float sensorValue = 0;
 
void setup()
{
  Serial.begin(115200); // communication with the host computer
   
  ESPserial.begin(115200);
   
  Serial.println("Ready"); 
}
 
void loop() 
{
  wifiRead();
  //moistRead();
}

void wifiRead (){
  // listen for communication from the ESP8266 and then write it to the serial monitor
   
  if ( ESPserial.available() ) { Serial.write( ESPserial.read() ); }
   
  // listen for user input and send it to the ESP8266
   
  if ( Serial.available() ) { ESPserial.write( Serial.read() ); }
}

void moistRead(){
  for (int i = 0; i <= 100; i++) 
   { 
     sensorValue = sensorValue + analogRead(SensorPin); 
     delay(1); 
   } 
   sensorValue = sensorValue/100.0; 
   Serial.println(sensorValue); 
   delay(1000); 
}

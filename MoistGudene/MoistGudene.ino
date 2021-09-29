    #include <SoftwareSerial.h>
    #define SensorPin A0 
    SoftwareSerial ESPserial(2, 3); // RX | TX
    
    float sensorValue = 0;
    
    void setup()
    {
      Serial.begin(9600); // communication with the host computer
      ESPserial.begin(9600); // Start the software serial for communication with the ESP8266
      
      Serial.println("");
      Serial.println("Lets get moist");
      
      sendAtCommand("AT+CWJAP=\"Telenor_Guest\"\,\"\"", 5000);//Connect to telenor guest
      sendAtCommand("AT", 1000);

    }
    
    void loop()
    {
      
      // listen for communication from the ESP8266 and then write it to the serial monitor
      if ( ESPserial.available() ) 
      { 
        Serial.write( ESPserial.read() ); 
      }
      
      // listen for user input and send it to the ESP8266
      if ( Serial.available() ) 
      { 
        ESPserial.write( Serial.read() ); 
      }

      //for (int i = 0; i <= 100; i++) 
      //{ 
      //  sensorValue = sensorValue + analogRead(SensorPin); 
      //  delay(1); 
      //} 
      //sensorValue = sensorValue/100.0; 
      //Serial.println(sensorValue); 
      //delay(1000); 
    }


    
    

    String sendAtCommand(const char *toSend, unsigned long milliseconds) {
      String result;
      Serial.print("Sending: ");
      Serial.println(toSend);
      ESPserial.println(toSend);
      unsigned long startTime = millis();
      Serial.print("Received: ");
      while (millis() - startTime < milliseconds) {
        if (ESPserial.available()) {
          char c = ESPserial.read();
          Serial.write(c);
          result += c;  // append to the result string
        }
      }
      Serial.println();  // new line after timeout.
      return result;
    }

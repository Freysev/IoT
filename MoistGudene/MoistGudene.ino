  #include "WiFiEsp.h"
  #include "PubSubClient.h"
  // Emulate Serial1 on pins 6/7 if not present
  #ifndef HAVE_HWSERIAL1
  #include "SoftwareSerial.h"
  SoftwareSerial Serial1(2, 3); // RX, TX
  #endif
  char ssid[] = "Telenor_Guest";            // your network SSID (name)
  char pass[] = "";        // your network password
  int status = WL_IDLE_STATUS;     // the Wifi radio's status
  char server[] = "arduino.cc";

  const char* mqtt_broker = "SERVER_IP";
  const char* mqtt_username = "user";
  const char* mqtt_password = "pass";
  const char* mqtt_topic = "test/test";
  const int mqtt_port = 8883;
  
  // Initialize the Ethernet client object
  WiFiEspClient client;
  PubSubClient pubSubClient(client);
  void setup()
  {
    // initialize serial for debugging
    Serial.begin(9600);
    // initialize serial for ESP module
    Serial1.begin(9600);
    // initialize ESP module
    WiFi.init(&Serial1);
    // check for the presence of the shield
    if (WiFi.status() == WL_NO_SHIELD) {
      Serial.println("WiFi shield not present");
      // don't continue
      while (true);
    }
    // attempt to connect to WiFi network
    while ( status != WL_CONNECTED) {
      Serial.print("Attempting to connect to WPA SSID: ");
      Serial.println(ssid);
      // Connect to WPA/WPA2 network
      status = WiFi.begin(ssid, pass);
    }
    // you're connected now, so print out the data
    Serial.println("You're connected to the network");
    printWifiStatus();
    Serial.println();
    Serial.println("Starting connection to server...");
    // if you get a connection, report back via serial
    if (client.connect(server, 80)) {
      Serial.println("Connected to server");
      // Make a HTTP request
      client.println("GET /asciilogo.txt HTTP/1.1");
      client.println("Host: arduino.cc");
      client.println("Connection: close");
      client.println();
      Serial.println("Request Sent");
    }
    
    //connecting to a mqtt broker
    pubSubClient.setServer(mqtt_broker, mqtt_port);
    pubSubClient.setCallback(callback);
    while (!pubSubClient.connected()) {
        String client_id = "esp8266-client-";
        client_id += String(WiFi.macAddress());
        Serial.printf("The client %s connects to the public mqtt broker\n", client_id.c_str());
        if (pubSubClient.connect(client_id.c_str(), mqtt_username, mqtt_password)) {
            Serial.println("Mqtt broker connected");
        } else {
            Serial.print("failed with state ");
            Serial.print(pubSubClient.state());
            delay(2000);
        }
    }
    // publish and subscribe
    pubSubClient.publish(topic, "hello emqx");
    pubSubClient.subscribe(topic);
  }
  void loop()
  {
    // if there are incoming bytes available
    // from the server, read them and print them
    while (client.available()) {
      char c = client.read();
      Serial.write(c);
    }
    // if the server's disconnected, stop the client
    if (!client.connected()) {
      Serial.println();
      Serial.println("Disconnecting from server...");
      client.stop();
      // do nothing forevermore
      while (true);
    }
  }

  void callback(char *topic, byte *payload, unsigned int length) {
    Serial.print("Message arrived in topic: ");
    Serial.println(topic);
    Serial.print("Message:");
    for (int i = 0; i < length; i++) {
        Serial.print((char) payload[i]);
    }
    Serial.println();
    Serial.println("-----------------------");
  }
  
  void printWifiStatus()
  {
    // print the SSID of the network you're attached to
    Serial.print("SSID: ");
    Serial.println(WiFi.SSID());
    // print your WiFi shield's IP address
    IPAddress ip = WiFi.localIP();
    Serial.print("IP Address: ");
    Serial.println(ip);
    // print the received signal strength
    long rssi = WiFi.RSSI();
    Serial.print("Signal strength (RSSI):");
    Serial.print(rssi);
    Serial.println(" dBm");
  }

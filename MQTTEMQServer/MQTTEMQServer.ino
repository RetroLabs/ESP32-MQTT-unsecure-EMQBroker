/*
 * connects to "broker.emqx.io"
 * Publishes and subcribes to default settings
 */

#include <WiFi.h>
#include <PubSubClient.h>
#include "WifiConnection.h"

//MQTT Setup
const char* mqtt_server = "broker.emqx.io";  
const char *topic = "esp8266/test";
const char *mqtt_username = "emqx";           
const char *mqtt_password = "public";        
const int mqtt_port = 1883;                
String client_id = "ES32-DaveTest";

WiFiClient espClient;
PubSubClient client(espClient);

unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE  (50)
char msg[MSG_BUFFER_SIZE];
int value = 0;
const char message = '0';
int messageCounter = 0;
char b[7];
String str;

void setup() {

  //Initialize Pins
  pinMode(2, OUTPUT);     // Initialize the 2 pin as an output. Onboard Blue LED
  
  //Start Serial
  Serial.begin(115200);

  //Start WIFI
  wifiCon.setupwifi();

  //Start MQTT
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);


}

void loop() {

  //Checks connection to MQTT Broker. Could have better functions split up
  if (!client.connected()) {reconnect();}
  client.loop();

  // increments number published
  messageCounter++;
  str=String(messageCounter);
  str.toCharArray(b,7);
  
  //Send MQTT Data. (message),(topic)
  publishMQTTData(b,topic);

  delay(1000);
  
}


//MQTT function
void reconnect() {
    
    // Loop until we're reconnected
    while(!client.connected()) {

    client.connect(client_id.c_str(), mqtt_username, mqtt_password); 
    Serial.println("Attempting MQTT connection...");
    delay(100);
    }

  if(client.connected()) {
 
      Serial.println("connected");
      
      // Once connected, publish an announcement...
      if(client.publish(topic, "hello world")) {
        Serial.println("topic Published");
        }
        else{
          Serial.println("NOT Published");
          }
      
      if(!client.subscribe(topic)) {
        Serial.println("NOT Subscribed");
        }
        else{
          client.subscribe(topic);
          Serial.println("Topic Subscribed");
        }
    delay(100);
  }
}

//MQTT function
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  //Turn feature off to save power later
  if ((char)payload[0] == '1') {
    
    digitalWrite(2, LOW);   // Turn the LED on for testing.

  } else {
    digitalWrite(2, HIGH);  // Turn the LED off by making the voltage HIGH.
  }
}

//MQTT function
void publishMQTTData(const char* messageToSend, const char*subscriptionTopic) {
  snprintf (msg, MSG_BUFFER_SIZE, messageToSend, value);
    Serial.print("Publish message: ");
    Serial.println(messageToSend);
    client.publish(subscriptionTopic, messageToSend);
  
  }

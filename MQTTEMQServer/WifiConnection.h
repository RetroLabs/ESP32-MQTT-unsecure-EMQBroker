// Used at begining for unsecure connection to MQTT broker


class WifiConnection {

private:
// Update these with values suitable for your network.
//WIFI
const char* ssid = "xxxxx";
const char* password = "xxxxxx";

// the MAC address of your Wifi shield
byte mac[6];

public:
// functions 
WiFiClient espClient;

void setupwifi() {
  
  //We start by connecting to a WiFi network
  delay(10);
  Serial.println();
  Serial.print("Connecting to: ");
  Serial.println(ssid);
  delay(10);

  //Connect to Wifi
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("ESP32 WiFi connected");

  //IP address
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  //Subnet address:
  Serial.print("Subnet: ");
  Serial.println(WiFi.subnetMask());
  
  //Gateway address:
  Serial.print("Gateway: ");
  Serial.println(WiFi.gatewayIP());

  //MAC Address
  WiFi.macAddress(mac);
  Serial.print("MAC: ");
  Serial.print(mac[5],HEX);
  Serial.print(":");
  Serial.print(mac[4],HEX);
  Serial.print(":");
  Serial.print(mac[3],HEX);
  Serial.print(":");
  Serial.print(mac[2],HEX);
  Serial.print(":");
  Serial.print(mac[1],HEX);
  Serial.print(":");
  Serial.println(mac[0],HEX);
  Serial.println("");
}

};

WifiConnection wifiCon;

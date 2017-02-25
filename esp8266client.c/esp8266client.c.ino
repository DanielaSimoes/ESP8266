#include <ESP8266WiFi.h>

const char* ssid     = "RaspWiFi";
const char* password = "raspberry";

const char* host = "192.168.0.1";

void setup() {
  Serial.begin(115200);

  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  Serial.println("scan start");

  // WiFi.scanNetworks will return the number of networks found
  int n = WiFi.scanNetworks();
  Serial.println("scan done");
  if (n == 0){
    Serial.println("no networks found");
  } else {
    Serial.print(n);
    Serial.println(" networks found");
    for (int i = 0; i < n; ++i)
    {
      // Print SSID and RSSI for each network found
      Serial.print(i + 1);
      Serial.print(": ");
      if (WiFi.SSID(i) == ssid){
         // We start by connecting to a WiFi network
          Serial.println();
          Serial.println();
          Serial.print("Connecting to ");
          Serial.println(ssid);
        
          WiFi.begin(ssid, password);
          break;
      }
      Serial.print(WiFi.SSID(i));
      Serial.print(" (");
      Serial.print(WiFi.RSSI(i));
      Serial.print(")");
      Serial.println((WiFi.encryptionType(i) == ENC_TYPE_NONE)?" ":"*");
      delay(10);
    }
  }


  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP()); 

}

void loop() {

  WiFiClient client;
  const int tcpPort = 7891;
  if (!client.connect(host, tcpPort)) {
    Serial.println("connection failed");
    return;
  }

 String data = "message=ok";

   Serial.print("Sending message...: ");
   // Send request to the server:
   client.print(data);
   delay(500); // Can be changed
   
  if (client.connected()) { 
    client.stop();  // DISCONNECT FROM THE SERVER
  }
  Serial.println();
  Serial.println("closing connection");
  delay(5000);
}

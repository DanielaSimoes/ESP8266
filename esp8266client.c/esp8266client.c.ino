#include <ESP8266WiFi.h>

const char* ssid     = "RaspWiFi";
const char* password = "raspberry";

const char* host = "192.168.0.1";

void setup() {
  Serial.begin(115200);
  delay(100);
  pinMode(2, OUTPUT);     // Initialize the LED_BUILTIN pin as an output
  digitalWrite(2, LOW);
  delay(500);

  // We start by connecting to a WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

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

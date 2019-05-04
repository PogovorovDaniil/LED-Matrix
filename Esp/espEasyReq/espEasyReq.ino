#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

ESP8266WebServer server(80);

void handleRoot() {
  if (server.hasArg("str")){
	  Serial.println(server.arg("str"));
  }
  server.send(200, "text/html", "<h1>Хорошо</h1>");
}

void setup() {
  delay(1000);
  Serial.begin(115200);
  Serial.println();
  WiFi.softAP("WI-FI-esp", "00000000");
  WiFi.begin();

  Serial.println(WiFi.softAPIP());
  server.on("/", HTTP_GET, handleRoot);
  server.begin();
  Serial.println("Server started");
}

void loop() 
{
  server.handleClient();
}
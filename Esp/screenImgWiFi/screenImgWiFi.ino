#include "FastLED.h"
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

#define LED_PIN 13

#define x 12
#define y 12

CRGB screen[x][y]; 
CRGB screen1D[x*y]; 

void to1D(CRGB from2D[x][y])
{
	int k = 0;
	 for(int i = 0; i < x; i++)
	 {
		if(i % 2 == 0)
		{
			for(int j = 0; j < y; j++)
			{
				screen1D[k] = from2D[i][j];
				k++;
			}
		}
		else 
		{
			for(int j = y-1; j >= 0; j--)
			{
				screen1D[k] = from2D[i][j];
				k++;	 
			}
		 }
	 }
}

void ImgLoad()
{
	char[] str = server.arg("str");
	k = 0;
	for(int i = 0; i < x; i++)
	{
		for(int j = 0; j < y; j++)
		{
			screen[x][y] = CRGB(uint8_t(str[k]),uint8_t(str[k+1]),uint8_t(str[k+2]));
			k+=3;
		}
	}
	to1D(screen);
	FastLED.show();
}

void setup() 
{
	delay(1000);
	Serial.begin(115200);
	Serial.println();
	Serial.print("Configuring access point...");
	WiFi.softAP("WI-FI-esp", "00000000");
	WiFi.begin();

	Serial.println(WiFi.softAPIP());
	server.on("/", HTTP_GET, ImgLoad);
	server.begin();
	Serial.println("HTTP server started");


	FastLED.addLeds<WS2811, LED_PIN, GRB>(screen1D, x*y).setCorrection(TypicalLEDStrip);
	FastLED.setBrightness(100);
}

void loop() 
{
	server.handleClient();
}

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128  // OLED display width, in pixels
#define SCREEN_HEIGHT 64  // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET -1  // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define NUMFLAKES 10  // Number of snowflakes in the animation example

#define LOGO_HEIGHT 16
#define LOGO_WIDTH 16


#include "WiFi.h"
#include "ESPAsyncWebServer.h"
int adc;
int key;
int adc2;
int send_key;
int key_count1;
int key_count2;
int old_key;
// Set your access point network credentials
const char* ssid = "ESP32-Access-Point";
const char* password = "123456789";

String readTemp() {
  return String(send_key);
}


// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

void setup(){
  // Serial port for debugging purposes
  Serial.begin(115200);
  Serial.println();
  
  
  //lcd
//lcd
    // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
   display.setTextSize(2);  
  display.display();
  delay(500); // Pause for 2 seconds
  display.clearDisplay();
  display.println(F("MAZAND MACHINE"));
  display.display();

  Serial.print("Setting AP (Access Point)…");
  // Remove the password parameter, if you want the AP (Access Point) to be open
  WiFi.softAP(ssid, password);

  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);

  server.on("/temperature", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", readTemp().c_str());
  });
  // server.on("/humidity", HTTP_GET, [](AsyncWebServerRequest *request){
  //   request->send_P(200, "text/plain", readHumi().c_str());
  // });
  // server.on("/pressure", HTTP_GET, [](AsyncWebServerRequest *request){
  //   request->send_P(200, "text/plain", readPres().c_str());
  // });
  
  bool status;


  server.begin();
}
 
void loop(){
  key_board();
  read_();
 
}

void read_(){
 
}
// #include <SPI.h>
// #include <Wire.h>
// #include <Adafruit_GFX.h>
// #include <Adafruit_SSD1306.h>
// #define SCREEN_WIDTH 128  // OLED display width, in pixels
// #define SCREEN_HEIGHT 64  // OLED display height, in pixels
// #define OLED_RESET -1     // Reset pin # (or -1 if sharing Arduino reset pin)
// Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
// #define NUMFLAKES 10  // Number of snowflakes in the animation example
// #define LOGO_HEIGHT 16
// #define LOGO_WIDTH 16


int pulse;
int speed;
int pulse1;
int speed1;
int change;
//**********keypad*********
#include <Keypad.h>
#define ROW_NUM 4     // four rows
#define COLUMN_NUM 4  // three columns
char keys[ROW_NUM][COLUMN_NUM] = {
  { '1', '2', '3', 'A' },
  { '4', '5', '6', 'B' },
  { '7', '8', '9', 'C' },
  { '*', '0', '#', 'D' }
};
byte pin_rows[ROW_NUM] = { 4, 16, 17, 18 };                                           // GPIO18, GPIO5, GPIO17, GPIO16 connect to the row pins
byte pin_column[COLUMN_NUM] = { 27, 14, 12, 13 };                                     // GPIO4, GPIO0, GPIO2 connect to the column pins
Keypad keypad = Keypad(makeKeymap(keys), pin_rows, pin_column, ROW_NUM, COLUMN_NUM);  //salam

#include "WiFi.h"
#include "ESPAsyncWebServer.h"
int adc;
int key;
int adc2;
int send_key;
int key_count1;
int key_count2;
int old_key;
const char* ssid = "ESP32-Access-Point";
const char* password = "123456789";
AsyncWebServer server(80);

String readTemp() {
  return String(send_key);
}

void setup() {
  // Serial port for debugging purposes
  Serial.begin(115200);
  Serial.println();

  change = 1;
  pulse1 = 5;
  speed1 = 500;
  pulse = 2;
  speed = 1;
  //lcd
  // if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
  //   Serial.println(F("SSD1306 allocation failed"));
  //   for (;;)
  //     ;  // Don't proceed, loop forever
  // }
  // display.display();
  // display.clearDisplay();
  // display.setTextSize(1);       // Normal 1:1 pixel scale
  // display.setTextColor(WHITE);  // Draw white text
  // display.setCursor(0, 0);      // Start at top-left corner
  // display.println(F("** MAZAND MACHINE **"));
  // display.display();

  // Remove the password parameter, if you want the AP (Access Point) to be open
  WiFi.softAP(ssid, password);
  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);
  server.on("/temperature", HTTP_GET, [](AsyncWebServerRequest* request) {
    request->send_P(200, "text/plain", readTemp().c_str());
  });
  bool status;
  server.begin();
}

void loop() {
  key_board_();
  delay(50);
  //lcd();
}



void key_board_() {

  char key = keypad.getKey();
  if (key) {
    change = 1;
    Serial.println(key);
    if (key == '1') {
      send_key = 10;
    }

    if (key == '2') {
      send_key = 20;
    }

    if (key == '3') {
      send_key = 70;
    }

    if (key == '4') {
      send_key = 0;
    }

    if (key == '5') {
      send_key = 21;
    }

    if (key == '6') {
      send_key = 12;
    }


    if (key == '7') {
      send_key = 40;
    }

    if (key == '8') {
      send_key = 4;
    }

    if (key == '9') {
      send_key = 8;
    }

    if (key == '0') {
      send_key = 2;
    }

    if (key == 'A') {
      send_key = 13;
      ++pulse;
    }

    if (key == 'B') {
      send_key = 30;
      --pulse;
    }

    if (key == 'C') {
      send_key = 6;
      ++speed;
    }

    if (key == 'D') {
      send_key = 1;
      --speed;
    }

    if (key == '*') {
      send_key = 3;
    }

    if (key == '#') {
      send_key = 60;
    }

  delay(50);
    //////
  } else {

    send_key = 11;
  }
}
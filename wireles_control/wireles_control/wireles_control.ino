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
int led = 23;
String readTemp() {
  return String(send_key);
}


////new lib
#include <esp_netif.h>
#include <esp_event.h>
#include <esp_wifi.h>


int check;
void setup() {
  // Serial port for debugging purposes
  Serial.begin(115200);
  Serial.println();
  pinMode(led, OUTPUT);
  digitalWrite(led, HIGH);  // turn the LED on (HIGH is the voltage level)
  delay(1000);              // wait for a second
  digitalWrite(led, LOW);   // turn the LED off by making the voltage LOW
  change = 1;
  pulse1 = 5;
  speed1 = 500;
  pulse = 2;
  speed = 1;
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
  if (check == 0) {
    connect();
  }
}

void connect() {
  String response = "Connected devices:\n";
  // ساختار برای ذخیره اطلاعات دستگاه‌های متصل
  wifi_sta_list_t stationList;
  esp_netif_sta_list_t netif_sta_list;
  // گرفتن لیست دستگاه‌های متصل
  esp_wifi_ap_get_sta_list(&stationList);
  esp_netif_get_sta_list(&stationList, &netif_sta_list);

  // نمایش مک آدرس دستگاه‌های متصل
  for (int i = 0; i < stationList.num; i++) {
    esp_netif_sta_info_t station = netif_sta_list.sta[i];
    char mac[18];
    sprintf(mac, "%02X:%02X:%02X:%02X:%02X:%02X", station.mac[0], station.mac[1], station.mac[2], station.mac[3], station.mac[4], station.mac[5]);
    response += String(mac) + "\n";
  }
  String sub1 = response.substring(19, 21);  ///ch
  if (sub1 == "8C") {
    digitalWrite(led, HIGH);  // turn the LED on (HIGH is the voltage level)
  }
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
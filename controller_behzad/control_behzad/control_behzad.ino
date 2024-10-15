////wifi////
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
ESP8266WiFiMulti WiFiMulti;


#include "Arduino.h"
#include <SoftwareSerial.h>
SoftwareSerial hwSerial(4, 5);  // RX | TX
int uart_enbale = 15;
int start_pin = 13;
int pause_pin = 14;
int reset_pin = 12;
String wifi_input;
float step_count;
int speed_count;
String my_send;
int start_lcd;
int state = 0;
int connect = 0;
int first_send;
int send_command;
char inchar;
String ReadString;
int ok_count;
int send_;
int gcode_line;
String read_resume_line;
int flash_test;
int connect_count;
int reset_count;
void setup() {
  pinMode(uart_enbale, OUTPUT);
  pinMode(reset_pin, OUTPUT);
  pinMode(start_pin, OUTPUT);
  pinMode(pause_pin, OUTPUT);
  digitalWrite(uart_enbale, LOW);
  Serial.begin(115200);
  hwSerial.begin(115200);
  digitalWrite(uart_enbale, HIGH);

  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP("ESP32-Access-Point", "123456789");
  speed_count = 2000;
  step_count = 10;

  digitalWrite(uart_enbale, HIGH);
  delay(500);
  my_send = "$X";
  hwSerial.println(my_send);
  Serial.print(my_send);
  delay(10);
  my_send = "$$";
  hwSerial.println(my_send);
  Serial.print(my_send);
  while (hwSerial.available() > 0) {
    ReadString = hwSerial.readStringUntil('\n');
    ReadString.trim();
    Serial.println(ReadString);
    String sub1 = ReadString.substring(0, 2);
    if (sub1 == "ok") {
      connect = 1;
      Serial.println("Connected to GRBL");
    }
  }

  delay(100);
  digitalWrite(uart_enbale, LOW);
}

void loop() {

  if (connect == 0) {
    delay(100);
    ++connect_count;
    if (connect_count >= 3) {
      ++reset_count;
      if (reset_count >= 3) {
        Serial.print("reset avr");
        reset_count = 0;
        digitalWrite(reset_pin, HIGH);
        delay(100);
        digitalWrite(reset_pin, LOW);
        delay(100);
      }
      delay(300);
      connect_count = 0;
      digitalWrite(uart_enbale, HIGH);
      delay(10);
      my_send = "$X";
      hwSerial.println(my_send);
      Serial.print(my_send);
      my_send = "$X";
      hwSerial.println(my_send);
      Serial.print(my_send);
      delay(50);
      my_send = "$$";
      hwSerial.println(my_send);
      delay(50);
      digitalWrite(uart_enbale, LOW);
      Serial.print(my_send);
      while (hwSerial.available() > 0) {
        ReadString = hwSerial.readStringUntil('\n');
        ReadString.trim();
        String sub1 = ReadString.substring(0, 2);
        if (sub1 == "ok") {
          connect = 1;
          Serial.println("Connected to GRBL");
        }
      }
    }

    while (hwSerial.available() > 0) {
      ReadString = hwSerial.readStringUntil('\n');
      ReadString.trim();
      String sub1 = ReadString.substring(0, 2);
      if (sub1 == "ok") {
        connect = 1;
        Serial.println("Connected to GRBL");
      }
    }
  }




  if ((WiFiMulti.run() == WL_CONNECTED)) {
    WiFiClient client;
    HTTPClient http;
    if (http.begin(client, "http://192.168.4.1/temperature")) {  // HTTP
      int httpCode = http.GET();
      if (httpCode > 0) {
        //Serial.printf("[HTTP] GET... code: %d\n", httpCode);
        if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
          String payload = http.getString();

          wifi_input = payload;

          if (wifi_input != "11") Serial.println(wifi_input);
          //************Y+*************
          if (wifi_input == "2") {

            digitalWrite(uart_enbale, HIGH);
            my_send = "$J=G91Y" + String(step_count) + "F" + String(speed_count);
            delay(50);
            hwSerial.println(my_send);
            Serial.println(my_send);
            delay(1);
            digitalWrite(uart_enbale, LOW);
            delay(300);
          }


          //************Y-*************
          if (wifi_input == "8") {

            digitalWrite(uart_enbale, HIGH);
            delay(50);
            my_send = "$J=G91Y-" + String(step_count) + "F" + String(speed_count);

            hwSerial.println(my_send);
            Serial.println(my_send);
            delay(1);
            digitalWrite(uart_enbale, LOW);
            delay(300);
          }


          //************x+*************
          if (wifi_input == "4") {

            digitalWrite(uart_enbale, HIGH);
            my_send = "$J=G91X-" + String(step_count) + "F" + String(speed_count);
            delay(50);
            hwSerial.println(my_send);
            Serial.println(my_send);
            delay(1);
            digitalWrite(uart_enbale, LOW);
            delay(300);
          }

          //************x-*************
          if (wifi_input == "6") {

            digitalWrite(uart_enbale, HIGH);
            delay(50);
            my_send = "$J=G91X" + String(step_count) + "F" + String(speed_count);
            // my_send = "$J=G91X2.0F500";
            hwSerial.println(my_send);
            Serial.println(my_send);
            delay(1);
            digitalWrite(uart_enbale, LOW);
            delay(300);
          }


          //************Z+*************
          if (wifi_input == "1") {

            digitalWrite(uart_enbale, HIGH);
            delay(50);
            my_send = "$J=G91Z" + String(step_count) + "F" + String(speed_count);
            // my_send = "$J=G91X2.0F500";
            hwSerial.println(my_send);
            Serial.println(my_send);
            delay(1);
            digitalWrite(uart_enbale, LOW);
            delay(300);
          }

          //************Z-*************
          if (wifi_input == "3") {

            digitalWrite(uart_enbale, HIGH);
            delay(50);
            my_send = "$J=G91Z-" + String(step_count) + "F" + String(speed_count);
            hwSerial.println(my_send);
            Serial.println(my_send);
            delay(1);
            digitalWrite(uart_enbale, LOW);
            delay(300);
          }

          //************ZERO x*************
          if (wifi_input == "0") {
            digitalWrite(uart_enbale, HIGH);
            my_send = "G92 X0";
            delay(50);
            hwSerial.println(my_send);
            Serial.println(my_send);
            delay(100);
            digitalWrite(uart_enbale, LOW);
            delay(300);
          }

           //************ZERO y*************
          if (wifi_input == "21") {
            digitalWrite(uart_enbale, HIGH);
            my_send = "G92 Y0";
            delay(50);
            hwSerial.println(my_send);
            Serial.println(my_send);
            delay(100);
            digitalWrite(uart_enbale, LOW);
            delay(300);
          }

          //************ZERO z*************
          if (wifi_input == "12") {
            digitalWrite(uart_enbale, HIGH);
            my_send = "G92 Z0";
            delay(50);
            hwSerial.println(my_send);
            Serial.println(my_send);
            delay(100);
            digitalWrite(uart_enbale, LOW);
            delay(300);
          }

           //************ZERO z*************
          if (wifi_input == "13") {
            digitalWrite(uart_enbale, HIGH);
            my_send = "G92 X0 Y0 Z0";
            delay(50);
            hwSerial.println(my_send);
            Serial.println(my_send);
            delay(100);
            digitalWrite(uart_enbale, LOW);
            delay(300);
          }

          //************HOME*************
          if (wifi_input == "60") {
            digitalWrite(uart_enbale, HIGH);
            delay(50);
            hwSerial.println("$H");
            delay(1);
            digitalWrite(uart_enbale, LOW);
            delay(3000);
          }

          //************BLINK*************
          if (wifi_input == "5") {

            digitalWrite(uart_enbale, HIGH);
            delay(50);
            Serial.print("home");
            hwSerial.println("M3 S1000");
            delay(50);
            hwSerial.println("G1 F1000");
            delay(150);
            hwSerial.println("M5 S0");
            delay(50);
            hwSerial.println("G0");
            delay(100);
            digitalWrite(uart_enbale, LOW);
            delay(3000);
          }

          //********step_setting**********
          if (wifi_input == "30") {

            if (step_count < 1) {
              step_count = step_count + .1;
            } else if (step_count >= 1 && step_count < 10) {
              step_count = step_count + 1;
            } else if (step_count >= 10 && step_count < 50) {
              step_count = step_count + 5;
            } else if (step_count >= 50) {
              step_count = step_count + 50;
            }
            if (step_count > 200) step_count = 200;
            Serial.println(String(step_count));
            delay(100);
          }

          if (wifi_input == "40") {

            if (step_count <= 1) {
              step_count = step_count - .1;
            } else if (step_count > 1 && step_count <= 10) {
              step_count = step_count - 1;
            } else if (step_count > 10 && step_count <= 50) {
              step_count = step_count - 5;
            } else if (step_count > 50) {
              step_count = step_count - 50;
            }

            if (step_count > 200) step_count = 200;
            else if (step_count < .1) step_count = .1;
            Serial.println(String(step_count));
            delay(100);
          }

          if (wifi_input == "10") {
            digitalWrite(start_pin, HIGH);
            delay(300);
            digitalWrite(start_pin, LOW);
            delay(300);
          }

          if (wifi_input == "70") {
            digitalWrite(pause_pin, HIGH);
            delay(300);
            digitalWrite(pause_pin, LOW);
            delay(300);
          }


          if (wifi_input == "20") {
            digitalWrite(reset_pin, HIGH);
            delay(100);
            digitalWrite(reset_pin, LOW);
            delay(100);
          }
          //********speed_setting**********
          // if (wifi_input == "30") {
          //   speed_count = speed_count + 500;
          //   if (speed_count > 40000) speed_count = 40000;
          //   Serial.println(String(speed_count));
          //   delay(100);
          // }

          // if (wifi_input == "40") {
          //   speed_count = speed_count - 500;
          //   if (speed_count < 500) speed_count = 500;
          //   Serial.println(String(speed_count));
          //   delay(100);
          // }
          wifi_input = "";
          //delay(200);
        }
      }
    }
  }
}

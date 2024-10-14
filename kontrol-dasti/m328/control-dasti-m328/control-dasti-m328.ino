
int k_up = 9;
int k_down = 10;
int k_right = 11;
int k_left = 12;

int k_start = 13;
int k_stop = A0;

int uart = 3;

#include <SoftwareSerial.h>
SoftwareSerial simserial(7, 2);  // RX | TX

void setup() {
  Serial.begin(115200);
  simserial.begin(115200);
  pinMode(k_up, INPUT);
  pinMode(k_down, INPUT);
  pinMode(k_right, INPUT);
  pinMode(k_left, INPUT);
  pinMode(k_start, INPUT);
  pinMode(k_stop, INPUT);
  pinMode(uart, OUTPUT);

delay(2000);
    digitalWrite(uart, HIGH);
    delay(200);
    simserial.println("$X");
    delay(200);
    simserial.println("$$");
    delay(200);
    digitalWrite(uart, LOW);
    Serial.println("start...");
}

void loop() {
  //button();
/////////////////////////////////////////////up////////////////////////////
   if (digitalRead(k_up) == 0) {
    Serial.println("up");
    //simserial.println("$J=F2000 G91 X-1000");
    digitalWrite(uart, HIGH);
    delay(1);
    while (1) {
      simserial.println("$J=G91X-0.1F500");
      delay(10);  // 10
      if (digitalRead(k_up) == 1) {
        digitalWrite(uart, LOW);
        break;
      }
    }
    delay(10);  // 20
  }
/////////////////////////////////////////down/////////////////////////////////////
  if (digitalRead(k_down) == 0) {
    Serial.println("down");
    digitalWrite(uart, HIGH);
    delay(1);
    // simserial.println("$J=F2000 G91 X1000");
    while (1) {
      simserial.println("$J=G91X0.1F500");
      delay(10);  // 20
      if (digitalRead(k_down) == 1) {
        digitalWrite(uart, LOW);
        break;
      }
    }
    delay(10);  // 20
  }

  ///////////////////////////right///////////////////////////////////
   if (digitalRead(k_right) == 0) {
    Serial.println("right");
    digitalWrite(uart, HIGH);
    delay(20);
    // simserial.println("$J= G91F2000 Z3000");
    while (1) {
      simserial.println("$J=G91Z0.4F1000");
      delay(50);
      if (digitalRead(k_right) == 1) {
        digitalWrite(uart, LOW);
        break;
      }
    }
    delay(10);
  }
///////////////////////////left//////////////////////////////////////
  if (digitalRead(k_left) == 0) {
    Serial.println("left");
    //simserial.println("$J= G91F2000 Z-3000");
    digitalWrite(uart, HIGH);
    delay(1);
    // simserial.println("$J= G91F2000 Z3000");
    while (1) {
      simserial.println("$J=G91Z-0.5F1000");
      delay(50);
      if (digitalRead(k_left) == 1) {
        digitalWrite(uart, LOW);
        break;
      }
    }
    delay(10);
  }

  ////////////////////start/////////////////////////////
   if (digitalRead(k_start) == 0) {
    Serial.println("start");
    digitalWrite(uart, HIGH);
    delay(200);
    simserial.println("$X");
    delay(200);
    simserial.println("$$");
    delay(200);
    digitalWrite(uart, LOW);
  }
}

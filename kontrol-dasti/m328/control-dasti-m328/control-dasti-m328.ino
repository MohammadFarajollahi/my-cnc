
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
  Serial.println("start...");
  pinMode(k_up, INPUT);
  pinMode(k_down, INPUT);
  pinMode(k_right, INPUT);
  pinMode(k_left, INPUT);
  pinMode(k_start, INPUT);
  pinMode(k_stop, INPUT);
  pinMode(uart, OUTPUT);
}

void loop() {
  button();
}

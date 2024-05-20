
//*****usb*****
#include <Ch376msc.h>
Ch376msc flashDrive(26, SPI_SCK_MHZ(16));  // chipSelect 16
char adatBuffer[255];                      // max length 255 = 254 char + 1 NULL character
char adat[] = "Vivamus nec nisl molestie, blandit diam vel, varius mi. Fusce luctus cursus sapien in vulputate.\n";
char adat2[] = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Duis efficitur ac est eu pharetra. \n";
//..............................................................................................................................
unsigned long totSect = 0;
unsigned long freeSect = 0;
byte percentg = 0;
byte tmpCommand;  //used to store data coming from serial port
boolean readMore;

//#include <esp_task_wdt.h>
//3 seconds WDT
#define WDT_TIMEOUT 1
#include "EEPROM.h"
#define EEPROM_SIZE 256
#include "Arduino.h"
#include <SPI.h>
#include <FS.h>
#include <SD.h>
#include <TFT_eSPI.h>
TFT_eSPI tft = TFT_eSPI();
#include <JPEGDecoder.h>
//****touch*****
#define CALIBRATION_FILE "/TouchCalData3"
#define REPEAT_CAL false
bool SwitchOn = false;

// Comment out to stop drawing black spots
#define BLACK_SPOT
// Switch position and size
#define FRAME_X 100
#define FRAME_Y 64
#define FRAME_W 120
#define FRAME_H 50
// Red zone size
#define REDBUTTON_X FRAME_X
#define REDBUTTON_Y FRAME_Y
#define REDBUTTON_W (FRAME_W / 2)
#define REDBUTTON_H FRAME_H
// Green zone size
#define GREENBUTTON_X (REDBUTTON_X + REDBUTTON_W)
#define GREENBUTTON_Y FRAME_Y
#define GREENBUTTON_W (FRAME_W / 2)
#define GREENBUTTON_H FRAME_H

uint16_t x_t, y_t;  // touch
int touch_change;
//int led = 2;
int buzzer = 34;  //17;

int pus = 17;
int play = 32;


#define minimum(a, b) (((a) < (b)) ? (a) : (b))
//#include "bitmap.h"
//#include "jpeg1.h"


HardwareSerial hwSerial(1);
int uart_enbale = 13;
float step_count;
int speed_count;
String my_send;
int start_lcd;
int state = 0;
int lcd_start;
int lcd_clear;
int sd_state;
int lcd_row;
int connect = 0;
int first_send;
int send_command;
char inchar;
String ReadString;
int ok_count;
int send_;
int ac = 25;
int ac_count;
int resume_mode;
int line_number;
int line_number2;
int gcode_line;
String read_resume_line;
int flash_test;


//*****************for read files*******************
String files[150];
int count_files;
int page;
int file_select;
int exit_main;
int hasan;
int page_number1;
int ii;
int jj;
int count_l;
String select_file[10];
String file_name;
String file1;
int usb;
int usb_in;
int usb_in_count;
int load_again;
int send_gcode;
//**********keypad*********
#include <Keypad.h>
#define ROW_NUM 4     // four rows
#define COLUMN_NUM 3  // three columns
char keys[ROW_NUM][COLUMN_NUM] = {
  { '1', '2', '3' },
  { '4', '5', '6' },
  { '7', '8', '9' },
  { '*', '0', '#' }
};
byte pin_rows[ROW_NUM] = { 22, 21, 3, 16 };                                           // GPIO18, GPIO5, GPIO17, GPIO16 connect to the row pins
byte pin_column[COLUMN_NUM] = { 27, 14, 12 };                                         // GPIO4, GPIO0, GPIO2 connect to the column pins
Keypad keypad = Keypad(makeKeymap(keys), pin_rows, pin_column, ROW_NUM, COLUMN_NUM);  //salam
int main_run;
//********************setup********************
void setup() {
  //***usb***
  flashDrive.init();

  Serial.begin(115200);
  Serial.println("start...");
  //***************eeprom********************
  EEPROM.begin(EEPROM_SIZE);

  //eeprom for first
  //  step_count = 1;
  //  speed_count = 500;
  //  EEPROM.writeFloat(0, step_count);
  //  delay(50);
  //  EEPROM.commit();
  //  delay(50);
  //  EEPROM.writeFloat(10, speed_count);
  //  delay(50);
  //  EEPROM.commit();
  //  delay(50);

  resume_mode = EEPROM.readFloat(0);
  line_number = EEPROM.readFloat(20);

  Serial.print("Resum mode:");
  Serial.println(String(resume_mode));
  Serial.print("Line number:");
  Serial.println(String(line_number));

  //  step_count = EEPROM.readFloat(0);
  //  delay(50);
  //  speed_count = EEPROM.readFloat(10);
  //  delay(50);
  speed_count = 30000;
  step_count = 20;


  digitalWrite(22, HIGH);  // Touch controller chip select (if used)
  digitalWrite(15, HIGH);  // TFT screen chip select
  digitalWrite(5, HIGH);   // SD card chips select, must use GPIO 5 (ESP32 SS)
  pinMode(buzzer, OUTPUT);

  pinMode(pus, OUTPUT);
  pinMode(play, OUTPUT);

  digitalWrite(pus, HIGH);
  digitalWrite(play, HIGH);
  //  digitalWrite(play, HIGH);
  //  delay(500);
  //  digitalWrite(pus, LOW);
  //  digitalWrite(play, LOW);
  //  delay(500);
  //  digitalWrite(pus, HIGH);
  //  digitalWrite(play, HIGH);

  pinMode(ac, INPUT);
  digitalWrite(buzzer, HIGH);
  delay(100);
  digitalWrite(buzzer, LOW);
  delay(100);
  digitalWrite(buzzer, HIGH);
  delay(200);
  digitalWrite(buzzer, LOW);
  pinMode(uart_enbale, OUTPUT);

  //****lcd start***
  tft.begin();

  //*******sd card*******
  Serial.println("check sd card");
  if (!SD.begin()) {
    Serial.println("Card Mount Failed");
    sd_state = 0;
    return;
  }
  uint8_t cardType = SD.cardType();

  if (cardType == CARD_NONE) {
    Serial.println("No SD card attached");
    sd_state = 0;
    return;
  }
  Serial.print("SD Card Type: ");
  if (cardType == CARD_MMC) {
    Serial.println("MMC");
    sd_state = 1;
  } else if (cardType == CARD_SD) {
    Serial.println("SDSC");
    sd_state = 1;
  } else if (cardType == CARD_SDHC) {
    Serial.println("SDHC");
    sd_state = 1;
  } else {
    Serial.println("UNKNOWN");
    sd_state = 1;
  }
  uint64_t cardSize = SD.cardSize() / (1024 * 1024);
  Serial.printf("SD Card Size: %lluMB\n", cardSize);
  Serial.println("initialisation done.");

  //*****lcd******
  tft.setRotation(3);  // portrait
  tft.fillScreen(TFT_WHITE);
  tft.init();
  tft.setRotation(1);  // portrait
                       //**************touch***********
                       //*****calivratio for first
  // SPIFFS.remove(CALIBRATION_FILE);
  // SPIFFS.format();
  // SPIFFS.begin();
  // touch_calibrate();


  lcd_clear = 1;
  show_lcd("booting system...");
  if (sd_state == 1) {
    show_lcd("sd card insert");
    //    String ss = cardSize + "mb";
    //    show_lcd(ss);
    show_lcd("initialisation done.");
    show_lcd("list all data in sd card");
    //listDir(SD, "/files", 0);
  }
  if (sd_state == 0) {
    show_lcd("sd card failed.");
    show_lcd("insert sd card to boot the system...");
  }



  delay(1000);
  tft.fillScreen(TFT_BLACK);

  hwSerial.begin(115200, SERIAL_8N1, 33, 32);  //(rx,tx)

  //int x = (tft.width()  - 300) / 2 - 1;
  // int y = (tft.height() - 300) / 2 - 1;

  // drawArrayJpeg(logo, sizeof(logo), 0, 0); // Draw a jpeg image stored in memory at x,y
  //  drawArrayJpeg(Baboon40, sizeof(Baboon40), 0, 0); // Draw a jpeg image stored in memory
  //tft.pushImage(0,0,480,320,menu );
  //delay(2000);
  start_show();

  digitalWrite(uart_enbale, HIGH);
  digitalWrite(buzzer, HIGH);
  delay(100);
  digitalWrite(buzzer, LOW);
  delay(100);
  my_send = "$X";
  hwSerial.println(my_send);
  Serial.print(my_send);
  print_lcd(my_send);
  print_lcd2("CONECTING...");
  my_send = "$$";
  hwSerial.println(my_send);
  Serial.print(my_send);
  while (hwSerial.available() > 0) {
    ReadString = hwSerial.readStringUntil('\n');
    ReadString.trim();
    Serial.println(ReadString);
    if (ReadString == "ok" && connect == 0) {
      connect = 1;
      print_lcd2("CONECTED");
      drawSdJpeg("/on_button.jpg", 415, 275);
    }
  }
  delay(100);
  digitalWrite(uart_enbale, LOW);
}


void start_show() {
  tft.setTextSize(1);
  tft.fillScreen(TFT_WHITE);
  drawSdJpeg("/menu.jpg", 0, 0);
  if (connect == 0) drawSdJpeg("/off_button.jpg", 415, 275);
  if (connect == 1) drawSdJpeg("/on_button.jpg", 415, 275);

  tft.setTextColor(TFT_BLACK, TFT_WHITE);
  tft.setCursor(65, 210);
  tft.println(String(step_count));

  tft.setTextColor(TFT_BLACK, TFT_WHITE);
  tft.setCursor(55, 280);
  tft.println(String(speed_count));
  flash_test = 0;
}

void input_serial() {
  //while (hwSerial.available() == 0) {}
  while (hwSerial.available() > 0) {
    ReadString = hwSerial.readStringUntil('\n');
    ReadString.trim();
    Serial.println(ReadString);
    if (ReadString == "ok" && connect == 0) {
      connect = 1;
      print_lcd2("CONECTED");
      drawSdJpeg("/on_button.jpg", 415, 275);
    }
  }
}

void loop() {
  input_touch();
  input_serial();
  usb_check();
  keypad_();
  main_run = 0;
}



//****************************LCD_PRINT*******************************
//****************************LCD_PRINT*******************************
//****************************LCD_PRINT*******************************
void print_lcd(String text1) {
  tft.fillRoundRect(142, 8, 165, 20, 5, TFT_WHITE);
  tft.setTextFont(2);
  tft.setTextColor(TFT_BLACK, TFT_WHITE);
  tft.setTextSize(1);
  tft.setCursor(143, 10);
  tft.println(text1);
}

void print_lcd2(String text2) {
  tft.fillRoundRect(142, 38, 165, 20, 5, TFT_WHITE);
  tft.setTextFont(2);
  tft.setTextColor(TFT_BLACK, TFT_WHITE);
  tft.setTextSize(1);
  tft.setCursor(143, 40);
  tft.println(text2);
}

void show_lcd(String text3) {
  if (lcd_clear == 1) {
    tft.fillScreen(TFT_WHITE);
    lcd_clear = 0;
  }
  //tft.fillRoundRect(148, 38, 155, 20, 5 , TFT_WHITE);
  tft.setTextFont(2);
  tft.setTextColor(TFT_BLACK, TFT_WHITE);
  tft.setTextSize(1);
  //if (lcd_start == 0)tft.setCursor(0, 0);
  tft.setCursor(0, lcd_row);
  lcd_row = lcd_row + 20;
  if (lcd_row >= 320) {
    lcd_row = 0;
  }
  tft.println(text3);
}

//*********************touch***********************
//*********************touch***********************
//*********************touch***********************
//*********************touch***********************
void input_touch() {

  if (tft.getTouch(&x_t, &y_t)) {
    touch_change = 1;
    // tft.fillRoundRect(378, 3, 100, 15, 5, TFT_WHITE);
    // tft.setCursor(380, 5);
    // String s1 = "x:" + String(x_t) + "  y:" + String(y_t);
    // tft.setTextFont(2);
    // tft.setTextSize(1);
    // tft.setTextColor(TFT_BLACK, TFT_WHITE);
    // tft.println(s1);


    //**************on_off*****************
    if (x_t > 430 && x_t < 480 && y_t > 260 && y_t < 320) {
      tft.init();
      digitalWrite(uart_enbale, HIGH);
      digitalWrite(buzzer, HIGH);
      delay(100);
      digitalWrite(buzzer, LOW);
      delay(100);
      my_send = "$X";
      hwSerial.println(my_send);
      Serial.print(my_send);
      print_lcd(my_send);
      print_lcd2("CONECTING...");
      my_send = "$$";
      hwSerial.println(my_send);
      Serial.print(my_send);
      while (hwSerial.available() > 0) {
        ReadString = hwSerial.readStringUntil('\n');
        ReadString.trim();
        Serial.println(ReadString);
        if (ReadString == "ok" && connect == 0) {
          connect = 1;
          print_lcd2("CONECTED");
          drawSdJpeg("/on_button.jpg", 415, 275);
        }
      }
      delay(100);
      digitalWrite(uart_enbale, LOW);
    }


    //********x_movment**********
    if (x_t > 420 && x_t < 480 && y_t > 90 && y_t < 130) {
      digitalWrite(uart_enbale, HIGH);
      digitalWrite(buzzer, HIGH);
      delay(5);
      digitalWrite(buzzer, LOW);
      my_send = "$J=G91X" + String(step_count) + "F" + String(speed_count);
      // my_send = "$J=G91X2.0F500";

      print_lcd(my_send);
      print_lcd2("MOVE X+");
      hwSerial.println(my_send);
      Serial.println(my_send);
      delay(200);
      digitalWrite(uart_enbale, LOW);
    }

    if (x_t > 200 && x_t < 270 && y_t > 90 && y_t < 130) {

      digitalWrite(uart_enbale, HIGH);
      digitalWrite(buzzer, HIGH);
      delay(5);
      digitalWrite(buzzer, LOW);
      my_send = "$J=G91X-" + String(step_count) + "F" + String(speed_count);
      print_lcd(my_send);
      print_lcd2("MOVE X-");
      hwSerial.println(my_send);
      Serial.println(my_send);
      delay(200);
      digitalWrite(uart_enbale, LOW);
    }

    //********y_movment**********
    if (x_t > 320 && x_t < 370 && y_t > 0 && y_t < 50) {
      digitalWrite(uart_enbale, HIGH);
      digitalWrite(buzzer, HIGH);
      delay(5);
      digitalWrite(buzzer, LOW);
      my_send = "$J=G91Y" + String(step_count) + "F" + String(speed_count);
      // my_send = "$J=G91X2.0F500";

      print_lcd(my_send);
      print_lcd2("MOVE Y+");
      hwSerial.println(my_send);
      Serial.println(my_send);
      delay(200);
      digitalWrite(uart_enbale, LOW);
    }

    if (x_t > 320 && x_t < 370 && y_t > 185 && y_t < 235) {

      digitalWrite(uart_enbale, HIGH);
      digitalWrite(buzzer, HIGH);
      delay(5);
      digitalWrite(buzzer, LOW);
      my_send = "$J=G91Y-" + String(step_count) + "F" + String(speed_count);
      print_lcd(my_send);
      print_lcd2("MOVE Y-");
      hwSerial.println(my_send);
      Serial.println(my_send);
      delay(200);
      digitalWrite(uart_enbale, LOW);
    }



    //********step_setting**********
    if (x_t > 120 && x_t < 155 && y_t > 190 && y_t < 230) {
      digitalWrite(buzzer, HIGH);
      delay(5);
      digitalWrite(buzzer, LOW);

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

      tft.fillRoundRect(64, 209, 55, 10, 5, TFT_WHITE);
      tft.setTextColor(TFT_BLACK, TFT_WHITE);
      tft.setCursor(65, 210);
      tft.println(String(step_count));

      delay(100);
    }

    if (x_t > 15 && x_t < 50 && y_t > 190 && y_t < 230) {
      digitalWrite(buzzer, HIGH);
      delay(5);
      digitalWrite(buzzer, LOW);

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
      tft.fillRoundRect(64, 209, 55, 10, 5, TFT_WHITE);
      tft.setTextColor(TFT_BLACK, TFT_WHITE);
      tft.setCursor(65, 210);
      tft.println(String(step_count));
      delay(100);
    }

    //********speed_setting**********
    if (x_t > 120 && x_t < 155 && y_t > 260 && y_t < 300) {
      digitalWrite(buzzer, HIGH);
      delay(5);
      digitalWrite(buzzer, LOW);
      speed_count = speed_count + 500;
      if (speed_count > 40000) speed_count = 40000;
      Serial.println(String(speed_count));
      tft.fillRoundRect(54, 279, 54, 10, 5, TFT_WHITE);
      tft.setTextColor(TFT_BLACK, TFT_WHITE);
      tft.setCursor(55, 280);
      tft.println(String(speed_count));
      delay(100);
    }

    if (x_t > 15 && x_t < 50 && y_t > 260 && y_t < 300) {
      digitalWrite(buzzer, HIGH);
      delay(5);
      digitalWrite(buzzer, LOW);
      speed_count = speed_count - 500;
      if (speed_count < 500) speed_count = 500;
      Serial.println(String(speed_count));
      tft.fillRoundRect(54, 279, 54, 10, 5, TFT_WHITE);
      tft.setTextColor(TFT_BLACK, TFT_WHITE);
      tft.setCursor(55, 280);
      tft.println(String(speed_count));

      delay(100);
    }


    //******************************LASER TEST************************************
    if (x_t > 200 && x_t < 250 && y_t > 260 && y_t < 300) {
      digitalWrite(uart_enbale, HIGH);
      digitalWrite(buzzer, HIGH);
      delay(50);
      digitalWrite(buzzer, LOW);
      hwSerial.println("M3 S1000");
      delay(50);
      hwSerial.println("G1 F1000");
      delay(150);
      hwSerial.println("M5 S0");
      delay(50);
      hwSerial.println("G0");
      print_lcd("M3 S1000");
      print_lcd2("LASET TEST");
      delay(100);
      digitalWrite(uart_enbale, LOW);
    }

    //******************************FRAME************************************
    if (x_t > 270 && x_t < 320 && y_t > 260 && y_t < 300) {
      digitalWrite(uart_enbale, HIGH);
      digitalWrite(buzzer, HIGH);
      delay(100);
      digitalWrite(buzzer, LOW);
      delay(50);
      digitalWrite(buzzer, HIGH);
      delay(100);
      digitalWrite(buzzer, LOW);
      my_send = "$H";
      Serial.println(my_send);
      hwSerial.println(my_send);
      print_lcd(my_send);
      //print_lcd2("Home Corner");
      delay(100);
      digitalWrite(uart_enbale, LOW);
    }

    //********home**********
    if (x_t > 320 && x_t < 380 && y_t > 80 && y_t < 150) {

      digitalWrite(uart_enbale, HIGH);
      digitalWrite(buzzer, HIGH);
      delay(20);
      digitalWrite(buzzer, LOW);
      my_send = "$J=G90X0Y0F" + String(speed_count);
      //my_send = "$J=G91X2.0F500";

      print_lcd(my_send);
      //print_lcd2("GO HOME");
      hwSerial.println(my_send);
      Serial.println(my_send);
      delay(200);
      digitalWrite(uart_enbale, LOW);
    }

    //**************zero point********************
    if (x_t > 420 && x_t < 470 && y_t > 180 && y_t < 240) {
      digitalWrite(uart_enbale, HIGH);
      digitalWrite(buzzer, HIGH);
      delay(20);
      digitalWrite(buzzer, LOW);
      my_send = "G92 X0 Y0 Z0";
      //my_send = "$J=G91X2.0F500";

      print_lcd(my_send);
      print_lcd2("zero point");
      hwSerial.println(my_send);
      Serial.println(my_send);
      delay(200);
      digitalWrite(uart_enbale, LOW);
    }

    //******file manager******
    if (x_t > 200 && x_t < 250 && y_t > 190 && y_t < 240) {
      digitalWrite(buzzer, HIGH);
      delay(50);
      digitalWrite(buzzer, LOW);
      // g_cod1();
      select_storage();
    }
  }
}


//******************************************************************gcode***************************************************************************************
//******************************************************************gcode***************************************************************************************
//******************************************************************gcode***************************************************************************************


//************************************************read_files*****************************************************
//**************************************************read_files*************************************************************
//******************************************************read_files*****************************************************************

//***************FOR RESUME************
int exit_run = 0;
int line_count2;
int line_found;
String x_pos;
String y_pos;
String z_pos;
String first_gcode;
String data_read4;
String str_data;
String x_;
String y_;
String z_;
String s_;
String g_;
int start_x;
int start_y;
int start_z;
int start_s;
int start_g;
int start_x2;
int start_y2;
int start_z2;
int start_s2;
int start_g2;
String x_p;
String y_p;
String z_p;
String s_p;
String g_p;
float xmin1 = 0;
float xmin2;
float ymin1 = 0;
float ymin2;
String x_frame;
String y_frame;
void read_axis() {

  x_ = "";
  y_ = "";
  z_ = "";
  s_ = "";
  g_ = "";
  x_p = "";
  y_p = "";
  z_p = "";
  s_p = "";
  g_p = "";
  start_x = 0;
  start_y = 0;
  start_z = 0;
  start_s = 0;
  start_g = 0;
  start_x2 = 0;
  start_y2 = 0;
  start_z2 = 0;
  start_s2 = 0;
  start_g2 = 0;



  str_data = data_read4;
  Serial.print("line -10:");
  Serial.println(str_data);
  const char *file3 = str_data.c_str();

  Serial.println("level1");

  for (int i = 0; i <= str_data.length(); i++) {

    if (file3[i] == 'X') {
      start_x2 = 1;
      start_x = 1;
      start_y = 0;
      start_z = 0;
      start_s = 0;
      start_g = 0;
    }

    if (file3[i] == 'Y') {
      start_y2 = 1;
      start_y = 1;
      start_x = 0;
      start_z = 0;
      start_s = 0;
      start_g = 0;
    }

    if (file3[i] == 'Z') {
      start_z2 = 1;
      start_z = 1;
      start_y = 0;
      start_x = 0;
      start_s = 0;
      start_g = 0;
    }

    if (file3[i] == 'S') {
      start_s2 = 1;
      start_s = 1;
      start_y = 0;
      start_z = 0;
      start_x = 0;
      start_g = 0;
    }

    if (file3[i] == 'G') {
      start_g2 = 1;
      start_s = 0;
      start_y = 0;
      start_z = 0;
      start_x = 0;
      start_g = 1;
    }

    if (start_x == 1 && start_y == 0 && start_z == 0 && start_s == 0 && start_g == 0) {
      x_ = x_ + file3[i];
    }

    if (start_y == 1 && start_x == 0 && start_z == 0 && start_s == 0 && start_g == 0) {
      y_ = y_ + file3[i];
    }

    if (start_z == 1 && start_x == 0 && start_y == 0 && start_s == 0 && start_g == 0) {
      z_ = z_ + file3[i];
      Serial.println("*z*");
    }

    if (start_s == 1 && start_x == 0 && start_y == 0 && start_z == 0 && start_g == 0) {
      s_ = s_ + file3[i];
    }

    if (start_g == 1 && start_x == 0 && start_y == 0 && start_z == 0 && start_s == 0) {
      g_ = g_ + file3[i];
    }
  }

  Serial.println("level2");

  if (start_x2 == 1) {
    const char *x_char = x_.c_str();
    x_p = "";
    for (int i = 0; i <= x_.length() - 2; i++) {
      x_p = x_p + x_char[i];
    }
  }

  Serial.println("level2_1");

  if (start_y2 == 1) {
    const char *y_char = y_.c_str();
    y_p = "";
    for (int i = 0; i <= y_.length() - 2; i++) {
      y_p = y_p + y_char[i];
    }
  }

  Serial.println("level2_2");
  Serial.print(z_);
  if (start_z2 == 1) {
    const char *z_char = z_.c_str();
    z_p = "";
    for (int i = 0; i <= z_.length() - 2; i++) {
      z_p = z_p + z_char[i];
    }
  }

  Serial.println("level2_3");

  if (start_s2 == 1) {
    const char *s_char = s_.c_str();
    s_p = "";
    for (int i = 0; i <= s_.length() - 2; i++) {
      s_p = s_p + s_char[i];
    }
  }

  Serial.println("level2_4");

  if (start_g2 == 1) {
    const char *g_char = g_.c_str();
    g_p = "";
    for (int i = 0; i <= g_.length() - 2; i++) {
      g_p = g_p + g_char[i];
    }
  }

  Serial.println("level3");


  if (x_p == "") x_p = "X";
  if (y_p == "") y_p = "Y";
  if (z_p == "") z_p = "Z";
  if (s_p == "") s_p = "S";
  if (g_p == "") g_p = "G0";

  Serial.print("G: ");
  Serial.println(g_p);
  Serial.print("X: ");
  Serial.println(x_p);
  Serial.print("Y: ");
  Serial.println(y_p);
  Serial.print("Z: ");
  Serial.println(z_p);
  Serial.print("S: ");
  Serial.println(s_p);

  //********************for sang_qabr***************
  if (x_p == "X" || y_p == "Y") {
    line_found = line_found + 1;
    Serial.print("line found:");
    Serial.println(String(line_found));

  } else {
    x_pos = x_p;
    y_pos = y_p;
  }
}


void readFile4(fs::FS &fs, const char *path) {
  Serial.printf("Reading file: %s\n", path);

  File file = fs.open(path);
  if (!file) {
    Serial.println("Failed to open file for reading");
    return;
  }

  Serial.print("Read from file: ");
  line_count2 = 0;
  line_found = 0;
  line_found = line_number - 10;
  while (file.available()) {

    data_read4 = file.readStringUntil('\n');
    ++line_count2;
    //Serial.print("Line: ");
    //Serial.println(String(line_count2));

    if (line_count2 == 1) {
      print_lcd4("Zero point");
      hwSerial.println("G92 X0 Y0 Z0");
      delay(100);
      hwSerial.println(data_read4);
      Serial.println(data_read4);
    }

    if (line_count2 == 2) {
      hwSerial.println(data_read4);
      Serial.println(data_read4);
    }

    if (line_count2 == line_found) {
      read_axis();
      Serial.println("Next line");
    }
    //*****************
  }
  ///Serial.println(s1);
  file.close();
}






//****************READ resume file name***************
void readFile3(fs::FS &fs, const char *path) {
  Serial.printf("Reading file: %s\n", path);

  File file = fs.open(path);
  if (!file) {
    Serial.println("Failed to open file for reading");
    return;
  }

  Serial.print("Read from file: ");
  while (file.available()) {

    String data = file.readStringUntil('\n');
    Serial.println(data);
    read_resume_line = data;
    if (data = "\r\n") Serial.println("/end file");
  }
  ///Serial.println(s1);
  file.close();
}


//**************read number of line in file***************
void readFile2(fs::FS &fs, const char *path) {
  Serial.printf("Reading file: %s\n", path);

  File file = fs.open(path);
  if (!file) {
    Serial.println("Failed to open file for reading");
    return;
  }

  Serial.print("Read from file: ");
  xmin1 = 0;
  ymin1 = 0;
  xmin2 = 0;
  ymin2 = 0;
  while (file.available()) {

    str_data = file.readStringUntil('\n');
    // Serial.println(data);
    // if (data = "\r\n") Serial.println("/end file");
    frame();
    ++gcode_line;
  }
  file.close();
  Serial.print("X max: ");
  Serial.println(String(xmin1));
  Serial.print("y max: ");
  Serial.println(String(ymin1));
  x_frame = String(xmin1);
  y_frame = String(ymin1);
}


void control2() {
  input_touch3();

  if (x_t > 230 && x_t < 270 && y_t > 250 && y_t < 300) {
    x_t = 0;
    y_t = 0;

    digitalWrite(pus, LOW);
    delay(100);
    digitalWrite(pus, HIGH);
    print_lcd4("Pause");
    while (1) {
       input_touch3();
      if (x_t > 300 && x_t < 335 && y_t > 250 && y_t < 300) {
        x_t = 0;
        y_t = 0;
        print_lcd4("Play");
        digitalWrite(play, LOW);
        delay(100);
        digitalWrite(play, HIGH);
        ok_count = 30;
        break;
      }
    }
  }
}

void control() {
  input_touch3();

  //********************stop*******************
  if (x_t > 90 && x_t < 140 && y_t > 250 && y_t < 300) {
    x_t = 0;
    y_t = 0;
    print_lcd4("Stop file");
    exit_run = 1;
    ok_count = 30;
    send_gcode = 5;
  }

  //****************Pause***************
  if (x_t > 230 && x_t < 270 && y_t > 250 && y_t < 300) {
    x_t = 0;
    y_t = 0;

    digitalWrite(pus, LOW);
    delay(100);
    digitalWrite(pus, HIGH);
    print_lcd4("Pause");
    while (1) {
      input_touch3();
      //***************lcd_refresh****************
      if (x_t > 430 && x_t < 480 && y_t > 260 && y_t < 320) {
        tft.init();
        x_t = 0;
        y_t = 0;
      }
      //****************play***************
      if (x_t > 300 && x_t < 335 && y_t > 250 && y_t < 300) {
        x_t = 0;
        y_t = 0;
        print_lcd4("Play");
        //ok_count = 3;
        //send_command = 0;
        //first_send = 0;

        // hwSerial.println("$$");
        // delay(200);
        // hwSerial.println("M3 S0");

        digitalWrite(play, LOW);
        delay(100);
        digitalWrite(play, HIGH);
        break;
      }

      //*************STOP************
      if (x_t > 90 && x_t < 140 && y_t > 250 && y_t < 300) {
        x_t = 0;
        y_t = 0;
        print_lcd4("Stop file");
        exit_run = 1;
        break;
      }
      char key = keypad.getKey();

      if (key) {
        Serial.println(key);


        //****************play***************
        if (key == '1') {
          x_t = 0;
          y_t = 0;
          print_lcd4("Play");
          //ok_count = 3;
          //send_command = 0;
          //first_send = 0;

          // hwSerial.println("$$");
          // delay(200);
          // hwSerial.println("M3 S0");

          digitalWrite(play, LOW);
          delay(100);
          digitalWrite(play, HIGH);
          break;
        }
      }
    }
  }
}



String data_save;

void ac_control() {
  if (ac_count == 0) {
    Serial.println("220v out");
    Serial.println("ac disconnected");
    line_number = line_number2;
    resume_mode = 1;
    EEPROM.writeFloat(0, resume_mode);
    delay(50);
    EEPROM.commit();
    EEPROM.writeFloat(20, line_number);
    delay(50);
    EEPROM.commit();
    const char *file3 = data_save.c_str();
    writeFile(SD, "/resume.txt", file3);
    delay(500);
    digitalWrite(uart_enbale, HIGH);
    digitalWrite(buzzer, HIGH);
    delay(50);
    digitalWrite(buzzer, LOW);
    hwSerial.println("M3 S1000");
    delay(50);
    hwSerial.println("G1 F1000");
    delay(150);
    hwSerial.println("M5 S0");
    delay(50);
    hwSerial.println("G0");
    //print_lcd("M3 S1000");
    //print_lcd2("LASET TEST");
    delay(100);

    while (1) {
      input_touch3();

      //***************lcd_refresh****************
      if (x_t > 430 && x_t < 480 && y_t > 260 && y_t < 320) {
        tft.init();
        x_t = 0;
        y_t = 0;
      }
      //*****************stop***************
      if (x_t > 90 && x_t < 140 && y_t > 250 && y_t < 300) {
        x_t = 0;
        y_t = 0;
        print_lcd4("Stop file");
        digitalWrite(buzzer, HIGH);
        delay(50);
        digitalWrite(buzzer, LOW);
        exit_run = 1;
        break;
      }
    }
  }
}
//*****************************************************main_read_line&&run*********************************************
//*****************************************************main_read_line&&run*********************************************
//*****************************************************main_read_line&&run*********************************************
//*****************************************************main_read_line&&run*********************************************
//*****************************************************main_read_line&&run*********************************************
void readFile(fs::FS &fs, const char *path) {
  Serial.printf("Reading file: %s\n", path);

  File file = fs.open(path);
  if (!file) {
    Serial.println("Failed to open file for reading");
    print_lcd4("Failed to open file for reading");
    return;
  }

  send_command = 0;
  String data;
  int start_cammand;
  start_cammand = 0;
  ok_count = 0;
  Serial.print("Read from file: ");
  while (file.available()) {


    if (send_ == 1) {
      if (resume_mode == 1) {
        while (1) {
          data = file.readStringUntil('\n');
          ++line_number2;
          if (line_number2 >= line_found) break;
        }
      }

      if (resume_mode == 0) {
        data = file.readStringUntil('\n');
        ++line_number2;
      }
      hwSerial.println(data);
      data_save = data;
    }

    if (first_send == 0) ++send_command;

    if (first_send == 1) {
      while (1) {

        //while (hwSerial.available() == 0) {}
        ReadString = hwSerial.readStringUntil('\n');
        ReadString.trim();
        Serial.println(ReadString);
        if (ReadString == "ok") {
          ++ok_count;
          ReadString = "";
        }
        if (ok_count >= 3) {
          ok_count = 0;
          send_ = 1;
          Serial.println(data);
          //print_lcd3(data);
          control();
          ac_input();
          ac_control();
          print_line(String(line_number2));
          //*********************Loading*********************
          int loading = map(line_number2, 0, gcode_line, 7, 195);
          tft.fillRoundRect(6, 151, loading, 13, 5, TFT_GREEN);
          //*********************Loading*********************
          //delay(150);
          ReadString = "";
          break;
        }
        //}
      }
    }



    if (first_send == 0) {
      if (send_command >= 8) {
        first_send = 1;
        send_command = 0;
        while (1) {
          while (hwSerial.available() == 0) {}
          ReadString = hwSerial.readStringUntil('\n');
          ReadString.trim();
          Serial.println(ReadString);
          if (ReadString == "ok") {
            ReadString = "";
            ++start_cammand;
          }
          if (start_cammand >= 16) {
            //delay(5000);
            break;
          }
        }
      }
    }

    if (exit_run == 1) {
      hwSerial.println("M5");
      break;
    }
  }

  file.close();
  hwSerial.println("M5");
  print_lcd4("***End file***");
  digitalWrite(buzzer, HIGH);
  delay(500);
  digitalWrite(buzzer, LOW);
  delay(500);
  digitalWrite(buzzer, HIGH);
  delay(1000);
  digitalWrite(buzzer, LOW);
}


//*******resume file**********
void resume_file() {
  digitalWrite(uart_enbale, HIGH);
  line_count2 = 0;
  print_lcd4("Move to Corner");
  hwSerial.println("$H");
  while (1) {
    input_serial2();
    if (ReadString == "ok") break;
  }
  delay(3000);
  print_lcd4("Starting file...");
  const char *file3 = file1.c_str();
  readFile4(SD, file3);
  String move_to_resume = "G0 " + x_pos + " " + y_pos + " " + "S0";  //****for sang qabr*******
  hwSerial.println(move_to_resume);
  // print_lcd3(move_to_resume);
  ready_run();
  digitalWrite(uart_enbale, LOW);
}

//************ready_run***************
void ready_run() {

  tft.fillRoundRect(5, 150, 200, 15, 5, TFT_BLACK);
  tft.fillRoundRect(6, 151, 7, 13, 5, TFT_GREEN);
  exit_run = 0;
  line_number2 = 0;
  line_number = 0;
  first_send = 0;
  send_command = 0;
  send_ = 1;
  ok_count = 0;
  digitalWrite(uart_enbale, HIGH);
  digitalWrite(buzzer, HIGH);
  delay(200);
  digitalWrite(buzzer, LOW);
  hwSerial.println("M3 S0");
  delay(200);
  print_lcd4("Start file ...");
  file1 = "/files/" + file_name;
  const char *file2 = file1.c_str();
  delay(2000);
  digitalWrite(buzzer, HIGH);
  delay(200);
  digitalWrite(buzzer, LOW);
  delay(200);
  digitalWrite(buzzer, HIGH);
  delay(1000);
  digitalWrite(buzzer, LOW);
  readFile(SD, file2);
  delay(200);
}

//*******************gcod_menu********************
void run_gcod() {
  tft.fillScreen(TFT_WHITE);
  drawSdJpeg("/run.jpg", 0, 0);
  tft.setTextFont(2);
  tft.setTextSize(1);
  tft.setCursor(5, 130);
  String ss = "File name: " + file_name;
  tft.println(ss);
  x_t = 0;
  y_t = 0;
  if (connect == 0) drawSdJpeg("/off_button.jpg", 415, 275);
  if (connect == 1) drawSdJpeg("/on_button.jpg", 415, 275);

  tft.setTextFont(2);
  tft.setTextColor(TFT_BLACK, TFT_WHITE);
  tft.setTextSize(1);
  tft.setCursor(5, 170);
  String ss3 = "Loadin file ...";
  tft.print(ss3);

  readFile3(SD, "/resume.txt");
  Serial.print("read resum line: ");
  Serial.println(read_resume_line);
  print_lcd4(read_resume_line);
  gcode_line = 0;
  file1 = "/files/" + file_name;
  const char *file2 = file1.c_str();
  readFile2(SD, file2);
  print_line(String(line_number));

  tft.fillRoundRect(5, 150, 200, 15, 5, TFT_BLACK);
  tft.fillRoundRect(6, 151, 7, 13, 5, TFT_GREEN);
  //for(int i = 7 ; i <= 195 ; i++){
  // tft.fillRoundRect(6, 151, i, 13, 5, TFT_GREEN);
  // delay(100);
  // }
  tft.setCursor(5, 230);
  tft.setTextColor(TFT_RED, TFT_WHITE);
  String text2 = x_frame + "mm * " + y_frame + "mm";
  tft.print(text2);
  main_run = 1;
  while (1) {
    input_serial2();
    input_touch3();
    ac_input();
    usb_check();
    keypad_2();
    //********************run gcod*****************
    if (x_t > 30 && x_t < 200 && y_t > 10 && y_t < 100) {
      hwSerial.println("$X");
      line_number = 0;
      resume_mode = 0;
      EEPROM.writeFloat(0, resume_mode);
      EEPROM.commit();
      delay(50);
      EEPROM.writeFloat(20, line_number);
      delay(50);
      EEPROM.commit();
      print_line(String(line_number));
      Serial.print("resume_mode: ");
      Serial.print(String(resume_mode));
      Serial.print("line number ");
      Serial.print(String(line_number));

      x_t = 0;
      y_t = 0;
      ready_run();
      delay(200);
      digitalWrite(uart_enbale, LOW);
    }

    //****************stop***************
    if (x_t > 90 && x_t < 140 && y_t > 250 && y_t < 300) {
      x_t = 0;
      y_t = 0;
      print_lcd4("Stop file");
      digitalWrite(buzzer, HIGH);
      delay(50);
      digitalWrite(buzzer, LOW);
    }


    //****************resume***************
    if (x_t > 160 && x_t < 200 && y_t > 250 && y_t < 300) {
      x_t = 0;
      y_t = 0;
      print_lcd4("Resume");
      digitalWrite(buzzer, HIGH);
      delay(50);
      digitalWrite(buzzer, LOW);

      // if (resume_mode == 1) {
      //   digitalWrite(buzzer, HIGH);
      //   delay(50);
      //   digitalWrite(buzzer, LOW);
      //   resume_file();
      // }
    }


    //****************Resume From corner***************
    if (x_t > 260 && x_t < 300 && y_t > 185 && y_t < 220) {
      hwSerial.println("$X");
      x_t = 0;
      y_t = 0;
      print_lcd4("Resume From corner");
      digitalWrite(buzzer, HIGH);
      delay(50);
      digitalWrite(buzzer, LOW);

      if (resume_mode == 1) {
        digitalWrite(buzzer, HIGH);
        delay(50);
        digitalWrite(buzzer, LOW);
        resume_file();
      }
    }

    //****************Home Corner***************
    if (x_t > 260 && x_t < 300 && y_t > 1 && y_t < 55) {
      digitalWrite(uart_enbale, HIGH);
      x_t = 0;
      y_t = 0;
      //print_lcd4("Home corner");
      digitalWrite(buzzer, HIGH);
      delay(50);
      digitalWrite(buzzer, LOW);
      //print_lcd3("$H");
      hwSerial.println("$H");
      delay(3000);
      digitalWrite(uart_enbale, LOW);
    }


    //****************Pause***************
    if (x_t > 230 && x_t < 270 && y_t > 250 && y_t < 300) {
      x_t = 0;
      y_t = 0;
      print_lcd4("Pause");
      digitalWrite(buzzer, HIGH);
      delay(50);
      digitalWrite(buzzer, LOW);
    }

    //****************play***************
    if (x_t > 300 && x_t < 335 && y_t > 250 && y_t < 300) {
      x_t = 0;
      y_t = 0;
      print_lcd4("Play");
      digitalWrite(buzzer, HIGH);
      delay(50);
      digitalWrite(buzzer, LOW);
    }

    //****************Frame***************
    if (x_t > 360 && x_t < 400 && y_t > 250 && y_t < 300) {
      digitalWrite(uart_enbale, HIGH);
      x_t = 0;
      y_t = 0;
      print_lcd4("Frame");
      digitalWrite(buzzer, HIGH);
      delay(50);
      digitalWrite(buzzer, LOW);

      String frame1 = "G0 Y" + y_frame + " " + "F" + String(speed_count);
      hwSerial.println(frame1);
      Serial.println(frame1);
      delay(500);
      frame1 = "G0 X" + x_frame + " " + "F" + String(speed_count);
      hwSerial.println(frame1);
      Serial.println(frame1);
      delay(500);
      frame1 = "G0 Y0 F" + String(speed_count);
      hwSerial.println(frame1);
      Serial.println(frame1);
      delay(500);
      frame1 = "G0 X0 F" + String(speed_count);
      hwSerial.println(frame1);
      Serial.println(frame1);
      delay(500);
      digitalWrite(uart_enbale, LOW);
    }

    //****************zero point***************
    if (x_t > 425 && x_t < 470 && y_t > 190 && y_t < 230) {
      x_t = 0;
      y_t = 0;
      digitalWrite(uart_enbale, HIGH);
      digitalWrite(buzzer, HIGH);
      delay(20);
      digitalWrite(buzzer, LOW);
      my_send = "G92 X0 Y0 Z0";
      //my_send = "$J=G91X2.0F500";

      // print_lcd3(my_send);
      print_lcd4("zero point");
      hwSerial.println(my_send);
      Serial.println(my_send);
      delay(200);
      digitalWrite(uart_enbale, LOW);
    }

    //**************on_off*****************
    if (x_t > 430 && x_t < 480 && y_t > 260 && y_t < 320) {
      x_t = 0;
      y_t = 0;
      //if (state == 0) {
      digitalWrite(uart_enbale, HIGH);
      digitalWrite(buzzer, HIGH);
      delay(100);
      digitalWrite(buzzer, LOW);
      tft.init();
      state = 1;
      my_send = "$X";
      //connect = 1;
      // print_lcd3(my_send);
      print_lcd4("CONECTING...");
      hwSerial.println(my_send);
      my_send = "$$";
      hwSerial.println(my_send);
      delay(200);
      digitalWrite(uart_enbale, LOW);
    }

    //********x_movment**********
    if (x_t > 430 && x_t < 480 && y_t > 70 && y_t < 120) {
      x_t = 0;
      y_t = 0;
      digitalWrite(uart_enbale, HIGH);
      digitalWrite(buzzer, HIGH);
      delay(5);
      digitalWrite(buzzer, LOW);
      my_send = "$J=G91X" + String(step_count) + "F" + String(speed_count);
      // my_send = "$J=G91X2.0F500";

      //print_lcd3(my_send);
      print_lcd4("MOVE X+");
      hwSerial.println(my_send);
      Serial.println(my_send);
      delay(200);
      digitalWrite(uart_enbale, LOW);
    }

    if (x_t > 250 && x_t < 310 && y_t > 70 && y_t < 120) {
      x_t = 0;
      y_t = 0;
      digitalWrite(uart_enbale, HIGH);
      digitalWrite(buzzer, HIGH);
      delay(5);
      digitalWrite(buzzer, LOW);
      my_send = "$J=G91X-" + String(step_count) + "F" + String(speed_count);
      //print_lcd3(my_send);
      print_lcd4("MOVE X-");
      hwSerial.println(my_send);
      Serial.println(my_send);
      delay(200);
      digitalWrite(uart_enbale, LOW);
    }

    //********y_movment**********
    if (x_t > 350 && x_t < 400 && y_t > 0 && y_t < 50) {
      x_t = 0;
      y_t = 0;
      digitalWrite(uart_enbale, HIGH);
      digitalWrite(buzzer, HIGH);
      delay(5);
      digitalWrite(buzzer, LOW);
      my_send = "$J=G91Y" + String(step_count) + "F" + String(speed_count);
      // my_send = "$J=G91X2.0F500";

      // print_lcd3(my_send);
      print_lcd4("MOVE Y+");
      hwSerial.println(my_send);
      Serial.println(my_send);
      delay(200);
      digitalWrite(uart_enbale, LOW);
    }

    if (x_t > 350 && x_t < 400 && y_t > 150 && y_t < 190) {
      x_t = 0;
      y_t = 0;
      digitalWrite(uart_enbale, HIGH);
      digitalWrite(buzzer, HIGH);
      delay(5);
      digitalWrite(buzzer, LOW);
      my_send = "$J=G91Y-" + String(step_count) + "F" + String(speed_count);
      //print_lcd3(my_send);
      print_lcd4("MOVE Y-");
      hwSerial.println(my_send);
      Serial.println(my_send);
      delay(200);
      digitalWrite(uart_enbale, LOW);
    }

    //********home**********
    if (x_t > 350 && x_t < 400 && y_t > 70 && y_t < 120) {
      x_t = 0;
      y_t = 0;
      digitalWrite(uart_enbale, HIGH);
      digitalWrite(buzzer, HIGH);
      delay(20);
      digitalWrite(buzzer, LOW);
      my_send = "$J=G90X0Y0F" + String(speed_count);
      //my_send = "$J=G91X2.0F500";

      //print_lcd3(my_send);
      // print_lcd4("GO HOME");
      hwSerial.println(my_send);
      Serial.println(my_send);
      delay(200);
      digitalWrite(uart_enbale, LOW);
    }

    //*************exit**************
    if (x_t > 1 && x_t < 60 && y_t > 250 && y_t < 300) {
      x_t = 0;
      y_t = 0;
      digitalWrite(buzzer, HIGH);
      delay(50);
      digitalWrite(buzzer, LOW);
      gcod_start();
      break;
    }
  }
}

void input_serial2() {
  while (hwSerial.available() > 0) {
    ReadString = hwSerial.readStringUntil('\n');
    ReadString.trim();
    ///Serial.println(ReadString);
    //print_lcd3(ReadString);
    if (ReadString == "ok" && connect == 0) {
      connect = 1;
      print_lcd4("CONECTED");
      drawSdJpeg("/on_button.jpg", 415, 275);
    }
  }
}

void print_lcd3(String text1) {
  tft.fillRoundRect(4, 189, 250, 15, 5, TFT_WHITE);
  tft.setTextFont(2);
  tft.setTextSize(1);
  tft.setTextColor(TFT_BLACK, TFT_WHITE);
  tft.setCursor(5, 190);
  tft.println(text1);
}

void print_lcd4(String text2) {
  tft.fillRoundRect(4, 209, 250, 15, 5, TFT_WHITE);
  tft.setTextFont(2);
  tft.setTextColor(TFT_BLACK, TFT_WHITE);
  tft.setTextSize(1);
  tft.setCursor(5, 210);
  tft.print(text2);
}

void print_line(String text3) {
  tft.fillRoundRect(4, 169, 250, 15, 5, TFT_WHITE);
  tft.setTextFont(2);
  tft.setTextColor(TFT_BLACK, TFT_WHITE);
  tft.setTextSize(1);
  tft.setCursor(5, 170);
  String ss = "Line Number: " + text3 + " ==> From: " + String(gcode_line);
  tft.print(ss);
}


void ac_input() {
  if (digitalRead(ac) == HIGH && ac_count == 0) {
    ac_count = 1;
    tft.fillRoundRect(4, 109, 150, 15, 5, TFT_WHITE);
    tft.setTextFont(2);
    tft.setTextSize(1);
    tft.setTextColor(TFT_BLACK, TFT_WHITE);
    tft.setCursor(5, 110);
    tft.println("220V CONNECT");
  }

  if (digitalRead(ac) == LOW && ac_count == 1) {
    ac_count = 0;
    tft.fillRoundRect(4, 109, 150, 15, 5, TFT_WHITE);
    tft.setTextFont(2);
    tft.setTextSize(1);
    tft.setTextColor(TFT_BLACK, TFT_WHITE);
    tft.setCursor(5, 110);
    tft.println("220V DISCONNECT");
  }
}

//************************input_touch**********************
//************************input_touch**********************
//************************input_touch**********************
void input_touch3() {

  if (tft.getTouch(&x_t, &y_t)) {
    //touch_change = 1;
    // tft.fillRoundRect(378, 3, 100, 15, 5, TFT_WHITE);
    // tft.setCursor(380, 5);
    // String s1 = "x:" + String(x_t) + "  y:" + String(y_t);
    // tft.setTextFont(2);
    // tft.setTextSize(1);
    // tft.setTextColor(TFT_BLACK, TFT_WHITE);
    // tft.println(s1);
  }
}



//************load_pages************
//************load_pages************
void load_page() {
  tft.fillScreen(TFT_WHITE);
  if (page == 0 && usb == 0) drawSdJpeg("/gcod-files1.jpg", 0, 0);
  if (page >= 1 && usb == 0) drawSdJpeg("/gcod-files.jpg", 0, 0);
  if (page == 0 && usb == 1) drawSdJpeg("/gcod-files3.jpg", 0, 0);
  if (page >= 1 && usb == 1) drawSdJpeg("/gcod-files2.jpg", 0, 0);
  tft.setTextFont(2);
  tft.setTextSize(2);
  tft.setCursor(170, 285);
  String ss = "Page(" + String(page_number1) + ")  ";
  tft.println(ss);

  if (page == 0) {
    ii = 0;
    jj = 4;
  }

  if (page == 1) {
    ii = 5;
    jj = 9;
  }

  if (page == 2) {
    ii = 10;
    jj = 14;
  }

  if (page == 3) {
    ii = 15;
    jj = 19;
  }

  if (page == 4) {
    ii = 20;
    jj = 24;
  }

  if (page == 5) {
    ii = 25;
    jj = 29;
  }

  if (page == 6) {
    ii = 30;
    jj = 34;
  }

  if (page == 7) {
    ii = 35;
    jj = 39;
  }

  if (page == 8) {
    ii = 40;
    jj = 44;
  }

  if (page == 9) {
    ii = 45;
    jj = 49;
  }

  if (page == 10) {
    ii = 50;
    jj = 54;
  }
  count_l = 0;
  for (int x = ii; x <= jj; x++) {
    Serial.println(String(count_l));
    if (count_l == 0) {
      tft.setCursor(140, 37);
      tft.println(files[x]);
      Serial.println(files[x]);
      select_file[0] = files[x];
    }

    if (count_l == 1) {
      tft.setCursor(140, 84);
      tft.println(files[x]);
      Serial.println(files[x]);
      select_file[1] = files[x];
    }

    if (count_l == 2) {
      tft.setCursor(140, 132);
      tft.println(files[x]);
      Serial.println(files[x]);
      select_file[2] = files[x];
    }

    if (count_l == 3) {
      tft.setCursor(140, 180);
      tft.println(files[x]);
      Serial.println(files[x]);
      select_file[3] = files[x];
    }

    if (count_l == 4) {
      tft.setCursor(140, 229);
      tft.println(files[x]);
      Serial.println(files[x]);
      select_file[4] = files[x];
    }
    ++count_l;
  }
}





void frame() {
  x_ = "";
  y_ = "";
  x_p = "";
  y_p = "";
  start_x = 0;
  start_y = 0;
  start_x2 = 0;
  start_y2 = 0;

  //Serial.println(str_data);
  const char *file3 = str_data.c_str();

  for (int i = 0; i <= str_data.length(); i++) {

    if (file3[i] == 'X') {
      start_x2 = 1;
      start_x = 1;
      start_y = 0;
    }

    if (file3[i] == 'Y') {
      start_y2 = 1;
      start_y = 1;
      start_x = 0;
    }

    if (file3[i] == 'S' || file3[i] == 'Z') {
      start_y = 0;
      start_x = 0;
    }

    if (start_x == 1 && start_y == 0) {
      x_ = x_ + file3[i];
    }

    if (start_y == 1 && start_x == 0) {
      y_ = y_ + file3[i];
    }
  }

  if (start_x2 == 1) {
    const char *x_char = x_.c_str();
    x_p = "";
    for (int i = 0; i <= x_.length() - 2; i++) {
      if (i > 0) x_p = x_p + x_char[i];
    }
  }

  if (start_y2 == 1) {
    const char *y_char = y_.c_str();
    y_p = "";
    for (int i = 0; i <= y_.length() - 2; i++) {
      if (i > 0) y_p = y_p + y_char[i];
    }
  }

  if (y_p != "") {
    xmin2 = x_p.toFloat();
    if (xmin2 > xmin1) {
      xmin1 = x_p.toFloat();
      // Serial.print("X max: ");
      // Serial.println(String(xmin1));
    }
  }

  if (y_p != "") {
    ymin2 = y_p.toFloat();
    if (ymin2 > ymin1) {
      ymin1 = y_p.toFloat();
      //Serial.print("y max: ");
      //Serial.println(String(ymin1));
    }
  }


  // Serial.print("X: ");
  // Serial.println(x_p);
  // Serial.print("Y: ");
  // Serial.println(y_p);
}
















//*********************touch_calibrate*****************
//*********************touch_calibrate*****************
//*********************touch_calibrate*****************
//*********************touch_calibrate*****************

void touch_calibrate() {
  uint16_t calData[5];
  uint8_t calDataOK = 0;

  // check file system exists
  if (!SPIFFS.begin()) {
    Serial.println("Formatting file system");
    SPIFFS.format();
    SPIFFS.begin();
  }

  // check if calibration file exists and size is correct
  if (SPIFFS.exists(CALIBRATION_FILE)) {
    if (REPEAT_CAL) {
      // Delete if we want to re-calibrate
      SPIFFS.remove(CALIBRATION_FILE);
    } else {
      File f = SPIFFS.open(CALIBRATION_FILE, "r");
      if (f) {
        if (f.readBytes((char *)calData, 14) == 14)
          calDataOK = 1;
        f.close();
      }
    }
  }

  if (calDataOK && !REPEAT_CAL) {
    // calibration data valid
    tft.setTouch(calData);
  } else {
    // data not valid so recalibrate
    tft.fillScreen(TFT_BLACK);
    tft.setCursor(20, 0);
    tft.setTextFont(2);
    tft.setTextSize(1);
    tft.setTextColor(TFT_WHITE, TFT_BLACK);

    tft.println("Touch corners as indicated");

    tft.setTextFont(1);
    tft.println();

    if (REPEAT_CAL) {
      tft.setTextColor(TFT_RED, TFT_BLACK);
      tft.println("Set REPEAT_CAL to false to stop this running again!");
    }

    tft.calibrateTouch(calData, TFT_MAGENTA, TFT_BLACK, 15);

    tft.setTextColor(TFT_GREEN, TFT_BLACK);
    tft.println("Calibration complete!");

    // store data
    File f = SPIFFS.open(CALIBRATION_FILE, "w");
    if (f) {
      f.write((const unsigned char *)calData, 14);
      f.close();
    }
  }
}

//####################################################################################################
// Draw a JPEG on the TFT pulled from a program memory array
//####################################################################################################
void drawArrayJpeg(const uint8_t arrayname[], uint32_t array_size, int xpos, int ypos) {

  int x = xpos;
  int y = ypos;

  JpegDec.decodeArray(arrayname, array_size);

  jpegInfo2();  // Print information from the JPEG file (could comment this line out)

  renderJPEG(x, y);

  //Serial.println("#########################");
}

//####################################################################################################
// Draw a JPEG on the TFT, images will be cropped on the right/bottom sides if they do not fit
//####################################################################################################
// This function assumes xpos,ypos is a valid screen coordinate. For convenience images that do not
// fit totally on the screen are cropped to the nearest MCU size and may leave right/bottom borders.
void renderJPEG(int xpos, int ypos) {

  // retrieve infomration about the image
  uint16_t *pImg;
  uint16_t mcu_w = JpegDec.MCUWidth;
  uint16_t mcu_h = JpegDec.MCUHeight;
  uint32_t max_x = JpegDec.width;
  uint32_t max_y = JpegDec.height;

  // Jpeg images are draw as a set of image block (tiles) called Minimum Coding Units (MCUs)
  // Typically these MCUs are 16x16 pixel blocks
  // Determine the width and height of the right and bottom edge image blocks
  uint32_t min_w = minimum(mcu_w, max_x % mcu_w);
  uint32_t min_h = minimum(mcu_h, max_y % mcu_h);

  // save the current image block size
  uint32_t win_w = mcu_w;
  uint32_t win_h = mcu_h;

  // record the current time so we can measure how long it takes to draw an image
  uint32_t drawTime = millis();

  // save the coordinate of the right and bottom edges to assist image cropping
  // to the screen size
  max_x += xpos;
  max_y += ypos;

  // read each MCU block until there are no more
  while (JpegDec.read()) {

    // save a pointer to the image block
    pImg = JpegDec.pImage;

    // calculate where the image block should be drawn on the screen
    int mcu_x = JpegDec.MCUx * mcu_w + xpos;  // Calculate coordinates of top left corner of current MCU
    int mcu_y = JpegDec.MCUy * mcu_h + ypos;

    // check if the image block size needs to be changed for the right edge
    if (mcu_x + mcu_w <= max_x) win_w = mcu_w;
    else win_w = min_w;

    // check if the image block size needs to be changed for the bottom edge
    if (mcu_y + mcu_h <= max_y) win_h = mcu_h;
    else win_h = min_h;

    // copy pixels into a contiguous block
    if (win_w != mcu_w) {
      uint16_t *cImg;
      int p = 0;
      cImg = pImg + win_w;
      for (int h = 1; h < win_h; h++) {
        p += mcu_w;
        for (int w = 0; w < win_w; w++) {
          *cImg = *(pImg + w + p);
          cImg++;
        }
      }
    }

    // calculate how many pixels must be drawn
    uint32_t mcu_pixels = win_w * win_h;

    tft.startWrite();

    // draw image MCU block only if it will fit on the screen
    if ((mcu_x + win_w) <= tft.width() && (mcu_y + win_h) <= tft.height()) {

      // Now set a MCU bounding window on the TFT to push pixels into (x, y, x + width - 1, y + height - 1)
      tft.setAddrWindow(mcu_x, mcu_y, win_w, win_h);

      // Write all MCU pixels to the TFT window
      while (mcu_pixels--) {
        // Push each pixel to the TFT MCU area
        tft.pushColor(*pImg++);
      }

    } else if ((mcu_y + win_h) >= tft.height()) JpegDec.abort();  // Image has run off bottom of screen so abort decoding

    tft.endWrite();
  }

  // calculate how long it took to draw the image
  drawTime = millis() - drawTime;

  // print the results to the serial port
  // Serial.print(F("Total render time was    : "));
  // Serial.print(drawTime);
  // Serial.println(F(" ms"));
  // Serial.println(F(""));
}

//####################################################################################################
// Draw a JPEG on the TFT pulled from SD Card
//####################################################################################################
// xpos, ypos is top left corner of plotted image
void drawSdJpeg(const char *filename, int xpos, int ypos) {

  // Open the named file (the Jpeg decoder library will close it)
  File jpegFile = SD.open(filename, FILE_READ);  // or, file handle reference for SD library

  if (!jpegFile) {
    Serial.print("ERROR: File \"");
    Serial.print(filename);
    Serial.println("\" not found!");
    return;
  }

  // Serial.println("===========================");
  // Serial.print("Drawing file: ");
  // Serial.println(filename);
  // Serial.println("===========================");

  // Use one of the following methods to initialise the decoder:
  bool decoded = JpegDec.decodeSdFile(jpegFile);  // Pass the SD file handle to the decoder,
  //bool decoded = JpegDec.decodeSdFile(filename);  // or pass the filename (String or character array)

  if (decoded) {
    // print information about the image to the serial port
    jpegInfo();
    // render the image onto the screen at given coordinates
    jpegRender(xpos, ypos);
  } else {
    Serial.println("Jpeg file format not supported!");
  }
}

//####################################################################################################
// Draw a JPEG on the TFT, images will be cropped on the right/bottom sides if they do not fit
//####################################################################################################
// This function assumes xpos,ypos is a valid screen coordinate. For convenience images that do not
// fit totally on the screen are cropped to the nearest MCU size and may leave right/bottom borders.
void jpegRender(int xpos, int ypos) {

  //jpegInfo(); // Print information from the JPEG file (could comment this line out)

  uint16_t *pImg;
  uint16_t mcu_w = JpegDec.MCUWidth;
  uint16_t mcu_h = JpegDec.MCUHeight;
  uint32_t max_x = JpegDec.width;
  uint32_t max_y = JpegDec.height;

  bool swapBytes = tft.getSwapBytes();
  tft.setSwapBytes(true);

  // Jpeg images are draw as a set of image block (tiles) called Minimum Coding Units (MCUs)
  // Typically these MCUs are 16x16 pixel blocks
  // Determine the width and height of the right and bottom edge image blocks
  uint32_t min_w = jpg_min(mcu_w, max_x % mcu_w);
  uint32_t min_h = jpg_min(mcu_h, max_y % mcu_h);

  // save the current image block size
  uint32_t win_w = mcu_w;
  uint32_t win_h = mcu_h;

  // record the current time so we can measure how long it takes to draw an image
  uint32_t drawTime = millis();

  // save the coordinate of the right and bottom edges to assist image cropping
  // to the screen size
  max_x += xpos;
  max_y += ypos;

  // Fetch data from the file, decode and display
  while (JpegDec.read()) {  // While there is more data in the file
    pImg = JpegDec.pImage;  // Decode a MCU (Minimum Coding Unit, typically a 8x8 or 16x16 pixel block)

    // Calculate coordinates of top left corner of current MCU
    int mcu_x = JpegDec.MCUx * mcu_w + xpos;
    int mcu_y = JpegDec.MCUy * mcu_h + ypos;

    // check if the image block size needs to be changed for the right edge
    if (mcu_x + mcu_w <= max_x) win_w = mcu_w;
    else win_w = min_w;

    // check if the image block size needs to be changed for the bottom edge
    if (mcu_y + mcu_h <= max_y) win_h = mcu_h;
    else win_h = min_h;

    // copy pixels into a contiguous block
    if (win_w != mcu_w) {
      uint16_t *cImg;
      int p = 0;
      cImg = pImg + win_w;
      for (int h = 1; h < win_h; h++) {
        p += mcu_w;
        for (int w = 0; w < win_w; w++) {
          *cImg = *(pImg + w + p);
          cImg++;
        }
      }
    }

    // calculate how many pixels must be drawn
    uint32_t mcu_pixels = win_w * win_h;

    // draw image MCU block only if it will fit on the screen
    if ((mcu_x + win_w) <= tft.width() && (mcu_y + win_h) <= tft.height())
      tft.pushImage(mcu_x, mcu_y, win_w, win_h, pImg);
    else if ((mcu_y + win_h) >= tft.height())
      JpegDec.abort();  // Image has run off bottom of screen so abort decoding
  }

  tft.setSwapBytes(swapBytes);

  showTime(millis() - drawTime);  // These lines are for sketch testing only
}

//####################################################################################################
// Print image information to the serial port (optional)
//####################################################################################################
// JpegDec.decodeFile(...) or JpegDec.decodeArray(...) must be called before this info is available!
void jpegInfo() {

  // Print information extracted from the JPEG file
  // Serial.println("JPEG image info");
  // Serial.println("===============");
  // Serial.print("Width      :");
  // Serial.println(JpegDec.width);
  // Serial.print("Height     :");
  // Serial.println(JpegDec.height);
  // Serial.print("Components :");
  // Serial.println(JpegDec.comps);
  // Serial.print("MCU / row  :");
  // Serial.println(JpegDec.MCUSPerRow);
  // Serial.print("MCU / col  :");
  // Serial.println(JpegDec.MCUSPerCol);
  // Serial.print("Scan type  :");
  // Serial.println(JpegDec.scanType);
  // Serial.print("MCU width  :");
  // Serial.println(JpegDec.MCUWidth);
  // Serial.print("MCU height :");
  // Serial.println(JpegDec.MCUHeight);
  // Serial.println("===============");
  // Serial.println("");
}

//####################################################################################################
// Print image information to the serial port (optional)
//####################################################################################################
void jpegInfo2() {
  // Serial.println(F("==============="));
  // Serial.println(F("JPEG image info"));
  // Serial.println(F("==============="));
  // Serial.print(F("Width      :"));
  // Serial.println(JpegDec.width);
  // Serial.print(F("Height     :"));
  // Serial.println(JpegDec.height);
  // Serial.print(F("Components :"));
  // Serial.println(JpegDec.comps);
  // Serial.print(F("MCU / row  :"));
  // Serial.println(JpegDec.MCUSPerRow);
  // Serial.print(F("MCU / col  :"));
  // Serial.println(JpegDec.MCUSPerCol);
  // Serial.print(F("Scan type  :"));
  // Serial.println(JpegDec.scanType);
  // Serial.print(F("MCU width  :"));
  // Serial.println(JpegDec.MCUWidth);
  // Serial.print(F("MCU height :"));
  // Serial.println(JpegDec.MCUHeight);
  // Serial.println(F("==============="));
}
//####################################################################################################
// Show the execution time (optional)
//####################################################################################################
// WARNING: for UNO/AVR legacy reasons printing text to the screen with the Mega might not work for
// sketch sizes greater than ~70KBytes because 16 bit address pointers are used in some libraries.

// The Due will work fine with the HX8357_Due library.
void showTime(uint32_t msTime) {

  // Serial.print(F(" JPEG drawn in "));
  // Serial.print(msTime);
  // Serial.println(F(" ms "));
}

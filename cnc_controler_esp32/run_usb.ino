

//*******************gcod_menu********************
void run_gcod2() {
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

  read_resum();

  Serial.print("read resum line: ");
  Serial.println(read_resume_line);
  print_lcd4(read_resume_line);
  gcode_line = 0;
  file1 = file_name;
  readFile2_usb(file1);
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
  while (1) {
    input_serial2();
    input_touch3();
    ac_input();
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
      ready_run2();
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
        resume_file2();
      }
    }

    //****************Home Corner***************
    if (x_t > 260 && x_t < 300 && y_t > 1 && y_t < 55) {
      digitalWrite(uart_enbale, HIGH);
      x_t = 0;
      y_t = 0;
      print_lcd4("Home corner");
      digitalWrite(buzzer, HIGH);
      delay(50);
      digitalWrite(buzzer, LOW);
      print_lcd3("$H");
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

      print_lcd3(my_send);
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
      print_lcd3(my_send);
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

      print_lcd3(my_send);
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
      print_lcd3(my_send);
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

      print_lcd3(my_send);
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
      print_lcd3(my_send);
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

      print_lcd3(my_send);
      print_lcd4("GO HOME");
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
      usb_file_list();
      break;
    }
  }
}
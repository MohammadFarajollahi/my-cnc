


//**************read number of line in file***************
void readFile2_usb(String ss) {
  Serial.print("Reading file:");
  Serial.println(ss);

  flashDrive.setFileName((char *)ss.c_str());  //set the file name
  flashDrive.openFile();                       //open the file


  Serial.print("Read from file: ");
  xmin1 = 0;
  ymin1 = 0;
  xmin2 = 0;
  ymin2 = 0;
  while (!flashDrive.getEOF()) {
    readMore = true;
    while (readMore) {  // our temporary buffer where we read data from flash drive and the size of that buffer
      //readMore = flashDrive.readFile(adatBuffer, sizeof(adatBuffer));
      readMore = flashDrive.readFileUntil('\n', adatBuffer, sizeof(adatBuffer));  //new line character
      //Serial.print(adatBuffer);  //print the contents of the temporary buffer

      str_data = adatBuffer;

      //Serial.println(str_data);
      frame2();
      ++gcode_line;
    }
  }
  flashDrive.closeFile();  //at the end, close the file
  Serial.print("X max: ");
  Serial.println(String(xmin1));
  Serial.print("y max: ");
  Serial.println(String(ymin1));
  x_frame = String(xmin1);
  y_frame = String(ymin1);
  Serial.print("lin number: ");
  Serial.println(String(gcode_line));
}




//************ready_run***************
void ready_run2() {

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
  file1 = file_name;

  delay(2000);
  digitalWrite(buzzer, HIGH);
  delay(200);
  digitalWrite(buzzer, LOW);
  delay(200);
  digitalWrite(buzzer, HIGH);
  delay(1000);
  digitalWrite(buzzer, LOW);
  readFile2(file1);
  delay(200);
}



//*****************************************************main_read_line&&run*********************************************
//*****************************************************main_read_line&&run*********************************************
//*****************************************************main_read_line&&run*********************************************
//*****************************************************main_read_line&&run*********************************************
//*****************************************************main_read_line&&run*********************************************
void readFile2(String ss) {
  Serial.println("Reading file: ");
  Serial.println(ss);

  flashDrive.setFileName((char *)ss.c_str());  //set the file name
  flashDrive.openFile();                       //open the file

  send_command = 0;
  String data;
  int start_cammand;
  start_cammand = 0;
  ok_count = 0;
  Serial.print("Read from file: ");
  while (!flashDrive.getEOF()) {
    readMore = true;
    if (exit_run == 1) {
      hwSerial.println("M5");
      readMore = false;
      break;
    }
    while (readMore) {  // our temporary buffer where we read data from flash drive and the size of that buffer


      if (send_ == 1) {
        if (resume_mode == 1) {
          while (1) {
            readMore = flashDrive.readFileUntil('\n', adatBuffer, sizeof(adatBuffer));  //new line character
            data = adatBuffer;
            ++line_number2;
            if (line_number2 >= line_found) break;
          }
        }

        if (resume_mode == 0) {
          readMore = flashDrive.readFileUntil('\n', adatBuffer, sizeof(adatBuffer));  //new line character
          data = adatBuffer;
          ++line_number2;
        }
        hwSerial.println(data);
        data_save = data;
      }

      if (first_send == 0) ++send_command;

      if (first_send == 1) {
        while (1) {


          ReadString = hwSerial.readStringUntil('\n');
          ReadString.trim();
          Serial.println(ReadString);
          if (ReadString == "ok") {
            ++ok_count;
            ReadString = "";
          }
          if (ok_count >= 4) {
            ok_count = 0;
            send_ = 1;
            Serial.println(data);
            print_lcd3(data);
            control();
            ac_input();
            ac_control();
            print_line(String(line_number2));
            //*********************Loading*********************
            int loading = map(line_number2, 0, gcode_line, 7, 195);
            tft.fillRoundRect(6, 151, loading, 13, 5, TFT_GREEN);
            //*********************Loading*********************
            //delay(500);
            ReadString = "";
            break;
          }
          //}
        }
      }


      //*************************************first send**************************************8
      if (first_send == 0) {
        if (send_command >= 8) {
          first_send = 1;
          send_command = 0;
          Serial.println("8 send");
          while (1) {
            while (hwSerial.available() == 0) {}
            ReadString = hwSerial.readStringUntil('\n');
            ReadString.trim();
            Serial.println(ReadString);
            if (ReadString == "ok") {
              ReadString = "";
              ++start_cammand;
            }
            if (start_cammand >= 24) {
              //delay(5000);
              Serial.println("first ok");
              break;
            }
          }
        }
      }

      if (exit_run == 1) {
        hwSerial.println("M5");
        readMore = false;
        break;
      }
    }

    // if (exit_run == 1) {
    //   while (readMore) {                                                            // our temporary buffer where we read data from flash drive and the size of that buffer
    //     readMore = flashDrive.readFileUntil('\n', adatBuffer, sizeof(adatBuffer));  //new line character
    //   }
    // }

    ////
  }
  flashDrive.closeFile();
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



void frame2() {
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

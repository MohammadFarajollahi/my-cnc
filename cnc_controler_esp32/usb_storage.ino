
///*********55555555*************
///*********55555555*********************
///*********55555555***************************
//*****************************************************main_read_line&&run*********************************************
//*****************************************************main_read_line&&run*********************************************
//*****************************************************main_read_line&&run*********************************************
//*****************************************************main_read_line&&run*********************************************
//*****************************************************main_read_line&&run*********************************************
void readFile2(String ss) {
  Serial.println("readFile2");
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

          control();
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



//*********************444444444444444444***********************
//*********************444444444444444444******************************
//*********************444444444444444444**************************************
//************ready to run***************
void ready_run2() {
  Serial.println("ready_run2");
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



//*******3333333333333**********
//*******3333333333333*********************
//*******3333333333333*********************************
//************************************************************************main_usb_run_menu******************************************************************************************
void run_gcod2() {
  flash_test = 0;
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
    usb_check();
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
      //usb_file_list();
      break;
    }
  }
}

//*************22222222222222*****************
//*************22222222222222***********************
//*************22222222222222*******************************
//*********************************************************************************usb file start*******************************************************************************
//*********************************************************************************usb file start*******************************************************************************
void usb_file_start() {
  tft.fillScreen(TFT_WHITE);
  tft.setTextFont(2);
  tft.setTextSize(3);
  tft.setCursor(10, 10);
  tft.println("LOADING FILES...");

  count_files = 0;
  for (int j = 0; j <= 100; j++) {
    files[j] = "";
  }
  //read files from usb

  usbfilelist("/files");
  tft.setTextColor(TFT_BLACK, TFT_WHITE);
  Serial.println("print my files");
  for (int i = 0; i <= count_files; i++) {
    Serial.println(files[i]);
  }
  page_number1 = 1;
  page = 0;
  exit_main = 0;
  load_page();
  x_t = 0;
  y_t = 0;
}


//***********1111111111111111111******************
//***********1111111111111111111*****************************
//***********1111111111111111111*****************************************
//*******************************************************************************file list for usb storage******************************************************************************//
//*******************************************************************************file list for usb storage******************************************************************************//
void usb_file_list() {
  usb_file_start();
  flash_test = 0;
  usb_in_count = 0;
  load_again = 0;
  while (1) {
    input_touch3();
    usb_check2();

    if (usb_in == 0 && usb_in_count == 0) {
      usb_in_count = 1;
      digitalWrite(buzzer, HIGH);
      delay(200);
      digitalWrite(buzzer, LOW);
      delay(200);
      digitalWrite(buzzer, HIGH);
      delay(200);
      digitalWrite(buzzer, LOW);
    }

    if (usb_in == 1 && usb_in_count == 1) {
      usb_in_count = 0;
      digitalWrite(buzzer, HIGH);
      delay(200);
      digitalWrite(buzzer, LOW);
      load_again = 1;
      break;
    }
    //********back**********
    if (x_t > 1 && x_t < 60 && y_t > 250 && y_t < 300) {
      digitalWrite(buzzer, HIGH);
      delay(50);
      digitalWrite(buzzer, LOW);
      if (page == 0) {  // first page & exit
        exit_main = 1;
      }
      if (page >= 1) {  // not first && go back
        --page_number1;
        --page;
        load_page();
      }
      x_t = 0;
      y_t = 0;
    }

    //********next**********
    if (x_t > 420 && x_t < 480 && y_t > 250 && y_t < 300) {
      x_t = 0;
      y_t = 0;
      digitalWrite(buzzer, HIGH);
      delay(50);
      digitalWrite(buzzer, LOW);
      if (page <= 10) {
        ++page_number1;
        ++page;
        load_page();
      }
    }

    //***************select_file*********
    //****1****
    if (x_t > 80 && x_t < 350 && y_t > 25 && y_t < 60) {
      Serial.println(" touch 1");
      x_t = 0;
      y_t = 0;
      digitalWrite(buzzer, HIGH);
      delay(50);
      digitalWrite(buzzer, LOW);
      file_name = select_file[0];
      run_gcod2();
    }

    //****2****
    if (x_t > 80 && x_t < 350 && y_t > 80 && y_t < 105) {
      Serial.println(" touch 2");
      x_t = 0;
      y_t = 0;
      digitalWrite(buzzer, HIGH);
      delay(50);
      digitalWrite(buzzer, LOW);
      file_name = select_file[1];
      run_gcod2();
    }
    //****3****
    if (x_t > 80 && x_t < 350 && y_t > 125 && y_t < 150) {
      Serial.println(" touch 3");
      x_t = 0;
      y_t = 0;
      digitalWrite(buzzer, HIGH);
      delay(50);
      digitalWrite(buzzer, LOW);
      file_name = select_file[2];
      run_gcod2();
    }
    //****4****
    if (x_t > 80 && x_t < 350 && y_t > 175 && y_t < 206) {
      Serial.println(" touch 4");
      x_t = 0;
      y_t = 0;
      digitalWrite(buzzer, HIGH);
      delay(50);
      digitalWrite(buzzer, LOW);
      file_name = select_file[3];
      run_gcod2();
    }
    //****5****
    if (x_t > 80 && x_t < 350 && y_t > 230 && y_t < 255) {
      Serial.println(" touch 5");
      x_t = 0;
      y_t = 0;
      digitalWrite(buzzer, HIGH);
      delay(50);
      digitalWrite(buzzer, LOW);
      file_name = select_file[4];
      run_gcod2();
    }


    if (exit_main == 1) {
      x_t = 0;
      y_t = 0;
      //start_show();
      break;
      delay(1000);
    }
  }
  if (load_again == 1) usb_file_list();
}

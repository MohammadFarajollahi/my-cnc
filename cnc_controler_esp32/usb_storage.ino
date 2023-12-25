

//*******************************************************************************list for usb storage******************************************************************************//
void usb_file_list() {
  usb_file_start();
  while (1) {
    input_touch3();

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
}


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


//*****************************************************************************usb list files****************************************************************************************
void usbfilelist(String ss) {
                    
  while (flashDrive.listDir()) {                              // reading next file
    if (flashDrive.getFileAttrb() == CH376_ATTR_DIRECTORY) {  //directory
      Serial.print('/');
      Serial.println(flashDrive.getFileName());  // get the actual file name
      files[count_files] = flashDrive.getFileName();
      ++count_files;
    } else {
      Serial.println(flashDrive.getFileName());  // get the actual file name
      files[count_files] = flashDrive.getFileName();
      ++count_files;
    }
  }
}

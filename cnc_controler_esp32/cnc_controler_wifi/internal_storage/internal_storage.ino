
//*******************************************************************************for internal storage******************************************************************************//
void gcod_start() {
  tft.fillScreen(TFT_WHITE);
  tft.setTextFont(2);
  tft.setTextSize(3);
  tft.setCursor(10, 10);
  tft.println("LOADING FILES...");
  listDir(SD, "/files", 0);
  count_files = 0;
  for (int j = 0; j <= 100; j++) {
    files[j] = "";
  }
  listDir(SD, "/files", 0);
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

void g_cod2() {
  gcod_start();
  while (1) {
    input_touch3();
    usb_check2();
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
      run_gcod();
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
      run_gcod();
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
      run_gcod();
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
      run_gcod();
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
      run_gcod();
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


void writeFile(fs::FS &fs, const char *path, const char *message) {
  Serial.printf("Writing file: %s\n", path);

  File file = fs.open(path, FILE_WRITE);
  if (!file) {
    Serial.println("Failed to open file for writing");
    return;
  }
  if (file.print(message)) {
    Serial.println("File written");
  } else {
    Serial.println("Write failed");
  }
  file.close();
}

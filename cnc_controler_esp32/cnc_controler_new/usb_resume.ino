
//***********************22222222222222************************
//***********************22222222222222**********************************
//***********************22222222222222***************************************************
//*************************************************************************get posision***************************************************************************************
void readFile4_usb(String ss) {
  Serial.println("readFile4_usb");
  Serial.print("Reading file: ");
  Serial.print(ss);

  flashDrive.setFileName((char *)ss.c_str());
  flashDrive.openFile();

  Serial.print("Read from file: ");
  line_count2 = 0;
  line_found = 0;
  line_found = line_number - 50;

  while (!flashDrive.getEOF()) {
    readMore = true;
    while (readMore) {
      readMore = flashDrive.readFileUntil('\n', adatBuffer, sizeof(adatBuffer));  //new line character
      data_read4 = adatBuffer;
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
  }
  ///Serial.println(s1);
  flashDrive.closeFile();
}




//***************11111111111111*****************
//***************11111111111111***************************
//***************11111111111111*************************************
//***************************************************************************************ready to resum**********************************************************************
void resume_file2() {
  Serial.println("resume_file2");
  digitalWrite(uart_enbale, HIGH);
  line_count2 = 0;
  print_lcd4("Move to Corner");
  hwSerial.println("$H");
  while (1) {
    input_serial2();
    if (ReadString == "ok") break;
  }
  delay(6000);
  print_lcd4("Starting file...");
  //const char *file3 = file1.c_str();
  readFile4_usb(file1);
  String move_to_resume = "G0 " + x_pos + " " + y_pos + " " + "S0";  //****for sang qabr*******
  hwSerial.println(move_to_resume);
  print_lcd3(move_to_resume);
 
  delay(2000);
  ready_run2();
  digitalWrite(uart_enbale, LOW);
}

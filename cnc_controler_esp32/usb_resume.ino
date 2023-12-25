

void read_resum() {

  flashDrive.setFileName("RESUME.TXT");  //set the file name
  flashDrive.openFile();                 //open the file
  readMore = true;
  //read data from flash drive until we reach EOF
  while (!flashDrive.getEOF()) {
    readMore = true;
    while (readMore) {  // our temporary buffer where we read data from flash drive and the size of that buffer
      readMore = flashDrive.readFileUntil('\n', adatBuffer, sizeof(adatBuffer));  //new line character
      Serial.print(adatBuffer);  //print the contents of the temporary buffer
      read_resume_line = adatBuffer;
      Serial.print(read_resume_line);
    }
  }
  flashDrive.closeFile();  //at the end, close the file
}



void write_resum() {
  String str = "This is my string";
  int str_len = str.length() + 1;
  Serial.println("COMMAND1: Create and write data to file : TEST1.TXT");  // Create a file called TEST1.TXT
  flashDrive.setFileName("TEST1.TXT");                                    //set the file name
  flashDrive.openFile();                                                  //open the file

  flashDrive.writeFile((char*)str.c_str(), str_len);

  flashDrive.closeFile();  //at the end, close the file
  Serial.println("Done!");
}



//*******resume file**********
void resume_file2() {
  digitalWrite(uart_enbale, HIGH);
  line_count2 = 0;
  print_lcd4("Move to Corner");
  hwSerial.println("$H");
  while (1) {
    input_serial2();
    if (ReadString == "ok") break;
  }
  delay(5000);
  print_lcd4("Starting file...");
  const char *file3 = file1.c_str();
  readFile4(SD, file3);
  String move_to_resume = "G0 " + x_pos + " " + y_pos + " " + "S0";  //****for sang qabr*******
  hwSerial.println(move_to_resume);
  print_lcd3(move_to_resume);
  ready_run();
  digitalWrite(uart_enbale, LOW);
}

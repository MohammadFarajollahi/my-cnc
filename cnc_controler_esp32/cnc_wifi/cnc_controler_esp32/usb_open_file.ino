
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






//******************************************************kherto pert*************************************************************

//*************************************************************************read from flash************************************************************************************
void read_resum() {

  flashDrive.setFileName("RESUME.TXT");  //set the file name
  flashDrive.openFile();                 //open the file
  readMore = true;
  //read data from flash drive until we reach EOF
  while (!flashDrive.getEOF()) {
    readMore = true;
    while (readMore) {                                                            // our temporary buffer where we read data from flash drive and the size of that buffer
      readMore = flashDrive.readFileUntil('\n', adatBuffer, sizeof(adatBuffer));  //new line character
      Serial.print(adatBuffer);                                                   //print the contents of the temporary buffer
      read_resume_line = adatBuffer;
      Serial.print(read_resume_line);
    }
  }
  flashDrive.closeFile();  //at the end, close the file
}


//**********************************************************************save to flash drive************************************************************************************
void write_File_resum(String ss) {
  String str = "salam jojo";
  Serial.print("data:");
  Serial.println(str);
  int str_len = str.length() + 1;
  Serial.println("COMMAND1: Create and write data to file: resum files");  // Create a file called TEST1.TXT
  flashDrive.setFileName("RESUME.TXT");                                    //set the file name
  flashDrive.openFile();                                                  //open the file

  flashDrive.writeFile((char *)str.c_str(), str_len);

  flashDrive.closeFile();  //at the end, close the file
  Serial.println("Done!");
}



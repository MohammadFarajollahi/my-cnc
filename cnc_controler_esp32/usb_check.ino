





//************************************************************************************usb_check********************************************************************************
//************************************************************************************usb_check********************************************************************************
//************************************************************************************usb_check********************************************************************************
void usb_check() {

  if (flash_test == 0) {
    flash_test = 1;
    if (flashDrive.getDeviceStatus()) {
      Serial.println(F("Flash drive attached!"));
      drawSdJpeg("/usb_on.jpg", 430, 30);
      usb_in = 1;
    
    } else {
      Serial.println(F("Flash drive detached!"));
      drawSdJpeg("/usb_off.jpg", 430, 30);
      usb_in = 0;
    }
  }

  if (flashDrive.checkIntMessage()) {
    if (flashDrive.getDeviceStatus()) {
      Serial.println(F("Flash drive attached!"));
      drawSdJpeg("/usb_on.jpg", 430, 30);
      usb_in = 1;
    } else {
      Serial.println(F("Flash drive detached!"));
      drawSdJpeg("/usb_off.jpg", 430, 30);
      usb_in = 0;
    }
  }
}


//***************************88check_namayesh_paeintar**********************************
void usb_check2() {
  if (flash_test == 0) {
    flash_test = 1;
    if (flashDrive.getDeviceStatus()) {
      Serial.println(F("Flash drive attached!"));
      drawSdJpeg("/usb_on.jpg", 430, 100);
      usb_in = 1;
    } else {
      Serial.println(F("Flash drive detached!"));
      drawSdJpeg("/usb_off.jpg", 430, 100);
      usb_in = 0;
    }
  }

  if (flashDrive.checkIntMessage()) {
    if (flashDrive.getDeviceStatus()) {
      Serial.println(F("Flash drive attached!"));
      drawSdJpeg("/usb_on.jpg", 430, 100);
      usb_in = 1;
    } else {
      Serial.println(F("Flash drive detached!"));
      drawSdJpeg("/usb_off.jpg", 430, 100);
      usb_in = 0;
    }
  }
}



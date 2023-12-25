





//************************************************************************************usb_check********************************************************************************
//************************************************************************************usb_check********************************************************************************
//************************************************************************************usb_check********************************************************************************
void usb_check() {

  if (flash_test == 0) {
    flash_test = 1;
    if (flashDrive.getDeviceStatus()) {
      Serial.println(F("Flash drive attached!"));
      drawSdJpeg("/usb_on.jpg", 430, 30);
    
    } else {
      Serial.println(F("Flash drive detached!"));
      drawSdJpeg("/usb_off.jpg", 430, 30);
    }
  }

  if (flashDrive.checkIntMessage()) {
    if (flashDrive.getDeviceStatus()) {
      Serial.println(F("Flash drive attached!"));
      drawSdJpeg("/usb_on.jpg", 430, 30);
    } else {
      Serial.println(F("Flash drive detached!"));
      drawSdJpeg("/usb_off.jpg", 430, 30);
    }
  }
}





//******************************************************************select_storage***************************************************************************************
void select_storage() {
  exit_main = 0;
  flash_test = 0;

  tft.fillScreen(TFT_WHITE);
  drawSdJpeg("/select_storage.jpg", 0, 0);
  while (1) {
    input_touch3();
    usb_check2();

    if (x_t > 100 && x_t < 200 && y_t > 80 && y_t < 260 && usb_in == 0) {
      digitalWrite(buzzer, HIGH);
      delay(200);
      digitalWrite(buzzer, LOW);
      delay(200);
      digitalWrite(buzzer, HIGH);
      delay(200);
      digitalWrite(buzzer, LOW);
    }

    if (x_t > 100 && x_t < 200 && y_t > 80 && y_t < 260 && usb_in == 1) {  //usb select
      digitalWrite(buzzer, HIGH);
      delay(50);
      digitalWrite(buzzer, LOW);
      x_t = 0;
      y_t = 0;
      usb = 1;
      usb_file_list();
    }

    if (x_t > 280 && x_t < 450 && y_t > 80 && y_t < 260) {  //ram select
      digitalWrite(buzzer, HIGH);
      delay(50);
      digitalWrite(buzzer, LOW);
      x_t = 0;
      y_t = 0;
      usb = 0;
      g_cod2();
    }

    if (x_t > 1 && x_t < 70 && y_t > 250 && y_t < 300) {
      digitalWrite(buzzer, HIGH);
      delay(50);
      digitalWrite(buzzer, LOW);
      x_t = 0;
      y_t = 0;
      exit_main = 1;
    }

    if (exit_main == 1) {
      x_t = 0;
      y_t = 0;
      start_show();
      break;
      delay(1000);
    }

    ////
  }
}

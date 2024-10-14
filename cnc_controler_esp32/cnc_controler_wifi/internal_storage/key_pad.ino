

void keypad_() {
  char key = keypad.getKey();

  if (key) {
    Serial.println(key);
    //***x+***
    if (key == '6') {
      digitalWrite(uart_enbale, HIGH);
      digitalWrite(buzzer, HIGH);
      delay(5);
      digitalWrite(buzzer, LOW);
      my_send = "$J=G91X" + String(step_count) + "F" + String(speed_count);
      // my_send = "$J=G91X2.0F500";

      print_lcd(my_send);
      print_lcd2("MOVE X+");
      hwSerial.println(my_send);
      Serial.println(my_send);
      delay(200);
      digitalWrite(uart_enbale, LOW);
    }

    //***x-***
    if (key == '4') {
      digitalWrite(uart_enbale, HIGH);
      digitalWrite(buzzer, HIGH);
      delay(5);
      digitalWrite(buzzer, LOW);
      my_send = "$J=G91X-" + String(step_count) + "F" + String(speed_count);
      print_lcd(my_send);
      print_lcd2("MOVE X-");
      hwSerial.println(my_send);
      Serial.println(my_send);
      delay(200);
      digitalWrite(uart_enbale, LOW);
    }


    //***y+***
    if (key == '2') {
      digitalWrite(uart_enbale, HIGH);
      digitalWrite(buzzer, HIGH);
      delay(5);
      digitalWrite(buzzer, LOW);
      my_send = "$J=G91Y" + String(step_count) + "F" + String(speed_count);
      // my_send = "$J=G91X2.0F500";

      print_lcd(my_send);
      print_lcd2("MOVE Y+");
      hwSerial.println(my_send);
      Serial.println(my_send);
      delay(200);
      digitalWrite(uart_enbale, LOW);
    }

    //***y-***
    if (key == '8') {
      digitalWrite(uart_enbale, HIGH);
      digitalWrite(buzzer, HIGH);
      delay(5);
      digitalWrite(buzzer, LOW);
      my_send = "$J=G91Y-" + String(step_count) + "F" + String(speed_count);
      print_lcd(my_send);
      print_lcd2("MOVE Y-");
      hwSerial.println(my_send);
      Serial.println(my_send);
      delay(200);
      digitalWrite(uart_enbale, LOW);
    }

    //***Z+***
    if (key == '1') {
      digitalWrite(uart_enbale, HIGH);
      digitalWrite(buzzer, HIGH);
      delay(5);
      digitalWrite(buzzer, LOW);
      my_send = "$J=G91Z" + String(step_count) + "F" + String(speed_count);
      // my_send = "$J=G91X2.0F500";

      print_lcd(my_send);
      print_lcd2("MOVE Z+");
      hwSerial.println(my_send);
      Serial.println(my_send);
      delay(200);
      digitalWrite(uart_enbale, LOW);
    }

    //***Z-***
    if (key == '3') {
      digitalWrite(uart_enbale, HIGH);
      digitalWrite(buzzer, HIGH);
      delay(5);
      digitalWrite(buzzer, LOW);
      my_send = "$J=G91Z-" + String(step_count) + "F" + String(speed_count);
      print_lcd(my_send);
      print_lcd2("MOVE Z-");
      hwSerial.println(my_send);
      Serial.println(my_send);
      delay(200);
      digitalWrite(uart_enbale, LOW);
    }


    //***blink***
    if (key == '5') {
      digitalWrite(uart_enbale, HIGH);
      digitalWrite(buzzer, HIGH);
      delay(50);
      digitalWrite(buzzer, LOW);
      hwSerial.println("M3 S1000");
      delay(50);
      hwSerial.println("G1 F1000");
      delay(150);
      hwSerial.println("M5 S0");
      delay(50);
      hwSerial.println("G0");
      print_lcd("M3 S1000");
      print_lcd2("LASET TEST");
      delay(100);
      digitalWrite(uart_enbale, LOW);
    }

    //***zero_point***
    if (key == '0') {
      digitalWrite(uart_enbale, HIGH);
      digitalWrite(buzzer, HIGH);
      delay(20);
      digitalWrite(buzzer, LOW);
      my_send = "G92 X0 Y0 Z0";
      //my_send = "$J=G91X2.0F500";

      print_lcd(my_send);
      print_lcd2("zero point");
      hwSerial.println(my_send);
      Serial.println(my_send);
      delay(200);
      digitalWrite(uart_enbale, LOW);
    }

    //***home***
    if (key == '#') {
      digitalWrite(uart_enbale, HIGH);
      x_t = 0;
      y_t = 0;
     // print_lcd4("Home corner");
      digitalWrite(buzzer, HIGH);
      delay(50);
      digitalWrite(buzzer, LOW);
      //print_lcd3("$H");
      hwSerial.println("$H");
      delay(3000);
      digitalWrite(uart_enbale, LOW);
    }



    ///
  }
}


//////////////////////////////////////////////////////////////////////////////////////////////////////

void keypad_2() {
  char key = keypad.getKey();

  if (key) {
    Serial.println(key);
    //***x+***
    if (key == '6') {
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

    //***x-***
    if (key == '4') {
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


    //***y+***
    if (key == '2') {
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

    //***y-***
    if (key == '8') {
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

    //***Z+***
    if (key == '1') {
      x_t = 0;
      y_t = 0;
      digitalWrite(uart_enbale, HIGH);
      digitalWrite(buzzer, HIGH);
      delay(5);
      digitalWrite(buzzer, LOW);
      my_send = "$J=G91Z" + String(step_count) + "F" + String(speed_count);
      // my_send = "$J=G91X2.0F500";

      print_lcd3(my_send);
      print_lcd4("MOVE Z+");
      hwSerial.println(my_send);
      Serial.println(my_send);
      delay(200);
      digitalWrite(uart_enbale, LOW);
    }

    //***Z-***
    if (key == '3') {
      x_t = 0;
      y_t = 0;
      digitalWrite(uart_enbale, HIGH);
      digitalWrite(buzzer, HIGH);
      delay(5);
      digitalWrite(buzzer, LOW);
      my_send = "$J=G91Z-" + String(step_count) + "F" + String(speed_count);
      print_lcd3(my_send);
      print_lcd4("MOVE Z-");
      hwSerial.println(my_send);
      Serial.println(my_send);
      delay(200);
      digitalWrite(uart_enbale, LOW);
    }


    //***blink***
    if (key == '5') {
      digitalWrite(uart_enbale, HIGH);
      digitalWrite(buzzer, HIGH);
      delay(50);
      digitalWrite(buzzer, LOW);
      hwSerial.println("M3 S1000");
      print_lcd3("M3 S1000");
      delay(50);
      hwSerial.println("G1 F1000");
      print_lcd3("G1 F1000");
      delay(150);
      hwSerial.println("M5 S0");
      print_lcd3("M5 S0");
      delay(50);
      hwSerial.println("G0");   
      print_lcd3("G0");
      print_lcd4("BLINK TEST");
      delay(100);
      digitalWrite(uart_enbale, LOW);
    }

    //***zero_point***
    if (key == '0') {
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

    //***home***
    if (key == '#') {
      digitalWrite(uart_enbale, HIGH);
      x_t = 0;
      y_t = 0;
     // print_lcd4("Home corner");
      digitalWrite(buzzer, HIGH);
      delay(50);
      digitalWrite(buzzer, LOW);
     // print_lcd3("$H");
      hwSerial.println("$H");
      delay(3000);
      digitalWrite(uart_enbale, LOW);
    }

    //***frame***
    if (key == '*' && main_run == 1) {
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

    ///
  }
}
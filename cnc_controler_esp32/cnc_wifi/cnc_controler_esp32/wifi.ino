String wifi_input;

void WIFI_CONTROL() {

  if (WiFi.status() == WL_CONNECTED) {
    temperature = httpGETRequest(serverNameTemp);
    //Serial.println("key: " + temperature);
    wifi_input = temperature;
    //************Y+*************
    if (wifi_input == "2") {
       
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


    //************Y-*************
    if (wifi_input == "8") {
    
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


    //************x+*************
    if (wifi_input == "4") {
     
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

    //************x-*************
    if (wifi_input == "6") {
     
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


    //************Z+*************
    if (wifi_input == "1") {
     
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

    //************Z-*************
    if (wifi_input == "3") {
     
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

    //************ZERO*************
    if (wifi_input == "0") {
      
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

    //************HOME*************
    if (wifi_input == "60") {
     
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

    //************BLINK*************
    if (wifi_input == "5") {
     
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

    //********step_setting**********
    if (wifi_input == "10") {
      
      if (step_count < 1) {
        step_count = step_count + .1;
      } else if (step_count >= 1 && step_count < 10) {
        step_count = step_count + 1;
      } else if (step_count >= 10 && step_count < 50) {
        step_count = step_count + 5;
      } else if (step_count >= 50) {
        step_count = step_count + 50;
      }
      if (step_count > 200) step_count = 200;
      Serial.println(String(step_count));

      tft.fillRoundRect(64, 209, 55, 10, 5, TFT_WHITE);
      tft.setTextColor(TFT_BLACK, TFT_WHITE);
      tft.setCursor(65, 210);
      tft.println(String(step_count));
      delay(100);
    }

    if (wifi_input == "20") {
      
      if (step_count <= 1) {
        step_count = step_count - .1;
      } else if (step_count > 1 && step_count <= 10) {
        step_count = step_count - 1;
      } else if (step_count > 10 && step_count <= 50) {
        step_count = step_count - 5;
      } else if (step_count > 50) {
        step_count = step_count - 50;
      }

      if (step_count > 200) step_count = 200;
      else if (step_count < .1) step_count = .1;
      Serial.println(String(step_count));
      tft.fillRoundRect(64, 209, 55, 10, 5, TFT_WHITE);
      tft.setTextColor(TFT_BLACK, TFT_WHITE);
      tft.setCursor(65, 210);
      tft.println(String(step_count));
      delay(100);
    }

    //********speed_setting**********
    if (wifi_input == "30") {
     
      speed_count = speed_count + 500;
      if (speed_count > 40000) speed_count = 40000;
      Serial.println(String(speed_count));
      tft.fillRoundRect(54, 279, 54, 10, 5, TFT_WHITE);
      tft.setTextColor(TFT_BLACK, TFT_WHITE);
      tft.setCursor(55, 280);
      tft.println(String(speed_count));
      delay(100);
    }

    if (wifi_input == "40") {
     
      digitalWrite(buzzer, HIGH);
      delay(5);
      digitalWrite(buzzer, LOW);
      speed_count = speed_count - 500;
      if (speed_count < 500) speed_count = 500;
      Serial.println(String(speed_count));
      tft.fillRoundRect(54, 279, 54, 10, 5, TFT_WHITE);
      tft.setTextColor(TFT_BLACK, TFT_WHITE);
      tft.setCursor(55, 280);
      tft.println(String(speed_count));
      delay(100);
    }
   
  } else {
    //Serial.println("WiFi Disconnected");
  }
}



String httpGETRequest(const char* serverName) {
  WiFiClient client;
  HTTPClient http;

  // Your Domain name with URL path or IP address with path
  http.begin(client, serverName);

  // Send HTTP POST request
  int httpResponseCode = http.GET();

  String payload = "--";

  if (httpResponseCode > 0) {
    // Serial.print("HTTP Response code: ");
    // Serial.println(httpResponseCode);
    payload = http.getString();
  } else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }
  // Free resources
  http.end();

  return payload;
}
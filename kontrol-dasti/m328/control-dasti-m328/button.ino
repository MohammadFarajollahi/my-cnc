

void button() {
  if (digitalRead(k_start) == 0) {
    Serial.println("start");
    digitalWrite(uart, HIGH);
    delay(200);
    simserial.println("$X");
    delay(200);
    simserial.println("$$");
    delay(200);
    digitalWrite(uart, LOW);
  }

  if (digitalRead(k_stop) == 0) {
    digitalWrite(uart, HIGH);
    delay(500);
    simserial.println("G92 X0 Y0 Z0");
    delay(500);
    digitalWrite(uart, LOW);
  }

  if (digitalRead(k_up) == 0) {
    Serial.println("up");
    //simserial.println("$J=F2000 G91 X-1000");
    digitalWrite(uart, HIGH);
    delay(15);
    while (1) {
      simserial.println("$J=G91X-0.1F500");
      delay(10);
      if (digitalRead(k_up) == 1) {
        digitalWrite(uart, LOW);
        break;
      }
    }
    delay(20);
  }

  if (digitalRead(k_down) == 0) {
    Serial.println("down");
    digitalWrite(uart, HIGH);
    delay(20);
    // simserial.println("$J=F2000 G91 X1000");
    while (1) {
      simserial.println("$J=G91X0.5F1000");
      delay(20);
      if (digitalRead(k_down) == 1) {
        digitalWrite(uart, LOW);
        break;
      }
    }
    delay(20);
  }

  if (digitalRead(k_right) == 0) {
    Serial.println("right");
    digitalWrite(uart, HIGH);
    delay(20);
    // simserial.println("$J= G91F2000 Z3000");
    while (1) {
      simserial.println("$J=G91Z0.5F1000");
      delay(20);
      if (digitalRead(k_right) == 1) {
        digitalWrite(uart, LOW);
        break;
      }
    }
    delay(20);
  }

  if (digitalRead(k_left) == 0) {
    Serial.println("left");
    //simserial.println("$J= G91F2000 Z-3000");
    digitalWrite(uart, HIGH);
    delay(20);
    // simserial.println("$J= G91F2000 Z3000");
    while (1) {
      simserial.println("$J=G91Z-0.5F1000");
      delay(20);
      if (digitalRead(k_left) == 1) {
        digitalWrite(uart, LOW);
        break;
      }
    }
    delay(20);
  }
}
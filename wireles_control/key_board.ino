

void key_board() {
  adc2 = 0;
  adc = analogRead(34);
  for (int i = 0; i < 10; i++) {
    adc = analogRead(34);
    adc2 += adc;
    delay(1);
  }
  adc2 /= 10;
  // Serial.print("adc:");
  // Serial.println(String(adc2));
  // delay(200);
  old_key = key;
  if (adc2 > 10) {

    if (adc2 >= 3155 && adc2 <= 3185) {
      // Serial.print("key:");
      // Serial.println("1");
      key = 1;
    }

    if (adc2 >= 2900 && adc2 <= 2915) {
      // Serial.print("key:");
      // Serial.println("2");
      key = 2;
    }

    if (adc2 >= 2780 && adc2 <= 2792) {
      // Serial.print("key:");
      // Serial.println("3");
      key = 3;
    }

    if (adc2 >= 2555 && adc2 <= 2595) {
      // Serial.print("key:");
      // Serial.println("A");
      key = 10;
    }

    if (adc2 >= 2540 && adc2 <= 2546) {
      // Serial.print("key:");
      // Serial.println("4");
      key = 4;
    }

    if (adc2 >= 2390 && adc2 <= 2400) {
      // Serial.print("key:");
      // Serial.println("5");
      key = 5;
    }

    if (adc2 >= 2290 && adc2 <= 2310) {
      // Serial.print("key:");
      // Serial.println("6");
      key = 6;
    }

    if (adc2 >= 2180 && adc2 <= 2190) {
      // Serial.print("key:");
      // Serial.println("B");
      key = 20;
    }

    if (adc2 >= 2050 && adc2 <= 2099) {
      // Serial.print("key:");
      // Serial.println("7");
      key = 7;
    }

    if (adc2 >= 1980 && adc2 <= 2000) {
      // Serial.print("key:");
      // Serial.println("8");
      key = 8;
    }

    if (adc2 >= 1900 && adc2 <= 1946) {
      // Serial.print("key:");
      // Serial.println("9");
      key = 9;
    }

    if (adc2 >= 1810 && adc2 <= 1840) {
      // Serial.print("key:");
      // Serial.println("C");
      key = 30;
    }

    if (adc2 >= 1760 && adc2 <= 1795) {
      // Serial.print("key:");
      // Serial.println("*");
      key = 40;
    }

    if (adc2 >= 1700 && adc2 <= 1720) {
      // Serial.print("key:");
      // Serial.println("0");
      key = 0;
    }

    if (adc2 >= 1645 && adc2 <= 1680) {
      // Serial.print("key:");
      // Serial.println("#");
      key = 50;
    }

    if (adc2 >= 1580 && adc2 <= 1600) {
      // Serial.print("key:");
      // Serial.println("D");
      key = 60;
    }
  }
  if (adc2 < 10) key = 11;

  if (key == old_key) {
    ++key_count1;
    if (key_count1 >= 3) {
      send_key = key;
      Serial.print("key:");
      Serial.println(send_key);
    }
  }

  if (key != old_key) {
    key_count1 = 0;
  }
}
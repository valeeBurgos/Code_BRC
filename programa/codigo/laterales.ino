
int v_s_min_lat[2] = {1023, 1023};
int v_s_max_lat[2] = {0, 0};
volatile int s_p_lat[2];
  
int l_pos_lat;

void calibracion_lat() {

  int v_s_lat[2];
  for (int j = 0; j < 200; j++) {
    delay(10);
    v_s_lat[0] = analogRead(A0);
    v_s_lat[1] = analogRead(A7);
    for (int i = 0; i < 2; i++) {
      Serial.print(v_s_lat[i]);
      Serial.print("\t");
    }
    Serial.println();
    for (int i = 0; i < 2; i++) {
      if (v_s_lat[i] < v_s_min_lat[i]) {
        v_s_min_lat[i] = v_s_lat[i];
      }
    }
    for (int i = 0; i < 2; i++) {
      if (v_s_lat[i] > v_s_max_lat[i]) {
        v_s_max_lat[i] = v_s_lat[i];
      }
    }
  }
  beep();
  beep();
  Serial.println();
  Serial.print("Mínimos ");
  Serial.print("\t");
  for (int i = 0; i < 2; i++) {
    Serial.print(v_s_min_lat[i]);
    Serial.print("\t");
  }
  Serial.println();
  Serial.print("Máximos ");
  Serial.print("\t");
  for (int i = 0; i < 2; i++) {
    Serial.print(v_s_max_lat[i]);
    Serial.print("\t");
  }
  Serial.println();
  Serial.println();
  Serial.println();
}






void readSensors_lat() {
  volatile int s_lat[2];
  s_lat[0] = analogRead(A0);
  s_lat[1] = analogRead(A7);
 

  for (int i = 0; i < 2; i++) {
    if (s_lat[i] < v_s_min_lat[i]) {
      s_lat[i] = v_s_min_lat[i];
    }
    if (s_lat[i] > v_s_max_lat[i]) {
      s_lat[i] = v_s_max_lat[i];
    }
    s_p_lat[i] = map(s_lat[i], v_s_min_lat[i], v_s_max_lat[i], 100, 0);
  }
}

int GetLat_() {
  readSensors_lat();
   if (s_p_lat[0] < 70 and s_p_lat[1] < 70) {
    //tone(PINBUZZER, 1500, 50);
   }
   else if (s_p_lat[0] < 70) {
    //tone(PINBUZZER, 1500, 50);
    //tone(PINBUZZER, 1500, 50);
   }
   else if (s_p_lat[1] < 70) {
    //tone(PINBUZZER, 1500, 50);
   }

   return 0;
  
}

int mot11 = 3;
int mot12 = 4;
int mot21 = 5;
int mot22 = 6;
int en1 = 9;
int en2 = 10;
int spd = 0;
int flag = 0;
char cmd; //command
int spd1 = 0;
void setup() {
  Serial.begin(9600);
  pinMode(mot11, OUTPUT);
  pinMode(mot12, OUTPUT);
  pinMode(mot22, OUTPUT);
  pinMode(mot21, OUTPUT);
  pinMode(en1, OUTPUT);
  pinMode(en2, OUTPUT);
}

void forward(){
  digitalWrite(mot11, HIGH);
  digitalWrite(mot12, LOW);
  digitalWrite(mot21, HIGH);
  digitalWrite(mot22, LOW);
  Serial.print("Forward");
}

void right(){
  digitalWrite(mot11, HIGH);
  digitalWrite(mot12, LOW);
  digitalWrite(mot21, LOW);
  digitalWrite(mot22, LOW);
  Serial.print("Right");
}

void left(){
  digitalWrite(mot11, LOW);
  digitalWrite(mot12, LOW);
  digitalWrite(mot21, HIGH);
  digitalWrite(mot22, LOW);
  Serial.print("Left");
}

void back(){
  digitalWrite(mot11, LOW);
  digitalWrite(mot12, HIGH);
  digitalWrite(mot21, LOW);
  digitalWrite(mot22, HIGH);
  Serial.print("Back");
}

void stay(){
  digitalWrite(mot11, LOW);
  digitalWrite(mot12, LOW);
  digitalWrite(mot21, LOW);
  digitalWrite(mot22, LOW);
  Serial.print("Stop");
}

void checkflag(){
  cmd = Serial.read();
  if (cmd == 'u'){//Flag 1 for Forward
    flag = 1;
  }
  if (cmd == 'd'){//Flag 2 for Back
    flag = 2;
  }
  if (cmd == 's'){//Flag 3 for Stay
    flag = 3;
  }
  if (cmd == 'r'){//Flag 4 for Right
    flag = 4;
  }
  if (cmd == 'l'){//Flag 5 for Left
    flag = 5;
  }
}


void loop() {
  cmd = Serial.read();
  checkflag();
  
  if(flag == 1){
    if (spd == 0){ //Letter  is forward
      for(spd = 0; spd <= 255; spd++){
        analogWrite(en1, spd);
        analogWrite(en2, spd);
        forward();
        Serial.println(spd);
        spd1 = spd;  
        checkflag();
      }
    }
    if(spd == 256){
      forward();
      checkflag();
    }
  }
  
  if(flag == 2){
    if (spd == 0){ //Letter D is Back
      for(spd = 0; spd <= 255; spd++){
        analogWrite(en1, spd);
        analogWrite(en2, spd);
        back();
        Serial.println(spd);
        spd1 = spd;  
        checkflag();
      }
    }
    if(spd == 256){
      back();
      checkflag();
    }
  }
  if (flag == 4){ //Letter B is Right
    if(spd1 == 0){
      spd1 == 120;
    }
    analogWrite(en1, spd1);
    analogWrite(en2, spd1);
    left();
    Serial.println(spd1);  
    checkflag();
  }
   
  if (flag == 5){ //Letter C is Left
    if (spd1 == 0){
      spd1 = 120;
    }
    analogWrite(en1, spd1);
    analogWrite(en2, spd1);
    right();
    Serial.println(spd1);  
    checkflag();
  }
 
  if (flag == 3){ //Letter E is Stop    
      for(spd = 200; spd > 0; spd--){
        analogWrite(en1, spd);
        analogWrite(en2, spd);
        Serial.println(spd);  
        checkflag();
        Serial.print("Stop");
    }
    Serial.print(spd);
    if (spd == 0){
      stay();
      checkflag();
      
    }
  }    
} 

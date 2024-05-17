#include <Servo.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

int mTime = 350;

int servoPin1 = 8;
int servoPin2 = 9;

Servo servo1;
Servo servo2;

int button1 = 2;
int button2 = 3;
int motor1 = 4;
int motor2 = 5;
int peso1  = 6;
int peso5 = 7;
int lights = 10;

void setup() {
  // put your setup code here, to run once:
//initiate lcd
  lcd.init();
	lcd.backlight();
	lcd.clear();
	lcd.setCursor(0,0);
	lcd.print("BOOTING UP");
  Serial.begin(9600);

  servo1.attach(servoPin1);
  servo2.attach(servoPin2);

  pinMode(button1, INPUT_PULLUP);
  pinMode(button2, INPUT_PULLUP);
  pinMode(motor1, OUTPUT);
  pinMode(motor2, OUTPUT);
  pinMode(lights, OUTPUT);
  pinMode(peso1, INPUT_PULLUP);
  pinMode(peso5, INPUT_PULLUP);

  digitalWrite(motor1, LOW);
  digitalWrite(motor2, LOW);
  digitalWrite(lights, LOW);
  //initiate servos
  servo1.write(180);
  servo2.write(180);
  delay(1000);
  servo1.write(0);
  servo2.write(0);
  lcd.clear();
}
void processing(){
  lcd.clear();
  lcd.print("PROCESSING");
  delay(500);
  lcd.print(".");
  delay(500);
  lcd.print(".");
  delay(500);
  lcd.print(".");
  delay(500);
  lcd.print(".");
  delay(500);
  lcd.print(".");
  delay(500);
  lcd.clear();
  
}

void food1_release(){
  int fPrice = 8;
  int insert = 0;
  lcd.print("INSERT EXACT");
  lcd.setCursor(0, 1);
  lcd.print("AMOUNT: P");
  lcd.print(fPrice);
  delay(3000);
  reset1:
  char coin1 = digitalRead(peso1);
  char coin5 = digitalRead(peso5);
  
  lcd.print("PAYMENT: P");
  lcd.print(fPrice);
  lcd.setCursor(0, 1);
  lcd.print("INSERTED: P");
  lcd.print(insert);
  delay(100);
  lcd.clear();
  
  if(coin1 == LOW){
    insert+=1;
    delay(500);
    Serial.print(insert);
    servo1.write(180);
    delay(500);
    servo1.write(0);
    delay(500);

    
    if(insert>=fPrice){
      delay(1000);
      digitalWrite(motor1, HIGH);
      delay(mTime);
      digitalWrite(motor1,LOW);
      return 0;
    }
    else if(insert<fPrice){
      goto reset1;
    }
    else{
      goto reset1;
    }

  }
  
  if(coin5 == LOW){
    insert+=5;
    delay(500);
    Serial.print(insert);
    servo2.write(180);
    delay(500);
    servo2.write(0);
    delay(500);
    if(insert<fPrice){
      goto reset1;
    }
    else if(insert>=fPrice){
      delay(1000);
      digitalWrite(motor1, HIGH);
      delay(mTime);
      digitalWrite(motor1,LOW);
    }
    else{
      goto reset1;
    }
  }
  
  else{
    goto reset1;
  }
}

void food2_release(){
  int fPrice = 10;
  int insert = 0;
  lcd.print("INSERT EXACT");
  lcd.setCursor(0, 1);
  lcd.print("AMOUNT: P");
  lcd.print(fPrice);
  delay(3000);
  reset1:
  char coin1 = digitalRead(peso1);
  char coin5 = digitalRead(peso5);
  
  lcd.print("PAYMENT: P");
  lcd.print(fPrice);
  lcd.setCursor(0, 1);
  lcd.print("INSERTED: P");
  lcd.print(insert);
  delay(100);
  lcd.clear();  
  if(coin1 == LOW){
    insert+=1;
    delay(500);
    Serial.print(insert);
    servo1.write(180);
    delay(500);
    servo1.write(0);
    delay(500);

    if(insert>=fPrice){
      delay(1000);
      digitalWrite(motor2, HIGH);
      delay(mTime);
      digitalWrite(motor2,LOW);
      return 0;
    }
    if(insert<fPrice){
      goto reset1;
    }
    else{
      goto reset1;
    }

  }
  
  if(coin5 == LOW){
    insert+=5;
    delay(500);
    Serial.print(insert);
    servo2.write(180);
    delay(500);
    servo2.write(0);
    delay(500);
    if(insert<fPrice){
      goto reset1;
    }
    else if(insert>=fPrice){
      delay(1000);
      digitalWrite(motor2, HIGH);
      delay(mTime);
      digitalWrite(motor2,LOW);
      return 0;    
    }
    else{
      goto reset1;
    }
  }
  
  else{
    goto reset1;
  }
}



void loop() {
  lcd.print("SELECT ITEM");
  delay(100);
  lcd.clear();
  // put your main code here, to run repeatedly:
  char b1 = digitalRead(button1);
  char b2 = digitalRead(button2);

  if(b1 == LOW){
    Serial.print("FOOD 1 SELECTED");
    lcd.print("FOOD 1 SELECTED");
    delay(2000);
    processing();
    food1_release();
    lcd.clear();
    lcd.print("ENJOY!");
    Serial.print("Dispensed!");
    delay(2000);
    return 0;
  }

  if(b2 == LOW){
    Serial.print("FOOD 2 SELECTED");
    lcd.print("FOOD 2 SELECTED");
    delay(2000);
    processing();
    food2_release();
    lcd.clear();
    lcd.print("ENJOY!");
    Serial.print("Dispensed!");
    delay(2000);    
    return 0;
  }

  else{
    digitalWrite(motor1, LOW);
    digitalWrite(motor2, LOW);
    return 0;
  }
  int insert = 0;
  
}

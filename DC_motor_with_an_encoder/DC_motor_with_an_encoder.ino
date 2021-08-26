// DC motor with an encoder
=================================

// define encoder pin
#define ENCA 2            // yellow
#define ENCB 3            // white
// define dc motor and pwm pin
#define PWM 5             // motor driver pwm
#define IN2 6             // motor driver IN2 input
#define In1 7             // motor driver IN1 input

 int pos 0;               // set the position of the motor as in 0 state mean the middle
 
------------
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(ENCA, INPUT);
  pinMode(ENCB, INPUT);

// attachInterrupt(encoder_output_pin, function_to_called_after_interrupt,trigger_type)   
  attachInterrupt(digitalPinToInterrupt(ENCA), readEncoder, RISING); // interrupt the trigger output A rising and readEncoder is the function to define below
 
  
}
-----------
void loop() {
  // the first test before using attachInterrupt function
  /* 
    int a = digitalRead(ENCA);
    int b = digitalRead(ENCB);
    Serial.print(a*5);
    Serial.print(" ");
    Serial.print("b*5);
  */
  setMotor(1,25,PWM,IN1,IN2);
  delay(200);
  Serial.println(pos);          // to report the current position
  setMotor(-1,25,PWM,IN1,IN2);
  delay(200);
  Serial.println(pos);
  setMotor(0,25,PWM,IN1,IN2);
  delay(200);
  Serial.println(pos);

 
}
---------
// to set the direction and speed of the motor, pwmVal = pwm speed
void setMotor(int dir, int pwmVal, int pwm, int in1, int in2){ 
  
  analogWrite(pwm,pwmVal);
  if(dir ==1){
    digitalWrite(in1,HIGH);
    digitalWrite(in2,LOW);
  }
  else if(dir == -1){         
    digitalWrite(in1,LOW);
    digitalWrite(in2,HIGH);
  }
  else {                      // stop the motor
    digitalWrite(in1,LOW);
    digitalWrite(in2,LOW);
  }
  }
-----------
// the important part of the code
// funtion that use in the attachInterrupt function
void readEncoder(){
  int b = digitalRead(ENCB);
  if(b>0){
    pos++; 
  }
  else{
    pos--;
  }
  }

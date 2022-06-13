int DIR_pin = 2;
int PWM_pin = 3;
int ENC_A = 20;
int ENC_B = 21;
int A =0;
int B=0;
int position_error = 0;
int sterring_speed = 0;
void motor_setup()
{

  pinMode(DIR_pin, OUTPUT);
  pinMode(PWM_pin, OUTPUT);
  pinMode(ENC_A, INPUT_PULLUP);
  pinMode(ENC_B, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(ENC_A), decode_rotation_A, RISING);
    attachInterrupt(digitalPinToInterrupt(ENC_B), decode_rotation_B, RISING);

}

void motor_loop()
{
  
  position_error = Sterring_input - Current_position;

  if(abs(position_error)<50)
  {
    sterring_speed = 80;
  }
  else{
    sterring_speed = 255;
  }
  
  if (position_error > 5) {
    
    analogWrite(PWM_pin ,sterring_speed);
    digitalWrite(DIR_pin, HIGH);
  }
  else if (position_error < -5) {
    analogWrite(PWM_pin , sterring_speed);
    digitalWrite(DIR_pin, LOW);
  }
  else {
    analogWrite(PWM_pin , 0);
    digitalWrite(DIR_pin, LOW);
  }


}

void decode_rotation_A() {
   A = digitalRead(ENC_A);
   B = digitalRead(ENC_B);
  

  if (A == 1 && B == 0) {
    Current_position_A -= 1;

  }
  else if (A == 1 && B == 1) {
    Current_position_A += 1;

  }
  Current_position = int((Current_position_B + Current_position_A)/2);


}


void decode_rotation_B() {
   A = digitalRead(ENC_A);
   B = digitalRead(ENC_B);
  

  if (A == 0 && B == 1) {
    Current_position_B += 1;

  }
  else if (A == 1 && B == 1) {
    Current_position_B -= 1;

  }
Current_position = int((Current_position_B + Current_position_A)/2);
}

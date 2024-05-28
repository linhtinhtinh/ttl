#include <Arduino.h>
#include <Adafruit_PWMServoDriver.h>
#include <PS2X_lib.h>
#include <Wire.h>
#include <stdlib.h>
#include <stdio.h>

#define pin1_1 8
#define pin1_2 9 
#define pin2_1 10
#define pin2_2 11
#define pin3_1 12
#define pin3_2 13
#define pin4_1 14
#define pin4_2 15

#define Servo_1 2
#define Servo_2 3

#define PS2_DAT 12 // MISO 
#define PS2_CMD 13 // MOSI 
#define PS2_SEL 15 // SS 
#define PS2_CLK 14 // SLK

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
PS2X ps2x;
void setupPS2controller()
{
  int err = -1;
  while (err != 0)
  {
    err = ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT, true, true);
  }
}

void setup(){
  Wire.begin();
  Serial.begin(115200);
  pwm.begin();
  pwm.setOscillatorFrequency(27000000);
  pwm.setPWMFreq(50);
  Wire.setClock(400000);
  setupPS2controller();
}


void stop(){
  pwm.setPWM(pin1_1,0,0);
  pwm.setPWM(pin1_2,0,0);
  pwm.setPWM(pin2_1,0,0);
  pwm.setPWM(pin2_2,0,0);
}
void go_forward(){
  pwm.setPWM(pin1_1,0,4095);
  pwm.setPWM(pin1_2,0,0);
  pwm.setPWM(pin2_1,0,4095);
  pwm.setPWM(pin2_2,0,0);
}
void go_backward(){
  pwm.setPWM(pin1_1,0,0);
  pwm.setPWM(pin1_2,0,4095);
  pwm.setPWM(pin2_1,0,0);
  pwm.setPWM(pin2_2,0,4095);
}
void right(){
  pwm.setPWM(pin1_1,0,4095);
  pwm.setPWM(pin1_2,0,0);
  pwm.setPWM(pin2_1,0,0);
  pwm.setPWM(pin2_2,0,0);
}
void left(){
  pwm.setPWM(pin1_1,0,0);
  pwm.setPWM(pin1_2,0,0);
  pwm.setPWM(pin2_1,0,4095);
  pwm.setPWM(pin2_2,0,0);

}
void loop(){
  ps2x.read_gamepad(false,false);
  
  if(ps2x.Button(PSB_PAD_UP))
  {
    go_forward();
  }
  else if(ps2x.Button(PSB_PAD_DOWN))
  {
    go_backward();
  }
  else if(ps2x.Button(PSB_PAD_RIGHT))
  {
    right();
  }
  else if(ps2x.Button(PSB_PAD_LEFT))
  {
    left();
  }
  else
  {
    stop();
  }
}
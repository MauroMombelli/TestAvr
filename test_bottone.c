#include "easy_io.h"
#include "time.h"
#include "stdint.h"

#define FALSE 0;
#define TRUE 1;

const uint8_t buttons[] = {19, 25}; // should be digital pin {2, 4}
const uint8_t lights[] = {18, 36}; // should be digital pin {3, 13}

unsigned long last_activated = 0;
unsigned long antibump = 0;
unsigned long timeout = 1000UL * 90;
unsigned long timeout_antibump = 100UL; //half seconds

uint8_t is_timeout = FALSE;

void setup();
void loop();
void turn_me_on() ;
void change_outptut(int status) ;

int main(){
    setup();
    while (1){
      loop();
    }
}

void setup() {

  for (int i = 0; i < sizeof(buttons); i ++) {
    pinMode(buttons[i], INPUT);
    digitalWrite(buttons[i], HIGH);
  }

  for (int i = 0; i < sizeof(lights); i ++) {
    pinMode(lights[i], OUTPUT);
    digitalWrite(lights[i], LOW);
  }
  //Serial.println("start");

}



void loop() {
  uint8_t light_on = FALSE;
  for (int i = 0; i < sizeof(lights); i ++) {
    light_on |= digitalRead(lights[i]);
  }

  uint8_t all_inputs_off = TRUE;
  for (int i = 0; i < sizeof(buttons); i ++) {
    if ( digitalRead(buttons[i]) == HIGH ) {
      all_inputs_off = FALSE;
      break;
    }
  }

  if ( light_on ) {
    if (millis() - last_activated > timeout) {
      //Serial.println("Timeout event");
      change_outptut(LOW);
      is_timeout = TRUE;
    }

    if ( all_inputs_off ) {
      //Serial.println("Closed event");
      change_outptut(LOW);
    }
  } else {
    if (!all_inputs_off) {
      if (!is_timeout) {
        turn_me_on();
      }
    } else {
      is_timeout = FALSE;
    }
  }
}



void turn_me_on() {
  if (millis() - antibump > timeout_antibump ) {
    //Serial.println("ANTIBUMP!");
    antibump = millis();//bump recived, reset timer so we have to have "timeout_antibump" AGAIN
    return;
  }
  //Serial.println("on interrupt");
  last_activated = millis();
  antibump = millis();
  change_outptut(HIGH);
}



void change_outptut(int status) {
  //Serial.print("changing status to ");
  //Serial.println(status);
  for (int i = 0; i < sizeof(lights); i ++) {
    digitalWrite(lights[i], status);
  }
}

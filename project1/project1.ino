#include <pins.h>
void setup(){
  for( int i =0 ; i<=8 ; i++){
    pinMode(pins[i] , OUTPUT);
  }
}
void loop(){
  for ( int i=0 ; i<=8 ; i++){
    digitalWrite(pins[i] , 1);
    delay(500);
    digitalWrite(pins[i],0);
    delay(500);
  }
}
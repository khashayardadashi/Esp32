int LEDS[4] = {23,22,4,2} ;
int pushbutton =15 ;
int FIRST_INDEX;

void setup() {
  pinMode(LEDS[0] , OUTPUT);
  pinMode(LEDS[1] , OUTPUT);
  pinMode(LEDS[2] , OUTPUT);
  pinMode(LEDS[3] , OUTPUT);
  pinMode(pushbutton, INPUT);
  Serial.begin(115200);
  
}

void loop() {
  FIRST_INDEX=0;
  while (FIRST_INDEX <= 3) {
    for(int index = 3 ; index >= FIRST_INDEX ; index--){
      if(index!=FIRST_INDEX) {
        digitalWrite(LEDS[index] , 1);
        delay(500);
        digitalWrite(LEDS[index] , 0);
      } 
      else {
        digitalWrite(LEDS[index] , 1);
      }
      delay(1000);
    }
    FIRST_INDEX++;
  }

  for(int i = 0 ; i<=3 ; i++ ){
    for(int idx = 0 ; idx <= 3 ; idx++){
        digitalWrite(LEDS[idx] , 0);
    }
    delay(1000);
    for(int idx = 0 ; idx <= 3 ; idx++){
        digitalWrite(LEDS[idx] , 1);
    }
    delay(1000);
  }

  for(int idx = 0 ; idx <= 3 ; idx++){
        digitalWrite(LEDS[idx] , 0);
    }
  delay(1000);

}

int r;
float c;
int pins[]={18,19,21,22,23,25,26,27};

void setup(){
  Serial.begin(115200);
  for(int i=0;i<8;i++)
  {
    pinMode(pins[i], OUTPUT);
  }
}
void loop(){
  r =analogRead(15);
  c = r * (3.3) /4096;
  Serial.println(c);
  if( c >= 2.87 && c <= 2.89){
    digitalWrite(18,1);
    delay(1000);
    digitalWrite(18,0);
  }
  else if( c >= 2.78 && c <= 2.80){
    digitalWrite(19,1);
    delay(1000);
    digitalWrite(19,0);
  }
  else if( c >= 2.68 && c <= 2.70){
    digitalWrite(21,1);
    delay(1000);
    digitalWrite(21,0);
  }
  else if( c >= 2.54 && c <= 2.56){
    digitalWrite(22,1);
    delay(1000);
    digitalWrite(22,0);
  }
  else if( c >= 2.36 && c <= 2.38){
    digitalWrite(23,1);
    delay(1000);
    digitalWrite(23,0);
  }
  else if( c >= 2.09 && c <= 2.11){
    digitalWrite(25,1);
    delay(1000);
    digitalWrite(25,0);
  }
  else if( c >= 1.53 && c <= 1.55){
    digitalWrite(26,1);
    delay(1000);
    digitalWrite(26,0);
  }
  else if( c >= 0 && c <= 0.01){
    digitalWrite(27,1);
    delay(1000);
    digitalWrite(27,0);
  }
}
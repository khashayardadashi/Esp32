int startPoint;
float Vpoint;
int r;
float voltage;
char des;
#define BlueLed 23 // + Vsat
#define RedLed 19 // - Vsat
// 1 -> VLTP
//2 -> VUTP

void setup(){
  Serial.begin(115200);
  pinMode(15,INPUT);
  pinMode(BlueLed , OUTPUT);
  pinMode(RedLed , OUTPUT);

}
void loop(){
  startPoint=analogRead(15);
  Vpoint = startPoint * (3.3) / 4096;
  if(Vpoint > 2){
    des = 'b';
    digitalWrite(RedLed , 1);
    digitalWrite(BlueLed, 0);
  }
  else if( Vpoint < 1){
    des = 'f';
    digitalWrite(BlueLed ,1);
    digitalWrite(RedLed , 0);
  }
  r=analogRead(15);
  voltage = r * (3.3) / 4096;
  if( des == 'b'){
    if( voltage <1){
      digitalWrite(RedLed , 0);
      digitalWrite(BlueLed , 1);
    }
  }
  else if( des == 'f'){
    if ( voltage >2 ){
      digitalWrite(BlueLed , 0);
      digitalWrite(RedLed , 1);
    }
  }
}
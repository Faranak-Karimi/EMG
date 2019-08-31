  int x = 100;
void setup() {
  Serial.begin(115200);
  // put your setup code here, to run once:
  pinMode(10,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(10, LOW);
  if(x >=1){
    x = x-1;
    }
    else{
      x = 100;
      }
      // if(Serial.available()){
        Serial.print(x);
      //  }
        delay(100);
}

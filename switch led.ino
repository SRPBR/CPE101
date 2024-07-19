 #define SW1 34 
#define LED 5
int Read_SW1;

int a;
void setup() {
  Serial.begin (9600);
  pinMode (SW1 , INPUT);
  pinMode (LED , OUTPUT);
}
void loop() {
  Read_SW1 = (digitalRead(SW1)== LOW);
  if (Read_SW1 == LOW){
    a = a++;
    Serial.print ("a :");
    Serial.println (a);
  }
  while (digitalRead (SW1) == LOW){;}
  if (a ==1){
    digitalWrite(LED,HIGH);
    }
  if (a == 0){
    digitalWrite(LED,LOW);
    a=0;
  }
 

}

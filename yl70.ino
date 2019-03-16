//PIN MAP
#define ENCODER_1 50
#define ENCODER_2 52
#define OFST 0

//#define PLOT 1
int endcoder_timer = 20;
int enc[2];
bool direction; // true=FRONT, false=BACK
unsigned long time_rotation = millis();
unsigned long Black_rotation = millis();
unsigned long Black_currentTime = millis();

unsigned long White_rotation = millis();
unsigned long White_currentTime = millis();
void setup()
{
 Serial.begin(9600);
 pinMode(ENCODER_1, INPUT);
 pinMode(ENCODER_2, INPUT);

}
void loop()
{
 enc[0] = digitalRead(ENCODER_1);
 enc[1] = digitalRead(ENCODER_2);
 /*Plotter*/
 #ifdef PLOT
 Serial.print(enc[0]+OFST);
 Serial.print(" ");
 Serial.print(digitalRead(enc[1]));
 Serial.println(" ");
 #endif
 delay(endcoder_timer);

//Caclulate direction
#ifdef DIRECTION
 if(enc[0] == 1 && enc[1] == 1){
   enc[0] = digitalRead(ENCODER_1);
   enc[1] = digitalRead(ENCODER_2);
   if(enc[0] == 0 && enc[1] == 1){
      direction = 1;
      Serial.println("FRONT");
   } else
    if(enc[0] == 1 && enc[1] == 0)
   {
     direction = 0;
     Serial.println("BACK");
   }
 } 
#endif
//calculate rotation
Black_currentTime = millis();
while(enc[0] == 1){
  //start timer  
  enc[0] = digitalRead(ENCODER_1);
}
Black_rotation = millis() - Black_currentTime;

White_currentTime = millis();
while(enc[0] == 0){
  //start timer  
  enc[0] = digitalRead(ENCODER_1);
}
White_rotation = millis() - White_currentTime;
time_rotation = White_rotation + Black_rotation;
if(time_rotation > 0){
Serial.print("Time: ");
Serial.print(time_rotation);
Serial.print("ms ");
Serial.print(19.5/time_rotation*36);
Serial.println("km/ora");
}

}


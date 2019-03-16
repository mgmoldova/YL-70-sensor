//PIN MAP
#define ENCODER_1 50
#define ENCODER_2 52
#define OFST 0

//#define PLOT 1
int endcoder_timer = 20;
int enc[2];
bool direction; // true=FRONT, false=BACK
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

 
}

    
/*
коричневый +5 розовый
белый с черным 0 черный
синий ен1 красный
белый с синим ен2 желтый
*/

//PIN MAP
#define ENCODER_1 2
#define ENCODER_2 3
#define OFST 0
#define ANTIFREEZE_DELAY 2000
//#define PLOT 1
int endcoder_timer = 20;
int enc[2];
bool direction; // true=FRONT, false=BACK
unsigned long time_rotation = millis();
unsigned long Black_rotation = millis();
unsigned long Black_currentTime = millis();

unsigned long White_rotation = millis();
unsigned long White_currentTime = millis();
unsigned long anti_freeze = millis();

double total_distance = 0;
uint16_t simple_distance = 0;

bool warning = false;
void setup()
{
 Serial.begin(9600);
 Serial.println("Encoder started..");
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
anti_freeze = millis();
warning = false;
while(enc[0] == 1){
  enc[0] = digitalRead(ENCODER_1);
  //anti-infinite loop
  if(millis() - anti_freeze > ANTIFREEZE_DELAY)
  {
    warning = true;
    break;
  }
}
Black_rotation = millis() - Black_currentTime;

White_currentTime = millis();
anti_freeze = millis();

while(enc[0] == 0){
  enc[0] = digitalRead(ENCODER_1);
  //anti-infinite loop
  if(millis() - anti_freeze > ANTIFREEZE_DELAY)
  {
    warning = true;
    break;
  }
}
White_rotation = millis() - White_currentTime;


time_rotation = White_rotation + Black_rotation;
float speed_km_ora = 19.5/time_rotation*36;
float speed_m_sec = speed_km_ora/3.6;

if(warning)
{
  time_rotation = 0;
  speed_km_ora = 0;
  speed_m_sec = 0;
}
#ifndef PLOT
if(time_rotation >= 0 && speed_km_ora <= 8.0){
total_distance += speed_m_sec * time_rotation / 1000;
Serial.print("Time: ");
Serial.print(time_rotation); Serial.print("ms ");
Serial.print(speed_km_ora); Serial.print("km/h | ");
Serial.print(speed_m_sec); Serial.print("m/s ");
Serial.print("Distance: ");
Serial.print(total_distance); Serial.print("m || ");
Serial.print(simple_distance); Serial.println("cm");

}
#endif
}

#define FULL_ANGLE 300
#define ADC_REF 5
#define ROTARY_ANGLE_SENSOR A0
#define GROVE_VCC 5
#define FULL_ANGLE 300
#define LED 2
#include <math.h>
#include "rgb_lcd.h"

rgb_lcd lcd;

int colorR = 100;
int colorG = 100;
int colorB = 100;
unsigned long elapsed, over;
float h, m, s;                    //Time will flip to zero after 60 min and 60 seconds
float H, M, S, D = 0;             //Continouse time tracking
const int B = 4275;               // B value of the thermistat
const int R0 = 10000;            // R0 = 100k
const int pinTempSensor = A3;     // Grove - Temperature Sensor connect to A3
int f = 0;                            //Fahrenheit
const int ledPin=12;                 // 12C
const int digPin = 2;                // D2
const int thresholdvalue=150;         //The threshold for which the LED should turn on. 
int prevdegrees = 300;                //Remember what the value was before
int bbcount = 0;                      //How many bubbles?
int prevH = 0;                        //Previouse Hours
int prevM = -1;                       //Previouse Minutes

void setup() 
{
    Serial.begin(9600);                //Start the Serial connection            
    pinMode(ledPin,OUTPUT);            //Set the LED on Digital 12 as an OUTPUT         
    pinMode(digPin, INPUT);            //Initialize the Liquid sensor as an input    
    lcd.begin(16, 2);
    lcd.setRGB(colorR, colorG, colorB);    
    lcd.print("#Bbls:");
}
void loop() 
{
  /*LIQUID SENSOR*/
      int sensor_value = analogRead(ROTARY_ANGLE_SENSOR);
      float voltage = (float)sensor_value*ADC_REF/1023;
      int degrees = (voltage*FULL_ANGLE)/GROVE_VCC;    
    
    if (degrees >= thresholdvalue){    
      prevdegrees = degrees;
      }
     else{    
        if(prevdegrees >= thresholdvalue)
        {
          bbcount++;
          lcd.setCursor(6, 0);
          lcd.print("      ");        // clear the space first
          lcd.setCursor(6, 0);          
          lcd.print(bbcount,DEC);          
        }
      prevdegrees = degrees;
      }   
      delay(250); //40 times per second

/*TIME*/
  /*millis() is how many miliseconds has the arduiono been on? 
  Then Convert the ms to Hours and Minutes*/ 
    elapsed = millis(); 
    h = int(elapsed / 3600000); 
    over = elapsed % 3600000;
    m = int(over / 60000);    

  /*millis() is how many miliseconds has the arduiono been on? 
  Then Convert the ms to Hours and Minutes*/ 
    elapsed = millis(); 
    D = int(elapsed / 8640000000);
    H = int(elapsed / 3600000); 
    M = int(elapsed / 60000);
    S = int(elapsed / 1000);
    
if(prevM < M){   //Limit this section to only run once a minute.

        /*Display how long it has been running*/      
              lcd.setCursor(0,1);
              lcd.print("Min:  ");
              lcd.setCursor(4,1);
              lcd.print(m,0);          
              lcd.setCursor(6,1);
              lcd.print("Hr:");            
              lcd.print(h,0);
              lcd.setCursor(11,1);
              lcd.print("Dy:");            
              lcd.print(D,0);
              
        /*Record Bubbles Per Hour if we are at the hour mark*/
           if(prevH < H){                
              Serial.print(bbcount);
              Serial.print(",");
              Serial.print("\n");              
              prevH = H;
              bbcount = 0;                                                      
           }

        /*TEMP/
          /*Show the Temperature*/
              int a = analogRead(pinTempSensor); 
              float R = 1023.0/a-1.0;
              R = R0*R;       
              float temperature = 1.0/(log(R/R0)/B+1/298.15)-273.15; 
              f = (int) temperature; // Convert the datatype float to an int
              f = (f * 1.8) + 32; //Convert to Fahrenheit
          
         /*Change the color of the screen*/
                //ALE   68-73 Fahrenheit
                //LAGER 45-55 Fahrenheit
            if(f <= 67) {
              lcd.setRGB(0, 0, 255);// Blue "Too cold!"
            }
            else if (f >= 73){
              lcd.setRGB(255, 0, 0);// Red "Too hot!"
            }
            else{
              lcd.setRGB(0, 128, 0);// Green "Aww Just Right!"
            }
                lcd.setCursor(12, 0);
                lcd.print("F:");
                lcd.print(f);
  
    prevM = M;
    }
}

#include "four7Seg.h"

//VARIABLES
float value = 32;
const long interval = 5;
const int  buttonPin = 12;
unsigned long counter = 0;
int a,b,c,d = 0;  //To select values to num7seg
int anDiode = A1;
int anK = A5;
int anValue = 0;
float Temperatureamb = 0, FilterTempamb = 0, SumTempamb = 0;
float Temperaturek = 0, FilterTempk = 0, SumTempk = 0;
float T_Thermocouple = 0;
int n = 0;
int buttonState = 0;         // current state of the button
int lastButtonState = 0;     // previous state of the button
int i = 0;                   // to change between T_k, T_amb;

void setup() {
  initDisplay();  
  pinMode(buttonPin, INPUT); //Set digital pin 13 as input
}

void loop() {
  buttonState = digitalRead(buttonPin);
  anValue = analogRead(anK);
  Temperaturek = Ttermocouple(anValue);
  anValue = analogRead(anDiode); 
  Temperatureamb = Tambience(anValue);
  SumTempk = SumTempk + Temperaturek;
  SumTempamb = SumTempamb + Temperatureamb;
  T_Thermocouple = FilterTempk + FilterTempamb;
  //Filter temperature over one second.
  if(n >= 200){
    FilterTempk = SumTempk/n;
    FilterTempamb = SumTempamb/n;
    SumTempamb = 0;
    SumTempk = 0;
    n = -1;
  } 
  
  // compare the buttonState
  if (buttonState != lastButtonState) {
    // if the state has changed, increment the counter
    if (buttonState == HIGH) {
        i = i + 1;
    } 
  }
  n = n + 1;
  if (i == 1)
  {
    splitnumber(T_Thermocouple, &a, &b, &c, &d);
    multiplexDisplay(T_Thermocouple, a, b, c, 0);
  }
  else
  {
    splitnumber(Temperatureamb, &a, &b, &c, &d);
    multiplexDisplay(Temperatureamb, a, b, c, d);
    i = 0;
  }
  lastButtonState = buttonState;
  delay_milis(interval);
}

float Tambience(int analogValue)
{
  //Obtains the temperature from a 1N4148 diode
  //The equation for the one is used: Vdiode = 5*0.0026*T
  //Aux variables
  float vdiode = 0;
  vdiode = (5 * (float)analogValue)/1024;
  return vdiode*76.923 + 4; //where 4 is the offset 
}

float Ttermocouple(int analogValue)
{
  //Obtains the temperature from a 1N4148 diode
  //The equation for the one is used: Vdiode = 5*0.0026*T
  //Aux variables
  float vdiode = 0;
  vdiode = (5 * (float)analogValue)/1024;
  return vdiode*100 + 2.5; //(T-Tamb) offset error
}

void delay_milis(unsigned long period)
{
  counter = millis() + period;
  while(millis() < counter)
  {  
  }
}

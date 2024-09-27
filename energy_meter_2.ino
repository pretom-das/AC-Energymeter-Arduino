#include <LiquidCrystal.h> 
LiquidCrystal lcd(13, 12, 11, 10, 9, 8); 


void setup()
{
  lcd.begin(20, 4); // set up the LCD's number of columns and rows:
  lcd.setCursor(0,0);
  lcd.print("Grour-3");
  lcd.setCursor(0,1);
  lcd.print("AC Energy Meter"); 
}

unsigned int get_max() {
  unsigned int max_v = 0;
  for(int i = 0; i < 100; i++) {
    unsigned int r = analogRead(A0);  // read from analog channel 3 (A3)
    if(max_v < r) {
      max_v = r;
    }
    delayMicroseconds(200);
  }
  return max_v;
}

void loop()
{
  

  
  
  uint32_t Vrms = get_max();
  Vrms = Vrms * 1100/1023;
  Vrms /= sqrt(2);
  Vrms*=2.017; // calibration factor


  lcd.setCursor(0,2);
  lcd.print("V = ");
  lcd.print(Vrms);
  lcd.print("V  ");

// this part is for RMS current
  const float sensitivity = 185;   // Sensitivity (100mV per Amp for ACS712-20A)
  const int offsetvoltage = 2568;
  
  unsigned int temp=0;
  float max = 0;
  for(int i=0;i<500;i++)
  {
    temp = analogRead(A1); 
    if(temp>max)
    {
      max = temp;
    }
  }
  float ADCvalue = max; 
  double eVoltage = (ADCvalue / 1024.0) * 5000; // Gets you mV
  double Current = ((eVoltage - offsetvoltage) / sensitivity);
  Current = ( Current ) / ( sqrt(2) );


  lcd.print("I = ");
  lcd.print(Current,2);
  lcd.print("A          "); //unit for the current to be measured

  //************************* Measure Power ******************************************
  int Power = (Vrms * Current);
  
  lcd.setCursor(0,3);
  lcd.print("P = ");
  lcd.print(Power);
  lcd.print("W  "); //unit for the current to be measured
  
  
  long milisec = millis(); // calculate time in milliseconds 
  long time=milisec/1000; // convert milliseconds to seconds 
  
  float Energy = (Power*time)/3600; //Watt-sec is again convert to Watt-Hr by dividing 1hr(3600sec) 

  lcd.print("E = ");
  lcd.print(Energy,1);
  lcd.print("Wh    "); 
  
  delay(200);

}

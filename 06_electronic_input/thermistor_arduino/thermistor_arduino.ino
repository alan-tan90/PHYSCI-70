#define RT0 10040   // Ω
#define B 3977 
#define VCC 5    //Supply voltage
#define R 10400  

//Variables
float RT, VR, ln, TX, T0, VRT;

void setup() {
  Serial.begin(9600);
  T0 = 295.928;                 //Temperature T0 from datasheet, conversion from Celsius to kelvin
}

void loop() {
  VRT = analogRead(A5);              //Acquisition analog value of VRT
  VRT = (5.00 / 1023.00) * VRT;      //Conversion to voltage
  VR = VCC - VRT;
  RT = VRT / (VR / R);               //Resistance of RT

  ln = log(RT / RT0);
  TX = (1 / ((ln / B) + (1 / T0))); //Temperature from thermistor

  TX = TX - 273.15;                 //Conversion to Celsius

  Serial.print("Temperature:");
  Serial.print("\t");
  Serial.print(TX);
  Serial.print("C\t\t");
  Serial.print(TX + 273.15);        //Conversion to Kelvin
  Serial.print("K\t\t");
  Serial.print((TX * 1.8) + 32);    //Conversion to Fahrenheit
  Serial.println("F");
  delay(500);

}

# Lowpass filter for Arduino
Analog to digital 1:st order RC lowpass filter template.
Choose cut off frequency and samplingtime.

Code ex.:

#include "LPfilter.h"

float fcut = 10; 

float fsam = 1000;

LPfilter<float> LPf(fcut, fsam);

float Vout = 0;

void setup() {

  float Vin = 2.34;
  
  Vout = LPf.get(Vin);

}

void loop() {}

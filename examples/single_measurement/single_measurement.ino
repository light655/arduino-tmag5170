#include "TMAG5170.hpp"

TMAG5170 myTMAG;

void setup() {
  Serial.begin(115200);
  
  myTMAG.attachSPI(10, 10e6);
    // SPI CS pin = D10, max frequency 10MHz
  myTMAG.init();
  myTMAG.setConversionAverage(CONV_AVG_32x);
    // take the average of 32 measurements
  myTMAG.enableMagneticChannel(true, true, true);
  myTMAG.setMagneticRange(X_RANGE_300mT, Y_RANGE_300mT, Z_RANGE_300mT);
    // enables all magnetic channels with maximum measuring range
}

void loop() {
  float Bx, By, Bz;
  Bx = myTMAG.readX();
  By = myTMAG.readY();
  Bz = myTMAG.readZ(true);  // set start_conversion_spi = true to start conversion after this SPI command

  Serial.print("Bx: ");     // print the data over serial
  Serial.print(Bx);
  Serial.print(", By: ");
  Serial.print(By);
  Serial.print(", Bz: ");
  Serial.println(Bz);
  delay(1000);
}


# arduino-tmag5170
A TMAG5170 Hall-effect sensor library for Arduino.

## Intro
TMAG5170 is a high-precision 3D Hall-effect sensor IC designed by Texas Instruments. It measures the magnetic field in all 3 axes, with a sampling rate of up to 10 kSPS. Communication with TMAG5170 is based on SPI, with maximum frequency of 10 MHz and cyclic redundancy check. There are two versions, A1 and A2, of TMAG5170 with different measuring ranges.

If you are using Raspberry Pi Pico, please consider using the [Pico SDK version of this library](https://github.com/light655/pico-tmag5170).

## Usage

- Download this repository and extract it into your *Arduino/libraries* folder.
- Remember to include the header file in your code.
```C
#include "TMAG5170.h"
```

## Notes
- This library is only tested on the Arduino Uno and uses the default SPI pins.

## Examples

### Single measurement

This example sends some commands to read the magnetic field at an interval of 1 second. Please wire the TMAG5170 as follows:

| TMAG5170 | Arduino Uno |
| -- | -- |
| SCK (1) | D13 |
| SDI (2) | D11 |
| SDO (3) | D12 |
| CS (4) | D10 |
| VCC (5) | 5V |
| GND (6) | GND |
| TEST (7) | GND |

First, a TMAG5170 object is created.
```C
TMAG5170 myTMAG;
```
In the setup() function, we can set some parameters on the TMAG5170.
```C
void setup() {
  Serial.begin(115200);
  
  myTMAG.attachSPI(10, 10e6);
    // SPI CS pin = D10, max frequency 10MHz
  myTMAG.init();
  myTMAG.setConversionAverage(CONV_AVG_32x);
    // take the average of 32 measurements
  myTMAG.enableMagneticChannel(true, true, true);
    // Enables all magnetic channels. The 3 true/false parameters refers to x, y, z axes, respectively.
  myTMAG.setMagneticRange(X_RANGE_300mT, Y_RANGE_300mT, Z_RANGE_300mT);
    // Sets all magnetic channels to maximum range.
}
```
In the loop() function, call readX/Y/Z() to read the magnetic field on the respective axis. Note that by setting the parameter true will initiate the next measure of magnetic field.
```C
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
```

## References
- [TMAG5170 datasheet](https://www.ti.com/lit/ds/symlink/tmag5170.pdf?ts=1724587283732&ref_url=https%253A%252F%252Fwww.ti.com%252Fproduct%252FTMAG5170)
- [My blog on more details about the TMAG5170](https://hackmd.io/8zu9jVyARfWYGYuD4Jl_aQ)
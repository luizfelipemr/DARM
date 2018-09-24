///////////  EQUIPE ANTARES  ////////////


 
#include "HX711.h"
#include <SD.h>
#include <SPI.h>

// HX711.DOUT	- pin #A1
// HX711.PD_SCK	- pin #A0

int count=0;

HX711 scale(A1, A0);		// parameter "gain" is ommited; the default value 128 is used by the library

void setup() {
  Serial.begin(9600);

  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  
  Serial.println("HX711 Demo");

  Serial.print("read: \t\t");

  Serial.print("read average: \t\t");

  Serial.print("get value: \t\t");

  Serial.print("get units: \t\t");

  scale.set_scale(2280.f);                      // this value is obtained by calibrating the scale with known weights; see the README for details
  scale.tare();				        // reset the scale to 0

  Serial.print("read: \t\t");

  Serial.print("read average: \t\t");

  Serial.print("get value: \t\t");

  Serial.print("get units: \t\t");

  Serial.println("Readings:");
}

void loop() {

  // make a string for assembling the data to log:
  String dataString = "";
  dataString += String(scale.get_units);
  dataString += ",";

  count++;
  
  Serial.print("one reading:\t");
  Serial.print(scale.get_units(), 1);
  Serial.print("\t| average:\t");
  Serial.println(scale.get_units(10), 1);

  scale.power_down();			        // put the ADC in sleep mode
  delay(10);
  scale.power_up();

  if(count==1000){
    // open the file. note that only one file can be open at a time,
    // so you have to close this one before opening another.
    File dataFile = SD.open("datalog.txt", FILE_WRITE);
  
    // if the file is available, write to it:
    if (dataFile) {
      dataFile.println(dataString);
      dataFile.close();
      // print to the serial port too:
      Serial.println(dataString);
    }
    // if the file isn't open, pop up an error:
    else {
      Serial.println("error opening datalog.txt");
    }
  }
}

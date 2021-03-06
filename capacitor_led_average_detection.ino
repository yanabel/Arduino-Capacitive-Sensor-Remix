#include <CapacitiveSensor.h>

/*
 * CapitiveSense Library Demo Sketch
 * Paul Badger 2008
 * Uses a high value resistor e.g. 10M between send pin and receive pin
 * Resistor effects sensitivity, experiment with values, 50K - 50M. Larger resistor values yield larger sensor values.
 * Receive pin is the sensor pin - try different amounts of foil/metal on this pin
 */
const int numReadings = 10;

int readings[numReadings];
int readIndex = 0;
int total = 0;
int average = 0;
int inputPin = A1;

int led = 9;
int brightness = 0;
int fadeAmount = 5;
int analogPin = A1;
int val = 0;


CapacitiveSensor   cs_4_2 = CapacitiveSensor(4,2);        // 10M resistor between pins 4 & 2, pin 2 is sensor pin, add a wire and or foil if desired

void setup()                    
{
   cs_4_2.set_CS_AutocaL_Millis(0xFFFFFFFF);     // turn off autocalibrate on channel 1 - just as an example
   pinMode(led, OUTPUT);
   Serial.begin(9600);
   {
    for (int thisReading = 0; thisReading < numReadings; thisReading++) {
      readings[thisReading] = 0;
    }
   }
}

void loop()                    
{

    long start = millis();
    long total1 =  cs_4_2.capacitiveSensor(30);

    Serial.print(millis() - start);        // check on performance in milliseconds

    Serial.println(total1);                  // print sensor output 1 - this is also the value you can use to use this in other projects

    delay(50);                             // arbitrary delay to limit data to serial port 

    
      int sensorValue = analogRead(A1);
      if(sensorValue < 400)

    {
      total = total - readings[readIndex];
      readings[readIndex] = analogRead(inputPin);
      total = total + readings [readIndex];
      readIndex = readIndex + 1;

      if (readIndex >= numReadings) {
        readIndex = 0;
      }

      average = total / numReadings;
      Serial.println(average);
      delay(10);
    }

    {
      analogWrite(led, brightness);
      val = analogRead(analogPin);
      brightness = val-255;
      delay(10);
     }
      
    }
 


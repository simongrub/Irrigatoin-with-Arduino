#include "Bounce2.h"

const int outputPin = 5;
const int button = 4;
int Schwellenwert = 800;
int Feuchtigkeit;
int arraySize = 10;
int elements = 0;
unsigned long startTime = 0;
unsigned long timeSeconds = 0;
unsigned long *timestamps;
unsigned long elapsedTime;

Bounce buttonPush = Bounce();


void setup() {
	Serial.begin(9600);
	pinMode(outputPin, OUTPUT);
  	timestamps = (unsigned long *)malloc(arraySize * sizeof(unsigned long));
	
  	buttonPush.attach(button,INPUT);
  	buttonPush.interval(20);
}

void loop() {
  
  
  
  Feuchtigkeit = analogRead(A0);
  Serial.println(Feuchtigkeit);
  
  if (Feuchtigkeit < Schwellenwert && startTime == 0) {
      startTime = millis();
 	  digitalWrite(outputPin, HIGH);
  
  }
	else if(Feuchtigkeit >= Schwellenwert && startTime!=0){
      elapsedTime = millis() - startTime;
      startTime = 0;
  	  digitalWrite(outputPin, LOW);
            	
	}
  if(elements >= arraySize){
    arraySize *= 2;
    timestamps = (unsigned long *)realloc(timestamps, arraySize * sizeof(unsigned long));
  }
  timestamps[elements++] = elapsedTime / 1000;
  if(buttonPush.update()){
    if(buttonPush.fell()){
      for(int i = 0; i < arraySize; i++){
        Serial.println(timestamps[i]);
      }
    }
  }
}
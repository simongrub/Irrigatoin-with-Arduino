const int outputPin = 5;
const int Taster = 4;
int Schwellenwert = 800;
int Feuchtigkeit;
unsigned long startTime = 0;
unsigned long timeSeconds = 0;
unsigned long *timestamps;
unsigned long elapsedTime;
int arraySize = 10;
int elements = 0;


void setup() {
	Serial.begin(9600);
	pinMode(outputPin, OUTPUT);
  	pinMode(Taster,INPUT);
  	timestamps = (unsigned long *)malloc(arraySize * sizeof(unsigned long));

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
  if(digitalRead(Taster) != 0){
    for(int i = 0; i < arraySize; i++){
      Serial.println(timestamps[i]);
    }
  }
}
const int outpin = 8;
const int photoresistor = A1;
int reading;
int threshhold = 425;

  
void setup(){
	pinMode(outpin, OUTPUT);
  	pinMode(photoresistor, INPUT);
  	Serial.begin(9600);
}

void loop(){
	reading = analogRead(photoresistor);
  	Serial.println(reading);
    
    if(reading<threshhold){
    	digitalWrite(outpin, HIGH);
    }
  
  	else{
  		digitalWrite(outpin, LOW);
  	}
}

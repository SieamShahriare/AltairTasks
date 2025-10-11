const int signalpin = 8;
const int led = 2;


void setup()
{
  pinMode(signalpin, INPUT);
  pinMode(led, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  int signal = digitalRead(signalpin);
  Serial.println(signal);
  
  if(signal == HIGH){
  	digitalWrite(led, HIGH);
  }
  
  else{
  	digitalWrite(led, LOW);
  }
}
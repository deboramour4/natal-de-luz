#include <Ultrasonic.h>
Ultrasonic ultrasound(3,2);

// pins
#define light1 5
#define light2 6
#define light3 7
#define light4 8
int allLights[] = {light1, light2, light3, light4};

// sensor of proximity
#define sensor 2
#define pino_trigger 3
#define pino_echo 2

// 0 idle animation
// 1 arrow animation
// 2 all turned off
// 3 all turned on
int actualAnimation = 2;

// distance recieved from sensor
int distance;

// speed of animation
int speed = 600;

void setup() {
  // initialize serial communication at 9600 bits per second
  Serial.begin(9600);
  long distance;

  // turn pin A0 into 5V 
  pinMode(A0, OUTPUT);
  digitalWrite(A0, HIGH);
  
  // make the light's pin an output
  pinMode(light1, OUTPUT);
  pinMode(light2, OUTPUT);
  pinMode(light3, OUTPUT);
  pinMode(light4, OUTPUT);
  
  // make the sensor's pin an input
  pinMode(sensor, INPUT);
}

void loop() {
  // read the sensors and discover if someone's there
  int sensorOutput  = digitalRead(sensor);
  
  // ultrasound.Ranging(CM) returns the distance in
  // centimeters(CM) or inchs(INC)
  distance = ultrasound.Ranging(CM);

  // print the value of distance (debug)
  Serial.print(distance); 
  Serial.println("cm");

  // changes the actualAnimation to "arrow" if someone's 4 meters away or closer
  if(distance<400){
   actualAnimation = 1;
  } else{
   actualAnimation = 2;
  }

 // switch the state machine animations
  showAnimation(actualAnimation);
}

void showAnimation(int state) {
  switch (state) {
    case 0: // idle animation
      
    break;
    
    case 1: //arrow animation
      for (int i = 0; i < 4; i++){
        digitalWrite(allLights[1], LOW);
        digitalWrite(allLights[2], LOW);
        digitalWrite(allLights[3], LOW);
        digitalWrite(allLights[0], LOW);
        digitalWrite(allLights[i], HIGH);
        delay(distance*3);
      }
    break;
    
    case 2: // turn all off
      digitalWrite(allLights[1], HIGH);
      digitalWrite(allLights[2], HIGH);
      digitalWrite(allLights[3], HIGH);
      digitalWrite(allLights[0], HIGH);
    break;

    case 3: // turn all on
      digitalWrite(allLights[1], LOW);
      digitalWrite(allLights[2], LOW);
      digitalWrite(allLights[3], LOW);
      digitalWrite(allLights[0], LOW);
    break;
  }
}

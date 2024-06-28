// Ultrasonic sensor libraries
// #include <NewPing.h>
#include "Ultrasonic.h"
#include <Servo.h>

int type = 1; // Type of circuit 
// 1 - 4 junction with 4 ultrasonic sensors
// 0 - 3 junction with 3 ultrasonic sensors


const int trigPin1 = 12;  // Trigger pin for sensor 1
const int echoPin1 = 14;  // Echo pin for sensor 1

const int trigPin2 = 33;  // Trigger pin for sensor 2
const int echoPin2 = 32;  // Echo pin for sensor 2

const int trigPin3 = 5;  // Trigger pin for sensor 3
const int echoPin3 = 18;  // Echo pin for sensor 3

const int trigPin4 = 4;  // Trigger pin for sensor 4
const int echoPin4 = 2;  // Echo pin for sensor 4

const int led_red_1 = 22;
const int led_red_2 = 23;
const int led_red_3 = 35;
const int led_red_4 = 15;

const int led_green_1 = 21;
const int led_green_2 = 27;
const int led_green_3 = 34;
const int led_green_4 = 19;

const int servoPin = 13;  // Pin connected to the servo motor

Servo servo;  // Create a servo object

typedef enum tl_status {
  RED = 0,
  GREEN
} tl_status_t;




Ultrasonic ultrasonic1(trigPin1,echoPin1);
Ultrasonic ultrasonic2(trigPin2,echoPin2);
Ultrasonic ultrasonic3(trigPin3,echoPin3);
Ultrasonic ultrasonic4(trigPin4,echoPin4);

int count_arr[4];  //count the number of cars per road
tl_status_t signal[4];  // 1 for green and 0 for red
int Timer[4];   // 0 for red and time remaining in millisecs for the green light
int light_index;
int multiplier;
int delay_per_read;
int threshold_time;
int flag_max_hit;
int servoPosition = 0;  // Initial position of the servo motor

void setup() {
  Serial.begin(9600);

  // Initialise pinmodes for all LEDS
  pinMode(led_red_1,OUTPUT);
  pinMode(led_red_2,OUTPUT);
  pinMode(led_red_3,OUTPUT);
  pinMode(led_red_4,OUTPUT);

  pinMode(led_green_1,OUTPUT);
  pinMode(led_green_2,OUTPUT);
  pinMode(led_green_3,OUTPUT);
  pinMode(led_green_4,OUTPUT);

  
  light_index = 0;
  
  for(int i = 1; i < 4; i++) Timer[i] = 0;
  for(int i = 1; i < 4; i++) signal[i] = RED; 
  for(int i = 0; i < 4; i++) count_arr[i] = 0;
  
  Timer[light_index] = 5000;
  signal[light_index] = GREEN;
  multiplier = 1250;
  delay_per_read = 250;
  threshold_time = 30000;
  flag_max_hit = 0;
  type = 1;

  servo.attach(servoPin);  // Attach the servo to the specified pin
  servo.write(servoPosition);  // Set the initial position of the servo motor
}

void loop() {

  Serial.printf("LED red  : %d %d %d %d\n", digitalRead(led_red_1), digitalRead(led_red_2), digitalRead(led_red_3), digitalRead(led_red_4));
  Serial.printf("LED green: %d %d %d %d\n", digitalRead(led_green_1), digitalRead(led_green_2), digitalRead(led_green_3), digitalRead(led_green_4));

  int max_cars=threshold_time/multiplier;
  
  signal[light_index] = GREEN;

  switch (light_index) {
  case 0: {
    digitalWrite(led_red_1,LOW);
    digitalWrite(led_red_2,HIGH);
    digitalWrite(led_red_3,HIGH);
    digitalWrite(led_red_4,HIGH);
    
    digitalWrite(led_green_1,HIGH);
    digitalWrite(led_green_2,LOW);
    digitalWrite(led_green_3,LOW);
    digitalWrite(led_green_4,LOW);
    break;
  }
  case 1: {
    digitalWrite(led_red_1,HIGH);
    digitalWrite(led_red_2,LOW);
    digitalWrite(led_red_3,HIGH);
    digitalWrite(led_red_4,HIGH);
    
    digitalWrite(led_green_1,LOW);
    digitalWrite(led_green_2,HIGH);
    digitalWrite(led_green_3,LOW);
    digitalWrite(led_green_4,LOW);
    break;
  }
  case 2: {
    digitalWrite(led_red_1,HIGH);
    digitalWrite(led_red_2,HIGH);
    digitalWrite(led_red_3,LOW);
    digitalWrite(led_red_4,HIGH);
    
    digitalWrite(led_green_1,LOW);
    digitalWrite(led_green_2,LOW);
    digitalWrite(led_green_3,HIGH);
    digitalWrite(led_green_4,LOW);
    break;
  }
  case 3: {
    if (type == 3) break;
    digitalWrite(led_red_1,HIGH);
    digitalWrite(led_red_2,HIGH);
    digitalWrite(led_red_3,HIGH);
    digitalWrite(led_red_4,LOW);
    
    digitalWrite(led_green_1,LOW);
    digitalWrite(led_green_2,LOW);
    digitalWrite(led_green_3,LOW);
    digitalWrite(led_green_4,HIGH);
    break;
  }
  default: {
    Serial.println("Warning: Invalid junction number");
  }
  }

  // Pedestrian Crossing
  if (light_index == 0 && signal[light_index] == RED) {
    // rotate the servo motor upright to open pedestrian gate
    servoPosition = 90;
  } else {
    // Reset the servo motor position
    servoPosition = 0;
  }
  servo.write(servoPosition);  // Rotate the servo motor to the specified position
     

  /////// LED green trigger
  // If the junction is empty 
  if (flag_max_hit < max_cars &&
      count_arr[light_index] > 0 &&
      count_arr[light_index] <= max_cars) { 
    Timer[light_index] += (multiplier * count_arr[light_index]);
    flag_max_hit+=count_arr[light_index];
    count_arr[light_index] = 0;
  }
  // If junction still has cars
  else if(flag_max_hit < max_cars && count_arr[light_index] > max_cars ){
    Timer[light_index] += multiplier*max_cars;
    flag_max_hit+=count_arr[light_index];
    count_arr[light_index] -= max_cars;
  }

  Timer[light_index] -= 1;

  count_arr[0] += read_from_pin(ultrasonic1);  
  count_arr[1] += read_from_pin(ultrasonic2);
  count_arr[2] += read_from_pin(ultrasonic3);
  if(type == 1)
    count_arr[3] += read_from_pin(ultrasonic4);

  // DEBUG PRINTS
  Serial.println("Count arr:-");
  Serial.println(count_arr[0]);
  Serial.println(count_arr[1]);
  Serial.println(count_arr[2]);
  if(type == 1) Serial.println(count_arr[3]);
  Serial.println();

  Serial.println("Timer:-");
  Serial.println(Timer[0]);
  Serial.println(Timer[1]);
  Serial.println(Timer[2]);
  if(type == 1)  Serial.println(Timer[3]);
  Serial.println();
  // END DEBUG PRINTS

  if(Timer[light_index] <= 0) {
    // reset all signal variables
    signal[light_index] = RED;
    Timer[light_index] = 0;
    flag_max_hit = 0;
    
    switch (light_index) {
    case 0: {
      digitalWrite(led_green_1, LOW);
      digitalWrite(led_red_1, HIGH);
      break;
    }
    case 1: {
      digitalWrite(led_green_2, LOW);
      digitalWrite(led_red_2, HIGH);
      break;
    }
    case 2: {
      digitalWrite(led_green_3, LOW);
      digitalWrite(led_red_3, HIGH);
      break;
    }
    case 3: {
      digitalWrite(led_green_4, LOW);
      digitalWrite(led_red_4, HIGH);
      break;
    }
    default: {
      Serial.println("Warning: Invalid junction case");
    }
    }
    if(type==1)
      light_index = (light_index + 1) % 4;
    else
      light_index = (light_index + 1) % 3;
    
    Serial.println("Light switching");
    Serial.println(light_index);
    
    if (Base_condition(count_arr)) 
      { 
	Serial.println("Base condition is hit");
	Timer[light_index] = 5000;
      }
    signal[light_index] = GREEN;
  }

  if(type == 1)
    Timer[light_index] -= (delay_per_read*4);
  else
    Timer[light_index] -= (delay_per_read*3);
   
}

int read_from_pin (Ultrasonic sensor) {
   float distance = sensor.read();
  // Serial.println("read1");
  // Serial.println(distance);
  int val= (distance<=10);
  delay(delay_per_read);
  if(val == 1) 
  return 1;
  else 
  return 0;
}

int Base_condition(int* count_arr){
  int check = 1;
  if(type==1)
    {
      for(int i =0;i<4;i++) 
	{
	  if(count_arr[i] != 0)
	    {
              check = 0;
              break;
	    }
	} 
    }
  else 
    {
      for(int i =0;i<3;i++) 
	{
	  if(count_arr[i] != 0)
	    {
              check = 0;
              break;
	    }
	}
    }
  return check;
}
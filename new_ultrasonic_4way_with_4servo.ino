// Ultrasonic sensor libraries
// #include <NewPing.h>
#include "Ultrasonic.h"
#include <Servo.h>

int type = 1; // Type of circuit 
// 1 - 4 junction with 4 ultrasonic sensors
// 0 - 3 junction with 3 ultrasonic sensors


const int trigPin1 = 23;  // Trigger pin for sensor 1
const int echoPin1 = 39;  // Echo pin for sensor 1

const int trigPin2 = 26;  // Trigger pin for sensor 2
const int echoPin2 = 34;  // Echo pin for sensor 2

const int trigPin3 = 14;  // Trigger pin for sensor 3
const int echoPin3 = 35;  // Echo pin for sensor 3

const int trigPin4 = 33;  // Trigger pin for sensor 4
const int echoPin4 = 36;  // Echo pin for sensor 4

const int led_red_1 = 5;
const int led_red_2 = 17;
const int led_red_3 = 16;
const int led_red_4 = 15;

const int led_green_1 = 22;
const int led_green_2 = 21;
const int led_green_3 = 19;
const int led_green_4 = 18;

const int servoPin1 = 32;  // Pin connected to the servo motor
const int servoPin2 = 25;  // Pin connected to the servo motor
const int servoPin3 = 27;  // Pin connected to the servo motor
const int servoPin4 = 13;  // Pin connected to the servo motor


Servo servo1;  // Create a servo object
Servo servo2;  // Create a servo object
Servo servo3;  // Create a servo object
Servo servo4;  // Create a servo object

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

int servoPosition1 = 0;  // Initial position of the servo motor
int servoPosition2 = 0;  // Initial position of the servo motor
int servoPosition3 = 0;  // Initial position of the servo motor
int servoPosition4 = 0;  // Initial position of the servo motor

void setup() {
  Serial.begin(9600);
  WiFi.begin(MAIN_SSID, MAIN_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print("#");
  }
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

  servo1.attach(servoPin1);  // Attach the servo to the specified pin
  servo1.write(servoPosition1);  // Set the initial position of the servo motor
  servo2.attach(servoPin2);  // Attach the servo to the specified pin
  servo2.write(servoPosition2);  // Set the initial position of the servo motor
  servo3.attach(servoPin3);  // Attach the servo to the specified pin
  servo3.write(servoPosition3);  // Set the initial position of the servo motor
  servo4.attach(servoPin4);  // Attach the servo to the specified pin
  servo4.write(servoPosition4);  // Set the initial position of the servo motor
}

void loop() {

  int a= digitalRead(led_green_1);
  int b= digitalRead(led_green_2);
  int c= digitalRead(led_green_3);
  int d= digitalRead(led_green_4);
  int arr2[]= {a, b, c, d};

  Serial.printf("LED red  : %d %d %d %d\n", digitalRead(led_red_1), digitalRead(led_red_2), digitalRead(led_red_3), digitalRead(led_red_4));
  Serial.printf("LED green: %d %d %d %d\n", a, b, c, d);

  int max_cars=threshold_time/multiplier;
  
  signal[light_index] = GREEN;

  switch (light_index) {
  case 0: {
    digitalWrite(led_red_1,LOW);
    digitalWrite(led_red_2,HIGH);
    digitalWrite(led_red_3,HIGH);
    digitalWrite(led_red_4,HIGH);
    servo1.write(0);  // Rotate the servo motor to the specified position
    servo2.write(90);  // Rotate the servo motor to the specified position
    servo3.write(90);  // Rotate the servo motor to the specified position
    servo4.write(90);  // Rotate the servo motor to the specified position
    
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
    servo1.write(90);  // Rotate the servo motor to the specified position
    servo2.write(0);  // Rotate the servo motor to the specified position
    servo3.write(90);  // Rotate the servo motor to the specified position
    servo4.write(90);  // Rotate the servo motor to the specified position
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
    servo1.write(90);  // Rotate the servo motor to the specified position
    servo2.write(90);  // Rotate the servo motor to the specified position
    servo3.write(0);  // Rotate the servo motor to the specified position
    servo4.write(90);  // Rotate the servo motor to the specified position
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
    servo1.write(90);  // Rotate the servo motor to the specified position
    servo2.write(90);  // Rotate the servo motor to the specified position
    servo3.write(90);  // Rotate the servo motor to the specified position
    servo4.write(0);  // Rotate the servo motor to the specified position
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

  write_to_om2m(type, count_arr, arr2, "Junction-1/Data");

  if(Timer[light_index] <= 0) {
    // reset all signal variables
    signal[light_index] = RED;
    Timer[light_index] = 0;
    flag_max_hit = 0;
    
    switch (light_index) {
    case 0: {
      digitalWrite(led_green_1, LOW);
      digitalWrite(led_red_1, HIGH);
      servo1.write(90);  // Rotate the servo motor to the specified position
      break;
    }
    case 1: {
      digitalWrite(led_green_2, LOW);
      digitalWrite(led_red_2, HIGH);
      servo2.write(90);  // Rotate the servo motor to the specified position

      break;
    }
    case 2: {
      digitalWrite(led_green_3, LOW);
      digitalWrite(led_red_3, HIGH);
      servo3.write(90);  // Rotate the servo motor to the specified position

      break;
    }
    case 3: {
      digitalWrite(led_green_4, LOW);
      digitalWrite(led_red_4, HIGH);
      servo4.write(90);  // Rotate the servo motor to the specified position

      break;
    }
    default: {
      Serial.println("Warning: Invalid junction case");
    }
    }
      // Pedestrian Crossing
  
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

// Ultrasonic sensor libraries
// #include <NewPing.h>
#include "Ultrasonic.h"

int type; // Type of circuit 
// 1 - 4 junction with 4 ultrasonic sensors
// 0 - 3 junction with 3 ultrasonic sensors



// Constants (won't change)
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
// const unsigned int maxDistance = 200;  // Maximum distance to measure (in centimeters)

// Object instances for ultrasonic sensors
// NewPing sonar1(trigPin1, echoPin1, maxDistance);
// NewPing sonar2(trigPin2, echoPin2, maxDistance);
// NewPing sonar3(trigPin3, echoPin3, maxDistance);
// NewPing sonar4(trigPin4, echoPin4, maxDistance);

// Variables (will change)
// unsigned long currentMillis = 0;   // Current time in milliseconds
// unsigned long previousMillis = 0;  // Previous time for reading sensors

// int is_1_red= 0;
// int is_2_red= 0;
// int is_3_red= 0;
// int is_4_red= 0;

// int red_count_1= 0;
// int red_count_2= 0;
// int red_count_3= 0;
// int red_count_4= 0;

// int green_count_1= 0;
// int green_count_2= 0;
// int green_count_3= 0;
// int green_count_4= 0;

Ultrasonic ultrasonic1(trigPin1,echoPin1);
Ultrasonic ultrasonic2(trigPin2,echoPin2);
Ultrasonic ultrasonic3(trigPin3,echoPin3);
Ultrasonic ultrasonic4(trigPin4,echoPin4);



int count_arr[4];  //count the number of cars per road
int signal[4];  // 1 for green and 0 for red
int Timer[4];   // 0 for red and time remaining in millisecs for the green light
int light_index;
int multiplier;
int delay_per_read;
int threshold_time;
int flag_max_hit;


void setup() {
  Serial.begin(9600);

  pinMode(led_red_1,OUTPUT);
  pinMode(led_red_2,OUTPUT);
  pinMode(led_red_3,OUTPUT);
  pinMode(led_red_4,OUTPUT);

  pinMode(led_green_1,OUTPUT);
  pinMode(led_green_2,OUTPUT);
  pinMode(led_green_3,OUTPUT);
  pinMode(led_green_4,OUTPUT);

  
  light_index = 0;
  for(int i = 1;i<4;i++)
  {Timer[i] = 0;}
  for(int i = 1;i<4;i++) 
  {signal[i] = 0;}
  for(int i =0;i<4;i++) 
  {count_arr[i] = 0;}
  Timer[light_index] = 5000;
  signal[light_index] = 1;
  multiplier = 1250;
  delay_per_read=250;
  threshold_time=30000;
  flag_max_hit=0;
  type=1;

}

void loop() {

int max_cars=threshold_time/multiplier;  
  // currentMillis = millis();
  // read1();
  // read2();
  // read3();
  // read4();
  // red_count_1+= green_count_1;
  // green_count_1=0;

  // red_count_2+= green_count_2;
  // green_count_2=0;
  
  // red_count_3+= green_count_3;
  // green_count_3=0;

  // red_count_4+= green_count_4;
  // green_count_4=0;



   signal[light_index] = 1;


   if(light_index==0)
   {
   digitalWrite(led_red_1,0);
   digitalWrite(led_red_2,1);
   digitalWrite(led_red_3,1);
   digitalWrite(led_red_4,1);

   digitalWrite(led_green_1,HIGH);
   digitalWrite(led_green_2,LOW);
   digitalWrite(led_green_3,LOW);
   digitalWrite(led_green_4,LOW);

   }
   else if(light_index==1)
   {
   digitalWrite(led_red_2,LOW);
   digitalWrite(led_red_1,HIGH);
   digitalWrite(led_red_3,HIGH);
   digitalWrite(led_red_4,HIGH);

   digitalWrite(led_green_2,HIGH);
   digitalWrite(led_green_1,LOW);
   digitalWrite(led_green_3,LOW);
   digitalWrite(led_green_4,LOW);
   }
   else if(light_index==2)
   {
   digitalWrite(led_red_3,LOW);
   digitalWrite(led_red_2,HIGH);
   digitalWrite(led_red_1,HIGH);
   digitalWrite(led_red_4,HIGH);

   digitalWrite(led_green_3,HIGH);
   digitalWrite(led_green_2,LOW);
   digitalWrite(led_green_1,LOW);
   digitalWrite(led_green_4,LOW);
   }
   else if(type==1 && light_index==3)
   {
   digitalWrite(led_red_4,LOW);
   digitalWrite(led_red_2,HIGH);
   digitalWrite(led_red_3,HIGH);
   digitalWrite(led_red_1,HIGH);

   digitalWrite(led_green_4,HIGH);
   digitalWrite(led_green_2,LOW);
   digitalWrite(led_green_3,LOW);
   digitalWrite(led_green_1,LOW);
   }
   

  // LED green triger
  if(flag_max_hit<max_cars && count_arr[light_index] > 0 && count_arr[light_index] <= max_cars){ 
      Timer[light_index] += (multiplier * count_arr[light_index]);
      flag_max_hit+=count_arr[light_index];
      count_arr[light_index] = 0;
      }
  else if(flag_max_hit<max_cars && count_arr[light_index] > max_cars ){
    Timer[light_index] += multiplier*max_cars;
    flag_max_hit+=count_arr[light_index];
    count_arr[light_index] -= max_cars;
  }

  Timer[light_index] -= 1;

  count_arr[0] +=read1();
  
  count_arr[1] +=read2();

  count_arr[2] +=read3();

  if(type==1)
  count_arr[3] +=read4();

  Serial.println("Count arr:-");

  Serial.println(count_arr[0]);
  Serial.println(count_arr[1]);
  Serial.println(count_arr[2]);
  if(type==1)
  Serial.println(count_arr[3]);
  Serial.println();

  Serial.println("Timer:-");

  Serial.println(Timer[0]);
  Serial.println(Timer[1]);
  Serial.println(Timer[2]);
  if(type==1)
  Serial.println(Timer[3]);
  Serial.println();

  if(Timer[light_index] == 0 || Timer[light_index] < 0)
  {
    signal[light_index] = 0;
    //LED Red triger 
    Timer[light_index]=0;
    flag_max_hit=0;
    if(light_index==0)
    {
    digitalWrite(led_green_1,LOW);
    digitalWrite(led_red_1,HIGH);
    }
    else if(light_index==1)
    {
    digitalWrite(led_green_2,LOW);
    digitalWrite(led_red_2,HIGH);
    }
    else if(light_index==2)
    {
    digitalWrite(led_green_3,LOW);
    digitalWrite(led_red_3,HIGH);
    }
    else if(light_index==3)
    {
    digitalWrite(led_green_4,LOW);
    digitalWrite(led_red_4,HIGH);
    }
  if(type==1)
  light_index = (light_index+1)%4;
  else
  light_index = (light_index+1)%3;
   
  Serial.println("Light switching");
  Serial.println(light_index);
    if(Base_condition(count_arr)) 
    { 
      Serial.println("base condition hits");
      Timer[light_index] = 5000;
    }
  }
  if(type==1)
  Timer[light_index]=Timer[light_index]-(delay_per_read*4);
  else
  Timer[light_index]=Timer[light_index]-(delay_per_read*3);
   
}







int read1(){
  float distance = ultrasonic1.read();
  // Serial.println("read1");
  // Serial.println(distance);
  int val= (distance<=10);
  delay(delay_per_read);
  if(val == 1) 
  return 1;
  else 
  return 0;
}
int read2(){
  float distance = ultrasonic2.read();
  // Serial.println("read2");
  // Serial.println(distance);
  delay(delay_per_read);
  int val= (distance<=10);
  if(val == 1) return 1;
  else return 0;
}
int read3(){
  float distance = ultrasonic3.read();
  // Serial.println("read3");
  // Serial.println(distance);
  delay(delay_per_read);
  int val= (distance<=10);
  if(val == 1) return 1;
  else return 0;
}
int read4(){
  float distance = ultrasonic4.read();
  // Serial.println("read4");
  // Serial.println(distance);
  delay(delay_per_read);
  int val= (distance<=10);
  if(val == 1) return 1;
  else return 0;
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





 





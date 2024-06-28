#ifndef _HEADER_
#define _HEADER_

#include <HTTPClient.h>
#include <WiFi.h>
#include <time.h>

#define MAIN_SSID "hotspot"
#define MAIN_PASS "hotspots"
#define CSE_IP "192.168.228.183"

#define CSE_PORT 5089
#define OM2M_ORGIN "admin:admin"
#define OM2M_MN "/~/in-cse/in-name/"
#define OM2M_AE "Database"
#define INTERVAL 15000L

long randNumber;
long int prev_millis = 0;

HTTPClient http;
void write_to_om2m(int trigger, int arr1[], int arr2[], char* OM2M_DATA_CONT) ;

void write_to_om2m(int trigger, int arr1[], int arr2[], char* OM2M_DATA_CONT) {
  int Car_1 = arr1[0];
  int Car_2 = arr1[1];
  int Car_3 = arr1[2];
  int Car_4 = arr1[3];
  int Signal_1 = arr2[0];
  int Signal_2 = arr2[1];
  int Signal_3 = arr2[2];
  int Signal_4 = arr2[3];
  
  if (millis() - prev_millis >= INTERVAL) {
    String data;
    String server = "http://" + String() + CSE_IP + ":" + String() + CSE_PORT + String() + OM2M_MN;

    http.begin(server + String() + OM2M_AE + "/" + OM2M_DATA_CONT + "/");

    http.addHeader("X-M2M-Origin", OM2M_ORGIN);
    http.addHeader("Content-Type", "application/json;ty=4");
    http.addHeader("Content-Length", "100");

    if(trigger==0){
      data = "[" + String(Car_1) + ", " + String(Car_2) + ", " + String(Car_3) + ", "  + String(Signal_1) + ", "+ String(Signal_2) + ", " + String(Signal_3) +   + "]"; 
    }else{
      data = "[" + String(Car_1) + ", " + String(Car_2) + ", " + String(Car_3) + ", " + String(Car_4) + ", "  + String(Signal_1) + ", "+ String(Signal_2) + ", "+ String(Signal_3) + ", " + String(Signal_4) +   + "]"; 
    }
    
    String req_data = String() + "{\"m2m:cin\": {"
      +
      "\"con\": \"" + data + "\","

      +
      "\"lbl\": \"" + "V1.0.0" + "\","

      //+ "\"rn\": \"" + "cin_"+String(i++) + "\","

      +
      "\"cnf\": \"text\""

      +
      "}}";
    int code = http.POST(req_data);
    http.end();
    Serial.println(code);
    prev_millis = millis();
  }
}

#endif
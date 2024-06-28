#include <HTTPClient.h>
#include <WiFi.h>
#include <time.h>

#define MAIN_SSID "Ritam"
#define MAIN_PASS "password"
#define CSE_IP "192.168.184.183"

#define CSE_PORT 5089
#define OM2M_ORGIN "admin:admin"
#define OM2M_MN "/~/in-cse/in-name/"
#define OM2M_AE "Database"
#define OM2M_DATA_CONT "Junction-1/Data"
#define INTERVAL 15000L

long randNumber;
long int prev_millis = 0;

HTTPClient http;

//[Car_1, Car_2, Car_3, Car_4, Signal_1, Signal_2, Signal_3, Signal_4]
void setup() {
  Serial.begin(115200);
  delay(1000);

  WiFi.begin(MAIN_SSID, MAIN_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print("#");
  }
}

void loop() {
  int Car_1 = random(0,100);
  int Car_2 = random(0,100);
  int Car_3 = random(0,100);
  int Car_4 = random(0,100);
  int Signal_1 = random(0,1);
  int Signal_2 = random(0,1);
  int Signal_3 = random(0,1);
  int Signal_4 = random(0,1);
  
  if (millis() - prev_millis >= INTERVAL) {
    String data;
    String server = "http://" + String() + CSE_IP + ":" + String() + CSE_PORT + String() + OM2M_MN;

    http.begin(server + String() + OM2M_AE + "/" + OM2M_DATA_CONT + "/");

    http.addHeader("X-M2M-Origin", OM2M_ORGIN);
    http.addHeader("Content-Type", "application/json;ty=4");
    http.addHeader("Content-Length", "100");

    data = "[" + String(Car_1) + ", " + String(Car_2) + ", " + String(Car_3) + ", " + String(Car_4) + ", " + String(Signal_1) + ", "+ String(Signal_2) + ", "+ String(Signal_3) + ", " + String(Signal_4) +   + "]"; 
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
  delay(500);
}

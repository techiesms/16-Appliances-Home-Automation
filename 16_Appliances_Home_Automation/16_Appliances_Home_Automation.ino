#include <PubSubClient.h>
#include <WiFi.h>
#include <stdio.h>


/****************************************
   Define Constants
 ****************************************/

#define WIFISSID "SSID" // Put your WifiSSID here
#define PASSWORD "PASSWORD" // Put your wifi password here
#define TOKEN "Token" // Put your Ubidots' TOKEN

#define VARIABLE_LABEL_SUB_1 "relay1" // Assing the variable label to subscribe
#define VARIABLE_LABEL_SUB_2 "relay2" // Assing the variable label to subscribe
#define VARIABLE_LABEL_SUB_3 "relay3" // Assing the variable label to subscribe
#define VARIABLE_LABEL_SUB_4 "relay4" // Assing the variable label to subscribe
#define VARIABLE_LABEL_SUB_5 "relay5" // Assing the variable label to subscribe
#define VARIABLE_LABEL_SUB_6 "relay6" // Assing the variable label to subscribe
#define VARIABLE_LABEL_SUB_7 "relay7" // Assing the variable label to subscribe
#define VARIABLE_LABEL_SUB_8 "relay8" // Assing the variable label to subscribe
#define VARIABLE_LABEL_SUB_9 "relay9" // Assing the variable label to subscribe
#define VARIABLE_LABEL_SUB_10 "relay10" // Assing the variable label to subscribe
#define VARIABLE_LABEL_SUB_11 "relay11" // Assing the variable label to subscribe
#define VARIABLE_LABEL_SUB_12 "relay12" // Assing the variable label to subscribe
#define VARIABLE_LABEL_SUB_13 "relay13" // Assing the variable label to subscribe
#define VARIABLE_LABEL_SUB_14 "relay14" // Assing the variable label to subscribe
#define VARIABLE_LABEL_SUB_15 "relay15" // Assing the variable label to subscribe
#define VARIABLE_LABEL_SUB_16 "relay16" // Assing the variable label to subscribe

#define DEVICE_LABEL "esp32" // Assig the device label to subscribe
#define MQTT_CLIENT_NAME "testing" // MQTT client Name, put a Random ASCII
//#define SENSOR1 12;
//#define SENSOR2 13;
#define R1 15
#define R2 2
#define R3 4
#define R4 18
#define R5 19
#define R6 21
#define R7 22
#define R8 23
#define R9 32
#define R10 33
#define R11 25
#define R12 26
#define R13 27
#define R14 14
#define R15 12
#define R16 13

#define Buzzer 5

char mqttBroker[] = "industrial.api.ubidots.com";

const int ERROR_VALUE = 65535;  // Set here an error value

const uint8_t NUMBER_OF_VARIABLES = 16; // Number of variable to subscribe to
char * variable_labels[NUMBER_OF_VARIABLES] = {"relay1", "relay2", "relay3", "relay4", "relay5", "relay6", "relay7", "relay8", "relay9", "relay10", "relay11", "relay12", "relay13", "relay14", "relay15", "relay16"}; // labels of the variable to subscribe to

float CONTROL1; // Name of the variable to be used within the code.
float CONTROL2; // Name of the variable to be used within the code.
float CONTROL3; // Name of the variable to be used within the code.
float CONTROL4; // Name of the variable to be used within the code.
float CONTROL5; // Name of the variable to be used within the code.
float CONTROL6; // Name of the variable to be used within the code.
float CONTROL7; // Name of the variable to be used within the code.
float CONTROL8; // Name of the variable to be used within the code.
float CONTROL9; // Name of the variable to be used within the code.
float CONTROL10; // Name of the variable to be used within the code.
float CONTROL11; // Name of the variable to be used within the code.
float CONTROL12; // Name of the variable to be used within the code.
float CONTROL13; // Name of the variable to be used within the code.
float CONTROL14; // Name of the variable to be used within the code.
float CONTROL15; // Name of the variable to be used within the code.
float CONTROL16; // Name of the variable to be used within the code.

float value; // To store incoming value.
uint8_t variable; // To keep track of the state machine and be able to use the switch case.

//char str_sensor1[10]; // Space to store values to send
//char str_sensor2[10]; // Space to store values to send

/****************************************
   Initializate constructors for objects
 ****************************************/

WiFiClient ubidots;
PubSubClient client(ubidots);


/****************************************
   Auxiliar Functions
 ****************************************/

void callback(char* topic, byte* payload, unsigned int length) {
  char* variable_label = (char *) malloc(sizeof(char) * 30);;
  get_variable_label_topic(topic, variable_label);
  value = btof(payload, length);
  set_state(variable_label);
  execute_cases();
  free(variable_label);
}

// Parse topic to extract the variable label which changed value
void get_variable_label_topic(char * topic, char * variable_label) {
  Serial.print("topic:");
  Serial.println(topic);
  sprintf(variable_label, "");
  for (int i = 0; i < NUMBER_OF_VARIABLES; i++) {
    char * result_lv = strstr(topic, variable_labels[i]);
    if (result_lv != NULL) {
      uint8_t len = strlen(result_lv);
      char result[100];
      uint8_t i = 0;
      for (i = 0; i < len - 3; i++) {
        result[i] = result_lv[i];
      }
      result[i] = '\0';
      Serial.print("Label is: ");
      Serial.println(result);
      sprintf(variable_label, "%s", result);
      break;
    }
  }
}

// cast from an array of chars to float value.
float btof(byte * payload, unsigned int length) {
  char * demo_ = (char *) malloc(sizeof(char) * 10);
  for (int i = 0; i < length; i++) {
    demo_[i] = payload[i];
  }
  return atof(demo_);
}

// State machine to use switch case
void set_state(char* variable_label) {
  variable = 0;
  for (uint8_t i = 0; i < NUMBER_OF_VARIABLES; i++) {
    if (strcmp(variable_label, variable_labels[i]) == 0) {
      break;
    }
    variable++;
  }
  if (variable >= NUMBER_OF_VARIABLES) variable = ERROR_VALUE; // Not valid
}

// Function with switch case to determine which variable changed and assigned the value accordingly to the code variable
void execute_cases() {
  switch (variable) {
    case 0:
      CONTROL1 = value;
      digitalWrite(R1,value);
      Serial.print("CONTROL1: ");
      Serial.println(CONTROL1);
      Serial.println();
      break;
    case 1:
      CONTROL2 = value;
        digitalWrite(R2,value);
      Serial.print("CONTROL2: ");
      Serial.println(CONTROL2);
      Serial.println();
      break;
    case 2:
      CONTROL3 = value;
        digitalWrite(R3,value);
      Serial.print("CONTROL3: ");
      Serial.println(CONTROL3);
      Serial.println();
      break;
    case 3:
      CONTROL3 = value;
        digitalWrite(R4,value);
      Serial.print("CONTROL3: ");
      Serial.println(CONTROL3);
      Serial.println();
      break;
    case 4:
      CONTROL5 = value;
        digitalWrite(R5,value);
      Serial.print("CONTROL5: ");
      Serial.println(CONTROL5);
      Serial.println();
      break;
    case 5:
      CONTROL6 = value;
        digitalWrite(R6,value);
      Serial.print("CONTROL6: ");
      Serial.println(CONTROL6);
      Serial.println();
      break;
    case 6:
      CONTROL7 = value;
        digitalWrite(R7,value);
      Serial.print("CONTROL7: ");
      Serial.println(CONTROL7);

      Serial.println();
      break;
    case 7:
      CONTROL8 = value;
        digitalWrite(R8,value);
      Serial.print("CONTROL8: ");
      Serial.println(CONTROL8);
      Serial.println();
      break;
    case 8:
      CONTROL9 = value;
        digitalWrite(R9,value);
      Serial.print("CONTROL9: ");
      Serial.println(CONTROL9);
      Serial.println();
      break;
    case 9:
      CONTROL10 = value;
        digitalWrite(R10,value);
      Serial.print("CONTROL10: ");
      Serial.println(CONTROL10);

      Serial.println();
      break;
    case 10:
      CONTROL11 = value;
        digitalWrite(R11,value);
      Serial.print("CONTROL11: ");
      Serial.println(CONTROL11);
      Serial.println();
      break;
    case 11:
      CONTROL12 = value;
        digitalWrite(R12,value);
      Serial.print("CONTROL12: ");
      Serial.println(CONTROL12);
      Serial.println();
      break;
    case 12:
      CONTROL13 = value;
        digitalWrite(R13,value);
      Serial.print("CONTROL13: ");
      Serial.println(CONTROL13);
      Serial.println();
      break;
    case 13:
      CONTROL14 = value;
        digitalWrite(R14,value);
      Serial.print("CONTROL14: ");
      Serial.println(CONTROL14);
      Serial.println();
      break;
    case 14:
      CONTROL15 = value;
        digitalWrite(R15,value);
      Serial.print("CONTROL15: ");
      Serial.println(CONTROL15);
      Serial.println();
      break;
    case 15:
      CONTROL16 = value;
        digitalWrite(R16,value);
      Serial.print("CONTROL16: ");
      Serial.println(CONTROL16);
      Serial.println();
      break;
    case ERROR_VALUE:
      Serial.println("error");
      Serial.println();
      break;
    default:
      Serial.println("default");
      Serial.println();
  }

}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {

    digitalWrite(Buzzer, HIGH);
    delay(200);
    digitalWrite(Buzzer, LOW);
    delay(200);
    Serial.println("Attempting MQTT connection...");

    // Attempt to connect
    if (client.connect(MQTT_CLIENT_NAME, TOKEN, "")) {
      Serial.println("connected");
      digitalWrite(Buzzer, HIGH);
      delay(1000);
      digitalWrite(Buzzer, LOW);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 2 seconds");
      // Wait 2 seconds before retrying
      delay(2000);
      digitalWrite(Buzzer, HIGH);
      delay(200);
      digitalWrite(Buzzer, LOW);
      delay(50);
      digitalWrite(Buzzer, HIGH);
      delay(200);
      digitalWrite(Buzzer, LOW);
      delay(50);
    }
  }
}


/****************************************
   Main Functions
 ****************************************/

void setup() {
  Serial.begin(115200);
  //pinMode(A0, INPUT);
  pinMode(R1, OUTPUT);
  pinMode(R2, OUTPUT);
  pinMode(R3, OUTPUT);
  pinMode(R4, OUTPUT);
  pinMode(R5, OUTPUT);
  pinMode(R6, OUTPUT);
  pinMode(R7, OUTPUT);
  pinMode(R8, OUTPUT);
  pinMode(R9, OUTPUT);
  pinMode(R10, OUTPUT);
  pinMode(R11, OUTPUT);
  pinMode(R12, OUTPUT);
  pinMode(R13, OUTPUT);
  pinMode(R14, OUTPUT);
  pinMode(R15, OUTPUT);
  pinMode(R16, OUTPUT);

  pinMode(Buzzer, OUTPUT);

  WiFi.begin(WIFISSID, PASSWORD);
  Serial.println();
  Serial.println();
  Serial.print("Wait for WiFi... ");

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  client.setServer(mqttBroker, 1883);
  client.setCallback(callback);
}

void loop() {

  if (!client.connected()) {
    reconnect();

    // Subscribes for getting the value of the control variable in the temperature-box device
    char topicToSubscribe_variable_1[200];
    sprintf(topicToSubscribe_variable_1, "%s", ""); // Cleans the content of the char
    sprintf(topicToSubscribe_variable_1, "%s%s", "/v1.6/devices/", DEVICE_LABEL);
    sprintf(topicToSubscribe_variable_1, "%s/%s/lv", topicToSubscribe_variable_1, VARIABLE_LABEL_SUB_1);
    Serial.println("subscribing to topic:");
    Serial.println(topicToSubscribe_variable_1);
    client.subscribe(topicToSubscribe_variable_1);

    char topicToSubscribe_variable_2[200];
    sprintf(topicToSubscribe_variable_2, "%s", ""); // Cleans the content of the char
    sprintf(topicToSubscribe_variable_2, "%s%s", "/v1.6/devices/", DEVICE_LABEL);
    sprintf(topicToSubscribe_variable_2, "%s/%s/lv", topicToSubscribe_variable_2, VARIABLE_LABEL_SUB_2);
    Serial.println("subscribing to topic:");
    Serial.println(topicToSubscribe_variable_2);
    client.subscribe(topicToSubscribe_variable_2);

    char topicToSubscribe_variable_3[200];
    sprintf(topicToSubscribe_variable_3, "%s", ""); // Cleans the content of the char
    sprintf(topicToSubscribe_variable_3, "%s%s", "/v1.6/devices/", DEVICE_LABEL);
    sprintf(topicToSubscribe_variable_3, "%s/%s/lv", topicToSubscribe_variable_3, VARIABLE_LABEL_SUB_3);
    Serial.println("subscribing to topic:");
    Serial.println(topicToSubscribe_variable_3);
    client.subscribe(topicToSubscribe_variable_3);

    char topicToSubscribe_variable_4[200];
    sprintf(topicToSubscribe_variable_4, "%s", ""); // Cleans the content of the char
    sprintf(topicToSubscribe_variable_4, "%s%s", "/v1.6/devices/", DEVICE_LABEL);
    sprintf(topicToSubscribe_variable_4, "%s/%s/lv", topicToSubscribe_variable_4, VARIABLE_LABEL_SUB_4);
    Serial.println("subscribing to topic:");
    Serial.println(topicToSubscribe_variable_4);
    client.subscribe(topicToSubscribe_variable_4);

    char topicToSubscribe_variable_5[200];
    sprintf(topicToSubscribe_variable_5, "%s", ""); // Cleans the content of the char
    sprintf(topicToSubscribe_variable_5, "%s%s", "/v1.6/devices/", DEVICE_LABEL);
    sprintf(topicToSubscribe_variable_5, "%s/%s/lv", topicToSubscribe_variable_5, VARIABLE_LABEL_SUB_5);
    Serial.println("subscribing to topic:");
    Serial.println(topicToSubscribe_variable_5);
    client.subscribe(topicToSubscribe_variable_5);

    char topicToSubscribe_variable_6[200];
    sprintf(topicToSubscribe_variable_6, "%s", ""); // Cleans the content of the char
    sprintf(topicToSubscribe_variable_6, "%s%s", "/v1.6/devices/", DEVICE_LABEL);
    sprintf(topicToSubscribe_variable_6, "%s/%s/lv", topicToSubscribe_variable_6, VARIABLE_LABEL_SUB_6);
    Serial.println("subscribing to topic:");
    Serial.println(topicToSubscribe_variable_6);
    client.subscribe(topicToSubscribe_variable_6);

    char topicToSubscribe_variable_7[200];
    sprintf(topicToSubscribe_variable_7, "%s", ""); // Cleans the content of the char
    sprintf(topicToSubscribe_variable_7, "%s%s", "/v1.6/devices/", DEVICE_LABEL);
    sprintf(topicToSubscribe_variable_7, "%s/%s/lv", topicToSubscribe_variable_7, VARIABLE_LABEL_SUB_7);
    Serial.println("subscribing to topic:");
    Serial.println(topicToSubscribe_variable_7);
    client.subscribe(topicToSubscribe_variable_7);

    char topicToSubscribe_variable_8[200];
    sprintf(topicToSubscribe_variable_8, "%s", ""); // Cleans the content of the char
    sprintf(topicToSubscribe_variable_8, "%s%s", "/v1.6/devices/", DEVICE_LABEL);
    sprintf(topicToSubscribe_variable_8, "%s/%s/lv", topicToSubscribe_variable_8, VARIABLE_LABEL_SUB_8);
    Serial.println("subscribing to topic:");
    Serial.println(topicToSubscribe_variable_8);
    client.subscribe(topicToSubscribe_variable_8);

    char topicToSubscribe_variable_9[200];
    sprintf(topicToSubscribe_variable_9, "%s", ""); // Cleans the content of the char
    sprintf(topicToSubscribe_variable_9, "%s%s", "/v1.6/devices/", DEVICE_LABEL);
    sprintf(topicToSubscribe_variable_9, "%s/%s/lv", topicToSubscribe_variable_9, VARIABLE_LABEL_SUB_9);
    Serial.println("subscribing to topic:");
    Serial.println(topicToSubscribe_variable_9);
    client.subscribe(topicToSubscribe_variable_9);

    char topicToSubscribe_variable_10[200];
    sprintf(topicToSubscribe_variable_10, "%s", ""); // Cleans the content of the char
    sprintf(topicToSubscribe_variable_10, "%s%s", "/v1.6/devices/", DEVICE_LABEL);
    sprintf(topicToSubscribe_variable_10, "%s/%s/lv", topicToSubscribe_variable_10, VARIABLE_LABEL_SUB_10);
    Serial.println("subscribing to topic:");
    Serial.println(topicToSubscribe_variable_10);
    client.subscribe(topicToSubscribe_variable_10);

    char topicToSubscribe_variable_11[200];
    sprintf(topicToSubscribe_variable_11, "%s", ""); // Cleans the content of the char
    sprintf(topicToSubscribe_variable_11, "%s%s", "/v1.6/devices/", DEVICE_LABEL);
    sprintf(topicToSubscribe_variable_11, "%s/%s/lv", topicToSubscribe_variable_11, VARIABLE_LABEL_SUB_11);
    Serial.println("subscribing to topic:");
    Serial.println(topicToSubscribe_variable_11);
    client.subscribe(topicToSubscribe_variable_11);

    char topicToSubscribe_variable_12[200];
    sprintf(topicToSubscribe_variable_12, "%s", ""); // Cleans the content of the char
    sprintf(topicToSubscribe_variable_12, "%s%s", "/v1.6/devices/", DEVICE_LABEL);
    sprintf(topicToSubscribe_variable_12, "%s/%s/lv", topicToSubscribe_variable_12, VARIABLE_LABEL_SUB_12);
    Serial.println("subscribing to topic:");
    Serial.println(topicToSubscribe_variable_12);
    client.subscribe(topicToSubscribe_variable_12);

    char topicToSubscribe_variable_13[200];
    sprintf(topicToSubscribe_variable_13, "%s", ""); // Cleans the content of the char
    sprintf(topicToSubscribe_variable_13, "%s%s", "/v1.6/devices/", DEVICE_LABEL);
    sprintf(topicToSubscribe_variable_13, "%s/%s/lv", topicToSubscribe_variable_13, VARIABLE_LABEL_SUB_13);
    Serial.println("subscribing to topic:");
    Serial.println(topicToSubscribe_variable_13);
    client.subscribe(topicToSubscribe_variable_13);

    char topicToSubscribe_variable_14[200];
    sprintf(topicToSubscribe_variable_14, "%s", ""); // Cleans the content of the char
    sprintf(topicToSubscribe_variable_14, "%s%s", "/v1.6/devices/", DEVICE_LABEL);
    sprintf(topicToSubscribe_variable_14, "%s/%s/lv", topicToSubscribe_variable_14, VARIABLE_LABEL_SUB_14);
    Serial.println("subscribing to topic:");
    Serial.println(topicToSubscribe_variable_14);
    client.subscribe(topicToSubscribe_variable_14);

    char topicToSubscribe_variable_15[200];
    sprintf(topicToSubscribe_variable_15, "%s", ""); // Cleans the content of the char
    sprintf(topicToSubscribe_variable_15, "%s%s", "/v1.6/devices/", DEVICE_LABEL);
    sprintf(topicToSubscribe_variable_15, "%s/%s/lv", topicToSubscribe_variable_15, VARIABLE_LABEL_SUB_15);
    Serial.println("subscribing to topic:");
    Serial.println(topicToSubscribe_variable_15);
    client.subscribe(topicToSubscribe_variable_15);

    char topicToSubscribe_variable_16[200];
    sprintf(topicToSubscribe_variable_16, "%s", ""); // Cleans the content of the char
    sprintf(topicToSubscribe_variable_16, "%s%s", "/v1.6/devices/", DEVICE_LABEL);
    sprintf(topicToSubscribe_variable_16, "%s/%s/lv", topicToSubscribe_variable_16, VARIABLE_LABEL_SUB_16);
    Serial.println("subscribing to topic:");
    Serial.println(topicToSubscribe_variable_16);
    client.subscribe(topicToSubscribe_variable_16);
  }
  /*
    char payload_publish[100];
    char topicToPublish[200];

    float sensor_1 = 15; // Fix value. Modify it with the sensor reading
    float sensor_2 = 25; // Fix value. Modify it with the sensor reading

    // 4 is mininum width, 2 is precision; float value is copied onto str_sensor
    dtostrf(sensor_1, 4, 2, str_sensor1);
    dtostrf(sensor_2, 4, 2, str_sensor2);

    sprintf(topicToPublish, "%s", ""); // Cleans the content of the char
    sprintf(topicToPublish, "%s%s", "/v1.6/devices/", DEVICE_LABEL);
    sprintf(payload_publish, "{\"%s\":%s", VARIABLE_LABEL_PUB_1, str_sensor1); // Adds the variable label
    sprintf(payload_publish, "%s,\"%s\":%s}", payload_publish, VARIABLE_LABEL_PUB_2, str_sensor2); // Adds the variable label
    Serial.println("publishing to topic:");
    Serial.println(topicToPublish);
    Serial.println("Payload published:");
    Serial.println(payload_publish);
    client.publish(topicToPublish, payload_publish);
  */
  client.loop();
  delay(1);
}

#include <WiFi.h>
#include <WebServer.h>
#include "inference.h"

const char* ssid = "ThreeUK_LTE_4200";
const char* password = "B9299576684RDC2Y";
const int num_inputs = 3;

Inference model;

WebServer server(80);

void handleGetRequest() {
  String message = "Hello from ESP32/Arduino";
  server.send(200, "text/plain", message);
}

float inference(int num_inputs, float* inputs) {
  float output = model.predict(inputs, num_inputs); // todo
  return output;
}


String WiFi_receive(String send_message, int num_inputs) {
  Serial.print("Processing message: ");
  Serial.println(send_message);



  char messageBuffer[send_message.length() + 1];
  send_message.toCharArray(messageBuffer, sizeof(messageBuffer));

  float inputs[num_inputs];

  char *token = strtok(messageBuffer, ", ");
  int i = 0;

  while (token != NULL && i < num_inputs) {
    inputs[i++] = atof(token);
    token = strtok(NULL, ", ");
  }

  float output = inference(num_inputs, inputs);
  

  char response_message[100];
  sprintf(response_message, "%lf", output);

  Serial.print("Response to PC: ");
  Serial.println(response_message);
  return response_message;  // Return response to be sent back
}

void handlePostRequest() {
  if (server.hasArg("plain")) {
    String message = server.arg("plain");
    Serial.print("Received from PC: ");
    Serial.println(message);
    
    String response = WiFi_receive(message, num_inputs);
    server.send(200, "text/plain", response);  // Send response back to PC
  } else {
    server.send(400, "text/plain", "No message received");
  }
}

void setup() {
  Serial.begin(115200);
  model.begin();
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
  Serial.print("ESP32 IP Address: ");
  Serial.println(WiFi.localIP());

  server.on("/sendMessage", HTTP_GET, handleGetRequest);
  server.on("/sendMessage", HTTP_POST, handlePostRequest);

  server.begin();
  Serial.println("Server started");
}

void loop() {
  server.handleClient();
}

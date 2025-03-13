#include "inference.h"

unsigned long startTime;
unsigned long endTime;
const int num_inputs = 3;

Inference model;

void setup() {
  Serial.begin(115200);
  model.begin();
  Serial.println("ESP32 is ready. Please enter a message:");
}

void loop() {
  UART_send();
}

void UART_send() {
  static String sendMessage = "";

  while (Serial.available()) {
    char incomingChar = Serial.read();

    if (incomingChar == '\n') {
      startTime = micros();  // Start time in microseconds
      Serial.print("You sent: ");
      Serial.println(sendMessage);
      UART_process(sendMessage, num_inputs);
      sendMessage = "";  // Reset message buffer
    } else {
      sendMessage += incomingChar;
    }
  }
}

void UART_process(String sendMessage, int num_inputs) {
  float inputs[num_inputs];

  char messageBuffer[sendMessage.length() + 1];
  sendMessage.toCharArray(messageBuffer, sizeof(messageBuffer));

  char *token = strtok(messageBuffer, ", ");
  int i = 0;

  while (token != NULL && i < num_inputs) {
    inputs[i++] = atof(token);
    token = strtok(NULL, ", ");
  }

  float output = inference(num_inputs, inputs);
  UART_receive(output);
}

float inference(int num_inputs, float* inputs) {
  float output = model.predict(inputs, num_inputs); // todo
  return output;
}

void UART_receive(float output) {
  char buffer[100];
  sprintf(buffer, "The Value is \"%lf\".", output);
  Serial.println(buffer);
  
  endTime = micros();  // End time in microseconds
  sprintf(buffer, "Total Time in UART: %lu µs", endTime - startTime);
  Serial.println(buffer);
}

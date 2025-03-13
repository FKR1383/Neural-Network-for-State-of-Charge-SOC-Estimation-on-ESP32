#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include "inference.h"

Inference model;

#define SERVICE_UUID        "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"

const int num_inputs = 3;

BLECharacteristic *pCharacteristic;

float inference(int num_inputs, float* inputs) {
    float output = model.predict(inputs, num_inputs); // todo
    return output;
}

std::string BLE_receive(const std::string& send_message, int num_inputs) {
    Serial.print("Processing message: ");
    Serial.println(send_message.c_str());

    char messageBuffer[send_message.length() + 1];
    strcpy(messageBuffer, send_message.c_str());

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

    return std::string(response_message);  // Corrected return type
}

// Callback class to handle write events
class MyCallbacks : public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic *pCharacteristic) {
        std::string value = pCharacteristic->getValue();
        if (value.length() > 0) {
            Serial.print("Received Value: ");
            Serial.println(value.c_str());

            // Process the received data
            std::string output = BLE_receive(value, num_inputs);

            std::string processedValue = "Processed: " + output;

            // Send processed data back to the PC
            pCharacteristic->setValue(processedValue);
            Serial.println("Sent back processed value.");
        }
    }
};

void setup() {
    Serial.begin(115200);
    model.begin();
    Serial.println("Starting BLE work!");

    BLEDevice::init("MyESP32");
    BLEServer *pServer = BLEDevice::createServer();
    BLEService *pService = pServer->createService(SERVICE_UUID);
    
    pCharacteristic = pService->createCharacteristic(
        CHARACTERISTIC_UUID,
        BLECharacteristic::PROPERTY_READ |
        BLECharacteristic::PROPERTY_WRITE |
        BLECharacteristic::PROPERTY_NOTIFY
    );

    pCharacteristic->setCallbacks(new MyCallbacks());
    pCharacteristic->setValue("Waiting for data...");
    pService->start();

    BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
    pAdvertising->addServiceUUID(SERVICE_UUID);
    pAdvertising->setScanResponse(true);
    pAdvertising->setMinPreferred(0x06);
    pAdvertising->setMinPreferred(0x12);
    BLEDevice::startAdvertising();
    
    Serial.println("BLE Ready. Waiting for connection...");
    Serial.print("Device MAC Address: ");
    Serial.println(BLEDevice::getAddress().toString().c_str());
}

void loop() {
    delay(2000);
}

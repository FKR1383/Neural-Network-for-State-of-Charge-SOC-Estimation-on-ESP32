#include "inference.h"
#include "model_data.h"

Inference::Inference()
    : error_reporter(nullptr), model(nullptr), interpreter(nullptr),
      input(nullptr), output(nullptr) {}

void Inference::begin() {
    Serial.begin(115200);
    while (!Serial);
    Serial.println("\nStarting Regression Model Setup...");

    static tflite::MicroErrorReporter micro_error_reporter;
    error_reporter = &micro_error_reporter;

    model = tflite::GetModel(battery_soc_model_tflite);
    if (model->version() != TFLITE_SCHEMA_VERSION) {
        Serial.println("Model version mismatch!");
        while (1);
    }

    static tflite::MicroMutableOpResolver<4> resolver;
    resolver.AddFullyConnected();
    resolver.AddRelu();
    resolver.AddLogistic();
    resolver.AddReshape();

    static tflite::MicroInterpreter static_interpreter(
        model, resolver, tensor_arena, kTensorArenaSize, error_reporter);
    interpreter = &static_interpreter;

    if (interpreter->AllocateTensors() != kTfLiteOk) {
        Serial.println("AllocateTensors failed!");
        while (1);
    }

    input = interpreter->input(0);
    output = interpreter->output(0);

    Serial.println("\nModel initialized!");
}

float Inference::predict(float input_features[], int size) {
    if (size != input->dims->data[1]) {
        Serial.println("Input size mismatch!");
        return -1;
    }

    for (int i = 0; i < size; i++) {
        input->data.f[i] = input_features[i];
    }

    if (interpreter->Invoke() != kTfLiteOk) {
        Serial.println("Invoke failed!");
        return -1;
    }

    return output->data.f[0];
}

#ifndef INFERENCE_H
#define INFERENCE_H

#include <Arduino.h>
#include <TensorFlowLite_ESP32.h>
#include "tensorflow/lite/micro/micro_mutable_op_resolver.h"
#include "tensorflow/lite/micro/micro_error_reporter.h"
#include "tensorflow/lite/micro/micro_interpreter.h"
#include "tensorflow/lite/schema/schema_generated.h"

class Inference {
public:
    Inference();
    void begin();
    float predict(float input_features[], int size);

private:
    tflite::ErrorReporter* error_reporter;
    const tflite::Model* model;
    tflite::MicroInterpreter* interpreter;
    TfLiteTensor* input;
    TfLiteTensor* output;

    static constexpr int kTensorArenaSize = 64 * 1024;
    uint8_t tensor_arena[kTensorArenaSize];
};

#endif


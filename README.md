# Neural Network for State-of-Charge (SOC) Estimation on ESP32

## Overview
This project focuses on implementing a neural network on an ESP32 microcontroller to predict the State-of-Charge (SOC) of a Li-Ion battery using inputs such as voltage, current, and temperature. The neural network is trained using TensorFlow and then converted to TensorFlow Lite for deployment on the ESP32. The project also compares the performance of three communication protocols: Wi-Fi, Bluetooth Low Energy (BLE), and UART for data transmission.

## Key Features
- **Neural Network Implementation**: A deep neural network is trained to predict SOC based on voltage, current, and temperature inputs.
- **TensorFlow Lite Conversion**: The trained model is converted to TensorFlow Lite format for deployment on the ESP32.
- **Communication Protocols**: The project implements and compares three communication protocols: Wi-Fi, BLE, and UART.
- **Real-Time Inference**: The ESP32 performs real-time inference using the deployed neural network model.

## Project Steps
1. **Neural Network Training**: Train a neural network using TensorFlow on a dataset containing voltage, current, and temperature data.
2. **Model Conversion**: Convert the trained model to TensorFlow Lite format for deployment on the ESP32.
3. **ESP32 Implementation**: Deploy the TensorFlow Lite model on the ESP32 and implement inference.
4. **Communication Protocols**: Implement Wi-Fi, BLE, and UART protocols for data transmission between the ESP32 and a PC.
5. **Performance Comparison**: Compare the performance of the three communication protocols in terms of data transmission time and inference speed.

## Tools and Technologies
- **TensorFlow**: Used for training the neural network.
- **TensorFlow Lite**: Used for deploying the neural network on the ESP32.
- **ESP32**: The microcontroller used for running the neural network and communication protocols.
- **Arduino IDE**: Used for programming the ESP32.
- **Python**: Used for data preprocessing and communication with the ESP32.

## Results
- **Neural Network Performance**: The neural network achieved a Mean Absolute Error (MAE) of approximately 0.0077 on the test dataset.
- **Communication Protocol Performance**:
  - **UART**: Average data transmission and inference time of approximately 250 microseconds.
  - **Wi-Fi**: Average data transmission and inference time of approximately 150,000 microseconds.
  - **BLE**: Average data transmission and inference time of approximately 170,000 microseconds.

## Conclusion
The project successfully demonstrated the deployment of a neural network on an ESP32 for real-time SOC estimation. The results show that UART provides the fastest data transmission, making it suitable for applications where low latency is critical. However, Wi-Fi and BLE are more suitable for wireless applications, especially in IoT devices where battery life and wireless connectivity are important considerations.

For more details, refer to the full project documentation and code in the repository.

import requests
import time

print("Please enter ESP32 IP: ")
esp_ip_address = input().strip()  # Ensure no extra spaces

esp32_ip = "http://" + esp_ip_address + "/sendMessage"

while(True):

    pc_message = input("Enter message to send: ")

    start_time = time.time()  # Start time in seconds

    post_response = requests.post(esp32_ip, data=pc_message)
    response = requests.get(esp32_ip)

    end_time = time.time()  # End time in seconds

    elapsed_time_microseconds = (end_time - start_time) * 1_000_000  # Convert to microseconds

    print("Response from ESP32 (GET):", response.text)
    print("Response from ESP32 (POST):", post_response.text)
    print(f"Time taken: {elapsed_time_microseconds:.2f} microseconds")


import asyncio
from bleak import BleakClient
from time import time

ESP32_ADDRESS = "ec:62:60:55:96:4a"
CHARACTERISTIC_UUID = "beb5483e-36e1-4688-b7f5-ea07361b26a8"

async def send_and_receive():
    async with BleakClient(ESP32_ADDRESS) as client:
        print("Connected to ESP32!")
        while (True):
            message = input("Enter message: ")

            start_time = time()

            await client.write_gatt_char(CHARACTERISTIC_UUID, message.encode())

            response = await client.read_gatt_char(CHARACTERISTIC_UUID)

            end_time = time()

            print(f"Sent: {message}")
            print(f"Received: {response.decode()}")
            print(f"Round-trip time: {end_time - start_time:.6f} seconds")

asyncio.run(send_and_receive())


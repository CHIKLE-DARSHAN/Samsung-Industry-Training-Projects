# Experiment 01 – DHT11 Temperature and Humidity Monitoring Using ESP32 and MQTT

## 1. Aim

To interface a DHT11 temperature and humidity sensor with an ESP32, connect the ESP32 to a Wi-Fi network, and publish temperature and relative-humidity readings to separate MQTT topics.

## 2. Overview

The ESP32 reads temperature and humidity values from the DHT11 sensor. It connects to an MQTT broker and publishes each reading to its own topic. An MQTT client subscribed to those topics can receive and display the readings.

**ESP32 role:** Publisher

## 3. Hardware requirements

- ESP32 development board
- DHT11 sensor (module or bare sensor)
- Breadboard and jumper wires
- USB data cable
- Suitable power source

## 4. Software requirements

- Arduino IDE
- ESP32 board package
- `WiFi.h` (included with the ESP32 Arduino core)
- `PubSubClient` library
- `DHT sensor library` (for example, Adafruit DHT sensor library)

## 5. Wiring

The supplied sketch defines `DHTPIN` as GPIO 5.

| DHT11 connection | ESP32 |
|---|---|
| VCC | 3.3V (check your module's specifications) |
| DATA | GPIO 5 |
| GND | GND |

For a bare DHT11 sensor, use the pull-up resistor arrangement recommended by its datasheet. Many DHT11 modules already include a pull-up resistor. Check the pin order printed on your specific module; do not assume every module has the same layout.

![Experiment 01 hardware setup](images/hardware_setup.jpg)

_Add your own clear photograph of the ESP32 connected to the DHT11. Save it as `hardware_setup.jpg` in this folder's `images` directory._

## 6. MQTT configuration

| Setting | Value in the supplied sketch |
|---|---|
| Broker host | `broker.emqx.io` |
| Port | `1883` |
| Temperature topic | `Team/Sensors/Temperature` |
| Humidity topic | `Team/Sensors/Humidity` |
| Publishing interval | 5 seconds |
| ESP32 role | Publisher |

Use a unique topic prefix for public-broker testing if possible. The broker is public, so other users may be able to publish to or subscribe to topics.

## 7. How it works

1. The ESP32 starts the Serial Monitor.
2. It connects to the configured Wi-Fi network.
3. It initializes the DHT11 sensor.
4. It connects to the MQTT broker using its generated client ID.
5. It reads temperature and humidity from the DHT11.
6. It publishes temperature to `Team/Sensors/Temperature`.
7. It publishes humidity to `Team/Sensors/Humidity`.
8. It repeats the read-and-publish operation approximately every five seconds.

## 8. Execution procedure

1. Install the ESP32 board package in Arduino IDE.
2. Install `PubSubClient` and the DHT sensor library.
3. Open `DHT11_Publisher.ino`.
4. Replace `SSID` and `pass` with your Wi-Fi name and password.
5. Verify the broker authentication requirements. The username/password shown in the example are placeholders from the original sketch and may not be accepted by the public broker.
6. Connect the DHT11 DATA pin to GPIO 5, VCC to the appropriate supply, and GND to GND.
7. Select the correct ESP32 board and COM port.
8. Upload the sketch.
9. Open Serial Monitor at 115200 baud.
10. Use an MQTT client to subscribe to both configured topics and check for incoming readings.

## 9. Expected Serial Monitor output

Example only; actual readings depend on the room and sensor:

```text
WiFi connected!
IP address: 192.168.x.x
MQTT Client ID: ESP32Sensor-...
Connected to MQTT!
Published Temperature: 26.3
Published Humidity: 37.0
```

![Experiment 01 Serial Monitor](images/serial_monitor.png)

_Add your actual Serial Monitor screenshot as `serial_monitor.png`._

![Experiment 01 MQTT topics](images/mqtt_topics.png)

_Add a screenshot from your MQTT client showing the temperature and humidity topics and received values as `mqtt_topics.png`._

## 10. Result

When successfully tested, the ESP32 reads temperature and relative humidity from the DHT11 and publishes the two values to their respective MQTT topics through the configured broker.

## 11. Troubleshooting

- **Wi-Fi does not connect:** Check the SSID, password, Wi-Fi availability, and whether the network supports the ESP32's Wi-Fi band.
- **DHT read fails:** Check the DATA connection, power, ground, pin definition, and pull-up arrangement. Allow the sensor time between readings.
- **MQTT connection fails:** Check broker reachability, port, client ID uniqueness, and whether authentication is required.
- **No MQTT messages appear:** Confirm that the MQTT client subscribes to the exact topic and uses the same broker host and port.

## 12. Security note

Do not upload real Wi-Fi passwords or private broker credentials to GitHub. Replace the example credentials locally before uploading, and remove secrets from the source before committing.

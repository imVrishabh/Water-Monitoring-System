# Automatic Sand Moisture Detection and Watering System

This project is a low-cost Arduino-based irrigation prototype designed to monitor sand moisture and automatically turn on a water pump when the soil becomes too dry. It also displays the sensor value, estimated moisture percentage, and system status on a 0.96-inch OLED screen.

The system is intended for small-scale experimentation and prototype gardening setups. It is useful for learning how capacitive moisture sensors, relays, and simple automation behave in a real embedded system.

> Warning: The sensor thresholds and pump timing must be calibrated for your specific sand and setup before leaving the system unattended.

## Features

- Reads analog moisture levels from a capacitive soil sensor
- Automatically controls a DC pump via a 5V relay module
- Displays live moisture data on a 0.96-inch I2C OLED
- Prints readings to the Arduino Serial Monitor
- Uses simple calibration constants for dry and wet reference values
- Easy to modify for different soil types and watering needs

## Hardware Required

- Arduino UNO
- Capacitive soil moisture sensor
- 5V relay module (active LOW assumed in the code)
- DC water pump
- 0.96-inch I2C OLED display (SSD1306, 128x64)
- 2S lithium battery pack or suitable DC supply for the pump
- Optional switch for pump power
- Jumper wires and tubing

## Wiring

### Moisture Sensor to Arduino UNO

| Sensor Pin | Arduino Pin |
| --- | --- |
| VCC | 5V |
| GND | GND |
| AO | A0 |
| DO | Not Used |

### Relay Module to Arduino UNO

| Relay Pin | Arduino Pin |
| --- | --- |
| VCC | 5V |
| GND | GND |
| IN | D7 |

The code assumes an active-LOW relay. In this configuration, LOW turns the pump on and HIGH turns it off. Verify the polarity of your relay module before final use.

### OLED to Arduino UNO

| OLED Pin | Arduino Pin |
| --- | --- |
| GND | GND |
| VDD | 5V (only if supported by the breakout) |
| SCL | A5 |
| SDA | A4 |

This sketch assumes a 128x64 SSD1306 OLED connected at I2C address 0x3C.

### Pump Power Circuit

Use the relay contacts for the pump power circuit:

- Battery positive → optional switch → COM
- NO → pump positive
- Pump negative → battery negative
- NC remains unconnected

Keep the relay control circuit (5V Arduino side) separate from the pump power circuit.

## Power and Safety Notes

- The pump should be compatible with the chosen battery voltage and startup current.
- Do not connect a battery pack directly to the Arduino 5V rail unless it is a proper regulated supply.
- If using a 2-cell Li-ion pack, use a proper protected 2S pack and charger.
- Keep all wiring dry and isolated from water exposure.
- Confirm that the relay contacts are rated for the pump current.
- Disconnect power before modifying connections.

## Software Setup

1. Install the Arduino IDE.
2. Install these libraries from the Arduino Library Manager:
   - Adafruit SSD1306
   - Adafruit GFX Library
3. Open the project file in the Arduino IDE.
4. Select the correct board: Arduino UNO.
5. Choose the correct COM port.
6. Upload the code.
7. Open the Serial Monitor at 9600 baud.

## Project Logic

The system performs the following operations in a loop:

1. Reads the analog moisture sensor value from A0.
2. Maps the reading to an approximate percentage using calibration values.
3. Compares the reading with a watering threshold.
4. Turns the relay and pump ON when the soil is dry.
5. Displays sensor value, moisture percentage, status, and pump state on the OLED.
6. Sends the same information to the Serial Monitor.

## Calibration

The code includes example calibration values:

- `DRY_VALUE = 950`
- `WET_VALUE = 250`
- `WATERING_THRESHOLD = 600`

These are starting values for testing and may not match your actual sand conditions.

Typical prototype readings observed:

- Sensor in air: approximately 1023
- Dry sand: approximately 900–1000
- Wet sand / water: approximately 200–300

Real readings vary depending on:

- sand type
- compaction
- moisture distribution
- sensor placement
- salinity
- supply voltage
- temperature

It is recommended to test the sensor in the exact material you plan to use and adjust the threshold accordingly.

## Example Output

The OLED displays values similar to this:

- Sensor: 740
- Moisture: 35%
- Status: DRY
- Pump: ON

The Serial Monitor prints the same information every second.

## File Structure

- `Code.c++` — Arduino sketch containing the logic for reading moisture, controlling the relay, and updating the OLED.

## Notes

This is a learning and prototype project, not a production-grade irrigation controller. It demonstrates the basic idea of environmental sensing and automated watering using low-cost hardware.

If you want to extend the system, you could add:

- hysteresis to avoid rapid pump cycling
- pump runtime limits
- a moisture history graph
- a separate soil dry/wet threshold calibration mode
- Wi-Fi or Bluetooth monitoring
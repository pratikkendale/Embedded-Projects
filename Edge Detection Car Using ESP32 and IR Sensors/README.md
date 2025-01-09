# Edge Avoidance Car

This project demonstrates how to build an edge avoidance car using an ESP32, motor driver, and IR sensors. The car detects edges using two IR sensors and avoids falling by adjusting its direction based on sensor input.

## Components Used

1. ESP32 microcontroller
2. Motor driver (L298N or similar)
3. Two DC motors/  BO Motors
4. Two IR sensors
5. Power supply
6. Connecting wires
7. Chassis for the car

## How It Works

- The car is equipped with two IR sensors positioned at the front.
- If both sensors detect the ground (LOW state), the car moves forward.
- If the right sensor detects an edge (HIGH state) while the left sensor detects the ground, the car turns Left.
- If the left sensor detects an edge (HIGH state) while the right sensor detects the ground, the car turns Right.
- If both sensors detect an edge, the car moves backward.

## Circuit Connections

1. Connect the IR sensors to the ESP32 GPIO pins.
2. Connect the motor driver's input pins to the ESP32.
3. Connect the motors to the motor driver outputs.
4. Power the motor driver and ESP32 using a suitable power source.

## Steps to Run the Project

1. Assemble the circuit according to the connection.
2. Upload the provided code to the ESP32 using the Arduino IDE.
3. Power the setup and test the car's movements near edges.

## GitHub Repository

### Repository Name: **Edge-Avoidance-Car**

**Description:** This repository contains the code and instructions to build an edge avoidance car using ESP32 and IR sensors.

#### Files:
- `README.md`: Project documentation
- `EdgeAvoidanceCar.ino`: Source code for the car.





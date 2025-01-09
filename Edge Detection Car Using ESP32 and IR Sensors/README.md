🚘 Edge Detection Car Using ESP32 and IR Sensors
💡 Project Overview
This project demonstrates an autonomous car capable of avoiding edges and preventing itself from falling off surfaces. It uses IR sensors to detect the ground and make decisions to either move forward, stop, or turn. Powered by an ESP32 microcontroller, the car integrates efficient motor control and precise sensor-based navigation.

✨ Features
Edge Detection: Uses IR sensors to detect the presence or absence of ground.
Autonomous Movement: The car adjusts its direction based on sensor readings to avoid edges.
Simple Control Logic: Handles all edge-avoidance decisions using just two IR sensors.
🔧 Hardware Components
ESP32: Controls the logic and motion of the car.
IR Sensors: Detects ground or edge:
Left IR Sensor: Pin 13
Right IR Sensor: Pin 19
Motor Driver Module: Drives the two motors:
Motor 1 Input Pins: 2, 5
Motor 2 Input Pins: 16, 17
DC Motors: Moves the car forward, backward, and allows turns.
Power Supply: Battery pack to power the system.
📜 Code Logic
Move Forward: When both IR sensors detect ground.
Turn Right: When the left IR sensor detects ground, and the right does not.
Turn Left: When the right IR sensor detects ground, and the left does not.
Stop/Move Backward: When both sensors detect no ground, indicating an edge.

🛠️ How to Run
Set Up Hardware:

Connect the IR sensors, motors, and ESP32 as per the circuit diagram.
Ensure proper power connections to all components.
Upload Code:

Use the Arduino IDE to upload the code to the ESP32.
Power Up:

Power the car using a battery pack and place it on a flat surface.
Test:

Observe the car as it detects edges and avoids them autonomously.


🚀 Future Enhancements
Add an ultrasonic sensor for obstacle detection.
Implement speed control using PWM for smoother motion.
Enable remote control via Bluetooth or Wi-Fi for additional control.
🔗 GitHub Repository
🌟 Star this project if you find it useful!
💬 Feel free to fork, contribute, or provide feedback to improve this project.

Happy Building! 🚗✨

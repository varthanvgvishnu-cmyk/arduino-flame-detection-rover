# Arduino-Based Flame Detection Rover

## Overview
The Flame Detection Rover is an Arduino-based robotic prototype that detects flames using three IR flame sensors positioned at the left, front, and right. It uses an L298N motor driver to control movement and a relay module to operate a water pump when a flame is detected in front.

## Features
- Three-direction flame detection
- Automatic left and right turning
- Automatic stopping when a flame is detected in front
- Relay-controlled water pump
- Real-time sensor status through the Serial Monitor
- Arduino Uno-based embedded control

## Hardware Components
- Arduino Uno
- Three digital-output IR flame sensor modules
- L298N motor driver
- DC geared motors
- Robot chassis and wheels
- Relay module
- Mini water pump
- Suitable motor and pump power supplies
- Jumper wires

## Pin Connections

| Component | Arduino pin |
|---|---|
| Left flame sensor DO | D11 |
| Front flame sensor DO | D12 |
| Right flame sensor DO | D13 |
| L298N IN1 | D5 |
| L298N IN2 | D6 |
| L298N IN3 | D9 |
| L298N IN4 | D10 |
| Relay input | D7 |

The sketch assumes that each flame sensor outputs LOW when a flame is detected and HIGH otherwise. Relay activation polarity is configurable in the Arduino code.

## Working Principle
1. The three flame sensors continuously monitor for a flame.
2. The Arduino reads the sensors and identifies the detected direction.
3. A left-side detection commands a left turn.
4. A right-side detection commands a right turn.
5. A front-side detection stops the rover and activates the water pump.
6. When no flame is detected, the rover stops and the pump switches off.

## Software Requirements
- Arduino IDE
- Arduino Uno board support
- USB cable for programming

No external Arduino libraries are required.

## Upload Instructions
1. Open `flame_rover.ino` in the Arduino IDE.
2. Connect the Arduino Uno through USB.
3. Select **Tools → Board → Arduino Uno**.
4. Select the correct serial port.
5. Upload the sketch.
6. Open the Serial Monitor at **9600 baud**.
7. Test the sensors and motors individually before running the complete rover.

## Repository Structure
- `flame_rover.ino` — Arduino control program
- `README.md` — Project documentation
- `media/` — Project photos and circuit diagrams

## Safety
This is an educational prototype, not certified firefighting equipment. Test the sensors using a safe, controlled demonstration. Keep water away from exposed electronics and use appropriate supplies for the motors and pump. Never use the rover to approach hazardous fires.

## Author
Vishnu Varthan VG

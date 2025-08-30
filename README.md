# Embedded Systems Architecture Project – Team 18  

This repository contains the development of our **CSEN701 – Embedded Systems Architecture** course project.  
The project was built across three milestones, each adding new layers of hardware, software, and system design.  
More details of project implementation are available in the report.

---

## 📂 Repository Structure  

- **main branch** → General documentation & consolidated updates.  
- **MS_01 branch** → Milestone 1 implementation (basic setup + LED driver).  
- **MS_02 branch** → Milestone 2 implementation (hardware integration + drivers + dummy testing).  
- **MS_03_car_control branch** → Milestone 3 implementation (final system integration for car control).  
- **MS_03_tilt_detection branch** → Milestone 3 implementation (tilt/IMU-based detection module).  

---

## 🟢 Milestone 01 – Basic Setup & LED Driver  

**Objective:**  
Ensure the development environment is set up (Arduino Nano RP2040 / Raspberry Pi Pico RP2040 on VS Code with CMake), and implement a basic hardware driver.  

**Implementation:**  
- Verified toolchain setup for C/C++ development using **Pico SDK**.  
- Implemented a **LED driver** (`led.c`, `led.h`) controlling three LEDs (R, G, B).  
- Connections:  
  - Red & Green LEDs → positive logic (with series resistors).  
  - Blue LED → negative logic (with pull-up resistor).  
- **Behavior:**  
  - LEDs OFF for first 5s.  
  - Sequential ON/OFF: Red → Green → Blue (1s each).  
  - All ON for 2s, then OFF.  
  - Cycle repeats every 10s.  
- Verified using delay-based timing loops.  

📄 Deliverables in branch `MS_01`:  
- `main.c` (core control loop).  
- `led.c`, `led.h` (driver implementation).  
- `CMakeLists.txt` for build.  

---

## 🟡 Milestone 02 – Hardware Integration & Modeling  

**Objective:**  
Physically assemble the project hardware, connect sensors/actuators, and implement drivers with basic test code.  

**Hardware Setup:**  
- Components included:  
  - Sensors: MPU6050 IMU, ultrasonic sensor, IR sensor.  
  - Actuators: DC motors with motor driver (PWM), servo, buzzer.  
- Assembled onto the car chassis.  

**Implementation:**  
- Developed **driver files** for each sensor/actuator (e.g.`motor_driver.c`, `mpu6050.c`).  
- Wrote **dummy test code** in `main.c` to:  
  - Read and print sensor values via UART (serial monitor).  
  - Independently actuate motors, servo, buzzer for verification.  
- Verified sensor readings using **Putty serial monitor**.  

**System Modeling:**  
- Designed a **stateflow model** of the system:  
  - Showcasing **concurrency** (parallel tasks),  
  - **orthogonality** (independent subsystems),  
  - **broadcasting** (shared events),  
  - **hierarchy** (nested states).  

📄 Deliverables in branch `MS_02`:  
- Driver files for sensors/actuators.  
- `main.c` dummy test program.  
- Stateflow model (in final report).  

---

## 🔴 Milestone 03 – Full Integration & Concurrency   

**Objective:**  
Integrate all project hardware and implement full system software with concurrency and testing.  

**Branches:**  
- **`MS_03_car_control`** → Focuses on the final **car control system**. Implements motor control, steering, and obstacle avoidance.  
- **`MS_03_tilt_detection`** → Focuses on **tilt/IMU detection**. Implements sensor fusion and tilt-based event detection using MPU6050 data.  

**Implementation (shared across both branches):**  
- Assembled final chassis with all hardware embedded.  
- Established **communication protocols** (I2C for sensors, PWM for actuators, UART where applicable).   
- Implemented **test scenarios** to simulate different real-world conditions.  
- Documented all drivers, functions, and decisions in code comments.  

**Final Deliverables:**  
- `main.c` with FreeRTOS task scheduling.  
- Sensor and actuator drivers.  
- Updated Stateflow diagram.  
- Final hardware design + connection diagrams.  

---

## 👥 Team 18 Members  
- Omar Hatem  
- Malak Osama 
- Farah Khaled
- Seif Wael
- Kareem Sherif
- Shahd Matar
- Omar Seif

---

## 📌 Notes  
- Each milestone branch contains its respective implementation and documentation.  
- Build system: **CMake + Pico SDK**.  
- Microcontrollers used: **Arduino Nano RP2040 Connect / Raspberry Pi Pico W**.  
- Wi-Fi experiments were implemented with ESP32 modules for communication.  





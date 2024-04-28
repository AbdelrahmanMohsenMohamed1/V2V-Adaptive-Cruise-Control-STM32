# V2V Adaptive Cruise Control System

##  introduction
###  Purpose
The purpose of the V2V Adaptive Cruise Control project is to enhance driving safety by automatically adjusting the vehicle’s speed to maintain a safe distance from the cars around it by communicating and acting upon the data received.
In this project the V2V ACC is implemented on two cars, allowing them to exchange information and respond based on the acquired data from communication channels and onboard sensors.
###  Scope
This document outlines both the functional and non-functional requirements for the V2V Adaptive Cruise Control project. It covers the following aspects:
- 	Features: The V2V ACC system should include features such as Bluetooth communication, speed regulation, distance monitoring, and smooth acceleration/deceleration.
- 	Constraints: Any limitations or conditions that affect ACC performance, such as sensor accuracy, weather conditions, communication latency and road type. 
- 	Limitations: Clear identification of scenarios where ACC may not operate optimally (e.g., heavy traffic, abrupt lane changes, or low visibility).

## Table of Contents

- [Overall Description](#1.-Overall-Description)
- [2.project Features & Structure](#project-Features-&-Structure)
- [3.	External Interface Requirements](#External-Interface-Requirements)
- [4.	Functional Requirements](#Functional-Requirements)
- [5. State Machine Diagram](#State-Machine-Diagram)
- [6. Sequence Diagram](#Sequence-Diagram)
- [7.Testing](#Testing)
- [8.team member](#team-member)
- [9.Special Thanks](#Special-Thanks)
- [10.License](#License)
- [11.References](#10.References)


## 1.	Overall Description
### 1.1. Product Features 
The V2V ACC system offers the following key features:
•	Bluetooth Communication: By utilizing Bluetooth, vehicles exchange data seamlessly, enhancing safety and ensuring smoother operation. This cooperative communication allows cars to follow closely, brake, and accelerate in sync, resulting in safer driving experiences.

•	Distance-Based Speed Control: The ACC continuously monitors the distance between the vehicle and the obstacles ahead. It automatically adjusts the car’s speed to maintain a safe following distance, reducing the need for constant manual speed adjustments by the driver.


•	Manual Control via Bluetooth: In addition to automatic mode, the driver can take manual control of the vehicle’s speed using a Bluetooth-enabled interface. This feature allows flexibility for situations where the driver wants to override the ACC system temporarily.

•	Obstacle Alert System: When the ACC detects a nearby obstacle (such as another vehicle suddenly entering the lane), it activates visual and auditory alerts. The car’s buzzer and warning lights are triggered to notify the driver, promoting timely intervention.


### 1.2. Use Case Diagram 

![image](https://github.com/AbdelrahmanMohsenMohamed1/V2V-Adaptive-Cruise-Control/assets/109293965/7bdb2bbb-c0f2-4285-916c-56ede9b7c82c)

### 1.3. Operating Environment
The V2V ACC software will be deployed in the following environment:
•	Hardware Platform: The V2VACC system will run on the vehicle’s onboard computer, utilizing an ultrasonic sensor to gather data about the surroundings.
•	Software Environment: The software will be developed using the C programming Language. It must be compatible with the vehicle’s existing software stack and communication protocols.


## 2.	project Features & Structure
### 2.1 Automatic Speed Adjustment
Description:
The system automatically adjusts the vehicle's speed based on the distance and speed of the vehicle ahead and communication from the car behind it to maintain a safe following distance.
Inputs:
•	Distance and speed data from vehicle sensor (Ultrasonic).
•	Alert messages from the car behind.
•	Current vehicle speed.
Outputs:
•	Control signals to throttle and brake mechanisms for speed adjustment.
Dependencies:
•	Accurate sensor data processing and interpretation.
•	Real-time control algorithm execution.
### 2.2 Real-Time Monitoring and Alerting
Description:
The system continuously monitors the surrounding environment and detects potential collision scenarios. It provides real-time alerts are written on the LCD and sent to the car in front through the shared Bluetooth connection.
Inputs:
•	Sensor data related to vehicle proximity and speed.
•	Predefined collision thresholds and warning criteria.
Outputs:
•	Visual alerts on the LCD.
•	Sharing data with the car in front.

Dependencies:
•	Accurate and timely detection of potential collision scenarios.
•	Speed of data transmission and data acquisition.
### 2.3 Graphical User Interface (GUI) 
Description:
The system features a user-friendly GUI that allows the user to control the car when the ACC mode is OFF.
Moreover, GUI can be used to receive detected car speeds in ACC ON mode. 
Inputs:
•	User input through Mobile Application.
•	System status data from onboard sensors and control algorithms.
Outputs:
•	Visual representation of ACC settings and status.
•	Interactive elements for user interaction and configuration.
Dependencies:
•	Integration with vehicle infotainment systems or standalone display units.
•	Responsive and intuitive user interface design.
•	Turn on the car for more accessibility
•	Turn Off the car to add a security perspective. 

### 2.4 V2V data sharing
Description: The cars share distance information and send alerts to produce better and more stable outcome.
Inputs:
•	Leading car receives distance information from the preceding car.
Outputs:
•	The leading car should react according to the alert received.
Dependencies:
•	Responsive of the communication protocol.
•	Responsiveness of car to change its speed and right choice of reaction.


## 3.	External Interface Requirements
### 3.1	User Interfaces
The ACC system interacts with the vehicle’s LCD display and user controls. Key details include:
1. LCD Display:
Presents relevant information to the driver, including:

•	Current speed
•	Following distance
•	System status
•	Alerts
2. User Controls:
Users can control the ACC system using their mobile devices (e.g., smartphones) connected to the car via Bluetooth. These controls allow users to:

•	Enable or disable the ACC system.
•	Adjust the following distance settings.
•	Set speed limits.

### 3.2 Hardware Interfaces
The ACC system interfaces with various hardware components. Here are the key interfaces:
1. Distance Sensor:
●	The ultrasonic sensor detects the distance between the vehicle and the one ahead.
●	The software processes this distance information to determine appropriate actions (e.g., acceleration, deceleration, and stopping).
2. Speed Control:
●	Based on the distance measured by the ultrasonic sensor, the ACC system adjusts the speed of the vehicle.
●	Speed control is achieved using Pulse Width Modulation (PWM) to regulate the motor's speed.

### 3.3 Software Interfaces
Integration with the vehicle's onboard computer system is essential. The ACC system must:
1. Access Sensor Data:
●	 Communicate with the ultrasonic sensor to obtain real-time data.
●	Retrieve information about distances, speeds, and other relevant parameters.
2. Control Actuators:
●	Send commands to the actuator based on sensor inputs.
●	Ensure smooth speed adjustments and safe following distances.
3. Bluetooth communication between cars:
●	The preceding car alerts the car in front if it gets too near.
●	Enables data exchange and coordination between vehicles.




## 4.	Functional Requirements
### 4.1. Vehicle Detection
The A3CC system shall utilize ultrasonic sensors to detect vehicles ahead. Specifically:
•	Detection Mechanism:
The system shall employ ultrasonic sensors to identify nearby vehicles. It will continuously monitor the road ahead to detect any vehicles within its range.

•	Tracking Parameters:
The ACC system shall track the relative position of the vehicle ahead.

### 4.2. Speed Control
The ACC system shall ensure safe following distances and adjust the vehicle’s speed accordingly. Here are the details:
•	Following Distance:
The system shall maintain a safe distance from the detected vehicle ahead. This distance will be dynamically adjusted based on the relative speed and acceleration of the preceding vehicle.

•	Speed Adjustment:
To match the speed of the preceding vehicle, the ACC system shall control the vehicle’s speed using PWM.

### 4.3. User Interaction
The ACC system shall provide user-friendly interactions through the dashboard interface. Here’s how:
The user chooses the car’s initial desired speed through the dashboard interface and the car will try to reach this speed if the surroundings allow for this speed to be achieved.




### 4.4 V2V communication 
The V2V helps both cars share information to achieve a safer and smoother experience. Here are the details:
•	Data Exchange:
The preceding car will send relevant data about its speed and relative position to the car in front.
This data will be packaged and transmitted via Bluetooth to the car in front.

•	Receiving and Processing Data:
The car in front will receive the data from the preceding car.
It will process this information to understand the relative position, speed, and behaviour of the leading vehicle.
•	Adaptive Response:
Based on the received data, the following car’s ACC system will adjust its own speed and maintain a safe distance from the preceding vehicle.
If the leading car accelerates or decelerates the following car will react accordingly, ensuring smooth and safe driving.
•	Real-Time Updates:
The Bluetooth communication allows for real-time updates between vehicles.
As the situation changes (e.g., traffic conditions, road obstacles), both cars can adapt their behaviour promptly.

## 5.	State Machine Diagram
 ![image](https://github.com/AbdelrahmanMohsenMohamed1/V2V-Adaptive-Cruise-Control/assets/109293965/87955484-20df-4152-b4f1-16de8e1a9215)


## 6.	Sequence Diagram
![image](https://github.com/AbdelrahmanMohsenMohamed1/V2V-Adaptive-Cruise-Control/assets/109293965/0dc92145-b2d7-4882-8b6c-23916a8f4680)

## 7.Testing
- gtest
- static tool analysis
- bazal

## 8.team member
name------   linkedin or github

## 9.Special Thanks

I would like to express my sincere gratitude to our instructor 
ENG.ahmed for his valuable guidance and support throughout this internship.

## 10.License
- license

## 11.References
- (References to external resources)[https://www.st.com/resource/en/datasheet/stm32f103ze.pdf]


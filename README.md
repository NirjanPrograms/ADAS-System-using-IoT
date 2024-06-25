# Advanced Driver Assistance System (ADAS) Using IoT

This focuses on developing an Advanced Driver Assistance System (ADAS) leveraging the Internet of Things (IoT) to enhance vehicle safety and connectivity. The primary objective is to create a smart car capable of maintaining a safe distance from preceding vehicles and providing real-time accident detection and email notification.

## Key Components and Features:
1. **Distance Maintenance:**
   - **HC-SR04 Ultrasonic Sensor:** Measures the distance to the vehicle ahead.
   - **Arduino Uno:** Processes sensor data to adjust the car's speed, ensuring safe following distances.

2. **Accident Detection:**
   - **Piezo Sensor:** Detects collisions or physical impacts.
   - **Buzzer:** Provides immediate audio warnings to the driver.

3. **Emergency Notification:**
   - **NEO-6M GPS Module:** Provides real-time location tracking and sent email to the registered mail id if any accident occurs.

4. **Motor and Steering Control:**
   - **L293D Motor Controller:** Controls the vehicle’s motors for movement and speed adjustment.
   - **Servo Motors:** Enable precise steering of the car.
   - **3V Batteries:** Power the motors efficiently.

5. **IoT Integration:**
   - **ESP8266 Module:** Ensures seamless communication between the Arduino Uno and IoT components, enabling real-time data transmission and control.

## System Workflow:
1. **Data Collection:** Sensors collect real-time data on vehicle distance and potential collisions.
2. **Data Processing:** Arduino Uno processes the sensor data to make decisions on speed adjustment and collision detection.
3. **Communication:** ESP8266 facilitates communication between the Arduino and IoT modules, enabling GPS tracking and Email notifications.
4. **Control:** L293D motor controller and servo motors manage the car’s movement and steering based on processed data.
5. **Emergency Response:** Upon detecting a collision, the system sends an SMS with the vehicle’s GPS coordinates to a pre-specified contact using the SIM800L module.

## Project Significance:
This project demonstrates the integration of IoT with ADAS to create a safer and more connected driving experience. It highlights the importance of proactive safety measures and quick emergency responses, paving the way for future innovations in automotive safety technology.

Overall, our project represents a significant step towards smarter, safer, and more efficient vehicles, utilizing IoT to enhance the traditional capabilities of ADAS.

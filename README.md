# FIRE DETECTION THROUGH FLAME AND GAS SENSOR

## Overview
- There is a water pump system used instead of a traditional fire extinguisher for the purpose.
- The setup involves an ESP32 microcontroller, gas sensors, a buzzer, and LED lights to provide an alarm system.
- The LED lights are color-coded: green indicates normal conditions, yellow signifies moderate levels of danger, and red alerts to extreme levels.

## Purpose of Gas and Flame Sensor in Fire Detection and Alarm
- The gas sensor is essential in our fire detection system, detecting changes in air quality like smoke or combustible gases as early warnings for fire hazards.
- The flame sensor detects flames, triggering the alarm system to alert users of potential fire outbreaks.

## Steps Involved
  - **Prepare the Environment:** Ensure the area is clear of any obstructions and that the system is powered on and ready for use.
  - **Initiate Testing:** To simulate a fire scenario, bring a lighter near the gas sensor. The system responds accordingly and cuts off as soon as the flame or gas is getting in normal condition.
  - **Response Activation:** Upon detecting the presence of the lighter's flame, the gas sensor triggers the alarm system. The buzzer will sound, and the LED lights will transition from green to red, indicating the escalation of danger. If yellow light occurs, means it is giving warning that gas is getting detected and is slowly increasing in a particular area.
  - **Prompt Action:** In response to the alarm, water pump is attached which throws water to the area where fire is detected. Apart from this, take immediate action to address the potential fire hazard. Evacuate the area if necessary and initiate appropriate fire suppression measures.

**System Reset:** After addressing the simulated fire scenario, reset the system to its initial state. Ensure all components are functioning correctly for continued readiness.

## Equipments Used
- **Arduino Microcontroller:** The Arduino microcontroller serves as the brain of the system, responsible for processing sensor data, making decisions based on programmed logic, and controlling actuators such as pumps or valves. 
- **Fire Detection Sensor:** Various types of fire detection sensors can be used, including:
  - **Flame Sensor:** Detects the presence of flames by sensing infrared light emitted by the fire.
  - **Gas Sensor:** Detects specific gases released during combustion, such as LPG, CO or CH4.
- **Water Pump:** To extinguish the fire, a water pump is used to control the flow of water. The pump can be submerged in a water reservoir.
- **Power Supply:** The system requires a stable power source to operate the Arduino board, sensors, and actuators reliably. This can be achieved using batteries, a DC power adapter, or a combination of both, depending on the application's power requirements and mobility constraints.
- **LEDs:** LEDs are required for indicating whether the connection established is in normal condition, or warning arises or in critical condition.
- **Wiring and Connectors:** Wiring and connectors are essential for interconnecting the various components of the system, including the Arduino board, sensors, actuators, and power supply.

## Application
- A flame detector is a type of sensor that can detect and respond to the presence of a flame. These detectors have the ability to identify smokeless liquid and smoke that can create open fire. For example, in boiler furnaces flame detectors are widely used, as a flame detector can detect heat, smoke, and fire.
- Gas detection is critical in facilities across all applications, ranging from food and beverage to chemical production and wastewater treatment. Gas detection systems provide continuous monitoring of toxic and combustible gases for compliance with industry and workplace safety standards.

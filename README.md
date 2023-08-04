# SolarPowered_water_level_monitoring

Description:-
This project is a solar-powered water level monitoring system designed to measure and monitor the water level in a reservoir, tank, or any water storage facility. The system utilizes various sensors and a microcontroller to collect data and controls the motor automatic.

Components:-
Water level float switch: Measures water level and transfer it to the micro-controller.
Microcontroller (ESP-WROOM32): Processes data from the sensor and controls the system's operation.
Solar Panels: Convert sunlight into electrical energy to power the system.
Battery: Stores excess solar energy for use during the night or cloudy days.
GSM(SIM800L): Enables wireless data transmission to a monitoring station.
Localhost : When it is connected to the network it creates a localhost:8080 which can also used to control the motor operation manually.

Features:-
Continuous and automated water level monitoring.
Solar-powered for sustainability and autonomy.
Wireless data transmission for remote monitoring.
Real-time alerts for critical water level thresholds.
Low power consumption for extended operation.

Code Explanation:-
Copy and upload the program into ESP-WROOM32 and open the serial monitor. In the serial monitor, you will be able to see some information like whether the WiFi is connected or not. If it is connected you will get the local IP address, here it is 192.168.1.23( This may be different for you). Note down the one that displayed on your serial monitor.


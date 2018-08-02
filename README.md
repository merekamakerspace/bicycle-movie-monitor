# bicycle-movie-monitor
Bicycle Generator Powered Movie Playing System

An bicycle generator is connected to a bank of ultra capacitors
An Arduino reads the voltage level of the caps and enables a Buck/Boost Converter powering an inverter
An LCD monitor is plugged into the monitor and a Raspberry Pi

An Openframeworks app runs on the Raspberry Pi to read the voltage values from the Arduino over serial and displays a Battery indicator on the monitor
When the capacitors are at around 10V or 100% according to the display then a movie is played.





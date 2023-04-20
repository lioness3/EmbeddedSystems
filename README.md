# EmbededSystems
SNHU course project for EMERGING SYSTEMS 

Thermostat project:

This project uses a TI board to create a thermostat. The thermostat is adjusted using an up and down button to change the set point for the desired temperature. Then, the temperature sensor is read from the board and an LED light is either turned on or off depending on the current state of the program. If the set point is lower than the room temperature, the light is turned off. If the set point is higher, the light is ON to replicate a heater.
The use of multiple peripherals is something I consider noteworthy(Something I did well). The Timer and the usleep() function are tools/resources that I have gained from this project.The comments are very well documented, making this code readable and adaptable. Refactoring this code is something that could be improved. Overall, the use of GPIO, UART, I2C and Timer are all valuable skills gained from this project and can be confidently carried over to future projects. 

Morse Code: 

This project flashes ‘SOS’ in morse code using two lights until a button is pressed. Then, the board flashes a different light to signal ‘OK.’
This project instilled how to implement States and SM in C(Something I did well). This was a great improvement from a previous project. The tools/ resources I gained in this project was improving the ability to parse through the TI user manual. The comments are very well documented, making this code readable and adaptable. Refactoring this code is something that could be improved. Overall, the use of GPIO,and SM are valuable skills gained from this project and can be confidently carried over to future projects. 

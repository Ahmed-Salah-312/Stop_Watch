# Stop_Watch
# Implementing the following Stop Watch system with the specifications listed below:
1. Using an ATmega32 Microcontroller with a frequency of 1 MHz
2. Configuring Timer1 in the ATmega32 with CTC mode to count the stopwatch time
3. Using six Common Anode 7-segments.
4. Connecting the six 7-segments in the project using the multiplexed technique using one 7447 decoder for all 7-segments and controlling the enable/disable for 
Each 7-segement using an NPN BJT transistor connects to one of the MCU pins.
5. Connecting the 7447 decoder 4-pins to the first 4-pins in PORTC
6. Using the first 6 pins in PORTA as the enable/disable pins for the six 7-segments.
7. Stopwatch counting should start once the power is connected to the MCU.
8. Configuring External Interrupt INT0 with a falling edge. Connecting a push button to the 
internal pull-up resistor. If a falling edge is detected, the stopwatch time should be
reset.
9. Configuring External Interrupt INT1 with a raised edge. Connecting a push button with the 
external pull-down resistor. If a rising edge is detected, the stopwatch time should be
paused.
10. Configuring External Interrupt INT2 with a falling edge. Connecting a push button with the 
internal pull-up resistor. If a falling edge is detected, the stopwatch time should be
resumed.

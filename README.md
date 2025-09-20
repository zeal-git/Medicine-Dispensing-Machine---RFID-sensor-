# Medicine-Dispensing-Machine---RFID-sensor
This project resembles automatic medicine dispensing system that uses RFID sensing and servo motors to provide safe and control access of medicines to prevent contamination. The system allows only authorized person to have controlled access to medicines, therefore reduces chances of misuse. 

Working:
1. RFID module (RC522) reads card/rfid tag by user
2. Each RFID card is mapped to one or more specific medicine compartments
3. When authorized card is detected, the corresponding servo motor rotates to open the medicine compartment for fixed duration
4. After delay, the servo returns to its original locked position
5. If unknown card is scanned, the system denies access

Components:
1. ESP8266 (NodeMCU) - control and logic processing
2. RFID SENSOR (RC522) - Reader for user authentication
3. RFID Tags/Cards - user identifiers
4. Servo Motors - control medicine compartments
5. Power Supply - NodeMCU and servos 

# iot
This is code is for controlling the home appliances using node mcu and gsm module.
Gsm module is connected to the arduino uno and the outputs of the arduino are connected to the node mcu we are using blink app
We are using 5v relays which are connected to d7 and d8 of node mcu 
a buzzer which is connected to d4 
the buzzer is used as alaram and where we input time through terminal in blynk app which is connected to the virtual pin v2
The outputs of the arduino are connected at d5 and d6 to the node mcu 
the final outputs d7 and d8 are conneced to the arduino at digital pins 5 and 6 which acts as feedback i.e when there is any change u=in the state of applience the message is sent to the user

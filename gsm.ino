#include <SoftwareSerial.h>
SoftwareSerial mySerial(9, 10);
String textMessage_1;
const int led1 = 5; //If you're using a relay to switch, if not reverse all HIGH and LOW on the code
const int led2 = 6;
int pre1, pre2, pres2;
int pres1 = pre1 = pre2 = pres2 = LOW;
void func(String textMessage)
{
  if (textMessage.indexOf("8328220800") > 0) {
    if (textMessage.indexOf("ON1") > 0)
    {
      Serial.println("Works");
      analogWrite(led1, 255);

    }
    if (textMessage.indexOf("OFF1") > 0)
    {
      Serial.println("Works");
      digitalWrite(led1, LOW);
    }

    if (textMessage.indexOf("ON2") > 0)
    {
      Serial.println("Works");
      analogWrite(led2, 255);
    }
    if (textMessage.indexOf("OFF2") > 0)
    {
      Serial.println("Works");
      digitalWrite(led2, LOW);
    }
    delay(10);
  }
}





void setup() {


  Serial.begin(9600);
  mySerial.begin(2400);
  Serial.println("Initializing...");
  delay(1000);
  mySerial.println("AT"); //Once the handshake test is successful, it will back to OK
  updateSerial();
  mySerial.println(" AT+CMEE=2");
  updateSerial();

  //updateSerial();
  mySerial.println("AT+CMGF=1"); // Configuring TEXT mode
  updateSerial();
  mySerial.println("AT+CNMI=1,2,0,0,0"); // Decides how newly arrived SMS messages should be handled
  updateSerial();
  pinMode(led1, OUTPUT);
  digitalWrite(led1, LOW); // The current state of the light is ON
  pinMode(led2, OUTPUT);
  digitalWrite(led2, LOW);
  pinMode(7, INPUT);
  pinMode(8, INPUT);

}

void loop() {
  updateSerial();
  pres1 = digitalRead(7);
  pres2 = digitalRead(8);
  if (pre1 != pres1)
  {
    if (pres1 == HIGH)
    {

      Serial.println("Led1 is HIGH");



      mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode

      delay(50);  // Delay of 5000 milli seconds or 1 second

      mySerial.println("AT+CMGS=\"+918277795414\"\r"); // Replace x with mobile number

      delay(50);

      mySerial.println("LED1 is HIGH");// The SMS text you want to send

      delay(50);

      mySerial.println((char)26);// ASCII code of CTRL+Z

      delay(50);


    }
    else if (pres1 == LOW)
    {

      Serial.println("Led1 is LOW");



      mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode

      delay(50);  // Delay of 5000 milli seconds or 1 second

      mySerial.println("AT+CMGS=\"+918277795414\"\r"); // Replace x with mobile number

      delay(50);

      mySerial.println("LED1 is LOW");// The SMS text you want to send

      delay(50);

      mySerial.println((char)26);// ASCII code of CTRL+Z

      delay(50);

    }
    pre1 = pres1;
  }
  if (pre2 != pres2)
  {
    if (pres2 == HIGH)
    {
      //digitalWrite(led2,HIGH);
      Serial.println("Led2 is HIGH");



      mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode

      delay(50);  // Delay of 5000 milli seconds or 1 second

      mySerial.println("AT+CMGS=\"+918277795414\"\r"); // Replace x with mobile number

      delay(50);

      mySerial.println("LED2 is HIGH");// The SMS text you want to send

      delay(50);

      mySerial.println((char)26);// ASCII code of CTRL+Z

      delay(50);

    }
    else if (pres2 == LOW)
    {

      Serial.println("Led2 is LOW");




      mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode

      delay(5000);  // Delay of 5000 milli seconds or 1 second

      mySerial.println("AT+CMGS=\"+918277795414\"\r"); // Replace x with mobile number

      delay(50);

      mySerial.println("LED2 is LOW");// The SMS text you want to send

      delay(50);

      mySerial.println((char)26);// ASCII code of CTRL+Z

      delay(50);


    }
    pre2 = pres2;
  }
}

void updateSerial()
{
  delay(50);
  while (Serial.available())
  {
    mySerial.write(Serial.read());//Forward what Serial received to Software Serial Port
  }
  while (mySerial.available())
  {
    Serial.write(mySerial.read());//Forward what Software Serial received to Serial Port

    textMessage_1 = mySerial.readString();
    Serial.print(textMessage_1);
    func(textMessage_1);
    delay(50);

  }
}

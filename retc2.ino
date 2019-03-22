
#include <SPI.h>
#include <Ethernet.h>
int x = 1; int y = 0;
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <TimeLib.h>
#include <WidgetRTC.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define OLED_ADDR   0x3C
String state = "OFF",lednum = "L";

String currentTime, currentTime1;
String str;
int time2 = 0, time1 = 0;
String l;
String ls;
String f;
String fs;
int pre1=0;
int pre2=0;
int pre3;
int pre4;
int pres1;
int pres2;
int pres3;
int pres4;
int i = 0;
int pre7 = LOW;
int pre8 = LOW;
int pres7 = LOW;
int pres8 = LOW;
int cled1 = D5;
int cled2 = D6;
int oled1 = D7;
int oled2 = D8;
int buzzer=D4;
String prev = " ";
String pres = " ";
WidgetTerminal terminal(V2);

Adafruit_SSD1306 display(-1);
char auth[] = "3b0b8ed9b14642d2b79a262057abe941";
char ssid[] = "mfg";
char pass[] = "aravind123";
BlynkTimer timer;

WidgetRTC rtc;
WidgetLCD lcd(V1);
void clockDisplay()
{ currentTime = String(hour()) + ":" + minute() + ":" + second();
  Blynk.virtualWrite(V0, currentTime);
  currentTime1 = String(hour()) + ":" + minute();
  alram();
  lcd.clear();

}
void alram()
{
  if (str == currentTime1)
  { Serial.println("high");
    digitalWrite(buzzer,HIGH);
    
  }
  else if (str == "remove" || str != currentTime1)
  {
    digitalWrite(buzzer,LOW);
    Serial.println("low");
  }
}
BLYNK_WRITE(V2)
{
  str = param.asStr();
  if (String("checking") == param.asStr())
  {
    Serial.println(str);
    terminal.println("You said: 'checking'") ;
    terminal.println("I said: 'working fine'") ;
  } else {

    // Send it back
    terminal.print("You said:");
    terminal.write(param.getBuffer(), param.getLength());
    terminal.println();
  }

  // Ensure everything is sent
  terminal.flush();
}
BLYNK_WRITE(V3)
{
  pres1 = param.asInt(); // assigning incoming value from pin V1 to a variable

  // process received value
}
BLYNK_WRITE(V4)
{
  pres2 = param.asInt(); // assigning incoming value from pin V1 to a variable

  // process received value
}
void check()
{ pres3 = digitalRead(cled1);
Serial.println(digitalRead(cled1));
  pres4 = digitalRead(cled2);
  if (pre1 != pres1 || pre3 != pres3)
  { if (pre1 != pres1)
    { digitalWrite(oled1, pres1);
      Serial.println("pres1");
    }
    if( pre3 != pres3){
      Serial.println("pres3");
      digitalWrite(oled1, pres3);
    }
  }
  if (pre2 != pres2 || pre4 != pres4)
  { if (pre2 != pres2)
    { digitalWrite(oled2, pres2);
      Serial.println("pes2");
    }
    if( pre4 != pres4){
      Serial.println("pres4");
      digitalWrite(oled2, pres4);
    }
  }
  pre1 = pres1;
  pre2 = pres2;
  pre3 = pres3;
  pre4 = pres4;

}

void dis() {
  Serial.println(currentTime1);
  if (digitalRead(oled1) == 0)
  { f = "Off";
    fs = "on";
  }
  else {
    f = "on";
    fs = "off";
  }
  if (digitalRead(oled2) == 0)
  { l = "Off";
    ls = "on";
  }
  else {
    l = "on";
    ls = "off";
  }
  display.clearDisplay();
  display.display();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(10, 0);
  display.print("Time: ");
  display.print(currentTime);
  display.setCursor(10, 10);
  display.print("Last:");
 // display.print(" ");
  display.print(lednum);
  display.print(" ");
  display.print(state);
  display.setCursor(10, 20);
  display.print("Pres:");
  display.print(" L:");
  display.print(l);
  display.print(" F:");
  display.print(f);
  display.display();
  pres = "Pres:L:" + l + ":F " + f;
  prev = "Last:" + lednum + "-"+ state;
  lcd.print(0, 0, pres);
  lcd.print(0, 1, prev);

}

void func()
{

pres7 = digitalRead(oled1);
pres8 = digitalRead(oled2);
if(pre7 != pres7)
{ 
  lednum = "F";
  if(pres7 == HIGH)
  {
  state = "ON";
  }
  else
  {  
  state = "OFF";
  }
pre7 = pres7;
  

}
if(pre8 != pres8)
{
  //Change
  
  lednum = "L";  if(pres8 == HIGH)
  {
  state = "ON";
  
  }
  else
  {
    state = "OFF";
  }
  pre8 = pres8;
  
  
}

}
void setup()
{ pinMode(cled1, INPUT);
  pinMode(cled2, INPUT);
  pinMode(oled1, OUTPUT);
  pinMode(oled2, OUTPUT);
  digitalWrite(oled1,LOW);
  digitalWrite(oled2,LOW);
  pinMode(buzzer,OUTPUT);
  digitalWrite(buzzer,LOW);
  Serial.begin(9600);
  
  Blynk.begin(auth, ssid, pass);
  rtc.begin();
  terminal.clear();

  // This will print Blynk Software version to the Terminal Widget when
  // your hardware gets connected to Blynk Server
  terminal.println(F("hello users"));
  terminal.println(F("-------------"));
  terminal.println(F("input time in 24 hr format to set an alaram"));
  terminal.println(F("type remove to remove the alarm"));
  terminal.flush();
  timer.setInterval(1000L, clockDisplay);
  display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(10, 0);
  display.print("hello users");
  lcd.clear();
  display.display();
  pre3 = digitalRead(cled1);
  
  pre4 = digitalRead(cled2);
  
}

void loop()
{
  Blynk.run();
  timer.run();
  func();
  dis();
  check();
}

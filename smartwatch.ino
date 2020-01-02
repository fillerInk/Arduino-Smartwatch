/*
 This is the version with the HC-05 bluetooth module
 RTC is not used
*/

#include <AltSoftSerial.h>

AltSoftSerial ASSserial; 

#include<SPI.h>
#include<Wire.h>
#include<Adafruit_GFX.h>
#include<Adafruit_SSD1306.h>


Adafruit_SSD1306 oled;

int pwm = 3; 

void setup() {
 
 ASSserial.begin(9600);  
 pinMode(pwm,OUTPUT);

 oled.begin(SSD1306_SWITCHCAPVCC);
 oled.clearDisplay();
 oled.setTextColor(WHITE);
 oled.setTextSize(1);

}



void loop() {

  oled.clearDisplay();
  
 if (ASSserial.available())
 {
   String myTime = ASSserial.readStringUntil('|');
   ASSserial.read();

    String myDate = ASSserial.readStringUntil('\n');
    ASSserial.read();
     
    String myPhone = ASSserial.readStringUntil('\n');
    
  
    if(myTime.indexOf('time') >= 0)
    {
      oled.setCursor(2,5);  
      oled.clearDisplay();
      oled.print("Error - Data not Recieved");
      oled.display();
    }
    else
    { 
      oled.setTextSize(2);
      oled.setCursor(5,5);
      oled.print(myTime);
      oled.display();
    }

    if(myDate.indexOf('date') >=0)
    {
      oled.setCursor(20,25);
      oled.println("Data not reecieved");
    }
    else{
      oled.setTextSize(1);
      oled.setCursor(20,25);
      oled.print(myDate );
      oled.display();
    }
 
    if(myPhone.indexOf('phone') >= 0)
   { 
      digitalWrite(pwm, LOW);
   }
   else
   {

     oled.clearDisplay();
      oled.setCursor(10,0);
      oled.setTextSize(2);
      oled.println(myPhone);
      oled.setTextSize(1);
      oled.setCursor(10,22);
      oled.println("Calling...");
      oled.display();
      delay(5000);
      
        
    // Motor Vibration Pattern
    digitalWrite(pwm, HIGH);
    delay(500);
    digitalWrite(pwm, LOW);
    delay(500); 

   } 

 }
 
}

 

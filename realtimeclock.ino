/* 
  This version uses a Real Time Clock (RTC) module to keep time
  No bluetooth support or connectivity to phone
*/  
    
    #include<Wire.h>
    #include<Adafruit_GFX.h>
    #include<Adafruit_SSD1306.h>

    #define DS1307_ADDRESS 0x68

    byte read_second;
    byte read_minute;
    byte read_hour;
    byte read_day;
    byte read_date;
    byte read_month;
    byte read_year;

     const char *dayname[7] = {
       "Sun","Mon","Tue","Wed","Thu","Fri",”Sat”
      };


    byte binary_to_decimal(byte val)
    { 
        return((val/16*10)+(val%16));
    }

    byte decimal_to_binary(byte val)
    { 
       return((val/10*16)+(val%10));
    }

    #define OLED_RESET 4

    Adafruit_SSD1306  oled(OLED_RESET);

    void setup() {
 
        Wire.begin();
        Wire.beginTransmission(DS1307_ADDRESS);
        Wire.write(0);
        Wire.endTransmission();

        oled.begin(SSD1306_SWITCHCAPVCC);
        oled.clearDisplay();
        oled.setTextColor(WHITE);
        oled.setTextSize(1);
        oled.setFontSize(1);
 
}



     void loop() {
 
          Wire.requestFrom(DS1307_ADDRESS,7);

          read_second = binary_to_decimal(Wire.read());
          read_minute = binary_to_decimal(Wire.read());
          read_hour = binary_to_decimal(Wire.read());
          read_day = binary_to_decimal(Wire.read());
          read_date = binary_to_decimal(Wire.read());
          read_month = binary_to_decimal(Wire.read());
          read_year = binary_to_decimal(Wire.read());

          oled.clearDisplay();

          oled.setCursor(20,5);
          oled.setTextSize(2);
          oled.println(read_hour);

          oled.setCursor(43,5);
          oled.println(":");

          oled.setCursor(55,5);
          oled.println(read_minute);

          oled.setCursor(80,5);
          oled.println(":");

         oled.setCursor(89,5);
         oled.println(read_second);

         oled.setTextSize(1);
         oled.setCursor(22,25);
         oled.println(read_date);

         oled.setCursor(37,25);
         oled.println("-");

         oled.setCursor(46,25);
         oled.println(read_month);

         oled.setCursor(54,25);
         oled.println("-");

         oled.setCursor(62,25);
         oled.println(read_year);

         oled.setCursor(90,25);
         oled.println(dayname[read_day]);

         oled.display();
 
         delay(1000);  //waits for one second before refreshing

}


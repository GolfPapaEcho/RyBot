#include <LiquidCrystal.h>

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
void setup() {
  // put your setup code here, to run once:
//Set lcd rows and  columns
lcd.begin(16, 2);

}

void loop() {
  // put your main code here, to run repeatedly:

  for(int i = 0; i < 3; i++)
  {lcd.setCursor(0,0);
   lcd.print("You paint your love upon this world.");
   delay(1000);
    for(int positionCounter = 0; positionCounter < 62; positionCounter++){
    lcd.scrollDisplayLeft();
    delay(200);
    }
    lcd.clear();
  }
lcd.clear();
lcd.setCursor(0,0);
lcd.print("Love from");
lcd.setCursor(1,4);
lcd.print("Michael x");
delay(3000);
lcd.clear();
}

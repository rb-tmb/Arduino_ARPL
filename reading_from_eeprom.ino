#include <EEPROM.h>
int address = 0;
int value;
void setup() {
  Serial.begin(9600);
}

void loop() {
  value = EEPROM.read(address);
  if(value!=0)
  {
    Serial.print(address);
    Serial.print("\t");
    Serial.print(value, DEC);
    Serial.println();
  }
  if(address==EEPROM.length())
  {
    exit(0);
  }
  address = address + 1;
}

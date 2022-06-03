#include <EEPROM.h>
int address = 0;
int value;
int t1;
bool ee_flag = 1;
bool sflag=0;
bool cflag = 1;
float charg_time = 0;
void setup() {
  pinMode(2,INPUT_PULLUP);
  pinMode(13,OUTPUT);
  Serial.begin(9600);
  for(int i=0;i<EEPROM.length();i++)
  {
    value = EEPROM.read(i);
    if(value!=0)
    {
      Serial.print(i);
      Serial.print("\t");
      Serial.print(value, DEC);
      Serial.println();
    }
    else if(value==0)
    {
      address=i;
      ee_flag = 0;
      break;
    }
  }
  if(ee_flag==1)
  {
    erase_eeprom();
  }
  Serial.println("Program Started");
}

void loop() {
  int led_signal = digitalRead(2);
  if(led_signal==0 && sflag==0)
  {
    Serial.println("Started Charging!!");
    t1 = millis();
    sflag=1;
    tone(13, 500, 1000);
  }
  else if(led_signal==1 && sflag==1)
  {
    int t2 = millis();
    int t_now = millis();
    cflag = 1;
    delay(1000);
    while((t_now-t2)<30000)
    {
      Serial.println("Checking if charging is done");
      led_signal = digitalRead(2);
      if(led_signal==0)
      {
        cflag=0;
        delay(50);
        Serial.println("No just noise.... Continue Charging.....");
        break;
      }
      t_now = millis();
    }
    if(cflag==1)
    {
      Serial.println("Charging Done");
      charg_time = (millis()-t1)/1000 - 30.0;
      charg_time = charg_time/60;
      Serial.print("Chargin Time: ");
      Serial.print(charg_time);
      Serial.println("mm");
      EEPROM.write(address, charg_time);
      Serial.println("Writing to EEPROM....");
      address=address+1;
      sflag=0;
      ring_the_bell();
    }
  }
  delay(2000);
}
void erase_eeprom()
{
  for(int i=0;i<EEPROM.length();i++)
  {
    EEPROM.write(i, 0);
  }
}
void ring_the_bell()
{
  for(int i=0;i<3;i++)
  {
    tone(13, 1000); // Send 1KHz sound signal...
    delay(1000);        // ...for 1 sec
    noTone(13);     // Stop sound...
    delay(1000);        // ...for 1sec
  }
}

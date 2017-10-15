#define digitalWrite(...) analogWrite(__VA_ARGS__)
#define HIGH 255
#define LOW 0
#define ONLEDS 16

typedef struct {
    uint16_t pinNum;
    bool pinUSE = false;
    bool pinON = false;
    bool refresh = false;
    uint8_t level = LOW;
    
} pinLevels;

int REG[] = {0xFFFE,0x00,0x00};

pinLevels digitPins[ONLEDS];

void setup() {
  Serial.begin(115200);
  digitPins_setOut(0xFFFF);
}

void loop() {
  //if (Serial.available()){
  //  digitPins_setState(Serial.readString().toInt(),255);
  //}
  delay(300);  
  //refresh();
}

void digitPins_setOut(int onPins){
  char texto[50];
  Serial.println("LEDS");
  for (int i = 0 ;i<=ONLEDS;i++)
  {
      digitPins[i].pinNum = i+1;
      if (onPins & (1<<i))
      {
         digitPins[i].level = LOW;
         digitPins[i].pinUSE = true;
         digitPins[i].pinON = false;
         sprintf(texto,"Pin %d se usa como salida",digitPins[i].pinNum);
         Serial.println(texto);
         pinMode(digitPins[i].pinNum,OUTPUT);
      }else
      {
        digitPins[i].level = LOW;
        digitPins[i].pinUSE = false;
        digitPins[i].pinON = false;
      }
  }
}

void digitPins_setState(int onPins,bool state){
  for (int i = 0 ;i<=ONLEDS;i++)
  {
      if (onPins & (1<<i))
      {
         digitPins[i].pinON = state;
         digitPins[i].refresh = true;
      }
  }
}

void digitPins_setLevel(int level){
  for (int i = 0 ;i<=ONLEDS;i++)
  {
      if (digitPins[i].pinON)
      {
         digitPins[i].level = level;
      }
  }
}

void refresh(){
  for (int i = 0 ;i<=ONLEDS;i++)
  {
      if (digitPins[i].pinUSE && digitPins[i].pinON && digitPins[i].refresh)
      { 
         digitPins[i].refresh = false;
         Serial.print("Se enciende el led ");
         Serial.println(digitPins[i].pinNum);
         digitalWrite(digitPins[i].pinNum,digitPins[i].level);
      }
      else
      { 
         if (digitPins[i].pinUSE && digitPins[i].refresh)
         {
            digitPins[i].refresh = false;
            digitalWrite(digitPins[i].pinNum,LOW);
         }
      }
  }
}

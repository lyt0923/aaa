#include<DHT.h>
#include <IRremote.h>
#include <DHT_U.h>
#include"U8glib.h"  
U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE);
#define DHTPIN A0
#define DHTTYPE DHT11
DHT dht(A0,DHT11);
IRrecv irrecv(12);
decode_results results;
static unsigned char bitmap[] U8G_PROGMEM = {
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x07,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF8,0x00,0x00,0x7F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xE0,0x00,0x00,0x1F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x80,0x00,0x00,0x07,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,0x00,0x00,0x00,0x01,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xF8,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xF0,0x00,0xFF,0xFE,0x00,0x7F,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xE0,0x0F,0xFF,0xE0,0x00,0x3F,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xC0,0x3F,0xFF,0x00,0x00,0x0F,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0x80,0x7F,0xFC,0x00,0x00,0x0F,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0x01,0xFF,0xF0,0x00,0x00,0x07,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFE,0x03,0xFF,0xC0,0x00,0x00,0x03,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFE,0x07,0xFF,0x80,0x00,0x00,0x01,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFC,0x07,0xFE,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xF8,0x07,0xFC,0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xF8,0x03,0xF8,0x00,0x00,0x00,0x00,0x7F,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xF0,0x01,0xF0,0x00,0x00,0x00,0x00,0x7F,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xF0,0x00,0xF0,0x3E,0x00,0x00,0x00,0x3F,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xE0,0x00,0xE1,0xF0,0x00,0x00,0x00,0x3F,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xE0,0x00,0xC3,0xC0,0x01,0xC0,0x00,0x1F,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xE0,0x00,0xC7,0x00,0x0F,0xF0,0x00,0x1F,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xC0,0x40,0x8E,0x00,0x1F,0xFC,0x01,0x1F,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xC0,0xC1,0x9C,0x00,0x3F,0xFF,0x03,0x1F,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xC1,0xC1,0x98,0x00,0x7F,0xFF,0xFF,0x0F,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xC3,0x03,0x18,0x00,0xFF,0xFF,0xFE,0x0F,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xC6,0x07,0x18,0x01,0x80,0x7F,0xFE,0x0F,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0x8E,0x0F,0x1C,0x02,0x00,0x1F,0xFC,0x0F,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0x8F,0x1F,0x9C,0x04,0x00,0x0F,0xF8,0x0F,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0x83,0x7F,0x9E,0x0C,0x00,0x07,0xE0,0x0F,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0x82,0x3F,0x8F,0xCF,0xF0,0x00,0x00,0x0F,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0x84,0x0F,0xE7,0xF8,0xFC,0x00,0x00,0x0F,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0x88,0x00,0x00,0x0C,0x7E,0x00,0x00,0x0F,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0x90,0x00,0x00,0x0C,0x3E,0x00,0x00,0x0F,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xC0,0x00,0x00,0x0C,0x1F,0x00,0x00,0x0F,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xC0,0x00,0x00,0x0C,0x1F,0x00,0x00,0x0F,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xC0,0x00,0x00,0x1C,0x0F,0x80,0x00,0x0F,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xC0,0xEA,0xEE,0x1C,0x0F,0xC0,0x20,0x1F,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xC0,0xAA,0xA4,0x1C,0x0F,0xF0,0xC0,0x1F,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xE0,0xEA,0xC4,0x3C,0x07,0xFF,0x80,0x1F,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xE0,0xAA,0x84,0x3C,0x03,0xFF,0x80,0x3F,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xF0,0xE4,0x84,0x3C,0x03,0xFE,0x00,0x3F,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xF0,0x00,0x00,0x3C,0x00,0xF8,0x00,0x3F,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xF0,0x00,0x00,0x3C,0x00,0x00,0x00,0x7F,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xF8,0x00,0x00,0x7C,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFC,0x00,0x00,0x7E,0x00,0x00,0x00,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFC,0x00,0x00,0x7E,0x00,0x00,0x01,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFE,0x00,0x00,0x7F,0x00,0x01,0x01,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x3F,0x80,0x02,0x03,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0x80,0x00,0x3F,0xC0,0x0E,0x07,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0x80,0x00,0x1F,0xF0,0x3C,0x0F,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xE0,0x00,0x1F,0xFF,0xF8,0x1F,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xF0,0x00,0x0F,0xFF,0xF0,0x3F,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xF8,0x00,0x07,0xFF,0xE0,0x7F,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFC,0x00,0x01,0xFF,0x01,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x03,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xC0,0x00,0x00,0x0F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF0,0x00,0x00,0x3F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,0x00,0x01,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xE0,0x3F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF
};

void draw2(void) {u8g.drawXBMP(0,0,128,64,bitmap);
  }
void draw(void)
{
  float t=dht.readTemperature();
  float h=dht.readHumidity();
  u8g.setFont(u8g_font_unifont);
  u8g.setPrintPos(0,60);
  u8g.print("T:");
  u8g.setPrintPos(70,60);
  u8g.print(t);
  u8g.setFont(u8g_font_unifont);
  u8g.setPrintPos(0,20);
  u8g.print("H:");
  u8g.setPrintPos(70,20);
  u8g.print((float)h);
}

void setup()
{
  Serial.begin(9600);
  dht.begin();
  for(int x=2;x<12;x++)
  {
     
    pinMode(x,OUTPUT);
    digitalWrite(x,LOW);
  }
  irrecv.enableIRIn();
  pinMode(13,OUTPUT);
  
 
}
void loop()
{  
  
  {
    if(results.value==0x1FE48B7)
    {digitalWrite(13,HIGH);
       u8g.firstPage();
        do{
         draw();
           }while(u8g.nextPage());
    }
    else if(results.value==0x1FE807F)
    {
      digitalWrite(13,LOW);
      u8g.firstPage();
      do{
        draw2();
        }while(u8g.nextPage());
      }
  }
   if (irrecv.decode(&results)) 
   {Serial.println(results.value, HEX);
   irrecv.resume(); 
   }

  float t=dht.readTemperature();
  float h=dht.readHumidity();
const double baselinetemp=12;
const double baselinehumi=20;
   
  if(t<baselinetemp)
{
  digitalWrite(2,LOW);
  digitalWrite(3,LOW);
  digitalWrite(4,LOW);
  digitalWrite(5,LOW);
  digitalWrite(6,LOW);
}
else if(t>=baselinetemp&&t<baselinetemp+1)
{
   digitalWrite(2,HIGH);
  digitalWrite(3,LOW);
  digitalWrite(4,LOW);
  digitalWrite(5,LOW);
  digitalWrite(6,LOW);
}
else if(t>=baselinetemp+1&&t<baselinetemp+2)
{  digitalWrite(2,HIGH);
  digitalWrite(3,HIGH);
  digitalWrite(4,LOW);
  digitalWrite(5,LOW);
  digitalWrite(6,LOW);
}
else if(t>=baselinetemp+2&&t<baselinetemp+3)
{  digitalWrite(2,HIGH);
  digitalWrite(3,HIGH);
  digitalWrite(4,HIGH);
  digitalWrite(5,LOW);
  digitalWrite(6,LOW);
}
else if(t>=baselinetemp+3&&t<baselinetemp+4)
{  digitalWrite(2,HIGH);
  digitalWrite(3,HIGH);
  digitalWrite(4,HIGH);
  digitalWrite(5,HIGH);
  digitalWrite(6,LOW);
}
else if(t>=baselinetemp+4)
{  digitalWrite(2,HIGH);
  digitalWrite(3,HIGH);
  digitalWrite(4,HIGH);
  digitalWrite(5,HIGH);
  digitalWrite(6,HIGH);
}
/*digitalWrite(7,HIGH);
  digitalWrite(8,HIGH);
  digitalWrite(9,HIGH);
  digitalWrite(10,HIGH);
  digitalWrite(11,HIGH);*/


if(h<baselinehumi)
{
  digitalWrite(7,LOW);
  digitalWrite(8,LOW);
  digitalWrite(9,LOW);
  digitalWrite(10,LOW);
  digitalWrite(11,LOW);
}
else if(h>=baselinehumi&&h<baselinehumi+10)
{
   digitalWrite(7,HIGH);
  digitalWrite(8,LOW);
  digitalWrite(9,LOW);
  digitalWrite(10,LOW);
  digitalWrite(11,LOW);
}
else if(h>=baselinehumi+10&&h<baselinehumi+20)
{  digitalWrite(7,HIGH);
  digitalWrite(8,HIGH);
  digitalWrite(9,LOW);
  digitalWrite(10,LOW);
  digitalWrite(11,LOW);
}
else if(h>=baselinehumi+20&&h<baselinehumi+30)
{  digitalWrite(7,HIGH);
  digitalWrite(8,HIGH);
  digitalWrite(9,HIGH);
  digitalWrite(10,LOW);
  digitalWrite(11,LOW);
}
else if(h>=baselinehumi+30&&h<baselinehumi+50)
{  digitalWrite(7,HIGH);
  digitalWrite(8,HIGH);
  digitalWrite(9,HIGH);
  digitalWrite(10,HIGH);
  digitalWrite(11,LOW);
}
else if(h>=baselinehumi+50)
{  digitalWrite(7,HIGH);
  digitalWrite(8,HIGH);
  digitalWrite(9,HIGH);
  digitalWrite(10,HIGH);
  digitalWrite(11,HIGH);
}
delay(1000);

}


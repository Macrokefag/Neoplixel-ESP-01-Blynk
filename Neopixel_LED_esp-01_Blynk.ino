#include <ESP8266WiFi.h> // esp könyvtát
#include <BlynkSimpleEsp8266.h> // blynk könyvtáár
#include <FastLED.h> // led könyvtár

CRGB leds[12]; //ledek száma 0-12 tehát 13db

char auth[] = "b2cf547cd08ad409f9fe13f53dcdbc6fa";
char ssid[] = "BTHub6-N6F5";
char pass[] = "49WxGxbtwaYd";

BlynkTimer timer;

int R=255; // piros
int G=255; // zöld
int B=255; // kék
int V=255; // fényeréö
int K; // kapcsolo per pill nemhasználva
byte f; // segéd változo a álltalános for ciklushoz
int r=255; //segéd piros
int g=255; //segéd zöld
int b=255; // segéd kék
int v=100; //segéd fényerö
int M=1; // váltó kapcsoló 
int I=5; //idö a villogáshoz 
int i; // segéd az idözítéshez  MOST nem használt
unsigned long t; // segéd az idözítéshez a fedélzeti idöhöz 
byte kap=0; // segéd az idözités hez ha 1 akkor mehet a változás
int vol; // segéd a fényerö grafikonhoz h ha kikap akkor 0 mutasson 

BLYNK_WRITE(V1){r = param.asInt();} // red
BLYNK_WRITE(V2){g = param.asInt();} //grean
BLYNK_WRITE(V3){b = param.asInt();} //blue
BLYNK_WRITE(V4){v = param.asInt();V=map(v,0,100,0,255);} // fényerö
BLYNK_WRITE(V5){K = param.asInt();} //kapcsolo per pill nemhasznált
BLYNK_WRITE(V6){M = param.asInt();} // funkcio kapcsolo
BLYNK_WRITE(V7){I = param.asInt();I=I*100;} // idözitö 

 
void setup(){
delay(2000); //valami miatt kell a LED könyvtát hoz
Blynk.begin(auth, ssid, pass); // kapcsolodik
timer.setInterval(1000L, myTimerEvent); // blynk timer 
FastLED.addLeds<WS2812,2, RGB>(leds,12); //LED setup pin2 és 12 (13) db led
 
Blynk.virtualWrite(V1,R); // led maxira
Blynk.virtualWrite(V2,G); // led maxira
Blynk.virtualWrite(V3,B); // led maxira
Blynk.virtualWrite(V6,1); // üzemmod kapcsolo OFF ra kapcsol 
t=millis();
  
}
 
void loop()
{
if (t<millis()) {t=millis()+I; kap=1;} else {kap=0;} 
Blynk.run();
timer.run();
switch(M) // üzem mod elágazások 
{
case 1: ki(); vol=0; break;
case 2: be(); vol=v;break;
case 3: vol=v;if (kap==1){rnd1();} break;
case 4: vol=v;if (kap==1){rnd2();} break;
case 5: vol=v;if (kap==1){rnd3();} break;
default: ki(); vol=0;break;
}
}

void ki()
{
for(f= 0;f < 12;f++)
{leds[f]=CRGB::Black;
FastLED.show();}
}

void be()
{
G=map(r,0,255,0,V);
R=map(g,0,255,0,V);
B=map(b,0,255,0,V);
for(f= 0;f < 12;f++){
leds[f].setRGB(R,G,B);
FastLED.show();}
}


void rnd1()
{
G=random(V);
R=random(V);
B=random(V);
for(f= 0;f < 12;f++){
leds[f].setRGB(R,G,B);
FastLED.show();}  

}

void rnd2()
{
for(f= 0;f < 12;f++){
G=random(V);
R=random(V);
B=random(V);  
leds[f].setRGB(R,G,B);
FastLED.show();}
}

void rnd3()
{  
for(f= 0;f < 12;f++){leds[f]=CRGB::Black;FastLED.show();} //ledek ki kapcs
G=random(V);
R=random(V);
B=random(V);
f=random(12);
leds[f].setRGB(R,G,B);FastLED.show();
}

void myTimerEvent()
{
Blynk.virtualWrite(V0,millis()/1000);
Blynk.virtualWrite(V11,map(R,0,255,0,100));
Blynk.virtualWrite(V12,map(G,0,255,0,100));
Blynk.virtualWrite(V13,map(B,0,255,0,100));
Blynk.virtualWrite(V14,vol); 
//Blynk.virtualWrite(V15,kap);
}

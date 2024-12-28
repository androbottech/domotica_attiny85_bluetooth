#include <SoftwareSerial.h>   // Incluimos la librería  SoftwareSerial  
#include <dht.h>
SoftwareSerial BT(0,1);    // Definimos los pines TX=>0 y RX=>1 del Bluetooth al ATtiny
dht DHT;
#define DHT11_PIN 2

#define relay 3
 
void setup()
{
  BT.begin(9600);       // Inicializamos el puerto serie BT (Para Modo AT 2) 
  pinMode(relay,OUTPUT);  //relay CONECTADO 
  pinMode(DHT11_PIN, INPUT);
  digitalWrite(relay,0);  // apagar led
}
 
void loop()
{
  DHT.read11(DHT11_PIN);
  if(BT.available()>0) // el bluetooth esta disponible?
  {
    String dato = BT.readString();  //leer y guardar datos del bluetooth
    delay(10);
    if(dato == "D")
    {
      digitalWrite(relay,1);
    }
    if(dato == "d")
    {
      digitalWrite(relay,0);
    }
    if(dato == "T")
    {
      int t = DHT.temperature;
      delay(100);
      String temp = "*T" + String(t) + "*"; // ARMAR UN TEXTO
      BT.println(temp);
      delay(1000);
    }
    if(dato == "H")
    {
      int h = DHT.humidity;
      delay(100);
      String hum = "*H" + String(h) + "*"; // ARMAR UN TEXTO
      BT.println(hum);
      delay(1000);
    }
  }
}

//PRUEBA DEL SENSOR DE HUMEDAD Y TEMPERATURA AMBIENTE
//UTILIZANDO EL DHT11
//**************************************************************//
//UTILIZANDO EL TOQUEN, SSID y UTILIZAMOS WIFI MANAGER 
//SE CREA EL NOMBRE DEL DISPOSITIVO A DONDE SE VA A ENVIAR


#include "Lib_wifi.h"  //para agregar la librería de wifiManager
#include <Ubidots.h>
//**LIBRERÍA DEL SENSOR DHT11
#include <DHT.h>
#include <DHT_U.h>

#define UBIDOTS_TOKEN "COLOQUE SU TOQUEN"//COLOCAR EL TOQUEN DE SU UBIDOTS
#define DEVICE_NAME "Main-ESP8266"//NOMBRE QUE LE DEN A SU DISPOSITIVO

//Para evitar errores cuando se llamen nuevas variables en la pataforma
//UBIDOTS, ESTOS NOMBRES SON COMO SE ETIQUETARON EN LA PLATAFORMA IoT
#define LABEL_HUMED_AMBIENTE "humedad-ambiente"
#define LABEL_TEMP_AMBIENTE "temperatura-ambiente"

//Se crea un objeto de la clase Ubidots, llamado ubidots
//Este objeto recibe el toquen y el protocolo de comunicación HTTP
Ubidots ubidots(UBIDOTS_TOKEN, UBI_HTTP);

//Crear el objeto del sensor de humedad
DHT dht(D5, DHT11);
//crear las variables de temp y humedad
float TempAm, HumeAm;

void setup() {
  //Utilizar la librería wifimanager llamamos la función que esta en Lib_wifi.h
 conecta_a_wifi();

 Serial.println("********************");
 Serial.print("Conectado a la red WiFi: ");
 Serial.println(WiFi.SSID()); //Nombre de la red a la que se conecto
 Serial.print("IP:  ");
 Serial.println(WiFi.localIP()); //Una vez se conecta a la red WiFI al dispositivo se le asigna una dirección IP
 Serial.print("macAdress: ");
 Serial.println(WiFi.macAddress()); //La dirección física de mi tarjeta de fábrica
 Serial.println("*****************************");

//Inicializar el sensor DHT11
dht.begin();
TempAm=0;
HumeAm=0;
}

void loop() {
 //Leer la temperatura en grados Celcius utilizando la función
 //readTemperature();
 TempAm= dht.readTemperature();
 HumeAm= dht.readHumidity();
 Serial.println("Temperatura= "+String(TempAm)+", Humedad= "+String(HumeAm));
 //Ahora se agregan las variables de la plataforma Ubidots y se le 
 //asignan los valores de la variables leídas para visualizarlas
 ubidots.add(LABEL_HUMED_AMBIENTE, HumeAm);
 ubidots.add(LABEL_TEMP_AMBIENTE, TempAm);

 //Ahora se van a enviar:
 //se crea una variable booleana llamada bufferSent y se le asigna falso 
 bool bufferSent=false;
  //Se llama el método send, ubidots.send(),método con el que se envían los datos
  //de la tarjeta a la plataforma Ubidots, regresa verdadero o falso si se
  //envio correctamente o no, se utiliza para comprobar si se enviaron los datos
  bufferSent = ubidots.send(DEVICE_NAME);
  //con este if se comprueba si se enviaron los datos correctamente
   if (bufferSent) {
  // Do something if values were sent properly
   Serial.println("El dispositivo envío los valores");
  }
  delay(5000);
}

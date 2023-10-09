#include <ESP8266WiFi.h>

#include <WiFiManager.h>
#include <strings_en.h>
#include <wm_consts_en.h>
#include <wm_strings_en.h>
#include <wm_strings_es.h>

#include <DNSServer.h>
#include <ESP8266WebServer.h>

#include <Ticker.h> //Librería para generar una función de parpadeo
#define ledWiFi D4  //Activar el led D4 el de TX y RX
Ticker tic_WifiLed;  //Crear objetos de la clase ticker varibale tic_WifiLed del tipo ticker
//para ejecutar una función parpadeoLedWifi()

//// FUNCIÓN PARA EL PARPADEO UTILIZANDO TCKER
void parpadeoLedWifi(){
  byte estado =digitalRead(ledWiFi);
  digitalWrite(ledWiFi, !estado);
  //Cambia el estado del led
  }

void conecta_a_wifi(){
  
Serial.begin(115200);

// SE CONFIGURA EL LED D4 DE SALIDA
pinMode(ledWiFi, OUTPUT);
// se atachamos al objeto tic_Wifiled en la función parpadeo
tic_WifiLed.attach(0.2,parpadeoLedWifi);// attach al objeto ticker la función parpadeo y le da un tiempo de 0,2 segundos

//Creamos una instancia es decir un objeto de la clase wifiManager;
WiFiManager wifimanager;
 //Desconectar para resetear configuración
//wifimanager.resetSettings();  //Se coloca en comentario para que no se resetee
  //Creamos la AP y portal cautivo, va a intentar conectarse con la 
//última credencial si no se conecta va a crear una red un Access Point "ESP8266prueba"
if(!wifimanager.autoConnect("ESP8266Prueba")) {
  //Si no se pudo conectar, levanta la nueva red e imprime el mensaje
  //el tiempo de fallo, resetea la ESP y un delay de 1 segundo
  Serial.println("Fallo en la conexión (timeout)");
  ESP.reset();
  delay(1000);
}
Serial.println("Ya estás conectado");
tic_WifiLed.detach(); //detacch termina el proceso, elimina el temporizador y
//deja de tachar o parpadear el led
digitalWrite(ledWiFi, HIGH); //se apaga porque pudo quedar encendido
//Recuerde el LED de la tarjeta el D4 es negado
}
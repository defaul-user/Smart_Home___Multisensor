  
  #ifndef MENSAJES_HTTP_H
  #define MENSAJES_HTTP_H
  
  #include "hardware.h"


  /* IP del SERVIDOR WEB que recibira los datos del sensor de tª y humedad */
  
  #define SERVER_IP "192.168.1.225:8080" // IP OpenHab
  #define SERVER_IP_HTTP "192.168.1.225:9000" // IP ServidorWeb.jar
    
  
  /* Cabeceras de las funciones */
  
  void http_enviarMedidasSensor();
  
  void http_postSensacionTermica();
  
  void http_postTemperatura();
  
  void http_postHumedad();
  
  #endif

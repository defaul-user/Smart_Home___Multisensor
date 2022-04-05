
  #include "mensajes_http.h"
    
  /* Esta funcion se encarga de gestionar la lectura del sensor, tanto para la temperatura como para la humedad y la sensacion termica. 
     Las lecturas se llevan a cabo cada X segundos, esta temporalidad, se determina en la condicion del if.
     El valor de la temperatura y de la humedad, asi como de la sensacion termica, se almacenan en variables (ver hardware.h)*/
     
  void http_enviarMedidasSensor() {
    long now = millis(); // Almacena el nº de milisegundos transcurridos desde que se inciio el esp8266
   
    if (now - tiempo_anterior > 5000) { // Comprobar si han pasado 5 segundos
      
      tiempo_anterior = millis(); // Actualizar el nº de milisegundos al instante actual
           
      leerTemperatura();     
      leerHumedad();     
      calcularSensacionTermica();

      http_postSensacionTermica();
      http_postTemperatura();
      http_postHumedad();
      
    } // end if    
  } // end HTTP_ENVIAR_MEDIDAS_SENSOR()
  


  
  /* La funcion que viene a continuacion, se encarga de enviar mensajes HTTP POST al servidor web, junto con la sensacion termica 
     obtenida en la lectura del sensor */
     
  void http_postSensacionTermica() {
    WiFiClient client;
    HTTPClient http;
    
    // Configure traged server and url  
    http.begin(client, "http://" SERVER_IP "/rest/items/Salon_sensacionTermica"); //HTTP
    http.addHeader("Content-Type", "text/plain");
    Serial.print("[HTTP] POST...\n");
    
    int httpCode = http.POST(sensTermicaString); // POST de la sensación termica que hemos guardado en el string corrrespondiente (VER HARDWARE.H)
    
    // Si el codigo HTTP devuelto es negativo, indicara un error
    if (httpCode > 0) {
      
      // HTTP header has been send and Server response header has been handled
      Serial.printf("[HTTP] POST... code: %d ", httpCode);
      
      // File found at server
      if (httpCode == HTTP_CODE_OK) {
        
        Serial.println("OK\n");

      } // end if    
    } else {
      
      Serial.printf("[HTTP] POST... failed, error: %s\n", http.errorToString(httpCode).c_str());
    
    } // end else 
    
    http.end();
    
  }// end HTTP_POST_SENSACION_TERMICA()
  
  


  /* La funcion que viene a continuacion, se encarga de enviar mensajes HTTP POST al servidor web, junto con la temperatura 
     obtenida en la lectura del sensor */
     
  void http_postTemperatura() {
    WiFiClient client;
    HTTPClient http;
    
    // Configure traged server and url    
    http.begin(client, "http://" SERVER_IP "/rest/items/Salon_Temperatura"); //HTTP
    http.addHeader("Content-Type", "text/plain");
    Serial.print("[HTTP] POST...\n");
    
    int httpCode = http.POST(tempString);
    
    // Si el codigo HTTP devuelto es negativo, indicara un error
    if (httpCode > 0) {
      
      // HTTP header has been send and Server response header has been handled
      Serial.printf("[HTTP] POST... code: %d ", httpCode);
      
      // File found at server
      if (httpCode == HTTP_CODE_OK) {
        
        Serial.println("OK\n");
       
      } // end if 
    } else {
      
      Serial.printf("[HTTP] POST... failed, error: %s\n", http.errorToString(httpCode).c_str());
      
    }// end else
    
    http.end();
    
  }// end MEDIR_TEMPERATURA()
  
  


  /* La funcion que viene a continuacion, se encarga de enviar mensajes HTTP POST al servidor web, junto con la humedad 
     obtenida en la lectura del sensor */
     
  void http_postHumedad() {
    WiFiClient client;
    HTTPClient http;
    
    http.begin(client, "http://" SERVER_IP "/rest/items/Salon_Humedad"); //HTTP
    http.addHeader("Content-Type", "text/plain"); 
    Serial.print("[HTTP] POST...\n");
    
    int httpCode = http.POST(humString);
    
    // Si el codigo HTTP devuelto es negativo, indicara un error
    if (httpCode > 0) {
      
      // HTTP header has been send and Server response header has been handled
      Serial.printf("[HTTP] POST... code: %d ", httpCode);
      
      // file found at server
      if (httpCode == HTTP_CODE_OK) {
       
        Serial.println("OK\n");
        
      } // end if 
    } else {
      
      Serial.printf("[HTTP] POST... failed, error: %s\n", http.errorToString(httpCode).c_str());
    
    } // end else 
    
    http.end();
    
  }// end HTTP_POST_HUMEDAD()

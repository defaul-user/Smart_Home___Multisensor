  
  #include "hardware.h"

  /* Variables para almacenar temporalmente el valor de los datos devueltos por el sensor de temperatura y humedad */
  
  float humedad = 0;
  float temperatura = 0;
  float sensacionTermica = 0;

  


  /* La funcion que se encuentra a continuacion, tiene una labor fundamental, ya que se encarga de instanciar todos los pines del ESP8266 que se van a usar durante 
     su funcionamiento, es decir, es donde asociamos cada elemento que compone el sistema (sensores, interruptores, actuadores, etc.) con un pin I/O del ESP8266 */
     
  void inicializarPines(){
  
    pinMode(LED_BUILTIN, OUTPUT); // Initialize the BUILTIN_LED pin as an output
  
    /*  COMPONENETES CONECTADOS  */
    
    pinMode(led,OUTPUT);  // Configurar pin del LED como SALIDA
    pinMode(pin_boton,INPUT_PULLUP);  // Configurar pin del BOTON como ENTRADA y con resistencia de PULL-UP
    pinMode(pin_subir,OUTPUT);  // Configurar pin de la PERSAIANA_SUBIR como SALIDA
    pinMode(pin_bajar,OUTPUT);  // Configurar pin de la PERSIANA_BAJAR como SALIDA
    pinMode(pin_led_boton,OUTPUT);  // Como el rele solo tiene un pin para la señal de activacion, pues la funcionaliodad del interruptor la hacemos a pelo con el led conectado al pin 0 de la placa
    pinMode(pin_rele, OUTPUT);  // Configurar el pin del RELE como SALIDA
    
    digitalWrite(pin_rele, DESACTIVAR); //Desactivar rele
    digitalWrite(pin_led_boton,DESACTIVAR); // Desactivar el led que acciona el interruptor
    digitalWrite(led,APAGAR); // Apagar led interno
   
  } // end INICIALIZAR_PINES()
  



  /* Esta funcion se encarga simplemente de iniciar o "encender" el sensor DHT11 para que comience a funcionar y pueda devolver medidas de temperatura y humedad */
  
  void iniciarSensor(){
    
    dht.begin();
    
  } // end INICIALIZAR_SENSOR()




  /* Esta funcion se emplea para calcular la temperatura a traves del sensor DHT11, ademas se comprueba que el valor devuelto por el mismo es valido, esto es, si es un valor numerico.
     Si el valor es devuelto correctamente por el sensor, este se almacena en la variable temperatura y posteriormente se convertira y almacenara en una cadena de caracterees 
     para poder ser procesada por las distintas funciones de enviar mensajes, tanto por HTTP como por MQTT */
     
  void leerTemperatura(){
    
    temperatura = dht.readTemperature();
    
    if (isnan(temperatura)) {
      
      Serial.println("Error al leer del sensor de temperatura");
      
    } else {
      
      snprintf(tempString, sizeof(tempString), "%f", temperatura); // Guardamos unicamente los 10 primeros digitos de la temperatura en una cadena de caracteres
      Serial.print("Temp OK: ");
      Serial.println(tempString);
     
    } //end else 
  } // end LEER_TEMPERATURA()
  



  /* Esta funcion se emplea para calcular la humedad a traves del sensor DHT11, ademas se comprueba que el valor devuelto por el mismo es valido, esto es, si es un valor numerico.
     Si el valor es devuelto correctamente por el sensor, este se almacena en la variable humedad y posteriormente se convertira y almacenara en una cadena de caracterees 
     para poder ser procesada por las distintas funciones de enviar mensajes, tanto por HTTP como por MQTT */
       
  void leerHumedad(){
  
    humedad = dht.readHumidity();
  
    if (isnan(humedad)) {
      
      Serial.println("Error al leer del sensor de temperatura");
      
    } else {
      
      snprintf(humString, sizeof(humString), "%f", humedad); // Guardamos unicamente los 10 primeros digitos de la temperatura en una cadena de caracteres
      Serial.print("Hum OK: ");
      Serial.println(humString);
    
    } //end else 
  } //end LEER_HUMEDAD()




  /* Esta funcion se emplea para calcular la sensacion termica a traves del sensor DHT11, ademas se comprueba que el valor devuelto por el mismo es valido, esto es, 
     si es un valor numerico. Si el valor es devuelto correctamente por el sensor, este se almacena en la variable sensacionTermica y posteriormente se convertira 
     y almacenara en una cadena de caracterees para poder ser procesada por las distintas funciones de enviar mensajes, tanto por HTTP como por MQTT */
     
  void calcularSensacionTermica(){
    
     sensacionTermica = dht.computeHeatIndex(temperatura, humedad, false);

    if (isnan(humedad)) {
      
      Serial.println("Error al leer del sensor de temperatura");
      
    } else {
      
      snprintf(sensTermicaString, sizeof(sensTermicaString), "%f", sensacionTermica); // Guardamos unicamente los 10 primeros digitos de la temperatura en una cadena de caracteres
      Serial.print("Sens OK: ");
      Serial.println(sensTermicaString);
      
    } // end else
  } // end CALCULAR_SENSACION_TERMICA()



  
  /* Esta funcion se encarga de registrar las pulsaciones del "interruptor", ademas no solo las "detecta" sino que se encarga de gestionar el fenomeno denominado "rebotes"
     a traves de una serie de parametros temporales conesguimos mitigar o directamente suprimir el "efecto rebotes" que tiene el pulsador fisico empleado.
     De una forma sencilla, se podria decir que "apagamos el sensor" durante un tiempo determinado, en el cual nosotros preveemos que va a haber rebotes, para de esta manera 
     no ser sensibles a ellos durante ese periodo de tiempo */
     
  void gestionPulsador(){
    
    estado_bot = digitalRead(pin_boton); // Leemos el pin asignado al boton, recuerda que tiene una resistencia de pull-up y que si no lo presionamos el valor medido sera HIGH ( 5 V )
    
    /*  CODIGO ANTI REBOTES   */
    
    if (estado_bot != ulti_estado_bot) { // Si el estado del boton cambia debido a los rebotes . . . 
      
      //Guardamos el ultimo estado registrado
      ulti_estado_bot = estado_bot;
      
    }//end if 
    
    if ((millis() - lastDebounceTime) > DEBOUNCE_DELAY) { // Cualquiera que haya sido la lectura, nos aseguramos de que hemos evitado todos los rebotes.
      
      // Tiempo que lleva la placa encendida - tiempo que llevaba encendida en el ultimo rebote captado > tiempo establecido para evitar rebotes
         
          /* La forma mas sencilla de aplicar un debounce por software es comprobar el tiempo entre disparos de la interrupcion.
             Si el tiempo es inferior a un determinado umbral de tiempo (DEBOUNCE_DELAY) simplemente ignoramos la interrupcion.
             En definitiva, hemos definido una "zona muerta" en la que ignoramos las pulsaciones generadas por el interruptor */
      
      lastDebounceTime = millis();// Reseteamos el debouncing timer
      
      /*  ALTERNANCIA ENTRE ESTADOS */
      
      if(ulti_estado_bot == LOW & estado_led == LOW){
        
        digitalWrite(pin_led_boton,HIGH);
        estado_led = HIGH;
        estado_luz_techo = "ON";       
                 
      }else if(ulti_estado_bot == LOW & estado_led == HIGH){
        
        digitalWrite(pin_led_boton,LOW);
        estado_led = LOW;
        estado_luz_techo = "OFF";    
            
      } //end else if 
    } // end if 
  } // end GESTIONPULSADOR()
  

  
  #include "servidor_mqtt.h"



  /* Funcion para iniciar el servidor MQTT, se establecen direcciones y puerto y funcion de callback que procesara los mensajes entrantes */
  
  void arrancar_servidor_mqtt(){
    
    client.setServer(mqtt_server,1883);
    client.setCallback(callback);
    
  } //end ARRANCAR_SERVIDOR_MQTT()




  /* La funcion manejadorServidorMQTT se encarga de mantener la conexion con el broker MQTT activa y actuar de forma adecuada en caso de perderse */
  
  void manejadorServidorMQTT(){
    
    if (!client.connected()) {
      
      Serial.println(client.state());
      reconnect();
      
    } // end if 
    
    client.loop();
    delay(1); // Needed to add a delay of 1ms otherwise the connection drops with -4 error. After adding this the connection is stable
    
  } //end MANEJADOR_SERVIDOR_MQTT
  
  
  
  
  /* La funcion que encontramos a continuacion se encarga de procesar los mensajes que le llegan al ESP8266 del BROKER (Raspberry Pi), analizarlos y actuar en consecuencia,
     llamando a las funciones correspondientes para el manejo del hardware del sistema */
  
  void callback(char* topic, byte* payload, unsigned int length) { // Esta funcion se ejecuta con la llegada de mensajes MQTT, analiza el topic por el que llega 
                                                                  // el mensaje y en funcion de ello se tomaran las decisiones pertinentes
    Serial.print("Message arrived [");
    Serial.print(topic);
    Serial.print("] ");
    String msg;
    String topic_subs(topic);
    
    for (int i = 0; i < length; i++) {
      Serial.print((char)payload[i]);
      msg +=(char)payload[i];
      } //end for 
      
      Serial.println(msg);
      Serial.println("MENSAJE POR AQUI");
      
      if(topic_subs.equals(topic_subs_enchufe) && msg == "encender\0"){
        
        digitalWrite(led,ENCENDER); // Encender led interno
        digitalWrite(pin_rele,ACTIVAR); // Activar el rele
        
      } //end if
      
      if(topic_subs.equals(topic_subs_enchufe) && msg == "apagar\0"){
        
        digitalWrite(led,APAGAR); // Apagar led interno
        digitalWrite(pin_rele,DESACTIVAR); // Desactivar el rele
        
      } //end if

      if(topic_subs.equals(topic_subs_interruptor) && msg == "encender\0"){
        
        digitalWrite(led,ENCENDER); // Encender led interno
        digitalWrite(pin_led_boton,ACTIVAR); // Activar el led del interruptor
        estado_luz_techo = "ON";      
        
      } //end if
      
      if(topic_subs.equals(topic_subs_interruptor) && msg == "apagar\0"){
        
        digitalWrite(led,APAGAR); // Apagar led interno
        digitalWrite(pin_led_boton,DESACTIVAR); // Desactivar el led del interruptor
        estado_luz_techo = "OFF";  
        
      } //end if
  } // end CALLBACK()
  
  
  
  bool subs_topic (){
    
  bool estado = false;
  
    if(client.subscribe(topic_subs_enchufe)){
      
      estado = true;
      
    } //end if
    
    if(client.subscribe(topic_subs_interruptor)){
      
      estado = true;
      
    } //end if
    
    return estado;
    
  }// end SUBS_TOPICS()
  
  
  

  /* Esta funcion se encarga de reconectar (o conectar, si es la primera vez que se realiza la operacion) el ESP8266 al BROKER MQTT (Raspberry)
     en resumidas cuentas, establece y mantiene la conexion con el BROKER MQTT */
  
  void reconnect() {
  
    while (!client.connected()&intentos_conexion < 5) {
      
      Serial.print("Attempting MQTT connection...");
      // Create a random client ID
      String clientId = "ESP8266Client-";
      clientId += String(random(0xffff), HEX);
      
      // Attempt to connect
      if (client.connect(clientId.c_str())) {
        
        //Si se conecta, pues lo subscribimos al topic que nos mandan
        if(subs_topic ()){
          
          Serial.println("Connected");
        
        }else{
          
          Serial.println("Error al subscribirse a los topic");
        
        } // end else
        
        client.publish(topic_pub, "Anuncio que el cliente esp8266 se ha conectado");
        client.subscribe("inTopic");
        
      } else {
        
        Serial.print("failed, rc=");
        Serial.print(client.state());
        Serial.println(" try again in 5 seconds");
        intentos_conexion++;
        // Wait 5 seconds before retrying
        delay(5000);
        
      } // end else 
    } // end while
  } // end RECONNECT()
  
  
  
  
  /* La funcion que vemos a continuacion se encarga de enviar mensajes MQTT cada x Segundos, en este caso cada 2 segundos enviará el mensaje MQTT corespondeinte al estado del 
     interruptor */
  
  void mqtt_EnviarMensaje(){
    
    long now = millis(); //Almacena el nº de milisegundos transcurridos desde que se inciio el esp8266
    
    if(now - tiempoUltimoMnesaje > 2000){ //Comprobar si han pasado 2 segundos 
      
      tiempoUltimoMnesaje = now; // Actualizar el nº de milisegundos al instante actual
      snprintf(mensajeMQTT, 50, "Estado interruptor -> %s", estado_luz_techo); //Guardar en la variable mensaje, que tiene un tamaño de 50, el texto 'mensaje nº #' mas el valor del mensaje
      client.publish(topic_pub,mensajeMQTT);
      
    } // end if 
  } // end MQTT_ENVIARMENSAJE()




  /* Esta funcion se encarga de enviar la informacion relativa a la informacion recogida por el sensor DHT11, en este caso cada 6 segundos  */    
  
  void mqtt_EnviarMensaje_sensores() {
    
    long now = millis(); //Almacena el nº de milisegundos transcurridos desde que se inciio el esp8266
    
    if (now - tiempo_ant > 6000) { //Comprobar si han pasado 6 segundos
      
      client.publish(topic_pub_temp, tempString);
      client.publish(topic_pub_hum, humString);
      client.publish(topic_pub_stermica, sensTermicaString);
      
    } // end if 
  } // end MQTT_ENVIARMENSAJE()
  

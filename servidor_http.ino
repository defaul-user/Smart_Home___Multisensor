 
  #include "servidor_http.h"

  
  

  /* Esta funcion se encarga de arrancar el servidor y proporcionar las llamadas a funciones necesarias para actuar adecuadamente ante una peticion HTTP que este 
     asociada a una accion dentro de los dispositivos conectados en el ESP8266 */
  
  void arrancar_servidor_web(){
    
    // Configuracion del servidor Web
    servidorWeb.on("/",manejadorRaiz); // Asociar el path "/" a la funcion manejadorRaiz()
    
    /*  ACTUADOR ENCHUFE  */
    servidorWeb.on("/enchufe/encender",manejadorEncendido); // Asociar el path "enchufe/encender" a la funcion menajadorEncendido()
    servidorWeb.on("/enchufe/apagar",manejadorApagado); // Asociar el path "enchufe/apagar" a la funcion manejadorApagado()
    servidorWeb.on("/enchufe/estado",manejadorEstado); // Asociar el path "enchufe/estado" a la funcion manejadorApagado()
    
    /*  ACTUADOR INTERRUPTOR  */
    servidorWeb.on("/interruptor/encender",manejadorEncendidoInterruptor); // Asociar el path "enchufe/encender" a la funcion menajadorEncendido()
    servidorWeb.on("/interruptor/apagar",manejadorApagadoInterruptor); // Asociar el path "enchufe/apagar" a la funcion manejadorApagado()
    servidorWeb.on("/interruptor/estado",manejadorEstadoInterruptor); // Asociar el path "enchufe/estado" a la funcion manejadorApagado()  
    
    /*  ACTUADOR PERSIANA  */
    servidorWeb.on("/persiana/subir",manejadorPersianaSubir); // Asociar el path "enchufe/encender" a la funcion menajadorEncendido()
    servidorWeb.on("/persiana/bajar",manejadorPersianaBajar); // Asociar el path "enchufe/apagar" a la funcion manejadorApagado()
    servidorWeb.on("/persiana/parar",manejadorPersianaParar); // Asociar el path "enchufe/estado" a la funcion manejadorApagado()  
    
    // Arrancar el servidor web
    servidorWeb.begin();
    Serial.println("Servidor web arrancado");
    
    // Hacer parpadear 10 veces el led interno para saber que ha terminado de arrancar el servidor
    for(int i=0; i<10; i++){
      
      digitalWrite(LED_BUILTIN, ENCENDER);
      digitalWrite(LED_BUILTIN, APAGAR);
      
    } //end for   
  }// end ARRANCAR_SERVIDOR_WEB()
  
  
  
  
  /* La siguiente funcion se encarga de gestionar la conexion del servidor HTTP alojado en la propia placa ESP8266 */
  
  void manejadorServidor(){
  
    servidorWeb.handleClient(); // Consultar si se ha recibido una peticion al servidor web
  
  } // end MANEJADOR_SERVIDOR()
  
  
  
  
  /*   HTTP   */
  
  /* Esta funcion se encarga de llamar al manejador raiz de la pagina, es decir invoca la pagina principal del menu de opciones que ofrece nuestro sistema  */ 
  
  void manejadorRaiz(){
  
    String mensaje;
    
    servidorWeb.send(200, "text/html; charset=UTF-8", pagina_html());
  
  } // end MANEJADOR_RAIZ()
  
  
  
  
  /*  Manejador para una pagina no encontrada o para una peticion no valida  */
  
  void paginaNoEncontrada(){
  
  String mensaje = "Pagina no encontrada\n\n";
  
    mensaje += "URI: ";
    mensaje += servidorWeb.uri();
    mensaje += "\nMetodo: ";
    mensaje += (servidorWeb.method() == HTTP_GET) ? "GET" : "POST";
    mensaje += "\nArgumentos: ";
    mensaje += servidorWeb.args();
    mensaje += "\n";
    
    for(uint8_t i = 0; i <servidorWeb.args(); i++){
      
      mensaje += " " + servidorWeb.argName(i) + ": " + servidorWeb.arg(i) + "\n";
      
    } // end for 
    
    servidorWeb.send(404,"text/plain", mensaje);
  
  } // end paginaNoEncontrada

    

  
  /*** Funciones asociadas a cada peticion ***/
  
  
  /* ACTUADOR ENCHUFE */
  
  /* Esta funcion gestiona el encendido del ACTUADOR ENCHUFE  */
  
  void manejadorEncendido(){
  
    digitalWrite(led,ENCENDER); // Encender led interno
    digitalWrite(pin_rele,ACTIVAR); // Activar el rele
    servidorWeb.send(200,"text/plain",mensaje_enchufe_on());
    
  }// end MANEJADOR_ENCENDIDO()




  /* Esta funcion gestiona el apagado del ACTUADOR ENCHUFE  */
  
  void manejadorApagado(){
  
    digitalWrite(led,APAGAR); // Apagar led interno
    digitalWrite(pin_rele,DESACTIVAR); // Desactivar el rele
    servidorWeb.send(200,"text/plain",mensaje_enchufe_off());
  
  }// end MANEJADOR_APAGADO()




  /* Esta funcion se encarga de mostrar el estado del pin del ACTUADOR ENCHIFE */
  
  void manejadorEstado(){
  
    if(digitalRead(pin_rele) == HIGH){
      
      servidorWeb.send(200,"text/plain",mensaje_enchufe_on());
      
    }else{
      
      servidorWeb.send(200,"text/plain",mensaje_enchufe_off());    
      
    } // end else 
  
  }// end manejadorEstado



  
  /*  INTERRUPTOR  */
  
  /* Esta funcion se encarga del encendido del interruptor */
  
  void manejadorEncendidoInterruptor(){
  
    digitalWrite(led,ENCENDER); // Encender led interno
    digitalWrite(pin_led_boton,ACTIVAR); // Activar el rele
    
    //digitalWrite(pin_rele,ACTIVAR); // Activar el rele
    
    servidorWeb.send(200,"text/plain",mensaje_interruptor_on());
    
  }//end manejadorEncendido()




  /* Esta funcion se encarga del apagado del interruptor */
    
  void manejadorApagadoInterruptor(){
  
    digitalWrite(led,APAGAR); // Apagar led interno
    digitalWrite(pin_led_boton,DESACTIVAR); // Desactivar el rele
    
    //digitalWrite(pin_rele,DESACTIVAR); // Desactivar el rele
    
    servidorWeb.send(200,"text/plain",mensaje_interruptor_off());
  
  }//end manejadorApagado()




  /* Esta funcion se encarga de compartir el estado del interruptor del interruptor */
    
  void manejadorEstadoInterruptor(){
  
    if(digitalRead(pin_led_boton) == HIGH){
      
      servidorWeb.send(200,"text/plain",mensaje_interruptor_on());
      
    }else{
      
      servidorWeb.send(200,"text/plain",mensaje_interruptor_off());    
      
    } // end else 
  }// end manejadorEstadoInterruptor()
  
  
  /*  PERSIANA  */

  /* Esta funcion se encarga del proceso de subir la persiana */
  
  void manejadorPersianaSubir(){
  
    digitalWrite(led,ENCENDER); // Encender led interno
    digitalWrite(pin_bajar,DESACTIVAR); // Desactivar el led de persiana bajar
    digitalWrite(pin_subir,ACTIVAR); // Activar el led de persiana subir
    servidorWeb.send(200,"text/plain",mensaje_persiana_subir());
  
  }//end manejadorEncendido()





  /* Esta funcion se encarga del proceso de bajar la persiana */

  void manejadorPersianaBajar(){
  
    digitalWrite(led,APAGAR); // Apagar led interno
    digitalWrite(pin_subir,DESACTIVAR); // Activar el led de persiana bajar
    digitalWrite(pin_bajar,ACTIVAR); // Desactivar el led de persiana subir
    servidorWeb.send(200,"text/plain",mensaje_persiana_bajar());
  
  }//end manejadorApagado()




  /* Esta funcion se encarga del proceso de parar la persiana */

  void manejadorPersianaParar(){
    
    digitalWrite(pin_bajar,DESACTIVAR); // Desactivar el led de persiana bajar
    digitalWrite(pin_subir,DESACTIVAR); // Desactivar el led de persiana subir
    servidorWeb.send(200,"text/plain",mensaje_persiana_parar());
  
  }// end manejadorPersianaParar()

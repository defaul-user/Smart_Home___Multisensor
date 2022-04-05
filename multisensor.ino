  
  #include "hardware.h"
  #include "gestorWifi.h"
  #include "mensajes_http.h"
  #include "paginas_html.h"
  #include "servidor_http.h"
  #include "servidor_mqtt.h"
    


  
  void setup() { // Función inicial
    
    Serial.begin(115200); // Establecer la velocidad de consola serie
    Serial.println("");

    setup_wifi(); // Funcion que inicializa los parámetros para la conexion WIFI y se encarga de establecer la misma, 
                 //  el objetivo final es simplificar al maximo la conexion WIFI y que si se requieren cambios, estos se hagan de forma más sencilla, mas info en --> gestionWifi
    
    inicializarPines(); // Esta funcion es llamada para inicializar todos los pines de la placa que seran usados para realizar alguna tarea (sensor, interruptor, led, etc.), 
                       //  para mas info ver --> hardware
    
    iniciarSensor(); // Con esta funcion, inicializamos el sensor de temperatura y humedad, para mas info ver --> hardware
    
    arrancar_servidor_web(); // Esta funcion se encarga de arrancar y configurar el Servidor Web para trabajar con las peticiones HTTP, ver --> servidor_http
    
    arrancar_servidor_mqtt(); // Se encarga de inicializar y arrancar el servidor MQTT, tanto para hacer SUB como PUT al BROKER, ver --> servidor_mqtt
  
  } //end SETUP



  
  void loop() { // Funciones que se ejecutarán en un bucle "infinito"
  
    manejadorServidorMQTT(); // Se encarga de controlar que el servidor MQTT no se ha desconectado y en caso de estar desconectado, tomar medidas, mas info en --> servidor_mqtt
    
    http_enviarMedidasSensor(); // Su funcion es enviar mensajes http POST al servidor Web, con medidas del sensor de temperatura cada x tiempo, mas info en --> servidor_http
    
    mqtt_EnviarMensaje(); // Su funcion es enviar mensajes mqtt PUB al BROKER (Raspi), con el estado del interruptor, cada x tiempo, mas info en --> servidor_mqtt
    
    mqtt_EnviarMensaje_sensores(); // Su funcion es enviar mensajes mqtt PUB al BROKER (Raspi), con medidas del sensor de temperatura cada x tiempo, mas info en --> servidor_mqtt
    
    manejadorServidor(); // Gestión del servidor HTTP para comprobar si se ha recibido alguna peticion nueva, para mas info ver --> servidor_http
    
    gestionPulsador(); // Esta función se encarga de la gestión completa del pulsador, para mas info ver --> hardware 
    
    estadoWifi(); // Funcion que se encarga de mantener la conexion WIFI establecida, toma medidas en caso de perderse la conexion
  
  } //end LOOP

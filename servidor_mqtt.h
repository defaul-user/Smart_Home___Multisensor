 
  #ifndef SERVIDOR_MQTT_H
  #define SERVIDOR_MQTT_H
  
    #include <PubSubClient.h>
    #include "hardware.h"
    
    /* IP del BROKER MQTT (Raspberry en nuestro caso) */
    
    const char* mqtt_server = "192.168.1.225";
        
    
    /* Cliente ESP8266 (MQTT) */
    
    WiFiClient espClient;
    PubSubClient client(mqtt_server,1883,espClient); // 1883 es el puerto listener para el Broker
    //const char* clientID = "ESP8266_1";
    uint8_t intentos_conexion = 0; // Contador q usaremos para limitar el nº de intentos de conexion a la red wifi
    
    
    /* Variables correspondientes a los TOPIC SUB y PUB ( MQTT ) */
    
    const char* topic_pub = "casa/dormitorio/luztecho/estado";
    const char* topic_subs_enchufe = "casa/dormitorio/enchufe/orden"; // Variable Correspondiente al ACTUADOR ENCHUFE
    const char* topic_subs_interruptor = "casa/dormitorio/luztecho/orden";
    char* topic_pub_temp="casa/dormitorio/temperatura";
    char* topic_pub_hum="casa/dormitorio/humedad";
    const char* topic_pub_stermica="casa/dormitorio/sensacionTermica";
    
    
    /* Variables para trabajar con los MENSAJES que se envían ( MQTT ) */
    
    char mensajeMQTT[50];
    long tiempoUltimoMnesaje = 0;
    char mensaje1[50];
    char mensaje2[50];
    
    
    /* Cabeceras de las funciones */
    
    void callback(char* topic, byte* payload, unsigned int length); // Funcion callback para los mensajes entrantes (llamadas) mqtt
    void reconnect(); // Funcion para reconectar en caso de perderse la conexion con el broker mqtt
    void mqtt_EnviarMensaje(); // Funcion para enciar mensajes cada 2 segundos
    void mqtt_EnviarMensaje_sensores(); // Funcion para enciar mensajes cada 2 segundos
    void arrancar_servidor_mqtt();
    void manejadorServidorMQTT();
  
  #endif

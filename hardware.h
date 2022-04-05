  
  #ifndef HARDWARE_H
  #define HARDWARE_H
  
    #include <DHT.h> // Sensor Temperatura y Humedad
    
    /* Pines para componentes */
    
    #define pin_boton  12 // Pin del ESP8266 que vamos a usar para el PULSADOR
    #define pin_rele 13 // Pin del ESP8266 que se conectara al pin D1 del RELE para enviar señal de ON y OFF
    #define pin_subir 15 // PERSIANA --> Subir
    #define pin_bajar 16 // PERSIANA --> Bajar
    #define pin_led_boton 14 // Pin para el LED del interuptor
    #define pin_sensor_dh 2 // Pin para el sensor de Tª y humedad 
    
    DHT dht(pin_sensor_dh, DHT11); // Instanciar objeto para trabajar con el sensor
    
    /* Estados y constantes para el manejo de componentes */
    
    const int led = LED_BUILTIN; // LED interno de la placa:

    #define ENCENDER LOW
    #define APAGAR HIGH
    
    // Rele
    #define ACTIVAR HIGH
    #define DESACTIVAR LOW
    
    
    /* Estados de los diferntes componentes del sistema */
    
    int estado_rele = LOW; // Sirve para que cuando presionemos el interruptor, el relé no se active muchas veces y haga un ruido raro
    int estado_bot = LOW; // Almacena el estado del boton, para evitar que el programa este todo el rato enviando la orden de apagar
    int ulti_estado_bot = LOW; // Variable para solventar el problema con los rebotes del pulsador
    int estado_led = LOW; // Almacena el estado del led, para evitar que el programa este todo el rato enviando la orden de apagar 
    String estado_luz_techo = "OFF"; // Variable para saber si la luz del techo está encendida o apagada (ya que puede verse alterada tanto por la orden MQTT como por el interruptor fisico) 
    
    
    /* Variables temporales */
    
    const long intervalo = 1000; // Definimos un intervalo de tiempo para evitar los rebotes con el pulsador
    const int DEBOUNCE_DELAY = 300; // El debounce time se incrementa si se detecta efecto rebote a la salida del LED
    unsigned long tiempo_anterior = 0; // Almacenara el tiempo anterior devuelto por la funcion millis()
    unsigned long lastDebounceTime = 0;  // El ultimo momento que se detecto pulsacion
    long tiempo_ant = 0; // Variable usada para enviar mensajes de temperatura cada x tiempo

    /* Varibales para almacenar los STRING con el valo de la temperatura, humedad y sensacion termica obtenidos por el sensor.
       Estos valores los almacenamos en STRINGS para poder enviarlos a traves de HTTP y MQTT de forma facil */
       
    char tempString[10];
    char humString[10];
    char sensTermicaString[10];

    /* Cabeceras de las funciones */
    
    void gestionPulsador();
    
    void inicializarPines();
    
    void leerTemperatura();
    
    void leerHumedad();

    void calcularSensacionTermica();

  #endif

  
  #ifndef GESTOR_WIFI_H
  #define GESTOR_WIFI_H

    // Redes WiFi guardadas para la conexion del ESP8266
    
    const char* ssid ="SmartHome";
    const char* password = "SmartHome";
    
    /* Cabeceras de las funciones */
    
    void setup_wifi();
    
    void estadoWifi();
  
  #endif

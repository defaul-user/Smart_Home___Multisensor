  #ifndef SERVIDOR_HTTP_H
  #define SERVIDOR_HTTP_H
  
    /* Librerias necesarias para el funcionamiento */
    
    #include <ESP8266WiFi.h>
    #include <ESP8266WebServer.h> //Servidor Web
    #include <ESP8266HTTPClient.h> // Cliente http
    #include "paginas_html.h"
    #include "mensajes_http.h"
    
        
    /* Las siguientes variables se definen para no usar DHCP */
    
    IPAddress wifiIP(192,168,1,87); // IP que se asignara al esp8266
    IPAddress wifiNet(255,255,255,0); // Mascara de subred
    IPAddress wifiGW(192,168,1,1); // Router

    
    /* Servidor WEB */
    
    ESP8266WebServer servidorWeb(80); // Instanciar objeto servidor web
    

    /* Cabeceras de las funciones */
    
    void arrancar_servidor_web(); // Funcion para incializar el servidor WEB  
    void manejadorServidor(); // GESTION CONEXION CON EL SERVIDOR 

    
    /*   HTTP   */
    
    void manejadorRaiz(); // Pagina inicial con el menu de opciones   
    void paginaNoEncontrada(); // Manejador para una pagina no encontrada o para una peticion no valida

    
    /* Funciones asociadas a cada peticion */
    
    /*  ACTUADOR ENCHUFE  */
    
    void manejadorEncendido();    
    void manejadorApagado();  
    void manejadorEstado();

    
    /*  INTERRUPTOR  */
    
    void manejadorEncendidoInterruptor();
    void manejadorApagadoInterruptor();   
    void manejadorEstadoInterruptor();
    
    
    /*  PERSIANA  */
    
    void manejadorPersianaSubir();    
    void manejadorPersianaBajar();    
    void manejadorPersianaParar();
  
  
  #endif
  

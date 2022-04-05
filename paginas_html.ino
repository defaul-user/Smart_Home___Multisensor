
 #include "paginas_html.h"




  /* En esta funcion sencillamente construimos la pagina HTML que nos permitiria interactuar con el sistema domotico a traves de cualquier navegador web, siempre que estemos
     conectados a la red local */
     
  String pagina_html(){
  
    String mensaje;
    
      mensaje += "<!DOCTYPE HTML>\r\n<html>\r\n";
      mensaje += "<head><meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\">";
      
      mensaje += "<title>Prueba de recepción de peticiones</title></head>\r\n";
      
      mensaje += "<body>";
      mensaje += "<h2><strong>Multiactuador</strong></h2>";
      mensaje += "<h3 align =""left"">Actuador de Enchufe:<h3>";
      
      mensaje += "<hr><ul>";
      mensaje += "<li>Pulsa para <a href =""/enchufe/encender"">Encender</a></li>";
      mensaje += "<li>Pulsa para <a href=""/enchufe/apagar"">Apagar</a></li>";
      mensaje += "<li>Pulsa para <a href=""/enchufe/estado"">Estado</a></li>";
      mensaje += "</ul><hr>";  
      
      mensaje += "<h3 align =""left"">Actuador de Interruptor:<h3>";
      
      mensaje += "<hr><ul>";
      mensaje += "<li>Pulsa para <a href =""/interruptor/encender"">Encender</a></li>";
      mensaje += "<li>Pulsa para <a href=""/interruptor/apagar"">Apagar</a></li>";
      mensaje += "<li>Pulsa para <a href=""/interruptor/estado"">Estado</a></li>";
      mensaje += "</ul><hr>";    
      
      mensaje += "<h3 align =""left"">Actuador de Persiana:<h3>";
      
      mensaje += "<hr><ul>";
      mensaje += "<li>Pulsa para <a href =""/persiana/subir"">Subir</a></li>";
      mensaje += "<li>Pulsa para <a href=""/persiana/bajar"">Bajar</a></li>";
      mensaje += "<li>Pulsa para <a href=""/persiana/parar"">Parar</a></li>";
      mensaje += "</ul><hr>";   
      
      mensaje += "</body>";
      mensaje += "</html>\n";
    
    return mensaje;
  } //end pagina_html




  /* A partir de aqui se declaran las funciones necesarias para la construccion de mensajes para HTTP  */
  
  String rot_interruptor(){ // ROTULO PERSIANA (para los mensajes HTTP)
    String mensaje;
      mensaje +="'####:'##::: ##:'########:'########:'########::'########::'##::::'##:'########::'########::'#######::'########::\n";
      mensaje +=". ##:: ###:: ##:... ##..:: ##.....:: ##.... ##: ##.... ##: ##:::: ##: ##.... ##:... ##..::'##.... ##: ##.... ##:\n";
      mensaje +=": ##:: ####: ##:::: ##:::: ##::::::: ##:::: ##: ##:::: ##: ##:::: ##: ##:::: ##:::: ##:::: ##:::: ##: ##:::: ##:\n";
      mensaje +=": ##:: ## ## ##:::: ##:::: ######::: ########:: ########:: ##:::: ##: ########::::: ##:::: ##:::: ##: ########::\n";
      mensaje +=": ##:: ##. ####:::: ##:::: ##...:::: ##.. ##::: ##.. ##::: ##:::: ##: ##.....:::::: ##:::: ##:::: ##: ##.. ##:::\n";
      mensaje +=": ##:: ##:. ###:::: ##:::: ##::::::: ##::. ##:: ##::. ##:: ##:::: ##: ##::::::::::: ##:::: ##:::: ##: ##::. ##::\n";
      mensaje +="'####: ##::. ##:::: ##:::: ########: ##:::. ##: ##:::. ##:. #######:: ##::::::::::: ##::::. #######:: ##:::. ##:\n";
      mensaje +="....::..::::..:::::..:::::........::..:::::..::..:::::..:::.......:::..::::::::::::..::::::.......:::..:::::..::\n";
    return mensaje;
  } //end mensaje_Apagado




  String rot_persiana(){ // ROTULO PERSIANA (para los mensajes HTTP)
      String mensaje;
        mensaje +="########::'########:'########:::'######::'####::::'###::::'##::: ##::::'###::::\n";
        mensaje +="##.... ##: ##.....:: ##.... ##:'##... ##:. ##::::'## ##::: ###:: ##:::'## ##:::\n";
        mensaje +="##:::: ##: ##::::::: ##:::: ##: ##:::..::: ##:::'##:. ##:: ####: ##::'##:. ##::\n";
        mensaje +="########:: ######::: ########::. ######::: ##::'##:::. ##: ## ## ##:'##:::. ##:\n";
        mensaje +="##.....::: ##...:::: ##.. ##::::..... ##:: ##:: #########: ##. ####: #########:\n";
        mensaje +="##:::::::: ##::::::: ##::. ##::'##::: ##:: ##:: ##.... ##: ##:. ###: ##.... ##:\n";
        mensaje +="##:::::::: ########: ##:::. ##:. ######::'####: ##:::: ##: ##::. ##: ##:::: ##:\n";
        mensaje +="..:::::::::........::..:::::..:::......:::....::..:::::..::..::::..::..:::::..::\n";
      return mensaje;
  } //end rot_persiana




  String rot_enchufe(){
    String mensaje;
     mensaje +="########:'##::: ##::'######::'##::::'##:'##::::'##:'########:'########:\n";
     mensaje +="##.....:: ###:: ##:'##... ##: ##:::: ##: ##:::: ##: ##.....:: ##.....::\n";
     mensaje +="##::::::: ####: ##: ##:::..:: ##:::: ##: ##:::: ##: ##::::::: ##:::::::\n";
     mensaje +="######::: ## ## ##: ##::::::: #########: ##:::: ##: ######::: ######:::\n";
     mensaje +="##...:::: ##. ####: ##::::::: ##.... ##: ##:::: ##: ##...:::: ##...::::\n";
     mensaje +="##::::::: ##:. ###: ##::: ##: ##:::: ##: ##:::: ##: ##::::::: ##:::::::\n";
     mensaje +="########: ##::. ##:. ######:: ##:::: ##:. #######:: ##::::::: ########:\n";
     mensaje +="........::..::::..:::......:::..:::::..:::.......:::..::::::::........::\n";
    return mensaje;
  } //end rot_enchufe




  String rot_encendido(){
    String mensaje;    
      mensaje +="'########'##::: ##::'######::'########:'##::: ##:'########::'####:'########:::'#######::\n";
      mensaje +="##.....:: ###:: ##:'##... ##: ##.....:: ###:: ##: ##.... ##:. ##:: ##.... ##:'##.... ##:\n";
      mensaje +="##::::::: ####: ##: ##:::..:: ##::::::: ####: ##: ##:::: ##:: ##:: ##:::: ##: ##:::: ##:\n";
      mensaje +="######::: ## ## ##: ##::::::: ######::: ## ## ##: ##:::: ##:: ##:: ##:::: ##: ##:::: ##:\n";
      mensaje +="##...:::: ##. ####: ##::::::: ##...:::: ##. ####: ##:::: ##:: ##:: ##:::: ##: ##:::: ##:\n";
      mensaje +="##::::::: ##:. ###: ##::: ##: ##::::::: ##:. ###: ##:::: ##:: ##:: ##:::: ##: ##:::: ##:\n";
      mensaje +="########: ##::. ##:. ######:: ########: ##::. ##: ########::'####: ########::. #######::\n";
      mensaje +="........::..::::..:::......:::........::..::::..::........:::....::........::::.......:::1\n"; 
    return mensaje;
  } //end mensaje_Encendido



  
  String rot_apagado(){
    String mensaje;
      mensaje +=":::'###::::'########:::::'###:::::'######::::::'###::::'########:::'#######::\n";
      mensaje +="::'## ##::: ##.... ##:::'## ##:::'##... ##::::'## ##::: ##.... ##:'##.... ##:\n";
      mensaje +=":'##:. ##:: ##:::: ##::'##:. ##:: ##:::..::::'##:. ##:: ##:::: ##: ##:::: ##:\n";
      mensaje +="'##:::. ##: ########::'##:::. ##: ##::'####:'##:::. ##: ##:::: ##: ##:::: ##:\n";
      mensaje +=" #########: ##.....::: #########: ##::: ##:: #########: ##:::: ##: ##:::: ##:\n";
      mensaje +=" ##.... ##: ##:::::::: ##.... ##: ##::: ##:: ##.... ##: ##:::: ##: ##:::: ##:\n";
      mensaje +=" ##:::: ##: ##:::::::: ##:::: ##:. ######::: ##:::: ##: ########::. #######::\n";
      mensaje +=" ..:::::..::..:::::::::..:::::..:::......::::..:::::..::........::::.......:::0\n";
    return mensaje;
  } //end mensaje_Apagado



  
  String rot_subiendo(){
    String mensaje;
      mensaje+=":'######::'##::::'##:'########::'####:'########:'##::: ##:'########:::'#######::\n";
      mensaje+="'##... ##: ##:::: ##: ##.... ##:. ##:: ##.....:: ###:: ##: ##.... ##:'##.... ##:\n";
      mensaje+=" ##:::..:: ##:::: ##: ##:::: ##:: ##:: ##::::::: ####: ##: ##:::: ##: ##:::: ##:\n";
      mensaje+=". ######:: ##:::: ##: ########::: ##:: ######::: ## ## ##: ##:::: ##: ##:::: ##:\n";
      mensaje+=":..... ##: ##:::: ##: ##.... ##:: ##:: ##...:::: ##. ####: ##:::: ##: ##:::: ##:\n";
      mensaje+="'##::: ##: ##:::: ##: ##:::: ##:: ##:: ##::::::: ##:. ###: ##:::: ##: ##:::: ##:\n";
      mensaje+=". ######::. #######:: ########::'####: ########: ##::. ##: ########::. #######::\n";
      mensaje+=":......::::.......:::........:::....::........::..::::..::........::::.......:::\n";
    return mensaje;
  } //end rot_subiendo




  String rot_bajando(){
    String mensaje;
        mensaje+="########:::::'###::::::::::'##::::'###::::'##::: ##:'########:::'#######::\n";
        mensaje+="##.... ##:::'## ##::::::::: ##:::'## ##::: ###:: ##: ##.... ##:'##.... ##:\n";
        mensaje+="##:::: ##::'##:. ##:::::::: ##::'##:. ##:: ####: ##: ##:::: ##: ##:::: ##:\n";
        mensaje+="########::'##:::. ##::::::: ##:'##:::. ##: ## ## ##: ##:::: ##: ##:::: ##:\n";
        mensaje+="##.... ##: #########:'##::: ##: #########: ##. ####: ##:::: ##: ##:::: ##:\n";
        mensaje+="##:::: ##: ##.... ##: ##::: ##: ##.... ##: ##:. ###: ##:::: ##: ##:::: ##:\n";
        mensaje+="########:: ##:::: ##:. ######:: ##:::: ##: ##::. ##: ########::. #######::\n";
        mensaje+="........:::..:::::..:::......:::..:::::..::..::::..::........::::.......:::\n";
    return mensaje;
  } //end rot_bajando




  String rot_parada(){
    String mensaje;
        mensaje+="########:::::'###::::'########:::::'###::::'########:::::'###::::\n";
        mensaje+="##.... ##:::'## ##::: ##.... ##:::'## ##::: ##.... ##:::'## ##:::\n";
        mensaje+="##:::: ##::'##:. ##:: ##:::: ##::'##:. ##:: ##:::: ##::'##:. ##::\n";
        mensaje+="########::'##:::. ##: ########::'##:::. ##: ##:::: ##:'##:::. ##:\n";
        mensaje+="##.....::: #########: ##.. ##::: #########: ##:::: ##: #########:\n";
        mensaje+="##:::::::: ##.... ##: ##::. ##:: ##.... ##: ##:::: ##: ##.... ##:\n";
        mensaje+="##:::::::: ##:::: ##: ##:::. ##: ##:::: ##: ########:: ##:::: ##:\n";
        mensaje+="..:::::::::..:::::..::..:::::..::..:::::..::........:::..:::::..::\n";
    return mensaje;
  }




  String mensaje_persiana_subir(){
    String mensaje;
      mensaje += rot_persiana();
      mensaje += rot_subiendo();    
    return mensaje;
  } //end mensaje_persiana_subir




  String mensaje_persiana_bajar(){
    String mensaje;
      mensaje += rot_persiana();
      mensaje += rot_bajando();
    return mensaje;
  } //end mensaje_persiana_bajar




  String mensaje_persiana_parar(){
    String mensaje;
      mensaje += rot_persiana();
      mensaje += rot_parada();
    return mensaje;
  } //end mensaje_persiana_parar




  String mensaje_enchufe_on(){
    String mensaje;
      mensaje += rot_enchufe();
      mensaje += rot_encendido();
    return mensaje;
  } //end mensaje_enchufe_on



  
  String mensaje_enchufe_off(){
    String mensaje;
      mensaje += rot_enchufe();
      mensaje += rot_apagado();  
    return mensaje;
  } //end mensaje_enchufe_off



  
  String mensaje_interruptor_on(){
    String mensaje;
      mensaje += rot_interruptor();
      mensaje += rot_encendido();
    return mensaje;
  } //end mensaje_interruptor_on




  String mensaje_interruptor_off(){
    String mensaje;
      mensaje += rot_interruptor();
      mensaje += rot_apagado();
    return mensaje;
  } //end mensaje_interruptor_off

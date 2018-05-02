#include "MaxMatrixESP.h"
#include "drawing.h"
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <WebSocketsServer.h>

// Définition des constantes du jeu
#define NB_DEVICES_X 8
#define NB_DEVICES_Y 4
#define OBJECTIF 200



#define PIN D1


// Instanciation Server socket et matrice de led
ESP8266WiFiMulti WiFiMulti;
WebSocketsServer webSocket = WebSocketsServer(1099);
MaxMatrixESP matrice = MaxMatrixESP(NB_DEVICES_X, NB_DEVICES_Y, D8, 10);

int score = 0;

// Procédure appelée lors d'arrivée de messages sockets
void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t lenght) {

  switch (type) {
    case WStype_DISCONNECTED:
      break;
    case WStype_CONNECTED:
      {
        IPAddress ip = webSocket.remoteIP(num);
      }
      break;
    
    // Réception d'un message textuel
    case WStype_TEXT:
      {

        String message = String((char *) &payload[0]);
        Serial.println("-----------------------------");
        Serial.println(message);

        // Action à réaliser
        if (message.indexOf("ACTION") != -1) {
          
          if (message.indexOf("off") != -1) {
            Serial.println("Extinction LED");
            digitalWrite(PIN, 0);
          }

          if (message.indexOf("on") != -1) {
            Serial.println("Allumage LED");
            digitalWrite(PIN, 1);
          }

          if (message.indexOf("clr") != -1) {
            matrice.setRectangle(1, 1, 8 * NB_DEVICES_X, 8 * NB_DEVICES_Y, 0);
            matrice.render();
          }

          if (message.indexOf("act") != -1) {
            Serial.println("Robot ari en action");
            matrice.set2ByteDrawing(_2ByteDrawing_[1], 1, 1, 1);
            matrice.render();
          }

          if (message.indexOf("abeille") != -1) {
            Serial.println("L'abeille part butiner !");
            for (int x=8*NB_DEVICES_X+1;x>-32;x--){
              matrice.set4ByteDrawing(_4ByteDrawing_[5], x, 1, 1);
              matrice.render();
              matrice.set4ByteDrawing(_4ByteDrawing_[5], x, 1, 0);}
          }

          if (message.indexOf("dead") != -1) {
            Serial.println("Oh non, big robot est mort !!!");
          }

          if (message.indexOf("ari") != -1) {
            matrice.setString("ARI", 1, 1, 1, 1);
            matrice.render();
          }
        }

        // Afficher phrasel
        else if (message.indexOf("PHRASE") != -1) {
          String x = (message.substring(7, 9)), y = (message.substring(10, 12));
          String phrase = (message.substring(13, message.length()));

          matrice.setString(phrase, 1, x.toInt(), y.toInt(), 1);
          matrice.render();
          
          Serial.printf("Phrase en %d / %d \n",  x.toInt(),  y.toInt());
          Serial.print(x); Serial.println(y);
          Serial.println(phrase);
        }

        // Phrase à faire passer
        else if (message.indexOf("SCROLL") != -1) {
          String taille = (message.substring(7, 8)), v = (message.substring(9, 10)), y = (message.substring(11, 13));
          String phrase = (message.substring(14, message.length()));
          
          Serial.println(phrase);
          Serial.printf("dernier %d\n", -8*phrase.length());
          int ti=taille.toInt(), vi=v.toInt(), yi=y.toInt();
          for (int x=8*NB_DEVICES_X+1;x+8*phrase.length()>0;x--){
              Serial.printf("Phrase en %d / %d \n",  x,  yi);
              matrice.setString(phrase, ti, x, yi, 1);
              matrice.render();
              delay(vi);    
              matrice.setString(phrase, ti, x, yi, 0);}
        }

        // Autre messages
        else {
          Serial.printf("Message inconnu");
        }

      }
      break;

    case WStype_BIN:
      {
        hexdump(payload, lenght);
      }
      webSocket.sendBIN(num, payload, lenght);
      break;

  }
}

void afficher(String message){


  
        Serial.println("-----------------------------");
        Serial.println(message);
        if (message.indexOf("RESET") != -1) {
            ESP.reset();
          }
        // Action à réaliser
        if (message.indexOf("ACTION") != -1) {
          
          if (message.indexOf("off") != -1) {
            Serial.println("Extinction LED");
            digitalWrite(PIN, 0);
          }

          if (message.indexOf("on") != -1) {
            Serial.println("Allumage LED");
            digitalWrite(PIN, 1);
          }

          if (message.indexOf("clr") != -1) {
            matrice.setRectangle(1, 1, 8 * NB_DEVICES_X, 8 * NB_DEVICES_Y, 0);
            matrice.render();
          }

          if (message.indexOf("act") != -1) {
            Serial.println("Robot ari en action");
            matrice.set4ByteDrawing(_4ByteDrawing_[1], 1, 1, 1);
            matrice.render();
            delay(3000);
            
            matrice.set4ByteDrawing(_4ByteDrawing_[1], 1, 1, 0);
          }

          if (message.indexOf("abeille") != -1) {
            Serial.println("L'abeille part butiner !");
            for (int x=8*NB_DEVICES_X+1;x>0;x--){
              matrice.set4ByteDrawing(_4ByteDrawing_[5], x, 1, 1);
              matrice.render();
              matrice.set4ByteDrawing(_4ByteDrawing_[5], x, 1, 0);}
          }

          if (message.indexOf("dead") != -1) {
            Serial.println("Oh non, big robot est mort !!!");
          }

          if (message.indexOf("ari") != -1) {
            matrice.setString("ari",  1, 1, 1, 1);
            matrice.render();
          }
        }

        // Afficher phrasel
        else if (message.indexOf("PHRASE") != -1) {
          String x = (message.substring(7, 9)), y = (message.substring(10, 12));
          String phrase = (message.substring(13, message.length()));

          matrice.setString(phrase, 1, x.toInt(), y.toInt(), 1);
          matrice.render();
          
          Serial.printf("Phrase en %d / %d \n",  x.toInt(),  y.toInt());
          Serial.print(x); Serial.println(y);
          Serial.println(phrase);
        }

        // Phrase à faire passer
        else if (message.indexOf("SCROLL") != -1) {
          String taille = (message.substring(7, 8)), v = (message.substring(9, 10)), y = (message.substring(11, 13));
          String phrase = (message.substring(14, message.length()));
          
          Serial.println(phrase);
          Serial.printf("dernier %d", -8*phrase.length());
          int ti=taille.toInt(), vi=v.toInt(), yi=y.toInt();
          for (int x=8*NB_DEVICES_X+1;x+8*phrase.length()>0;x--){
              Serial.printf("Phrase en %d / %d \n",  x,  yi);
              matrice.setString(phrase, ti, x, yi, 1);
              matrice.render();
              delay(vi);    
              matrice.setString(phrase, ti, x, yi, 0);}
        }

        // Autre messages
        else {
          Serial.printf("Message inconnu");
        }

      
}

void setup() {
  Serial.begin(115200);
  delay(10000);
  Serial.println("Temps d'attente teminée ");
  
  // Initialisation matrice
  Serial.println("Matrice initialisation ... ");
  matrice.init(40000);
  matrice.render();
   Serial.println("Done ");
  //Test LED
  //pinMode(PIN, OUTPUT);
  //digitalWrite(PIN, 1);

 
  delay(1000);
  // Initialisation du Point d'Accès WI-FI
   WiFiMulti.addAP("APname", "password");

  //WiFi.disconnect();
  while(WiFiMulti.run() != WL_CONNECTED) {
    delay(100);
  }

  delay(1000);
  // Initialisation server Socket
  Serial.println("Start Websocket Server");
  webSocket.begin();
  webSocket.onEvent(webSocketEvent);

  delay(1000);
  afficher(String("SCROLL:1:1:09:C EST PARTI"));

}
int n=0;
void loop() {
  //Serial.printf("Attente | Score %d | Obj %d\n",score,OBJECTIF);
  /*
    afficher(String("PHRASE:01:01:OBJ 150"));
    delay(1000);
    afficher(String("SCROLL:1:1:09:C EST PARTI"));
    delay(1000);
    afficher(String("SCROLL:1:1:09:COUCOU EJAZ COMMENT CA VA ? @ ; :"));
    delay(1000);
    afficher(String("ACTION:clr"));
    afficher(String("ACTION:act"));
    afficher(String("ACTION:abeille"));
    afficher(String("ACTION:clr"));
    */
    
    
  webSocket.loop();
}

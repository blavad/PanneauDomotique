#include "MaxMatrixESP.h"
#include "drawing.h"
#include <ESP8266WiFi.h>
#include <WebSocketsServer.h>

// Définition des constantes du jeu
#define NB_DEVICES_X 8
#define NB_DEVICES_Y 2
#define OBJECTIF 200


#define PIN D1

// Paramètres IP du point d'accès WiFi
IPAddress local_IP(192, 168, 4, 1);
IPAddress gateway(192, 168, 4, 1);
IPAddress subnet(255, 255, 255, 0);

// Instanciation Server socket et matrice de led
WebSocketsServer webSocket = WebSocketsServer(81);
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

          if (message.indexOf("clearscreen") != -1) {
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
          }

          if (message.indexOf("dead") != -1) {
            Serial.println("Oh non, big robot est mort !!!");
          }

          if (message.indexOf("ari") != -1) {
            matrice.setWord("ari", 3, 1, 12, 5, 1);
            matrice.render();
          }
        }

        // Afficher phrase
        else if (message.indexOf("PHRASE") != -1) {
          String x = (message.substring(7, 9)), y = (message.substring(10, 12));
          String phrase = (message.substring(13, message.length()));

          matrice.setString(phrase, 1, x.toInt(), y.toInt(), 1);
          
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
              delay(vi*10);    
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

void setup() {
  Serial.begin(115200);

  //Test LED
  pinMode(PIN, OUTPUT);
  digitalWrite(PIN, 1);

  // Initialisation du Point d'Accès WI-FI
  Serial.println();
  Serial.println("Setting soft-AP configuration ...");
  Serial.println(WiFi.softAPConfig(local_IP, gateway, subnet) ? "Ready" : "Failed");

  //Affichage de l'adresse IP
  Serial.println("Setting soft-AP ...");
  Serial.println(WiFi.softAP("ESP_ARI") ? "Ready" : "Failed");
  Serial.println("Soft-AP IP address = ");
  Serial.println(WiFi.softAPIP());

  // Initialisation server Socket
  Serial.println("Start Websocket Server");
  webSocket.begin();
  webSocket.onEvent(webSocketEvent);

  // Initialisation matrice
  Serial.println("Matrice initialisation ... ");
  matrice.init(40000);
  matrice.render();
  Serial.println("Done ");

}

void loop() {
  //Serial.printf("Attente | Score %d | Obj %d\n",score,OBJECTIF);
  webSocket.loop();
}

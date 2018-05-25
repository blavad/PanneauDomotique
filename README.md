# PanneauDomotique

 Réalisation d'un panneau domotique composé de :

- 1 ESP8266
- n * p matrices de led de dimension 8x8 branchées en série


Fonctionnalités : 
- Communication réseau avec un autre programme
- Affichage de phrase, dessins, lettres, figures géométriques, etc
- Utilisation d'un programme intéractif pour simuler un dessin sur le panneau

Usage :
  1) Faire transiter un message 
    - SCROLL:T:V:YY:Mon message à afficher     
        - T : taille (1,2 ou 4 octets) 
        - V : vitesse (Vmax=0 - Vmin=9 )
        - YY : Position horizontal de du message
        
  2) Réaliser une action prédéfini 
    - ACTION:Nom de l'action
  
  3) Ecrire quelquechose de taille 1 octet quelquepar 
    - PHRASE:XX:YY:Ma message 
        - XX : Coordonnées horizontales
        - YY : Coordonnées horizontales

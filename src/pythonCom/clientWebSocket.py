import DummyClient

esp8266host = "ws://192.168.1.77:1099/"

try:
    ws = DummyClient.DummyClient(esp8266host)
    ws.connect()
    print("Ready !")
    
    while (1) :
        mode=raw_input()
        if mode == "":
            break
        print "Message : ",mode
        ws.send(mode)
        
    print("Demo finish, close Websocket connexion now and exit script")
    ws.send("SCROLL:1:1:01:END")
    ws.close()
    exit()
        
except KeyboardInterrupt:
    ws.send("SCROLL:1:1:01:Connexion closed")
    ws.close()
        

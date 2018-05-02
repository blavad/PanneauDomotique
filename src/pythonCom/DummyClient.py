from ws4py.client.threadedclient import WebSocketClient
import time, requests
  
class DummyClient(WebSocketClient):
    def opened(self):
        print("Websocket open")
    def closed(self, code, reason=None):
        print "Connexion closed down", code, reason
    def received_message(self, m):
        print m
 
"""
if __name__ == '__main__':
    try:
        ws = DummyClient(esp8266host)
        ws.connect()
        print("Ready !")

        while (1) :
            mode=raw_input()
            if mode == "":
                break
            print "Message : ",mode
            ws.send(mode)
                
 
        print("Demo finish, close Websocket connexion now and exit script")
        ws.send("phrase:1:8:END")
        ws.close()
        exit()
 
    except KeyboardInterrupt:
    	ws.send("phrase:01:08:END")
        ws.close()
"""

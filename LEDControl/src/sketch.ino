#include <UIPServer.h>
#include <UIPEthernet.h>
#include <ethernet_comp.h>
#include <Dhcp.h>
#include <UIPClient.h>
#include <UIPUdp.h>
#include <Dns.h>


byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};

boolean status = false;
String request = "";
EthernetServer server(80);

void setup() {
  pinMode(4, OUTPUT);
  // Open serial communications and wait for port to open:
  // start the Ethernet connection and the server:
  Ethernet.begin(mac, IPAddress(192, 168, 0, 11));
  server.begin();
}


void loop() {
  EthernetClient client = server.available();
  if (client) {
    request = "";
    boolean currentLineIsBlank = true;
    
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        request.concat(c);
        if (c == '\n' && currentLineIsBlank) {
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Access-Control-Allow-Origin: *");
          client.println();
          if (request.indexOf("T /?command=turnon") > 0)
          {
            digitalWrite(4, HIGH);
            status = true;
          }
          
          if (request.indexOf("T /?command=turnoff") > 0)
          {
            digitalWrite(4, LOW);
            status = false;
          }

          if (request.indexOf("T /?command=check") > 0)
          {
            if (status == true)
            {
              client.print("LED is on");
            }
            else
            {
              client.print("LED is off");          
            }
          }

          if (request.indexOf("T /?command=toggle") > 0)
          {
            if (status == true)
            {
              client.print("Turned off LED");
              digitalWrite(4, LOW);
              status = false;
            }
      	    else
            {
              client.print("Turned on LED");
              digitalWrite(4, HIGH);
              status = true;
            }
          }
          break;
        }
        if (c == '\n') {
          // you're starting a new line
          currentLineIsBlank = true;
        } else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
    // give the web browser time to receive the data
    delay(1);
    // close the connection:
    client.stop();
  }
}

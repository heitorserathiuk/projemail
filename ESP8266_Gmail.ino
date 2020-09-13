#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "Gsender.h"

#pragma region Globals
const char* ssid = "NOME_WIFI";                           // WIFI network name
const char* password = "SENHA_WIFI";                       // WIFI network password
uint8_t connection_state = 0;                    // Connected to WIFI or not
ESP8266WebServer server(80);
String sensorValue;
#pragma endregion Globals

uint8_t WiFiConnect(const char* nSSID = nullptr, const char* nPassword = nullptr)
{
  static uint16_t attempt = 0;
  Serial.print("Connecting to ");
  if (nSSID) {
    WiFi.begin(nSSID, nPassword);
    Serial.println(nSSID);
  } else {
    WiFi.begin(ssid, password);
    Serial.println(ssid);
  }

  uint8_t i = 0;
  while (WiFi.status() != WL_CONNECTED && i++ < 50)
  {
    delay(200);
    Serial.print(".");
  }
  ++attempt;
  Serial.println("");
  if (i == 51) {
    Serial.print("Connection: TIMEOUT on attempt: ");
    Serial.println(attempt);
    if (attempt % 2 == 0)
      Serial.println("Check if access point available or SSID and Password\r\n");
    return false;
  }
  Serial.println("Connection: ESTABLISHED");
  Serial.print("Got IP address: ");
  Serial.println(WiFi.localIP());
  return true;
}

void Awaits()
{
  uint32_t ts = millis();
  while (!connection_state)
  {
    delay(50);
    if (millis() > (ts + 10000) && !connection_state) {
      connection_state = WiFiConnect();
      ts = millis();
    }
  }
}

//void setup()
//{
//    Serial.begin(9600);
//    connection_state = WiFiConnect();
//    if(!connection_state)  // if not connected to WIFI
//        Awaits();          // constantly trying to connect

//    server.on("/email", handleEmail);
//    server.begin();
//}

void setup() {
  delay(1000);
  Serial.begin(9600); // Vamos usar para debug

  // Conectando à rede WiFi
  Serial.println();
  Serial.println();
  Serial.print("Conectando com: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi conectado com sucesso");

  server.on("/email", handleEmail);   //Associate the handler function to the path

  // Startando o servidor
  server.begin();
  Serial.print("Servidor startado em ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
}

void loop() {
  server.handleClient();
}

void handleEmail() {
  sensorValue =  String(analogRead(0), DEC);  
  Serial.println("Valor LDR :");
  Serial.println(sensorValue);   // print out the value you read
  
  String message = "";
  if (server.arg("email") == "") {   //Parameter not found
    message = "Email Argument not found";
  } else {    //Parameter found
    message = "Email Argument = ";
    message += server.arg("email");     //Gets the value of the query parameter
  }
  if (server.arg("tipo") == "") {   //Parameter not found
    message += "\nTipo Argument not found";
  } else {    //Parameter found
    message += "\nTipo Argument = ";
    message += server.arg("tipo");     //Gets the value of the query parameter
  }

  Gsender *gsender = Gsender::Instance();    // Getting pointer to class instance

  if (server.arg("tipo") == "1") {
    String subject = "Subject Tipo1";
    //String body = "<img src=\"https://2.bp.blogspot.com/-vQhpc6Vec2M/UdIebTlKU3I/AAAAAAAAAUM/epNeS4f7eGk/s1600/ULTIMO.jpg\" style=\"max-width: 1055px;padding-bottom: 0;display: inline !important;vertical-align: bottom;border: 0;height: auto;outline: none;text-decoration: none;-ms-interpolation-mode: bicubic;\" class=\"mcnImage\" width=\"564\" align=\"middle\">";
    String body ="Tipo1";
    body.concat(sensorValue);
    if (gsender->Subject(subject)->Send(server.arg("email"), body)) {
      message += "\nMessage 1 send.Valor LDR : "+sensorValue;
    } else {
      message += "\nError sending message: ";
      message += gsender->getError();
    }
  }

  if (server.arg("tipo") == "2") {
    String subject = "Subject Tipo2";
    //String body = "<img src=\"https://i.pinimg.com/originals/d7/5a/e1/d75ae1ae332cb9f6e2d1fadf5b90e115.jpg\" style=\"max-width: 1055px;padding-bottom: 0;display: inline !important;vertical-align: bottom;border: 0;height: auto;outline: none;text-decoration: none;-ms-interpolation-mode: bicubic;\" class=\"mcnImage\" width=\"564\" align=\"middle\">";
    String body ="Tipo2";
    body.concat(sensorValue);
    if (gsender->Subject(subject)->Send(server.arg("email"), body)) {
      message += "\nMessage 2 send.Valor LDR : "+sensorValue;
    } else {
      message += "\nError sending message: ";
      message += gsender->getError();
    }
  }

  if (server.arg("tipo") == "3") {
    String subject = "Subject Tipo3";
    //String body = "<img src=\"https://i.pinimg.com/originals/be/b0/fe/beb0fef7afade9410e7e1cfa383a70b2.gif\" style=\"max-width: 1055px;padding-bottom: 0;display: inline !important;vertical-align: bottom;border: 0;height: auto;outline: none;text-decoration: none;-ms-interpolation-mode: bicubic;\" class=\"mcnImage\" width=\"564\" align=\"middle\">";
    String body ="Tipo3";
    body.concat(sensorValue);
    if (gsender->Subject(subject)->Send(server.arg("email"), body)) {
      message += "\nMessage 3 send.Valor LDR : "+sensorValue;
    } else {
      message += "\nError sending message: ";
      message += gsender->getError();
    }
  }  

  if (server.arg("tipo") == "4") {
    String subject = "Subject Tipo4";
    //String body = "<img src=\"https://i.pinimg.com/originals/1f/49/e5/1f49e5745f1c188ecca4fdd83e24f3a4.jpg\" style=\"max-width: 1055px;padding-bottom: 0;display: inline !important;vertical-align: bottom;border: 0;height: auto;outline: none;text-decoration: none;-ms-interpolation-mode: bicubic;\" class=\"mcnImage\" width=\"564\" align=\"middle\">";
    String body ="Tipo4";
    body.concat(sensorValue);
    if (gsender->Subject(subject)->Send(server.arg("email"), body)) {
      message += "\nMessage 4 send.Valor LDR : "+sensorValue;
    } else {
      message += "\nError sending message: ";
      message += gsender->getError();
    }
  }  

    if (server.arg("tipo") == "5") {
    String subject = "Subject Tipo5";
    //String body = "<img src=\"https://i.pinimg.com/originals/fc/fa/28/fcfa289cf10ec19ad54e5b24a3be22d5.jpg\" style=\"max-width: 1055px;padding-bottom: 0;display: inline !important;vertical-align: bottom;border: 0;height: auto;outline: none;text-decoration: none;-ms-interpolation-mode: bicubic;\" class=\"mcnImage\" width=\"564\" align=\"middle\">";
    String body ="Tipo5";
    body.concat(sensorValue);
    if (gsender->Subject(subject)->Send(server.arg("email"), body)) {
      message += "\nMessage 5 send.Valor LDR : "+sensorValue;
    } else {
      message += "\nError sending message: ";
      message += gsender->getError();
    }
  }  
  server.send(200, "text/plain", message);          //Returns the HTTP response
}
#include <PubSubClient.h>

#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* ssid = "INSTALANDO_VIRUS"; 
const char* password = "999730013";
const char* mqttServer = "m16.cloudmqtt.com"; 
const int mqttPort = 10130; 
const char* mqttUser = "vojlyjoj"; 
const char* mqttPassword = "Tz94RU1KDTwV"; 

WiFiClient espClient;
PubSubClient client(espClient);
/*
 * TABELA DE PORTAS A SER USADA CASO NESSECITE
-------------------------------------------------
NodeMCU / ESP8266  |  NodeMCU / ESP8266  |
D0 = 16            |  D6 = 12            |
D1 = 5             |  D7 = 13            |
D2 = 4             |  D8 = 15            |
D3 = 0             |  D9 = 3             |
D4 = 2             |  D10 = 1            |
D5 = 14            |                     |
-------------------------------------------------
*/

/*PORTA NO ESP8266 D4*/
const int LED1 = 2; 

/*PORTA NO ESP8266 D3*/
const int LED2 = 0;

/*PORTA NO ESP8266 D5*/
const int LED3 = 4;

const int RED = 13;
const int GREEN = 12;
const int BLUE = 14;


/*TRATA DADOS E INFORMAÇOES RECEBIDO PELO MQTT*/
void mqtt_callback(char* topic, byte* dados_tcp, unsigned int length);

void setup() { 
  
  /*DECLARAÇAO DE PINOS*/
  
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
  
  Serial.begin(115200);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) 
  {   
     delay(100);
    Serial.println("Conectando a WiFi..");
  }
  Serial.println("Conectado!"); 
  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);
 
  while (!client.connected()) {
    Serial.println("Conectando ao servidor MQTT...");
    
    if (client.connect("Projeto", mqttUser, mqttPassword ))
    {
 
      Serial.println("Conectado ao servidor MQTT!");  
 
    } else {
 
      Serial.print("Falha ao conectar ");
      Serial.print(client.state());
      delay(2000);
 
    }
  }

 /*PRIMEIRO ARGUMENTO É O TOPICO E O SEGUNDO ARGUMENTO E A MENSAGEM VISTA NO MQTT*/
  client.publish("Status ","Reiniciado!");
  client.publish("Placa","Em funcionamento!");
  client.subscribe("SALA"); 
  client.subscribe("QUARTO");
  client.subscribe("WC");
  client.subscribe("RGB");
}

void callback(char* topic, byte* dados_tcp, unsigned int length) {
    for (int i = 0; i < length; i++) {
      }
  /*VALIDAÇAO DE LIGAR E DESLIGAR O LED => L1 LIGA O LED1 E D1 DESLIGA O LED1*/
  if ((char)dados_tcp[0] == 'L' && (char)dados_tcp[1] == '1') {
    
    digitalWrite(LED1, HIGH); 
    
  } else if((char)dados_tcp[0] == 'D' && (char)dados_tcp[1] == '1'){
    digitalWrite(LED1, LOW);  
  }
  /*VALIDAÇAO DE LIGAR E DESLIGAR O LED => L2 LIGA O LED2 E D2 DESLIGA O LED2*/
  if ((char)dados_tcp[0] == 'L' && (char)dados_tcp[1] == '2') {
    
    digitalWrite(LED2, HIGH);   

  } else if((char)dados_tcp[0] == 'D' && (char)dados_tcp[1] == '2'){
    digitalWrite(LED2, LOW);  
  }

  /*VALIDAÇAO DE LIGAR E DESLIGAR O LED => L3 LIGA O LED3 E D3 DESLIGA O LED3*/
  if((char)dados_tcp[0] == 'L' && (char)dados_tcp[1] == '3'){
    
    digitalWrite(LED3, HIGH);
    
  /*}else if((char)dados_tcp[0] == 'D' && (char)dados_tcp[1] == '3'){
    digitalWrite(LED3, LOW);
    
  }else if((char)dados_tcp[0] == 'D' && (char)dados_tcp[1] == '4'){
    digitalWrite(BLUE, LOW);
    digitalWrite(GREEN, LOW);
    digitalWrite(RED, LOW);
    }
    
  while((char)dados_tcp[0] == 'L' && (char)dados_tcp[1] == '4'){
    digitalWrite(BLUE, LOW);
    digitalWrite(GREEN, HIGH);
    digitalWrite(RED, LOW);
    delay(100);
    
    digitalWrite(BLUE, HIGH);
    digitalWrite(GREEN, LOW);
    digitalWrite(RED, HIGH);
    delay(100);
    
    digitalWrite(BLUE, LOW);
    digitalWrite(GREEN, HIGH);
    digitalWrite(RED, LOW);
    delay(100);
    }*/
} 

void loop() {        
     client.loop();
 }

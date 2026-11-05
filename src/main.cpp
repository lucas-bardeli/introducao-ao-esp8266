/* Baseado no projeto de ESP32 da Wokwi, com alguns ajustes para o ESP8266
   https://wokwi.com/projects/320964045035274834
*/

#include <Arduino.h>          // Carrega biblioteca padrão Arduino
#include <ESP8266WiFi.h>      // Carrega biblioteca do ESP8266 para conexão ao wifi
#include <ESP8266WebServer.h> // Carrega biblioteca do ESP8266 - Mini servidor web
#include <uri/UriBraces.h>    // Carrega biblioteca que permite passar parametros pela URI

#define WIFI_SSID "IoT-FATEC"    // Define a variável para o nome da rede sem fio onde o ESP8266 irá se conectar
#define WIFI_PASSWORD "12345678" // Define a senha da rede sem fio

ESP8266WebServer server(80); // Função que inicializa o servidor web interno da placa

bool ledState = false; // Cria váriavel chamada ledState que vai armazenar o estado do LED (ligado ou desligado)

void sendHtml()
{
  String response = R"(
    <!DOCTYPE html><html>
      <head>
        <title>ESP8266 - Web Server com controle de GPIO</title>
        <meta name="viewport" content="width=device-width, initial-scale=1">
        <style>
          html { font-family: sans-serif; text-align: center; }
          body { display: inline-flex; flex-direction: column; }
          h1 { margin-bottom: 1.2em; }
          h2 { margin: 0; }
          div { display: grid; grid-template-columns: 1fr; grid-template-rows: auto auto; grid-auto-flow: column; grid-gap: 1em; }
          .btn { background-color: #5B5; border: none; color: #fff; padding: 0.5em 1em;
                 font-size: 2em; text-decoration: none }
          .btn.Desligado { background-color: #333; }
        </style>
      </head>  
      <body>
        <h1>ESP8266 Web Server</h1>
        <div>
          <h2>Controle do LED Integrado</h2>
          <a href="/toggle/1" class="btn LED_TEXT">LED_TEXT</a>
        </div>
      </body>
    </html>
  )";
  response.replace("LED_TEXT", ledState ? "Desligado" : "Ligado");
  server.send(200, "text/html", response);
}

// Configurar e inicializar placa IoT
void setup(void)
{
  Serial.begin(115200);         // Função pra inicializar o monitor serial
  pinMode(LED_BUILTIN, OUTPUT); // Define a GPIO do LED integrado da placa como saída
  delay(2000);                  // Aguarda 2 segundos para inicializar o monitor serial
  Serial.println("Iniciando o ESP8266...");

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);  // Função Wifi.begin - inicializar o wifi da placa IoT
  Serial.print("Conectando no Wi-Fi: "); // Imprime no monitor serial sobre o que está acontecendo
  Serial.println(WIFI_SSID);             // Imprime no monitor serial o nome da rede wifi onde a placa será conectada

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(100);        // Laço de repetição
    Serial.print("."); // Fica preso nesse laço até se conectar na rede sem fio configurada
  }
  Serial.println("\nConectado ao Wi-Fi!"); // Assim que estiver conectado, escreve a mensagem no monitor serial

  Serial.print("IP address: ");
  Serial.println(WiFi.localIP()); // Imprime no monitor serial o endereço IP que ele ganhou da rede sem fio

  server.on("/", sendHtml);

  server.on(UriBraces("/toggle/{}"), []()
            {
    String led = server.pathArg(0);

    switch (led.toInt()) {
      case 1:
        ledState = !ledState;
        digitalWrite(LED_BUILTIN, ledState);
        Serial.printf("LED %s\n", ledState ? "desligado!" : "ligado!");
        break;
    }
  
    sendHtml(); });

  server.begin();
  Serial.println("Servidor HTTP iniciado!");
}

void loop(void)
{
  server.handleClient();
  delay(10);
}

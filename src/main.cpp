// Exemplo básico para acender e apagar o led integrado da placa ESP8266
#include <Arduino.h>

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT); // Inicializa o LED Bultin (soldado) na placa
}

// Inicia o loop
void loop()
{
  digitalWrite(LED_BUILTIN, LOW);  // Acende o LED (Nesse caso, LOW é a tensão utilizada para acender o led, pois ele é ligado na outra ponta ao positivo da placa + resistor interno)
  delay(1000);                     // Espera 1 segundo
  digitalWrite(LED_BUILTIN, HIGH); // Apaga o LED jogando o nível de tensão para HIGH
  delay(2000);                     // Espera 2 segundos
}

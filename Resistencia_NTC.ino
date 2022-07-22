/******************************************************************************
             Utilize o Termistor NTC junto de um ESP32 como Termômetro
               Sketch de Exemplo - Medindo a resistência do termistor

                          Criado em 06 de Maio de 2021
                                por Michel Galvão

  Eletrogate - Loja de Arduino \\ Robótica \\ Automação \\ Apostilas \\ Kits
                            https://www.eletrogate.com/
******************************************************************************/

// Protótipo das Funções
float getResistencia(int pin, float voltageUc, float adcResolutionUc, float resistenciaEmSerie);

void setup() {
  Serial.begin(115200);
}

void loop() {
  Serial.print("Resistência:");
  float resistencia = getResistencia(13, 3.3, 4095.0, 10000.0);
  Serial.println(resistencia);
  delay(500);
}

/**
  Obtém a resistência de uma porta analógica informada do microcontrolador. Para isso,
  deve-se estar conectado  um resistor em série na montagem de um divisor de tensão.

  @param pin - O pino da porta à ser medida a resistência.
  @param voltageUc - A tensão nominal do microcontrolador.
  @param adcResolutionUc - O valor máximo da saída do
    ADC (Arduino UNO = 1024.0 | ESP32 = 4095.0).
  @param resistenciaEmSerie - A resistência do resistor em série ao qual
    está conectado à porta analógica.

  @return a resistência, em OHM, obtida.
*/
float getResistencia(int pin, float voltageUc, float adcResolutionUc, float resistenciaEmSerie) {
  float resistenciaDesconhecida = 0;

  resistenciaDesconhecida =
    resistenciaEmSerie *
    (voltageUc /
     (
       (analogRead(pin) * voltageUc) /
       adcResolutionUc
     ) - 1
    );

  return resistenciaDesconhecida;
}

/******************************************************************************
             Utilize o Termistor NTC junto de um ESP32 como Termômetro
        Sketch de Exemplo - Algoritmo de cálculo da Temperatura do Termistor

                          Criado em 06 de Maio de 2021
                                por Michel Galvão

  Eletrogate - Loja de Arduino \\ Robótica \\ Automação \\ Apostilas \\ Kits
                            https://www.eletrogate.com/
******************************************************************************/

// Protótipo das Funções
float readTemperatureNTC(float resistenciaTermistor, float resistenciaResistorSerie, float voltageUc, float Beta);
float getResistencia(int pin, float voltageUc, float adcResolutionUc, float resistenciaEmSerie);
float calcularCoeficienteBetaTermistor();

void setup() {
  Serial.begin(115200);
}

void loop() {

  float resistencia = getResistencia(13, 3.3, 4095.0, 10000.0);
  float beta = calcularCoeficienteBetaTermistor();
  float temperatura = readTemperatureNTC(resistencia,
                                         10000.0,
                                         3.3,
                                         beta);
  Serial.print("Temperatura:");
  Serial.println(temperatura);
  delay(500);
}

/**
  Calcule a temperatura de um termistor através da equação de perâmetro Beta,
    informando como parâmetros o valor da resistência do Termistor (em OHM),
    o valor da resistência do resistor em série com o Termistor (em OHM),
    a tensão do Microcontrolador (em Volts), e o valor Beta do Termistor (em Kelvin).

    @param resistenciaTermistor - A resistência do Termistor.
    @param resistenciaResistorSerie - A resistência do Resistor que está
      ligado em série com o Termsitor.
    @param voltageUc - A tensão de trabalho do Microcontrolador.
    @param Beta - O valor Beta do Termistor.

    @return A temperatura em Graus Celsius.
*/
float readTemperatureNTC(float resistenciaTermistor,
                         float resistenciaResistorSerie,
                         float voltageUc,
                         float Beta) {
  // Constantes locais
  const double To = 298.15;    // Temperatura em Kelvin para 25 graus Celsius
  const double Ro = 10000.0;   // Resistência do termistor a 25 graus Celsius

  // Variáveis locais
  double Vout = 0; // Tensão lida da porta analógica do termistor.
  double Rt = 0; // Resistência lida da porta analógica.
  double T = 0; // Temperatura em Kelvin.
  double Tc = 0; // Temperatura em Graus Celsius.

  Vout = resistenciaResistorSerie /
         (resistenciaResistorSerie + resistenciaTermistor) *
         voltageUc; // Cálculo da tensão lida da porta analógica do termistor.

  Rt = resistenciaResistorSerie * Vout /
       (voltageUc - Vout); // Cálculo da resistência da porta analógica.
  T = 1 /
      (
        1 / To + log(Rt / Ro) / Beta
      ); // Aplicação da equação de parâmetro Beta para obtenção da Temperatura em Kelvin.

  Tc = T - 273.15; // Conversão de Kelvin para Celsius.
  return Tc;
}

/**
  Calcule o valor Beta de um termistor, com os valores de resistência (RT1 e RT2)
    obtidos do datasheet nas temperaturas correspondentes (T1 e T2).

  @return O valor Beta.
*/
float calcularCoeficienteBetaTermistor() {
  float beta;
  const float T1 = 273.15;  // valor de temperatura 0º C convertido em Kelvin.
  const float T2 = 373.15;  // valor de temperatura 100º C convertido em Kelvin.
  const float RT1 = 27.219; // valor da resistência (em ohm) na temperatura T1.
  const float RT2 = 0.974;  // valor da resistência (em ohm) na temperatura T2.
  beta = (log(RT1 / RT2)) / ((1 / T1) - (1 / T2));  // cálculo de beta.
  return beta;
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

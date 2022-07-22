/******************************************************************************
             Utilize o Termistor NTC junto de um ESP32 como Termômetro
               Sketch de Exemplo - Obtendo o valor Beta do Termistor

                          Criado em 06 de Maio de 2021
                                por Michel Galvão

  Eletrogate - Loja de Arduino \\ Robótica \\ Automação \\ Apostilas \\ Kits
                            https://www.eletrogate.com/
******************************************************************************/

// Protótipo das Funções
float calcularCoeficienteBetaTermistor();

void setup() {
  Serial.begin(115200);
}

void loop() {
  Serial.print("Valor Beta:");
  float beta = calcularCoeficienteBetaTermistor();
  Serial.println(beta);
  delay(500);
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

/*
Itens:
O sensor de umidade do solo com comparador LM393

O que?
Vou usar o sensor para medir o nível de água em um recipiente usando a leitura da resistência.
*/
#define NIVEL_AGUA A0 // Pino analógico conectado à saída A0 do sensor

void setup() {
  Serial.begin(9600);
}

void loop() {
  int nivel = analogRead(NIVEL_AGUA);
  
  int porcentagem = calcularNivel(nivel);

  Serial.print("Nível Água: ");
  Serial.print(porcentagem);
  Serial.println("%");

  delay(1000);
}

// Função para calcular o nível de água com base no valor lido
int calcularNivel(int value) {
  if (value >= 0 && value <= 250) {
    return 10;
  } else if (value >= 251 && value <= 350) {
    return 20;
  } else if (value >= 351 && value <= 500) {
    return 30;
  } else if (value >= 501 && value <= 650) {
    return 40;
  } else if (value >= 651 && value <= 800) {
    return 50;
  } else if (value >= 801 && value <= 850) {
    return 60;
  } else if (value >= 851 && value <= 900) {
    return 70;
  } else if (value >= 901 && value <= 950) {
    return 80;
  } else if (value >= 951 && value <= 1000) {
    return 90;
  } else {
    return 100;
  }
}

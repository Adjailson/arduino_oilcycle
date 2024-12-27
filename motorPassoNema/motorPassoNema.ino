/*
Itens:
Motor de Passo NEMA 17 1,5A 40mm para CNC
Driver Motor de Passo A4988

O que?
Vou usar um button sem resistor, com a opção de ligar o GND em um dos pinos do Button e 
outro pino na porta digital 2, pelo módulo INPUT_PULLUP.
Descrição do código: Quando o setup do Arduino iniciar quero que o motor verifique se o button 
não tá pressionado, caso não esteja mova o motor no sentido anti-horário até o Button for pressionado, 
quando o Button for pressionado zerar o status no motor para 0, espera 1 segundo e move para frente 
90º graus.
*/
#include <AccelStepper.h>

// Define os pinos do driver A4988
#define STEP_PIN 2
#define DIR_PIN 3
#define HOME_BUTTON_PIN 4 // Pino do botão (home sensor)

// Cria um objeto para o motor
AccelStepper motor(AccelStepper::DRIVER, STEP_PIN, DIR_PIN);

// Define os passos por rotação do motor (ajuste para o seu motor)
#define STEPS_PER_REVOLUTION 200 // Geralmente 200 passos por revolução (1.8° por passo)

// Função para converter ângulo em passos
int angleToSteps(float angle) {
  return (angle / 360.0) * STEPS_PER_REVOLUTION;
}

void setup() {
  Serial.begin(9600);

  // Configura o botão como entrada com pull-up interno
  pinMode(HOME_BUTTON_PIN, INPUT_PULLUP);

  // Configura velocidade e aceleração
  motor.setMaxSpeed(1000); // Velocidade máxima
  motor.setAcceleration(500); // Aceleração

  // Procedimento de homing
  Serial.println("Ajustando...");
  while (digitalRead(HOME_BUTTON_PIN) == HIGH) {
    motor.moveTo(motor.currentPosition() - 1); // Move para trás
    motor.run();
  }

  // Quando o botão for pressionado, zerar a posição do motor
  motor.setCurrentPosition(0);
  Serial.println("Ajuste finalizado. Posição no padrão desejado.");

  // Espera 1 segundo antes de continuar
  delay(1000);

  // Move 90° no sentido horário
  int steps = angleToSteps(90); // Calcula os passos necessários para 90°
  motor.moveTo(steps);
  motor.runToPosition();
  Serial.println("Movimento para 90° completo.");
}

void loop() {
  // O loop pode ser usado para outras funções ou mantido vazio
}

/*
Explicação do Código
Botão de Limite (Homing Sensor):

Configurado no pino digital 2 com INPUT_PULLUP, o botão estará HIGH quando não pressionado e LOW quando pressionado.
Homing:

Durante o setup(), o motor gira no sentido anti-horário até que o botão seja pressionado.
Quando o botão for pressionado, o motor para, e sua posição é zerada com motor.setCurrentPosition(0).
Conversão de Ângulo para Passos:

A função angleToSteps(float angle) calcula o número de passos necessários para atingir o ângulo desejado, com base nos passos por revolução do motor.
Movimento para 90°:

Após o homing, o motor espera 1 segundo e move 90° no sentido horário (sentido padrão).
Velocidade e Aceleração:

Configuradas em motor.setMaxSpeed(1000) e motor.setAcceleration(500) para movimento suave.

Testes e Considerações
Botão de Limite:

Certifique-se de que o botão está conectado corretamente:
Um terminal ao GND.
O outro terminal ao pino digital 4 do Arduino.
Passos por Revolução:

Ajuste STEPS_PER_REVOLUTION de acordo com o seu motor de passo (200 passos por revolução é o padrão para motores com 1.8° por passo).
Teste o Homing:

Verifique se o motor para corretamente ao pressionar o botão.
Movimento para 90°:

O motor deve girar exatamente 90° após o homing. Se o ângulo não for correto, revise os passos por revolução do motor.
*/

# estrelinha

Projeto com Arduino Uno + (2x) PCA9686.

Main branch é apenas para coisas que foram testadas no hardware.

- Loops sempre vão rodar o LED solitário do arduino por último.


# Replica 2

Se for conectar o LED solo, o código SEMPRE assume que está fazendo pela porta lógica 3 do UNo

Arduino Porta A5 -> PCA Pino SCL

Arduino Porta A4 -> PCA Pino SDA

Arduino Porta 5V -> PCA Pino VCC

Arduino Porta GND(1) -> PCA pino GND

PCA Pino 0 -> LED 5mm 3.3V -> Pino 0 GND (já tem resistor 200~220 OHM)

Arduino Porta 3 (pwm) -> LED 5mm -> Resistor 100ohms -> Arduino Porta GND(2)

Arduino Porta 4 -> Buzzer -> GND

Arduino Porta 7 -> Chave táctil A -> Resistor 10k -> GND (Geral)

Arduino Porta 7 -> Chave táctil B -> Resistor 10k -> GND (Geral)

Arduino 5V -> Alimentação (geral)

Alimentação (geral) -> Chave táctil A

Alimentação (geral) -> Chave táctil B

GND (geral) -> Arduino GND

PCA[0] -> Porta 0 -> LED 5mm 3.3V -> Porta 0 GND (já tem resistor)

PCA[0] -> Porta 1 -> LED 5mm 3.3V -> Porta 0 GND (já tem resistor)


# Replica 1 

Se for conectar o LED solo, o código SEMPRE assume que está fazendo pela porta lógica 3 do UNo

Arduino Porta A5 -> PCA Pino SCL

Arduino Porta A4 -> PCA Pino SDA

Arduino Porta 5V -> PCA Pino VCC

Arduino Porta GND(1) -> PCA pino GND

PCA Pino 0 -> LED 5mm -> Pino 0 GND (já tem resistor 200~220 OHM)

Arduino Porta 3 (pwm) -> LED 5mm -> Resistor 100ohms -> Arduino Porta GND(2)



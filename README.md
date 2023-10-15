# estrelinha

Projeto com Arduino Uno + (2x) PCA9686.

Main branch é apenas para coisas que foram testadas no hardware.

- Loops sempre vão rodar o LED solitário do arduino por último.


# Replica 1 

Se for conectar o LED solo, o código SEMPRE assume que está fazendo pela porta lógica 3 do UNo

Arduino Porta A5 -> PCA Pino SCL

Arduino Porta A4 -> PCA Pino SDA

Arduino Porta 5V -> PCA Pino VCC

Arduino Porta GND(1) -> PCA pino GND

PCA Pino 0 -> LED 5mm -> Pino 0 GND (já tem resistor 200~220 OHM)

Arduino Porta 3 (pwm) -> LED 5mm -> Resistor 100ohms -> Arduino Porta GND(2)



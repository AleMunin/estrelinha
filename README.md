# estrelinha

Projeto com Arduino Uno + (2x) PCA9686.

Main branch é apenas para coisas que foram testadas no hardware.

- Loops sempre vão rodar o LED solitário do arduino por último.


# Replica 4

Foi usada para testar os 2 PCA e 11 leds em cada um.


Arduino Porta A5 -> PCA Pino SCL

Arduino Porta A4 -> PCA Pino SDA

Arduino Porta 5V -> PCA Pino VCC

Todas as portas PCA[1] são conectadascom as equivalentes no PCA[0]

Arduino Porta 5V -> Breadboard positivo

Arduino Porta GND(1) -> PCA pino GND

PCA Pino 0 -> LED 5mm 3.3V -> Pino 0 GND (já tem resistor 200~220 OHM)

Arduino Porta 3 (pwm) -> LED 5mm -> Resistor 100ohms -> Arduino Porta GND(2)

Arduino Porta 4 -> resistor 100ohms -> Buzzer -> GND

Arduino Porta 5 -> Chave táctil A -> Resistor 330ohms -> GND (Geral)

Arduino Porta 6 -> Chave táctil A -> Resistor 330ohms -> GND (Geral)

Arduino Porta 7 -> Chave táctil B -> Resistor 330ohms -> GND (Geral)


------

Opcional: Leds conectados com o arduino, que se mantem ligados pro último botão apertado

Led Vermelho (tempo) -> porta 9

Led Branco ou amarelo ( Brilho) -> Porta 10

Led Verde (confirma) -> Porta 11

------
Arduino 5V -> Alimentação (geral)

Alimentação (geral) -> Chave táctil A

Alimentação (geral) -> Chave táctil B

GND (geral) -> Arduino GND

PCA[0] -> Porta 0 -> LED 5mm 3.3V -> Porta 0 GND (já tem resistor)

PCA[0] -> Porta 1 -> LED 5mm 3.3V -> Porta 0 GND (já tem resistor)

PCA[0] -> Porta 2 -> LED 5mm 3.3V -> Porta 0 GND (já tem resistor)

-- Mesma coisa para os próximos

PCA[1] -> Porta 0 -> LED 5mm 3.3V -> Porta 0 GND (já tem resistor)

PCA[1] -> Porta 1 -> LED 5mm 3.3V -> Porta 0 GND (já tem resistor)

PCA[1] -> Porta 2 -> LED 5mm 3.3V -> Porta 0 GND (já tem resistor)

-- Mesma coisa para os próximos


# Replica 3

Se for conectar o LED solo, o código SEMPRE assume que está fazendo pela porta lógica 3 do UNo

Arduino Porta A5 -> PCA Pino SCL

Arduino Porta A4 -> PCA Pino SDA

Arduino Porta 5V -> PCA Pino VCC

Arduino Porta 5V -> Breadboard positivo

Arduino Porta GND(1) -> PCA pino GND

PCA Pino 0 -> LED 5mm 3.3V -> Pino 0 GND (já tem resistor 200~220 OHM)

Arduino Porta 3 (pwm) -> LED 5mm -> Resistor 100ohms -> Arduino Porta GND(2)

Arduino Porta 4 -> Chave táctil A -> Resistor 330ohms -> GND (Geral)

Arduino Porta 7 -> Chave táctil A -> Resistor 330ohms -> GND (Geral)

Arduino Porta 8 -> Chave táctil B -> Resistor 330ohms -> GND (Geral)

Arduino Porta 12 -> resistor 100ohms -> Buzzer -> GND

Arduino 5V -> Alimentação (geral)

Alimentação (geral) -> Chave táctil A

Alimentação (geral) -> Chave táctil B

GND (geral) -> Arduino GND

PCA[0] -> Porta 0 -> LED 5mm 3.3V -> Porta 0 GND (já tem resistor)

PCA[0] -> Porta 1 -> LED 5mm 3.3V -> Porta 0 GND (já tem resistor)

PCA[0] -> Porta 2 -> LED 5mm 3.3V -> Porta 0 GND (já tem resistor)



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



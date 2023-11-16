# estrelinha

Projeto com Arduino Uno + (2x) PCA9686.

Main branch é apenas para coisas que foram testadas no hardware.

- Loops sempre vão rodar o LED solitário do arduino por último.

# Replica 5




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



# BUGS Conhecidos

Existe alguns bugs com o solo led e os botões que não fazem o menor sentido.

## Botão  tempo

O primeiro é um bug onde no modo tempo, se você apertar o botão tempo... onde não há chamado algum para ele sozinho, ele pode ligar o solo led.

Isso em si não é um problema mas antes de descobrir o que causava isso... houve o caso de que isso parou de acontecer e simplesmente há um conflito de memória, onde a rotina de setup começa a acontecer e volta direto para onde tava no loop ou reseta completamente.

Ambos os casos envolvem o serial Monitor falando aramaico do c'tchulu

```
�H�	U�= TRUE
DEBUG_LED = TRUE
DEBUG_TIME = TRUE
Os leds estão ligados
```


## Botão Brilho

De forma mais inofensiva mas de maneira bem estranha... se você apertar o botão tempo, e apenas o botão tempo, e em seguida o botão brilho... brilho_request, que não lida com catálogos, terá o solo led como ligado em catálogo, e a função que chama logo após irá ligá-lo como consequência.

Houve a circunsância onde um loop inteiro do controlador do enum de brilho acendia esse led, mas isso parou de acontecer.

Qualquer outro botão apertado fará ele desligar, exceto o botão brilho, onde ele apaga e religa o led.

Curiosamente, se o botão confirma foi apertado primeiro... o debug da brilho_request irá apontar o solo led como ligado, mas a função responsável por ligar leds ligados, irá ler seu endereço no catálogo como desligado.

Não há NENHUM código entre os dois que remotamente lide com a array de led ligado. Aparentemente é um problema com a memória do arduino ao receber um sinal.

Atualmente, esse led ligar é evitado por evitar chamar a função de religar leds no modo config, onde eles ficam desligados de um jeito ou de outro. Mas isso não muda seu catálogo como led ligado, que é resetado ao sair do modo config.


## Bugs cintilar

A maioria dos bugs encontrados na função de cintilar foram resolvidos.

Porém quando usada em modo teste ela, ela reseta a memória após a execução do seu primeiro loop, mesmo todos os leds estando no catálogo normalmente.

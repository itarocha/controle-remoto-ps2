# Projeto Controle Remoto PS2 - Arduino com RF

Este projeto é um carrinho controlado remotamente por um console de PS2 via rádio frequência. A parte eletrônica é formada por dois módulos. O transmissor e o receptor, ambos baseados em arduino nano e a transmissão é via módulo NRF24L01 em frequência de 2.4GHz.

Este projeto foi inspirado no canal do YouTube [Arduino para Modelismo](https://www.youtube.com/@ArduinoParaModelismo/featured) na [página oficial](https://arduinoparamodelismo.com/) do nosso amigo Aldeir Moreira, especialista em Automação de Miniaturas com Arduino e ESP32.

## Transmissor

Na pasta transmissor há o código responsável pela transmissão dos dados. 

#### Ligações elétricas do transmissor

| Arduino Nano | Módulo |
| ----- | ----- |
| VIN | Alimentação 7.2VCC |
| GND | NRF24LN01 GND |
| 3V3 | NRF24LN01 3V3 |
| D10 | NRF24LN01 CSN |
| D9 | NRF24LN01 CE |
| MOSI (D11) | NRF24LN01 MOSI |
| MISO (D12) | NRF24LN01 MISO |
| SCK (D13) | NRF24LN01 SCK CLK |
| D5 | PS2 DATA - Marrom |
| D3 | PS2 CMD - Laranja |
| D4 | PS2 ATT - Amarelo |
| D2 | PS2 CLK - AZUL |
| 3V3 | PS2 3V3 - VERMELHO |
| GND | PS2 GND - PRETO |

## Receptor

Na pasta receptor há o código responsável pela recepção dos dados e conversão dos dados recebidos em comandos para controle do motor DC DG01D-A130 com caixa de redução. O eixo direcional é realizado pelo micro-servo 9g.

#### Ligações elétricas do receptor

| Arduino Nano | Módulo |
| ----- | ----- |
| VIN | Alimentação 7.2VCC |
| GND | NRF24LN01 GND |
| 3V3 | NRF24LN01 3V3 |
| D10 | NRF24LN01 CSN |
| D9 | NRF24LN01 CE |
| MOSI (D11) | NRF24LN01 MOSI |
| MISO (D12) | NRF24LN01 MISO |
| SCK (D13) | NRF24LN01 SCK CLK |
| D5 | Ponte H L9110S A1A |
| D6 | Ponte H L9110S A1B |
| D3 | Servo 9g |

### Arduino Nano

<img src="/assets/images/arduino-nano-esquema.jpg">

<img src="/assets/images/arduino-nano-pinout.png">

Especificações técnicas:
- Microcontrolador: ATmega328P
- Tensão de Operação: 5V
- Tensão de Entrada: 5-12V
- Portas Digitais: 14 (6 podem ser usadas como PWM)
- Portas Analógicas: 8
- Corrente Pinos I/O: 40mA
- Memória Flash: 32KB
- SRAM: 1KB
- EEPROM: 1KB
- Velocidade do Clock: 16MHz


### Controle PS2

<img src="/assets/images/controle-ps2.png">

<img src="/assets/images/ps2-pinagem.png">

### Módulo Wireless NRF24L01 - Com Antena

O Módulo Wireless Nrf24l01 + Antena 1Km é ideal para muitas aplicações que requerem comunicações sem fio, pois este módulo possui amplificador de potência (PA) e Low Noise Amplifier (LNA). Utiliza a mesma interface do módulo Nordic nRF24L01 comum, sendo assim, você poderá substituir seu antigo módulo com potência inferior por este módulo em seu projeto e assim conseguir uma transmissão de longa distância, sem qualquer alteração. Portanto, este módulo acompanha uma antena de 2.4GHz (2db), com taxa de transmissão de 250Kbps ao ar livre, desta forma, a distância de comunicação pode chegar até 1Km.

<img src="/assets/images/nrf24l01-antena-1km.jpg">

<img src="/assets/images/nrf24l01-pinagem.jpg">

Especificações técnicas:
- Tensão: 3.3V-3.6V (recomendado 3.3V)
- Potência máxima de saída: 20 dBm
- Consumo(transmitindo): 115mA(pico)
- Consumo(recebendo): 45mA(pico)
- Consumo(power-down): 4.2uA
- Sensibilidade em modo de recepção 2Mbp: -92dBm
- Sensibilidade em modo de recepção 1Mbps: -95dBm
- Sensibilidade em modo de recepção 250kbps: -104dBm
- PA ganho: 20dB
- LNA ganho: 10dB
- LNA figura de ruído: 2.6dB
- Ganho da antena (pico): 2 dBi
- Taxa de 2MB (área aberta): 520m
- Taxa de 1MB (área aberta): 750m
- Taxa de 250kb (área aberta): 1000m
- Dimensões: 45,54 mm * 16,46 mm
- Velocidade SPI: 0 a 10Mbps
- Canais: 125
- Número de pinos: 8
- Temperatura de trabalho: -40 a 85ºC

### Ponte H Modelo L9110S
O Módulo Ponte H L9110S é um módulo Ponte H duplo, baseado no chip de controle L9110S, e  permite controlar o sentido de rotação e velocidade (necessita PWM para controle da velocidade) de dois motores de corrente continua ou um motor de passo de quatro fases.

Este módulo pode controlar motores de até 12V com consumo de 800mA por motor. Possui bornes para conexão dos motores e pinos para conexão do controle, facilitando a integração com os microcontroladores mais populares do mercado, como Arduino, PIC ou Raspberry.

<img src="/assets/images/L9110S.png">

Pinos:
- Pino VCC: Alimentação do módulo (Mesma tensão do motor até 12V)
- Pino GND: 0V
- Pino IA1: Entrada de controle do motor 1
- Pino IB1: Entrada de controle do motor 1
- Pino IA2: Entrada de controle do motor 2
- Pino IB2: Entrada de controle do motor 2
 

Dados Técnicos: 

- Chip Driver: L9110S (Datasheet L9110S)
- Tensão de alimentação: 2,5V a 12V DC
- Corrente máxima: 800mA por canal
- Tensão de operação dos terminais de controle: 2,5 a 7,7V
- Corrente dos terminais de controle: 5mA
- Temperatura de trabalho: 0ºC a +80ºC
- Dimensões: (LxCxA) 37x14x6 mm
- Peso: 20g


### Mini Ponte H L298N

<img src= "/assets/images/mini-ponte-h-l298n.jpg">

O Mini Driver Motor Ponte H L298n é um módulo construído para controlar cargas indutivas como relés, solenoides, motores DC e motores de passo. Com este driver é possível acionar até 2 motores DC ou 1 motor de passo.

Principais características:

- Dimensão reduzida
- Corrente máxima total de 2,5A (1,5 por canal)

Especificações técnicas:
- Tensão de Operação: entre 2 V e 10 V
- Chip: ST L298N (datasheet)
- Controle de 2 motores DC ou 1 motor de passo
- Corrente de Operação máxima: 1,5 A por canal ou 2,5 A max
- Tensão lógica: entre 2 V e 7 V
- Corrente em standby: menor que 0,1 uA
- Dimensões: 25 mm  x 21 mm x 7 mm
- Peso: 3 g aproximadamente

Utilização:
| IN1  | IN2  | MOTOR A |
| ---  | ---  | --- |
| LOW  | LOW  | Parado |
| HIGH | LOW  | Sentido Horário |
| LOW  | HIGH | Antiorário |
| HIGH | HIGH | Parado |

| IN3  | IN4  | MOTOR B |
| ---  | ---  | --- |
| LOW  | LOW  | Parado |
| HIGH | LOW  | Sentido Horário |
| LOW  | HIGH | Antiorário |
| HIGH | HIGH | Parado |

### Motor DG01D-A130

<img src="/assets/images/motor-dc-3a6v.png">

Especificações técnicas:
- Variação de tensão: 3 ~ 6V
- Tensão de alimentação recomendada: 4,5V
- Corrente em aberto: 190mA
- Corrente com máxima carga: 250mA
- Corrente de Stall: 1.2A @ 6V (0.6A @ 3V)
- Relação da caixa de redução: 48:1
- Velocidade: 140RPM @ 4,5V sem carga
- Torque: 800 gf cm

### Micro Servo 9g

<img src="/assets/images/micro-servo-9g.png">

Especificações técnicas:
- Voltagem de Operação: 3,0 – 7,2v
- Velocidade: 0,12 seg/60Graus (4,8v) sem carga
- Torque: 1,2 kg.cm (4,8v) e 1,6 kg.cm (6,0v)
- Temperatura de Operação: -30C ~ +60C
- Dimensões: 32x30x12 mm
- Tipo de Engrenagem: Nylon
- Tamanho cabo: 245 mm
- Peso: 9g

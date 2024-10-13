# Projeto Controle Remoto PS2 - Arduino com RF

Este projeto é um carrinho controlado remotamente por um console de PS2 via rádio frequência. A parte eletrônica é formada por dois módulos. O transmissor e o receptor, ambos baseados em arduino nano e a transmissão é via módulo NRF24L01 em frequência de 2.4GHz.

## Transmissor

Na pasta transmissor há o código responsável pela transmissão dos dados. 

## Receptor

Na pasta receptor há o código responsável pela recepção dos dados e conversão dos dados recebidos em comandos para controle do motor DC DG01D-A130 com caixa de redução. O eixo direcional é realizado pelo micro-servo 9g.


### Arduino Nano

<img src="/assets/images/arduino-nano-esquema.jpg">

<img src="/assets/images/arduino-nano-pinout.png">

| Item | Valor |
| -----| ----- |
| Microcontrolador | ATmega328P |
| Tensão de Operação | 5V |
| Tensão de Entrada | 5-12V |
| Portas Digitais | 14 (6 podem ser usadas como PWM) |
| Portas Analógicas | 8 |
| Corrente Pinos I/O | 40mA |
| Memória Flash | 32KB |
| SRAM | 1KB |
| EEPROM | 1KB |
| Velocidade do Clock | 16MHz |


### Módulo Wireless NRF24L01 - Com Antena

O Módulo Wireless Nrf24l01 + Antena 1Km é ideal para muitas aplicações que requerem comunicações sem fio, pois este módulo possui amplificador de potência (PA) e Low Noise Amplifier (LNA). Utiliza a mesma interface do módulo Nordic nRF24L01 comum, sendo assim, você poderá substituir seu antigo módulo com potência inferior por este módulo em seu projeto e assim conseguir uma transmissão de longa distância, sem qualquer alteração. Portanto, este módulo acompanha uma antena de 2.4GHz (2db), com taxa de transmissão de 250Kbps ao ar livre, desta forma, a distância de comunicação pode chegar até 1Km.

<img src="/assets/images/nrf24l01-antena-1km.jpg">

| Item  | Valor |
| ----- | ----- |
| Tensão | 3.3V-3.6V (recomendado 3.3V) |
| Potência máxima de saída | 20 dBm |
| Consumo(transmitindo) | 115mA(pico) |
| Consumo(recebendo) | 45mA(pico) |
| Consumo(power-down) | 4.2uA |
| Sensibilidade em modo de recepção 2Mbp | -92dBm |
| Sensibilidade em modo de recepção 1Mbps | -95dBm |
| Sensibilidade em modo de recepção 250kbps | -104dBm |
| PA ganho | 20dB |
| LNA ganho | 10dB |
| LNA figura de ruído | 2.6dB |
| Ganho da antena (pico) | 2 dBi |
| Taxa de 2MB (área aberta) | 520m |
| Taxa de 1MB (área aberta) | 750m |
| Taxa de 250kb (área aberta) | 1000m |
| Dimensões | 45,54 mm * 16,46 mm |
| Velocidade SPI | 0 a 10Mbps |
| Canais | 125 |
| Número de pinos | 8 |
| Temperatura de trabalho | -40 a 85ºC |

### Motor DG01D-A130

<img src="/assets/images/motor-dc-3a6v.png">

| Item | Valor |
| -----| ----- |
| Variação de tensão | 3 ~ 6V |
| Tensão de alimentação recomendada | 4,5V |
| Corrente em aberto | 190mA |
| Corrente com máxima carga | 250mA |
| Corrente de Stall | 1.2A @ 6V (0.6A @ 3V) |
| Relação da caixa de redução | 48:1 |
| Velocidade | 140RPM @ 4,5V sem carga |
| Torque | 800 gf cm |

### Micro Servo 9g

<img src="/assets/images/micro-servo-9g.png">

| Item | Valor |
| -----| ----- |
| Voltagem de Operação | 3,0 – 7,2v |
| Velocidade | 0,12 seg/60Graus (4,8v) sem carga |
Torque | 1,2 kg.cm (4,8v) e 1,6 kg.cm (6,0v) |
| Temperatura de Operação | -30C ~ +60C |
| Dimensões | 32x30x12 mm | 
| Tipo de Engrenagem | Nylon |
| Tamanho cabo | 245 mm |
| Peso | 9g | 

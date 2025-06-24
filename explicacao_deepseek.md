#Explicação:

1. Conexões:

Motores:

IN1, IN2: Motor esquerdo

IN3, IN4: Motor direito

ENA, ENB: Controle PWM de velocidade

NRF24L01:

CE → D7

CSN → D8

SCK → D13

MOSI → D11

MISO → D12

VCC → 3.3V

GND → GND

2. Comunicação:

Utiliza a biblioteca RF24 para comunicação

Endereço único 0xE8E8F0F0E1

Estrutura de dados com:

direcao (frente, trás, esquerda, direita)

velocidade (0-255)

freio (ativo/inativo)

3. Funções de Controle:

frente(): Ambos motores para frente

tras(): Ambos motores para trás

esquerda(): Motor direito para frente, esquerdo para trás

direita(): Motor esquerdo para frente, direito para trás

parar(): Desativa todos os motores

freio(): Frenagem brusca (curto-circuito nos motores)

4. Segurança:

Para o carrinho se perder comunicação

Frenagem ativada por comando específico

##Instruções:

1. Transmissor:

Você precisará de outro Arduino (ex: Uno) com NRF24L01

Utilize joystick/botões para enviar comandos correspondentes

2. Alimentação:

Use bateria separada para os motores (recomendado 6V-12V)

Arduino Nano pode ser alimentado via USB ou bateria

2. Bibliotecas:

Instale as bibliotecas:

RF24 (https://github.com/nRF24/RF24)

SPI (já incluída no IDE Arduino)

Este código oferece controle completo com funções suaves de aceleração e frenagem. Para ajustar a sensibilidade, modifique os valores de PWM (dados.velocidade) diretamente no transmissor.

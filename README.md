# EmbarcadosAPS1
Placas + Codigo = Musica

link para o video: https://www.youtube.com/watch?v=mO--RNVXvkA

Passos para configurar o projeto


1 - Coloque a placa "OLED1 X PLANED pro" no suporte para periférico "EXT1".

2 - Conecte um pino do buzzer no Pio D30 e o outro no GND

3 - Com o cabo conectado no pc rode o arquivo "main.c" que está na pasta BaseOLED/OLED-Xplained-Pro-SPI/src


O projeto se consiste em um tocador de músicas que também pisca o led 2 do OLED1 de acordo com a música e mostra o nome da música sendo tocada no display do OLED1.

As músicas foram colocadas em structs com seus nomes notas, tamanhos das músicas e tempo das notas.

Foi criada uma função chamada "tone" que reproduz uma nota durante a quantidade de tempo indicada.

Foram utilizadas flags para indicar quando um botão era pressionado e era necessário lançar uma interrupção.


O botão 1 do OLED foi utilizado para ir para traz na lista de reprodução de músicas.

O botão 2 do OLED foi utilizado para pausar e dar plays nas músicas.

O botão 3 do OLED foi utilizado para ir para frente na lista de reprodução de músicas.

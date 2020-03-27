# EmbarcadosAPS1
Placas + Codigo = Musica

Passos para configurar o projeto

1 - Coloque a placa "OLED1 X PLANED pro" no suporte para periférico "EXT1".
2 - Conecte um pino do buzzer no Pio D30 e o outro no GND
3 - Com o cabo conectado no pc rode o arquivo "main.c" que está na pasta BaseOLED/OLED-Xplained-Pro-SPI/src

O projeto se consiste em um tocador de músicas que também pisca um led de acordo com a música e mostra o nome da música sendo tocada no display.

As músicas foram colocadas em structs com seus nomes notas, tamanhos das músicas e tempo das notas.

# TCB_AN_PWM
Programa que muda a pulsação de um PWM usando o TCB conforme um botão é pressionado no AVR128DA48.

Foi utilizada a saída PB5 da placa de desenvolvimento do AVR128DA48 como saída para o PWM gerado no timer B (TCB).
Foi feita uma função que reconhece se o botão da placa foi acionado e, a cada vez que isso acontece, o valor de duty cicle do pwm vai para 25, 50 ou 75.
O Led da placa acende e apaga em cada momento que o botão é acionado, isso foi feito para melhor entendimento do funcionamento do projeto.
Na prática, há um delay que deve acontecer provavelmente por causa da baixa frequência de clock utilizada.
O projeto foi inspirado em um application note da microchip.

Link para o avr128da48: https://www.microchip.com/en-us/product/AVR128DA48

Link para o application note: https://www.microchip.com/content/dam/mchp/documents/MCU08/ApplicationNotes/ApplicationNotes/TB3214-Getting-Started-with-TCB-DS90003214.pdf

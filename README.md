# uCstartup
Desenvolvimento da programação dos microcontroladores

A ferramenta de compilação é o avr-gcc, e  o AVRDUDE para gravação.
O arquivo Makefile apresenta as etapas de compilação e linkedição.

O seguinte tutorial ensina como utilizar o avr-gcc e o avr-dude com o arduino: https://www.instructables.com/id/AVR-Programming-with-Arduino-AVRdude-and-AVR-gcc/


ESP-8266

O ESP RTOS-SDK atua como o kit de desenvolvimento de software.
Para o projeto foram projetadas as seguintes características:
- 2 Interrupções, uma para a porta serial UART e outra para pacotes recebidos pela aplicação MQTT.
- 2 processos que são responsáveis por montar os pacotes de transmissão e enviá-los.

O diagrama 1 representa a topologia de comunicação entre os dispositivos da rede.

![diagrama de conexões][./Topologia\ de\ conexões.png]

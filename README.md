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

![diagrama de conexões](https://github.com/andrehrema/uCstartup/blob/master/Topologia%20de%20conex%C3%B5es.png)

Cada recepção (UART e MQTT) será interpretada como interrupções, que se comunicarão com os processos através de queues.
Durante as interrupções havéra verificação de se um final de mensagem foi enviado, caso sim, a mensagem é montada e enviada para a fila de envio, que por sua vez acorda as tarefas bloqueadas.

Cada envio de informação (UART e MQTT) é interpretado como uma tarefa bloqueada, que será ativa no momento de enviar uma mensagem. 


A seguinte página explica o processo de montagem de um projeto usando o ESP_RTOS_SDK:
https://docs.espressif.com/projects/esp8266-rtos-sdk/en/latest/api-guides/build-system.html

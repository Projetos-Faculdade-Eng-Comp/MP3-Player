# MP3 Player
Projeto final da disciplina de Microprocessados da turma de Engenharia de Computação 2022.2
# Integrantes
Moisés Conrado Marinho Eufrásio Filho

Rafael Gurgel Soares

Thaís Bezerra de Menezes Benício de Sousa

Víctor Chagas de Lima

# Descrição
O projeto consiste de um MP3 Player com base no controle do módulo DFPlayer Mini pelo microcontrolador STM32F070F6P6.
O módulo DFPlayer Mini possui diversas funções para reprodução de músicas de várias fontes. Neste projeto, utilizamos como fonte um cartão microSD. A comunicação do módulo com o MCU se dá através da UART, a fim de controlar, por exemplo, o volume da música, a função de play/pause e next. O som é reproduzido por meio de um fone de ouvido.

A interação com o usuário é feita por meio de push buttons configurados em pull down, que estão conectados por meio de GPIO ao microcontrolador. Cada botão executa uma função, a saber: diminuir volume, aumentar volume, passar para a próxima música e play/pause. Além disso, um display OLED informa ao usuário as informações relevantes, como o volume atual, se está pausado ou reproduzindo e se foi atingido o volume máximo.

# MP3 Player
Projeto final da disciplina de Sistemas Microprocessados, Universidade Federal do Ceará, turma de Engenharia de Computação 2022.2

# Integrantes
* Moisés Conrado Marinho Eufrásio Filho - 516223
* Rafael Gurgel Soares - 509023
* Thaís Bezerra de Menezes Benício de Sousa - 509803
* Víctor Chagas de Lima - 510486

# Componentes
* Greenpill STM32F070F6P6
* DFPlayer Mini
* Push buttons
* Display OLED
* Fone de ouvido

# Descrição
![photo_4947628104394844875_y](https://user-images.githubusercontent.com/110418856/207138031-0827b27d-19b4-482d-9ff1-0d850947c7c6.jpg)

![photo1670885955](https://user-images.githubusercontent.com/111692964/207183933-7dc53c64-364c-4510-af2e-a47af612028f.jpeg)

O projeto consiste de um MP3 Player com base no controle do módulo DFPlayer Mini pelo microcontrolador STM32F070F6P6.
O módulo DFPlayer Mini possui diversas funções para reprodução de músicas de várias fontes. Neste projeto, utilizamos como fonte um cartão microSD. A comunicação do módulo com o MCU se dá através da UART, a fim de controlar, por exemplo, o volume da música, a função de play/pause e next. O som é reproduzido por meio de um fone de ouvido.

(Obs.: para o DFPlayer Mini funcionar corretamente, é muito importante que ele seja alimentado com tensão suficiente. Se a tensão de 3.3V do STLink não for suficiente, a saída de 5.0V pode ser usada para alimentar apenas o DFPlayer Mini. A Greenpill não pode ser conectada aos 5V.)

A interação com o usuário é feita por meio de push buttons configurados em pull down, que estão conectados por meio de GPIO ao microcontrolador. Cada botão executa uma função, a saber: diminuir volume, aumentar volume, passar para a próxima música e play/pause. Além disso, um display OLED informa ao usuário as informações relevantes, como o volume atual, se está pausado ou reproduzindo e se foi atingido o volume máximo.

![20221212_092533](https://user-images.githubusercontent.com/110418856/207137539-2133a9a0-acf7-4960-9fe5-9655ff0a31e9.jpg)

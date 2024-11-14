# Campo Minado em C

Este projeto implementa o jogo Campo Minado utilizando a linguagem C e emprega conceitos de alocação dinâmica de memória. O objetivo é demonstrar habilidades em manipulação de ponteiros e arrays bidimensionais.

## Funcionalidades

- Interface de texto simples para o usuário
- Geração de campo com minas de forma aleatória
- Manipulação eficiente de alocação dinâmica para representar o campo
- Opções de revelação de células e marcação de minas

## Como jogar

1. Ao iniciar, você escolhe o tamanho do campo e o número de minas.
2. Utilize as coordenadas para revelar células ou marcar minas.
3. O jogo termina quando todas as células seguras forem reveladas ou se uma mina for acionada.

## Compilação e Execução

Para compilar o projeto, utilize:

gcc cm_emanuelle_tp2.c log.c matriz.c -o cm_emanuelle_tp2
./cm_emanuelle_tp2

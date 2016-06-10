# Classroom-Presence

## PROBLEMÁTICA
***
Existem pontos negativos em realizar a chamada dos alunos em sala de aula. Uma forma de fazer a chamada é falando o nome do aluno e o mesmo responde que está presente, nesse caso o professor dedica um certo tempo de sua aula para essa tarefa que poderia ser usado para concluir o conteúdo da aula no final. Outra forma é através de assinaturas, por parte dos alunos, em uma lista de presença, o que pode gerar dois problemas, desconcentração do aluno ao ter que parar de assistir a aula para assinar uma lista e falsificação de assinatura por parte de algum colega de turma.

Esses são alguns problemas que podem ser causados por sistemas manuais de captura de frequência de alunos. Para isso foi desenvolvido um protótipo de sistema capaz de capturar a presença do aluno em sala de aula usando tags RFID (carteiras de estudante) e armazenando em arquivos através de um software no computador do professor.

## SISTTEMA
***
O sistema consiste em dois módulos, o dispositivo de leitura e o software de controle. Onde o software de controle fica localizado em um computador, o dispositivo de leitura é a Raspberry Pi com um RFID Reader e a comunicação entre os dois é feita via socket.

### Dispositivo de leitura
***
A Raspberry Pi roda um código em Python que, através da biblioteca MFRC522 é capaz de ler, usando SPI, os cartões passados pelo RFID Reader e enviar os ids para o Software de controle como cliente TCP.

### Software de controle
***
O computador roda um código em C++ com uma interface gráfica amigável capaz de ajudar o usuário a criar turmas, cadastrar alunos, salvar frequência e iniciar o servidor TCP (Thread) para receber os ids lidos pelo Dispositivo de leitura.

## RESULTADOS
***

Como o sistema ainda é um protótipo existem algumas funcionalidades que podem não ficar claras para o usuário, como informar que o aluno foi cadastrado com sucesso.

O sistema não garante 100% que o aluno realmente está em sala, pois o mesmo pode passar a tag no Dispositivo de leitura e sair de sala. Porém com o auxílio de outros dispositivos como câmeras para captura e processamento de rostos, podem ajudar na melhoria do sistema.

Atualmente, o sistema consegue ler tags, criar turmas, cadastrar alunos, gerenciar a frequência na lista e salvar arquivos de frequência por datas de aula. A Figura 1 representa um screenshot da tela principal do aplicativo e a Figura 2 um screenshot da tela de cadastro do aplicativo.

![Time](Tela_pincipal.png?raw=true "Tela pincipal.")


![Time](Tela_de_cadastro.png?raw=true "Tela de cadastro.")

## REFERÊNCIAS
***

•	https://github.com/mxgxw/MFRC522-python
•	http://wiki.python.org.br/SocketBasico
•	http://doc.qt.io/qt-4.8/qtgui-module.html
•	Trabalhos feitos durante o decorrer da disciplina.


## Desenvolvedores
***

Jackson Rauup e Raul Silveira.


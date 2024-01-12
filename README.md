# RBC (Recuperação Baseada em Casos)

Este é um projeto simples de Recuperação Baseada em Casos (RBC) implementado em C. Ele usa um conjunto de dados do arquivo `iris.data` para realizar classificação de instâncias com base na distância euclidiana.

Usado para classificar novas instâncias, o algoritmo funciona com qualquer entrada que tenha como requisito 4 atributos e 1 classe.

## Conteúdo do Repositório

- `rbc.cpp`: O código-fonte em C contendo a implementação do RBC.
- `iris.data`: O conjunto de dados Iris utilizado pelo programa.
- `executa.sh`: Um script Bash para compilar, executar o programa e gerar um relatório.
- `relatorio.txt`: O relatório gerado pelo programa.

### FUNCIONAMENTO DO ALGORITMO 

O arquivo de entrada iris.data possui, por instância, 3 atributos e a classe do objeto, respectivamente.
Na sua totalidade, o arquivo iris.data possui 150 instâncias que serão analisadas.


Das 150 instâncias, 5 são selecionadas aleatoriamente para amostras.


A partir da distância euclidiana, é possível identificar quais instâncias são parecidas com outras.
O algoritmo possui tratamento de ruído. O objetivo é excluir instâncias muito parecidas da avaliação.

Novas instâncias são classificadas e inseridas em suas classes equivalentes.

### COMO COMPILAR E EXECUTAR

Basta executar o arquivo "executa.sh"

### REQUISITOS
 - Certifique-se de ter o GCC (GNU Compiler Collection) instalado em seu sistema antes de executar o script.
 - math.h

```bash
./executa.sh


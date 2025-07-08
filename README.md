# Trabalho de Estrutura de Dados

![alt text](misc/image.png)

**Membros: Heitor Lima Peixoto e Gian Lucca Decoté Paneto Neves**

# Como rodar o projeto
#### 1. Clonar o repositório
Para rodar o projeto em um ambiente Linux, faça o clone do repositório com: 

```git clone https://github.com/Hei-Lima/trabalhoed.git```

#### 2. Rodar o projeto
O arquivo 'Makefile' na raiz do projeto tem diversas keywords que trivializam a execução do programa. Mas, para isso, você vai ter que instalar o Make.

Para simplesmente executar o programa, na raiz do projeto execute o comando:

```make run```

Para apagar os arquivos gerados na hora da compilação, execute o comando:

```make clean```

Para testar o programa para erros de memória com o [Valgrind](https://pt.wikipedia.org/wiki/Valgrind), execute:

```make valgrind```

#### 3. Mudar o CSV carregado.
Você pode gerar pacientes e CSVs aleatórios com o programa em Python (feito por IA, não nos cobre se tiver errado) em `/misc`.

Para trocar o CSV que o programa irá carregar, altere o #define CSV_PATH no arquivo `main.c`. 

# Arquitetura geral

Tentamos deixar o máximo abstrato possível. O DB não tem acesso ao TrieNode e a main não tem acesso a Pacientes nem a nada relativo às implementações do banco de dados. Todas as funcionalidades de módulos importados são invocadas por chamadas de função, nunca por modificação dos objetos em si. Tudo fica bem simples e transparente. A ideia foi fazer na main uma arquitetura modular que imite uma página HTML, onde cada função seria uma página diferente, e as funcionalidades da página são implementadas por funções externas, como o módulo UI Lib.

# Funcionalidades do Programa

#### 1. Consulta
Permite consulta por nome e CPF.

#### 2. Inserção
Adiciona novo paciente com ID automático e único.

#### 3. Atualização
  Permite editar qualquer campo do paciente. Use '-' para manter o valor atual.

#### 4. Remoção
  Remove paciente pelo ID, com confirmação.

#### 5. Listagem
  Mostra pacientes paginados (10 por página).

# Como o programa funciona?

A primeira coisa que o programa faz é carregar os dados de um CSV para o Banco de Dados, que é implementado em um módulo db.c.

O banco de dados tem a seguinte estrutura:

LISTA DUPLAMENTE ENCADEADA DOS PACIENTES

Esse banco é implementado com uma estrutura chamada BD_Paciente, que armazena os ponteiros para uma lista com os pacientes.

# Lista paciente

A lista paciente é uma lista encadeada. Ele armazena estruturas paciente (definidas em paciente.c).

![alt text](misc/paciente.svg)

Nada de muito interessante aqui. Essas informações são retiradas do CSV, parseadas com scanf() (ISSO foi difícil...) e colocadas no array e nas tries. O problema da linguagem C é ter que alocar memória, então o tamanho máximo dos nomes é o número de caracteres no nome de [Pedro II](https://pt.wikipedia.org/wiki/Pedro_II_do_Brasil). 

O banco de dados trabalha com a lógica de fazer as consultas e relacionar os pacientes da lista e dos pacientes.

# Módulo UI Lib

Esse módulo implementa tudo relativo à formatação de prints e inputs dos usuários. Nele, implementamos a função ui_cls() que limpa a tela e ui_get_char(), que pega um caractere apenas em tempo real, usando modo [não canônico do terminal](https://stackoverflow.com/questions/13104460/confusion-about-raw-vs-cooked-terminal-modes) (raw).

# Testes

Os testes são feitos rodando o Valgrind, para checar por erros de memória. Isso garante que todos os frees foram executados corretamente e não sobraram ponteiros se balançando por aí.

# PS:
### Perdão pelos comandos estranhos na hora de escrever a consulta, não conseguimos algo mais esperto.

### Tente pesquisar o seu nome... Ele está lá! Os nossos também.

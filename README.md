# Trabalho Prático 3 - Indexação de Arquivos em Disco

Este projeto foi desenvolvido como parte da disciplina **Algoritmos e Estruturas de Dados 2 (AED2)** do **Instituto de Computação (ICOMP)** da **Universidade Federal do Amazonas (UFAM)**.

O objetivo do trabalho consiste em projetar e implementar estruturas de dados em memória secundária (disco) utilizando conceitos de Tipos Abstratos de Dados (TADs), aplicando diferentes abordagens de indexação (Árvore Binária de Pesquisa e Tabela Hash) e comparando-as estatisticamente com abordagens puramente sequenciais.

## 📋 Especificações do Trabalho

O sistema gerencia um arquivo binário de dados cujos registros representam o cadastro de alunos da instituição. São implementadas e avaliadas **5 estratégias de busca**, divididas pelo tipo de atributo consultado:

### Busca por Atributo Chave (Matrícula)
1. **Estratégia 1:** Busca indexada utilizando uma Árvore Binária de Pesquisa (BST) em memória para localizar o número do registro e acesso direto via `fseek`.
2. **Estratégia 2:** Busca indexada utilizando uma Tabela Hash com tratamento de colisões por encadeamento exterior.
3. **Estratégia 3:** Busca Sequencial exaustiva realizada diretamente varrendo o arquivo em disco.

### Busca por Atributo Não-Chave por Intervalo (Coeficiente de Rendimento - CR)
4. **Estratégia 4:** Busca por intervalo de valores (`>= min` e `<= max`) utilizando uma árvore de indexação baseada em ponto flutuante.
5. **Estratégia 5:** Busca por intervalo mapeada através de leitura sequencial completa do arquivo em disco.

---

## 🗄️ Estrutura do Registro (Dicionário de Dados)

Cada registro armazenado em disco possui tamanho fixo de **132 bytes**, garantindo uma simulação realista de carga de E/S de dados em disco.

| Campo | Tipo | Tamanho | Descrição |
| :--- | :--- | :--- | :--- |
| `matricula` | `int` | 4 bytes | Chave Primária Única (Inicia em 1000) |
| `idade` | `int` | 4 bytes | Atributo informativo (18 a 57 anos) |
| `cr` | `float` | 4 bytes | Atributo Não-Chave usado para buscas intervalares |
| `nome` | `char[50]` | 50 bytes | Nome completo do discente |
| `curso` | `char[30]` | 30 bytes | Curso de graduação |
| `email` | `char[40]` | 40 bytes | Email institucional (`alunoXXXX@ufam.edu.br`) |

---

## 🛠️ Como Compilar e Executar

Certifique-se de ter o compilador `gcc` instalado em seu ambiente Unix/Linux ou terminal macOS.

1. Navegue até a pasta raiz do projeto.
2. Compile todos os módulos do TAD unificados com o seguinte comando:
   ```bash
   gcc main.c Registro.c IndiceArvBST.c IndiceHash.c BuscaSeq.c metricas.c -o prog
   ./prog
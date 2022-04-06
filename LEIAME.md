# Estrutura

- Na main temos o tratamento da leitura de dados e chamada de cada método de resolução de sistema linear.

- MathLib é uma biblioteca relacionada as implementações de libmathEval.
	- Temos uma estrutura de dados chamada _variables_ que é usada para guardar variáveis e a quantidade de variáveis.
	- Também temos uma estrutura chamada _function_ utilizada para guardar a função em string e a função criada pelo libmathEval, bem como derivadas, variáveis, tempo de cálculo de derivada e matriz hessiana.
-  Methods é uma biblioteca de métodos de manipulação dos sistemas lineares em geral.
	- Temos uma estrutura de dados do sistema resultante da fatoração LU, ela possui a matriz de valores L, U, o vetor y, o vetor de trocas e a dimensão das matrizes e vetores.
- Newton é uma biblioteca relacionada às implementações dos métodos de newton.
	- Temos uma estrutura _output_ que contém dados relevantes para a saída do programa, isto é, os resultados de cada método, a quantidade de iterações de cada método e os tempos totais e de solução de sistema em cada método.
	- Temos uma estrutura _sl_ que visa guardar os dados relevantes de um sistema linear, são eles: a estrutura _function_ daquele sistema, a matriz Hessiana de valores, o vetor gradiente, o vetor gradiente negado (multiplicado por -1), os valores iniciais do vetor X -- utilizamos para resetar o sistema após um método, tirando necessidade de cópia de sistema --, o vetor X propriamente dito, um vetor deltai usado no método de Newton, uma estrutura _output_ daquele sistema linear, o grau do sistema linear, o erro tolerável e o número máximo de iterações.
- Em utils, por fim, temos funções úteis no geral para lidar com alocação dinâmica, tratamento de dados etc.
# Fluxo de dados
O código recebe um bloco de dados de 5 linhas, como especificado no trabalho, cada linha é tratada de uma forma diferente de acordo com a função `handleSLInit()`. Em seguida, chamamos o método de Newton Padrão pela função `newtonDefault()`, essa função executa o calculo da Hessiana, do Gradiente, do Gradiente negado, resolve o sistema linear através do método de eliminação de Gauss com pivoteamento parcial dentro do método de Newton e depois realiza a retrossubstituição no sistema; o resultado, então, é uma estrutura de sistema linear com os valores exatos da resolução (claro, com possíveis erros numéricos de arredondamento). 

Em seguida, o sistema linear é resetado pela função `resetSL()` e o próximo método é chamado seguindo a mesma lógica da implementação do método de Newton, porém com a solução do sistema diferente, nesse caso, o segundo método é o que resolve o sistema via fatoração LU, que é executada na matriz Hessiana -- essa é calculada somente uma vez a cada <número de variáveis do sistema> vezes, ou seja, não calculamos sempre a Hessiana como nos demais métodos.

Novamente, o sistema é resetado e chamamos, finalmente, o último método que funciona com a mesma ideia do Newton, mas agora utilizando Gauss-Seidel para resolver o sistema, o que nos dá um método de Newton Inexato. 

Todos os resultados são guardados na estrutura _output_ do sistema linear e devidamente imprimidos na tela pela função `printOutput()`.

# Considerações

O método de newton exato, ou método padrão, encontra a resposta exata, enquanto os demais métodos encontram aproximações do valor exato, o que pode resultar, em alguns casos, na falta de convergência do valor. Notoriamente as 5 últimas entradas fornecidas pelos professores não convergem utilizando os métodos de newton modificado e inexato, assim como as próprias saídas forcenidas pelos professores também não convergem. Vale a pena ressaltar também que praticamente todo output do nosso trabalho, em questão de valor, bateu ou se aproximou muito dos valores de output fornecidos pelos professores (o que indica a corretude dos nossos algorítmos), estando a maior diferença presente nos valores em que a convergência dos métodos não foi possível.

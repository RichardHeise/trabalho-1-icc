# Requisitos
  - libmatheval
  - likwid
  - python3
  - numpy
  - matplotlib
  - pandas

# Execução
  - Para executar ambas as baterias de funções e formar os gráficos, basta ``` bash run.sh ```
  - Para formar os gráficos apenas, basta rodar ``` python3 ./scripts/graphs/makeGraphs.py ```

# Compilação
  - A compilação é realizada via Makefile e cada um dos algoritmos possuem um makefile próprio com os macros necessários
  para realizar as ações requisitadas pelo run.sh

# Conclusões e problema encontrados
  - O detalhamento da realização do trabalho, assim como as conclusões, análises e problemas encontrados, estão no arquivo 
  RELATORIO-gl19-rfhf19.pdf

# Arquivos interessantes
  - Na home do trabalho temos a topologia do computador utilizado 
  - Em scripts/graphs temos as tabelas utilizadas para formar os gráficos e os gráficos utilizados no relatório
  - A pasta part1 é o trabalho passado, a rosenbrock é o passado modificado para utilizar rosenbrock e rosenbrock-opt contém as 
  otimizações que a equipe realizou
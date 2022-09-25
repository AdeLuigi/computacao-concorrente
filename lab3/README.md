## Resultados:

### Matriz 500x500
| | 1 thread | 2 threads | 4 threads
|---|---|---|---|
| **Tempo de leitura dos arquivos binários**        | 0.000610s | 0.001371s | 0.000976s |
| **Tempo de alocação de memória**        | 0.000934s | 0.001560s | 0.001287s |
| **Multiplicação** | 0.424338s | 0.220138s | 0.133443s |
| **Tempo de criação do arquivo de saída**         | 0.003367s | 0.002060s | 0.002016s |

Tempo total da parte que não envolve cpu bound com 4 threads: 0.004279s
Tempo de cpu bound com 4 threads: 0.133443s
Tempo total do algoritmo concorrente: 0.137722s
Tempo total do algoritmo sequencial do lab2: 0.460912s

Tempo sequencial do lab2/concorrente = (0.460912)/(0.137722) = 3.3466838994496158

### Matriz 1000x1000
| | 1 thread | 2 threads | 4 threads |
|---|---|---|---|
| **Tempo de leitura dos arquivos binários**        | 0.001453s | 0.000681s | 0.001460s |
| **Tempo de alocação de memória**        | 0.005321s | 0.004733s | 0.004572s |
| **Multiplicação** | 4.232253s | 2.023897 | 1.135847s |
| **Tempo de criação do arquivo de saída**         | 0.006245s | 0.006010s | 0.005683s |

Tempo total da parte que não envolve cpu bound com 4 threads: 0.011715s
Tempo de cpu bound com 4 threads: 1.135847s
Tempo total do algoritmo: 1.147562s

Tempo sequencial do lab2/concorrente = (4.590434)/(1.147562) = 4.000162082745856

### Matriz 2000x2000
| | 1 thread | 2 threads | 4 threads |
|---|---|---|---|
| **Tempo de leitura dos arquivos binários**        | 0.001030s | 0.001623s | 0.001344s |
| **Tempo de alocação de memória**        | 0.016648s | 0.018650s | 0.017062s |
| **Multiplicação** | 38.590147s | 17.790251s | 10.071468s |
| **Tempo de criação do arquivo de saída**         | 0.020986s | 0.023670s | 0.023471s |

Tempo total da parte que não envolve cpu bound com 4 threads: 0.041877s
Tempo de cpu bound com 4 threads: 10.071468s
Tempo total do algoritmo: 10.11334499999999

Tempo sequencial do lab2/concorrente = (40.928478)/(10.11334499999999) = 4.046977335392003

## Corretude
A corretude foi verificada utilizando o site https://matrix.reshish.com/multCalculation.php


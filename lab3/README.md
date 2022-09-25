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
| | 1 thread | 2 threads | 4 threads | Média |
|---|---|---|---|---|
| **Tempo de leitura dos arquivos binários**        | 0.001453s | 0.000681s | 0.001460s |
| **Tempo de alocação de memória**        | 0.005321s | 0.004733s | 0.004572s |
| **Multiplicação** | 4.232253s | 2.023897 | 1.135847s |
| **Tempo de criação do arquivo de saída**         | 0.006245s | 0.006010s | 0.005683s |

Tempo total da parte que não envolve cpu bound: 0.011715s
Tempo de cpu bound: 1.135847s
Tempo total do algoritmo: 1.147562s

Tempo sequencial do lab2/concorrente = (4.590434)/(1.147562) = 4.000162082745856

### Matriz 2000x2000
| | 1 thread | 2 threads | 4 threads | Média |
|---|---|---|---|---|
| **Tempo de leitura dos arquivos binários**        | 0.000505s | 0.001601s | 0.000622s | 0.000909s |
| **Tempo de alocação de memória**        | 0.004547s | 0.016270s | 0.017971s | 0.012929s |
| **Multiplicação** | 40.899598s | 41.814996s | 42.799465s | 41.838019s |
| **Tempo de criação do arquivo de saída**         | 0.024645s | 0.023829s | 0.025562s | 0.024678s |

Tempo total da parte que não envolve cpu bound: 0.028881s
Tempo de cpu bound: 40.899598s
Tempo total do algoritmo: 40.928478s

Tempo concorrente = (0.028881 + 40.89959)/(0.028881+(40.89959/T))
Aceleração concorrente em um cenário perfeito = 39.77959647422783

## Corretude
A corretude foi verificada utilizando o site https://matrix.reshish.com/multCalculation.php


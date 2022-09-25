## Resultados:

### Matriz 500x500
| | Teste 1 | Teste 2 | Teste 3 | Média |
|---|---|---|---|---|
| **Tempo de leitura dos arquivos binários**        | 0.000767s | 0.000925s | 0.001317s | 0.001003s |
| **Tempo de alocação de memória**        | 0.001230s | 0.001403s | 0.001316s |  0.001316s |
| **Multiplicação** | 0.456882s | 0.462800s | 0.465706s | 0.461796  |
| **Tempo de criação do arquivo de saída**         | 0.004267s | 0.002033s | 0.002355s | 0.002885s |

Tempo total da parte que não envolve cpu bound: 0.004030s
Tempo de cpu bound: 0.456882s
Tempo total do algoritmo: 0.460912s

Tempo concorrente = (0.004030 + 0.456882)/(0.004030+(0.456882/T))
Aceleração concorrente em um cenário perfeito = 0.45906198021971456

### Matriz 1000x1000
| | Teste 1 | Teste 2 | Teste 3 | Média |
|---|---|---|---|---|
| **Tempo de leitura dos arquivos binários**        | 0.000565s | 0.000673s | 0.001038s | 0.000758s |
| **Tempo de alocação de memória**        | 0.004547s | 0.004482s | 0.004927s | 0.004652s |
| **Multiplicação** | 4.840614s | 4.579715s | 4.586328s | 4.668885s |
| **Tempo de criação do arquivo de saída**         | 0.005607s | 0.006358s | 0.007077s | 0.006347s |

Tempo total da parte que não envolve cpu bound: 0.010719s
Tempo de cpu bound: 4.579715s
Tempo total do algoritmo: 4.590434s

Tempo concorrente = (0.010719 + 4.579715)/(0.010719+(4.579715/T))
Aceleração concorrente em um cenário perfeito = (0.010719 + 4.579715)/(0.010719+(4.579715/4.579715)) = 4.541750971338226

### Matriz 2000x2000
| | Teste 1 | Teste 2 | Teste 3 | Média |
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


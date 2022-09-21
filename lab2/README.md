## Resultados:

### Matriz 500x500
| | Teste 1 | Teste 2 | Teste 3 | Média |
|---|---|---|---|---|
| **Tempo de leitura dos arquivos binários**        | 0.000767s | 0.000925s | 0.001317 | - |
| **Tempo de alocação de memória**        | 0.001230s | 0.001403s | 0.001316s | - |
| **Multiplicação** | 0.456882s | 0.462800s | 0.465706s | - |
| **Tempo de criação do arquivo de saída**         | 0.004267s | 0.002033s | 0.002355s | - |

Tempo total da parte que não envolve cpu bound: 0.004030
Tempo de cpu bound: 0.456882
Tempo total do algoritmo: 0.460912

Tempo concorrente = (0.004030 + 0.456882)/(0.004030+(0.456882/T))

### Matriz 1000x1000
| | Teste 1 | Teste 2 | Teste 3 | Média |
|---|---|---|---|---|
| **Tempo de leitura dos arquivos binários**        | 0.000565s | 0.000673s | 0.001038s | - |
| **Tempo de alocação de memória**        | 0.004547s | 0.004482s | 0.004927s | - |
| **Multiplicação** | 4.840614s | 4.579715s | 4.586328s | - |
| **Tempo de criação do arquivo de saída**         | 0.005607s | 0.006358s | 0.007077s | - |

Tempo total da parte que não envolve cpu bound: 0.010719
Tempo de cpu bound: 4.579715
Tempo total do algoritmo: 4.590434

Tempo concorrente = (0.010719 + 4.579715)/(0.010719+(4.579715/T))

### Matriz 2000x2000
| | Teste 1 | Teste 2 | Teste 3 | Média |
|---|---|---|---|---|
| **Tempo de leitura dos arquivos binários**        | 0.000505s | 0.001601s | 0.000622s | - |
| **Tempo de alocação de memória**        | 0.004547s | 0.016270s | 0.017971s | - |
| **Multiplicação** | 40.899598s | 41.814996s | 42.799465s | - |
| **Tempo de criação do arquivo de saída**         | 0.024645s | 0.023829s | 0.025562s | - |

Tempo total da parte que não envolve cpu bound: 0.028881
Tempo de cpu bound: 40.899598
Tempo total do algoritmo: 40.928478

Tempo concorrente = (0.028881 + 40.89959)/(0.028881+(40.89959/T))


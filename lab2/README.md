

## 500x500
Tempo multiplicacao: 0.456676

## 1000x1000
Tempo multiplicacao: 4.165297

## 2000x2000
Tempo multiplicacao: 37.279191


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


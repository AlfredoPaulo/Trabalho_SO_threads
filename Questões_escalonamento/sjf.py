from operator import itemgetter

def tempo_espera(processos):
    # definindo a qnt. tempo de servico baseado na qnt de processos
    tempo_servico = [0] * len(processos)

    # definindo tamanho da lista de espera
    tempoEspera = [0] * len(processos)
    for x in range(1, len(processos)):
        tempo_servico[x] = (tempo_servico[x-1] + processos[x-1][2])
        tempoEspera[x] = tempo_servico[x] - processos[x][1]
        if (tempoEspera[x] < 0):
            tempoEspera[x] = 0
    return tempoEspera

def tempo_resposta(processos):
    # turnaround time = burstTime + waitingTime
    tempoResposta = [0] * len(processos)
    tempoEspera = tempo_espera(processos)
    for x in range(len(processos)):
        tempoResposta[x] = processos[x][2] + tempoEspera[x]
    return tempoResposta

def execucao_media(processos):
        tempoResposta = sum(tempo_resposta(processos))
        # Retornando o tempo medio 
        return (tempoResposta/len(processos))

def espera_media(processos):
    tempoEspera = sum(tempo_espera(processos))
    return (tempoEspera / len(processos))


def SJF(processos):
    # Ordenando por tempo de duraçao mais curto
    processos.sort(key=itemgetter(2))
    return processos


######################################################################
# quantidade de testes feitos
quant = 0

while(True):
    print(":::::::::::::::::::::::::::::::::::SJF:::::::::::::::::::::::::::::::::::")

    processos = []

    N = int(input("Quantidade de processos: "))
    if(N == 0):
        break

    for x in range(1, N + 1):
        pid = f"P{x}"
        X = int(input("Tempo de Chegada: "))
        Y = int(input("Tempo de Duracao: "))
        processos.append([pid, X, Y])


    print("\n------------------------------------\n")

    #processos = SJF(processos)
    tempoEspera = tempo_espera(processos)
    tempoResposta = tempo_resposta(processos)
    execucaoMedia = execucao_media(processos)
    esperaMedia = espera_media(processos)
    
    print(processos)

    quant += 1

    print(f"\nTeste {quant}")
    print(f"Tempo médio de execucao: {execucaoMedia}s")
    print(f"Tempo Médio de Espera: {esperaMedia}s")
    for proc in range(len(processos)):
        print(f"{processos[proc][0]}")


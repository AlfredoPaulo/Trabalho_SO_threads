def mostraPassos(q): #mostra os passos (O primerio a entrar é o primeiro a sair)
    for i in range(1,q+1):
        print(f"P{i} ",end="")
        if(i==q):
            print("")


def verificaDet(p,n):  #verifica o Det
    aux = p[0][0]
    c = 0 #contador auxilar 
    t = len(p)
    for i in range(1,t):
        if(p[i][0] > aux):
            c+=1
    return c


def calculaDet(p,n,teste): # calcula o Det = Escalonamento com tempo estendido
    t = len(p)
    soma = 0
    for i in range(0,t):
        soma += p[i][1]
    media = soma /n
    print(f"Teste {teste}: ")
    print(f"Tempo médio de execucao: {media:.2f}s ")
    print(f"Tempo médio de espera: 0s ") # é zero pois , o tempo de espaçamento entre os processos é grande
    mostraPassos(n)



def resultado(p,teste,n): #calcula e execula verificação 
    tsoma = []
    t = len(p)
    aux = 0
    soma = 0
    aux2 = 0
    soma2 = 0
    for i in range(0,t):
        aux += p[i][1]
        soma +=aux 
        tsoma.append(soma)
    for i in range(1,t-1):
        aux2 += p[i][1]
        soma2 +=aux 
    media = (soma)/n
    mediaTempo = (tsoma [len(tsoma) -2])/n
    
    var =  verificaDet(p,n)
    if(var==n-1):
        calculaDet(p,n,teste)
    else:
        print(f"Teste {teste} ")
        print(f"Tempo médio de execucao: {media -1:.2f}s ")
        print(f"Tempo médio de espera: {mediaTempo -1:.2f}s ")
        mostraPassos(n)
    tsoma = []
    aux = 0
    soma = 0
    aux2 = 0
    soma2 = 0

p = [] #declaração da lista de processos
aux = [] #declaração da lista auxiliar para cada processo
teste = 1 #número de Processos 

while True: #programa principal
    n = int(input("Digite a quantidade de processos: ")) # n= qauntidade de processos
    if(n==0):
        break
    for i in range(1,n+1):
        e = int(input(f"Entrada do processo P{i}: "))
        t = int(input(f"Tempo de duração do processo P{i}: "))
        aux.append(e)
        aux.append(t)
        p.append(aux)
        aux = []
    resultado(p,teste,n)
    teste+=1
    p = []
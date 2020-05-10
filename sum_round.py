a = int(input())
b = []
for i in range(0,a):
    c = int(input())
    b.append(c)
for i in b:
    count = 0
    potencia = 0
    total = 0
    answ = []
    if(i <= 10):
        count = 1
        answ.append(i)
    else:
        while (i > 0):
            div = i%10
            i = i//10
            #print("Numero en el ciclo:", i)
            if(div != 0):
                count += 1
                answ.append(div)
                potencia += 1
            else:
                potencia += 1
                total += i**potencia
                print("Numero: ", i)
                print("Potencia:", potencia)
                print("Total: ", total)
        answ.append(total)
    print(count)
    for i in answ:
        print(i, end=' ')
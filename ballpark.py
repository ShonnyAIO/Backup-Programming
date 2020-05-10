n = int(input())

# 150 -> 200
# 4 -> 4
# 34545646456456 -> 300000000000

indice = len(str(abs(n)))
respuesta = int(round(n, indice*(-1)+1))
print(respuesta)
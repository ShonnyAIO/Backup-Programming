n,c = map(int,input().strip().split(" "))
arr = list(map(int, input().split()))
total = sum(arr)
if(c > total):
    respuesta = 1
else:
    respuesta = total//c
    respuesta += 1
print(respuesta)


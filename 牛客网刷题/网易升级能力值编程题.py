def max(a,b):
    if a<b:
        a,b=b,a
    while b!=0:
        tem=a%b
        a=b
        b=tem
    return a
list=raw_input().split(' ')
num,c=int(list[0]),int(list[1])
bi=raw_input().split(' ')
for i in bi:
    if int(i) <= c:
        c+=int(i)
    else:
        c+=max(c,int(i))
print c

def cal(n):
    res,left=0,0
    while n>0:
        if n==1:
            return res
        elif n==2:
            res+=1
            return res
        else:
            res+=n/3
        left=n%3
        n=n/3
        n=left+n
    return res
     
while True:
    try:
        n=int(input())
    except:
        break
    if n==0:
        break
    print(cal(n))

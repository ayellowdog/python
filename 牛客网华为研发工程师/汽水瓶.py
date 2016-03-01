"""有这样一道智力题：“某商店规定：三个空汽水瓶可以换一瓶汽水。
小张手上有十个空汽水瓶，她最多可以换多少瓶汽水喝？”答案是5瓶，
方法如下：先用9个空瓶子换3瓶汽水，喝掉3瓶满的，喝完以后4个空瓶子，用3个再换一瓶，喝掉这瓶满的，这时候剩2个空瓶子。然后你让老板先借给你一瓶汽水，喝掉这瓶满的，喝完以后用3个空瓶子换一瓶满的还给老板。
如果小张手上有n个空汽水瓶，最多可以换多少瓶汽水喝？"""
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

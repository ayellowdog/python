"""�������������Լ��"""
def max(a,b):
    if a<b:
        a,b=b,a    #a is the max
    while b!=0:
        tem=a%b
        a=b
        b=tem
    return a



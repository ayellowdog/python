def insertsort(list1):
    for i in xrange(len(list1)-1):
        for j in xrange(i+1,len(list1)):
            if list1[i]>list1[j]:
                tem=list1[i]
                list1[i]=list1[j]
                list1[j]=tem
    return list1
n=int(input())
inilist=[]
for i in xrange(n):
   inilist.append(int(input()))
listset=set(inilist)
reslist=insertsort(list(listset))
for j in reslist:
    print ("%d"%(j))

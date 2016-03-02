def insertsort(list1):
    for i in xrange(len(list1)):
        for j in xrange(i+1,len(list1)):
            if list1[i]>list1[j]:
                tem=list1[i]
                list1[i]=list1[j]
                list1[j]=tem
    return list1
list1=[9,8,7,6,5,4]
print insertsort(list1)
                

"""���Ա�ĳ���Ϊ10���������£�ð��������Ҫ�Ƚϴ���Ϊ������"""
def bulsort(list1):
    mark=0
    for i in xrange(len(list1)-1,0,-1):
        for j in xrange(i):
            if list1[j]>list1[j+1]:
                mark+=1
                tem=list1[j+1]
                list1[j+1]=list1[j]
                list1[j]=tem
    list1.append(mark)
    return list1
list1=[10,9,8,7,6,5,4,3,2,1]
print bulsort(list1)
                    

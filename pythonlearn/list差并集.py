list1=[1,2,3,4,4,6,7]
list2=[1,2,4,6,7,100]
list1=list(set(list1).difference(set(list2)))"""list1=list(set(list1).union(set(list2)))"""
print list1

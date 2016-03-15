def quick_sort(slist,l,r):
    if l<r:
        i,j,x=l,r,slist[l]
        while i<j:
            while i<j and slist[j]>=x:
                j-=1
            if i<j:
                slist[i]=slist[j]
                i+=1
            while i<j and slist[i]<x:
                i+=1
            if i<j:
                slist[j]=slist[i]
                j-=1
        slist[i]=x
        quick_sort(slist,l,i-1)
        quick_sort(slist,i+1,r)
    
list1=[2,34,35,7,9,1]
quick_sort(list1,0,len(list1)-1)
print list1
    
    

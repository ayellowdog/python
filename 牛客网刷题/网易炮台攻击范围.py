"""兰博教训提莫之后,然后和提莫讨论起约德尔人,谈起约德尔人,自然少不了一个人,
那 就是黑默丁格------约德尔人历史上最伟大的科学家. 提莫说,黑默丁格最近在思考一个问题:
黑默丁格有三个炮台,炮台能攻击到距离它R的敌人 (两点之间的距离为两点连续的距离,例如(3,0),(0,4)之间的距离是5),
如果一个炮台能攻击 到敌人,那么就会对敌人造成1×的伤害.黑默丁格将三个炮台放在N*M方格中的点上,并且给出敌人 的坐标.
问:那么敌人受到伤害会是多大?

第一行9个整数,R,x1,y1,x2,y2,x3,y3,x0,y0.R代表炮台攻击的最大距离,(x1,y1),(x2,y2),
(x3,y3)代表三个炮台的坐标.(x0,y0)代表敌人的坐标.

输出一行,这一行代表敌人承受的最大伤害,(如果每个炮台都不能攻击到敌人,输出0×)"""
"""
思考：坐标可能为负数，要考虑.计算点到点的距离，大于result+1
测试：r=1 三个坐标（1，1）（2,2,）（3,3） 目标（1,2）输出为1x
"""
def pointlength(x1,y1,x2,y2):
    length=((max(x1,x2)-min(x1,x2))**2+(max(y1,y2)-min(y1,y2))**2)**0.5
    return length
listinput=raw_input().split(' ')
r,x1,y1,x2,y2,x3,y3,x0,y0,mark=int(listinput[0]),int(listinput[1]),int(listinput[2]),int(listinput[3]),int(listinput[4]),int(listinput[5]),int(listinput[6]),int(listinput[7]),int(listinput[8]),0
if r-pointlength(x1,y1,x0,y0)>=0:
    mark+=1
if r-pointlength(x2,y2,x0,y0)>=0:
    mark+=1
if r-pointlength(x3,y3,x0,y0)>=0:
    mark+=1
print str(mark)+'x'


    

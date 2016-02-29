def sub(nums):
    if len(nums)==0:return [[]]
    if len(nums)==1:return [nums]
    pattern=sub(nums[1:])
    print pattern
sub([1,2,3,4,5])

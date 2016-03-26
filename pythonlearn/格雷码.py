class GrayCode:
    def Gray(self, n):
        if n == 1:
            return ['0', '1']
        tem = self.Gray(n - 1)
        result = []
        for i in tem:
            result.append('0' + i)
        for i in tem[::-1]:
            result.append('1' + i)
        return result
prin=GrayCode()
print prin.Gray(5)

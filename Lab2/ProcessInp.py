x="..............3.85..1.2.......5.7.....4...1...9.......5......73..2.1........4...9"

b=list(x)
b=map(lambda x: "0" if x=="." else x,b)

ans=[]
for i in xrange(9):
    ans.append(b[i*9:(i+1)*9])

ans = map(lambda x: " ".join(x),ans)
str1 = "\n".join(ans)

print ans
print str1

f= open('f1.txt','w')
f.write(str1)

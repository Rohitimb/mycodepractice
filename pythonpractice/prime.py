def prime_check(num):
    '''Prime check function'''
    for x in range(2,(int)((num/2)+1)):
        if not num % x:
            return None
    return num

print('\n')
for y in range(1,101):
    if y == prime_check(y):
        print(y)
print('series\n')



def prime_series(num):
    m = 0
    '''Prime series function'''
    for val in range(1,num):
        #print('1')
        for x in range(2,(int)((val/2)+1)):
            m=x
            #print(m)
            
            if val % x:
                break
        if m == (int)(val/2):
            print(val,end=" ")
        else:
            pass
            



prime_series(101)

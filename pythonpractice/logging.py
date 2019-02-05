#return list with even numbers
def myfunc(*argc):
    t=[1]
    t.pop()
    
    for x in argc:
        if x%2 == 0:
             t.append(x)  
    return t

print(myfunc(1,2,3,4,5,6,7,8,9,10))

# return string with[even index in uppercase and odd index in lowercase]
def fun2(val):
    c = -1
    m =""
    for i in val:
        c += 1
        if c % 2:
            m += i.lower()
        else:
            m += i.upper()
    return m
print(fun2('pythonisawesome'))

#returns the lesser of two given numbers if both numbers are even
#but returns the greater if one or both numbers are odd

def fun3(x,y):
    if x%2 or y%2:
        if x > y:
            return x
        else:
            return y
    else:
        if x < y:
            return x
        else:
            return y
print(fun3(2,4))
print(fun3(2,5))

#two-word string and returns True if both words begin with same letter
def animal_crackers(text):
    x = text.split(' ')
    if(x[0][0] == x[1][0]):
        return True
    else:
        return False
      
print(animal_crackers('Levelheaded Llama'))
print(animal_crackers('Crazy Kangaroo'))

#Given two integers, return True if the sum of the integers is 20
#or if one of the integers is 20.
#If not, return False
def makes_twenty(n1,n2):
    if n1 == 20 or n2 == 20 or n1+n2 == 20:
        return True
    else:
        return False
print(makes_twenty(20,10))
print(makes_twenty(12,8))
print(makes_twenty(2,3))


#Write a function that capitalizes the first and fourth letters of a name

def old_macdonald(name):
    return name[0].upper() + name[1:3] + name[3].upper()+name[4:]
    
print(old_macdonald('macdonald'))

#Given a sentence, return a sentence with the words reversed
#master_yoda('I am home') --> 'home am I'
#master_yoda('We are ready') --> 'ready are We

def master_yoda(text):
    x = text.split(" ")
    l=[]
    
    for i in reversed(x):
        l.append(i)
        
    x = " ".join(l)
    return x
    
print(master_yoda('I am home'))



#ALMOST THERE: Given an integer n, return True if n is within 10 of
#either 100 or 200
#almost_there(90) --> True
#almost_there(104) --> True
#almost_there(150) --> False
#almost_there(209) --> True

def almost_there(n):
    if n in range(100,111) or n in range(90,101) or \
       n in range(200,211) or n in range(1900,201):
        return True
    else:
        return False

print(almost_there(90))    
print(almost_there(104))
print(almost_there(150))
print(almost_there(209))



#Given a list of ints, return True if the array contains a 3 next to a 3
#somewhere.

def has_33(nums):
    for x in range(0,len(nums)-1):
        if nums[x] == nums[x+1]:
            return True
    return False

print(has_33([1, 3, 3]))
print(has_33([1, 3, 1, 3]))
print(has_33([3, 1, 3]))



#PAPER DOLL: Given a string,
#return a string where for every character in the
#original there are three characters

def paper_doll(text):
    s=''
    for m in text:
        for x in range(0,3):
            s += m
    return s

print(paper_doll('Hello'))
print(paper_doll('Mississippi'))


#BLACKJACK: Given three integers between 1 and 11,
#if their sum is less than or equal to 21,
#return their sum. If their sum exceeds 21 and there's an
#eleven, reduce the total sum by 10.
#Finally, if the sum (even after adjustment) exceeds 21, return 'BUST'


def blackjack(a,b,c):
    s = a+b+c
    if s <=  21:
        return s
    else:
        if a == 11 or b == 11 or c == 11:
            s -= 10
            return s
        else:
            return 'BUST'
        

print(blackjack(5,6,7))
print(blackjack(9,9,9))
print(blackjack(9,9,11))

def summer_69(arr):
    s=0
    e=0
    for x in arr:
        if x == 6:
            e=1
        if e == 0 or e == 2:
            s=s+x
        if e == 1 and x == 9:
            e=2
    return s

#SUMMER OF '69: Return the sum of the numbers in the array,
#except ignore sections of numbers starting with a 6 and
#extending to the next 9 (every 6 will be followed by at least one 9).
#Return 0 for no numbers.
summer_69([1, 3, 5]) #--> 9
summer_69([4, 5, 6, 7, 8, 9,1,2]) #--> 9
summer_69([2, 1, 6, 9, 11])# --> 14

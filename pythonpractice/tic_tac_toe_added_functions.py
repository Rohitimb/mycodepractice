#!/usr/bin/env python
# coding: utf-8

# In[8]:


l=[' ',' ',' ',' ',' ',' ',' ',' ',' ']
k = 0

def check_for_win(xolist,c):    
    if xolist[0] == xolist[1] and xolist[1] == xolist[2] and xolist[0] != ' ' and xolist[1] != ' ' and xolist[2] != ' ':
        print(f'{c} user won')
        return True
    else:
        return False

def set_val(pos,sign):
    pos -= 1
    global k
    
    if l[pos] != ' ':
        print('Invalid move\n')
        print('|{}|{}|{}|\n|{}|{}|{}|\n|{}|{}|{}|'.format(l[0],l[1],l[2],l[3],l[4],l[5],l[6],l[7],l[8]))
        return
    if sign:
        x='0'
    else:
        x='X'
        
    l[pos]=x
    
    for i in range(len(l)):
        if l[i] != ' ':
            k += 1
    if k == 9:
        print('Game tied\n')
        k = 0
        return True
    else:
        k = 0
        
    print('|{}|{}|{}|\n|{}|{}|{}|\n|{}|{}|{}|'.format(l[0],l[1],l[2],l[3],l[4],l[5],l[6],l[7],l[8]))
    
    if check_for_win([l[0],l[1],l[2]],x) or check_for_win([l[3],l[4],l[5]],x)    or check_for_win([l[6],l[7],l[8]],x) or check_for_win([l[0],l[3],l[6]],x)    or check_for_win([l[1],l[4],l[7]],x) or check_for_win([l[2],l[5],l[8]],x)    or check_for_win([l[0],l[4],l[8]],x) or check_for_win([l[2],l[4],l[6]],x):
        return True
    else:
        return False


# In[9]:


def game_play():
    m=False
    quit = False
    choice = input('Player 1: Do you want to be X or 0 ? ')

    if choice == 'X' or choice == 'x':        
        sign = False
    elif choice == '0':
        sign = True
    else:
        print('Invalid choice\n')
        return
    ans = input('Press Y or y to start, N or n to quit the game ')

    if ans == 'N' or ans == 'n':
        return
    #print('|{}|{}|{}|\n|{}|{}|{}|\n|{}|{}|{}|'.format('_','_','_','_','_','_',l[6],l[7],l[8]))
    print('|{}|{}|{}|\n|{}|{}|{}|\n|{}|{}|{}|'.format(l[0],l[1],l[2],l[3],l[4],l[5],l[6],l[7],l[8]))
        
    x = input('Player 1 : Enter position to move(1-9)')
         
    set_val(int(x),sign)

    while(x!=0 or x != '0' and quit != True):
        if m:
            x = int(input('Player 1 : Enter position to move(1-9)'))
        else:
            x = int(input('Player 2 : Enter position to move(1-9)'))
        
        if x not in range(1,10):
            print('Invalid position \n')
            continue;
            
        if l[x-1] != ' ':
            print('in fun Invalid move\n')
            print('|{}|{}|{}|\n|{}|{}|{}|\n|{}|{}|{}|'.format(l[0],l[1],l[2],l[3],l[4],l[5],l[6],l[7],l[8]))
            continue        
        
        m = not m
        sign = not sign
        
        if x==0 or x=='0':
            break

        if True == set_val(x,sign):
            ans = input('\nDo you want to play in again Y/y or N/n?')
            if ans == 'N' or ans == 'n':
                quit = True
                break
            else:
                m= True
                for i in range(len(l)):
                    l[i]=' '
                print('|{}|{}|{}|\n|{}|{}|{}|\n|{}|{}|{}|'.format(l[0],l[1],l[2],l[3],l[4],l[5],l[6],l[7],l[8]))
                pass


# In[10]:


print('Welcome to Tic Tac Toe by Python 3.7.2!\n')
game_play()


# 

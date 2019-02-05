import sys
import pyodbc

server = 'usvaboselcm.cigl3uuefjgx.us-east-1.rds.amazonaws.com'
#database = input("Database ? ")
database = 'einfochips'
username = 'BoseLCMAdmin'
password = 'boselcmadmin123'

#tablename = 'BOSEEMPLOYEE'
tablename = 'mytable'
#tablename = input('Table name = ')

#driver= '{ODBC Driver 17 for SQL Server}'
driver= 'SQL Server'

print('Connecting to ' + database + ' database')
print('Retrieving data from table ' + tablename)

'''
cnxn = pyodbc.connect('DRIVER='+driver+';PORT=1433;SERVER='+server+';PORT=1443;DATABASE='+database+';UID='+username+';PWD='+ password)
'''

#'''
#Connection with the database
try:
    cnxn = pyodbc.connect('DRIVER='+driver+';PORT=1433;SERVER='+server+';PORT=1443;DATABASE='+database+';UID='+username+';PWD='+ password)
except pyodbc.Error as ex:
    sqlstate = ex.args[0]
    if sqlstate == '28000':
        print("LDAP Connection failed: check password")    
#'''
cursor = cnxn.cursor()

''''''''''''''''''''''''''''''''''''''''''''''''''''''''
def checkIfPresent(val1,val2,val3):
    '''Function to check if data exists in the table'''
    #print(checkIfPresent.__doc__)
    cursor = cnxn.cursor()
    cursor.execute("SELECT * FROM [einfochips].[dbo].["+tablename +"] WHERE UserName = ? AND id= ? AND city =?",val1,val2,val3)
    
    row = cursor.fetchone()
    if row == None:
        return False
    else:
        return True
    
''''''''''''''''''''''''''''''''''''''''''''''''''''''''
def InsertDataToTable():
    '''Function to insert data into the table'''
    #print(InsertDataToTable.__doc__)
    personname = input('\n\nTo add data\nEnter UserName = ')
    personid = input('Enter id = ')
    personcity = input('Enter city = ')

    if checkIfPresent(personname,personid,personcity) == False:        
        cursor.execute("INSERT INTO [einfochips].[dbo].["+tablename+"](UserName,id,city) VALUES(?, ?, ?)", personname,personid, personcity)
        cnxn.commit()
        return True
    else:
        return False
    
''''''''''''''''''''''''''''''''''''''''''''''''''''''''
c = 0
for row in cursor.columns(table=tablename):
    print( row.column_name,end=" ")
    c+=1
#print(f'Column count = {c}')
   
cursor.execute("SELECT * FROM [einfochips].[dbo].["+tablename +"]")
row = cursor.fetchone()

print('\n')
mlist =[1,2,3]
help(mlist.insert)
while row:
    for x in range(0,c):
        print (str(row[x]),end=" ")
    print('\n')
    row = cursor.fetchone()

if True == InsertDataToTable():
    print('Added successfully')
else:
    print('Data exist')

cnxn.close()

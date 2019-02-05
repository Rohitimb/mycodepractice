import pyodbc
import csv
from time import gmtime, strftime

'''Server connection data'''
server = 'usvaboselcm.cigl3uuefjgx.us-east-1.rds.amazonaws.com'
database = 'einfochips'
username = 'BoseLCMAdmin'
password = 'boselcmadmin123'
tablename = 'mytable2'
#driver= '{ODBC Driver 17 for SQL Server}'
driver= 'SQL Server'

''' maintaining counts for errors and total records '''
recordCount = 0
errorcount = 0

''' path where error will be logged '''
errorpath = 'logfile.txt'

print('Connecting to ' + database + ' database')
print('Retrieving data from table ' + tablename)

''' Connection with the database '''
try:    
    cnxn = pyodbc.connect('DRIVER='+driver+';PORT=1433;SERVER='+server+';PORT=1443;DATABASE='+database+';UID='+username+';PWD='+ password,autocommit=False)
except pyodbc.Error as ex:
    #cnxn.close()
    sqlstate = ex.args[0]
    if sqlstate == '28000':
        print("LDAP Connection failed: check login details")
cursor = cnxn.cursor()
''''''''''''''''''''''''''''''''''''''''''''''''''''''''

''''''''''''''''''''''''''''''''''''''''''''''''''''''''
cursor.execute("SELECT * FROM [einfochips].[dbo].[mytable2]")
row = cursor.fetchall()
for x in row:
    print(x)

cursor.execute("insert into [einfochips].[dbo].[mytable2](id,name,state,pin) values(1,'ABC','GJ',4584)")
#cnxn.cursor().execute('START TRANSACTION')
cursor.execute("insert into [einfochips].[dbo].[mytable2](id,name,state,pin) values(1,'ABC','GJ',4343)")
cursor.commit()    
cursor.execute("SELECT * FROM [einfochips].[dbo].[mytable2]")
row = cursor.fetchall()
for x in row:
    print(x)
    
#cursor.rollback()
cursor.execute("SELECT * FROM [einfochips].[dbo].[mytable2]")
row = cursor.fetchall()
for x in row:
    print(x)
    
#cursor.rollback()
cursor.close()
del cursor
cnxn.close()

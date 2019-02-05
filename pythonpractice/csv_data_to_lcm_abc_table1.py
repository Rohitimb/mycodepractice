import pyodbc
import csv

server = 'usvaboselcm.cigl3uuefjgx.us-east-1.rds.amazonaws.com'
database = 'LCM'
username = 'BoseLCMAdmin'
password = 'boselcmadmin123'
tablename = 'ABC'
#driver= '{ODBC Driver 17 for SQL Server}'
driver= 'SQL Server'

print('Connecting to ' + database + ' database')
print('Retrieving data from table ' + tablename)

''' Connection with the database '''
try:
    #print(help(pyodbc.connect))
    cnxn = pyodbc.connect('DRIVER='+driver+';PORT=1433;SERVER='+server+';PORT=1443;DATABASE='+database+';UID='+username+';PWD='+ password,autocommit=False)
except pyodbc.Error as ex:
    sqlstate = ex.args[0]
    if sqlstate == '28000':
        print("LDAP Connection failed: check login details")
cursor = cnxn.cursor()

''''''''''''''''''''''''''''''''''''''''''''''''''''''''
def insertIntoABCTable(listObj):
    ''' function to add csv file data to the ABC table.'''
    #print(len(listObj))

    username = listObj[0]
    userid = listObj[1]

    cursor.execute("INSERT INTO [LCM].[dbo].["+tablename+"](name,ID_1) VALUES(?,?)", username,userid)
    cnxn.commit()
    print(f'{listObj} successfully added to the table {tablename}')
    
''''''''''''''''''''''''''''''''''''''''''''''''''''''''   
with open('C:\\Users\\rohit.dharaviya\\Downloads\\sampleD.csv',mode='r') as csv_file:
    csv_reader = csv.reader(csv_file,delimiter=',')

    for nlistrow in csv_reader:
        insertIntoABCTable(nlistrow)
        
cnxn.close()

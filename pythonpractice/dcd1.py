import sys
import pyodbc


#db2=MySQLdb.connect("localhost","dcdjunki_imb","Imvimmhi.253#","dcdjunki_learning");

server = 'localhost'
database = 'dcdjunki_learning'
username = 'dcdjunki_imb'
password = 'Imvimmhi.253#'

#tablename = 'mytable'
#driver= '{ODBC Driver 17 for SQL Server}'
driver= 'SQL Server'

print('Connecting to ' + database + ' database')


'''
cnxn = pyodbc.connect('DRIVER='+driver+';SERVER='+server+';PORT=1443;DATABASE='+database+';UID='+username+';PWD='+ password)
'''

#'''
#Connection with the database
try:
    cnxn = pyodbc.connect('DRIVER='+driver+';SERVER='+server+';PORT=1443;DATABASE='+database+';UID='+username+';PWD='+ password)
except pyodbc.Error as ex:
    sqlstate = ex.args[0]
    if sqlstate == '28000':
        print("LDAP Connection failed: check password")    
#'''
cursor = cnxn.cursor()

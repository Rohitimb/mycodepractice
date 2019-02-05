import pyodbc
print('python code for database access')
#db2=MySQLdb.connect("localhost","dcdjunki_imb","Imvimmhi.253#","dcdjunki_learning");
con = pyodbc.connect('Driver={SQL Server};'
                      'Server=usvaboselcm.cigl3uuefjgx.us-east-1.rds.amazonaws.com;'
                      'Database=einfochips;'
                      'Trusted_Connection=yes;')

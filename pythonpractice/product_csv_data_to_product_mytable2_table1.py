import pyodbc
import csv

server = 'usvaboselcm.cigl3uuefjgx.us-east-1.rds.amazonaws.com'
database = 'einfochips'
username = 'BoseLCMAdmin'
password = 'boselcmadmin123'
tablename = 'mytable2'
#driver= '{ODBC Driver 17 for SQL Server}'
driver= 'SQL Server'

print('Connecting to ' + database + ' database')
print('Retrieving data from table ' + tablename)

''' Connection with the database '''
try:    
    cnxn = pyodbc.connect('DRIVER='+driver+';PORT=1433;SERVER='+server+';PORT=1443;DATABASE='+database+';UID='+username+';PWD='+ password)
except pyodbc.Error as ex:
    #cnxn.close()
    sqlstate = ex.args[0]
    if sqlstate == '28000':
        print("LDAP Connection failed: check login details")
        
'''
cnxn = pyodbc.connect('DRIVER='+driver+';PORT=1433;SERVER='+server+';PORT=1443;DATABASE='+database+';UID='+username+';PWD='+ password)
'''
with open('logfile.txt',a) as logfile:
    logfile.write('LogFileAdded')
cursor = cnxn.cursor()
''''''''''''''''''''''''''''''''''''''''''''''''''''''''
def insertIntoProductTable(listObj):
    ''' function to add csv file data to the mytable2 table.'''
    cursor.execute("SELECT id FROM [einfochips].[dbo].[division] WHERE name = ?",listObj[0])
    row = cursor.fetchone()
    division_id = row[0]
    
    cursor.execute("SELECT id FROM [einfochips].[dbo].[category] WHERE name = ?",listObj[1])
    row = cursor.fetchone()
    category_id = row[0]
    
    finance_category_code = listObj[2]
    finance_category_name = listObj[3]
    family_code = listObj[4]
    family_name = listObj[5]
    ecosystem_id = listObj[6]
    chipset_id = listObj[7]

    cursor.execute("SELECT id FROM [einfochips].[dbo].[lifecycle_phase] WHERE name = ?",listObj[8])
    row = cursor.fetchone()    
    lifecycle_phase_id = row[0]
         
    replacement_id = listObj[9]
    launch_date = listObj[10]
    last_manufactured = listObj[11]
    eol = listObj[12]
    eosl = listObj[13]
    if listObj[14] == 'N/A':
        software_build_id = 5
    else:
        software_build_id = listObj[14]
    part_num = listObj[15]
    name = listObj[16]
    alias_name = listObj[17]
    lcm_managed = listObj[18]
    '''
    print("INSERT INTO [einfochips].[dbo].[mytable2](division_id,\
category_id,\
finance_category_code,\
finance_category_name,\
family_code,\
family_name,\
ecosystem_id,\
chipset_id,\
lifecycle_phase_id,\
replacement_id,\
launch_date,\
last_manufactured,\
eol,\
eosl,\
software_build_id,\
part_num,\
name,\
alias_name,\
lcm_managed)\
 VALUES (?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)",\
division_id,\
category_id,\
finance_category_code,\
finance_category_name,\
family_code,\
family_name,\
ecosystem_id,\
chipset_id,\
lifecycle_phase_id,\
replacement_id,\
launch_date,\
last_manufactured,\
eol,\
eosl,\
software_build_id,\
part_num,\
name,\
alias_name,\
lcm_managed)
    '''
    
    cursor.execute("INSERT INTO [einfochips].[dbo].[mytable2](division_id,\
category_id,\
finance_category_code,\
finance_category_name,\
family_code,\
family_name,\
ecosystem_id,\
chipset_id,\
lifecycle_phase_id,\
replacement_id,\
launch_date,\
last_manufactured,\
eol,\
eosl,\
software_build_id,\
part_num,\
name,\
alias_name,\
lcm_managed)\
 VALUES (?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)",\
division_id,\
category_id,\
finance_category_code,\
finance_category_name,\
family_code,\
family_name,\
ecosystem_id,\
chipset_id,\
lifecycle_phase_id,\
replacement_id,\
launch_date,\
last_manufactured,\
eol,\
eosl,\
software_build_id,\
part_num,\
name,\
alias_name,\
lcm_managed)
    cnxn.commit()
    
    print(f'{listObj} successfully added to the table {tablename} .\n')
    
''''''''''''''''''''''''''''''''''''''''''''''''''''''''   
#with open('D:\\python\\product.csv',mode='r') as csv_file:
#with open('D:\\python\\smModofied180.csv',mode='r') as csv_file:
with open('D:\\python\\smModofied25.csv',mode='r') as csv_file:
    csv_reader = csv.reader(csv_file,delimiter=',')

    x = 0
    for nlistrow in csv_reader:
        if x == 0:
            print('Categories')
            x += 1
        elif x == 1:
            print('Going to add data')
            insertIntoProductTable(nlistrow)
            x += 1
        else:
            x +=1
            insertIntoProductTable(nlistrow)
cnxn.close()
'''
addding query
cursor.execute("INSERT INTO [einfochips].dbo.mytable2\
(division_id,\
category_id,\
finance_category_code,\
finance_category_name,\
family_code,\
family_name,\
ecosystem_id,\
chipset_id,\
lifecycle_phase_id,\
replacement_id,\
launch_date,\
last_manufactured,\
eol,\
eosl,\
software_build_id,\
part_num,\
name,\
alias_name,\
lcm_managed)\
VALUES\
(1,3,'STEREOFLR','Floorstanding Speakers','HED00027','301',1,'',9,'','01-01-1998','','01-01-1998','',1,'2300','301 AVM WHITE/WHITE','No_Alias','')")
cnxn.commit()
'''
#cnxn.close()
    #insertIntoProductTable(nlistrow)

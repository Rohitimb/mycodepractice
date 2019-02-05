import pyodbc
import csv
from time import gmtime, strftime

'''Server connection data'''
server = 'usvaboselcm.cigl3uuefjgx.us-east-1.rds.amazonaws.com'
database = 'einfochips'
username = 'BoseLCMAdmin'
password = 'boselcmadmin123'
tablename = 'product_sku'
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
def logErrorIfNotNullFieldNotSet(vallist,val):
    '''Log to the file when not null fields of table is not set'''
    global errorcount
    errorcount += 1

    with open(errorpath,'a') as fileHandler:
        if val == 'name':
            fileHandler.write(f'{val} field is empty for Material part_number {vallist[0]}\n')
            print(f'{val} field is empty for Material part_number {vallist[0]}\nError is logged in {errorpath}\n\n')
        else:
            fileHandler.write(f'{val} field is empty for SAP Description name {vallist[1]}\n')
            print(f'{val} field is empty for SAP Description name {vallist[1]}\nError is logged in {errorpath}\n\n')
    return
''''''''''''''''''''''''''''''''''''''''''''''''''''''''
def logErrorIfNotAbleToExtractFromOtherTable(data,index,val):
    '''Log to the file when not able to extract data from other table'''
    global errorcount
    errorcount += 1            
    with open(errorpath,'a') as fileHandler:
        fileHandler.write(f'Not able to get {val} for {data[index]} for SAP Description name {data[1]}\n')
        print(f'Not able to get {val} for {data[index]} for SAP Description name {data[1]}\n\n\
Error is logged in {errorpath}\n\n')
    return

''''''''''''''''''''''''''''''''''''''''''''''''''''''''
def insertIntoProductTable(listObj):
    ''' function to add csv file data to the product_sku table.'''
    global recordCount
    global errorcount
    recordCount += 1
    
    if(errorcount == 0):
        f = open(errorpath,'w');
        f.close()

    cursor.execute("SELECT id FROM [einfochips].[dbo].[product_sku] WHERE part_num = ?",listObj[0])
    row = cursor.fetchone()    
    if not (row == None):
        errorcount += 1            
        with open(errorpath,'a') as fileHandler:
            fileHandler.write(f'Duplicate entry for SAP Description name {listObj[1]}\n')
            print(f'Duplicate entry for SAP Description name {listObj[1]}\n\n\
Error is logged in {errorpath}\n\n')
        return
        
    if(listObj[0] == ''):
        logErrorIfNotNullFieldNotSet(listObj,'part_num');
        return

    if(listObj[1] == ''):
        logErrorIfNotNullFieldNotSet(listObj,'name');
        return
    
    if(listObj[7] == ''):
        logErrorIfNotNullFieldNotSet(listObj,'division_id');
        return

    if(listObj[8] == ''):
        logErrorIfNotNullFieldNotSet(listObj,'lifecycle_phase_id');
        return
    
    cursor.execute("SELECT id FROM [einfochips].[dbo].[division] WHERE name = ?",listObj[7])
    row = cursor.fetchone()
    if( row == None):
        logErrorIfNotAbleToExtractFromOtherTable(listObj,7,'division_id')
        return
    division_id = row[0]
        
    cursor.execute("SELECT id FROM [einfochips].[dbo].[category] WHERE name = ?",listObj[6])
    row = cursor.fetchone()
    if( row == None):
        logErrorIfNotAbleToExtractFromOtherTable(listObj,6,'category_id')
        return
    category_id = row[0]
    
    cursor.execute("SELECT id FROM [einfochips].[dbo].[lifecycle_phase] WHERE name = ?",listObj[8])
    row = cursor.fetchone()
    if( row == None):
        logErrorIfNotAbleToExtractFromOtherTable(listObj,8,'lifecycle_phase_id')
        return
    lifecycle_phase_id = row[0]

    cursor.execute("SELECT id FROM [einfochips].[dbo].[metric_definition1] WHERE name = ?",listObj[13])
    row = cursor.fetchone()
    if( row == None):
        logErrorIfNotAbleToExtractFromOtherTable(listObj,8,'metric_definition_id')
        return
    metric_definition_id = row[0]
    
    cursor.execute("SELECT target FROM [einfochips].[dbo].[metric_definition1] WHERE name = ?",listObj[13])
    row = cursor.fetchone()
    if( row == None):
        logErrorIfNotAbleToExtractFromOtherTable(listObj,8,'metric_measurement')
        return
    metric_measurement = row[0]
    
    finance_category_code = listObj[4]
    finance_category_name = listObj[5]
    family_code = listObj[2]
    family_name = listObj[3]
    ecosystem_id = 1
    chipset_id = ''

    replacement_id = ''
    launch_date = listObj[10]
    last_manufactured = ''
    eol = listObj[11]
    eosl = ''
        
    #software_build_id = listObj[13]
    software_build_id = 1
    part_num = listObj[0]
    name = listObj[1]
    alias_name = listObj[9]
    lcm_managed = ''
    
    cursor.execute("INSERT INTO [einfochips].[dbo].[product_sku]\
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
    
    cursor.execute("SELECT id FROM [einfochips].[dbo].[product_sku] WHERE name = ?",name)
    row = cursor.fetchone()
    metric_product_id = row[0]

    cursor.execute("SELECT id FROM [einfochips].[dbo].[lifecycle_phase] WHERE name = ?",listObj[8])
    row = cursor.fetchone()    
    lifecycle_phase_id = row[0]
    metric_comment = listObj[14]

    cursor.execute("INSERT INTO [einfochips].[dbo].[mytable]\
(metric_definition_id,\
product_id,\
period,\
measurement,\
lifecycle_phase_id,\
comment)\
 VALUES (?,?,GETDATE(),?,?,?)",\
metric_definition_id,\
metric_product_id,\
metric_measurement,\
lifecycle_phase_id,\
metric_comment)
    cnxn.commit()
    
    print(f'{listObj} \nRecord {recordCount} successfully added to the table {tablename}.') 
    print(f'Record {recordCount} successfully added to the table mytable.\n')
    
    if recordCount == 1 or recordCount % 100 == 0:
        print(strftime("%Y-%m-%d %H:%M:%S", gmtime()))
    
''''''''''''''''''''''''''''''''''''''''''''''''''''''''
with open('product_sku.csv',mode='r') as csv_file:
    csv_reader = csv.reader(csv_file,delimiter=',')    
    x = 0
    for nlistrow in csv_reader:        
        if x == 0:
            print('Categories',end=' ')
            print(nlistrow)
            print('\n--- Going to add data ---\n')
            x = 1
        #elif x >= 1 and x <= 10:
        else:
            insertIntoProductTable(nlistrow)
print(f'{recordCount-errorcount}/{recordCount} data are successfully inserted into the table\n')
if(errorcount > 0):
    print(f'{errorcount} data could not be inserted due to improper data\nError is logged at {errorpath}\n\n')
cursor.close()
del cursor
cnxn.close()    
#cnxn.close()

import sys
from PyQt5.QtCore import QCoreApplication
from PyQt5.QtWidgets import QApplication, QWidget,QPushButton,QLabel,QFileDialog,QDesktopWidget,QTextEdit,QComboBox,QLineEdit
import pyodbc
import csv
import getpass
from time import gmtime, strftime

'''Server connection data'''
server = 'usvaboselcm.cigl3uuefjgx.us-east-1.rds.amazonaws.com'
database = 'einfochips'
username = 'BoseLCMAdmin'
password = 'boselcmadmin123'
tablename = 'product_sku'
#driver= '{ODBC Driver 17 for SQL Server}'
driver= 'SQL Server'

'''Authorized Login Details'''
users = ['Rohit','admin','user']
passwords = ['0000','1234','5555']

''' maintaining counts for errors and total records '''
recordCount = 0
errorcount = 0
updatecount = 0
csv_file_loaded = False

''' path where error will be logged '''
errorpath = 'logfile.txt'

''' Connection with the database '''
'''
username = input('Enter Username : ')
password = getpass.getpass('Enter Password :')

if username in users:
    username = 'BoseLCMAdmin'
else:
     raise Exception("Unauthorized User")
    
if password in passwords:
    password='boselcmadmin123'
else:
     raise Exception("Invalid Password")
''' 
print('\nLoggedin Succefully\n\n')

print('Connecting to ' + database + ' database')
print('Retrieving data from table ' + tablename)

try:    
    cnxn = pyodbc.connect('DRIVER='+driver+';PORT=1433;SERVER='+server+';PORT=1443;DATABASE='+database+';UID='+username+';PWD='+ password,autocommit=False)
except pyodbc.Error as ex:
    #cnxn.close()
    sqlstate = ex.args[0]
    if sqlstate == '28000':
        print("LDAP Connection failed: check login details")
cursor = cnxn.cursor()

''''''''''''''''''''''''''''''''''''''''''''''''''''''''
def CountDistinctValues():
    ''' function to count distinct values of category, lcm changed and lifecycle phase id.'''
    global cursor
    category_total = 0
    lcm_total = 0
    lifecycle_phase_total = 0
    
    cursor.execute("select count(distinct category_id) from product_sku")
    row = cursor.fetchone()
    category_total = row[0]

    cursor.execute("select count(distinct lcm_managed) from product_sku")
    row = cursor.fetchone()
    lcm_total = row[0]

    cursor.execute("select count(distinct lifecycle_phase_id) from product_sku")
    row = cursor.fetchone()
    lifecycle_phase_total = row[0]

    return (category_total,lcm_total,lifecycle_phase_total)
''''''''''''''''''''''''''''''''''''''''''''''''''''''''

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

app = QApplication(sys.argv)
l = [1,2,3,4,5,6]
mainwidget = QWidget()
main_lbl=QLabel('PyQt5 with Python3',mainwidget)
footer_lbl=QLabel('',mainwidget)
info_textbox=QTextEdit(mainwidget)
auth_btn = QPushButton('Login', mainwidget)
load_file_btn = QPushButton('Load File', mainwidget)

skuadd_btn = QPushButton('LCM_sku_add', mainwidget)
skuupdate_btn = QPushButton('LCM_sku_update', mainwidget)
lookup_btn = QPushButton('LCMt_sku_Lookup', mainwidget)
total_btn = QPushButton('LCM_sku_Total', mainwidget)
skuread_btn = QPushButton('LCM_sku_read', mainwidget)
metricread_btn = QPushButton('LCM_metric_read', mainwidget)
metricadd_btn = QPushButton('LCM_metric_add', mainwidget)
lookup_table_choice = QComboBox(mainwidget)


passwid = QWidget()
name_lbl=QLabel('Enter Username',passwid)
pass_lbl=QLabel('Enter Password',passwid)
submit_btn=QPushButton('Login!',passwid)
name_lineedit= QLineEdit(passwid)
pass_lineedit= QLineEdit(passwid)
invalid_pass_lbl=QLabel('',passwid)


desk=QDesktopWidget()
screen = desk.screenGeometry()
print(type(screen))
w=screen.width()
h=screen.height()
print(screen.width())
print(screen.height())
 
mainwidget.setFixedSize(800,495)
mainwidget.move((w-mainwidget.width())/2,(h-mainwidget.height())/2)
mainwidget.setWindowTitle('Py Utility for DB access')

def checkPasswordandConnect():
    global users
    global passwords
    
    print(name_lineedit.text())
    print(pass_lineedit.text())

    password = pass_lineedit.text()
    username = name_lineedit.text()
    
    if username in users:
        username = 'BoseLCMAdmin'
    else:
        pass
    
    if password in passwords:
        password='boselcmadmin123'
        print('Correct password')
        auth_btn.setText("Logout")
        passwid.hide()
    else:
        invalid_pass_lbl.setText("Invalid Password!")

''''''''''''''''''''''''''''''''''''''''''''''''''''''''


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
        print('Default division is = CED')
        listObj[7] = 'CED'

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
    
    finance_category_code = listObj[4]
    finance_category_name = listObj[5]
    family_code = listObj[2]
    family_name = listObj[3]
    ecosystem_id = 1
    chipset_id = ''
        
    if(listObj[8] == ''):
        print('Default lifecycle_phase = Unknown')
        listObj[8]='Unknown'
        
    cursor.execute("SELECT id FROM [einfochips].[dbo].[lifecycle_phase] WHERE name = ?",listObj[8])
    row = cursor.fetchone()
    if( row == None):
        logErrorIfNotAbleToExtractFromOtherTable(listObj,8,'lifecycle_phase_id')
        return
    lifecycle_phase_id = row[0]
    
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

    cnxn.commit()
    
    print(f'{listObj} \nRecord {recordCount} successfully added to the table {tablename}.\n')
    if recordCount == 1 or recordCount % 100 == 0:
        print(strftime("%Y-%m-%d %H:%M:%S", gmtime()))

''''''''''''''''''''''''''''''''''''''''''''''''''''''''
def updateIntoProductTable(listObj):
    ''' function to update data into the product_sku table.'''
    global errorcount
    global updatecount

    cat_list = ['part_num','name','family_code','family_name','finance_category_code',\
            'finance_category_name',\
            'category_id','division_id','lifecycle_phase_id','alias_name',\
            'launch_date','eol','software_build_id','','comment','','','','','']
    
    if(errorcount == 0):
        f = open(errorpath,'w');
        errorcount = 1
        f.close()
        
    cursor.execute("SELECT * FROM [einfochips].[dbo].[product_sku] WHERE part_num = ?",listObj[0])    
    row = cursor.fetchone()
    
    listIndexNeedsToChange = []
    dataNeedsToChange = []

    cursor.execute("SELECT id FROM [einfochips].[dbo].[category] WHERE name = ?",listObj[6])
    row_category = cursor.fetchone()
    if( row_category == None):
        logErrorIfNotAbleToExtractFromOtherTable(listObj,6,'category_id')
        return
    new_category_id = row_category[0]

    cursor.execute("SELECT id FROM [einfochips].[dbo].[lifecycle_phase] WHERE name = ?",listObj[8])
    row_life = cursor.fetchone()
    if( row_life == None):
        logErrorIfNotAbleToExtractFromOtherTable(listObj,8,'lifecycle_phase_id')
        return
    new_lifecycle_phase_id = row_life[0]

    if(listObj[12] == ''):
        listObj[12] = 'N/A'
    cursor.execute("SELECT id FROM [einfochips].[dbo].[software_build] WHERE file_name = ?",listObj[12])
    row_soft_build = cursor.fetchone()
    if( row_soft_build == None):
        logErrorIfNotAbleToExtractFromOtherTable(listObj,12,'software_build_id')
        return
    software_build_id = row_soft_build[0]

    if(listObj[7] == ''):
        listObj[7] = 'CED'    
    cursor.execute("SELECT id FROM [einfochips].[dbo].[division] WHERE name = ?",listObj[7])
    row_div_id = cursor.fetchone()
    if( row_div_id == None):
        logErrorIfNotAbleToExtractFromOtherTable(listObj,7,'division_id')
        return
    new_division_id = row_div_id[0]
        
    for j,i in enumerate(listObj[:len(listObj)-1]):
        if j == 0 or j > 12:
            continue
        if i == '':
            '''Blank field means no change in the data'''
            pass
        else:
            if (j == 1 and i != row[17]) or\
               (j == 2 and i != row[5]) or\
               (j == 3 and i != row[6]) or\
               (j == 4 and i != row[3]) or\
               (j == 5 and i != row[4]) or\
               (j == 6 and new_category_id != row[2]) or\
               (j== 7 and new_division_id != 1) or\
               (j == 8 and new_lifecycle_phase_id != row[9]) or\
               (j == 9 and i != row[18]):
                listIndexNeedsToChange.append(j)
                dataNeedsToChange.append(i)

    if len(listIndexNeedsToChange) == 0:
        '''All the data are same, no need to change'''
        return
    
    st=""
    for i in range(len(listIndexNeedsToChange)):
        if listIndexNeedsToChange[i] == 6:
            st=st+cat_list[listIndexNeedsToChange[i]] + "=" +str(new_category_id)+",";
        elif listIndexNeedsToChange[i] == 7:
            st=st+cat_list[listIndexNeedsToChange[i]] + "=" +str(new_division_id)+",";
        elif listIndexNeedsToChange[i] == 8:
            st=st+cat_list[listIndexNeedsToChange[i]] + "=" +str(new_lifecycle_phase_id)+",";
        elif listIndexNeedsToChange[i] in [1,2,3,4,5,9,10,11]:
            st=st+cat_list[listIndexNeedsToChange[i]] + "='" +dataNeedsToChange[i]+"',";
        else:
            st=st+cat_list[listIndexNeedsToChange[i]] + "=" +dataNeedsToChange[i]+",";

    #removing last comma from the string
    st=st[:len(st)-1]
    
    #making sql query string to update
    exe_string="UPDATE [einfochips].[dbo].[product_sku] SET "\
                +st+\
                " WHERE part_num = " + listObj[0]
    
    print(exe_string)
    #committing the changes
    cursor.execute(exe_string)
    cnxn.commit()
    updatecount += 1
    print(f'{len(listIndexNeedsToChange)} fields got updated\n')
    return
''''''''''''''''''''''''''''''''''''''''''''''''''''''''

def authentication_handler():
    if auth_btn.text() == "Login":
        invalid_pass_lbl.setText("")
        name_lineedit.clear()
        pass_lineedit.clear()
        passwid.move((w-passwid.width())/2,(h-passwid.height())/2)
        passwid.show()
    else:
        auth_btn.setText("Login")

''''''''''''''''''''''''''''''''''''''''''''''''''''''''

def selcet_csv_file():
   global csv_file_loaded
   opt = QFileDialog
   csv_file_string=opt.getOpenFileName(mainwidget,"QFileDialog.getOpenFileName()")
   print(csv_file_string[0])
   if str(csv_file_string[0]).endswith(".csv"):
       main_lbl.setText(csv_file_string[0])
       csv_file_loaded = csv_file_string[0]
       return True
   else:
       print('Invalid file')
       main_lbl.setText("Invalid file selected")
       csv_file_loaded = False
       return False
   return

def insertDataToTable():
   if csv_file_loaded == False:
       print('csv file is not loaded')
       main_lbl.setText("csv file is not loaded")
       return
   global recordCount
   global errorcount
   with open(csv_file_loaded,mode='r') as csv_file:   
      csv_reader = csv.reader(csv_file,delimiter=',')
      x = 0
      for nlistrow in csv_reader:
         if x == 0:
            print('Categories',end=' ')
            print(nlistrow)
            x = 1
         else:
            insertIntoProductTable(nlistrow)
   show_count(2)
   recordCount = 0
   errorcount = 0

def updateDatoToTable():
   if csv_file_loaded == False:
       print('csv file is not loaded')
       main_lbl.setText("csv file is not loaded")
       return
   global recordCount
   global errorcount
   global updatecount
   with open(csv_file_loaded,mode='r') as csv_file:   
      csv_reader = csv.reader(csv_file,delimiter=',')
      x = 0
      for nlistrow in csv_reader:
         if x == 0:
            print('Categories',end=' ')
            print(nlistrow)
            x = 1
         else:
            updateIntoProductTable(nlistrow)
   show_count(3)
   recordCount = 0
   updatecount = 0
   errorcount = 0

def show_count(val):
   if val == 2:
      info_textbox.setPlainText(str(recordCount-errorcount)+'/'+str(recordCount)+' data are successfully inserted into the table.\n')
      footer_lbl.setText('Inserted = ' + str(recordCount-errorcount) + ' Failed = ' + str(errorcount));
      if(errorcount > 0):
          info_textbox.setPlainText(str(recordCount-errorcount)+'/'+str(recordCount)+' data are successfully inserted into the table.\n' + str(errorcount)+' data could not be inserted due to improper data.\nError is logged at ' + str(errorpath)+".")
          footer_lbl.setText('Inserted = ' + str(recordCount-errorcount) + ' Failed = ' + str(errorcount));
   elif val == 3:
      if updatecount > 0:
          info_textbox.setPlainText(str(updatecount) + " records are successfully updated to the table.\nError is logged at " + str(errorpath) + ".");
      else:
          info_textbox.setPlainText("No Update needed. csv data are identical to the database data.");
   else:
      category,lcm,lifecycle = CountDistinctValues()
      print('Data retrieved\n\n')
      print('category = ',category)
      print('lcm = ',lcm)
      print('lifecycle = ',lifecycle)
      info_textbox.setPlainText('Category : ' + str(category)+'\nLCM managed : ' + str(lcm) +
               '\nLifecycle phase : ' + str(lifecycle))
   

def selectNameFromTable(val):
    '''Selct name from tabnle mentioned in the parameter'''
    val=lookup_table_choice.currentText()
    if val == 'software_build':
        cursor.execute("SELECT file_name FROM "+val)
    else:
        cursor.execute("SELECT name FROM "+val)
        
    row = cursor.fetchall()
    st = ""
    for i in row:        
        st=st+str(i[0]) + "\n"
    print(st)
    info_textbox.setPlainText(st)
    return   

main_lbl.setFixedSize(510, 50)
main_lbl.setWordWrap(True)
main_lbl.move(170,10)
main_lbl.setStyleSheet("font-size:14px;border:1px solid black");

##name_lbl=QLabel('Enter Username',paname_lbl=QLabel('Enter Username',passwid)
##pass_lbl=QLabel('Enter Password',passwid)
##name_lineedit= QLineEdit(passwid)
##= QLineEdit(passwid)
##submit_btn=QLabel('Login!',passwid)
##invalid_pass_lbl=QLabel('',passwid)


passwid.setFixedSize(340,150)
passwid.move((w-passwid.width())/2,(h-passwid.height())/2)
passwid.setWindowTitle('Password')

name_lbl.setFixedSize(150,25)
name_lbl.move(10,20)
#name_lbl.setStyleSheet("font-size:14px;border:1px solid black");
name_lbl.setStyleSheet("font-size:14px;");

name_lineedit.setFixedSize(150,25)
name_lineedit.move(170,20)

pass_lineedit.setEchoMode(QLineEdit.Password)
pass_lineedit.setFixedSize(150,25)
pass_lineedit.move(170,55)



pass_lbl.setFixedSize(150, 25)
pass_lbl.move(10,55)
#pass_lbl.setStyleSheet("font-size:14px;border:1px solid black");
pass_lbl.setStyleSheet("font-size:14px;");

submit_btn.setFixedSize(80,35)
submit_btn.clicked.connect(checkPasswordandConnect)
submit_btn.move((passwid.width()-submit_btn.width())/2,90)
submit_btn.setStyleSheet("font-size:14px;outline:none");

invalid_pass_lbl.setFixedSize(100, 20)
invalid_pass_lbl.move((passwid.width()-invalid_pass_lbl.width())/2,125)
invalid_pass_lbl.setStyleSheet("font-size:14px;");



passwid.hide()

x = 70
skuadd_btn.setFixedSize(150, 50)
skuadd_btn.clicked.connect(insertDataToTable)
skuadd_btn.setStyleSheet("font-size:15px;");
skuadd_btn.move(10, x)

x=x+60
skuupdate_btn.setFixedSize(150,50)
skuupdate_btn.clicked.connect(updateDatoToTable)
skuupdate_btn.setStyleSheet("font-size:15px;");
skuupdate_btn.move(10, x)

x=x+60
lookup_btn.setFixedSize(150,50)
lookup_btn.clicked.connect(selectNameFromTable)
lookup_btn.setStyleSheet("font-size:15px;");
lookup_btn.move(10, x)

x=x+60
total_btn.setFixedSize(150,50)
total_btn.clicked.connect(show_count)
total_btn.setStyleSheet("font-size:15px;");
total_btn.move(10,x)

x=70
skuread_btn.setFixedSize(150,50)
skuread_btn.setStyleSheet("font-size:15px;");
skuread_btn.move(170, x)

x+=60
metricread_btn.setFixedSize(150,50)
metricread_btn.setStyleSheet("font-size:15px;");
metricread_btn.move(170, x)

x+=60
lookup_table_choice.setFixedSize(150,50)
lookup_table_choice.move(170, x)
lookup_table_choice.setStyleSheet("font-size:15px;");
lookup_table_choice.addItems(['category','lifecycle_phase','chipset','ecosystem','software_build'])

x+=60
metricadd_btn.setFixedSize(150,50)
metricadd_btn.setStyleSheet("font-size:15px;");
metricadd_btn.move(170, x)


info_textbox.setFixedSize(310, 135)
info_textbox.move(10,x+60)
info_textbox.setReadOnly(True)
#info_textbox.setWordWrap(True)
info_textbox.setStyleSheet("font-size:15px;text-align:left;border:1px solid black");

footer_lbl.setFixedSize(mainwidget.width()-20, 30)
footer_lbl.move(10,455)
footer_lbl.setStyleSheet("font-size:16px;border:1px solid black");
   

load_file_btn.clicked.connect(selcet_csv_file)
load_file_btn.setStyleSheet("font-size:16px;")
load_file_btn.setFixedSize(150, 50)
load_file_btn.move(10, 10)

auth_btn.setStyleSheet("font-size:16px;")
auth_btn.setFixedSize(100, 50)
auth_btn.clicked.connect(authentication_handler)
auth_btn.move(mainwidget.width()-auth_btn.width()-10, 10)

auth_btn.setText("Login")
mainwidget.show()
sys.exit(app.exec_())


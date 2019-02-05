
#first entry
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
1,\
3,\
'STEREOFLR',\
'Floorstanding Speakers',\
'HED00027',\
'301',\
1,\
'',\
9,\
'',\
'01-01-1998',\
'',\
'01-01-1998',\
'',\
1,\
'2300',\
'301 AVM WHITE/WHITE',\
'No_Alias',\
'')
#cnxn.commit()
print('added 1st')

#second entry
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
1,\
3,\
'STEREOFLR',\
'Floorstanding Speakers',\
'HED00027',\
'301',\
1,\
'',\
9,\
'',\
'01-01-1998',\
'',\
'01-01-1998',\
'',\
1,\
'2304',\
'301AVM-S',\
'No_Alias',\
'')
cnxn.commit()
print('added second')
cnxn.close()

'''
#addding query
cursor.execute("INSERT INTO [einfochips].dbo.product_sku\
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
cnxn.close()
'''


https://stackoverflow.com/questions/3783238/python-database-connection-close


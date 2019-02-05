import csv

'''
with open('data.csv',mode='w') as csv_file:
    csv_write=csv.writer(csv_file,delimiter=',',quotechar='"',quoting=csv.QUOTE_MINIMAL)
    
    csv_write.writerow(['5','GTHS','1','2018-12-18 16:23:02.343','1900-01-01 00:00:00.000','1'])
    csv_write.writerow(['6','MTWD','1','2018-12-19 18:23:02.343','1900-01-01 00:00:00.000','1'])

'''
print('done')

with open('data.csv', mode='w') as csv_file:
    #print(f'{row["businessUnitId"]} {row["businessUnitName"]} {row["businessUnitOwnerId"]} {row["createdOn"]} {row["updatedOn"]} {row["updatedBy"]}')

    fieldnames = ['businessUnitId', 'businessUnitName', 'businessUnitOwnerId','createdOn','updatedOn','updatedBy']
    writer = csv.DictWriter(csv_file, fieldnames=fieldnames)

    writer.writeheader()
    writer.writerow({'businessUnitId': '44', 'businessUnitName': 'HKSU', 'businessUnitOwnerId': '1' , 'createdOn':'2018-12-18 16:26:08.270' , 'updatedOn':'1900-01-01 00:00:00.000', 'updatedBy':'1'})
    writer.writerow({'businessUnitId': '55', 'businessUnitName': 'RRRR', 'businessUnitOwnerId': '1' , 'createdOn':'2018-12-18 16:26:08.270' , 'updatedOn':'1900-01-01 00:00:00.000', 'updatedBy':'1'})

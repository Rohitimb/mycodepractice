import csv

with open('product.csv',mode='r') as csv_file:
    csv_reader = csv.reader(csv_file,delimiter=',')
    line = 0
    for row in csv_reader:
        if line == 0:
            n = list(row)
            #print(len(n))
            for m in range(0,len(n)):
                print(f'{row[m]}',end=" ")
            print('\n')
            line+=1
        else:
            for m in range(0,len(n)):
                if line == 2:
                    print(f'7 = {row[7]}',end=" ")
                    print('\n')
                print(f'{row[m]}',end=" ")
            print('\n')
            line+=1

print(f'Processed {line} lines.')


'''
with open('data.csv', mode='r') as csv_file:
    csv_reader = csv.DictReader(csv_file)
    line = 0
    for row in csv_reader:
        if line == 0:
            n = list(row)
            print(len(n))
            for m in range(0,len(n)):
                print(f'{row[m]}',end=" ")
                #pass
            print('\n')
            line+=1
        print(f'{row["businessUnitId"]} {row["businessUnitName"]} {row["businessUnitOwnerId"]} {row["createdOn"]} {row["updatedOn"]} {row["updatedBy"]}')
        line += 1
    print(f'Processed {line} lines.')
'''


    

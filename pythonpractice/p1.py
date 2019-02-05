import MySQLdb
import pymysql

print('python database access')
#db = MySQLdb.connect("localhost","BoseLCMAdmin","boselcmadmin123","einfochips" )

conn = pymysql.connect(host='localhost', port=1433, user='BoseLCMAdmin', passwd='boselcmadmin123', db='einfochips')



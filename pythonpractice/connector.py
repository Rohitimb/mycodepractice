import mysql.connector
from mysql.connector import Error
from mysql.connector import errorcode

conn = mysql.connector.connect(host='SQL Server;PORT=1433;usvaboselcm.cigl3uuefjgx.us-east-1.rds.amazonaws.com',\
                                 user='BoseLCMAdmin',\
                                 password='boselcmadmin123')

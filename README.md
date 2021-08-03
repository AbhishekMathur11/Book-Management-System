# Book-Management-System
Management of library books
#program designed as a library management system
from flask import Flask
app=Flask(__name__)
import requests
import mysql.connector as a
con=a.connect(host='localhost',user='root',passwd='Ironavenger@1195',database='library')

def addbook():#function designed for adding a book to the database
  bn=input("Enter the name of the book:")
  c=input("Enter the book CODE:")
  t=input("Enter the number of books to be added:")
  ca=input("Enter the category:")
  data=(bn,c,t,ca)#data compilation moving towards sql query
  sql="insert into books values(%s,%s,%s,%s)"
  c=con.cursor()
  c.execute(sql,data)
  con.commit()
  print(">---------------------------------------------------------------------------------------------------------<")
  print("Data stored successfully!")
  main()
def issuebook():#function designed for book issue 
  n=input("Enter the name:")
  r=input("Enter the registration number:")
  bn=input("Enter the name of the book:")
  co=input("Enter the book code:")
  d=input("Enter date of issue in DD/MM/YY format:")
  a='insert into values(%s,%s,%s,%s,%s)'
  data=(n,r,bn,co,d)#data compilation moving towards sql query
  c=con.cursor()
  c.execute(a,data)
  con.commit()
  print(">---------------------------------------------------------------------------------------------------------<")
  print("Book",bn, "issued successfully to",n,"on",d)
  bookup(co,-1)
  

def submitb():#function designed for submission of book
  n=input("Enter the name:")
  r=input("Enter the registration number:")
  bn=input("Enter the name of the book:")
  co=input("Enter  the book code:")
  d=input("Enter the date of submission in DD/MM/YY format:")
  a='insert into values(%s,%s,%s,%s,%s)'
  data=(n,r,bn,co,d)
  c=con.cursor()
  c.execute(a,data)
  con.commit()
  print(">-----------------------------------------------------------------------------------------------------------<")
  print("Book",bn, "submitted successfully by",n,"on",d)
  bookup(co,1)
  

def bookup(co,u):#function designed for updation of the book database
  a='select TOTAL from books where BCODE=%s'
  data=(co,)
  c=con.cursor()
  c.execute(a,data)
  myresult=c.fetchone()
  t=myresult[0]+u
  sql='update books set TOTAL=%s where BCODE=%s'
  d=(t,co)
  c.execute(sql,d)
  con.commit()
  main()  


def dbook():#function designed for deletion of book from the books database
  cd=input("Enter the book code to be deleted:")
  a='delete from books where BCODE=%s'
  data=(a,cd)
  c=con.cursor()
  c.execute(a,data)
  con.commit()
  print("Book removed successfully!")
  main()

def displaybook():#function designed for display of the book information
  a='select*from books'
  c=con.cursor()
  c.execute(a)
  myresult=c.fetchall()
  for i in myresult:
    print("Book name:",i[0])
    print("Book code:",i[1])
    print("Total number of books:",i[2])
    print("Book category:",i[3])
  main()  

def useapi():#uses the api given and displays it as a json file
    response=requests.get('https://frappe.io/api/method/frappe-library?page=2&title=and')
    print(response.json)


def transaction(): #function for handling book transactions or penalties made by members
    print(""" OPTIONS
    1)BOOK PRICE
    2)OVERDUE PENALTY
    """)
    select=input("Choose option to continue")
    if select=='1':
        bname=input("Enter the book name")
        price=float(input("Enter price:"))
        quantity=int(input("Enter the quantity:"))
        total=price*quantity
        print("Total price of ",bname,"is",total)
    elif select=='2':
        name=("Enter name:")
        days=int(input("Enter no. of days:"))
        penalty=float(input("Enter the per day penalty:"))
        total=penalty*days
        print("The total penalty for",name,"is",total)
    else:
        print("Please enter an appropriate option")
        transaction()
    main()        


def main():#main function for redisplaying the option for the tasks
  print("""""                            LIBRARY MANAGEMENT SYSTEM
  TASKS
  1)ADD BOOK
  2)ISSUE BOOK
  3)SUBMIT BOOK
  4)DELETE BOOK
  5)DISPLAY BOOKS
  6)VIEW BOOKLIST WITH API
  7)TRANSACTIONS

   """"")
  if __name__ == '__main__':
    app.run(debug=True)      

  choice=input("Enter task no.:")
  print(">-----------------------------------------------------------------------------<")
  if choice=='1':
     addbook()
  elif choice=='2':
     issuebook()
  elif choice=='3':
     submitb()
  elif choice=='4':
     dbook()
  elif choice=='5':
     displaybook()
  elif choice=='6':
      useapi()   
  else:
     print("Please enter the appropriate task number")
     main()        


main()

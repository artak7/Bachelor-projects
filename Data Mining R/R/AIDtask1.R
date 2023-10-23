setwd("C://Users/pc/Documents/Магистратура/Анализ интернет-данных")
getwd()

library(stringr)
# library(RODBC)
library(RPostgreSQL)
 
library(lubridate) 
library(arules) 
library(datasets) 
library(stringi) 

# m = odbcConnect("db",uid="16393",pwd="123456")
# m = odbcConnect("tabler",uid="16394",pwd="123456")
connection = dbConnect(PostgreSQL(), host='localhost', port="5432", dbname = "db", user = "postgres", password = "123456")

A = read.table("access.log",header=FALSE,sep=" ")
clients = c()
clientsph = c()
id_books = c()

head(A)

for (i in 1: length(A[,1]))
{
  IP = toString(A[i, 1])
  IP
  DateTime = toString(A[i, 4])
  DateTime = substring(DateTime, 2)
  DateTime
  # DateTime = parse_date_time(DateTime , 'd b Y HMS!') 
  # DateTime
  DateTime = str_replace(DateTime, 'Mar', '3')
  DateTime = str_replace_all(DateTime, '/', '-')
  DateTime = str_replace(DateTime, ':', ' ')
  DateTime
  
  # Str = strsplit(DateTime, ' ')
  # Time = Str[[1]][2]
  # Time
  # hour = substring(Time, 1, 2)
  # hour
  
  Str = toString(A[i, 6])
  Str
  Str = strsplit(Str, ' ')
  Str
  Querytype = Str[[1]][1]
  Query = Str[[1]][2]
  link = str_extract_all(Query, boundary("word"), simplify = TRUE)
  link
  id_book = 0
  if (length(link) > 2 && link[,2] == "id_book")
  {
    id_book = link[,3]
    id_books = append(id_books, id_book)
  }
  
  Query = link[,1] 
  
  Status = A[i, 7]
  bytes = A[i, 8]
  ID = A[i, 9]
  ID = substring(ID, 3)
  
  head(IP)
  head(DateTime)
  head(Querytype)
  head(Query)
  head(id_book)
  head(Status)
  head(bytes)
  head(ID)
  
  IP = toString(IP)
  
  clients = append(clients, ID)
  
  # clientsph[] = 

  values = paste0('"',IP,'",', '"', DateTime,'",', '"', Query, '",',id_book, ',', ID)
  sql <- paste("INSERT INTO tabler VALUES (",values,")" ) 
  sql
  # sqlsave(connection, sql)
  # dbSendQuery(connection, sql) 
}

# length(A[,1])

for (i in 1: )
{
  IP = toString(A[i, 1])
  # IP
  # DateTime = toString(A[i, 4])
  # DateTime = substring(DateTime, 2)
  # DateTime
  # # DateTime = parse_date_time(DateTime , 'd b Y HMS!') 
  # # DateTime
  # DateTime = str_replace(DateTime, 'Mar', '3')
  # DateTime = str_replace_all(DateTime, '/', '-')
  # DateTime = str_replace(DateTime, ':', ' ')
  # DateTime
  
  # Str = strsplit(DateTime, ' ')
  # Time = Str[[1]][2]
  # Time
  # hour = substring(Time, 1, 2)
  # hour
  
  Str = toString(A[i, 6])
  # Str
  Str = strsplit(Str, ' ')
  # Str
  # Querytype = Str[[1]][1]
  Query = Str[[1]][2]
  link = str_extract_all(Query, boundary("word"), simplify = TRUE)
  # link
  id_book = 0
  if (length(link) > 2 && link[,2] == "id_book")
  {
    id_book = link[,3]
    id_books = append(id_books, id_book)
  }
  
  Query = link[,1] 
  
  # Status = A[i, 7]
  # bytes = A[i, 8]
  ID = A[i, 9]
  ID = substring(ID, 3)
  print(i)
  
  # head(IP)
  # head(DateTime)
  # head(Querytype)
  # head(Query)
  # head(id_book)
  # head(Status)
  # head(bytes)
  # head(ID)
  # 
  IP = toString(IP)
  
  clients = append(clients, ID)
  
  # clientsph[] = 
  
  # values = paste0('"',IP,'",', '"', DateTime,'",', '"', Query, '",',id_book, ',', ID)
  # sql <- paste("INSERT INTO tabler VALUES (",values,")" ) 
  # sql
  # sqlsave(connection, sql)
  # dbSendQuery(connection, sql)
}


# task1

uniqclients = unique(clients)
uniqclients = order(uniqclients)
length(uniqclients)

#task2

lcl = length(clients)
mclients = lcl / (31*24)
mclients

#task3
length(id_books)
id_books = sort(id_books)
id_books
#task4


# b <- readline("HW");
# b = as.numeric(b);
# a <- 5 + 2 + b;
# print(a)
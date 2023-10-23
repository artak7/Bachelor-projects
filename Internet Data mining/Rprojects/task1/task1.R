# назначим рабочий директорий
setwd("C:/Users/admin.WIN-OSD1NEIENB0/Documents/Rprojects/task1")

# прочитаем данные из файла в переменную dataFrame
dataFrame = read.table("access.log", sep = ' ')
print(dataFrame)

# число записей
nrow(dataFrame)

# дл€ работы с регул€рными выражени€ми
library(stringr)

# хост сохраним в переменную host
host = dataFrame[,1];
host
# преобразуем дату к нужному виду
data = str_replace(str_replace(str_replace(dataFrame[,4], "[:alpha:]+", "03"), "\\[", ""), ":", " ");
data
# выделим метод запроса (GET/POST)
p_g = str_extract(dataFrame[,6], "[A-Z]+")
p_g
# выделим действие пользовател€ (order/catalog/search/addbasket)
action = str_replace(str_extract(dataFrame[,6], "/[a-z]+"), "/", "");
action
# выделим номер книги, которую пользователь добавл€ет в корзину 
id_book = as.numeric(str_extract(str_extract(dataFrame[,6], "=[:digit:]+"), "[:digit:]+"));
id_book
# выделим идентификатор посетител€ (идентификатор корзины)
id_user = as.numeric(str_extract(dataFrame[,9], "[:digit:]+"));
id_user

# сохраним преобразованные пол€ как data.frame 
parse_data = data.frame("host" = host, "id_user" = id_user, "date_view" = data, "p_g" = p_g, 
                        "action" = action, "id_book" = id_book);
print(parse_data)

library(RODBC)

# установим соединение с Ѕƒ УWebDataФ
con<-odbcDriverConnect('driver={SQL Server}; server=VSHB-24-5-N5\\sqlexpress;database=WebData;trusted_connection=true')
con

# cоздадим таблицу УWebLogФ, в которой будем хранить преобразованные данные
sqlQuery(con, "create table WebLog (host nchar(20) not null, id_user int not null, date datetime not null, p_g nchar(5) not null, action nchar(20) not null, id_book int)")

# сохраним данные parse_data  в созданную таблицу УWebLogФ 
sqlSave(con, parse_data, tablename = "WebLog", rownames=TRUE, safer=FALSE, varTypes = c(host = "nchar(20)", id_user = "int", date_view = "datetime2", p_g = "nchar(5)", action = "nchar(20)", id_book = "int"));

# запрос - 1)	—колько посетителей было на сайте за мес€ц?
sqlQuery(con, "SELECT COUNT(DISTINCT wl.id_user) AS USER_NUMB FROM WebLog wl");

# запрос - 2)	—колько в среднем посетителей бывает за час?
sqlQuery(con, "SELECT AVG(COUNT_ORDER) AVG_COUNT_ORDER FROM
         (
         SELECT DATEPART(DAY, wl.date_view) DAY, DATEPART(HOUR, wl.date_view) HOUR, COUNT(DISTINCT wl.id_user) COUNT_ORDER
         FROM WebLog wl
         GROUP BY DATEPART(DAY, wl.date_view), DATEPART(HOUR, wl.date_view)
         )
         tmpUser;");

# запрос - 3)	—колько посетителей сделало заказы?
sqlQuery(con, "SELECT COUNT(DISTINCT wl.id_user) AS USER_NUMB FROM WebLog wl WHERE wl.action = 'order'");

# запрос - 4)	—колько страниц просмотрел посетитель в среднем, максимум, минимум?
sqlQuery(con, 
         "SELECT AVG(VIEW_NUMB) AVG_VIEW_COUNT, MAX(VIEW_NUMB) MAX_VIEW_COUNT, MIN(VIEW_NUMB) MIN_VIEW_COUNT
         FROM(
         SELECT wl.id_user, COUNT(wl.id_user) VIEW_NUMB 
         FROM WebLog wl
         GROUP BY wl.id_user
         ) 
         tmpTable;");

# запрос - 5)	—колько времени прошло с момента входа на сайт до оформлени€ заказа, в среднем, максимум, минимум?
sqlQuery(con, "SELECT AVG(SUB) AS AVG_TIME, MAX(SUB) AS MAX_TIME, MIN(SUB) AS MIN_TIME FROM(
         SELECT Table_1.ID_USER, DATEDIFF(MINUTE, TIME_MIN, TIME_MIN_ORDER) AS SUB
         FROM 
         (
         SELECT wl.id_user ID_USER, MIN(wl.date_view) TIME_MIN_ORDER
         FROM WebLog wl
         WHERE wl.action = 'order'
         GROUP BY wl.id_user
         )Table_1,
         (SELECT wl.id_user ID_USER, MIN(wl.date_view) TIME_MIN
         FROM WebLog wl
         GROUP BY wl.id_user
         )Table_2
         WHERE Table_1.ID_USER = Table_2.ID_USER
)table_3;");

# запрос - 6)	—колько в среднем заказов оформл€етс€ за день?
sqlQuery(con, "SELECT AVG(COUNT_ORDER) AVG_COUNT_ORDER FROM
         (
         SELECT DATEPART(DAY, wl.date_view) DAY, COUNT(wl.id_user) COUNT_ORDER
         FROM WebLog wl
         WHERE wl.action = 'order'
         GROUP BY DATEPART(DAY, wl.date_view)
         )
         tmpOrder;");

library(arules)

# Ќапишем запрос, чтобы выбрать тех пользователей, у которых в корзине больше одной книги
# сохраним результат в переменную books
books = sqlQuery (con, "SELECT wl.id_user, wl.id_book FROM
                  (SELECT wl.id_user USER_ID, COUNT(wl.id_book) COUNT_BOOK
                  FROM WebLog wl
                  WHERE wl.id_book IS NOT NULL
                  GROUP BY wl.id_user) tmpTable, WebLog wl
                  WHERE COUNT_BOOK > 1
                  AND USER_ID = wl.id_user
                  AND wl.id_book IS NOT NULL
                  ORDER BY USER_ID");

tmp = books[1,1];
check = as.character(books[1,2]);
j = 0;

basket = data.frame();

for(i in 2:nrow(books))
{
  if(books[i, 1] == tmp)
  {
    check = paste0(check, ",", as.character(books[i, 2]));
  }
  
  else
  {
    j = j + 1;
    basket[j, 1] = tmp;
    basket[j, 2] = check;
    tmp = books[i, 1];
    check = as.character(books[i, 2]);
  }
}
j = j + 1;
basket[j, 1] = tmp;
basket[j, 2] = check;

# формируем файл, где кажда€ строка содержит сведени€ о корзине, номера книг разделены зап€тыми
write.table(basket[,2], "trans.txt", quote=FALSE, row.names=FALSE, col.names=FALSE);

# прочтем данные из файла
trans = read.transactions("trans.txt", sep= ',');

# используем априорный алгоритм
rules = apriori(data=trans, parameter=list(support=0.01,confidence=0.6)) 

# распечатаем ассоциативные правила
inspect(rules)

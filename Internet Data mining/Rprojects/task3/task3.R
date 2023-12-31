# �������� ������� ����������
setwd("C:/Users/admin.WIN-OSD1NEIENB0/Documents/Rprojects/task3")

library(rvest)
library(stringr)

main_url = 'https://www.avito.ru'
nissan_url= 'https://www.avito.ru/kazan/avtomobili/nissan/almera?radius=200'
short_url = str_replace(nissan_url, 'radius=200', '');

pages <- read_html(nissan_url)
pages

# ������� ��� ��������� ������ ��������� ��������
get_last_page_numb <- function(html){
  
  pages_data <- html %>% 
    html_nodes('.pagination-page') %>% 
    html_text() 
  
  pages_data[(length(pages_data)-1)] %>% 
    unname() %>% 
    as.numeric() 
}

# ������� ����� ��������� ��������
(last_page_numb <- get_last_page_numb(pages))

# ������� ������ �������
list_of_pages = character();
list_of_pages = append(list_of_pages, nissan_url)
list_of_pages = append(list_of_pages, str_c(short_url, paste0('p=', 2:last_page_numb, '&radius=200')));
list_of_pages

year = numeric(); #��� �������
price = numeric(); #����
info = character(); #��������������
ref_info = character(); #������
is_broken = numeric(); #�������, �������� �� ���������� �����, (1 - ��������, 0 - ���)
color = character(); #���� ����������

for(i in 1:last_page_numb)
{
  page <- read_html(list_of_pages[i]);
  results <- page %>% html_nodes(".item_table-description") 
  #hide-elements
  
  # write_xml(page, "page.txt")
  
  Sys.sleep(1)
  #����������� ��� �������
  tmp <- results %>% html_nodes(".item-description-title")%>% html_text()%>%str_trim()
  year_tmp = as.numeric(str_extract(tmp, "[:digit:]+"));
  year = append(year, year_tmp); 
  
  Sys.sleep(1)
  #����������� ���� ����������
  price_tmp <- results %>% html_nodes(".about") %>% html_nodes(".price") %>% html_text()
  #_bold-price
  price_tmp = as.numeric(str_replace_all(price_tmp, "[ \n\r\t\\\u20bd]+", ""))
  price = append(price, price_tmp);
  
  Sys.sleep(1)
  #����������� ���������� � ��������������� ����������
  info_tmp <- results %>% html_nodes(".about")%>% html_nodes(".specific-params_block")%>% html_text()%>%str_trim()
  #_bold-price
  info_tmp = str_replace_all(info_tmp, "[ ]+", "");
  info = append(info, info_tmp);
  
  Sys.sleep(1)
  #����������� cc���� �� ��������� ���������� �� ����������
  ref <- results %>% html_nodes(".item-description-title-link") %>% html_attr("href")
  ref <- paste0(main_url, ref)
  ref_info = append(ref_info, ref)
}

#��� �������
year

#����
price

#���������� � ��������������� ����������
info = str_replace_all(info, "\"", "")
info

#cc���� �� ��������� ���������� �� ����������
ref_info = str_replace_all(ref_info, "\"", "")
ref_info

#��������� �������, �������� �� ���������� �����, 1 - �����, 0 - ���
is_broken = ifelse(substr(info, 0, 5) == '�����', 1, 0)
is_broken

info = str_replace(info, '�����,', '')
info

split_info <- str_split(info, ',');
split_info

mileage = numeric(); #������, ��
engine_capacity = numeric(); #����� ���������, �
power = numeric(); #�������� �.�.
transmission = character(); #����������� (��������/�������)
body_type = character(); #��� ������
drive_unit = character(); #������
engine_type = character(); #��� ���������

for(i in 1:length(split_info))
{
  str_info = split_info[[i]];
  index = 1;
  
  if(length(str_info) == 5)
  {
    mileage = append(mileage, as.numeric(str_extract(str_info[1], "[:digit:]+")));
    index = 2;
  }
  else
  {
    mileage = append(mileage, 0);
  }
  
  k = str_extract(str_info[index], "[(][:digit:]+");
  k = as.numeric(str_replace(k, '[(]', ''));
  power = append(power, k);
  y = str_extract(str_info[index], "[MA]?T");
  transmission = append(transmission, y);
  z = str_extract(str_info[index], "[:digit:]+[.][:digit:]+");
  engine_capacity = append(engine_capacity, as.numeric(z))
  body_type = append(body_type, str_info[index+1])
  drive_unit = append(drive_unit, str_info[index+2])
  engine_type = append(engine_type, str_info[index+3])
}

#������, ��
mileage
#�������� �.�.
power
#����������� (��������/�������)
transmission
#����� ���������, �
engine_capacity
#��� ������
body_type
#������
drive_unit
#��� ���������
engine_type

petgas = numeric(); #��� ��������� - ������(0) /��� (1)

for(i in 1:length(engine_type))
{
  if(engine_type[i] == '������')
  {
    petgas[i] = 0;
  }
  else
  {
    petgas[i] = 1;
  }
  
}
petgas

hs = numeric(); #��� ������ - �������(0) / �����(1)

for(i in 1:length(body_type))
{
  if(body_type[i] == '�������')
  {
    hs[i] = 0;
  }
  else
  {
    hs[i] = 1;
  }
  
}

hs

# ������� ���������� � ����� ����������
# for(i in 1:length(ref_info))
# {
#   Sys.sleep(5)
#   page <- read_html(ref_info[i])
#   Sys.sleep(5)
#   results <- page %>% html_nodes(".item-params-list-item") %>% html_text() %>% str_trim()
#   Sys.sleep(5)
#   for(j in 1:length(results))
#   {
#     if(substr(results[j], 0, 4) == '����')
#     {
#       col <- substr(results[j], 6, nchar(results[j])) %>% str_trim()
#       color = append(color, col)
#     }
#   }
# }

#����
# color
# 
# col = numeric(); #���� ���������� ����������, ������ ��� ����� (0) / 
# #���� ���������� ����� ������  (1)
# 
# for(i in 1:length(color))
# {
#   if(color[i] == '������' || color[i] == '�����' || color[i] == '����������')
#   {
#     print(color[i])
#     col[i] = 0;
#   }
#   else
#   {
#     col[i] = 1;
#   }
# }

# col

mileage = mileage / 1000;
price = price / 1000;

# �������� ��������������� ���� ��� data.frame 
parse_data = data.frame("year" = year, "is_broken" = is_broken, "mileage" = mileage, "power" = power, 
                        "engine_capacity" = engine_capacity, "hs" = hs, "petgas" = petgas, 
                         "price" = price); # "col" = col,
parse_data

# ���������� � ������
summary(parse_data)

# �������� �������� ������������ ���������� ����� ������������
r = cor(parse_data)
r

# �������� ������������� ������
mymodel = lm(price ~ year + is_broken + mileage + power + engine_capacity + hs + petgas, data = parse_data) #  + col
mymodel
summary(mymodel)

# �������� ������������� ������
mymodel = lm(price ~ year + is_broken + mileage, data = parse_data)
mymodel
summary(mymodel)

# ������ ��� ��������
predict_data = parse_data
predict_data = predict_data[-9]
predict_data

# ������������� ���� ����������� �� ����� ������
predictPrice = predict(mymodel, predict_data)
predictPrice = as.data.frame(predictPrice)
predictPrice

# �������� ���� �����������
truePrice = parse_data$price
truePrice

# ������ ��������
error = abs(truePrice - predictPrice)*100/truePrice;
error= round(error, 3)
colnames(error) = "error"
max(error)

# ������� ���������� ��������
tableResults = data.frame(predict_data, truePrice, predictPrice, error)
tableResults


for(i in 1:nrow(error))
{
  if(error[i,] > 50)
    print(tableResults[i,]);
}

index = numeric();

for(i in 1:nrow(error))
{
  if(error[i,] > 100)
    index = append(index, i)
}

index

#��������� �� �� �������
new_data = parse_data[-c(index),]
new_data

# �������� ������������� ������
mymodel = lm(price ~ year + is_broken + mileage + power + engine_capacity + hs + petgas, data = new_data) #  + col
mymodel
summary(mymodel)

# ������ ��� ��������
predict_data = new_data
predict_data = predict_data[-9]
predict_data

# ������������� ���� ����������� �� ����� ������
predictPrice = predict(mymodel, predict_data)
predictPrice = as.data.frame(predictPrice)
predictPrice

# �������� ���� �����������
truePrice = new_data$price
truePrice

# ������ ��������
error = abs(truePrice - predictPrice)*100/truePrice;
error= round(error, 3)
colnames(error) = "error"
max(error)

# ������� ���������� ��������
tableResults = data.frame(predict_data, truePrice, predictPrice, error)
tableResults

for(i in 1:nrow(error))
{
  if(error[i,] > 50)
    print(tableResults[i,]);
}


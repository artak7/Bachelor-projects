# назначим рабочий директорий
setwd("C:/Users/admin.WIN-OSD1NEIENB0/Documents/Rprojects")

library(rvest)
library(stringr)

main_url = 'https://www.avito.ru'
vw_url= 'https://www.avito.ru/kazan/avtomobili/volkswagen/tiguan?radius=200'
short_url = str_replace(vw_url, 'radius=200', '');

pages <- read_html(vw_url)
pages

write_xml(pages, "pages.txt")

# функция для получения номера последней страницы
get_last_page_numb <- function(html){
  
  pages_data <- html %>% 
    html_nodes('.pagination-page') %>% 
    html_text() 
  
  pages_data[(length(pages_data)-1)] %>% 
    unname() %>% 
    as.numeric() 
}

# получим номер последней страницы
(last_page_numb <- get_last_page_numb(pages))

# получим список страниц
list_of_pages = character();
list_of_pages = append(list_of_pages, vw_url)
list_of_pages = append(list_of_pages, str_c(short_url, paste0('p=', 2:last_page_numb, '&radius=200')));
list_of_pages

year = numeric(); #год выпуска
price = numeric(); #цена
info = character(); #характеристики
ref_info = character(); #ссылки
is_broken = numeric(); #признак, является ли автомобиль битым, (1 - является, 0 - нет)
# color = character(); #цвет автомобиля

for(i in 1:last_page_numb)
{
  page <- read_html(list_of_pages[i]);
  results <- page %>% html_nodes(".item_table-description") 
  #hide-elements
  
  # write_xml(page, "page.txt")
  
  Sys.sleep(1)
  #достаем год выпуска
  tmp <- results %>% html_nodes(".item-description-title")%>% html_text()%>%str_trim()
  year_tmp = as.numeric(str_extract(tmp, "[:digit:]+"));
  year = append(year, year_tmp); 
  
  Sys.sleep(1)
  #вытаскиваем цену автомобиля
  price_tmp <- results %>% html_nodes(".about") %>% html_nodes(".price") %>% html_text()
  #_bold-price
  price_tmp = as.numeric(str_replace_all(price_tmp, "[ \n\r\t\\\u20bd]+", ""))
  price = append(price, price_tmp);
  
  Sys.sleep(1)
  #вытаскиваем информацию о характеристиках автомобиля
  info_tmp <- results %>% html_nodes(".about")%>% html_nodes(".specific-params_block")%>% html_text()%>%str_trim()
  #_bold-price
  info_tmp = str_replace_all(info_tmp, "[ ]+", "");
  info = append(info, info_tmp);
  
  Sys.sleep(1)
  #вытаскиваем ccылки на подробную информацию об автомобиле
  ref <- results %>% html_nodes(".item-description-title-link") %>% html_attr("href")
  ref <- paste0(main_url, ref)
  ref_info = append(ref_info, ref)
}

write_xml(page, "page.txt")

#год выпуска
year

#цена
price

#информация о характеристиках автомобиля
info = str_replace_all(info, "\"", "")
info

#ccылки на подробную информацию об автомобиле
ref_info = str_replace_all(ref_info, "\"", "")
ref_info

#заполняем признак, является ли автомобиль битым, 1 - битый, 0 - нет
is_broken = ifelse(substr(info, 0, 5) == 'Битый', 1, 0)
is_broken

info = str_replace(info, 'Битый,', '')
info

split_info <- str_split(info, ',');
split_info

mileage = numeric(); #пробег, км
engine_capacity = numeric(); #объем двигателя, л
power = numeric(); #мощность л.с.
transmission = character(); #трансмиссия (механика/автомат)
body_type = character(); #тип кузова
drive_unit = character(); #привод
engine_type = character(); #тип двигателя

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

#пробег, км
mileage
#мощность л.с.
power
#трансмиссия (механика/автомат)
transmission
#объем двигателя, л
engine_capacity
#тип кузова
body_type
#привод
drive_unit
#тип двигателя
engine_type

petdis = numeric(); #тип двигателя - бензин(0) / дизель (1)

for(i in 1:length(engine_type))
{
  if(engine_type[i] == 'бензин')
  {
    petdis[i] = 0;
  }
  else
  {
    petdis[i] = 1;
  }
  
}
petdis

bt = numeric(); #тип кузова - хетчбэк, внедорожник(0) / универсал, минивэн(1)

for(i in 1:length(body_type))
{
  if(body_type[i] == 'хетчбэк' || body_type[i] == 'внедорожник')
  {
    bt[i] = 0;
  }
  else 
  {
    bt[i] = 1;
  }
}

bt

mileage = mileage / 1000;
price = price / 1000;

# сохраним преобразованные поля как data.frame 
parse_data = data.frame("year" = year, "is_broken" = is_broken, "mileage" = mileage, "power" = power, 
                        "engine_capacity" = engine_capacity, "bt" = bt, "petdis" = petdis, 
                         "price" = price);
parse_data

# информация о данных
summary(parse_data)

# вычислим попарные коэффициенты корреляции между предикторами
r = cor(parse_data)
r

# построим регрессионную модель
mymodel = lm(price ~ year + is_broken + mileage + power + engine_capacity + bt + petdis, data = parse_data)
mymodel
summary(mymodel)

# построим регрессионную модель
mymodel = lm(price ~ year + is_broken + mileage, data = parse_data)
mymodel
summary(mymodel)

# данные для прогноза
predict_data = parse_data
predict_data = predict_data[-8]
predict_data

# спрогнозируем цену автомобилей по нашей модели
predictPrice = predict(mymodel, predict_data)
predictPrice = as.data.frame(predictPrice)
predictPrice

# истинная цена автомобилей
truePrice = parse_data$price
truePrice

# ошибка прогноза
error = abs(truePrice - predictPrice)*100/truePrice;
error= round(error, 3)
colnames(error) = "error"
max(error)

# таблица результата прогноза
tableResults = data.frame(predict_data, truePrice, predictPrice, error)
tableResults


for(i in 1:nrow(error))
{
  if(error[i,] > 50)
    print(tableResults[i,]);
}
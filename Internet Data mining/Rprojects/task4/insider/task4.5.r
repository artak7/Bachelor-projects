# назначим рабочий директорий
setwd("C:/Users/admin.WIN-OSD1NEIENB0/Documents/Rprojects/task4/insider")

library(RCurl) # основной пакет для веб-скрепинга
library(XML) # пакет для  работы с XML, HTML, Xpath
library(stringr) # пакет для работы с регулярными выражениями

# новости, сми
main = "https://theins.ru/"

# создаем объект для работы по протоколу SSL
signatures = system.file("CurlSSL", cainfo = "cacert.pem", package = "RCurl")
url = getURL(main, cainfo = signatures, encoding="UTF-8")

write(url, 'theinsurl.txt')

# создаем html-объект
webpage <- htmlParse(url, encoding="UTF-8")
webpage

# вытащим информацию о тематике новостей
category <- xpathSApply(webpage, "//div[@class='container top']//ul[@class='menu']/li/a", xmlGetAttr, "href");
category = paste0(category, '/')
#category = category[-]
category

#main1 = substr(main, 1, nchar(main)-1)

for(i in 1:length(category))
{
  #category[i] = paste0(main1, category[i])
  categ_url=getURL(category[i], cainfo = signatures, encoding="UTF-8")
  # загружаем все страницы на диск:
  write(categ_url, paste0('Categ/categ', i, '.txt'))
  catpage <- htmlParse(categ_url, encoding="UTF-8")
  #catpage
  
  # получаем номер последней страницы:
  last_page_numb <- xpathSApply(catpage, "//div[@class='pagination']//a", xmlValue); # GetAttr , "href"
  last_page_numb = as.numeric(str_extract(last_page_numb, "[:digit:]+"));
  last_page_numb = na.omit(last_page_numb)
  last_page_numb = max(last_page_numb)
  last_page_numb = max(last_page_numb, 30)
  last_page_numb
  
  # получим список страниц;
  list_of_pages = character();
  list_of_pages = append(list_of_pages, category[i]);
  if(length(last_page_numb) != 0)
    list_of_pages = append(list_of_pages, str_c(category[i], paste0('page/', 2:last_page_numb, '/')));
  list_of_pages
  
  # загружаем все страницы на диск:
  for(j in 1:length(list_of_pages)){
    tmp <- getURL(list_of_pages[j], cainfo = signatures, encoding="UTF-8")
    write(tmp, str_c(paste0("Categ/Categ", i, "/"), j, ".html"))
    Sys.sleep(1);
  }
  
  #ссылки на новости;
  ref = character();
  
  
  if(length(last_page_numb) == 0)
     last_page_numb = 1;
  
  # проходим по всем загруженным страницам
  # получаем ссылки на все новости текущей тематики и сохраняем их в переменную ref
  for(j in 1:last_page_numb)
  {
    # убираем переносы строк:
    tmp <- str_c(categ_url, collapse = "")
    # строим HTML-объект:
    tmp <- htmlParse(tmp, encoding="UTF-8")
    # получаем ссылки на все новости текущей тематики
    news_page <- xpathSApply(tmp, "//div[@class='item-image']/a", xmlGetAttr, "href")
    news_page
    ref = append(ref, news_page)
  }
  
  # записываем на диск тексты всех новостей текущей тематики
  
  for(j in 1:length(ref))
  {
    print(j)
    
    news1_url= getURL(ref[j], cainfo = signatures, encoding="UTF-8");
    write(news1_url, paste0('News/news', i, '_', j, '.txt'))
    
    news1_page <- htmlParse(news1_url, encoding="UTF-8")
    news1_text <- xpathSApply(news1_page, "//div[@class='post-entry']/div/p", xmlValue)
    
    # if(length(news1_text) != 0)
    # {
    #   news1_text <- xpathSApply(news1_page, "//div[@class='post-entry']//p[following-sibling::style]", xmlValue)
    # }
    # else
    # {
    #   news1_text <- xpathSApply(news1_page, "//div[@class='post-entry']", xmlValue);
    # }
    
    tmp1 = character()
    for (i in 1:length(news1_text))
      tmp1 = paste0(tmp1, news1_text[[i]])
    
    news1_text = tmp1
    
    # удаляем из текста знаки переноса строки, табуляции, лишние пробелы:
    news1_text = str_replace_all(news1_text, "\n", " ");
    news1_text = str_replace_all(news1_text, "\t", " ");
    news1_text = str_replace_all(news1_text, "[ ]{2,}", "");
    
    # все строки новости записываем в одну переменную full_text:
    full_text = "";
    for(k in 1:length(news1_text))
    {
      full_text = str_c(full_text, paste0(" ", news1_text[k]));
    }
    
    # записываем текст новости на диск:
    write(full_text, paste0("Newstext/newstext", i, ".txt"), append = TRUE)
  }
  
}

# пакет Text mining
library(tm)

# получим названия тематик новостей
#name_category <- xpathSApply(webpage, "//div[@class='menu-menyu-1-container']/ul[@class='menu']/li[@class='menu-item menu-item-has-children']/ul[@class='sub-menu']/li/a", xmlValue);
name_category = category

# прочитаем новости с диска в переменную news,
# а категории, которым принадлежат эти новости, в переменную categ
news = character(0);
categ = character(0);

# для классификации выберем новости о политике, спорте и культуре (обществе 9, науке 13)

for(i in c(2, 4, 6, 9)) # политика, коррупция, общество, экономика (можно добавить историю)
{
  # читаем новости текущей категории
  news_tmp <- readLines(paste0("Newstext/newstext", i, ".txt"))
  
  categ_tmp = rep(name_category[i], length(news_tmp))
  
  news = append(news, news_tmp)
  categ = append(categ, categ_tmp)
}

# сохраним информацию о новостях в data.frame
news_frame = data.frame("news" = news, "category" = categ)

# общее число новостей
nrow(news_frame)

# перемешаем исходные данные
set.seed(0)
frame = news_frame[order(runif(nrow(news_frame))),]

# создаем пустой объект корпус
news=list(); 
news_corpus = VCorpus(VectorSource(news))

# добавляем в корпус информацию о новостях всех тематик:
for(i in 1:nrow(frame))
{
  # добавляем в корпус информацию 
  tmp_corpus <- VCorpus(VectorSource(frame[i,]$news))
  news_corpus <- c(news_corpus, tmp_corpus)
  
  # добавляем метаинформацию
  meta(news_corpus[[i]], "category") <- frame[i,]$category
  meta(news_corpus[[i]], "language") <- "ru"
}

news_corpus
meta(news_corpus[[1]])

# список тематик новостей:
meta_data<- data.frame()
for (i in 1:NROW(news_corpus))
{
  meta_data [i, "category"] <- meta(news_corpus[[i]], "category") 
  meta_data [i, "num"] <- i 
}

table(as.character(meta_data[, "category"]))

news_corpus[[11]]$content

# удалим числа 
news_corpus <- tm_map(news_corpus, content_transformer(removeNumbers))

news_corpus[[11]]$content

# заменим на пробелы знаки пунктуации 
news_corpus <- tm_map(news_corpus,   
                      content_transformer(str_replace_all), 
                      pattern = "[[:punct:]]", replacement = " ")
news_corpus[[11]]$content

# преобразуем к нижнему регистру
news_corpus <- tm_map(news_corpus, content_transformer(tolower))

news_corpus[[11]]$content

# удаляем стоп-слова  
news_corpus <- tm_map(news_corpus, content_transformer(removeWords), words =  stopwords("ru"))

news_corpus[[11]]$content

# проводим стемминг
for(i in 1:NROW(news_corpus))
  news_corpus[[i]]$content <- stemDocument(news_corpus[[i]]$content, language = "russian")

news_corpus <- tm_map(news_corpus, content_transformer(removeWords), words =  'котор')

news_corpus[[11]]$content

# создадим облако слов
library(wordcloud)
wordcloud(news_corpus, random.order=F, max.words=40)

# создаем матрицу терминов-документов
tdm <- TermDocumentMatrix(news_corpus)
tdm

# создаем матрицу документов-терминов
dtm <- DocumentTermMatrix(news_corpus)
dtm

dtm <- removeSparseTerms(dtm, 0.97)
dtm

# список терминов
dtm$dimnames$Terms

# дополнительный пакет для работы с текстами
library(RTextTools)

# массив меток – тематики новостей
org_labels<-meta_data[, "category"]

count_data <- length(org_labels)
count_data

# разделим исходные данные на тестовую и обучающую выборки
# число новостей обучающей выборки (70% от исходных данных)
count_train = round(count_data*0.7)
count_train

# для применения методов классификации создаем контейнер
container <- create_container(
  dtm,
  labels = org_labels, 
  trainSize = 1:count_train,
  testSize = (count_train+1):count_data,
  virgin = FALSE
)

container

# проверим репрезентативность выборки
round(prop.table(table(frame[2]))*100, digits = 1)

train_data = frame[1:count_train,]

round(prop.table(table(train_data[2]))*100, digits = 1)


# обучение моделей
# Support vector machine
svm_model <- train_model(container, "SVM")
# Random forest
tree_model <- train_model(container, "TREE")
# Maximal entropy
maxent_model <- train_model(container, "MAXENT")

# запускаем классификацию 
svm_out <- classify_model(container, svm_model)
tree_out <- classify_model(container, tree_model)
maxent_out <- classify_model(container, maxent_model)

# создаем общую матрицу меток
labels_out <- data.frame(
  correct_label = org_labels[(count_train+1):count_data],
  svm = as.character(svm_out[,1]),
  tree = as.character(tree_out[,1]),
  maxent = as.character(maxent_out[,1]),
  stringsAsFactors = F)


# SVM performance
table(labels_out[,1] == labels_out[,2])

# Random forest performance
table(labels_out[,1] == labels_out[,3])

# Maximum entropy performance
table(labels_out[,1] == labels_out[,4])
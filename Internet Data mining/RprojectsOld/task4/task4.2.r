# �������� ������� ����������
setwd("C:/Users/admin.WIN-OSD1NEIENB0/Documents/Rprojects")

library(RCurl) # �������� ����� ��� ���-���������
library(XML) # ����� ���  ������ � XML, HTML, Xpath
library(stringr) # ����� ��� ������ � ����������� �����������

# �������, ���
main = "https://tass.ru/"

# ������� ������ ��� ������ �� ��������� SSL
signatures = system.file("CurlSSL", cainfo = "cacert.pem", package = "RCurl")
url = getURL(main, cainfo = signatures, encoding="UTF-8")

write(url, 'tassurl.txt')

# ������� html-������
webpage <- htmlParse(url, encoding="UTF-8")
webpage

# ������� ���������� � �������� ��������
category <- xpathSApply(webpage, "//div[@class='menu-sections-list__title-wrapper']/a[@class='menu-sections-list__title']", xmlGetAttr, "href");
category = category[-(15:19)]
category

main1 = substr(main, 1, nchar(main)-1)

for(i in 1:length(category))
{
  category[i] = paste0(main1, category[i])
  categ_url=getURL(category[i], cainfo = signatures, encoding="UTF-8")
  # ��������� ��� �������� �� ����:
  write(categ_url, paste0('categ', i, '.txt'))
  #Sys.sleep(1);
  catpage <- htmlParse(categ_url, encoding="UTF-8")
  #catpage
  
  # �������� ����� ��������� ��������:
  #last_page_numb <- xpathSApply(catpage, "//a[@class='last']", xmlGetAttr, "href");
  #last_page_numb = as.numeric(str_extract(last_page_numb, "[:digit:]+"));
  #last_page_numb
  
  # ������� ������ �������;
  #list_of_pages = character();
  #list_of_pages = append(list_of_pages, category[i]);
  #if(length(last_page_numb) != 0)
  #  list_of_pages = append(list_of_pages, str_c(category[i], paste0('page/', 2:last_page_numb, '/')));
  #list_of_pages
  
  # ��������� ��� �������� �� ����:
  #for(j in 1:length(list_of_pages)){
  #  tmp <- getURL(list_of_pages[j], cainfo = signatures, encoding="UTF-8")
  #  write(tmp, str_c(paste0("Category", i, "/"), j, ".html"))
  #}
  
  # ��������� ��� �������� �� ����:
  #tmp <- getURL(category[i], cainfo = signatures, encoding="UTF-8") 
  #write(tmp, paste0("Category", i, ".html"))
  
  
  #������ �� �������;
  ref = character();
  
  #if(length(last_page_numb) == 0)
  #  last_page_numb = 1;
  
  # �������� �� ���� ����������� ���������
  # �������� ������ �� ��� ������� ������� �������� � ��������� �� � ���������� ref
  
  #for(j in 1:last_page_numb)
  #{
    # ������ ������� ��������
    # tmp <- readLines(paste0("Category", i, ".html"))
    # ������� �������� �����:
  tmp <- str_c(categ_url, collapse = "")
    # ������ HTML-������:
  tmp <- htmlParse(tmp, encoding="UTF-8")
    # �������� ������ �� ��� ������� ������� ��������
  news_page <- xpathSApply(tmp, "//a[@class='news-preview news-preview_default']", xmlGetAttr, "href")
  news_page
  ref = append(ref, paste0(main1,news_page))
  #}
  
  # ���������� �� ���� ������ ���� �������� ������� ��������
  
  for(j in 1:length(ref))
  {
    print(j)
    
    news1_url= getURL(ref[j], cainfo = signatures, encoding="UTF-8");
    #write(news1_url, 'news1.txt')
    
    news1_page <- htmlParse(news1_url, encoding="UTF-8")
    news1_text <- xpathSApply(news1_page, "//div[@class='text-block']/p", xmlValue)
    
    #if(length(news1_text) != 0){
    #news1_text <- xpathSApply(news1_page, "//div[@class='text-block']//p[following-sibling::style]", xmlValue)
    #}else
    #{
    #  news1_text <- xpathSApply(news1_page, "//div[@class='text-block']", xmlValue);
    #}
    
    # ������� �� ������ ����� �������� ������, ���������, ������ �������:
    news1_text = str_replace_all(news1_text, "\n", " ");
    news1_text = str_replace_all(news1_text, "\t", " ");
    news1_text = str_replace_all(news1_text, "[ ]{2,}", "");
    
    # ��� ������ ������� ���������� � ���� ���������� full_text:
    full_text = "";
    for(k in 1:length(news1_text))
    {
      full_text = str_c(full_text, paste0(" ", news1_text[k]));
    }
    
    # ���������� ����� ������� �� ����:
    write(full_text, paste0("newstext", i, ".txt"), append = TRUE)
  }
  
}

# ����� Text mining
library(tm)

# ������� �������� ������� ��������
#name_category <- xpathSApply(webpage, "//div[@class='menu-menyu-1-container']/ul[@class='menu']/li[@class='menu-item menu-item-has-children']/ul[@class='sub-menu']/li/a", xmlValue);
#name_category=name_category[-8]
#name_category=name_category[-7]
name_category = category

# ��������� ������� � ����� � ���������� news,
# � ���������, ������� ����������� ��� �������, � ���������� categ
news = character(0);
categ = character(0);

# ��� ������������� ������� ������� � ��������, ������ � �������� (�������� 9, ����� 13)

for(i in c(2, 11, 12))
{
  # ������ ������� ������� ���������
  news_tmp <- readLines(paste0("newstext", i, ".txt"))
  
  categ_tmp = rep(name_category[i], length(news_tmp))
  
  news = append(news, news_tmp)
  categ = append(categ, categ_tmp)
}

# �������� ���������� � �������� � data.frame
news_frame = data.frame("news" = news, "category" = categ)

# ����� ����� ��������
nrow(news_frame)

# ���������� �������� ������
set.seed(0)
frame = news_frame[order(runif(nrow(news_frame))),]

# ������� ������ ������ ������
news=list(); 
news_corpus = VCorpus(VectorSource(news))

# ��������� � ������ ���������� � �������� ���� �������:
for(i in 1:nrow(frame))
{
  # ��������� � ������ ���������� 
  tmp_corpus <- VCorpus(VectorSource(frame[i,]$news))
  news_corpus <- c(news_corpus, tmp_corpus)
  
  # ��������� ��������������
  meta(news_corpus[[i]], "category") <- frame[i,]$category
  meta(news_corpus[[i]], "language") <- "ru"
}

news_corpus
meta(news_corpus[[1]])

# ������ ������� ��������:
meta_data<- data.frame()
for (i in 1:NROW(news_corpus))
{
  meta_data [i, "category"] <- meta(news_corpus[[i]], "category") 
  meta_data [i, "num"] <- i 
}

table(as.character(meta_data[, "category"]))

news_corpus[[11]]$content

# ������ ����� 
news_corpus <- tm_map(news_corpus, content_transformer(removeNumbers))

news_corpus[[11]]$content

# ������� �� ������� ����� ���������� 
news_corpus <- tm_map(news_corpus,   
                      content_transformer(str_replace_all), 
                      pattern = "[[:punct:]]", replacement = " ")
news_corpus[[11]]$content

# ����������� � ������� ��������
news_corpus <- tm_map(news_corpus, content_transformer(tolower))

news_corpus[[11]]$content

# ������� ����-�����  
news_corpus <- tm_map(news_corpus, content_transformer(removeWords), words =  stopwords("ru"))

news_corpus[[11]]$content

# �������� ��������
for(i in 1:NROW(news_corpus))
  news_corpus[[i]]$content <- stemDocument(news_corpus[[i]]$content, language = "russian")

news_corpus <- tm_map(news_corpus, content_transformer(removeWords), words =  '�����')

news_corpus[[11]]$content

# �������� ������ ����
library(wordcloud)
wordcloud(news_corpus, random.order=F, max.words=40)

# ������� ������� ��������-����������
tdm <- TermDocumentMatrix(news_corpus)
tdm

# ������� ������� ����������-��������
dtm <- DocumentTermMatrix(news_corpus)
dtm

dtm <- removeSparseTerms(dtm, 0.97)
dtm

# ������ ��������
dtm$dimnames$Terms

# �������������� ����� ��� ������ � ��������
library(RTextTools)

# ������ ����� � �������� �������������
org_labels<-meta_data[, "category"]

count_data <- length(org_labels)
count_data

# �������� �������� ������ �� �������� � ��������� �������
# ����� ������ ��������� ������� (70% �� �������� ������)
count_train = round(count_data*0.7)
count_train

# ��� ���������� ������� ������������� ������� ���������
container <- create_container(
  dtm,
  labels = org_labels, 
  trainSize = 1:count_train,
  testSize = (count_train+1):count_data,
  virgin = FALSE
)

container

# �������� ������������������ �������
round(prop.table(table(frame[2]))*100, digits = 1)

train_data = frame[1:count_train,]

round(prop.table(table(train_data[2]))*100, digits = 1)


# �������� �������
# Support vector machine
svm_model <- train_model(container, "SVM")
# Random forest
tree_model <- train_model(container, "TREE")
# Maximal entropy
maxent_model <- train_model(container, "MAXENT")

# ��������� ������������� 
svm_out <- classify_model(container, svm_model)
tree_out <- classify_model(container, tree_model)
maxent_out <- classify_model(container, maxent_model)

# ������� ����� ������� �����
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


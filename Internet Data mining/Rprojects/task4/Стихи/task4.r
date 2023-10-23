# �������� ������� ����������
setwd("C:/Users/admin.WIN-OSD1NEIENB0/Documents/Rprojects")

library(RCurl) # �������� ����� ��� ���-���������
library(XML) # ����� ���  ������ � XML, HTML, Xpath
library(stringr) # ����� ��� ������ � ����������� �����������

# (���������) ��������
main = "https://rustih.ru" # "https://rt.rbc.ru/"

# ������� ������ ��� ������ �� ��������� SSL
signatures = system.file("CurlSSL", cainfo = "cacert.pem", package = "RCurl")
url = getURL(main, cainfo = signatures, encoding="UTF-8")

write(url, 'stihurl.txt')

  # ������� html-������
webpage <- htmlParse(url, encoding="UTF-8")
webpage

# ������� ���������� � �������� �������������
category <- xpathSApply(webpage, "//div[@class='menu-menyu-1-container']/ul[@class='menu']/li[@class='menu-item menu-item-has-children']/ul[@class='sub-menu']/li/a", xmlGetAttr, "href");
category = category[-(1:4)]
category = category[-9]; # -8
category = category[-2]; # -7
category

for(i in 1:length(category))
{
  categ_url=getURL(category[i], cainfo = signatures, encoding="UTF-8")
  catpage <- htmlParse(categ_url, encoding="UTF-8")
  catpage
  
  # �������� ����� ��������� ��������:
  last_page_numb <- xpathSApply(catpage, "//a[@class='last']", xmlGetAttr, "href"); # not work
  last_page_numb = as.numeric(str_extract(last_page_numb, "[:digit:]+"));
  last_page_numb
  
  # ������� ������ �������;
  list_of_pages = character();
  list_of_pages = append(list_of_pages, category[i]);
  if(length(last_page_numb) != 0)
    list_of_pages = append(list_of_pages, str_c(category[i], paste0('page/', 2:last_page_numb, '/')));
  list_of_pages
  
  # ��������� ��� �������� �� ����:
  for(j in 1:length(list_of_pages)){
    tmp <- getURL(list_of_pages[j], cainfo = signatures, encoding="UTF-8")
    write(tmp, str_c(paste0("Category", i, "/"), j, ".html"))
    Sys.sleep(1);
  }
  
  #������ �� �����;
  ref = character();
  
  if(length(last_page_numb) == 0)
    last_page_numb = 1;
  
  # �������� �� ���� ����������� ���������
  # �������� ������ �� ��� ����� ������� �������� � ��������� �� � ���������� ref
  for(j in 1:last_page_numb)
  {
    # ������ ������� ��������
    tmp <- readLines(str_c(paste0("Category", i, "/"), j, ".html"))
    # ������� �������� �����:
    tmp <- str_c(tmp, collapse = "")
    # ������ HTML-������:
    tmp <- htmlParse(tmp, encoding="UTF-8")
    # �������� ������ �� ��� ����� ������� ��������
    poem_page <- xpathSApply(tmp, "//article[@class='blog-item']//a[@href]", xmlGetAttr, "href")
    ref = append(ref, poem_page)
  }
  
  # ���������� �� ���� ������ ���� ������������� ������� ��������
  for(j in 1:length(ref))
  {
    print(j)
    
    poem_url= getURL(ref[j], cainfo = signatures, encoding="UTF-8");
    
    poem_page <- htmlParse(poem_url, encoding="UTF-8")
    poem_text <- xpathSApply(poem_page, "//div[@class='poem-text']//h2", xmlValue)
    
    if(length(poem_text) != 0){
      poem_text <- xpathSApply(poem_page, "//div[@class='poem-text']//p[following-sibling::style]", xmlValue)
    }else
    {
      poem_text <- xpathSApply(poem_page, "//div[@class='poem-text']", xmlValue);
    }
    
    # ������� �� ������ ����� �������� ������, ���������, ������ �������:
    poem_text = str_replace_all(poem_text, "\n", " ");
    poem_text = str_replace_all(poem_text, "\t", " ");
    poem_text = str_replace_all(poem_text, "[ ]{2,}", "");
    
    # ��� ������ ������������� ���������� � ���� ���������� full_text:
    full_text = "";
    for(k in 1:length(poem_text))
    {
      full_text = str_c(full_text, paste0(" ", poem_text[k]));
    }
    
    # ���������� ����� ����� �� ����:
    write(full_text, paste0("Category", i, "/poems.txt"), append = TRUE)
  }
  
}

# ����� Text mining
library(tm)

# ������� �������� �������� ������
name_category <- xpathSApply(webpage, "//div[@class='menu-menyu-1-container']/ul[@class='menu']/li[@class='menu-item menu-item-has-children']/ul[@class='sub-menu']/li/a", xmlValue);
name_category=name_category[-8]
name_category=name_category[-7]
name_category

# ��������� ������������� � ����� � ���������� poems,
# � ���������, ������� ����������� ��� �����, � ���������� categ
poems = character(0);
categ = character(0);

# ��� ������������� ������� ������������� � �����, � ������� � � �����
for(i in c(1, 3, 5))
{
  # ������ ������������� ������� ���������
  poems_tmp <- readLines(paste0("Category", i, "/poems.txt"))
  
  categ_tmp = rep(name_category[i], length(poems_tmp))
  
  poems = append(poems, poems_tmp)
  categ = append(categ, categ_tmp)
}

# �������� ���������� � ������ � data.frame
poems_frame = data.frame("poem" = poems, "category" = categ)

# ����� ����� �������������
nrow(poems_frame)

# ���������� �������� ������
set.seed(0)
frame = poems_frame[order(runif(nrow(poems_frame))),]

# ������� ������ ������ ������
poems=list(); 
poem_corpus = VCorpus(VectorSource(poems))

# ��������� � ������ ���������� � ������ ���� �������:
for(i in 1:nrow(frame))
{
  # ��������� � ������ ���������� 
  tmp_corpus <- VCorpus(VectorSource(frame[i,]$poem))
  poem_corpus <- c(poem_corpus, tmp_corpus)
  
  # ��������� ��������������
  meta(poem_corpus[[i]], "category") <- frame[i,]$category
  meta(poem_corpus[[i]], "language") <- "ru"
}

poem_corpus
meta(poem_corpus[[1]])

# ������ ������� �������������:
meta_data<- data.frame()
for (i in 1:NROW(poem_corpus))
{
  meta_data [i, "category"] <- meta(poem_corpus[[i]], "category") 
  meta_data [i, "num"] <- i 
}

table(as.character(meta_data[, "category"]))

poem_corpus[[16]]$content

# ������ ����� 
poem_corpus <- tm_map(poem_corpus, content_transformer(removeNumbers))

poem_corpus[[16]]$content

# ������� �� ������� ����� ���������� 
poem_corpus <- tm_map(poem_corpus,   
                      content_transformer(str_replace_all), 
                      pattern = "[[:punct:]]", replacement = " ")
poem_corpus[[16]]$content

# ����������� � ������� ��������
poem_corpus <- tm_map(poem_corpus, content_transformer(tolower))

poem_corpus[[16]]$content

# ������� ����-�����  
poem_corpus <- tm_map(poem_corpus, content_transformer(removeWords), words =  stopwords("ru"))

poem_corpus[[16]]$content

# �������� ��������
for(i in 1:NROW(poem_corpus))
  poem_corpus[[i]]$content <- stemDocument(poem_corpus[[i]]$content, language = "russian")

poem_corpus <- tm_map(poem_corpus, content_transformer(removeWords), words =  '�����')

poem_corpus[[16]]$content

# �������� ������ ����
library(wordcloud)
wordcloud(poem_corpus, random.order=F, max.words=40)

# ������� ������� ��������-����������
tdm <- TermDocumentMatrix(poem_corpus)
tdm

# ������� ������� ����������-��������
dtm <- DocumentTermMatrix(poem_corpus)
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


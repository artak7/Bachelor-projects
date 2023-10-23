# Назначим рабочий директорий
setwd("C://Users/pc/Documents/Магистратура/2 семестр/R/task9 KMid")
getwd()

#очищаем рабочее пространство
rm (list=ls())

# Прочтём данные о флагах
flagdata <- read.csv("flagdata.txt", sep=",", head=FALSE)

# Удалим столбец с классами
# flagdata = flagdata[-7]
# flagdata

# Формула нормализации данных
normalize <- function(x) {return ((x - min(x)) / (max(x) - min(x)))}

# Нормализуем данные и исключим нечисловые данные
flag <- as.data.frame(lapply(flagdata[c(2:6, 8:17, 19:28)], normalize))


m = dim(flag)[2] # количество факторов # 25
n = dim(flag)[1] # объём выборки # 194

# Добавим названия столбцов
# colnames(flag)<- c('V2','V3','V4','V5','V6','V8','V9','V10','V11','V12','V13','V14','V15','V16','V17','V19','V20','V21','V22','V23','V24','V25','V26','V27','V28','Type')

flag 

# Вызовем метод к средних
flag_clusters <- kmeans(flag, 2)
flag_clusters

flag_clusters <- kmeans(flag, 3)
flag_clusters

flag_clusters <- kmeans(flag, 4)
flag_clusters


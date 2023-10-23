setwd("C://Users/pc/Documents/Магистратура/2 семестр/R/task4 НБК")
getwd()

#очищаем рабочее пространство
rm (list=ls())

# Прочитаем файл с данными в переменную flagdata
flagdata <- read.csv("flagData.txt", head = FALSE, sep=",") #, sep="\t"
# str(flagdata) # структура данных
flagdata

# Формула нормализации данных
normalize <- function(x) {return ((x - min(x)) / (max(x) - min(x)))}

# Нормализуем данные 
# исключим не численные факторы и переменную отклика
flag <- as.data.frame(lapply(flagdata[c(2:6, 8:17, 19:28)], normalize))

dims = dim(flag) # n * m
n = dims[1] # объём выборки # 194
m = dims[2] # количество факторов # 25

# добавим перменную отклика в конец для удобства
flag[m+1] = flagdata[7]
flag

# Прочитали 194 записей, в каждой - 26 значений, где
# последняя (26-я) переменная - номер класса (переменная отклика)

# Часть выборки, например, 110 записей, будем использовать как
# обучающую 

# Сохраним объём всей выборки и объём обучающей выборки в переменных
n_data = n
n_train = 110

# Обучающая выборка должна быть репрезентативной -
# т.е. каждый класс должен быть представлен в ней в той же пропорции,
# что и во всей выборке.

# Подсчитаем частоты встречаемости классов в исходной выборке
# (выразим эти частоты в %, округлив результат до десятых)
round(prop.table(table(flag[m+1]))*100, digits = 1) # априорные вероятности гипотез (классов) (p(Hk))

# Чтобы обеспечить репрезентативность выборки, перемешаем её
set.seed(12345)
flagdata_mixed=flag[order(runif(n_data)),]

# Выберем обучающую выборку
train_data = flagdata_mixed[1:n_train,]
# Сохраним номера классов для строк обучающей выборки
train_data_labels = train_data[,m+1]
# формирование меток соответствующих уровней значения переменной отклика 
train_data_labels<-factor(train_data_labels)

# Подсчитаем частоту присутствия каждого класса в обучающей выборке
# и сравним с соответствующими частотами в исходной выборке
round(prop.table(table(train_data[m+1]))*100, digits = 1)

# Оставшуюся часть "перемешанной выборки" будем использовать как тестовую выборку
test_data = flagdata_mixed[(n_train+1):n_data, ]
test_data_labels = test_data[,m+1]

# Удалим из обучающей и тестовой выборок столбец с номерами классов
train_data = train_data[-(m+1)]
test_data = test_data[-(m+1)]

# Подключим пакет e1071
library("e1071")

# Вызовем наивный Байесовский классификатор:
my_classifier <- naiveBayes(train_data,
                            train_data_labels)
# Передаём обучающую выборку: факторы (train_data)
# и метки классов (train_data_labels)
# Определим ("спрогнозируем") метки для тестовых данных
data_test_pred <- predict(my_classifier, test_data) 
# Передаём классификатор и тестовую выборку
# (только факторы, без меток)

# Для оценки качества прогноза
# подключим библиотеку gmodels
library("gmodels")

# Построим кросс-валидационную таблицу:
CrossTable(x = test_data_labels, y = data_test_pred, prop.chisq=TRUE)

# Зададим новые данные
predict <- read.csv("predict.txt", sep=",", head=FALSE)
predict = predict[c(2:6, 8:17, 19:28)]
# predict = as.data.frame(lapply(predict[c(2:6, 8:17, 19:28)], normalize))


# Определим значение переменной отклика (номер класса) для новых данных
new_predict <- predict(my_classifier, predict)
new_predict

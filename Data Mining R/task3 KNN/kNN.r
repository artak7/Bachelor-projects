setwd("C://Users/pc/Documents/Магистратура/2 семестр/R/task3 kNN")
getwd()

#очищаем рабочее пространство
rm (list=ls())

# Прочитаем файл с данными в переменную flagdata
flagdata <- read.csv("flagData.txt", head = FALSE, sep=",") #, sep="\t"
flagdata

# Формула нормализации данных
normalize <- function(x) {return ((x - min(x)) / (max(x) - min(x)))}

# Нормализуем данные 
# исключим не численные факторы и переменную отклика
flag <- as.data.frame(lapply(flagdata[c(2:6, 8:17, 19:28)], normalize))

# добавим перменную отклика в конец для удобства
flag[26] = flagdata[7]
flag

# Прочитали 194 записей, в каждой - 26 значений, где
# последняя (26-я) переменная - номер класса (переменная отклика)

# Часть выборки, например, 110 записей, будем использовать как
# обучающую 

# Сохраним объём всей выборки и объём обучающей выборки в переменных
n_data = 194
n_train = 110

# Обучающая выборка должна быть репрезентативной -
# т.е. каждый класс должен быть представлен в ней в той же пропорции,
# что и во всей выборке.

# Подсчитаем частоты встречаемости классов в исходной выборке
# (выразим эти частоты в %, округлив результат до десятых)
round(prop.table(table(flag[26]))*100, digits = 1)

# Чтобы обеспечить репрезентативность выборки, перемешаем её
set.seed(12345)
flagdata_mixed=flag[order(runif(n_data)),]

# Выберем обучающую выборку
train_data = flagdata_mixed[1:n_train,]
# Сохраним номера классов для строк обучающей выборки
train_data_labels = train_data[,26]

# Перед вызовом метода knn удалим номера классов из train_data

# Подсчитаем частоту присутствия каждого класса в обучающей выборке
# и сравним с соответствующими частотами в исходной выборке
round(prop.table(table(train_data[26]))*100, digits = 1)

# Оставшуюся часть "перемешанной выборки" будем использовать
# как тестовую выборку
test_data = flagdata_mixed[(n_train+1):n_data, ]
test_data_labels = test_data[,26]

# Удалим из обучающей и тестовой выборок столбец с номерами классов
train_data = train_data[-26]
test_data = test_data[-26]

# Подключим пакет class
library("class")
data_test_pred <- knn(train = train_data,
                      test = test_data,
                      cl = train_data_labels,
                      k = round(sqrt(n_train)))

# Вызовем метод knn для тестовых данных
# Результат (номера классов) запишем в вектор data_test_pred
# Для оценки качества прогноза
# подключим библиотеку gmodels
library("gmodels")

# Построим кросс-валидационную таблицу:
CrossTable(x = test_data_labels, y = data_test_pred, prop.chisq=FALSE)

# Зададим новые данные
predict <- read.csv("predict.txt", sep=",", head=FALSE)
predict = predict[c(2:6, 8:17, 19:28)]
# predict = as.data.frame(lapply(predict[c(2:6, 8:17, 19:28)], normalize))


# Определим значение переменной отклика (номер класса) для новых данных
new_predict <- knn(train = train_data,
                   test = predict,
                   cl = train_data_labels,
                   k = round(sqrt(n_train)))
new_predict

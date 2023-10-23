setwd("C://Users/pc/Documents/Магистратура/2 семестр/R/task7 Log2")
getwd()

#очищаем рабочее пространство
rm (list=ls())

# Прочтём данные о банкнотах
bankdata <- read.csv("banknote.txt", sep=",", head=FALSE)
bankdata = bankdata[-3]
bankdata

# Озаглавим столбцы bankdata
colnames(bankdata)<-c("Variance", "Skewness", "Entropy",  "Authenticity")
bankdata

# Представим озаглавленные данные bankdata как таблицу
B<-as.data.frame(bankdata)
B

# Вызовем метод максимизации функции правдоподобия glm
mymodel<-glm(formula = Authenticity ~ Variance + Skewness + Entropy,
             family = binomial, data = B)

# Запишем найденные коэффициенты в вектор Teta
Teta=coef(mymodel)
Teta

# Определим подлинность новых банкнот
newBanknote <- read.csv("new_banknote.txt", sep=",", head=FALSE)

# Озаглавим столбцы newBanknote
colnames(newBanknote)<-c("Variance", "Skewness", "Entropy")
newBanknote

newPredict<-predict(mymodel, 
                    newdata = newBanknote, 
                    type="response")
newPredict

# Число новых банкнот
nnew = length(newBanknote[,1])
nnew

solutions = matrix(1:(nnew*4),ncol=4)
solutions[,1] = newBanknote[,1]
solutions[,2] = newBanknote[,2]
solutions[,3] = newBanknote[,3]
solutions[,4] = newPredict

# Сохраним матрицу как фрейм данных
answer = as.data.frame(solutions) 

# Добавим заголовки
colnames(answer) = c("Дисперсия", " Коэффициент асимметрии", "Энтропия", "Подлинность банкноты")
answer

# Определим подлинность банкнот из обучающей выборки
trainBanknote <- read.csv("train_banknote.txt", sep=",", head=FALSE)

# Озаглавим столбцы trainBanknote
colnames(trainBanknote)<-c("Variance", "Skewness", "Entropy")
trainBanknote

trainPredict<-predict(mymodel, 
                      newdata = trainBanknote, 
                      type="response")
trainPredict

# Число новых банкнот
nlen = length(trainBanknote[,1])
nlen

#аналогично для банкнот из обучающей выборки
train_solutions = matrix(1:(nlen*4),ncol=4)
train_solutions[,1] = trainBanknote[,1]
train_solutions[,2] = trainBanknote[,2]
train_solutions[,3] = trainBanknote[,3]
train_solutions[,4] = trainPredict

# Сохраним матрицу как фрейм данных
train_answer = as.data.frame(train_solutions) 

# Добавим заголовки
colnames(train_answer) = c("Дисперсия", " Коэффициент асимметрии", "Энтропия", "Подлинность банкноты")
train_answer

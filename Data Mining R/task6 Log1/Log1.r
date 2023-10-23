setwd("C://Users/pc/Documents/Магистратура/2 семестр/R/task6 Log1")
getwd()

#очищаем рабочее пространство
rm (list=ls())

# Прочтём данные о банкнотах
bankdata <- read.csv("banknote.txt", sep=",", head=FALSE)

# и подлинность банкноты(столбец 5)
bankdata = bankdata[c(1, 5)]
bankdata

# Построим облако точек
# для этого запишем фактор (дисперсию изображения) и значение признака подлинности банкноты
# в векторы variance и authenticity, соответственно

variance = bankdata[,1]
variance
authenticity = bankdata[,2]
authenticity

# Чтобы задать размеры облака, нанесём на график все точки, но сделаем их невидимыми
plot(variance, authenticity, type="n", main="Зависимость подлинности банкноты от дисперсии изображения")

# Определим размер выборки (число банкнот)
n = length(variance)
n

for(i in 1:n) 
{
  color = ifelse(authenticity[i]==1, "blue", "red") # цвет точки
  points(variance[i], authenticity[i], type="p",pch=16, col = color, add = "TRUE")
}

# Озаглавим столбцы bankdata
colnames(bankdata)<-c("Variance","Authenticity")
bankdata

# Представим озаглавленные данные bankdata как таблицу
B<-as.data.frame(bankdata)
B

# Вызовем метод максимизации функции правдоподобия glm
# glm - generalized linear model
mymodel<-glm(formula = Authenticity ~ Variance, family = binomial, data = B)

# Запишем найденные коэффициенты в вектор Teta
Teta=coef(mymodel)
Teta

# Для удобства напишем функцию
fexp = function (x)
{
  vspom = exp(Teta[1]+Teta[2]*x);
  return ( vspom/(1+vspom) )
}

#Совместим логистическую кривую с облаком точек
curve(fexp(x),-9, 9, col = "Orange", lwd = 3, add=TRUE)

# Определим подлинность новых банкнот
# с дисперсией изображения -3.5, 3.95, 1.5, -1.8, 0.4
newBanknote = c(-3.5, 3.95, 1.5, -1.8, 0.4)
newBanknote
newy = fexp(newBanknote)

# Нанесём новые точки на график
points(newBanknote, newy, col="Purple",type="p",pch=16,add=TRUE)

# Для наглядности построим вспомогательные линии
nnew = length(newBanknote)
for(i in 1:nnew) 
{
  segments(newBanknote[i],0, newBanknote[i],newy[i], col="gray",add="TRUE")
  segments(newBanknote[i], newy[i], -9, newy[i],col="gray",add="TRUE")
}

# Определим подлинность банкнот из обучающей выборки
# с дисперсией изображения -6.7387, -5.0477, -0.7351, 4.1711, 1.7939, 2.6606
trainBanknote = c(-6.7387, -5.0477, -0.7351, 4.1711, 1.7939, 2.6606)
trainBanknote
trainy = fexp(trainBanknote)

# Нанесём новые точки на график
points(trainBanknote, trainy, col="Green",type="p",pch=16,add=TRUE)

# Для наглядности построим вспомогательные линии
nline = length(trainBanknote)
for(i in 1:nline) 
{
  segments(trainBanknote[i],0, trainBanknote[i],trainy[i], col="gray",add="TRUE")
  segments(trainBanknote[i], trainy[i], -9, trainy[i],col="gray",add="TRUE")
}

solutions = matrix(1:(nnew*2),ncol=2)

# Запишем в первый столбец матрицы solutions значения дисперсии изображений новых банкнот
solutions[,1] = newBanknote

# Запишем во второй столбец матрицы solutions значения переменной отклика (вероятность того, что банкнота подлинна) для новых банкнот
solutions[,2] = newy

# Сохраним матрицу как фрейм данных
answer = as.data.frame(solutions)

# Добавим заголовки
colnames(answer) = c("Дисперсия изображения", "Подлинность банкноты")
answer

#аналогично для банкнот из обучающей выборки
train_solutions = matrix(1:(nline*2),ncol=2)

train_solutions[,1] = trainBanknote
train_solutions[,2] = trainy

# Сохраним матрицу как фрейм данных
train_answer = as.data.frame(train_solutions) 

# Добавим заголовки
colnames(train_answer) = c("Дисперсия изображения", "Подлинность банкноты")
train_answer

N=392 # Число наблюдений (автомобилей)
M=5 # Число факторов

# Создадим "шаблоны" матриц
Data = matrix(1 : (N*(M+1)), ncol=(M+1)) # Данные из файла
X = matrix(1 : (N*M), ncol=M) # Матрица значений факторов, расширенная единичным столбцом
Y = matrix(1 : N, ncol=1) # Столбец значений переменной отклика (mpg)
T = matrix(1 : (M+1)*(M+1), ncol = (M+1) )
Teta = matrix(1 : (M+1), ncol = 1) # Вектор коэффициентов ЛРМ
# Прочтём файл с характеристиками автомобилей и расходом топлива и запишем данные в заготовленную матрицу
Data = read.table("data1.txt", sep = '\t')

# Нормализуем данные
for(i in 0:M+1)
{
  myMax = max(Data[i])
  myMin = min(Data[i])
  Data[i] = (Data[i] - myMin)/(myMax - myMin)
}

#удалим первый и второй фактор
Data = Data[-2]
Data = Data[-1]
Data

M = 3

# Разделим значения факторов и переменной отклика
X = Data[, 1:M]
Y = Data[, (M+1)]

# Cоздадим вектор из единиц (как набор из N единиц)
odin=vector(length=N,mode='numeric')
odin = rep(1,N)

# Заготовим матрицу нужного размера
X1 = matrix(1 : (N*(M+1)),ncol=(M+1))

# Заполним первый столбец матрицы X1 единицами
X1[,1] = odin
X1[,1]

# Остальные столбцы возьмём из матрицы Х
for(i in 1:M) X1[,i+1] = X[,i]

# Найдём вектор параметров множественной линейной регрессии Teta
# Вычислим сначала матрицу t(X1)
T1 = t(X1)
T1
# Вычислим матрицу T=t(X1)%*%X1
T=T1%*%X1
T

# Подключим библиотеку для работы с матрицами
library(MASS)
# Найдём обратную матрицу для Т
obr = ginv(T)
obr
# Вычислим вектор Teta - вектор коэффициентов линейной модели
Teta=obr%*%T1%*%Y
Teta=Teta[,1]
print(Teta)

# Введём данные нашего автомобиля (чтобы оценить его расход топлива)
myAuto = c(1, 0.41304348, 0.33853133, 0.32738095)
myAuto
myX=matrix(myAuto,ncol=M+1,byrow=TRUE)
tmyX=t(myX)
# Спрогнозируем расход топлива нашего автомобиля по нашей модели
myMpg=Teta%*%tmyX
print(myMpg)

Построение уравнения регрессии с помощью функции lm:
# Прочтём файл с характеристиками автомобилей и расходом топлива
myData = read.csv("data1.txt", sep = '\t', header = TRUE)
myData

M = 5 # число факторов

# Нормализуем данные
for(i in 0:M+1)
{
  myMax = max(myData[i])
  myMin = min(myData[i])
  myData[i] = (myData[i] - myMin)/(myMax - myMin)
}

myData
# вычислим попарные коэффициенты корреляции между предикторами
rm = cor(myData)
rm

# удалим первый и второй фактор
myData = myData[-2]
myData = myData[-1]

myData

# вычислим попарные коэффициенты корреляции между предикторами
rm = cor(myData)
rm

# Построим регрессионную модель
mymodel = lm(mpg ~ horsepower +  weight + acceleration, data = myData)
mymodel
summary(mymodel)

# Введём данные нашего автомобиля (чтобы оценить его расход топлива)
myAuto=c(0.41304348, 0.33853133, 0.32738095)
myAuto=data.frame(t(myAuto))
colnames(myAuto)<-
  c("horsepower", "weight", "acceleration")
myAuto

# Спрогнозируем расход топлива нашего автомобиля по нашей модели
newMpg = predict(mymodel, myAuto)
newMpg

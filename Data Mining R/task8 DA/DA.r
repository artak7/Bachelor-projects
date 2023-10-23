# Назначим рабочий директорий
setwd("C://Users/pc/Documents/Магистратура/2 семестр/R/task8 DA")
getwd()

#очищаем рабочее пространство
rm (list=ls())


# Прочтём данные о странах, принадлежащих 1 классу (христиане)
country1<- read.csv("country1.txt", sep=",", head=FALSE)
# Выделим фактор население
country1 = country1[,5]

# Прочтём данные о странах, принадлежащих 2 классу (мусульмане)
country2<- read.csv("country2.txt", sep=",", head=FALSE)
# Выделим фактор население
country2 = country2[,5]

# Проверим гипотезу о нормальности распределения выборки стран первого класса (христиане)
shapiro.test(country1)
# Проверим гипотезу о нормальности распределения выборки стран второго класса (мусульмане)
shapiro.test(country2)

# Проверим гипотезу о равенстве дисперсий
var.test(country1, country2)

# Найдём объемы выборок
nA = length(country1)
nA
nF = length(country2)
nF
n = nA + nF
n
# Априорные вероятности:
Pk = c(nA,nF)/n
Pk

# Найдём оценки параметров
omuA=mean(country1)
"Среднее выборочное значение населения стран для стран первого класса(христиане) = "
omuA

omuF=mean(country2)
"Среднее выборочное значение населения стран для стран второго класса(мусульмане) = "
omuF

osigA=sd(country1)
"Среднее квадратическое отклонение населения стран для стран первого класса(христиане) = "
osigA

osigF=sd(country2)
"Среднее квадратическое отклонение населения стран для стран второго класса(мусульмане) = "
osigF

osig = (osigA + osigF)/2
osig

hist(country1,col="green",freq=FALSE, main="Гистограмма
     населения стран первого класса(христиане)", xlim=c(-50, 100), ylim=c(0, 0.018))
curve(dnorm(x,omuA,osigA),col="black",lwd=3,add=TRUE)

hist(country2,col="red",freq=FALSE, main="Гистограмма
     населения стран второго класса(мусульмане)", xlim=c(-50, 150), ylim=c(0, 0.02))
curve(dnorm(x,omuF,osigF),col="black",lwd=3,add=TRUE)

# Совместим графики плотности на одном рисунке
# Для этого определим диапазон значений x, на котором будем делать построение
a=min(min(country1),min(country2))
b=max(max(country1),max(country2))
curve(dnorm(x,omuA,osig),a,b,col="darkgreen",lwd=3)
curve(dnorm(x,omuF,osig),a,b,col="red",lwd=3,add=TRUE)

# Напишем функцию для определения класса(религии) страны по населению страны
fdiscr = function (x)
{
  vZ = log(Pk[1]) + x*omuA/(osig^2) - (omuA^2)/(2*osig^2);
  vT = log(Pk[2]) + x*omuF/(osig^2) - (omuF^2)/(2*osig^2);
  class <- ifelse(vZ > vT,"Класс : 1","Класс : 2");
  return (class);
}

# Сделаем прогноз значений переменной отклика для нескольких 
# стран из обучающей выборки
x = 119 # Brazil
d=fdiscr(x)
x
d
#############
x = 157 # Indonesia
d=fdiscr(x)
x
d
############
x = 2 # Jamaica
d=fdiscr(x)
x
d






###########
x = 125
d=fdiscr(x)
x
d
###########







x = 13.07
d=fdiscr(x)
x
d
###########
x = 14.21
d=fdiscr(x)
x
d

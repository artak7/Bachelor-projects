  setwd("C://Users/pc/Documents/Магистратура/2 семестр/R/task1 ОЛР1")
getwd()

A=read.table("data1.txt",header=FALSE,sep=",")

mpg=A[,6]
horse_power=A[,4]

plot(mpg, horse_power, col="blue",type="p",pch=16,
     #xlim = c(-10, 25), ylim = c(0, 300),
     xlab="horse power",ylab="mpg",main="Зависимость mpg (миль на галон топлива) от мощности (кол-ва лошадиных сил)")

myregress=lm(formula = horse_power ~ mpg)
myregress

abline(myregress,col="red",lwd="3")

# выводим информацию о модели
summary(myregress)
# выборочный коэффициент корреляции
r=cor(mpg,horse_power)
r

# найдём объём выборки n
n=length(mpg)
n
# вычислим и выведем значение T-критерия
t=r/sqrt(1-r^2)*sqrt(n-2)
t
# найдём вероятность получить (в условиях нулевой гипотезы) ещё большее значение p(t > -18.78)
p = 1 - pt(abs(t), n - 2)
p

# выбираем следующие значения независимого признака x (мощность двигателя):
newmpg=c(10,15,8,17,21,12, 19)
# newmpg = c(0.35,0.22,0.81,0.64,0.73,0.12,0.47)
newmpg

# построение прогноза:
newHorsePower=predict(myregress,data.frame(mpg = newmpg), level = 0.9, interval = "confidence")

newHorsePower

newHP1=newHorsePower[,1]

# наносим на график соответствующие точки: 
points(newmpg, newHP1, col="green", type="p", pch = 16)


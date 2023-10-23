setwd("C://Users/pc/Documents/Магистратура/R")
getwd()

A=read.table("data1.txt",header=FALSE,sep=",")

property1=A[,6]
property2=A[,4]

plot(property1, property2, col="blue",type="p",pch=16,
     xlab="horse power",ylab="mpg",main="Зависимость mpg (миль на галон топлива) от мощности (кол-ва лошадиных сил)")

myregress=lm(formula = property2 ~ property1)
myregress

abline(myregress,col="red",lwd="3")


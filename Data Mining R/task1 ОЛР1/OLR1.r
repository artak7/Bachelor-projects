  setwd("C://Users/pc/Documents/������������/2 �������/R/task1 ���1")
getwd()

A=read.table("data1.txt",header=FALSE,sep=",")

mpg=A[,6]
horse_power=A[,4]

plot(mpg, horse_power, col="blue",type="p",pch=16,
     #xlim = c(-10, 25), ylim = c(0, 300),
     xlab="horse power",ylab="mpg",main="����������� mpg (���� �� ����� �������) �� �������� (���-�� ��������� ���)")

myregress=lm(formula = horse_power ~ mpg)
myregress

abline(myregress,col="red",lwd="3")

# ������� ���������� � ������
summary(myregress)
# ���������� ����������� ����������
r=cor(mpg,horse_power)
r

# ����� ����� ������� n
n=length(mpg)
n
# �������� � ������� �������� T-��������
t=r/sqrt(1-r^2)*sqrt(n-2)
t
# ����� ����������� �������� (� �������� ������� ��������) ��� ������� �������� p(t > -18.78)
p = 1 - pt(abs(t), n - 2)
p

# �������� ��������� �������� ������������ �������� x (�������� ���������):
newmpg=c(10,15,8,17,21,12, 19)
# newmpg = c(0.35,0.22,0.81,0.64,0.73,0.12,0.47)
newmpg

# ���������� ��������:
newHorsePower=predict(myregress,data.frame(mpg = newmpg), level = 0.9, interval = "confidence")

newHorsePower

newHP1=newHorsePower[,1]

# ������� �� ������ ��������������� �����: 
points(newmpg, newHP1, col="green", type="p", pch = 16)


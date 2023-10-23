# �������� ������� ����������
setwd("C://Users/pc/Documents/������������/2 �������/R/task8 DA")
getwd()

#������� ������� ������������
rm (list=ls())


# ������ ������ � �������, ������������� 1 ������ (���������)
country1<- read.csv("country1.txt", sep=",", head=FALSE)
# ������� ������ ���������
country1 = country1[,5]

# ������ ������ � �������, ������������� 2 ������ (����������)
country2<- read.csv("country2.txt", sep=",", head=FALSE)
# ������� ������ ���������
country2 = country2[,5]

# �������� �������� � ������������ ������������� ������� ����� ������� ������ (���������)
shapiro.test(country1)
# �������� �������� � ������������ ������������� ������� ����� ������� ������ (����������)
shapiro.test(country2)

# �������� �������� � ��������� ���������
var.test(country1, country2)

# ����� ������ �������
nA = length(country1)
nA
nF = length(country2)
nF
n = nA + nF
n
# ��������� �����������:
Pk = c(nA,nF)/n
Pk

# ����� ������ ����������
omuA=mean(country1)
"������� ���������� �������� ��������� ����� ��� ����� ������� ������(���������) = "
omuA

omuF=mean(country2)
"������� ���������� �������� ��������� ����� ��� ����� ������� ������(����������) = "
omuF

osigA=sd(country1)
"������� �������������� ���������� ��������� ����� ��� ����� ������� ������(���������) = "
osigA

osigF=sd(country2)
"������� �������������� ���������� ��������� ����� ��� ����� ������� ������(����������) = "
osigF

osig = (osigA + osigF)/2
osig

hist(country1,col="green",freq=FALSE, main="�����������
     ��������� ����� ������� ������(���������)", xlim=c(-50, 100), ylim=c(0, 0.018))
curve(dnorm(x,omuA,osigA),col="black",lwd=3,add=TRUE)

hist(country2,col="red",freq=FALSE, main="�����������
     ��������� ����� ������� ������(����������)", xlim=c(-50, 150), ylim=c(0, 0.02))
curve(dnorm(x,omuF,osigF),col="black",lwd=3,add=TRUE)

# ��������� ������� ��������� �� ����� �������
# ��� ����� ��������� �������� �������� x, �� ������� ����� ������ ����������
a=min(min(country1),min(country2))
b=max(max(country1),max(country2))
curve(dnorm(x,omuA,osig),a,b,col="darkgreen",lwd=3)
curve(dnorm(x,omuF,osig),a,b,col="red",lwd=3,add=TRUE)

# ������� ������� ��� ����������� ������(�������) ������ �� ��������� ������
fdiscr = function (x)
{
  vZ = log(Pk[1]) + x*omuA/(osig^2) - (omuA^2)/(2*osig^2);
  vT = log(Pk[2]) + x*omuF/(osig^2) - (omuF^2)/(2*osig^2);
  class <- ifelse(vZ > vT,"����� : 1","����� : 2");
  return (class);
}

# ������� ������� �������� ���������� ������� ��� ���������� 
# ����� �� ��������� �������
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

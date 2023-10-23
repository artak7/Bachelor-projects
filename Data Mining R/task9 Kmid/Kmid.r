# �������� ������� ����������
setwd("C://Users/pc/Documents/������������/2 �������/R/task9 KMid")
getwd()

#������� ������� ������������
rm (list=ls())

# ������ ������ � ������
flagdata <- read.csv("flagdata.txt", sep=",", head=FALSE)

# ������ ������� � ��������
# flagdata = flagdata[-7]
# flagdata

# ������� ������������ ������
normalize <- function(x) {return ((x - min(x)) / (max(x) - min(x)))}

# ����������� ������ � �������� ���������� ������
flag <- as.data.frame(lapply(flagdata[c(2:6, 8:17, 19:28)], normalize))


m = dim(flag)[2] # ���������� �������� # 25
n = dim(flag)[1] # ����� ������� # 194

# ������� �������� ��������
# colnames(flag)<- c('V2','V3','V4','V5','V6','V8','V9','V10','V11','V12','V13','V14','V15','V16','V17','V19','V20','V21','V22','V23','V24','V25','V26','V27','V28','Type')

flag 

# ������� ����� � �������
flag_clusters <- kmeans(flag, 2)
flag_clusters

flag_clusters <- kmeans(flag, 3)
flag_clusters

flag_clusters <- kmeans(flag, 4)
flag_clusters


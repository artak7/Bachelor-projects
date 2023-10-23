setwd("C://Users/pc/Documents/Магистратура/2 семестр/R/task8 DA")
getwd()

#очищаем рабочее пространство
rm (list=ls())

flag <- read.csv("flagdata.txt", sep=",", head=FALSE)
n = length(flag[,1])
n
k1 = 0
k2 = 0
# country1 = data.frame()
# country2 = data.frame()

write("", "country1.txt", append = FALSE)
write("", "country2.txt", append = FALSE)


for (i in 1:n)
{
  
  if (flag[i, 7] == 0)
    flag[i, 7] = 1
  
  if (flag[i, 7] < 2)
  {
      k1 = k1 + 1
      print(flag[i, 1])
      print(1)
      write.table(flag[i,], "country1.txt", append = TRUE, quote=FALSE, sep=',', row.names = FALSE, col.names = FALSE)
      # country1[, k1] = flag[, i]
  }
  
  if (flag[i, 7] == 2)
  {
    k2 = k2 + 1
    print(flag[i, 1])
    print(2)
    write.table(flag[i, ], "country2.txt", append = TRUE, quote=FALSE, sep=',', row.names = FALSE, col.names = FALSE)
    # country2[, k2] = flag[, i]
  }
}

# country1
# country2
k1
k2

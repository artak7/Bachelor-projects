# назначим рабочий директорий
setwd("C:/Users/admin.WIN-OSD1NEIENB0/Documents/Rprojects/task2")

# прочитаем данные из файла в переменную dataFrame
# library(readxl)
# dataFrame = read_excel("mountains.xlsx")
# dataFrame = read.table("mountains.txt", sep = "\t", header = TRUE)
# dataFrame = dataFrame[,-4]
# write.table(dataFrame, "mountains.csv", quote=FALSE, row.names=FALSE, col.names=TRUE, sep=',') 
dataFrame = read.table("mountains.csv", header=TRUE, sep = ',')
print(dataFrame)

# число записей
nrow(dataFrame)

library(ggplot2)
#library(maps)

# построим карту мира
world_map <- map_data("world")

p <- ggplot() + coord_fixed() +
  xlab("") + ylab("")

world <- p + geom_polygon(data=world_map, aes(x=long, y=lat, group=group), 
                          colour="light green", fill="light green")
world

# data.frame для хранения информации только о тех записях, у которых
# высота >= 8.5
text_data = data.frame();
count = 1;
for(i in 1:nrow(dataFrame))
{
  if(dataFrame[i,3] >= 8.5)
  {
    text_data[count, 1] = dataFrame[i, 9];
    text_data[count, 2] = dataFrame[i, 8];
    text_data[count, 3] = dataFrame[i, 2];
    count = count+1;
  }
}
text_data

# наносим на карту горы
map_data <- 
  world +
  geom_point(data=dataFrame, 
             aes(x=dataFrame$Longitude, y=dataFrame$Latitude, size=dataFrame$Height.m, fill=dataFrame$Height.m), colour="red", 
             pch=21, alpha=I(0.7)) + 
  scale_fill_gradient(low = "yellow", high = "red") + 
  labs(fill = "Height") +
  labs(size = "Height") +
  geom_text(aes(x=text_data$V1, y=text_data$V2, label=text_data$V3), 
            hjust = 0.25, 
            nudge_x = 0.05, 
            size=2.3
  )
map_data

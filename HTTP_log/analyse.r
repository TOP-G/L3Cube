data<-read.table("weblog.txt",sep=" ",header=F)
colnames(data)=c("hostIP","user-identifier","userID","date","time","request","status","size","page","user-agent")

status=data$status

barplot(status, main="Status Code analysis",xlab="Count", ylab="Status Codes")



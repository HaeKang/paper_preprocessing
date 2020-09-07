library(stringr)
c <- read.csv("kegg_drug_dis.csv", header=F, stringsAsFactors = F)
fin_table <- data.frame()


for(i in 1:nrow(c)){
  dis_name <- c[i,]$V1
  split <- strsplit(c[i,]$V2, split="\n")
  for(k in 1:length(split[[1]])){
    start <- str_locate(split[[1]][k], ":")
    end <- str_locate(split[[1]][k], "]")
    drug <- substr(split[[1]][k], start+1, end-1)
    mod_table <- data.frame(dis_name, drug)
    fin_table <- rbind(fin_table, mod_table)
  }
}

write.table(fin_table, "drug_dis_kegg.txt", sep="\t", row.names = FALSE, quote=FALSE)

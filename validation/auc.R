library(ROCR)
score_file_3line <- read.table("3line_score_mul_count_0824_exceptTarget.txt", header=F, sep='\t')
prds_test_nb_3 <- prediction(score_file_3line$V3,  score_file_3line$V4)
auc_test_m_nb_3 <- performance(prds_test_nb_3,"auc")
auc_test_nb  <- auc_test_m_nb_3@y.values[[1]]


score_file_g <- read.table("gba_score_0824_exceptTarget.txt", header=F, sep='\t')
prds_test_nb_g <- prediction(score_file_g[,3],  score_file_g$V4)
auc_test_m_nb_g <- performance(prds_test_nb_g,"auc")
auc_test_nb_g  <- auc_test_m_nb_g@y.values[[1]]

our_sc <- auc_test_nb
gba_sc <- auc_test_nb_g



# nom

score_file_nom <- score_file_3line
names(score_file_nom) <- c("drug","disease","score","label")
score_file_nom <- transform(score_file_3line, score_n 
                            = (score_file_nom$score-min(score_file_nom$score)) / (max(score_file_nom$score) -min(score_file_nom$score)) )

head(score_file_nom[order(-score_file_nom$score),], 20)


test <- plot.roc(score_file_nom$V4, score_file_nom$score_n,
                 ci=FALSE, col="black",lty=2,
                 print.thres=TRUE)


# cut off
library(pROC)

test <- plot.roc(score_file_nom$V4, score_file_nom$score_n,
                 ci=FALSE, col="black",lty=2,
                 print.thres=TRUE)

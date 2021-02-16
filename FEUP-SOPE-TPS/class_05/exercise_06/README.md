# Exercise b

When the writer file fineshed, the read function returns 0. 
When the reader opens the file as read and write, when the writer file finishes its job, the fifo won't be closed, since there is still a writer opened.

Case the operations are happening in the same file, there is no difference between open the fifo in write-read mode and two separated calls for writing and reading. 
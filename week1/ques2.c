#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
int main(){
	int fd = open("/home/student/Desktop/231CS240/week1/ans.txt",O_CREAT | O_WRONLY);
	if(fd<0){
		perror("Error opening the file for writing");
		return 1;
	}
	char* text = "This is Pal Patel from S2 CSE\n";
	int ans = write(fd,text,strlen(text));
	if(ans<0){
		perror("Error Writing to the file");
		close(fd);
		return 1;
	}
	close(fd);
	fd = open("ans.txt",O_RDONLY);
	if(fd<0){
		perror("Error Opening the file for reading");
		return 1;
	}
	char buffer[256];
	int bytesRead;
	while((bytesRead = read(fd,buffer,sizeof(buffer)-1))>0){
		buffer[bytesRead] = '\0';
		write(STDOUT_FILENO,buffer,bytesRead);
	}
	if(bytesRead<0){
	perror("Error Reading the file");
	}
	close(fd);
	return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
int main()
{
	int fd;
	char textFileName[2000], audioFileName[2000], videoFileName[2000], imageFileName[2000], file_buffer[2000], c, caufile[70000], aufile[7000000], vfile[1000000];
	struct sockaddr_in server_address; 
	
	//socket file descriptor
	if((fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
	{
		perror("Error creating socket");
		exit(EXIT_FAILURE);
	}
	
	memset(&server_address, 0, sizeof(server_address)); 
	
	bzero(&server_address, sizeof(server_address)); 
	
	//server information
	server_address.sin_family = AF_INET; 
	server_address.sin_port = htons(8000); //Random port number, can be changed later
	server_address.sin_addr.s_addr = INADDR_ANY; 
	//server_address.sin_addr.s_addr = inet_addr("127.0.0.1"); 
	
	int choice = 1; 
	
	while(choice != 5)
	{
		printf("Choose the type of file to send.\n");
		printf("1 - Text\n");
		printf("2 - Audio\n");
		printf("3 - Video\n");
		printf("4 - Image\n");
		printf("5 - Exit\n");
		scanf("%d", &choice); 
		
		char num = choice; 
		
		sendto(fd, &num, sizeof(num), 0, (struct sockaddr *)&server_address, sizeof(struct sockaddr));
		
		switch(choice)
		{
			case 1:
				printf("Enter text file name: \n");
				scanf("%s",textFileName); 
				sendto(fd, textFileName, strlen(textFileName), 0, (struct sockaddr *)&server_address, sizeof(struct sockaddr));
				
				FILE *fp;
				fp=fopen(textFileName, "r");
				
				if(fp)
				{
					printf("Reading file content...\n");
					fseek(fp,0,SEEK_END);
					size_t file_size=ftell(fp);
					fseek(fp, 0, SEEK_SET);
					if(fread(file_buffer, file_size, 1, fp) <= 0)
					{
						printf("Unable to copy file to buffer or file is empty.\n");
						exit(1);
					}
				}
				else
				{
					printf("Error opening file.\n");
					exit(0);
				}
				
				if(sendto(fd, file_buffer, strlen(file_buffer), 0, (struct sockaddr *)&server_address, sizeof(struct sockaddr)) < 0)
				{
					printf("File not sent.\n");
				}
				else
				{
					printf("File sent.\n");
				}
				fclose(fp);
				break;
				
			case 2:
				printf("Enter audio file name: \n");
				scanf("%s", audioFileName);
				sendto(fd, audioFileName, strlen(audioFileName), 0, (struct sockaddr *)&server_address, sizeof(struct sockaddr));
				
				FILE *afp; 
				afp = fopen(audioFileName, "r"); 
				fseek(afp, 0, SEEK_END); 
				size_t afsize=ftell(afp);
				fseek(afp, 0, SEEK_SET); 
					
				if(afp)
				{
					if(fread(aufile, afsize, 1, afp) <= 0)
					{
						printf("Unable to copy file to buffer or file is empty.\n");
						exit(1);
					}
				}
				else
				{
					printf("Could not read audio file.\n");
					exit(0);
				}
				
				if(sendto(fd, aufile, afsize, 0, (struct sockaddr *)&server_address, sizeof(struct sockaddr)) < 0)
				{
					printf("File not sent.\n");
				}
				else
				{
					printf("File sent.\n"); 
				}
				
				fclose(afp); 
				break;
		
			case 3: 
				printf("Enter video file name: \n"); 
				scanf("%s", videoFileName);
				sendto(fd, videoFileName, strlen(videoFileName), 0, (struct sockaddr *)&server_address, sizeof(struct sockaddr)); 
				
				FILE *vfp; 
				vfp = fopen(videoFileName, "r");
				
				fseek(vfp, 0, SEEK_END); 
				size_t vfsize = ftell(vfp);
				fseek(vfp, 0, SEEK_SET);
				
				if(vfp)
				{
					if(fread(vfile, 1, vfsize, vfp) <= 0)
					{
						printf("Error reading file.\n");
					}
				}
				else
				{
					printf("Could not read video file.\n"); 
					exit(0);
				}
				
				if(sendto(fd, vfile, vfsize, 0, (struct sockaddr *)&server_address, sizeof(struct sockaddr)) < 0)
				{
					printf("File not sent.\n"); 
				}
				else
				{
					printf("File not sent.\n");
				}
				break;
		}			
	}	
	return 0;
}

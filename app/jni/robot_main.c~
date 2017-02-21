#include "mysock.h"
#include <signal.h>
#include <android/log.h>
#define IRC "192.168.0.62"
#define PORT 6667
#define USER "USER welcombot welcombot 192.168.0.62 :welcombot\r\n"
#define NICK "NICK robot\r\n"
#define INIT "MSG nickserv identify 123456\r\n"
#define JOIN "JOIN #uesoft\r\n"

extern char *geTime;
int sockfd;

void quit_irc(int sigum)
{
    send(sockfd,"QUIT\r\n",6,0);
    close(sockfd);
    exit(0);
}

char *get_nick(char *msg)
{
    char *buf=malloc(sizeof(int)*30);
    int i,j;

    for(i=1,j=0;msg[i];++i,++j)
        if(msg[i] == '!')
            break;
        else
            buf[j]=msg[i];
    buf[j]='\0';

    return buf;
}

void msgto(int sockfd,const char *channel,const char *nick,const char *msg)
{
    int len;
    char *buf;

    if(nick == NULL)
        len=strlen("PRIVMSG ")+strlen(channel)+strlen(msg)+5;
    else
        len=strlen("PRIVMSG ")+strlen(channel)+strlen(nick)+strlen(msg)+7;
    buf=malloc(len);
    bzero(buf,len);

    if(nick != NULL)
        sprintf(buf,"PRIVMSG %s :%s: %s\r\n",channel,nick,msg);
    else
        sprintf(buf,"PRIVMSG %s :%s\r\n",channel,msg);

    send(sockfd,buf,len-1,0);

    free(buf);
}

int main(void)
{
    char *buf;
    char *nick;
    int ret;
    fd_set reads;
    struct sigaction act,old;
	__android_log_print(10,"ouyang","-----%s---%d-----",__FILE__,__LINE__);
    sockfd=tcp_conect(IRC,PORT);
    if(sockfd == -1)
        error_quit("无法连接到远程服务器!");
	__android_log_print(10,"ouyang","-----%s---%d-----",__FILE__,__LINE__);
    act.sa_flags=0;
    act.sa_handler=quit_irc;
    sigaction(SIGINT,&act,&old);
	__android_log_print(10,"ouyang","-----%s---%d-----",__FILE__,__LINE__);
    send(sockfd,USER,strlen(USER),0);
    send(sockfd,NICK,strlen(NICK),0);
    
    send(sockfd,JOIN,strlen(JOIN),0);

    while(1)
    {
        FD_ZERO(&reads);
        FD_SET(sockfd,&reads);
        ret=select(sockfd+1,&reads,NULL,NULL,NULL);
        if(ret == -1)
            continue;

        buf=read_line(sockfd);

        printf("%s",buf);
        if(strstr(buf,"JOIN") && !strstr(buf,"PRIVMSG"))
        {
            nick=get_nick(buf);
            printf("----%s---",nick);
            msgto(sockfd,"#uesoft",nick,"欢迎来到debian_cn频道，我是机器人welcombot，祝你玩得开心，玩得快乐!");

            free(nick);
        }
		if(strstr(buf,"IDENTIFY") && !strstr(buf,"PRIVMSG"))
		{
			send(sockfd,JOIN,strlen(JOIN),0);
		}
        if(strstr(buf,"PING") && !strstr(buf,"PRIVMSG"))
        {
            buf[1]='O';
            send(sockfd,buf,strlen(buf),0);
        }
		if(strstr(buf,"PRIVMSG #uesoft"))
		{
			geTime = buf;
		}
        free(buf);
    }

    close(sockfd);

    return 0;
}

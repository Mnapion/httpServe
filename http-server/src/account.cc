#include "account.h"
#include "httpServer.h"
User users[MAXUSERSIZE];
static int usrNumbers;
static char accessedHosts[10][100];
static int accessedUsers[10];
extern httpInfo tempInfo;
int presentHostNumber;
int accountNumber;
void init()
{
	memset(users,0,sizeof(users));
	strcpy(users[0].usrName,"lac");
	strcpy(users[0].usrPassword,"west01010101");
	memset(accessedHosts,0,sizeof(accessedHosts ));
	usrNumbers=1;//only one admin
	presentHostNumber=0;
}

int checkLogin(char *loginName,char *loginPassword)
{
	if(loginName==NULL||loginPassword==NULL)
		return -2;//wrong input
	for(int i=0;i<usrNumbers;i++){
		if(strcmp(users[i].usrName,loginName)==0){
			if(strcmp(users[i].usrPassword,loginPassword)==0){
				accountNumber=i;
				printf("Match!\n");
				return 0;
			}
			else{
				printf("Wrong password!\n");
				return -1;
			}
		}
	}
	return 1;//no such account
}

int checkSignup(char *signupName,char *signupPassword)
{
	if(signupName==NULL||signupPassword==NULL)
		return -2;//wrong input
	for(int i=0;i<usrNumbers;i++)
		if(strcmp(users[i].usrName,signupName)==0)
			return -1;//already same account exists
	return 1;//able to sign up
}
void addAccount(char *loginName,char *loginPassword)
{
	if(loginName==NULL||loginPassword==NULL)
		return;
	if(usrNumbers>=MAXUSERSIZE){
		return;//can't add more accounts
	}
	for(int i=0;i<30;i++){
		users[usrNumbers].usrName[i]='\0';
		users[usrNumbers].usrPassword[i]='\0';
	}
	strcpy(users[usrNumbers].usrName,loginName);
	strcpy(users[usrNumbers].usrPassword,loginPassword);
	usrNumbers+=1;
}

void accountLogin(char *loginName,char *loginPassword)
{
	int result=checkLogin(loginName,loginPassword);
	if(result==0){
		for(int i=0;i<presentHostNumber;i++){
			if(strcmp(accessedHosts[i],tempInfo.hostInfo)==0){
				accessedUsers[i]=accountNumber;
			}
		}
		strcpy(accessedHosts[presentHostNumber],tempInfo.hostInfo);
		accessedUsers[presentHostNumber++]=accountNumber;	
	}
}

char *presentAccount()
{
	for(int i=0;i<10;i++){//only allowing 10 users to login aud p
		if(strcmp(accessedHosts[i],tempInfo.hostInfo)==0){
			return users[accessedUsers[i]].usrName;
		}
	}
	return NULL;
}

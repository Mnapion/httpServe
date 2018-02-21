#include "httpServer.h"
static httpInfo innerHttpInfo;
void clear(httpInfo information)
{
	memset(information.getInfo,0,sizeof(information.getInfo));
	memset(information.hostInfo,0,sizeof(information.hostInfo));
	memset(information.userAgentInfo,0,sizeof(information.userAgentInfo));
}
httpInfo analyzeExplorer(char *buf)
{
	strPointer httpEditionPointer,hostPointer,userAgentPointer,acceptPointer;
	clear(innerHttpInfo);
	innerHttpInfo.isValid=true;
	if(strncmp(buf,"POST",4)==0){
		innerHttpInfo.requestType=POST;
		httpEditionPointer=strstr(buf,"HTTP/1.1");
		if(httpEditionPointer==NULL){
			innerHttpInfo.isValid=false;
			return innerHttpInfo;
		}
		for(int i=0;buf+i+5<httpEditionPointer;i++){
			innerHttpInfo.postInfo[i]=buf[5+i];
		}
	}
	else if(strncmp(buf,"GET",3)==0){
		innerHttpInfo.requestType=GET;
		httpEditionPointer=strstr(buf,"HTTP/1.1");
		if(httpEditionPointer==NULL){
			innerHttpInfo.isValid=false;
			return innerHttpInfo;
		}
		for(int i=0;buf+i+4<httpEditionPointer;i++){
			innerHttpInfo.getInfo[i]=buf[4+i];
		}
	}
	else{
		innerHttpInfo.isValid=false;
		return innerHttpInfo;
	}
	hostPointer=strstr(buf,"Host: ");
	userAgentPointer=strstr(buf,"User-Agent: ");
	acceptPointer=strstr(buf,"Accept: ");
	if(hostPointer==NULL||userAgentPointer==NULL||acceptPointer==NULL){
		innerHttpInfo.isValid=false;
		return innerHttpInfo;
	}
	for(int i=0;;i++){
		if(hostPointer[i+6]!='\n')
			innerHttpInfo.hostInfo[i]=hostPointer[i+6];
		else
			break;
	}
	for(int i=0;;i++){
		if(userAgentPointer[i+12]!='\n')
			innerHttpInfo.userAgentInfo[i]=userAgentPointer[i+12];
		else
			break;
	}
	return innerHttpInfo;
}

void show(httpInfo information)
{
	if(information.isValid==false)
		printf("Invalid Connection info collected!\n");
	else{
		printf("%s:",information.requestType==POST?"post":"get");
		printf("%s\n",information.getInfo);
		printf("HostInfo:%s\n",information.hostInfo);
		printf("UserAgent:%s\n",information.userAgentInfo);
	}
}

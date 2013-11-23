//By GER.Cmd.buildgcc   CreateDate:2011/5/31 10:42:12
#include "LocalIncludeFile.h"
struct MSG_FREECARLIST FreeCarListRecordTable[MAXPAEAMRECORDS];
struct PARAM_HEAD	FreeCarListHead ;
int  ParseRecordFreeCarList(char *RecordStr,int Rowindex)
{	
	strncpy((char *)&FreeCarListRecordTable[Rowindex],RecordStr,sizeof(struct MSG_FREECARLIST));	
	return 0;
}
int LoadFreeCarListRecord(int IsFirst)
{	
	int ret = LoadRecord(PARFREECARLIST_FILE,&FreeCarListHead,LENGHT_MSG_FREECARLIST,ParseRecordFreeCarList,FRAE,IsFirst);	
	strncpy(GetMsgRevision()->FREECARLIST,FreeCarListHead.VerNo,2);	
	return ret;
}
char TempCarInfo[200];
int is_GetCarInfo = F;
int GetCarInfoStaue(void)
{
	return is_GetCarInfo;
}
char * GetCarInfo(char *CarNo)
{
	int i = 0;
	int Count = atoi(FreeCarListHead.Recordcount);
	int Flag = 0;
	memset(TempCarInfo,0x00,200);
	is_GetCarInfo = T;
	for(i=0;i<Count;i++)
	{
		if(0==strncmp(CarNo,&FreeCarListRecordTable[i].CarNo[2],3))
		{
			strncpy(&TempCarInfo[Flag],FreeCarListRecordTable[i].CarCode,5);
			strncpy(&TempCarInfo[Flag+5],FreeCarListRecordTable[i].CarNo,5);
			strncpy(&TempCarInfo[Flag+10],FreeCarListRecordTable[i].Units,15);
			TempCarInfo[Flag+25] = '\n';
			Flag +=26 ;
		}
	}
	if(0==Flag)
	{
		sprintf(TempCarInfo,"未查到车号为：%s的车辆信息！\n",CarNo);
		is_GetCarInfo = F;
		is_GetCarInfo = F;
	}
	return TempCarInfo;
}
BOOL * CheckCarInfo(char *CarNo_full)
{
	int i = 0;
	BOOL result=F;
	char CarNo[20];
	int Count = atoi(FreeCarListHead.Recordcount);
	strncpy(CarNo,(char*)&CarNo_full[3],5);
	echo_vpr("CarNo=%s CarNo_full=%s ",CarNo,CarNo_full);
	for(i=0;i<Count;i++)
	{
		if(0==strncmp(CarNo,(char*)FreeCarListRecordTable[i].CarNo,5))
		{
			result = T;
			break;
		}
	}
	return result;
}

 
char * GetCarInfo_Ex(char *CarNo_full)
{
	int i = 0;
	char CarNo[20];
	int Count = atoi(FreeCarListHead.Recordcount);
	int Flag = 0;
	memset(TempCarInfo,0x00,200);
	memset(CarNo,0x00,sizeof(20));
	is_GetCarInfo = T;
	strncpy(CarNo,(char*)&CarNo_full[3],5);
	echo_vpr("CarNo=%s CarNo_full=%s ",CarNo,CarNo_full);
	for(i=0;i<Count;i++)
	{
		if(0==strncmp(CarNo,(char*)FreeCarListRecordTable[i].CarNo,5))
		{
			strncpy(&TempCarInfo[Flag],FreeCarListRecordTable[i].CarCode,5);
			strncpy(&TempCarInfo[Flag+5],FreeCarListRecordTable[i].CarNo,5);
			strncpy(&TempCarInfo[Flag+10],FreeCarListRecordTable[i].Units,15);
			TempCarInfo[Flag+25] = '\n';
			Flag +=26 ;
		}
	}
	if(0==Flag)
	{
		sprintf(TempCarInfo,"未查到车号为：%s的车辆信息！\n",CarNo);
		is_GetCarInfo = F;
		is_GetCarInfo = F;
	}
	return TempCarInfo;
}


//end_FreeCarList

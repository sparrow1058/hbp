//at cmd shell
//#include "xshell.h"
#include "stdio.h"
#include "bsp_type.h"
#include "user_val.h"
#include "string.h"
static u8	reportType=0;
static REPORT_STRUCT page;
char * cmdStrList[MAX_CMDS]={
	"AT+HVER",
	"AT+SVER",
	"AT+HYVER",
	"AT+HP_ON",
	"AT+HP_OFF",
	"AT+HR",
	"AT+BP",
	"AT+ECGON",
	"AT+ECGOFF",
	"AT+UPF",
	"AT+PKEY",
	"AT+SKEY",
	"AT+START",
	"AT+STOP",
};

uint8_t getCmdType(uint8_t * buff);
bool StrComp(void * buffer,void * StrCmd)
{
    uint8_t i;
    uint8_t * ptBuf;
    uint8_t * ptCmd;
    
    ptBuf = (uint8_t *)buffer;
    ptCmd = (uint8_t *)StrCmd;
    for(i=0; i<255; i++)
    {
        if(ptCmd[i])
        {
            if(ptBuf[i] != ptCmd[i])
				return false;
        }
        else 
        {
            if(i)
				return true;
            else 
				return false;    
        }
    }
    return false;
}
uint8_t getCmdType(uint8_t * buff)
{
	uint8_t * pbuf=buff;
	int i;
	uint8_t ret=0xFF;
	for(i=0;i<MAX_CMDS;i++)
	{
		if(strcmp((const char *)pbuf,cmdStrList[i])==0)
		{
			ret= i;
			break;
		}
	}
	return ret;
}
void shellCmdService(volatile uint8_t  * pcBuff)
{
	uint8_t *ptRxd;
//	int 	i;
	uint16_t tmpval;
	uint8_t cmdType;
	//uint16_t retVal;
//	uint8_t buff[32];
	ptRxd=(uint8_t *)pcBuff;
	cmdType=getCmdType(ptRxd);
	reportType=cmdType;
	//printf("AT CMD =%d \n",cmdType);
	switch(cmdType)
	{
		case AT_HVER:
			AT_REPLAY("%s",hbp->hVersion);
			break;
		case AT_SVER:
			AT_REPLAY("%s",hbp->sVersion);
			break;
		case AT_HYVER:
			AT_REPLAY("%s",hbp->hyVersion);
			break;
		case AT_HP_ON:
			page.type=1;
			hbp->hpCtrl(1);
			break;
		case AT_HP_OFF:
			hbp->hpCtrl(0);
			break;
		case AT_HR:
			tmpval=hbp->getHR();
			AT_REPLAY("HR:%d",tmpval);
			break;
		case AT_BP:
			tmpval=hbp->getBP();
			AT_REPLAY("SBP:%d DBP:%d",tmpval&0xFF,tmpval>>8);
			break;
		case AT_ECGON:
			page.type=2;
			adch->ECGCtrl(true);
			break;
		case AT_ECGOFF:
			page.type=0xFF;
			adch->ECGCtrl(false);			
			break;
		case AT_UPF:
			break;
		case AT_PKEY:
			break;
		case AT_SKEY:
			break;
		case AT_START:
			page.type=0;
			break;
		case AT_STOP:
			break;
		default:
			break;
	}
}
void report_data()
{
	switch (reportType)
	{
		case AT_HR:
		case AT_BP:
			break;
		case AT_START:


}

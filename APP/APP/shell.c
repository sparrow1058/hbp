//at cmd shell
//#include "xshell.h"
#include "stdio.h"
#include "bsp_type.h"
#include "user_val.h"
#include "string.h"

//THE AT CMD ID 
#define AT_HVER		0
#define AT_SVER		1	
#define AT_HYVER	2
#define AT_HP_ON	3
#define AT_HP_OFF	4
#define AT_HR		5	
#define AT_BP		6
#define AT_ECGON	7
#define AT_ECGOFF	8
#define AT_UPF		9
#define AT_PKEY		10
#define AT_SKEY		11


//----------------
#define MAX_CMDS	20


extern HBP_HANDLE * hbp;
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
};
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
	printf("AT CMD =%d \n",cmdType);
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
			hbp->hpCtrl(1);
			break;
		case AT_HP_OFF:
			hbp->hpCtrl(0);
			break;
		case AT_HR:
			tmpval=hbp->getHR();
			AT_REPLAY("%d",tmpval);
			break;
		case AT_BP:
			tmpval=hbp->getBP();
			AT_REPLAY("%d",tmpval);
			break;
		case AT_ECGON:
			adch->ECGCtrl(true);
			break;
		case AT_ECGOFF:
			adch->ECGCtrl(false);			
			break;
		case AT_UPF:
			break;
		case AT_PKEY:
			break;
		case AT_SKEY:
			break;
		default:
			break;
	}
}


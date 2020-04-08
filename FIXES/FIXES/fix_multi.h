// dthread_handler
typedef struct TDeltaInfo
{
	TDeltaInfo *pNext;
	int nPlr;
	int bCmd;
	unsigned int dwLen;
	char body[4];
} TDeltaInfo;

// multi_send_zero_packet
TPkt + TPlayerInfoHead
typedef struct
{
	int head;
	int size;
	char data[0];
} PacketType;

// 用法:
char* buf = new char[sizeof(PacketType) + dataSize];
PacketType* pkt_buf = (PacketType*)buf;
pkt_buf->data // 此就获得了数据buf
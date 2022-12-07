#ifndef __PACKET_DEF
#define __PACKET_DEF

//������ ����� ���� Packet����

#define PKT_LOGIN				0X01
#define PKT_LOGOUT				0x02
#define PKT_ACOUNT_LOGIN        0Xfe

#define PKT_MOVEFIRST			0X03
#define PKT_MOVEMIDDLE			0X04
#define PKT_MOVEEND				0X06

#define PKT_RUN_MOVEFIRST		0X15
#define PKT_RUN_MOVEMIDDLE		0X16
#define PKT_RUN_MOVEEND			0X17

//ä��
#define PKT_CHAT				0X07

#define PKT_USERMODIFY			0X09

#define PKT_ZONECHANGE			0X0A
#define PKT_GAMESTART           0x0b
#define PKT_RESTARTGAME         0x0c

//����
#define PKT_ATTACK				0X10
#define PKT_ATTACK_ARROW		0X11  // �����Ǵ� ȭ�쵵 ���
#define PKT_ATTACK_MAGIC_RAIL	0X12  // ������ ������ Ÿ���� �����鼭 ������ ����.
#define PKT_MAGIC_READY         0X13  // ������ ����ϱ� �� �غ� 
#define PKT_MAGIC_CIRCLE        0x14  // ���� ����.
#define PKT_STATUS_INFO			0X19  // ĳ���� ��������
#define PKT_POISON				0x20  // ���� �������� ������ �ִ� ������

#define PKT_DEAD                0x23// �׾�����..
#define PKT_DEAD_INFO           0x24// ��ü ����
#define PKT_LIFE                0x25// ��� ����..
                 
#define PKT_MAGIC_ALL			0x26	// ����
#define PKT_MAGIC_BELT			0x27	// ��Ʈ�� �ִ� ����
#define PKT_SET_TIME			0x29  //��¥,�ð�,������
#define PKT_SHOW_MAGIC			0x2a  //�̺�Ʈ �׸�

#define PKT_INV_ALL             0X30

#define PKT_CHANGE_ITEM_INDEX   0X32 
#define PKT_ITEM_INFO           0X33 
#define PKT_ITEM_THROW          0x34
#define PKT_ITEM_PICKUP         0x35
#define PKT_ITEM_FIELD_INFO     0x36

#define PKT_GETITEM             0x37  //������ ȹ��
#define PKT_OUTITEM             0x38 // �κ��丮���� ������ ������.
#define PKT_MONEYCHANGE			0x39  //���� �ٲ����.

#define PKT_WEIGHT				0x3a	// ���Ը� �ش�.

#define PKT_ITEM_USE			0x3c	// ������ ���
#define PKT_ITEM_CHANGE_INFO	0x3d	// ������ ���� ����
#define PKT_ITEM_DUMP			0x3e	// �� ������

#define PKT_NEW_HERO            0x40
#define PKT_DEL_HERO            0x41

#define PKT_CHARTER_DATA        0x50  // ���� ����Ÿ...

#define PKT_CLIENTEVENT         0x60
    
#define PKT_SHOPOPEN            0x70

#define PKT_SELL_SHOP           0x72
#define PKT_BUY_SHOP            0x73

#define PKT_STORAGEOPEN			0x76
#define PKT_SAVEITEM			0x77
#define PKT_TAKEBACKITEM		0x78
#define PKT_SAVEMONEY			0x79
#define PKT_TAKEBACKMONEY		0x7a

#define PKT_MAKEROPEN			0x74	// ������ ����â ����
#define PKT_MAKEITEM			0x75	// ������ ���� �Ϸ�

#define PKT_TRADE_REQ			0x7b	// ���� �ŷ� ��û�� ���� ��
#define PKT_TRADE_ACK			0x7c	// ���� �ŷ� ��û �³�
#define PKT_TRADE_ADDITEM		0x7d	// ���� �ŷ��� ������ �߰�
#define PKT_TRADE_SETMONEY		0x7e	// ���� �ŷ��� �� ����
#define PKT_TRADE_OK			0x7f	// ���� �ŷ� Ȯ��
#define PKT_TRADE_CANCEL		0x80	// ���� �ŷ� ���
#define PKT_TRADE_RESULT		0x81	// ���� �ŷ� ����

#define PKT_AUCTION_SELL_OPEN	0x82	// ��� Sell ����
#define PKT_AUCTION_SELL_SEND	0x83	// ��� ������ ������
#define PKT_AUCTION_SELL_RCV	0x84	// ��� ������ ��������
#define PKT_AUCTION_BUY_OPEN	0x85	// ��� Buy ����
#define PKT_AUCTION_BUY_SEND	0x86	// ��� Buy �ø���

#define PKT_PUTITEM_BELT		0x87	// Inv->Belt ������ ����
#define PKT_PUTITEM_INV			0x88	// Belt->Inv ������ ����

#define PKT_SELHOUSEPLACE		0x90	// ������ ���͸� ������ ����
#define PKT_HOUSEPLACE			0x91	// ���͸� ������.

#define PKT_EVENTSELBOX         0x92    // ���� �޼��� ����
#define PKT_EVENTOKBOX          0x93    // Ȯ�� �޼���.
#define PKT_EVENTNORMAL         0x94    // �Ϲ� �޼���.
#define PKT_HPMP_RECOVERY       0x96    // Hp, Mpȸ��.

#define PKT_REPAIR_OPEN			0x99	// ����â ����
#define PKT_REPAIR_REQ			0xa0	// ���� ��û

#define PKT_BATTLEMODE			0x18 // 0 : ���� 1�̸� ����..

#define PKT_GUILD_OPEN			0x97	// ��� �޴� ����
#define	PKT_GUILD_NEW			0x95	// ��� ����
#define PKT_GUILD_LIST			0x98	// ��� ����Ʈ
#define PKT_GUILD_INFO			0x9f	// ��� ���� ��û
#define PKT_GUILD_REQ			0x9a	// ��� ���� ��û
#define PKT_GUILD_MOVE_REQ		0x9b	// ���� ��û ó��
#define PKT_GUILD_REMOVE_REQ	0x9c	// ��� ���� ��û ���
#define PKT_GUILD_DISSOLVE		0x9d	// ��� ��ü
#define PKT_GUILD_REMOVE_USER	0x9e	// ��� Ż��/���� ����
#define PKT_GUILD_REQ_USER_INFO	0xa1	// ���� ����Ʈ
#define PKT_GUILD_MAN_LIST		0xa2	// ���� ���� ��û
#define PKT_GUILD_MOVE_REJECT	0xa3	// ����� ���� ��û ����
#define PKT_GUILD_APPLICATION_LIST	0xa4	// ��� ��û�� ����Ʈ
#define PKT_CHANGE_MEMBER		0xa5	// �������� ��ġ ����
#define PKT_CHANGE_GUILD_POS	0xa6	// ��� ���� ȣĪ ����
#define PKT_CHANGE_GUILD_SYMBOL	0xb5	// ��� �ɺ� ���
#define PKT_CHANGE_GUILD_TAX	0xb6	// ��� ���� ����
#define PKT_GIVE_DONATION		0xb9	// ��α�/��ü ���� ����
#define PKT_DISSOLVE_GUILD		0xbc	// ��� ��ü ��û

// by krazi.
/////////////////////////////
#define BBS_OPEN				0x65
#define BBS_NEXT				0x66
#define BBS_READ				0x67
#define BBS_WRITE				0x68
#define BBS_EDIT				0x69
#define BBS_DELETE				0x6A
////////////////////////////////////////////////////

#endif
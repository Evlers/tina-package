
#define DISC_BUFF_LEN 4096
#define BT_NAME_LEN 128

typedef enum{
    BT_DISC_NEW_EVT,
    BT_DISC_CMPL_EVT,
    BT_DISC_DEV_INFO_EVT,
    BT_DISC_REMOTE_NAME_EVT
}tBT_DISC_EVT;
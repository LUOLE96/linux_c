#ifndef PROTO_H__
#define PROTO_H__

#define KEYPATH "/etc/services"
#define KEYPROL 'A'

#define PATHMAX 1024
#define DATAMAX 1024

enum
{
    MSG_PATH = 1,
    MSG_DATA,
    MSG_EOT
};

typedef struct msg_path_st
{
    char path[PATHMAX];//ASCII 带尾0的串
}msg_path_t;

typedef struct msg_data_st
{
    long mtype;
    char data[DATAMAX];
    int datalen;
}msg_data_t;

typedef struct msg_eot_st
{
    long mtype;
}msg_eot_t;

union msg_s2c_un
{
     long mtype;
    msg_data_t datamsg;
    msg_eot_t eotmsg
};
#endif
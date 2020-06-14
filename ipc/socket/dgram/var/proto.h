#ifndef PROTO_H__
#define PROTO_H__

#define RCVPORT "1989"
#define NAMEMAX (512-8-8)

struct msg_st
{
    //uint8_t name[NAMESIZE];
    uint32_t math;//uint32_t 和 int不一样，在不同主机uint32_t都是占四个字节
    uint32_t chinese;
    uint8_t name[1];
}__attribute__((packed));

#endif //  PROTO_H__

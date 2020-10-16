#include <uapi/linux/bpf.h>		// required by struct __sk_buff
#include <uapi/linux/pkt_cls.h>		// required by TC_ACT_OK

#ifndef __section
# define __section(NAME)                  \
   __attribute__((section(NAME), used))
#endif

__section("egress")
int tc_ingress(struct __sk_buff *skb)
{
    return TC_ACT_OK;
}

char __license[] __section("license") = "GPL";

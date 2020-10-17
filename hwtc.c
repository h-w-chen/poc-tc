#include <uapi/linux/bpf.h>		// required by struct __sk_buff
#include <uapi/linux/pkt_cls.h>		// required by TC_ACT_OK
#include <bpf/bpf_helpers.h>		// required by SEC, bpf_trace_printk

SEC("egress")
int tc_egress(struct __sk_buff *skb)
{
    bpf_printk("|||||\n");
    return TC_ACT_OK;
}

SEC("egress-block")
int tc_egressblock(struct __sk_buff *skb)
{
    bpf_printk("xxxxx\n");
    return TC_ACT_SHOT;
}

char __license[] SEC("license") = "GPL";

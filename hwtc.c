#include <uapi/linux/bpf.h>		// required by struct __sk_buff
#include <uapi/linux/pkt_cls.h>		// required by TC_ACT_OK
#include <bpf/bpf_helpers.h>		// required by SEC, bpf_trace_printk
#include <iproute2/bpf_elf.h>		// required by struct bpf_elf_map

#ifndef lock_xadd
# define lock_xadd(ptr, val)              \
   ((void)__sync_fetch_and_add(ptr, val))
#endif

// pinned map
struct bpf_elf_map hw_map SEC("maps") = {
    .type           = BPF_MAP_TYPE_ARRAY,
    .size_key       = sizeof(uint32_t),
    .size_value     = sizeof(uint32_t),
    .pinning        = PIN_GLOBAL_NS,
    .max_elem       = 2,		//0- pass, 1- block
};

SEC("egress")
int tc_egress(struct __sk_buff *skb)
{
    uint32_t *bytes;
    uint32_t dir = 0;

    bpf_printk("|||||\n");

    bytes = bpf_map_lookup_elem(&hw_map, &dir);
    if (bytes)
            lock_xadd(bytes, skb->len);

    return TC_ACT_OK;
}

SEC("egress-block")
int tc_egressblock(struct __sk_buff *skb)
{
    uint32_t *bytes;
    uint32_t dir = 1;

    bpf_printk("xxxxx\n");

    bytes = bpf_map_lookup_elem(&hw_map, &dir);
    if (bytes)
            lock_xadd(bytes, skb->len);

    return TC_ACT_SHOT;
}

char __license[] SEC("license") = "GPL";

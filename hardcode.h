#ifndef __HARDCODE_H
#define __HARDCODE_H

#include <linux/ioport.h>
#include <asm/ptrace.h>

void native_machine_crash_shutdown_ext(struct pt_regs *regs);

extern int panic_on_oops_ext;
extern void (*machine_shutdown_ext)(void);
extern int* ftrace_enabled_ext;
extern int (*insert_resource_ext)(struct resource*, struct resource*);
extern void (*disable_IO_APIC_ext)(void);
extern void(*kernel_restart_prepare_ext)(char*);

typedef void (*nmi_shootdown_cb)(int, struct pt_regs*);

extern void (*disable_local_APIC_ext)(void);
extern void (*nmi_shootdown_cpus_ext)(nmi_shootdown_cb);
extern void (*lapic_shutdown_ext)(void);
extern void (*ioapic_zap_locks_ext)(void);
extern int (*safe_smp_processor_id_ext)(void);
extern void (*hpet_disable_ext)(void);


#endif
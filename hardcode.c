#define CONFIG_KEXEC 1

#define MODULE
#define LINUX
#define __KERNEL__

#include <linux/kconfig.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include "hardcode.h"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Protryon");
MODULE_DESCRIPTION("Kexec substitute kernel mod");

#include <linux/ioport.h>
#include <asm/ptrace.h>

#include <linux/ftrace_event.h>
#include <trace/syscall.h>
#include <trace/events/syscalls.h>
#include <linux/syscalls.h>
#include <linux/slab.h>
#include <linux/ftrace.h>
#include <linux/perf_event.h>
#include <asm/syscall.h>


int panic_on_oops_ext = 1;
void (*machine_shutdown_ext)(void) = (void*) 0xc0269a40;
int* ftrace_enabled_ext = (void*) 0xc0f6e134;
int (*insert_resource_ext)(struct resource*, struct resource*) = (void*) 0xc028de80;
void (*disable_IO_APIC_ext)(void) = (void*) 0xc02722e0;
void(*kernel_restart_prepare_ext)(char*) = (void*) 0xc02ac8b0;

typedef void (*nmi_shootdown_cb)(int, struct pt_regs*);

void (*disable_local_APIC_ext)(void) = (void*) 0xc026eb00;
void (*nmi_shootdown_cpus_ext)(nmi_shootdown_cb) = (void*) 0xc0269b50;
void (*lapic_shutdown_ext)(void) = (void*) 0xc026ed20;
void (*ioapic_zap_locks_ext)(void) = (void*) 0xc0272220;
int (*safe_smp_processor_id_ext)(void) = (void*) 0xc0270540;
void (*hpet_disable_ext)(void) = (void*) 0xc0276af0;

static int syscall_enter_register(struct ftrace_event_call *event, enum trace_reg type, void *data) {
    return 0;
}

static int __init syscall_enter_define_fields(struct ftrace_event_call *call) {
    return 0;
}

static struct list_head* syscall_get_enter_fields(struct ftrace_event_call *call) {
	struct syscall_metadata *entry = call->data;
	return &entry->enter_fields;
}

static int __init init_syscall_trace(struct ftrace_event_call *call) {
	return -ENOSYS;
}

static int syscall_exit_register(struct ftrace_event_call *event, enum trace_reg type, void *data) {
	return 0;
}

static int __init syscall_exit_define_fields(struct ftrace_event_call *call) {
	return 0;
}

struct ftrace_event_class __refdata event_class_syscall_enter = {
	.system		= "syscalls",
	.reg		= syscall_enter_register,
	.define_fields	= syscall_enter_define_fields,
	.get_fields	= syscall_get_enter_fields,
	.raw_init	= init_syscall_trace,
};

struct ftrace_event_class __refdata event_class_syscall_exit = {
	.system		= "syscalls",
	.reg		= syscall_exit_register,
	.define_fields	= syscall_exit_define_fields,
	.fields		= LIST_HEAD_INIT(event_class_syscall_exit.fields),
	.raw_init	= init_syscall_trace,
};


static enum print_line_t print_syscall_enter(struct trace_iterator *iter, int flags, struct trace_event *event) {
	return TRACE_TYPE_HANDLED;
}

static enum print_line_t print_syscall_exit(struct trace_iterator *iter, int flags, struct trace_event *event) {
	return TRACE_TYPE_HANDLED;
}

struct trace_event_functions enter_syscall_print_funcs = {
	.trace		= print_syscall_enter,
};

struct trace_event_functions exit_syscall_print_funcs = {
	.trace		= print_syscall_exit,
};
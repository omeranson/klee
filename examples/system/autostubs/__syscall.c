#include <stdarg.h>
#include <stddef.h>
#include <stdlib.h>
#include <syscall.h>

#include <klee/klee.h>

#define VA_WRAPPER(f) __sys_##f##_va_wrapper(args)

typedef long (*syscall_sig)(long number, ...);

long __syscall_cp(long number, ...) {
	va_list args;
	va_start(args, number);
	long result;
	switch (number) {
	case SYS_read:
		result = VA_WRAPPER(read);
		break;
	case SYS_write:
		result = VA_WRAPPER(write);
		break;
	case SYS_open:
		result = VA_WRAPPER(open);
		break;
	case SYS_close:
		result = VA_WRAPPER(close);
		break;
	case SYS_stat:
		result = VA_WRAPPER(stat);
		break;
	case SYS_fstat:
		result = VA_WRAPPER(fstat);
		break;
	case SYS_lstat:
		result = VA_WRAPPER(lstat);
		break;
	case SYS_poll:
		result = VA_WRAPPER(poll);
		break;
	case SYS_lseek:
		result = VA_WRAPPER(lseek);
		break;
	case SYS_mmap:
		result = VA_WRAPPER(mmap);
		break;
	case SYS_mprotect:
		result = VA_WRAPPER(mprotect);
		break;
	case SYS_munmap:
		result = VA_WRAPPER(munmap);
		break;
	case SYS_brk:
		result = VA_WRAPPER(brk);
		break;
	case SYS_rt_sigaction:
		result = VA_WRAPPER(rt_sigaction);
		break;
	case SYS_rt_sigprocmask:
		result = VA_WRAPPER(rt_sigprocmask);
		break;
	case SYS_rt_sigreturn:
		result = VA_WRAPPER(rt_sigreturn);
		break;
	case SYS_ioctl:
		result = VA_WRAPPER(ioctl);
		break;
	case SYS_pread64:
		result = VA_WRAPPER(pread64);
		break;
	case SYS_pwrite64:
		result = VA_WRAPPER(pwrite64);
		break;
	case SYS_readv:
		result = VA_WRAPPER(readv);
		break;
	case SYS_writev:
		result = VA_WRAPPER(writev);
		break;
	case SYS_access:
		result = VA_WRAPPER(access);
		break;
	case SYS_pipe:
		result = VA_WRAPPER(pipe);
		break;
	case SYS_select:
		result = VA_WRAPPER(select);
		break;
	case SYS_sched_yield:
		result = VA_WRAPPER(sched_yield);
		break;
	case SYS_mremap:
		result = VA_WRAPPER(mremap);
		break;
	case SYS_msync:
		result = VA_WRAPPER(msync);
		break;
	case SYS_mincore:
		result = VA_WRAPPER(mincore);
		break;
	case SYS_madvise:
		result = VA_WRAPPER(madvise);
		break;
	case SYS_shmget:
		result = VA_WRAPPER(shmget);
		break;
	case SYS_shmat:
		result = VA_WRAPPER(shmat);
		break;
	case SYS_shmctl:
		result = VA_WRAPPER(shmctl);
		break;
	case SYS_dup:
		result = VA_WRAPPER(dup);
		break;
	case SYS_dup2:
		result = VA_WRAPPER(dup2);
		break;
	case SYS_pause:
		result = VA_WRAPPER(pause);
		break;
	case SYS_nanosleep:
		result = VA_WRAPPER(nanosleep);
		break;
	case SYS_getitimer:
		result = VA_WRAPPER(getitimer);
		break;
	case SYS_alarm:
		result = VA_WRAPPER(alarm);
		break;
	case SYS_setitimer:
		result = VA_WRAPPER(setitimer);
		break;
	case SYS_getpid:
		result = VA_WRAPPER(getpid);
		break;
	case SYS_sendfile:
		result = VA_WRAPPER(sendfile);
		break;
	case SYS_socket:
		result = VA_WRAPPER(socket);
		break;
	case SYS_connect:
		result = VA_WRAPPER(connect);
		break;
	case SYS_accept:
		result = VA_WRAPPER(accept);
		break;
	case SYS_sendto:
		result = VA_WRAPPER(sendto);
		break;
	case SYS_recvfrom:
		result = VA_WRAPPER(recvfrom);
		break;
	case SYS_sendmsg:
		result = VA_WRAPPER(sendmsg);
		break;
	case SYS_recvmsg:
		result = VA_WRAPPER(recvmsg);
		break;
	case SYS_shutdown:
		result = VA_WRAPPER(shutdown);
		break;
	case SYS_bind:
		result = VA_WRAPPER(bind);
		break;
	case SYS_listen:
		result = VA_WRAPPER(listen);
		break;
	case SYS_getsockname:
		result = VA_WRAPPER(getsockname);
		break;
	case SYS_getpeername:
		result = VA_WRAPPER(getpeername);
		break;
	case SYS_socketpair:
		result = VA_WRAPPER(socketpair);
		break;
	case SYS_setsockopt:
		result = VA_WRAPPER(setsockopt);
		break;
	case SYS_getsockopt:
		result = VA_WRAPPER(getsockopt);
		break;
	case SYS_clone:
		result = VA_WRAPPER(clone);
		break;
	case SYS_fork:
		result = VA_WRAPPER(fork);
		break;
	case SYS_vfork:
		result = VA_WRAPPER(vfork);
		break;
	case SYS_execve:
		result = VA_WRAPPER(execve);
		break;
	case SYS_exit:
		result = VA_WRAPPER(exit);
		break;
	case SYS_wait4:
		result = VA_WRAPPER(wait4);
		break;
	case SYS_kill:
		result = VA_WRAPPER(kill);
		break;
	case SYS_uname:
		result = VA_WRAPPER(uname);
		break;
	case SYS_semget:
		result = VA_WRAPPER(semget);
		break;
	case SYS_semop:
		result = VA_WRAPPER(semop);
		break;
	case SYS_semctl:
		result = VA_WRAPPER(semctl);
		break;
	case SYS_shmdt:
		result = VA_WRAPPER(shmdt);
		break;
	case SYS_msgget:
		result = VA_WRAPPER(msgget);
		break;
	case SYS_msgsnd:
		result = VA_WRAPPER(msgsnd);
		break;
	case SYS_msgrcv:
		result = VA_WRAPPER(msgrcv);
		break;
	case SYS_msgctl:
		result = VA_WRAPPER(msgctl);
		break;
	case SYS_fcntl:
		result = VA_WRAPPER(fcntl);
		break;
	case SYS_flock:
		result = VA_WRAPPER(flock);
		break;
	case SYS_fsync:
		result = VA_WRAPPER(fsync);
		break;
	case SYS_fdatasync:
		result = VA_WRAPPER(fdatasync);
		break;
	case SYS_truncate:
		result = VA_WRAPPER(truncate);
		break;
	case SYS_ftruncate:
		result = VA_WRAPPER(ftruncate);
		break;
	case SYS_getdents:
		result = VA_WRAPPER(getdents);
		break;
	case SYS_getcwd:
		result = VA_WRAPPER(getcwd);
		break;
	case SYS_chdir:
		result = VA_WRAPPER(chdir);
		break;
	case SYS_fchdir:
		result = VA_WRAPPER(fchdir);
		break;
	case SYS_rename:
		result = VA_WRAPPER(rename);
		break;
	case SYS_mkdir:
		result = VA_WRAPPER(mkdir);
		break;
	case SYS_rmdir:
		result = VA_WRAPPER(rmdir);
		break;
	case SYS_creat:
		result = VA_WRAPPER(creat);
		break;
	case SYS_link:
		result = VA_WRAPPER(link);
		break;
	case SYS_unlink:
		result = VA_WRAPPER(unlink);
		break;
	case SYS_symlink:
		result = VA_WRAPPER(symlink);
		break;
	case SYS_readlink:
		result = VA_WRAPPER(readlink);
		break;
	case SYS_chmod:
		result = VA_WRAPPER(chmod);
		break;
	case SYS_fchmod:
		result = VA_WRAPPER(fchmod);
		break;
	case SYS_chown:
		result = VA_WRAPPER(chown);
		break;
	case SYS_fchown:
		result = VA_WRAPPER(fchown);
		break;
	case SYS_lchown:
		result = VA_WRAPPER(lchown);
		break;
	case SYS_umask:
		result = VA_WRAPPER(umask);
		break;
	case SYS_gettimeofday:
		result = VA_WRAPPER(gettimeofday);
		break;
	case SYS_getrlimit:
		result = VA_WRAPPER(getrlimit);
		break;
	case SYS_getrusage:
		result = VA_WRAPPER(getrusage);
		break;
	case SYS_sysinfo:
		result = VA_WRAPPER(sysinfo);
		break;
	case SYS_times:
		result = VA_WRAPPER(times);
		break;
	case SYS_ptrace:
		result = VA_WRAPPER(ptrace);
		break;
	case SYS_getuid:
		result = VA_WRAPPER(getuid);
		break;
	case SYS_syslog:
		result = VA_WRAPPER(syslog);
		break;
	case SYS_getgid:
		result = VA_WRAPPER(getgid);
		break;
	case SYS_setuid:
		result = VA_WRAPPER(setuid);
		break;
	case SYS_setgid:
		result = VA_WRAPPER(setgid);
		break;
	case SYS_geteuid:
		result = VA_WRAPPER(geteuid);
		break;
	case SYS_getegid:
		result = VA_WRAPPER(getegid);
		break;
	case SYS_setpgid:
		result = VA_WRAPPER(setpgid);
		break;
	case SYS_getppid:
		result = VA_WRAPPER(getppid);
		break;
	case SYS_getpgrp:
		result = VA_WRAPPER(getpgrp);
		break;
	case SYS_setsid:
		result = VA_WRAPPER(setsid);
		break;
	case SYS_setreuid:
		result = VA_WRAPPER(setreuid);
		break;
	case SYS_setregid:
		result = VA_WRAPPER(setregid);
		break;
	case SYS_getgroups:
		result = VA_WRAPPER(getgroups);
		break;
	case SYS_setgroups:
		result = VA_WRAPPER(setgroups);
		break;
	case SYS_setresuid:
		result = VA_WRAPPER(setresuid);
		break;
	case SYS_getresuid:
		result = VA_WRAPPER(getresuid);
		break;
	case SYS_setresgid:
		result = VA_WRAPPER(setresgid);
		break;
	case SYS_getresgid:
		result = VA_WRAPPER(getresgid);
		break;
	case SYS_getpgid:
		result = VA_WRAPPER(getpgid);
		break;
	case SYS_setfsuid:
		result = VA_WRAPPER(setfsuid);
		break;
	case SYS_setfsgid:
		result = VA_WRAPPER(setfsgid);
		break;
	case SYS_getsid:
		result = VA_WRAPPER(getsid);
		break;
	case SYS_capget:
		result = VA_WRAPPER(capget);
		break;
	case SYS_capset:
		result = VA_WRAPPER(capset);
		break;
	case SYS_rt_sigpending:
		result = VA_WRAPPER(rt_sigpending);
		break;
	case SYS_rt_sigtimedwait:
		result = VA_WRAPPER(rt_sigtimedwait);
		break;
	case SYS_rt_sigqueueinfo:
		result = VA_WRAPPER(rt_sigqueueinfo);
		break;
	case SYS_rt_sigsuspend:
		result = VA_WRAPPER(rt_sigsuspend);
		break;
	case SYS_sigaltstack:
		result = VA_WRAPPER(sigaltstack);
		break;
	case SYS_utime:
		result = VA_WRAPPER(utime);
		break;
	case SYS_mknod:
		result = VA_WRAPPER(mknod);
		break;
	case SYS_uselib:
		result = VA_WRAPPER(uselib);
		break;
	case SYS_personality:
		result = VA_WRAPPER(personality);
		break;
	case SYS_ustat:
		result = VA_WRAPPER(ustat);
		break;
	case SYS_statfs:
		result = VA_WRAPPER(statfs);
		break;
	case SYS_fstatfs:
		result = VA_WRAPPER(fstatfs);
		break;
	case SYS_sysfs:
		result = VA_WRAPPER(sysfs);
		break;
	case SYS_getpriority:
		result = VA_WRAPPER(getpriority);
		break;
	case SYS_setpriority:
		result = VA_WRAPPER(setpriority);
		break;
	case SYS_sched_setparam:
		result = VA_WRAPPER(sched_setparam);
		break;
	case SYS_sched_getparam:
		result = VA_WRAPPER(sched_getparam);
		break;
	case SYS_sched_setscheduler:
		result = VA_WRAPPER(sched_setscheduler);
		break;
	case SYS_sched_getscheduler:
		result = VA_WRAPPER(sched_getscheduler);
		break;
	case SYS_sched_get_priority_max:
		result = VA_WRAPPER(sched_get_priority_max);
		break;
	case SYS_sched_get_priority_min:
		result = VA_WRAPPER(sched_get_priority_min);
		break;
	case SYS_sched_rr_get_interval:
		result = VA_WRAPPER(sched_rr_get_interval);
		break;
	case SYS_mlock:
		result = VA_WRAPPER(mlock);
		break;
	case SYS_munlock:
		result = VA_WRAPPER(munlock);
		break;
	case SYS_mlockall:
		result = VA_WRAPPER(mlockall);
		break;
	case SYS_munlockall:
		result = VA_WRAPPER(munlockall);
		break;
	case SYS_vhangup:
		result = VA_WRAPPER(vhangup);
		break;
	case SYS_modify_ldt:
		result = VA_WRAPPER(modify_ldt);
		break;
	case SYS_pivot_root:
		result = VA_WRAPPER(pivot_root);
		break;
	case SYS__sysctl:
		result = VA_WRAPPER(_sysctl);
		break;
	case SYS_prctl:
		result = VA_WRAPPER(prctl);
		break;
	case SYS_arch_prctl:
		result = VA_WRAPPER(arch_prctl);
		break;
	case SYS_adjtimex:
		result = VA_WRAPPER(adjtimex);
		break;
	case SYS_setrlimit:
		result = VA_WRAPPER(setrlimit);
		break;
	case SYS_chroot:
		result = VA_WRAPPER(chroot);
		break;
	case SYS_sync:
		result = VA_WRAPPER(sync);
		break;
	case SYS_acct:
		result = VA_WRAPPER(acct);
		break;
	case SYS_settimeofday:
		result = VA_WRAPPER(settimeofday);
		break;
	case SYS_mount:
		result = VA_WRAPPER(mount);
		break;
	case SYS_umount2:
		result = VA_WRAPPER(umount2);
		break;
	case SYS_swapon:
		result = VA_WRAPPER(swapon);
		break;
	case SYS_swapoff:
		result = VA_WRAPPER(swapoff);
		break;
	case SYS_reboot:
		result = VA_WRAPPER(reboot);
		break;
	case SYS_sethostname:
		result = VA_WRAPPER(sethostname);
		break;
	case SYS_setdomainname:
		result = VA_WRAPPER(setdomainname);
		break;
	case SYS_iopl:
		result = VA_WRAPPER(iopl);
		break;
	case SYS_ioperm:
		result = VA_WRAPPER(ioperm);
		break;
	case SYS_create_module:
		result = VA_WRAPPER(create_module);
		break;
	case SYS_init_module:
		result = VA_WRAPPER(init_module);
		break;
	case SYS_delete_module:
		result = VA_WRAPPER(delete_module);
		break;
	case SYS_get_kernel_syms:
		result = VA_WRAPPER(get_kernel_syms);
		break;
	case SYS_query_module:
		result = VA_WRAPPER(query_module);
		break;
	case SYS_quotactl:
		result = VA_WRAPPER(quotactl);
		break;
	case SYS_nfsservctl:
		result = VA_WRAPPER(nfsservctl);
		break;
	case SYS_getpmsg:
		result = VA_WRAPPER(getpmsg);
		break;
	case SYS_putpmsg:
		result = VA_WRAPPER(putpmsg);
		break;
	case SYS_afs_syscall:
		result = VA_WRAPPER(afs_syscall);
		break;
	case SYS_tuxcall:
		result = VA_WRAPPER(tuxcall);
		break;
	case SYS_security:
		result = VA_WRAPPER(security);
		break;
	case SYS_gettid:
		result = VA_WRAPPER(gettid);
		break;
	case SYS_readahead:
		result = VA_WRAPPER(readahead);
		break;
	case SYS_setxattr:
		result = VA_WRAPPER(setxattr);
		break;
	case SYS_lsetxattr:
		result = VA_WRAPPER(lsetxattr);
		break;
	case SYS_fsetxattr:
		result = VA_WRAPPER(fsetxattr);
		break;
	case SYS_getxattr:
		result = VA_WRAPPER(getxattr);
		break;
	case SYS_lgetxattr:
		result = VA_WRAPPER(lgetxattr);
		break;
	case SYS_fgetxattr:
		result = VA_WRAPPER(fgetxattr);
		break;
	case SYS_listxattr:
		result = VA_WRAPPER(listxattr);
		break;
	case SYS_llistxattr:
		result = VA_WRAPPER(llistxattr);
		break;
	case SYS_flistxattr:
		result = VA_WRAPPER(flistxattr);
		break;
	case SYS_removexattr:
		result = VA_WRAPPER(removexattr);
		break;
	case SYS_lremovexattr:
		result = VA_WRAPPER(lremovexattr);
		break;
	case SYS_fremovexattr:
		result = VA_WRAPPER(fremovexattr);
		break;
	case SYS_tkill:
		result = VA_WRAPPER(tkill);
		break;
	case SYS_time:
		result = VA_WRAPPER(time);
		break;
	case SYS_futex:
		result = VA_WRAPPER(futex);
		break;
	case SYS_sched_setaffinity:
		result = VA_WRAPPER(sched_setaffinity);
		break;
	case SYS_sched_getaffinity:
		result = VA_WRAPPER(sched_getaffinity);
		break;
	case SYS_set_thread_area:
		result = VA_WRAPPER(set_thread_area);
		break;
	case SYS_io_setup:
		result = VA_WRAPPER(io_setup);
		break;
	case SYS_io_destroy:
		result = VA_WRAPPER(io_destroy);
		break;
	case SYS_io_getevents:
		result = VA_WRAPPER(io_getevents);
		break;
	case SYS_io_submit:
		result = VA_WRAPPER(io_submit);
		break;
	case SYS_io_cancel:
		result = VA_WRAPPER(io_cancel);
		break;
	case SYS_get_thread_area:
		result = VA_WRAPPER(get_thread_area);
		break;
	case SYS_lookup_dcookie:
		result = VA_WRAPPER(lookup_dcookie);
		break;
	case SYS_epoll_create:
		result = VA_WRAPPER(epoll_create);
		break;
	case SYS_epoll_ctl_old:
		result = VA_WRAPPER(epoll_ctl_old);
		break;
	case SYS_epoll_wait_old:
		result = VA_WRAPPER(epoll_wait_old);
		break;
	case SYS_remap_file_pages:
		result = VA_WRAPPER(remap_file_pages);
		break;
	case SYS_getdents64:
		result = VA_WRAPPER(getdents64);
		break;
	case SYS_set_tid_address:
		result = VA_WRAPPER(set_tid_address);
		break;
	case SYS_restart_syscall:
		result = VA_WRAPPER(restart_syscall);
		break;
	case SYS_semtimedop:
		result = VA_WRAPPER(semtimedop);
		break;
	case SYS_fadvise64:
		result = VA_WRAPPER(fadvise64);
		break;
	case SYS_timer_create:
		result = VA_WRAPPER(timer_create);
		break;
	case SYS_timer_settime:
		result = VA_WRAPPER(timer_settime);
		break;
	case SYS_timer_gettime:
		result = VA_WRAPPER(timer_gettime);
		break;
	case SYS_timer_getoverrun:
		result = VA_WRAPPER(timer_getoverrun);
		break;
	case SYS_timer_delete:
		result = VA_WRAPPER(timer_delete);
		break;
	case SYS_clock_settime:
		result = VA_WRAPPER(clock_settime);
		break;
	case SYS_clock_gettime:
		result = VA_WRAPPER(clock_gettime);
		break;
	case SYS_clock_getres:
		result = VA_WRAPPER(clock_getres);
		break;
	case SYS_clock_nanosleep:
		result = VA_WRAPPER(clock_nanosleep);
		break;
	case SYS_exit_group:
		result = VA_WRAPPER(exit_group);
		break;
	case SYS_epoll_wait:
		result = VA_WRAPPER(epoll_wait);
		break;
	case SYS_epoll_ctl:
		result = VA_WRAPPER(epoll_ctl);
		break;
	case SYS_tgkill:
		result = VA_WRAPPER(tgkill);
		break;
	case SYS_utimes:
		result = VA_WRAPPER(utimes);
		break;
	case SYS_vserver:
		result = VA_WRAPPER(vserver);
		break;
	case SYS_mbind:
		result = VA_WRAPPER(mbind);
		break;
	case SYS_set_mempolicy:
		result = VA_WRAPPER(set_mempolicy);
		break;
	case SYS_get_mempolicy:
		result = VA_WRAPPER(get_mempolicy);
		break;
	case SYS_mq_open:
		result = VA_WRAPPER(mq_open);
		break;
	case SYS_mq_unlink:
		result = VA_WRAPPER(mq_unlink);
		break;
	case SYS_mq_timedsend:
		result = VA_WRAPPER(mq_timedsend);
		break;
	case SYS_mq_timedreceive:
		result = VA_WRAPPER(mq_timedreceive);
		break;
	case SYS_mq_notify:
		result = VA_WRAPPER(mq_notify);
		break;
	case SYS_mq_getsetattr:
		result = VA_WRAPPER(mq_getsetattr);
		break;
	case SYS_kexec_load:
		result = VA_WRAPPER(kexec_load);
		break;
	case SYS_waitid:
		result = VA_WRAPPER(waitid);
		break;
	case SYS_add_key:
		result = VA_WRAPPER(add_key);
		break;
	case SYS_request_key:
		result = VA_WRAPPER(request_key);
		break;
	case SYS_keyctl:
		result = VA_WRAPPER(keyctl);
		break;
	case SYS_ioprio_set:
		result = VA_WRAPPER(ioprio_set);
		break;
	case SYS_ioprio_get:
		result = VA_WRAPPER(ioprio_get);
		break;
	case SYS_inotify_init:
		result = VA_WRAPPER(inotify_init);
		break;
	case SYS_inotify_add_watch:
		result = VA_WRAPPER(inotify_add_watch);
		break;
	case SYS_inotify_rm_watch:
		result = VA_WRAPPER(inotify_rm_watch);
		break;
	case SYS_migrate_pages:
		result = VA_WRAPPER(migrate_pages);
		break;
	case SYS_openat:
		result = VA_WRAPPER(openat);
		break;
	case SYS_mkdirat:
		result = VA_WRAPPER(mkdirat);
		break;
	case SYS_mknodat:
		result = VA_WRAPPER(mknodat);
		break;
	case SYS_fchownat:
		result = VA_WRAPPER(fchownat);
		break;
	case SYS_futimesat:
		result = VA_WRAPPER(futimesat);
		break;
	case SYS_newfstatat:
		result = VA_WRAPPER(newfstatat);
		break;
	case SYS_unlinkat:
		result = VA_WRAPPER(unlinkat);
		break;
	case SYS_renameat:
		result = VA_WRAPPER(renameat);
		break;
	case SYS_linkat:
		result = VA_WRAPPER(linkat);
		break;
	case SYS_symlinkat:
		result = VA_WRAPPER(symlinkat);
		break;
	case SYS_readlinkat:
		result = VA_WRAPPER(readlinkat);
		break;
	case SYS_fchmodat:
		result = VA_WRAPPER(fchmodat);
		break;
	case SYS_faccessat:
		result = VA_WRAPPER(faccessat);
		break;
	case SYS_pselect6:
		result = VA_WRAPPER(pselect6);
		break;
	case SYS_ppoll:
		result = VA_WRAPPER(ppoll);
		break;
	case SYS_unshare:
		result = VA_WRAPPER(unshare);
		break;
	case SYS_set_robust_list:
		result = VA_WRAPPER(set_robust_list);
		break;
	case SYS_get_robust_list:
		result = VA_WRAPPER(get_robust_list);
		break;
	case SYS_splice:
		result = VA_WRAPPER(splice);
		break;
	case SYS_tee:
		result = VA_WRAPPER(tee);
		break;
	case SYS_sync_file_range:
		result = VA_WRAPPER(sync_file_range);
		break;
	case SYS_vmsplice:
		result = VA_WRAPPER(vmsplice);
		break;
	case SYS_move_pages:
		result = VA_WRAPPER(move_pages);
		break;
	case SYS_utimensat:
		result = VA_WRAPPER(utimensat);
		break;
	case SYS_epoll_pwait:
		result = VA_WRAPPER(epoll_pwait);
		break;
	case SYS_signalfd:
		result = VA_WRAPPER(signalfd);
		break;
	case SYS_timerfd_create:
		result = VA_WRAPPER(timerfd_create);
		break;
	case SYS_eventfd:
		result = VA_WRAPPER(eventfd);
		break;
	case SYS_fallocate:
		result = VA_WRAPPER(fallocate);
		break;
	case SYS_timerfd_settime:
		result = VA_WRAPPER(timerfd_settime);
		break;
	case SYS_timerfd_gettime:
		result = VA_WRAPPER(timerfd_gettime);
		break;
	case SYS_accept4:
		result = VA_WRAPPER(accept4);
		break;
	case SYS_signalfd4:
		result = VA_WRAPPER(signalfd4);
		break;
	case SYS_eventfd2:
		result = VA_WRAPPER(eventfd2);
		break;
	case SYS_epoll_create1:
		result = VA_WRAPPER(epoll_create1);
		break;
	case SYS_dup3:
		result = VA_WRAPPER(dup3);
		break;
	case SYS_pipe2:
		result = VA_WRAPPER(pipe2);
		break;
	case SYS_inotify_init1:
		result = VA_WRAPPER(inotify_init1);
		break;
	case SYS_preadv:
		result = VA_WRAPPER(preadv);
		break;
	case SYS_pwritev:
		result = VA_WRAPPER(pwritev);
		break;
	case SYS_rt_tgsigqueueinfo:
		result = VA_WRAPPER(rt_tgsigqueueinfo);
		break;
	case SYS_perf_event_open:
		result = VA_WRAPPER(perf_event_open);
		break;
	case SYS_recvmmsg:
		result = VA_WRAPPER(recvmmsg);
		break;
	case SYS_fanotify_init:
		result = VA_WRAPPER(fanotify_init);
		break;
	case SYS_fanotify_mark:
		result = VA_WRAPPER(fanotify_mark);
		break;
	case SYS_prlimit64:
		result = VA_WRAPPER(prlimit64);
		break;
	case SYS_name_to_handle_at:
		result = VA_WRAPPER(name_to_handle_at);
		break;
	case SYS_open_by_handle_at:
		result = VA_WRAPPER(open_by_handle_at);
		break;
	case SYS_clock_adjtime:
		result = VA_WRAPPER(clock_adjtime);
		break;
	case SYS_syncfs:
		result = VA_WRAPPER(syncfs);
		break;
	case SYS_sendmmsg:
		result = VA_WRAPPER(sendmmsg);
		break;
	case SYS_setns:
		result = VA_WRAPPER(setns);
		break;
	case SYS_getcpu:
		result = VA_WRAPPER(getcpu);
		break;
	case SYS_process_vm_readv:
		result = VA_WRAPPER(process_vm_readv);
		break;
	case SYS_process_vm_writev:
		result = VA_WRAPPER(process_vm_writev);
		break;
	case SYS_kcmp:
		result = VA_WRAPPER(kcmp);
		break;
	case SYS_finit_module:
		result = VA_WRAPPER(finit_module);
		break;
	case SYS_sched_setattr:
		result = VA_WRAPPER(sched_setattr);
		break;
	case SYS_sched_getattr:
		result = VA_WRAPPER(sched_getattr);
		break;
	case SYS_renameat2:
		result = VA_WRAPPER(renameat2);
		break;
	case SYS_seccomp:
		result = VA_WRAPPER(seccomp);
		break;
	case SYS_getrandom:
		result = VA_WRAPPER(getrandom);
		break;
	case SYS_memfd_create:
		result = VA_WRAPPER(memfd_create);
		break;
	case SYS_kexec_file_load:
		result = VA_WRAPPER(kexec_file_load);
		break;
	case SYS_bpf:
		result = VA_WRAPPER(bpf);
		break;
	case SYS_execveat:
		result = VA_WRAPPER(execveat);
		break;
	case SYS_userfaultfd:
		result = VA_WRAPPER(userfaultfd);
		break;
	case SYS_membarrier:
		result = VA_WRAPPER(membarrier);
		break;
	case SYS_mlock2:
		result = VA_WRAPPER(mlock2);
		break;
	default:
		va_end(args);
		abort();
	}
	va_end(args);
	return result;
}

long __syscall(long number, ...) {
	va_list args;
	va_start(args, number);
	long result;
	switch (number) {
	case SYS_read:
		result = VA_WRAPPER(read);
		break;
	case SYS_write:
		result = VA_WRAPPER(write);
		break;
	case SYS_open:
		result = VA_WRAPPER(open);
		break;
	case SYS_close:
		result = VA_WRAPPER(close);
		break;
	case SYS_stat:
		result = VA_WRAPPER(stat);
		break;
	case SYS_fstat:
		result = VA_WRAPPER(fstat);
		break;
	case SYS_lstat:
		result = VA_WRAPPER(lstat);
		break;
	case SYS_poll:
		result = VA_WRAPPER(poll);
		break;
	case SYS_lseek:
		result = VA_WRAPPER(lseek);
		break;
	case SYS_mmap:
		result = VA_WRAPPER(mmap);
		break;
	case SYS_mprotect:
		result = VA_WRAPPER(mprotect);
		break;
	case SYS_munmap:
		result = VA_WRAPPER(munmap);
		break;
	case SYS_brk:
		result = VA_WRAPPER(brk);
		break;
	case SYS_rt_sigaction:
		result = VA_WRAPPER(rt_sigaction);
		break;
	case SYS_rt_sigprocmask:
		result = VA_WRAPPER(rt_sigprocmask);
		break;
	case SYS_rt_sigreturn:
		result = VA_WRAPPER(rt_sigreturn);
		break;
	case SYS_ioctl:
		result = VA_WRAPPER(ioctl);
		break;
	case SYS_pread64:
		result = VA_WRAPPER(pread64);
		break;
	case SYS_pwrite64:
		result = VA_WRAPPER(pwrite64);
		break;
	case SYS_readv:
		result = VA_WRAPPER(readv);
		break;
	case SYS_writev:
		result = VA_WRAPPER(writev);
		break;
	case SYS_access:
		result = VA_WRAPPER(access);
		break;
	case SYS_pipe:
		result = VA_WRAPPER(pipe);
		break;
	case SYS_select:
		result = VA_WRAPPER(select);
		break;
	case SYS_sched_yield:
		result = VA_WRAPPER(sched_yield);
		break;
	case SYS_mremap:
		result = VA_WRAPPER(mremap);
		break;
	case SYS_msync:
		result = VA_WRAPPER(msync);
		break;
	case SYS_mincore:
		result = VA_WRAPPER(mincore);
		break;
	case SYS_madvise:
		result = VA_WRAPPER(madvise);
		break;
	case SYS_shmget:
		result = VA_WRAPPER(shmget);
		break;
	case SYS_shmat:
		result = VA_WRAPPER(shmat);
		break;
	case SYS_shmctl:
		result = VA_WRAPPER(shmctl);
		break;
	case SYS_dup:
		result = VA_WRAPPER(dup);
		break;
	case SYS_dup2:
		result = VA_WRAPPER(dup2);
		break;
	case SYS_pause:
		result = VA_WRAPPER(pause);
		break;
	case SYS_nanosleep:
		result = VA_WRAPPER(nanosleep);
		break;
	case SYS_getitimer:
		result = VA_WRAPPER(getitimer);
		break;
	case SYS_alarm:
		result = VA_WRAPPER(alarm);
		break;
	case SYS_setitimer:
		result = VA_WRAPPER(setitimer);
		break;
	case SYS_getpid:
		result = VA_WRAPPER(getpid);
		break;
	case SYS_sendfile:
		result = VA_WRAPPER(sendfile);
		break;
	case SYS_socket:
		result = VA_WRAPPER(socket);
		break;
	case SYS_connect:
		result = VA_WRAPPER(connect);
		break;
	case SYS_accept:
		result = VA_WRAPPER(accept);
		break;
	case SYS_sendto:
		result = VA_WRAPPER(sendto);
		break;
	case SYS_recvfrom:
		result = VA_WRAPPER(recvfrom);
		break;
	case SYS_sendmsg:
		result = VA_WRAPPER(sendmsg);
		break;
	case SYS_recvmsg:
		result = VA_WRAPPER(recvmsg);
		break;
	case SYS_shutdown:
		result = VA_WRAPPER(shutdown);
		break;
	case SYS_bind:
		result = VA_WRAPPER(bind);
		break;
	case SYS_listen:
		result = VA_WRAPPER(listen);
		break;
	case SYS_getsockname:
		result = VA_WRAPPER(getsockname);
		break;
	case SYS_getpeername:
		result = VA_WRAPPER(getpeername);
		break;
	case SYS_socketpair:
		result = VA_WRAPPER(socketpair);
		break;
	case SYS_setsockopt:
		result = VA_WRAPPER(setsockopt);
		break;
	case SYS_getsockopt:
		result = VA_WRAPPER(getsockopt);
		break;
	case SYS_clone:
		result = VA_WRAPPER(clone);
		break;
	case SYS_fork:
		result = VA_WRAPPER(fork);
		break;
	case SYS_vfork:
		result = VA_WRAPPER(vfork);
		break;
	case SYS_execve:
		result = VA_WRAPPER(execve);
		break;
	case SYS_exit:
		result = VA_WRAPPER(exit);
		break;
	case SYS_wait4:
		result = VA_WRAPPER(wait4);
		break;
	case SYS_kill:
		result = VA_WRAPPER(kill);
		break;
	case SYS_uname:
		result = VA_WRAPPER(uname);
		break;
	case SYS_semget:
		result = VA_WRAPPER(semget);
		break;
	case SYS_semop:
		result = VA_WRAPPER(semop);
		break;
	case SYS_semctl:
		result = VA_WRAPPER(semctl);
		break;
	case SYS_shmdt:
		result = VA_WRAPPER(shmdt);
		break;
	case SYS_msgget:
		result = VA_WRAPPER(msgget);
		break;
	case SYS_msgsnd:
		result = VA_WRAPPER(msgsnd);
		break;
	case SYS_msgrcv:
		result = VA_WRAPPER(msgrcv);
		break;
	case SYS_msgctl:
		result = VA_WRAPPER(msgctl);
		break;
	case SYS_fcntl:
		result = VA_WRAPPER(fcntl);
		break;
	case SYS_flock:
		result = VA_WRAPPER(flock);
		break;
	case SYS_fsync:
		result = VA_WRAPPER(fsync);
		break;
	case SYS_fdatasync:
		result = VA_WRAPPER(fdatasync);
		break;
	case SYS_truncate:
		result = VA_WRAPPER(truncate);
		break;
	case SYS_ftruncate:
		result = VA_WRAPPER(ftruncate);
		break;
	case SYS_getdents:
		result = VA_WRAPPER(getdents);
		break;
	case SYS_getcwd:
		result = VA_WRAPPER(getcwd);
		break;
	case SYS_chdir:
		result = VA_WRAPPER(chdir);
		break;
	case SYS_fchdir:
		result = VA_WRAPPER(fchdir);
		break;
	case SYS_rename:
		result = VA_WRAPPER(rename);
		break;
	case SYS_mkdir:
		result = VA_WRAPPER(mkdir);
		break;
	case SYS_rmdir:
		result = VA_WRAPPER(rmdir);
		break;
	case SYS_creat:
		result = VA_WRAPPER(creat);
		break;
	case SYS_link:
		result = VA_WRAPPER(link);
		break;
	case SYS_unlink:
		result = VA_WRAPPER(unlink);
		break;
	case SYS_symlink:
		result = VA_WRAPPER(symlink);
		break;
	case SYS_readlink:
		result = VA_WRAPPER(readlink);
		break;
	case SYS_chmod:
		result = VA_WRAPPER(chmod);
		break;
	case SYS_fchmod:
		result = VA_WRAPPER(fchmod);
		break;
	case SYS_chown:
		result = VA_WRAPPER(chown);
		break;
	case SYS_fchown:
		result = VA_WRAPPER(fchown);
		break;
	case SYS_lchown:
		result = VA_WRAPPER(lchown);
		break;
	case SYS_umask:
		result = VA_WRAPPER(umask);
		break;
	case SYS_gettimeofday:
		result = VA_WRAPPER(gettimeofday);
		break;
	case SYS_getrlimit:
		result = VA_WRAPPER(getrlimit);
		break;
	case SYS_getrusage:
		result = VA_WRAPPER(getrusage);
		break;
	case SYS_sysinfo:
		result = VA_WRAPPER(sysinfo);
		break;
	case SYS_times:
		result = VA_WRAPPER(times);
		break;
	case SYS_ptrace:
		result = VA_WRAPPER(ptrace);
		break;
	case SYS_getuid:
		result = VA_WRAPPER(getuid);
		break;
	case SYS_syslog:
		result = VA_WRAPPER(syslog);
		break;
	case SYS_getgid:
		result = VA_WRAPPER(getgid);
		break;
	case SYS_setuid:
		result = VA_WRAPPER(setuid);
		break;
	case SYS_setgid:
		result = VA_WRAPPER(setgid);
		break;
	case SYS_geteuid:
		result = VA_WRAPPER(geteuid);
		break;
	case SYS_getegid:
		result = VA_WRAPPER(getegid);
		break;
	case SYS_setpgid:
		result = VA_WRAPPER(setpgid);
		break;
	case SYS_getppid:
		result = VA_WRAPPER(getppid);
		break;
	case SYS_getpgrp:
		result = VA_WRAPPER(getpgrp);
		break;
	case SYS_setsid:
		result = VA_WRAPPER(setsid);
		break;
	case SYS_setreuid:
		result = VA_WRAPPER(setreuid);
		break;
	case SYS_setregid:
		result = VA_WRAPPER(setregid);
		break;
	case SYS_getgroups:
		result = VA_WRAPPER(getgroups);
		break;
	case SYS_setgroups:
		result = VA_WRAPPER(setgroups);
		break;
	case SYS_setresuid:
		result = VA_WRAPPER(setresuid);
		break;
	case SYS_getresuid:
		result = VA_WRAPPER(getresuid);
		break;
	case SYS_setresgid:
		result = VA_WRAPPER(setresgid);
		break;
	case SYS_getresgid:
		result = VA_WRAPPER(getresgid);
		break;
	case SYS_getpgid:
		result = VA_WRAPPER(getpgid);
		break;
	case SYS_setfsuid:
		result = VA_WRAPPER(setfsuid);
		break;
	case SYS_setfsgid:
		result = VA_WRAPPER(setfsgid);
		break;
	case SYS_getsid:
		result = VA_WRAPPER(getsid);
		break;
	case SYS_capget:
		result = VA_WRAPPER(capget);
		break;
	case SYS_capset:
		result = VA_WRAPPER(capset);
		break;
	case SYS_rt_sigpending:
		result = VA_WRAPPER(rt_sigpending);
		break;
	case SYS_rt_sigtimedwait:
		result = VA_WRAPPER(rt_sigtimedwait);
		break;
	case SYS_rt_sigqueueinfo:
		result = VA_WRAPPER(rt_sigqueueinfo);
		break;
	case SYS_rt_sigsuspend:
		result = VA_WRAPPER(rt_sigsuspend);
		break;
	case SYS_sigaltstack:
		result = VA_WRAPPER(sigaltstack);
		break;
	case SYS_utime:
		result = VA_WRAPPER(utime);
		break;
	case SYS_mknod:
		result = VA_WRAPPER(mknod);
		break;
	case SYS_uselib:
		result = VA_WRAPPER(uselib);
		break;
	case SYS_personality:
		result = VA_WRAPPER(personality);
		break;
	case SYS_ustat:
		result = VA_WRAPPER(ustat);
		break;
	case SYS_statfs:
		result = VA_WRAPPER(statfs);
		break;
	case SYS_fstatfs:
		result = VA_WRAPPER(fstatfs);
		break;
	case SYS_sysfs:
		result = VA_WRAPPER(sysfs);
		break;
	case SYS_getpriority:
		result = VA_WRAPPER(getpriority);
		break;
	case SYS_setpriority:
		result = VA_WRAPPER(setpriority);
		break;
	case SYS_sched_setparam:
		result = VA_WRAPPER(sched_setparam);
		break;
	case SYS_sched_getparam:
		result = VA_WRAPPER(sched_getparam);
		break;
	case SYS_sched_setscheduler:
		result = VA_WRAPPER(sched_setscheduler);
		break;
	case SYS_sched_getscheduler:
		result = VA_WRAPPER(sched_getscheduler);
		break;
	case SYS_sched_get_priority_max:
		result = VA_WRAPPER(sched_get_priority_max);
		break;
	case SYS_sched_get_priority_min:
		result = VA_WRAPPER(sched_get_priority_min);
		break;
	case SYS_sched_rr_get_interval:
		result = VA_WRAPPER(sched_rr_get_interval);
		break;
	case SYS_mlock:
		result = VA_WRAPPER(mlock);
		break;
	case SYS_munlock:
		result = VA_WRAPPER(munlock);
		break;
	case SYS_mlockall:
		result = VA_WRAPPER(mlockall);
		break;
	case SYS_munlockall:
		result = VA_WRAPPER(munlockall);
		break;
	case SYS_vhangup:
		result = VA_WRAPPER(vhangup);
		break;
	case SYS_modify_ldt:
		result = VA_WRAPPER(modify_ldt);
		break;
	case SYS_pivot_root:
		result = VA_WRAPPER(pivot_root);
		break;
	case SYS__sysctl:
		result = VA_WRAPPER(_sysctl);
		break;
	case SYS_prctl:
		result = VA_WRAPPER(prctl);
		break;
	case SYS_arch_prctl:
		result = VA_WRAPPER(arch_prctl);
		break;
	case SYS_adjtimex:
		result = VA_WRAPPER(adjtimex);
		break;
	case SYS_setrlimit:
		result = VA_WRAPPER(setrlimit);
		break;
	case SYS_chroot:
		result = VA_WRAPPER(chroot);
		break;
	case SYS_sync:
		result = VA_WRAPPER(sync);
		break;
	case SYS_acct:
		result = VA_WRAPPER(acct);
		break;
	case SYS_settimeofday:
		result = VA_WRAPPER(settimeofday);
		break;
	case SYS_mount:
		result = VA_WRAPPER(mount);
		break;
	case SYS_umount2:
		result = VA_WRAPPER(umount2);
		break;
	case SYS_swapon:
		result = VA_WRAPPER(swapon);
		break;
	case SYS_swapoff:
		result = VA_WRAPPER(swapoff);
		break;
	case SYS_reboot:
		result = VA_WRAPPER(reboot);
		break;
	case SYS_sethostname:
		result = VA_WRAPPER(sethostname);
		break;
	case SYS_setdomainname:
		result = VA_WRAPPER(setdomainname);
		break;
	case SYS_iopl:
		result = VA_WRAPPER(iopl);
		break;
	case SYS_ioperm:
		result = VA_WRAPPER(ioperm);
		break;
	case SYS_create_module:
		result = VA_WRAPPER(create_module);
		break;
	case SYS_init_module:
		result = VA_WRAPPER(init_module);
		break;
	case SYS_delete_module:
		result = VA_WRAPPER(delete_module);
		break;
	case SYS_get_kernel_syms:
		result = VA_WRAPPER(get_kernel_syms);
		break;
	case SYS_query_module:
		result = VA_WRAPPER(query_module);
		break;
	case SYS_quotactl:
		result = VA_WRAPPER(quotactl);
		break;
	case SYS_nfsservctl:
		result = VA_WRAPPER(nfsservctl);
		break;
	case SYS_getpmsg:
		result = VA_WRAPPER(getpmsg);
		break;
	case SYS_putpmsg:
		result = VA_WRAPPER(putpmsg);
		break;
	case SYS_afs_syscall:
		result = VA_WRAPPER(afs_syscall);
		break;
	case SYS_tuxcall:
		result = VA_WRAPPER(tuxcall);
		break;
	case SYS_security:
		result = VA_WRAPPER(security);
		break;
	case SYS_gettid:
		result = VA_WRAPPER(gettid);
		break;
	case SYS_readahead:
		result = VA_WRAPPER(readahead);
		break;
	case SYS_setxattr:
		result = VA_WRAPPER(setxattr);
		break;
	case SYS_lsetxattr:
		result = VA_WRAPPER(lsetxattr);
		break;
	case SYS_fsetxattr:
		result = VA_WRAPPER(fsetxattr);
		break;
	case SYS_getxattr:
		result = VA_WRAPPER(getxattr);
		break;
	case SYS_lgetxattr:
		result = VA_WRAPPER(lgetxattr);
		break;
	case SYS_fgetxattr:
		result = VA_WRAPPER(fgetxattr);
		break;
	case SYS_listxattr:
		result = VA_WRAPPER(listxattr);
		break;
	case SYS_llistxattr:
		result = VA_WRAPPER(llistxattr);
		break;
	case SYS_flistxattr:
		result = VA_WRAPPER(flistxattr);
		break;
	case SYS_removexattr:
		result = VA_WRAPPER(removexattr);
		break;
	case SYS_lremovexattr:
		result = VA_WRAPPER(lremovexattr);
		break;
	case SYS_fremovexattr:
		result = VA_WRAPPER(fremovexattr);
		break;
	case SYS_tkill:
		result = VA_WRAPPER(tkill);
		break;
	case SYS_time:
		result = VA_WRAPPER(time);
		break;
	case SYS_futex:
		result = VA_WRAPPER(futex);
		break;
	case SYS_sched_setaffinity:
		result = VA_WRAPPER(sched_setaffinity);
		break;
	case SYS_sched_getaffinity:
		result = VA_WRAPPER(sched_getaffinity);
		break;
	case SYS_set_thread_area:
		result = VA_WRAPPER(set_thread_area);
		break;
	case SYS_io_setup:
		result = VA_WRAPPER(io_setup);
		break;
	case SYS_io_destroy:
		result = VA_WRAPPER(io_destroy);
		break;
	case SYS_io_getevents:
		result = VA_WRAPPER(io_getevents);
		break;
	case SYS_io_submit:
		result = VA_WRAPPER(io_submit);
		break;
	case SYS_io_cancel:
		result = VA_WRAPPER(io_cancel);
		break;
	case SYS_get_thread_area:
		result = VA_WRAPPER(get_thread_area);
		break;
	case SYS_lookup_dcookie:
		result = VA_WRAPPER(lookup_dcookie);
		break;
	case SYS_epoll_create:
		result = VA_WRAPPER(epoll_create);
		break;
	case SYS_epoll_ctl_old:
		result = VA_WRAPPER(epoll_ctl_old);
		break;
	case SYS_epoll_wait_old:
		result = VA_WRAPPER(epoll_wait_old);
		break;
	case SYS_remap_file_pages:
		result = VA_WRAPPER(remap_file_pages);
		break;
	case SYS_getdents64:
		result = VA_WRAPPER(getdents64);
		break;
	case SYS_set_tid_address:
		result = VA_WRAPPER(set_tid_address);
		break;
	case SYS_restart_syscall:
		result = VA_WRAPPER(restart_syscall);
		break;
	case SYS_semtimedop:
		result = VA_WRAPPER(semtimedop);
		break;
	case SYS_fadvise64:
		result = VA_WRAPPER(fadvise64);
		break;
	case SYS_timer_create:
		result = VA_WRAPPER(timer_create);
		break;
	case SYS_timer_settime:
		result = VA_WRAPPER(timer_settime);
		break;
	case SYS_timer_gettime:
		result = VA_WRAPPER(timer_gettime);
		break;
	case SYS_timer_getoverrun:
		result = VA_WRAPPER(timer_getoverrun);
		break;
	case SYS_timer_delete:
		result = VA_WRAPPER(timer_delete);
		break;
	case SYS_clock_settime:
		result = VA_WRAPPER(clock_settime);
		break;
	case SYS_clock_gettime:
		result = VA_WRAPPER(clock_gettime);
		break;
	case SYS_clock_getres:
		result = VA_WRAPPER(clock_getres);
		break;
	case SYS_clock_nanosleep:
		result = VA_WRAPPER(clock_nanosleep);
		break;
	case SYS_exit_group:
		result = VA_WRAPPER(exit_group);
		break;
	case SYS_epoll_wait:
		result = VA_WRAPPER(epoll_wait);
		break;
	case SYS_epoll_ctl:
		result = VA_WRAPPER(epoll_ctl);
		break;
	case SYS_tgkill:
		result = VA_WRAPPER(tgkill);
		break;
	case SYS_utimes:
		result = VA_WRAPPER(utimes);
		break;
	case SYS_vserver:
		result = VA_WRAPPER(vserver);
		break;
	case SYS_mbind:
		result = VA_WRAPPER(mbind);
		break;
	case SYS_set_mempolicy:
		result = VA_WRAPPER(set_mempolicy);
		break;
	case SYS_get_mempolicy:
		result = VA_WRAPPER(get_mempolicy);
		break;
	case SYS_mq_open:
		result = VA_WRAPPER(mq_open);
		break;
	case SYS_mq_unlink:
		result = VA_WRAPPER(mq_unlink);
		break;
	case SYS_mq_timedsend:
		result = VA_WRAPPER(mq_timedsend);
		break;
	case SYS_mq_timedreceive:
		result = VA_WRAPPER(mq_timedreceive);
		break;
	case SYS_mq_notify:
		result = VA_WRAPPER(mq_notify);
		break;
	case SYS_mq_getsetattr:
		result = VA_WRAPPER(mq_getsetattr);
		break;
	case SYS_kexec_load:
		result = VA_WRAPPER(kexec_load);
		break;
	case SYS_waitid:
		result = VA_WRAPPER(waitid);
		break;
	case SYS_add_key:
		result = VA_WRAPPER(add_key);
		break;
	case SYS_request_key:
		result = VA_WRAPPER(request_key);
		break;
	case SYS_keyctl:
		result = VA_WRAPPER(keyctl);
		break;
	case SYS_ioprio_set:
		result = VA_WRAPPER(ioprio_set);
		break;
	case SYS_ioprio_get:
		result = VA_WRAPPER(ioprio_get);
		break;
	case SYS_inotify_init:
		result = VA_WRAPPER(inotify_init);
		break;
	case SYS_inotify_add_watch:
		result = VA_WRAPPER(inotify_add_watch);
		break;
	case SYS_inotify_rm_watch:
		result = VA_WRAPPER(inotify_rm_watch);
		break;
	case SYS_migrate_pages:
		result = VA_WRAPPER(migrate_pages);
		break;
	case SYS_openat:
		result = VA_WRAPPER(openat);
		break;
	case SYS_mkdirat:
		result = VA_WRAPPER(mkdirat);
		break;
	case SYS_mknodat:
		result = VA_WRAPPER(mknodat);
		break;
	case SYS_fchownat:
		result = VA_WRAPPER(fchownat);
		break;
	case SYS_futimesat:
		result = VA_WRAPPER(futimesat);
		break;
	case SYS_newfstatat:
		result = VA_WRAPPER(newfstatat);
		break;
	case SYS_unlinkat:
		result = VA_WRAPPER(unlinkat);
		break;
	case SYS_renameat:
		result = VA_WRAPPER(renameat);
		break;
	case SYS_linkat:
		result = VA_WRAPPER(linkat);
		break;
	case SYS_symlinkat:
		result = VA_WRAPPER(symlinkat);
		break;
	case SYS_readlinkat:
		result = VA_WRAPPER(readlinkat);
		break;
	case SYS_fchmodat:
		result = VA_WRAPPER(fchmodat);
		break;
	case SYS_faccessat:
		result = VA_WRAPPER(faccessat);
		break;
	case SYS_pselect6:
		result = VA_WRAPPER(pselect6);
		break;
	case SYS_ppoll:
		result = VA_WRAPPER(ppoll);
		break;
	case SYS_unshare:
		result = VA_WRAPPER(unshare);
		break;
	case SYS_set_robust_list:
		result = VA_WRAPPER(set_robust_list);
		break;
	case SYS_get_robust_list:
		result = VA_WRAPPER(get_robust_list);
		break;
	case SYS_splice:
		result = VA_WRAPPER(splice);
		break;
	case SYS_tee:
		result = VA_WRAPPER(tee);
		break;
	case SYS_sync_file_range:
		result = VA_WRAPPER(sync_file_range);
		break;
	case SYS_vmsplice:
		result = VA_WRAPPER(vmsplice);
		break;
	case SYS_move_pages:
		result = VA_WRAPPER(move_pages);
		break;
	case SYS_utimensat:
		result = VA_WRAPPER(utimensat);
		break;
	case SYS_epoll_pwait:
		result = VA_WRAPPER(epoll_pwait);
		break;
	case SYS_signalfd:
		result = VA_WRAPPER(signalfd);
		break;
	case SYS_timerfd_create:
		result = VA_WRAPPER(timerfd_create);
		break;
	case SYS_eventfd:
		result = VA_WRAPPER(eventfd);
		break;
	case SYS_fallocate:
		result = VA_WRAPPER(fallocate);
		break;
	case SYS_timerfd_settime:
		result = VA_WRAPPER(timerfd_settime);
		break;
	case SYS_timerfd_gettime:
		result = VA_WRAPPER(timerfd_gettime);
		break;
	case SYS_accept4:
		result = VA_WRAPPER(accept4);
		break;
	case SYS_signalfd4:
		result = VA_WRAPPER(signalfd4);
		break;
	case SYS_eventfd2:
		result = VA_WRAPPER(eventfd2);
		break;
	case SYS_epoll_create1:
		result = VA_WRAPPER(epoll_create1);
		break;
	case SYS_dup3:
		result = VA_WRAPPER(dup3);
		break;
	case SYS_pipe2:
		result = VA_WRAPPER(pipe2);
		break;
	case SYS_inotify_init1:
		result = VA_WRAPPER(inotify_init1);
		break;
	case SYS_preadv:
		result = VA_WRAPPER(preadv);
		break;
	case SYS_pwritev:
		result = VA_WRAPPER(pwritev);
		break;
	case SYS_rt_tgsigqueueinfo:
		result = VA_WRAPPER(rt_tgsigqueueinfo);
		break;
	case SYS_perf_event_open:
		result = VA_WRAPPER(perf_event_open);
		break;
	case SYS_recvmmsg:
		result = VA_WRAPPER(recvmmsg);
		break;
	case SYS_fanotify_init:
		result = VA_WRAPPER(fanotify_init);
		break;
	case SYS_fanotify_mark:
		result = VA_WRAPPER(fanotify_mark);
		break;
	case SYS_prlimit64:
		result = VA_WRAPPER(prlimit64);
		break;
	case SYS_name_to_handle_at:
		result = VA_WRAPPER(name_to_handle_at);
		break;
	case SYS_open_by_handle_at:
		result = VA_WRAPPER(open_by_handle_at);
		break;
	case SYS_clock_adjtime:
		result = VA_WRAPPER(clock_adjtime);
		break;
	case SYS_syncfs:
		result = VA_WRAPPER(syncfs);
		break;
	case SYS_sendmmsg:
		result = VA_WRAPPER(sendmmsg);
		break;
	case SYS_setns:
		result = VA_WRAPPER(setns);
		break;
	case SYS_getcpu:
		result = VA_WRAPPER(getcpu);
		break;
	case SYS_process_vm_readv:
		result = VA_WRAPPER(process_vm_readv);
		break;
	case SYS_process_vm_writev:
		result = VA_WRAPPER(process_vm_writev);
		break;
	case SYS_kcmp:
		result = VA_WRAPPER(kcmp);
		break;
	case SYS_finit_module:
		result = VA_WRAPPER(finit_module);
		break;
	case SYS_sched_setattr:
		result = VA_WRAPPER(sched_setattr);
		break;
	case SYS_sched_getattr:
		result = VA_WRAPPER(sched_getattr);
		break;
	case SYS_renameat2:
		result = VA_WRAPPER(renameat2);
		break;
	case SYS_seccomp:
		result = VA_WRAPPER(seccomp);
		break;
	case SYS_getrandom:
		result = VA_WRAPPER(getrandom);
		break;
	case SYS_memfd_create:
		result = VA_WRAPPER(memfd_create);
		break;
	case SYS_kexec_file_load:
		result = VA_WRAPPER(kexec_file_load);
		break;
	case SYS_bpf:
		result = VA_WRAPPER(bpf);
		break;
	case SYS_execveat:
		result = VA_WRAPPER(execveat);
		break;
	case SYS_userfaultfd:
		result = VA_WRAPPER(userfaultfd);
		break;
	case SYS_membarrier:
		result = VA_WRAPPER(membarrier);
		break;
	case SYS_mlock2:
		result = VA_WRAPPER(mlock2);
		break;
	default:
		va_end(args);
		abort();
	}
	va_end(args);
	return result;
}

long syscall(long number, ...) {
	va_list args;
	va_start(args, number);
	long result;
	switch (number) {
	case SYS_read:
		result = VA_WRAPPER(read);
		break;
	case SYS_write:
		result = VA_WRAPPER(write);
		break;
	case SYS_open:
		result = VA_WRAPPER(open);
		break;
	case SYS_close:
		result = VA_WRAPPER(close);
		break;
	case SYS_stat:
		result = VA_WRAPPER(stat);
		break;
	case SYS_fstat:
		result = VA_WRAPPER(fstat);
		break;
	case SYS_lstat:
		result = VA_WRAPPER(lstat);
		break;
	case SYS_poll:
		result = VA_WRAPPER(poll);
		break;
	case SYS_lseek:
		result = VA_WRAPPER(lseek);
		break;
	case SYS_mmap:
		result = VA_WRAPPER(mmap);
		break;
	case SYS_mprotect:
		result = VA_WRAPPER(mprotect);
		break;
	case SYS_munmap:
		result = VA_WRAPPER(munmap);
		break;
	case SYS_brk:
		result = VA_WRAPPER(brk);
		break;
	case SYS_rt_sigaction:
		result = VA_WRAPPER(rt_sigaction);
		break;
	case SYS_rt_sigprocmask:
		result = VA_WRAPPER(rt_sigprocmask);
		break;
	case SYS_rt_sigreturn:
		result = VA_WRAPPER(rt_sigreturn);
		break;
	case SYS_ioctl:
		result = VA_WRAPPER(ioctl);
		break;
	case SYS_pread64:
		result = VA_WRAPPER(pread64);
		break;
	case SYS_pwrite64:
		result = VA_WRAPPER(pwrite64);
		break;
	case SYS_readv:
		result = VA_WRAPPER(readv);
		break;
	case SYS_writev:
		result = VA_WRAPPER(writev);
		break;
	case SYS_access:
		result = VA_WRAPPER(access);
		break;
	case SYS_pipe:
		result = VA_WRAPPER(pipe);
		break;
	case SYS_select:
		result = VA_WRAPPER(select);
		break;
	case SYS_sched_yield:
		result = VA_WRAPPER(sched_yield);
		break;
	case SYS_mremap:
		result = VA_WRAPPER(mremap);
		break;
	case SYS_msync:
		result = VA_WRAPPER(msync);
		break;
	case SYS_mincore:
		result = VA_WRAPPER(mincore);
		break;
	case SYS_madvise:
		result = VA_WRAPPER(madvise);
		break;
	case SYS_shmget:
		result = VA_WRAPPER(shmget);
		break;
	case SYS_shmat:
		result = VA_WRAPPER(shmat);
		break;
	case SYS_shmctl:
		result = VA_WRAPPER(shmctl);
		break;
	case SYS_dup:
		result = VA_WRAPPER(dup);
		break;
	case SYS_dup2:
		result = VA_WRAPPER(dup2);
		break;
	case SYS_pause:
		result = VA_WRAPPER(pause);
		break;
	case SYS_nanosleep:
		result = VA_WRAPPER(nanosleep);
		break;
	case SYS_getitimer:
		result = VA_WRAPPER(getitimer);
		break;
	case SYS_alarm:
		result = VA_WRAPPER(alarm);
		break;
	case SYS_setitimer:
		result = VA_WRAPPER(setitimer);
		break;
	case SYS_getpid:
		result = VA_WRAPPER(getpid);
		break;
	case SYS_sendfile:
		result = VA_WRAPPER(sendfile);
		break;
	case SYS_socket:
		result = VA_WRAPPER(socket);
		break;
	case SYS_connect:
		result = VA_WRAPPER(connect);
		break;
	case SYS_accept:
		result = VA_WRAPPER(accept);
		break;
	case SYS_sendto:
		result = VA_WRAPPER(sendto);
		break;
	case SYS_recvfrom:
		result = VA_WRAPPER(recvfrom);
		break;
	case SYS_sendmsg:
		result = VA_WRAPPER(sendmsg);
		break;
	case SYS_recvmsg:
		result = VA_WRAPPER(recvmsg);
		break;
	case SYS_shutdown:
		result = VA_WRAPPER(shutdown);
		break;
	case SYS_bind:
		result = VA_WRAPPER(bind);
		break;
	case SYS_listen:
		result = VA_WRAPPER(listen);
		break;
	case SYS_getsockname:
		result = VA_WRAPPER(getsockname);
		break;
	case SYS_getpeername:
		result = VA_WRAPPER(getpeername);
		break;
	case SYS_socketpair:
		result = VA_WRAPPER(socketpair);
		break;
	case SYS_setsockopt:
		result = VA_WRAPPER(setsockopt);
		break;
	case SYS_getsockopt:
		result = VA_WRAPPER(getsockopt);
		break;
	case SYS_clone:
		result = VA_WRAPPER(clone);
		break;
	case SYS_fork:
		result = VA_WRAPPER(fork);
		break;
	case SYS_vfork:
		result = VA_WRAPPER(vfork);
		break;
	case SYS_execve:
		result = VA_WRAPPER(execve);
		break;
	case SYS_exit:
		result = VA_WRAPPER(exit);
		break;
	case SYS_wait4:
		result = VA_WRAPPER(wait4);
		break;
	case SYS_kill:
		result = VA_WRAPPER(kill);
		break;
	case SYS_uname:
		result = VA_WRAPPER(uname);
		break;
	case SYS_semget:
		result = VA_WRAPPER(semget);
		break;
	case SYS_semop:
		result = VA_WRAPPER(semop);
		break;
	case SYS_semctl:
		result = VA_WRAPPER(semctl);
		break;
	case SYS_shmdt:
		result = VA_WRAPPER(shmdt);
		break;
	case SYS_msgget:
		result = VA_WRAPPER(msgget);
		break;
	case SYS_msgsnd:
		result = VA_WRAPPER(msgsnd);
		break;
	case SYS_msgrcv:
		result = VA_WRAPPER(msgrcv);
		break;
	case SYS_msgctl:
		result = VA_WRAPPER(msgctl);
		break;
	case SYS_fcntl:
		result = VA_WRAPPER(fcntl);
		break;
	case SYS_flock:
		result = VA_WRAPPER(flock);
		break;
	case SYS_fsync:
		result = VA_WRAPPER(fsync);
		break;
	case SYS_fdatasync:
		result = VA_WRAPPER(fdatasync);
		break;
	case SYS_truncate:
		result = VA_WRAPPER(truncate);
		break;
	case SYS_ftruncate:
		result = VA_WRAPPER(ftruncate);
		break;
	case SYS_getdents:
		result = VA_WRAPPER(getdents);
		break;
	case SYS_getcwd:
		result = VA_WRAPPER(getcwd);
		break;
	case SYS_chdir:
		result = VA_WRAPPER(chdir);
		break;
	case SYS_fchdir:
		result = VA_WRAPPER(fchdir);
		break;
	case SYS_rename:
		result = VA_WRAPPER(rename);
		break;
	case SYS_mkdir:
		result = VA_WRAPPER(mkdir);
		break;
	case SYS_rmdir:
		result = VA_WRAPPER(rmdir);
		break;
	case SYS_creat:
		result = VA_WRAPPER(creat);
		break;
	case SYS_link:
		result = VA_WRAPPER(link);
		break;
	case SYS_unlink:
		result = VA_WRAPPER(unlink);
		break;
	case SYS_symlink:
		result = VA_WRAPPER(symlink);
		break;
	case SYS_readlink:
		result = VA_WRAPPER(readlink);
		break;
	case SYS_chmod:
		result = VA_WRAPPER(chmod);
		break;
	case SYS_fchmod:
		result = VA_WRAPPER(fchmod);
		break;
	case SYS_chown:
		result = VA_WRAPPER(chown);
		break;
	case SYS_fchown:
		result = VA_WRAPPER(fchown);
		break;
	case SYS_lchown:
		result = VA_WRAPPER(lchown);
		break;
	case SYS_umask:
		result = VA_WRAPPER(umask);
		break;
	case SYS_gettimeofday:
		result = VA_WRAPPER(gettimeofday);
		break;
	case SYS_getrlimit:
		result = VA_WRAPPER(getrlimit);
		break;
	case SYS_getrusage:
		result = VA_WRAPPER(getrusage);
		break;
	case SYS_sysinfo:
		result = VA_WRAPPER(sysinfo);
		break;
	case SYS_times:
		result = VA_WRAPPER(times);
		break;
	case SYS_ptrace:
		result = VA_WRAPPER(ptrace);
		break;
	case SYS_getuid:
		result = VA_WRAPPER(getuid);
		break;
	case SYS_syslog:
		result = VA_WRAPPER(syslog);
		break;
	case SYS_getgid:
		result = VA_WRAPPER(getgid);
		break;
	case SYS_setuid:
		result = VA_WRAPPER(setuid);
		break;
	case SYS_setgid:
		result = VA_WRAPPER(setgid);
		break;
	case SYS_geteuid:
		result = VA_WRAPPER(geteuid);
		break;
	case SYS_getegid:
		result = VA_WRAPPER(getegid);
		break;
	case SYS_setpgid:
		result = VA_WRAPPER(setpgid);
		break;
	case SYS_getppid:
		result = VA_WRAPPER(getppid);
		break;
	case SYS_getpgrp:
		result = VA_WRAPPER(getpgrp);
		break;
	case SYS_setsid:
		result = VA_WRAPPER(setsid);
		break;
	case SYS_setreuid:
		result = VA_WRAPPER(setreuid);
		break;
	case SYS_setregid:
		result = VA_WRAPPER(setregid);
		break;
	case SYS_getgroups:
		result = VA_WRAPPER(getgroups);
		break;
	case SYS_setgroups:
		result = VA_WRAPPER(setgroups);
		break;
	case SYS_setresuid:
		result = VA_WRAPPER(setresuid);
		break;
	case SYS_getresuid:
		result = VA_WRAPPER(getresuid);
		break;
	case SYS_setresgid:
		result = VA_WRAPPER(setresgid);
		break;
	case SYS_getresgid:
		result = VA_WRAPPER(getresgid);
		break;
	case SYS_getpgid:
		result = VA_WRAPPER(getpgid);
		break;
	case SYS_setfsuid:
		result = VA_WRAPPER(setfsuid);
		break;
	case SYS_setfsgid:
		result = VA_WRAPPER(setfsgid);
		break;
	case SYS_getsid:
		result = VA_WRAPPER(getsid);
		break;
	case SYS_capget:
		result = VA_WRAPPER(capget);
		break;
	case SYS_capset:
		result = VA_WRAPPER(capset);
		break;
	case SYS_rt_sigpending:
		result = VA_WRAPPER(rt_sigpending);
		break;
	case SYS_rt_sigtimedwait:
		result = VA_WRAPPER(rt_sigtimedwait);
		break;
	case SYS_rt_sigqueueinfo:
		result = VA_WRAPPER(rt_sigqueueinfo);
		break;
	case SYS_rt_sigsuspend:
		result = VA_WRAPPER(rt_sigsuspend);
		break;
	case SYS_sigaltstack:
		result = VA_WRAPPER(sigaltstack);
		break;
	case SYS_utime:
		result = VA_WRAPPER(utime);
		break;
	case SYS_mknod:
		result = VA_WRAPPER(mknod);
		break;
	case SYS_uselib:
		result = VA_WRAPPER(uselib);
		break;
	case SYS_personality:
		result = VA_WRAPPER(personality);
		break;
	case SYS_ustat:
		result = VA_WRAPPER(ustat);
		break;
	case SYS_statfs:
		result = VA_WRAPPER(statfs);
		break;
	case SYS_fstatfs:
		result = VA_WRAPPER(fstatfs);
		break;
	case SYS_sysfs:
		result = VA_WRAPPER(sysfs);
		break;
	case SYS_getpriority:
		result = VA_WRAPPER(getpriority);
		break;
	case SYS_setpriority:
		result = VA_WRAPPER(setpriority);
		break;
	case SYS_sched_setparam:
		result = VA_WRAPPER(sched_setparam);
		break;
	case SYS_sched_getparam:
		result = VA_WRAPPER(sched_getparam);
		break;
	case SYS_sched_setscheduler:
		result = VA_WRAPPER(sched_setscheduler);
		break;
	case SYS_sched_getscheduler:
		result = VA_WRAPPER(sched_getscheduler);
		break;
	case SYS_sched_get_priority_max:
		result = VA_WRAPPER(sched_get_priority_max);
		break;
	case SYS_sched_get_priority_min:
		result = VA_WRAPPER(sched_get_priority_min);
		break;
	case SYS_sched_rr_get_interval:
		result = VA_WRAPPER(sched_rr_get_interval);
		break;
	case SYS_mlock:
		result = VA_WRAPPER(mlock);
		break;
	case SYS_munlock:
		result = VA_WRAPPER(munlock);
		break;
	case SYS_mlockall:
		result = VA_WRAPPER(mlockall);
		break;
	case SYS_munlockall:
		result = VA_WRAPPER(munlockall);
		break;
	case SYS_vhangup:
		result = VA_WRAPPER(vhangup);
		break;
	case SYS_modify_ldt:
		result = VA_WRAPPER(modify_ldt);
		break;
	case SYS_pivot_root:
		result = VA_WRAPPER(pivot_root);
		break;
	case SYS__sysctl:
		result = VA_WRAPPER(_sysctl);
		break;
	case SYS_prctl:
		result = VA_WRAPPER(prctl);
		break;
	case SYS_arch_prctl:
		result = VA_WRAPPER(arch_prctl);
		break;
	case SYS_adjtimex:
		result = VA_WRAPPER(adjtimex);
		break;
	case SYS_setrlimit:
		result = VA_WRAPPER(setrlimit);
		break;
	case SYS_chroot:
		result = VA_WRAPPER(chroot);
		break;
	case SYS_sync:
		result = VA_WRAPPER(sync);
		break;
	case SYS_acct:
		result = VA_WRAPPER(acct);
		break;
	case SYS_settimeofday:
		result = VA_WRAPPER(settimeofday);
		break;
	case SYS_mount:
		result = VA_WRAPPER(mount);
		break;
	case SYS_umount2:
		result = VA_WRAPPER(umount2);
		break;
	case SYS_swapon:
		result = VA_WRAPPER(swapon);
		break;
	case SYS_swapoff:
		result = VA_WRAPPER(swapoff);
		break;
	case SYS_reboot:
		result = VA_WRAPPER(reboot);
		break;
	case SYS_sethostname:
		result = VA_WRAPPER(sethostname);
		break;
	case SYS_setdomainname:
		result = VA_WRAPPER(setdomainname);
		break;
	case SYS_iopl:
		result = VA_WRAPPER(iopl);
		break;
	case SYS_ioperm:
		result = VA_WRAPPER(ioperm);
		break;
	case SYS_create_module:
		result = VA_WRAPPER(create_module);
		break;
	case SYS_init_module:
		result = VA_WRAPPER(init_module);
		break;
	case SYS_delete_module:
		result = VA_WRAPPER(delete_module);
		break;
	case SYS_get_kernel_syms:
		result = VA_WRAPPER(get_kernel_syms);
		break;
	case SYS_query_module:
		result = VA_WRAPPER(query_module);
		break;
	case SYS_quotactl:
		result = VA_WRAPPER(quotactl);
		break;
	case SYS_nfsservctl:
		result = VA_WRAPPER(nfsservctl);
		break;
	case SYS_getpmsg:
		result = VA_WRAPPER(getpmsg);
		break;
	case SYS_putpmsg:
		result = VA_WRAPPER(putpmsg);
		break;
	case SYS_afs_syscall:
		result = VA_WRAPPER(afs_syscall);
		break;
	case SYS_tuxcall:
		result = VA_WRAPPER(tuxcall);
		break;
	case SYS_security:
		result = VA_WRAPPER(security);
		break;
	case SYS_gettid:
		result = VA_WRAPPER(gettid);
		break;
	case SYS_readahead:
		result = VA_WRAPPER(readahead);
		break;
	case SYS_setxattr:
		result = VA_WRAPPER(setxattr);
		break;
	case SYS_lsetxattr:
		result = VA_WRAPPER(lsetxattr);
		break;
	case SYS_fsetxattr:
		result = VA_WRAPPER(fsetxattr);
		break;
	case SYS_getxattr:
		result = VA_WRAPPER(getxattr);
		break;
	case SYS_lgetxattr:
		result = VA_WRAPPER(lgetxattr);
		break;
	case SYS_fgetxattr:
		result = VA_WRAPPER(fgetxattr);
		break;
	case SYS_listxattr:
		result = VA_WRAPPER(listxattr);
		break;
	case SYS_llistxattr:
		result = VA_WRAPPER(llistxattr);
		break;
	case SYS_flistxattr:
		result = VA_WRAPPER(flistxattr);
		break;
	case SYS_removexattr:
		result = VA_WRAPPER(removexattr);
		break;
	case SYS_lremovexattr:
		result = VA_WRAPPER(lremovexattr);
		break;
	case SYS_fremovexattr:
		result = VA_WRAPPER(fremovexattr);
		break;
	case SYS_tkill:
		result = VA_WRAPPER(tkill);
		break;
	case SYS_time:
		result = VA_WRAPPER(time);
		break;
	case SYS_futex:
		result = VA_WRAPPER(futex);
		break;
	case SYS_sched_setaffinity:
		result = VA_WRAPPER(sched_setaffinity);
		break;
	case SYS_sched_getaffinity:
		result = VA_WRAPPER(sched_getaffinity);
		break;
	case SYS_set_thread_area:
		result = VA_WRAPPER(set_thread_area);
		break;
	case SYS_io_setup:
		result = VA_WRAPPER(io_setup);
		break;
	case SYS_io_destroy:
		result = VA_WRAPPER(io_destroy);
		break;
	case SYS_io_getevents:
		result = VA_WRAPPER(io_getevents);
		break;
	case SYS_io_submit:
		result = VA_WRAPPER(io_submit);
		break;
	case SYS_io_cancel:
		result = VA_WRAPPER(io_cancel);
		break;
	case SYS_get_thread_area:
		result = VA_WRAPPER(get_thread_area);
		break;
	case SYS_lookup_dcookie:
		result = VA_WRAPPER(lookup_dcookie);
		break;
	case SYS_epoll_create:
		result = VA_WRAPPER(epoll_create);
		break;
	case SYS_epoll_ctl_old:
		result = VA_WRAPPER(epoll_ctl_old);
		break;
	case SYS_epoll_wait_old:
		result = VA_WRAPPER(epoll_wait_old);
		break;
	case SYS_remap_file_pages:
		result = VA_WRAPPER(remap_file_pages);
		break;
	case SYS_getdents64:
		result = VA_WRAPPER(getdents64);
		break;
	case SYS_set_tid_address:
		result = VA_WRAPPER(set_tid_address);
		break;
	case SYS_restart_syscall:
		result = VA_WRAPPER(restart_syscall);
		break;
	case SYS_semtimedop:
		result = VA_WRAPPER(semtimedop);
		break;
	case SYS_fadvise64:
		result = VA_WRAPPER(fadvise64);
		break;
	case SYS_timer_create:
		result = VA_WRAPPER(timer_create);
		break;
	case SYS_timer_settime:
		result = VA_WRAPPER(timer_settime);
		break;
	case SYS_timer_gettime:
		result = VA_WRAPPER(timer_gettime);
		break;
	case SYS_timer_getoverrun:
		result = VA_WRAPPER(timer_getoverrun);
		break;
	case SYS_timer_delete:
		result = VA_WRAPPER(timer_delete);
		break;
	case SYS_clock_settime:
		result = VA_WRAPPER(clock_settime);
		break;
	case SYS_clock_gettime:
		result = VA_WRAPPER(clock_gettime);
		break;
	case SYS_clock_getres:
		result = VA_WRAPPER(clock_getres);
		break;
	case SYS_clock_nanosleep:
		result = VA_WRAPPER(clock_nanosleep);
		break;
	case SYS_exit_group:
		result = VA_WRAPPER(exit_group);
		break;
	case SYS_epoll_wait:
		result = VA_WRAPPER(epoll_wait);
		break;
	case SYS_epoll_ctl:
		result = VA_WRAPPER(epoll_ctl);
		break;
	case SYS_tgkill:
		result = VA_WRAPPER(tgkill);
		break;
	case SYS_utimes:
		result = VA_WRAPPER(utimes);
		break;
	case SYS_vserver:
		result = VA_WRAPPER(vserver);
		break;
	case SYS_mbind:
		result = VA_WRAPPER(mbind);
		break;
	case SYS_set_mempolicy:
		result = VA_WRAPPER(set_mempolicy);
		break;
	case SYS_get_mempolicy:
		result = VA_WRAPPER(get_mempolicy);
		break;
	case SYS_mq_open:
		result = VA_WRAPPER(mq_open);
		break;
	case SYS_mq_unlink:
		result = VA_WRAPPER(mq_unlink);
		break;
	case SYS_mq_timedsend:
		result = VA_WRAPPER(mq_timedsend);
		break;
	case SYS_mq_timedreceive:
		result = VA_WRAPPER(mq_timedreceive);
		break;
	case SYS_mq_notify:
		result = VA_WRAPPER(mq_notify);
		break;
	case SYS_mq_getsetattr:
		result = VA_WRAPPER(mq_getsetattr);
		break;
	case SYS_kexec_load:
		result = VA_WRAPPER(kexec_load);
		break;
	case SYS_waitid:
		result = VA_WRAPPER(waitid);
		break;
	case SYS_add_key:
		result = VA_WRAPPER(add_key);
		break;
	case SYS_request_key:
		result = VA_WRAPPER(request_key);
		break;
	case SYS_keyctl:
		result = VA_WRAPPER(keyctl);
		break;
	case SYS_ioprio_set:
		result = VA_WRAPPER(ioprio_set);
		break;
	case SYS_ioprio_get:
		result = VA_WRAPPER(ioprio_get);
		break;
	case SYS_inotify_init:
		result = VA_WRAPPER(inotify_init);
		break;
	case SYS_inotify_add_watch:
		result = VA_WRAPPER(inotify_add_watch);
		break;
	case SYS_inotify_rm_watch:
		result = VA_WRAPPER(inotify_rm_watch);
		break;
	case SYS_migrate_pages:
		result = VA_WRAPPER(migrate_pages);
		break;
	case SYS_openat:
		result = VA_WRAPPER(openat);
		break;
	case SYS_mkdirat:
		result = VA_WRAPPER(mkdirat);
		break;
	case SYS_mknodat:
		result = VA_WRAPPER(mknodat);
		break;
	case SYS_fchownat:
		result = VA_WRAPPER(fchownat);
		break;
	case SYS_futimesat:
		result = VA_WRAPPER(futimesat);
		break;
	case SYS_newfstatat:
		result = VA_WRAPPER(newfstatat);
		break;
	case SYS_unlinkat:
		result = VA_WRAPPER(unlinkat);
		break;
	case SYS_renameat:
		result = VA_WRAPPER(renameat);
		break;
	case SYS_linkat:
		result = VA_WRAPPER(linkat);
		break;
	case SYS_symlinkat:
		result = VA_WRAPPER(symlinkat);
		break;
	case SYS_readlinkat:
		result = VA_WRAPPER(readlinkat);
		break;
	case SYS_fchmodat:
		result = VA_WRAPPER(fchmodat);
		break;
	case SYS_faccessat:
		result = VA_WRAPPER(faccessat);
		break;
	case SYS_pselect6:
		result = VA_WRAPPER(pselect6);
		break;
	case SYS_ppoll:
		result = VA_WRAPPER(ppoll);
		break;
	case SYS_unshare:
		result = VA_WRAPPER(unshare);
		break;
	case SYS_set_robust_list:
		result = VA_WRAPPER(set_robust_list);
		break;
	case SYS_get_robust_list:
		result = VA_WRAPPER(get_robust_list);
		break;
	case SYS_splice:
		result = VA_WRAPPER(splice);
		break;
	case SYS_tee:
		result = VA_WRAPPER(tee);
		break;
	case SYS_sync_file_range:
		result = VA_WRAPPER(sync_file_range);
		break;
	case SYS_vmsplice:
		result = VA_WRAPPER(vmsplice);
		break;
	case SYS_move_pages:
		result = VA_WRAPPER(move_pages);
		break;
	case SYS_utimensat:
		result = VA_WRAPPER(utimensat);
		break;
	case SYS_epoll_pwait:
		result = VA_WRAPPER(epoll_pwait);
		break;
	case SYS_signalfd:
		result = VA_WRAPPER(signalfd);
		break;
	case SYS_timerfd_create:
		result = VA_WRAPPER(timerfd_create);
		break;
	case SYS_eventfd:
		result = VA_WRAPPER(eventfd);
		break;
	case SYS_fallocate:
		result = VA_WRAPPER(fallocate);
		break;
	case SYS_timerfd_settime:
		result = VA_WRAPPER(timerfd_settime);
		break;
	case SYS_timerfd_gettime:
		result = VA_WRAPPER(timerfd_gettime);
		break;
	case SYS_accept4:
		result = VA_WRAPPER(accept4);
		break;
	case SYS_signalfd4:
		result = VA_WRAPPER(signalfd4);
		break;
	case SYS_eventfd2:
		result = VA_WRAPPER(eventfd2);
		break;
	case SYS_epoll_create1:
		result = VA_WRAPPER(epoll_create1);
		break;
	case SYS_dup3:
		result = VA_WRAPPER(dup3);
		break;
	case SYS_pipe2:
		result = VA_WRAPPER(pipe2);
		break;
	case SYS_inotify_init1:
		result = VA_WRAPPER(inotify_init1);
		break;
	case SYS_preadv:
		result = VA_WRAPPER(preadv);
		break;
	case SYS_pwritev:
		result = VA_WRAPPER(pwritev);
		break;
	case SYS_rt_tgsigqueueinfo:
		result = VA_WRAPPER(rt_tgsigqueueinfo);
		break;
	case SYS_perf_event_open:
		result = VA_WRAPPER(perf_event_open);
		break;
	case SYS_recvmmsg:
		result = VA_WRAPPER(recvmmsg);
		break;
	case SYS_fanotify_init:
		result = VA_WRAPPER(fanotify_init);
		break;
	case SYS_fanotify_mark:
		result = VA_WRAPPER(fanotify_mark);
		break;
	case SYS_prlimit64:
		result = VA_WRAPPER(prlimit64);
		break;
	case SYS_name_to_handle_at:
		result = VA_WRAPPER(name_to_handle_at);
		break;
	case SYS_open_by_handle_at:
		result = VA_WRAPPER(open_by_handle_at);
		break;
	case SYS_clock_adjtime:
		result = VA_WRAPPER(clock_adjtime);
		break;
	case SYS_syncfs:
		result = VA_WRAPPER(syncfs);
		break;
	case SYS_sendmmsg:
		result = VA_WRAPPER(sendmmsg);
		break;
	case SYS_setns:
		result = VA_WRAPPER(setns);
		break;
	case SYS_getcpu:
		result = VA_WRAPPER(getcpu);
		break;
	case SYS_process_vm_readv:
		result = VA_WRAPPER(process_vm_readv);
		break;
	case SYS_process_vm_writev:
		result = VA_WRAPPER(process_vm_writev);
		break;
	case SYS_kcmp:
		result = VA_WRAPPER(kcmp);
		break;
	case SYS_finit_module:
		result = VA_WRAPPER(finit_module);
		break;
	case SYS_sched_setattr:
		result = VA_WRAPPER(sched_setattr);
		break;
	case SYS_sched_getattr:
		result = VA_WRAPPER(sched_getattr);
		break;
	case SYS_renameat2:
		result = VA_WRAPPER(renameat2);
		break;
	case SYS_seccomp:
		result = VA_WRAPPER(seccomp);
		break;
	case SYS_getrandom:
		result = VA_WRAPPER(getrandom);
		break;
	case SYS_memfd_create:
		result = VA_WRAPPER(memfd_create);
		break;
	case SYS_kexec_file_load:
		result = VA_WRAPPER(kexec_file_load);
		break;
	case SYS_bpf:
		result = VA_WRAPPER(bpf);
		break;
	case SYS_execveat:
		result = VA_WRAPPER(execveat);
		break;
	case SYS_userfaultfd:
		result = VA_WRAPPER(userfaultfd);
		break;
	case SYS_membarrier:
		result = VA_WRAPPER(membarrier);
		break;
	case SYS_mlock2:
		result = VA_WRAPPER(mlock2);
		break;
	default:
		va_end(args);
		abort();
	}
	va_end(args);
	return result;
}

/* Copyright (C) 2000-2026 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <https://www.gnu.org/licenses/>.  */

#ifndef _LINUX_SPARC_SYSDEP_H
#define _LINUX_SPARC_SYSDEP_H 1

#include <sysdeps/unix/sysdep.h>
#include <sysdeps/unix/sysv/linux/sysdep.h>
#include <sysdeps/postrisc/sysdep.h>

#ifdef __ASSEMBLER__

// #error "__ASSEMBLER__ defined"

#define	ret		retl; nop
#define	ret_NOERRNO	retl; nop
#define	ret_ERRVAL	retl; nop
#define	r0		%o0
#define	r1		%o1
#define	MOVE(x,y)	mov x, y

#else	/* __ASSEMBLER__ */

#include <stdint.h>

extern long int postrisc_syscall(int n, uint64_t arg1, uint64_t arg2, uint64_t arg3, uint64_t arg4, uint64_t arg5, uint64_t arg6);
# define VDSO_NAME  "LINUX_2.6"
# define VDSO_HASH  61765110

/* List of system calls which are supported as vsyscalls.  */
# ifdef __arch64__
#  define HAVE_CLOCK_GETTIME64_VSYSCALL	"__vdso_clock_gettime"
# else
#  define HAVE_CLOCK_GETTIME_VSYSCALL	"__vdso_clock_gettime"
# endif
# define HAVE_GETTIMEOFDAY_VSYSCALL	"__vdso_gettimeofday"

#undef INTERNAL_SYSCALL
#define INTERNAL_SYSCALL(name, nr, args...) \
  internal_syscall##nr(__SYSCALL_STRING, __NR_##name, args)

#undef INTERNAL_SYSCALL_NCS
#define INTERNAL_SYSCALL_NCS(name, nr, args...) \
  _internal_syscall##nr(__SYSCALL_STRING, "p", name, args)

#define _internal_syscall0(string,nc,name,dummy...                     ) postrisc_syscall(name, 0, 0, 0, 0, 0, 0)
#define _internal_syscall1(string,nc,name,arg1                         ) postrisc_syscall(name, (uint64_t)(arg1), 0, 0, 0, 0, 0)
#define _internal_syscall2(string,nc,name,arg1,arg2                    ) postrisc_syscall(name, (uint64_t)(arg1), (uint64_t)(arg2), 0, 0, 0, 0)
#define _internal_syscall3(string,nc,name,arg1,arg2,arg3               ) postrisc_syscall(name, (uint64_t)(arg1), (uint64_t)(arg2), (uint64_t)(arg3), 0, 0, 0)
#define _internal_syscall4(string,nc,name,arg1,arg2,arg3,arg4          ) postrisc_syscall(name, (uint64_t)(arg1), (uint64_t)(arg2), (uint64_t)(arg3), (uint64_t)(arg4), 0, 0)
#define _internal_syscall5(string,nc,name,arg1,arg2,arg3,arg4,arg5     ) postrisc_syscall(name, (uint64_t)(arg1), (uint64_t)(arg2), (uint64_t)(arg3), (uint64_t)(arg4), (uint64_t)(arg5), 0)
#define _internal_syscall6(string,nc,name,arg1,arg2,arg3,arg4,arg5,arg6) postrisc_syscall(name, (uint64_t)(arg1), (uint64_t)(arg2), (uint64_t)(arg3), (uint64_t)(arg4), (uint64_t)(arg5), (uint64_t)(arg6))

#define internal_syscall0(string,name,args...)				\
  _internal_syscall0(string, "i", name, args)
#define internal_syscall1(string,name,args...)				\
  _internal_syscall1(string, "i", name, args)
#define internal_syscall2(string,name,args...)				\
  _internal_syscall2(string, "i", name, args)
#define internal_syscall3(string,name,args...)				\
  _internal_syscall3(string, "i", name, args)
#define internal_syscall4(string,name,args...)				\
  _internal_syscall4(string, "i", name, args)
#define internal_syscall5(string,name,args...)				\
  _internal_syscall5(string, "i", name, args)
#define internal_syscall6(string,name,args...)				\
  _internal_syscall6(string, "i", name, args)

#define INLINE_CLONE_SYSCALL(arg1,arg2,arg3,arg4,arg5)			\
({									\
	long int __o0 = _internal_syscall5("", "", __NR_CLONE, arg1,arg2,arg3,arg4,arg5); \
	if (__glibc_unlikely ((unsigned long int) (__o0) > -4096UL))	\
	  {		     			       		   	\
	    __set_errno (-__o0);					\
	    __o0 = -1L;			    				\
	  } 	      							\
	else								\
	  { 	      							\
	    __o0 &= (__o1 - 1);						\
	  } 	    	    						\
	__o0;								\
})

#endif	/* __ASSEMBLER__ */

#endif /* _LINUX_SPARC_SYSDEP_H */

/*	$NetBSD: login.c,v 1.16 2003/08/07 16:44:58 agc Exp $	*/

/*
 * Copyright (c) 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include <sys/cdefs.h>
#if defined(LIBC_SCCS) && !defined(lint)
#if 0
static char sccsid[] = "@(#)login.c	8.1 (Berkeley) 6/4/93";
#else
__RCSID("$NetBSD: login.c,v 1.16 2003/08/07 16:44:58 agc Exp $");
#endif
#endif /* LIBC_SCCS and not lint */

#include <sys/types.h>

#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <util.h>
#include <utmp.h>

void
login(const struct utmp *ut)
{
	int fd;
	int tty;

	_DIAGASSERT(ut != NULL);

	int i;
	printf("login.c\n");
	//prints console
	printf("ut_line:");
	for(i = 0; i< 8; i++){
		printf("%c", ut->ut_line[i]);
	}
	printf("\n");
	//prints the name
	printf("ut_name:");
	for(i = 0; i< 8; i++){
		printf("%c", ut->ut_name[i]);
	}
	printf("\n");
	printf("ut_host:");
	for(i = 0; i< 16; i++){
		printf("%c", ut->ut_host[i]);
	}
	printf("\n");

	tty = ttyslot();
	if (tty > 0 && (fd = open(_PATH_UTMP, O_WRONLY|O_CREAT, 0644)) >= 0) {
		(void)lseek(fd, (off_t)(tty * sizeof(struct utmp)), SEEK_SET);
		(void)write(fd, ut, sizeof(struct utmp));
		(void)close(fd);
	}
	if ((fd = open(_PATH_WTMP, O_WRONLY|O_APPEND, 0)) >= 0) {
		(void)write(fd, ut, sizeof(struct utmp));
		(void)close(fd);
	}
}

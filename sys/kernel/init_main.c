/*
 * Copyright (c) 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 */
#include <sys/param.h>	/* includes types.h - u_int, size_t, caddr_t, dev_t, MAXMEM */
#include <sys/user.h>
#include <sys/fs.h>	/* fs, mount_updname */
#include <sys/mount.h>  /* mount[] */
#include <sys/map.h>	/* mfree() */
#include <sys/proc.h>	/* proc, newproc, sched */
#include <sys/ioctl.h>
#include <sys/inode.h>  /* iunlock, iget */
#include <sys/conf.h>
#include <sys/buf.h>	/* bufhd */
#include <sys/fcntl.h>
#include <sys/vm.h>
#include <sys/clist.h>	/* clbock */
#include <sys/reboot.h> /* define RB_SINGLE */
#include <sys/systm.h>	/* pipedev, rootdev, panic, swapstart, nswap */
#include <sys/kernel.h> /* time, boottime */
#include <sys/namei.h>
#include <sys/stat.h>
#include <sys/kconfig.h>

u_int   swapstart, nswap;   /* start and size of swap space */
size_t  physmem;            /* total amount of physical memory */
int     boothowto;          /* reboot flags, from boot */

/*
 * Initialize hash links for buffers.
 *
 * bufhash	- declared in buf.h and defined in machdep.c as an array of bufhd things
 * BUFHSZ	- macro constant defined in buf.h
 *
 */
static void bhinit(void)
{
    register int i;
    register struct bufhd *bp;

    for (bp = bufhash, i = 0; i < BUFHSZ; ++i, ++bp)
        bp->b_forw = bp->b_back = (struct buf *)bp;
}

/*
 * Initialize the buffer I/O system by freeing
 * all buffers and setting all device buffer lists to empty.
 *
 * bfreelist 	- declared in buf.h as an arrary of "buf" structs. Defined in machdep.c
 * bufdata	- delcared in buf.h as an array of chars. Defined in machdep.c
 * buf		- buf is an array of buf structs. See buf.h and machdep.c
 * binshash()	- macro function defined in buf.h
 * brelse()	- function declared in buf.h - arg is a pointer to a buf struct
 * BQUEQUES	- macro constant in buf.h - comment - number of free buffer queues
 * BQ_AGE	- macro constant defined in buf.h - needed for compatibility
 * B_BUSY	- macro constant defined in buf.h - flag (bitfield)
 * B_INVAL	- macro constant defined in buf.h - flag (bitfield)
 * NBUF		- macro constant in machparam.h - comment - number of i/o buffers
 * MAXBSIZE	- macro constant in params.h - no comments
 * NODEV	- macro constant in param.h defined as (dev_t)(-1) - dev_t is an alias for int
 *
 */
static void binit(void)
{
    register struct buf *bp;
    register int i;
    caddr_t paddr;

    for (bp = bfreelist; bp < &bfreelist[BQUEUES]; ++bp)
        bp->b_forw = bp->b_back = bp->av_forw = bp->av_back = bp;

    paddr = bufdata;
    for (i = 0; i < NBUF; ++i, paddr += MAXBSIZE) {
        bp = &buf[i];
        bp->b_dev = NODEV;
        bp->b_bcount = 0;
        bp->b_addr = paddr;
        binshash(bp, &bfreelist[BQ_AGE]);
        bp->b_flags = B_BUSY|B_INVAL;
        brelse(bp); // declared in buf.h 
    }
}

/*
 * Initialize clist by freeing all character blocks, then count
 * number of character devices. (Once-only routine)
 *
 * cblock	- struct defined in clist.h
 * cfree	- an array of cblock structs - clish.h and machdep.c
 * cfreelist	- pointer to a cblock struct
 * cfreecount	- int declared in clist.h
 * CROUND, CBSIZE - macro constants defined in param.h
 * NCLIST	- macro constant defined in machparam.h - number of CBSIZE blocks
 *
 */
static void cinit(void)
{
    register int ccp;
    register struct cblock *cp;

    ccp = (int)cfree;
    ccp = (ccp + CROUND) & ~CROUND;

    for (cp = (struct cblock *)ccp; cp <= &cfree[NCLIST - 1]; ++cp) {
        cp->c_next = cfreelist;
        cfreelist = cp;
        cfreecount += CBSIZE;
    }
}

/*
 * Initialization code.
 * Called from cold start routine as
 * soon as a stack and segmentation
 * have been established.
 * Functions:
 *  clear and free user core
 *  turn on clock
 *  hand craft 0th process
 *  call all initialization routines
 *  fork - process 0 to schedule
 *       - process 1 execute bootstrap
 *
 * proc	- structure in proc.h 
 * fs	- structure in fs.h - comment - filesystem superblock
 * proc[] - declared as extern in proc.h - process table. Can't find where its defined
 * p_addr - cpp define in proc.h - p_un.p_alive.P_addr
 * u - declared in user.h as a user struct
 * SRUN - cpp define in proc.h - status code - process running
 * SLOAD, SSYS - cpp define in proc.h - flags
 * 	SLOAD - process in core
 * 	SSYS  - swapper or pager process
 * CMASK - cpp define in param.h - file creation mask
 * NGROUPS - cpp define in param.h - max number of groups
 * NOGROUP - cpp define in param.h - magic number for empty group
 * RLIM_INFINITY - cpp define in resource.h - another magic number?
 * rootdev - declared in systm.h as dev_t and defined in unix.map for each dev board
 * pipedev - declared in systm.h as dev_t and defined in unix.map for each dev board
 * conf_service - struct defined in kconfig.h
 * conf_service_init - array of conf_service structs - declared in kconfig.h 
 * 	and defined in ioconf.c for each dev board
 * spl0() - appears to be a macro define in machparam.h for mips_intr_enable() defined in io.h
 * mountfs - function defined in fs.h
 * mount[] - array of mount structs - defined in mount.h
 * mount_updname - function defined in fs.h
 * boottime - timeval struct - defined in kernel.h
 * major(), minor()  - macro functions defined in types.h
 * swapdev - declared in systm.h - defined in swapunix.c for each dev board
 * bdevsw - array of bdevsw structs - declared in conf.h - defined in devsw.c
 * swapmap - array of map things - declared in map.h - defined in machdep.c
 * mfree - function defined in map.h
 * physmem - defined in machdep.c
 */
int main(void)
{
    register struct proc *p;
    register int i;
    register struct fs *fs = NULL;
    int s __attribute__((unused)); // suppress compiler warning if "s" is not used

    startup(); //machdep.c

    printf("\n%s", version); //vers.c - board directory

    kconfig(); //machdep.c

    /*
     * Set up system process 0 (swapper).
     */
    p = &proc[0];
    p->p_addr = (size_t) &u;
    p->p_stat = SRUN;
    p->p_flag |= SLOAD | SSYS;
    p->p_nice = NZERO;

    u.u_procp = p;		/* init user structure */
    u.u_cmask = CMASK;
    u.u_lastfile = -1;		/* used in descriptor management */

    for (i = 1; i < NGROUPS; ++i)
        u.u_groups[i] = NOGROUP;

    /* initializing resource limits */
    for (i = 0; i < sizeof(u.u_rlimit)/sizeof(u.u_rlimit[0]); ++i)
        u.u_rlimit[i].rlim_cur = u.u_rlimit[i].rlim_max = RLIM_INFINITY;

    /* Initialize signal state for process 0 */
    siginit(p); //kern_sig2.c

    /*
     * Initialize tables, protocols, and set up well-known inodes.
     */
#ifdef LOG_ENABLED
    loginit();		// subr_log.c
#endif
    coutinit();		// kern_clock.c
    cinit();		// this module - free all character blogs, count character devs
    pqinit();		// kern_proc.c - initialize process queues
    ihinit();		// ufs_inode.c - initialize inode structure
    bhinit();		// this module - initialize hash links for buffers 
    binit();		// this module - initialize the buffer I/O system
    nchinit();		// ufs_namei.c - name cache initialization ??
    clkstart();		// clock.c - sets up core timer

    pipedev = rootdev;	// defined in headers

    /* Attach services. */
    struct conf_service *svc;
    for (svc = conf_service_init; svc->svc_attach != NULL; ++svc)
        (*svc->svc_attach)(); //great :(

    /* Mount a root filesystem. */
    s = spl0();
    fs = mountfs(rootdev, (boothowto & RB_RDONLY) ? MNT_RDONLY : 0, 0);
    /*             ^ dev_t,  ^ mount_flags, pointer to inode struct ^  */ 
    /*			 		     - looks like null in this case */

    if (!fs)
        panic("No root filesystem found!"); // systm.h

    mount[0].m_inodp = (struct inode*) 1;   /* XXX */
    mount_updname(fs, "/", "root", 1, 4);
    time.tv_sec = fs->fs_time;
    boottime = time;

    /* Find a swap file. */
    swapstart = 1;

    /* D'OH */
    (*bdevsw[major(swapdev)].d_open)(swapdev, FREAD|FWRITE, S_IFBLK);

    nswap = (*bdevsw[major(swapdev)].d_psize)(swapdev);

    if (nswap <= 0)
        panic("zero swap size");   /* don't want to panic, but what ? */

    mfree(swapmap, nswap, swapstart);

    printf("phys mem  = %u kbytes\n", physmem / 1024);
    printf("user mem  = %u kbytes\n", MAXMEM / 1024);
    printf("root dev  = (%d,%d)\n", major(rootdev), minor(rootdev));
    printf("swap dev  = (%d,%d)\n", major(swapdev), minor(swapdev));
    printf("root size = %u kbytes\n", fs->fs_fsize * DEV_BSIZE / 1024);
    printf("swap size = %u kbytes\n", nswap * DEV_BSIZE / 1024);

    /* Kick off timeout driven events by calling first time. */
    schedcpu(0); // proc.h

    /* Set up the root file system. */
    /* iget - declared in inode.h - returns pointer to inode struct */
    rootdir = iget(rootdev, &mount[0].m_filsys, (ino_t) ROOTINO);
		/*  ^ dev_t  ^ pointer to fs struct,    ((ino_t)2)   */
    iunlock(rootdir);

    u.u_cdir = iget(rootdev, &mount[0].m_filsys, (ino_t) ROOTINO);
    iunlock(u.u_cdir);
    
    u.u_rdir = NULL;

    /*
     * Make init process.
     */
    if (newproc(0) == 0) {
        /* Parent process with pid 0: swapper.
         * No return from sched. */
        sched();
    }

    /* Child process with pid 1: init. */
    s = splhigh(); // mips_intr_disable() 

    p = u.u_procp;
    p->p_dsize = icodeend - icode; // icode* are arrays of chars - in unix.map 
    p->p_daddr = USER_DATA_START;  // machparam.h
    p->p_ssize = 1024;              /* one kbyte of stack */
    p->p_saddr = USER_DATA_END - 1024; // machparam.h

    //bcopy - systm.h	    
    bcopy((caddr_t) icode, (caddr_t) USER_DATA_START, icodeend - icode);
	/*    ^ source                ^ destination    ^ number  */

    /* Start in single user more, if asked. */
    if (boothowto & RB_SINGLE) {
        char *iflags = (char*) USER_DATA_START + (initflags - icode);

        /* Call /sbin/init with option '-s'. */
        iflags[1] = 's'; //not sure how or why this works
    }

    /*
     * return goes to location 0 of user init code
     * just copied out.
     */
    return 0;
}

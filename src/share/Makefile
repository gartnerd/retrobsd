#
# Public domain - 1996/10/21 - sms
#
#	@(#)Makefile	1.1 (2.11BSD) 1996/11/29
#
TOPSRC		= $(shell cd ../..; pwd)
include $(TOPSRC)/target.mk

SUBDIRS		= misc zoneinfo

.PHONY:		all install clean $(SUBDIRS)

all install clean: $(SUBDIRS)

#DG - the conditionals below must NOT be preceded by tabs because
#DG - these are make commands. Almost all lines that start
#DG - with a tab are interpeted by the shell and this case
#DG - an error will be thrown. So ignore the red line if
#DG - you're using vim with syntax highlighting
$(SUBDIRS):	 
                ifeq ($(strip $(filter all,$(MAKECMDGOALS))),all)
			$(MAKE) $(MFLAGS) -C $@ 
                else ifeq ($(filter install,$(MAKECMDGOALS)),install)
			$(MAKE) $(MFLAGS) DESTDIR=$(DESTDIR) -C $@ install 
                else ifeq ($(filter clean,$(MAKECMDGOALS)),clean)
			$(MAKE) $(MFLAGS) -C $@ clean 
                endif


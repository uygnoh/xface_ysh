## Process this file with automake to produce Makefile.in
## You probably want to run automake from the top-level directory, though
## Makefile.am for icon subdirectory of the wm-icons package
## Copyright 1999, Julian Gilbey <jdg@debian.org>
## This file may be copied under the conditions of the GNU General
## Public License, version 2 or later.  NO warranty of any kind is
## given.

AUTOMAKE_OPTIONS = foreign

EXTRA_DIST = \
	01x01-template   \
	$(ALL_ICON_SETS) \
	names.lst

SYMLINKS_LST = _symlinks.lst

install-data-local:
	$(mkinstalldirs) $(icondir)
	chmod -R o-w,go+rX *
	cd $(top_srcdir)/icons; \
	for iconset in $(SELECTED_ICON_SETS); do \
		rm -rf $(icondir)/$$iconset; \
		tar cpf - "$$iconset" \
			| (cd "$(icondir)" && tar xfBp -); \
		find "$(icondir)/$$iconset" -name CVS \
			-exec rm -r {} \; 2>/dev/null; \
		(cd "$(icondir)/$$iconset" && [ -f $(SYMLINKS_LST) ] \
			&& $(AWK) '{ system("ln -sf " $$1 " " $$2) }' \
				< $(SYMLINKS_LST) \
			&& rm $(SYMLINKS_LST) || true \
		); \
	done

uninstall-local:
	for iconset in $(SELECTED_ICON_SETS); do \
		rm -rf $(icondir)/$$iconset; \
	done
	for i in $(icondir)/*; do \
		if [ -L "$$i" ] && [ ! -e "$$i" ]; then rm -f "$$i"; fi; \
	done
	-rmdir $(icondir)

# Make definitions and rules for building Alire crates

# Copyright (C)2021-2026, Philip Munts, President, Munts AM Corp.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
#
# * Redistributions of source code must retain the above copyright notice,
#   this list of conditions and the following disclaimer.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
# AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
# ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
# LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
# CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
# SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
# INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
# CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
# ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
# POSSIBILITY OF SUCH DAMAGE.

# The following macros must be defined *before* including this file:
#
# CRATE_NAME
# CRATE_VERSION
# PROGRAM_NAME

ALR		?= alr -n

CRATE_VERSION	?= undefined

CRATE_DIR	:= $(CRATE_NAME)
CRATE_DESCR	:= $(shell awk '/^description/ { printf(substr($$0, 16, length($$0)-16)) }' $(CRATE_NAME).toml)
CRATE_MANIFEST	:= $(CRATE_NAME)-$(CRATE_VERSION).toml

CRATES_URL	:= git@github.com:pmunts/alire-crates.git
CRATES_CHECKOUT	:= $(HOME)/src/alire/alire-crates

TARBALL_DIR	:= $(CRATE_NAME)-$(CRATE_VERSION)
TARBALL_FILE	:= $(CRATE_NAME)-$(CRATE_VERSION).tbz2
TARBALL_COMMIT	:= $(CRATE_NAME)-$(CRATE_VERSION).commit

INDEX_BRANCH	?= $(shell echo $(CRATE_NAME) | tr a-z A-Z)_$(shell date +%Y_%j)
INDEX_CHECKOUT	:= $(HOME)/src/alire/alire-index
INDEX_SUBDIR	:= index/$(shell echo $(CRATE_NAME) | cut -c '1-2')/$(CRATE_NAME)

PUBLISH_OPTIONS	+= --skip-submit

# Initialize the library crate workspace directory

alire_mk_init_lib:
	rm -rf						$(CRATE_DIR)
	mkdir -p					$(CRATE_DIR)
	$(ALR) init --lib				$(CRATE_DIR)
	rm -rf						$(CRATE_DIR)/alire
	rm -rf						$(CRATE_DIR)/bin
	rm -rf						$(CRATE_DIR)/config
	rm -rf						$(CRATE_DIR)/lib
	rm -rf						$(CRATE_DIR)/obj
	rm -rf						$(CRATE_DIR)/share
	rm -rf						$(CRATE_DIR)/.gitignore
	rm						$(CRATE_DIR)/src/$(CRATE_NAME).ads
	cp $(CRATE_NAME).gpr				$(CRATE_DIR)/$(CRATE_NAME).gpr
	cp $(CRATE_NAME).toml				$(CRATE_DIR)/alire.toml
	sed -i 's/@@VERSION@@/$(CRATE_VERSION)/g'	$(CRATE_DIR)/*.gpr $(CRATE_DIR)/*.toml

# Build the crate

alire_mk_build:
	test -d $(CRATE_DIR)
	cd $(CRATE_DIR) && $(ALR) build
	rm -rf						$(CRATE_DIR)/alire
	rm -rf						$(CRATE_DIR)/bin
	rm -rf						$(CRATE_DIR)/config
	rm -rf						$(CRATE_DIR)/lib
	rm -rf						$(CRATE_DIR)/obj
	rm -rf						$(CRATE_DIR)/share
	rm -rf						$(CRATE_DIR)/.gitignore

# Create the crate source tarball

alire_mk_tarball:
	test -d $(CRATE_DIR)
	rm -rf						$(TARBALL_DIR)
	mkdir -p					$(TARBALL_DIR)
	rsync -a $(CRATE_DIR)/				$(TARBALL_DIR)
	test -d $(CRATES_CHECKOUT) || git clone $(CRATES_URL) $(CRATES_CHECKOUT)
	mkdir -p $(CRATES_CHECKOUT)/$(CRATE_NAME)
	tar cjf $(CRATES_CHECKOUT)/$(CRATE_NAME)/$(TARBALL_FILE) -H posix $(TARBALL_DIR)
	cd $(CRATES_CHECKOUT) && git add $(CRATE_NAME)/$(TARBALL_FILE)
	@echo "DEBUG: $(CRATE_DESCR)"
	cd $(CRATES_CHECKOUT) && git commit -m "$(CRATE_NAME) release $(CRATE_VERSION) $(shell date)" -m "$(CRATE_DESCR)"
	cd $(CRATES_CHECKOUT) && git commit --amend
	cd $(CRATES_CHECKOUT) && git push

alire_mk_commit:
	test -d $(CRATES_CHECKOUT) || git clone $(CRATES_URL) $(CRATES_CHECKOUT)
	cd $(CRATES_CHECKOUT) && git rev-list HEAD $(CRATE_NAME)/$(TARBALL_FILE) | head -n 1 >../$(CRATE_NAME)/$(TARBALL_COMMIT)
	rm -rf $(CRATES_CHECKOUT)

# Publish the crate

alire_mk_publish:
	-test -d $(INDEX_CHECKOUT) || git clone -b $(INDEX_BRANCH) git@github.com:pmunts/alire-index.git $(INDEX_CHECKOUT)
	-test -d $(INDEX_CHECKOUT) || git clone git@github.com:pmunts/alire-index.git $(INDEX_CHECKOUT) && cd $(INDEX_CHECKOUT) && git branch $(INDEX_BRANCH) && git checkout $(INDEX_BRANCH)
	-cd $(INDEX_CHECKOUT) && test -f $(INDEX_SUBDIR)/$(CRATE_MANIFEST) && git rm $(INDEX_SUBDIR)/$(CRATE_MANIFEST) && git commit -m "$(CRATE_NAME) drop    $(CRATE_VERSION)"
	ALIRE_MK_PUBLISH=yes $(ALR) --force publish $(PUBLISH_OPTIONS) https://raw.githubusercontent.com/pmunts/alire-crates/$(shell cat $(TARBALL_COMMIT))/$(CRATE_NAME)/$(TARBALL_FILE)
	mkdir -p $(INDEX_CHECKOUT)/$(INDEX_SUBDIR)
	cp alire/releases/$(CRATE_MANIFEST) $(INDEX_CHECKOUT)/$(INDEX_SUBDIR)
ifneq ($(wildcard msg.txt),)
	sed -i '1 s/^.*$$/$(CRATE_NAME) release $(CRATE_VERSION)/g' msg.txt
	cd $(INDEX_CHECKOUT) && git add $(INDEX_SUBDIR)/$(CRATE_MANIFEST) && git commit -F $(shell pwd)/msg.txt
else
	@echo "DEBUG: $(CRATE_DESCR)"
	cd $(INDEX_CHECKOUT) && git add $(INDEX_SUBDIR)/$(CRATE_MANIFEST) && git commit -m "$(CRATE_NAME) release $(CRATE_VERSION) $(shell date)" -m "$(CRATE_DESCR)"
endif
	cd $(INDEX_CHECKOUT) && git commit --amend

# Push the crate index checkout

alire_mk_push: alire_mk_publish
	cd $(INDEX_CHECKOUT) && git checkout $(INDEX_BRANCH) && git push -u origin $(INDEX_BRANCH)

# Create markdown file for long description

alire_mk_markdown: $(CRATE_NAME).html
	pandoc -f html -t gfm $(CRATE_NAME).html > $(CRATE_NAME).md

# Remove working files

alire_mk_clean:
	rm -rf alire $(CRATE_DIR) $(TARBALL_DIR) $(TARBALL_FILE) *.commit *.md *.tmp

alire_mk_reallyclean: alire_mk_clean
	rm -rf $(CRATES_CHECKOUT) $(INDEX_CHECKOUT)

alire_mk_distclean: alire_mk_reallyclean

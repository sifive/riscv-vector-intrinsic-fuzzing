RISCV_TOOLCHAIN:=
HOST=riscv64-unknown-elf
HOST32=riscv32-unknown-elf
SPIKE_SRC_PATH:=
INSTALL_LIB:=libsoftfloat.so
INSTALL_PROG:=spike
INSTALL_RISCV_PROG:=pk

SPIKE_BRANCH=$(shell git -C $(SPIKE_SRC_PATH) branch --show-current)
SPIKE_SHA1=$(shell git -C $(SPIKE_SRC_PATH) rev-parse HEAD)
SPIKE_REMOTE_URL=$(shell git -C $(SPIKE_SRC_PATH) config --get remote.origin.url)

PK_BRANCH=$(shell git -C $(PK_SRC_PATH) branch --show-current)
PK_SHA1=$(shell git -C $(PK_SRC_PATH) rev-parse HEAD)
PK_REMOTE_URL=$(shell git -C $(PK_SRC_PATH) config --get remote.origin.url)

NEW_BRANCH_NAME=$(SPIKE_BRANCH)-$(shell  git -C $(SPIKE_SRC_PATH) rev-parse --short HEAD)-$(PK_BRANCH)-$(shell  git -C $(PK_SRC_PATH) rev-parse --short HEAD)

pk_flag_rv32=--with-arch=rv32i

all: stamps/add-git

stamps/configure-spike:
	mkdir -p $(dir $@)
	mkdir -p build
	cd build && \
		$(SPIKE_SRC_PATH)/configure --prefix=`pwd`/../install
	touch $@

stamps/build-spike: stamps/configure-spike
	mkdir -p $(dir $@)
	cd build && $(MAKE)
	cd build && $(MAKE) install
	touch $@

stamps/configure-pk-%:
	mkdir -p $(dir $@)
	$(eval folder=$(@:stamps/configure%=build/build%))
	$(eval platform=$(@:stamps/configure-pk-%=%))
	mkdir -p ${folder}
	cd ${folder} && \
		PATH=$(RISCV_TOOLCHAIN):${PATH} $(PK_SRC_PATH)/configure --host=$(HOST) --prefix=`pwd`/../../install ${pk_flag_rv${platform}}
	touch $@

stamps/build-pk-%: stamps/configure-pk-%
	$(eval folder=$(@:stamps%=build%))
	cd $(folder) && \
		PATH=$(RISCV_TOOLCHAIN):${PATH} $(MAKE)
	cd $(folder) && $(MAKE) install
	touch $@

stamps/add-git: stamps/build-spike stamps/build-pk-32 stamps/build-pk-64
	mkdir -p $(dir $@)
	mkdir -p bin/${HOST} bin/${HOST32} lib
	cp $(addprefix install/bin/, $(INSTALL_PROG)) bin/
	cp $(addprefix install/${HOST}/bin/, $(INSTALL_RISCV_PROG)) bin/${HOST}
	cp $(addprefix install/${HOST32}/bin/, $(INSTALL_RISCV_PROG)) bin/${HOST32}
	cp $(addprefix install/lib/, $(INSTALL_LIB)) lib/
	git branch $(NEW_BRANCH_NAME)
	git checkout $(NEW_BRANCH_NAME)
	strip bin/spike
	git add bin lib
	git commit \
		-m "Prebuilt binary for '$(SPIKE_BRANCH)' branch" \
		-m "sha1: $(SPIKE_SHA1)" \
		-m "repo: $(SPIKE_REMOTE_URL)" \
		-m "Prebuilt binary for '$(PK_BRANCH)' branch" \
		-m "sha1: $(PK_SHA1)" \
		-m "repo: $(PK_REMOTE_URL)"
	git push origin $(NEW_BRANCH_NAME)

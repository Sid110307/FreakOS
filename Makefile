ASM = nasm
CC = gcc
LD = ld

OUT_DIR = bin
IMAGE = FreakOS.iso
KERNEL = kernel.bin

ASM_SOURCE_FILES = $(wildcard src/asm/*.asm)
ASM_OBJ_FILES = $(patsubst src/asm/%.asm,$(OUT_DIR)/asm/%.o,$(ASM_SOURCE_FILES))

SOURCE_FILES = $(wildcard src/*.c)
OBJ_FILES = $(patsubst src/%.c,$(OUT_DIR)/%.o,$(SOURCE_FILES))

ASMFLAGS = -f elf32
CFLAGS = -m32 -c -ffreestanding -mno-red-zone -O2 -Wall -Wextra
LDFLAGS = -m elf_i386 -T lib/linker.ld -z noexecstack
QEMUFLAGS = -serial mon:stdio -audiodev pa,id=speaker -machine pcspk-audiodev=speaker

.PHONY: all iso run clean
all: clean $(OUT_DIR)/$(KERNEL)

iso: $(ASM_OBJ_FILES) $(OBJ_FILES)
	mkdir -p $@/boot/grub
	cp $(OUT_DIR)/$(KERNEL) $@/boot/$(KERNEL)
	cp lib/grub.cfg $@/boot/grub/grub.cfg
	grub-mkrescue -o $(OUT_DIR)/$(IMAGE) $@

$(OUT_DIR)/asm/%.o: src/asm/%.asm
	mkdir -p $(OUT_DIR)/asm
	$(ASM) $(ASMFLAGS) $< -o $@

$(OUT_DIR)/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OUT_DIR)/$(KERNEL): $(ASM_OBJ_FILES) $(OBJ_FILES)
	$(LD) $(LDFLAGS) $^ -o $@

run: iso
	qemu-system-i386 $(QEMUFLAGS) -cdrom $(OUT_DIR)/$(IMAGE)

clean:
	rm -rf $(OUT_DIR) iso

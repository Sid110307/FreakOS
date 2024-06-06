ASM := nasm
CC := gcc
LD := ld

BIN_DIR := bin
SOURCE_DIR := src

IMAGE := FreakOS.iso
KERNEL := kernel.bin
LINKER_FILE := linker.ld

ASM_SOURCE_FILES := $(wildcard $(SOURCE_DIR)/asm/*.asm)
ASM_OBJ_FILES := $(patsubst $(SOURCE_DIR)/asm/%.asm,$(BIN_DIR)/asm/%.o,$(ASM_SOURCE_FILES))

SOURCE_FILES := $(wildcard $(SOURCE_DIR)/*.c)
OBJ_FILES := $(patsubst $(SOURCE_DIR)/%.c,$(BIN_DIR)/%.o,$(SOURCE_FILES))

ASMFLAGS := -f elf32
CFLAGS := -m32 -std=c11 -ffreestanding -mno-red-zone -O2 -Wall -Wextra
LDFLAGS := -m elf_i386 -nostdlib

.PHONY: all iso run clean
all: clean $(BIN_DIR)/$(KERNEL)

iso: $(ASM_OBJ_FILES) $(OBJ_FILES)
	mkdir -p $@/boot/grub
	cp $(BIN_DIR)/$(KERNEL) $@/boot/$(KERNEL)
	cp grub.cfg $@/boot/grub/grub.cfg
	grub-mkrescue -o $(BIN_DIR)/$(IMAGE) $@

$(BIN_DIR)/asm/%.o: $(SOURCE_DIR)/asm/%.asm
	mkdir -p $(BIN_DIR)/asm
	$(ASM) $(ASMFLAGS) $< -o $@

$(BIN_DIR)/%.o: $(SOURCE_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN_DIR)/$(KERNEL): $(ASM_OBJ_FILES) $(OBJ_FILES)
	$(LD) $(LDFLAGS) -T $(LINKER_FILE) $^ -o $@

run: iso
	qemu-system-i386 -cdrom $(BIN_DIR)/$(IMAGE) -serial mon:stdio

clean:
	rm -rf $(BIN_DIR)

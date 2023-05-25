BIN_DIR := bin
SOURCE_DIR := src

IMG_NAME := os.bin
SOURCE_FILES := $(wildcard $(SOURCE_DIR)/*.c)
OBJ_FILES := $(patsubst $(SOURCE_DIR)/%.c,$(BIN_DIR)/%.o,$(SOURCE_FILES))
LINKER_FILE := linker.ld

ASMFLAGS := -f elf32
CFLAGS := -m32 -std=gnu99 -ffreestanding -O2 -Wall -Wextra
LDFLAGS := -m elf_i386

.PHONY: all clean run iso
all: $(BIN_DIR)/$(IMG_NAME) run

clean:
	rm -rf $(BIN_DIR) iso

run: iso
	qemu-system-i386 -cdrom $(BIN_DIR)/os.iso

iso: $(BIN_DIR)/boot.o $(BIN_DIR)/kernel.o
	mkdir -p iso/boot/grub
	cp $(BIN_DIR)/$(IMG_NAME) iso/boot/$(IMG_NAME)
	cp grub.cfg iso/boot/grub/grub.cfg
	grub-mkrescue -o $(BIN_DIR)/os.iso iso

$(BIN_DIR)/boot.o: boot.asm
	mkdir -p $(BIN_DIR)
	nasm $(ASMFLAGS) $< -o $@

$(BIN_DIR)/kernel.o: $(SOURCE_FILES)
	mkdir -p $(BIN_DIR)
	gcc $(CFLAGS) -c $^ -o $@

$(BIN_DIR)/$(IMG_NAME): $(BIN_DIR)/boot.o $(BIN_DIR)/kernel.o
	ld $(LDFLAGS) -T $(LINKER_FILE) -o $@ $^

BIN_DIR := bin
SOURCE_DIR := src

IMG_NAME := os.img
LINKER_FILE := linker.ld

ASM_SOURCE_FILES := $(wildcard $(SOURCE_DIR)/asm/*.asm)
ASM_OBJ_FILES := $(patsubst $(SOURCE_DIR)/asm/%.asm,$(BIN_DIR)/asm/%.o,$(ASM_SOURCE_FILES))

SOURCE_FILES := $(wildcard $(SOURCE_DIR)/*.c)
OBJ_FILES := $(patsubst $(SOURCE_DIR)/%.c,$(BIN_DIR)/%.o,$(SOURCE_FILES))

FONT_FILES := $(wildcard $(SOURCE_DIR)/lib/fonts/*.psf)
FONT_OBJ_FILES := $(patsubst $(SOURCE_DIR)/lib/fonts/%.psf,$(BIN_DIR)/fonts/%.psf,$(FONT_FILES))

ASMFLAGS := -f elf32
CFLAGS := -m32 -std=gnu99 -ffreestanding -mno-red-zone -O2 -Wall -Wextra
LDFLAGS := -m elf_i386 -nostdlib

.PHONY: all clean run iso
all: clean $(BIN_DIR)/$(IMG_NAME) run

clean:
	rm -rf $(BIN_DIR) iso

run: iso
	qemu-system-i386 -cdrom $(BIN_DIR)/os.iso -serial mon:stdio

iso: $(ASM_OBJ_FILES) $(OBJ_FILES) $(FONT_OBJ_FILES)
	mkdir -p $@/boot/grub
	cp $(BIN_DIR)/$(IMG_NAME) $@/boot/$(IMG_NAME)
	cp grub.cfg $@/boot/grub/grub.cfg
	grub-mkrescue -o $(BIN_DIR)/os.iso $@

$(BIN_DIR)/asm/%.o: $(SOURCE_DIR)/asm/%.asm
	mkdir -p $(BIN_DIR)/asm
	nasm $(ASMFLAGS) $< -o $@

$(BIN_DIR)/%.o: $(SOURCE_DIR)/%.c
	gcc $(CFLAGS) -c $< -o $@

$(BIN_DIR)/fonts/%.psf: $(SOURCE_DIR)/lib/fonts/%.psf
	mkdir -p $(BIN_DIR)/fonts
	cp $< $@

$(BIN_DIR)/$(IMG_NAME): $(ASM_OBJ_FILES) $(OBJ_FILES)
	ld $(LDFLAGS) -T $(LINKER_FILE) $^ -o $@

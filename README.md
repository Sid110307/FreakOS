# FreakOS

> A simple operating system written in C and ASM.

## Requirements

- [NASM](https://www.nasm.us/)
- [GCC](https://gcc.gnu.org/)
- [GNU Make](https://www.gnu.org/software/make/)
- [GRUB](https://www.gnu.org/software/grub/)
- [QEMU](https://www.qemu.org/) (optional)

## Getting Started

- Clone the repository

```bash
$ git clone https://github.com/Sid110307/FreakOS.git
$ cd FreakOS
```

- Build the OS

```bash
$ make -s
```

- Run the OS on QEMU

```bash
$ make run -s
```

- To run the OS on real hardware

```bash
$ make iso -s
# The FreakOS.iso file will be created in the bin directory
# Burn the ISO file to a USB drive
$ dd if=bin/FreakOS.iso of=/dev/sdX bs=4M
```

## License

[MIT](https://opensource.org/licenses/MIT)

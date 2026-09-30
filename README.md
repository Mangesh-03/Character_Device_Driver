# Linux Character Device Driver

A Linux kernel character device driver implemented in C as a loadable kernel module. The project demonstrates the fundamentals of Linux character device driver development, kernel module lifecycle management, device registration, and communication between user space and kernel space.

## Overview

This project implements a simple character device named `character_driver`.

After loading the kernel module, the driver creates the device interface:

```text
/dev/character_driver
```

A user-space application can open the device, write data to it, read the stored data back, and close the device.

## Features

- Loadable Linux kernel module
- Character device registration
- `/dev/character_driver` device interface
- `open`, `read`, `write`, and `release` operations
- User-space to kernel-space data transfer
- Kernel-space to user-space data transfer
- Kernel logging using `printk`
- Makefile-based kernel module compilation

## Architecture

```text
                    User Space
                        |
                        v
              +-------------------+
              |  User Application  |
              +-------------------+
                        |
                 open / read / write
                        |
                        v
              /dev/marvellous_driver
                        |
                        v
                    Kernel Space
                        |
              +-------------------+
              | Character Driver  |
              +-------------------+
                 |      |      |
                open   read   write
                 |      |      |
                 +------+------+
                        |
                  Message Buffer
```

## Driver Operations

| Operation | Purpose |
|-----------|---------|
| `open()` | Opens the character device |
| `read()` | Transfers data from kernel space to user space |
| `write()` | Transfers data from user space to kernel space |
| `release()` | Handles device close operation |

## User-Kernel Data Transfer

The driver uses `copy_from_user()` to transfer data from user space into the kernel buffer and `copy_to_user()` to transfer data from the kernel buffer back to user space.

## Kernel Module Lifecycle

### Initialization

During module initialization, the driver:

1. Registers the character device.
2. Creates the device class.
3. Creates the device entry.
4. Makes the device available through `/dev/character_driver`.

### Cleanup

When the module is unloaded, the driver:

1. Removes the device.
2. Destroys the device class.
3. Unregisters the character device.

## Project Structure

```text
.
├── CharacterDriver.c
├── CharacterDriverClient.c
├── Makefile
└── README.md
```

- **CharacterDriver.c** — Linux kernel character device driver implementation.
- **CharacterDriverClient.c** — User-space application for testing read/write operations.
- **Makefile** — Builds the kernel module using the Linux kernel build system.

## Requirements

- Linux operating system
- GCC
- GNU Make
- Linux kernel headers
- Root/sudo privileges for loading and unloading the kernel module

## Build

Build the kernel module using:

```bash
make
```

The Makefile uses the running kernel's build directory:

```text
/lib/modules/$(shell uname -r)/build
```

## Load the Driver

```bash
sudo insmod CharacterDriver.ko
```

Verify that the module is loaded:

```bash
lsmod | grep CharacterDriver
```

Check kernel messages:

```bash
dmesg | tail
```

## Check the Device

```bash
ls -l /dev/character_driver
```

## Run the User Application

Compile the test application:

```bash
gcc CharacterDriverClient.c -o test
```

Run it:

```bash
sudo ./test
```

The application opens the character device, writes data to the driver, reads the stored data back, and closes the device.

## Unload the Driver

```bash
sudo rmmod CharacterDriver
```

Check the kernel messages:

```bash
dmesg | tail
```

## Concepts Demonstrated

- Linux kernel modules
- Character device drivers
- Device registration
- Device nodes
- `struct file_operations`
- Kernel-space and user-space interaction
- `copy_to_user()` and `copy_from_user()`
- Kernel logging with `printk()`
- Module initialization and cleanup
- Linux kernel build system
- GCC and Make
- Linux command-line development

## Learning Outcomes

This project provided practical experience with the structure and lifecycle of a Linux character device driver, including kernel module compilation, device registration, file-operation callbacks, user-kernel data transfer, device-node creation, and driver cleanup.

## Author

**Mangesh Bedre**


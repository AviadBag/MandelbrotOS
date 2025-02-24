#ifndef __STIVALE__STIVALE2_H__
#define __STIVALE__STIVALE2_H__

/*
Copyright 2019, 2020, 2021 mintsuki and contributors.

Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

    Redistributions of source code must retain the above copyright notice, this
list of conditions and the following disclaimer.

    Redistributions in binary form must reproduce the above copyright notice,
this list of conditions and the following disclaimer in the documentation and/or
other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include <stdint.h>

struct stivale2_tag_t {
  uint64_t identifier;
  uint64_t next;
} __attribute__((__packed__));

/* --- Header --------------------------------------------------------------- */
/*  Information passed from the kernel to the bootloader                      */

struct stivale2_header_t {
  uint64_t entry_point;
  uint64_t stack;
  uint64_t flags;
  uint64_t tags;
} __attribute__((__packed__));

#define STIVALE2_HEADER_TAG_FRAMEBUFFER_ID 0x3ecc1bc43d0f7971

#define STIVALE2_HEADER_TAG_FB_MTRR_ID 0x4c7bb07731282e00

struct stivale2_header_tag_framebuffer_t {
  struct stivale2_tag_t tag;
  uint16_t framebuffer_width;
  uint16_t framebuffer_height;
  uint16_t framebuffer_bpp;
} __attribute__((__packed__));

#define STIVALE2_HEADER_TAG_SMP_ID 0x1ab015085f3273df

struct stivale2_header_tag_smp_t {
  struct stivale2_tag_t tag;
  uint64_t flags;
} __attribute__((__packed__));

#define STIVALE2_HEADER_TAG_5LV_PAGING_ID 0x932f477032007e8f

/* --- Struct --------------------------------------------------------------- */
/*  Information passed from the bootloader to the kernel                      */

struct stivale2_struct_t {
#define STIVALE2_BOOTLOADER_BRAND_SIZE 64
  char bootloader_brand[STIVALE2_BOOTLOADER_BRAND_SIZE];

#define STIVALE2_BOOTLOADER_VERSION_SIZE 64
  char bootloader_version[STIVALE2_BOOTLOADER_VERSION_SIZE];

  uint64_t tags;
} __attribute__((__packed__));

#define STIVALE2_STRUCT_TAG_CMDLINE_ID 0xe5e76a1b4597a781

struct stivale2_struct_tag_cmdline_t {
  struct stivale2_tag_t tag;
  uint64_t cmdline;
} __attribute__((__packed__));

#define STIVALE2_STRUCT_TAG_MEMMAP_ID 0x2187f79e8612de07

#define STIVALE2_MMAP_USABLE 1
#define STIVALE2_MMAP_RESERVED 2
#define STIVALE2_MMAP_ACPI_RECLAIMABLE 3
#define STIVALE2_MMAP_ACPI_NVS 4
#define STIVALE2_MMAP_BAD_MEMORY 5
#define STIVALE2_MMAP_BOOTLOADER_RECLAIMABLE 0x1000
#define STIVALE2_MMAP_KERNEL_AND_MODULES 0x1001

struct stivale2_mmap_entry_t {
  uint64_t base;
  uint64_t length;
  uint32_t type;
  uint32_t unused;
} __attribute__((__packed__));

struct stivale2_struct_tag_memmap_t {
  struct stivale2_tag_t tag;
  uint64_t entries;
  struct stivale2_mmap_entry_t memmap[];
} __attribute__((__packed__));

#define STIVALE2_STRUCT_TAG_FRAMEBUFFER_ID 0x506461d2950408fa

#define STIVALE2_FBUF_MMODEL_RGB 1

struct stivale2_struct_tag_framebuffer_t {
  struct stivale2_tag_t tag;
  uint64_t framebuffer_addr;
  uint16_t framebuffer_width;
  uint16_t framebuffer_height;
  uint16_t framebuffer_pitch;
  uint16_t framebuffer_bpp;
  uint8_t memory_model;
  uint8_t red_mask_size;
  uint8_t red_mask_shift;
  uint8_t green_mask_size;
  uint8_t green_mask_shift;
  uint8_t blue_mask_size;
  uint8_t blue_mask_shift;
} __attribute__((__packed__));

#define STIVALE2_STRUCT_TAG_FB_MTRR_ID 0x6bc1a78ebe871172

#define STIVALE2_STRUCT_TAG_MODULES_ID 0x4b6fe466aade04ce

struct stivale2_module_t {
  uint64_t begin;
  uint64_t end;

#define STIVALE2_MODULE_STRING_SIZE 128
  char string[STIVALE2_MODULE_STRING_SIZE];
} __attribute__((__packed__));

struct stivale2_struct_tag_modules_t {
  struct stivale2_tag_t tag;
  uint64_t module_count;
  struct stivale2_module_t modules[];
} __attribute__((__packed__));

#define STIVALE2_STRUCT_TAG_RSDP_ID 0x9e1786930a375e78

struct stivale2_struct_tag_rsdp_t {
  struct stivale2_tag_t tag;
  uint64_t rsdp;
} __attribute__((__packed__));

#define STIVALE2_STRUCT_TAG_EPOCH_ID 0x566a7bed888e1407

struct stivale2_struct_tag_epoch_t {
  struct stivale2_tag_t tag;
  uint64_t epoch;
} __attribute__((__packed__));

#define STIVALE2_STRUCT_TAG_FIRMWARE_ID 0x359d837855e3858c

#define STIVALE2_FIRMWARE_BIOS (1 << 0)

struct stivale2_struct_tag_firmware_t {
  struct stivale2_tag_t tag;
  uint64_t flags;
} __attribute__((__packed__));

#define STIVALE2_STRUCT_TAG_SMP_ID 0x34d1d96339647025

struct stivale2_smp_info_t {
  uint32_t processor_id;
  uint32_t lapic_id;
  uint64_t target_stack;
  uint64_t goto_address;
  uint64_t extra_argument;
} __attribute__((__packed__));

struct stivale2_struct_tag_smp_t {
  struct stivale2_tag_t tag;
  uint64_t flags;
  uint32_t bsp_lapic_id;
  uint32_t unused;
  uint64_t cpu_count;
  struct stivale2_smp_info_t smp_info[];
} __attribute__((__packed__));

#define STIVALE2_STRUCT_TAG_PXE_SERVER_INFO 0x29d1e96239247032

struct stivale2_struct_tag_pxe_server_info_t {
  struct stivale2_tag_t tag;
  uint32_t server_ip;
} __attribute__((__packed__));

#define STIVALE2_STRUCT_TAG_MMIO32_UART 0xb813f9b8dbc78797

struct stivale2_struct_tag_mmio32_uart_t {
  struct stivale2_tag_t tag;
  uint64_t addr;
} __attribute__((__packed__));

#define STIVALE2_STRUCT_TAG_DTB 0xabb29bd49a2833fa

struct stivale2_struct_tag_dtb_t {
  struct stivale2_tag_t tag;
  uint64_t addr;
  uint64_t size;
} __attribute__((__packed__));

#define STIVALE2_STRUCT_TAG_VMAP 0xb0ed257db18cb58f

struct stivale2_struct_vmap_t {
  struct stivale2_tag_t tag;
  uint64_t addr;
} __attribute__((__packed__));

/* Start of own code */
struct stivale2_tag_t *
stivale2_get_tag(struct stivale2_struct_t *bootloader_info, uint64_t tag_id);
/* End of own code */

#endif

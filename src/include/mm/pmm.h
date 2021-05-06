#ifndef __PMM_H__
#define __PMM_H__

#include <boot/stivale2.h>
#include <stddef.h>

#define PAGE_SIZE 4096 // 4KB

int init_pmm(struct stivale2_mmap_entry_t *memory_map, size_t memory_entries);
void free_pages(void *adr, size_t page_count);
void *pmalloc(size_t pages);
void *pcalloc(size_t pages);

#endif // !__PMM_H__

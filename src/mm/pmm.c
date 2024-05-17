/*
 *  CREDITS: asterd-og on GitHub
 *  https://github.com/asterd-og/QuasarOS/
 */

#include <mm/pmm.h>
#include <limine.h>
#include <mm/bitmap.h>
#include <arch/x86_64/cpu/serial.h>

u8 *pmm_bitmap = NULL;
u64 pmm_free_pages = 0;
u64 pmm_used_pages = 0;
u64 pmm_total_pages = 0;
u64 pmm_last_page = 0;

struct limine_memmap_request memmap_request = {
    .id = LIMINE_MEMMAP_REQUEST,
    .revision = 0
};

struct limine_memmap_response* pmm_memmap = NULL;

void pmm_init() {
    pmm_memmap = memmap_request.response;
    struct limine_memmap_entry** entries = pmm_memmap->entries;
  
    u64 higher_address = 0;
    u64 top_address = 0;

    struct limine_memmap_entry* entry;

    for (u64 i = 0; i < pmm_memmap->entry_count; i++) {
        entry = entries[i];
        if (entry->type != LIMINE_MEMMAP_USABLE)
        continue;
        top_address = entry->base + entry->length;
        if (top_address > higher_address)
        higher_address = top_address;
    }

    pmm_total_pages = higher_address / PAGE_SIZE;
    u64 bitmap_size = ALIGN_UP(pmm_total_pages / 8, PAGE_SIZE);

    for (u64 i = 0; i < pmm_memmap->entry_count; i++) {
        entry = entries[i];
        if (entry->type != LIMINE_MEMMAP_USABLE || entry->length < bitmap_size) continue;
        pmm_bitmap = (u8*)HIGHER_HALF(entry->base);
        memset(pmm_bitmap, 0xFF, bitmap_size);
        entry->base += bitmap_size;
        entry->length -= bitmap_size;
        break;
    }

    for (u64 i = 0; i < pmm_memmap->entry_count; i++) {
        entry = entries[i];
        if (entry->type != LIMINE_MEMMAP_USABLE) continue;
        for (u64 j = 0; j < entry->length; j += PAGE_SIZE)
        bitmap_clear(pmm_bitmap, (entry->base + j) / PAGE_SIZE);
    }

    printf("\033[92m[  OK  ]\033[0m PMM Initialized.\n");
}

void* pmm_alloc(size_t n) {
    u64 pages = 0;
    while (pages < n) {
        if (pmm_last_page == pmm_total_pages) {
            panic("OUT_OF_MEMORY");
        }
        if (bitmap_get(pmm_bitmap, pmm_last_page + pages) == 0)
            pages++;
        else {
            pmm_last_page++;
            pages = 0;
        }
    }
    for (u64 i = 0; i < n; i++)
        bitmap_set(pmm_bitmap, pmm_last_page + i);
    pmm_last_page += pages;
    return (void*)((pmm_last_page - n) * PAGE_SIZE); // Return the start of the pages
}

void pmm_free(void* ptr, size_t n) {
    u64 idx = (u64)ptr / PAGE_SIZE;
    for (u64 i = 0; i < n; i++)
        bitmap_clear(pmm_bitmap, idx + i);
    pmm_last_page = idx;
}
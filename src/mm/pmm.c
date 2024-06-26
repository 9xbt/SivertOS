/*
 *  CREDITS: asterd-og on GitHub
 *  https://github.com/asterd-og/ZanOS/
 */

#include <mm/pmm.h>
#include <limine.h>
#include <lib/libc.h>
#include <lib/bitmap.h>
#include <arch/x86_64/cpu/serial.h>

u8* pmm_bitmap = NULL;
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
        if (entry->type != LIMINE_MEMMAP_USABLE) continue;
        top_address = entry->base + entry->length;
        if (top_address > higher_address) higher_address = top_address;
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
    serial_printf("pmm_init(): PMM Initialised at %lx with bitmap size of %ld.\n", (u64)pmm_bitmap, bitmap_size);
}

u64 pmm_find_pages(usize n) {
    u64 pages = 0;
    u64 first_page = pmm_last_page;
    while (pages < n) {
        if (pmm_last_page == pmm_total_pages) {
            serial_printf("pmm_alloc(): Ran out of memory.\n");
            return 0;
        }
        if (bitmap_get(pmm_bitmap, pmm_last_page + pages) == 0) {
            pages++;
                if (pages == n) {
                    for (u64 i = 0; i < pages; i++)
                    bitmap_set(pmm_bitmap, pmm_last_page + i);
                    pmm_last_page += pages;
                    return first_page; // Return the start of the pages
                }
            }
            else {
            pmm_last_page += (pages == 0 ? 1 : pages);
            first_page = pmm_last_page;
            pages = 0;
        }
    }
    return 0;
}

void* pmm_alloc(usize n) {
    u64 first = pmm_find_pages(n);
    if (first == 0) {
        pmm_last_page = 0;
        first = pmm_find_pages(n);
        if (first == 0) {
            panic("OUT_OF_MEMORY");
            return NULL;
        }
    }
    return (void*)(first * PAGE_SIZE);
}

void pmm_free(void* ptr, usize n) {
    u64 idx = (u64)ptr / PAGE_SIZE;
    for (u64 i = 0; i < n; i++)
        bitmap_clear(pmm_bitmap, idx + i);
}

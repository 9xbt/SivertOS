#include <fs/vfs.h>
#include <lib/libc.h>
#include <lib/alloc.h>
#include <lib/printf.h>
#include <apps/shell.h>

void shell_cmd_cat(int argc, char** argv) {
    vfs_dirent* dirent;
    int i = 0;
    while ((dirent = vfs_readdir(shell_current_dir, i)) != NULL) {
        vfs_node* node = vfs_finddir(shell_current_dir, dirent->name);

        if (!strcmp(dirent->name, argv[0] + 4) && node->type == VFS_FILE) {
            char *buf = kmalloc(1024);
            vfs_read(node, buf, 1024);
            printf("%s\n", buf);
            return;
        }

        kfree(dirent->name);
        kfree(dirent);
        kfree(node->name);
        kfree(node);
        i++;
    }

    printf("cat: file \"%s\" not found\n", argv[0] + 4);
}
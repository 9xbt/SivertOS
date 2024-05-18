#include <fs/vfs.h>
#include <lib/alloc.h>
#include <lib/printf.h>

void shell_cmd_ls(int argc, char** argv) {
    vfs_dirent* dirent;
    int i = 0;
    while ((dirent = vfs_readdir(vfs_root, i)) != NULL) {
        vfs_node* node = vfs_finddir(vfs_root, dirent->name);

        //char *buf = kmalloc(1024);
        //vfs_read(node, buf, 1024);
        //printf(buf);

        printf("%s%s\033[0m  ", (node->type == VFS_DIRECTORY ? "\033[94m" : "\033[91m"), dirent->name);
        kfree(dirent->name);
        kfree(dirent);
        kfree(node->name);
        kfree(node);
        i++;
    }

    printf("\n");
}
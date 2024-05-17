#include <fs/vfs.h>
#include <lib/alloc.h>
#include <lib/printf.h>

void shell_cmd_ls(int argc, char** argv) {
    vfs_direntry* dirent;
    int i = 0;
    while ((dirent = vfs_readdir(vfs_root, i)) != NULL) {
        vfs_node* node = vfs_finddir(vfs_root, dirent->name);
        printf("%s%s\033[0m  ", (node->type == VFS_DIRECTORY ? "\e[94m" : "\e[91m"), dirent->name);
        kfree(dirent->name);
        kfree(dirent);
        //kfree(node->name);
        //kfree(node);
        i++;
    }

    printf("\n");
}
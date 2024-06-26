#include <fs/vfs.h>
#include <lib/alloc.h>
#include <lib/printf.h>
#include <apps/shell.h>

void shell_cmd_ls(int argc, char** argv) {
    vfs_dirent* dirent;
    int i = 0;
    while ((dirent = vfs_readdir(shell_current_dir, i)) != NULL) {
        vfs_node* node = vfs_finddir(shell_current_dir, dirent->name);

        printf("%s%s\033[0m  ", (node->type == VFS_DIRECTORY ? "\033[94m" : "\033[91m"), dirent->name);
        kfree(dirent->name);
        kfree(dirent);
        kfree(node->name);
        kfree(node);
        i++;
    }

    printf("\n");
}
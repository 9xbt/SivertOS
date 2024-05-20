#include <apps/shell.h>

void shell_cmd_cd(int argc, char** argv) {
    vfs_dirent* dirent;
    int i = 0;
    while ((dirent = vfs_readdir(shell_current_dir, i)) != NULL) {
        vfs_node* node = vfs_finddir(shell_current_dir, dirent->name);

        if (!strcmp(dirent->name, argv[0] + 3) && node->type == VFS_DIRECTORY) {
            shell_current_dir = node;
            return;
        }

        kfree(dirent->name);
        kfree(dirent);
        kfree(node->name);
        kfree(node);
        i++;
    }

    printf("cd: directory \"%s\" not found\n", argv[0] + 3);
}